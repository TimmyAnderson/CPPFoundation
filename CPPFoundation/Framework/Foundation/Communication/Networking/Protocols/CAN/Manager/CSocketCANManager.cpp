//----------------------------------------------------------------------------------------------------------------------
#include "CSocketCANManager.h"
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Socket/CSocketCANReceiveFromParameters.h>
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Socket/CSocketCANReceiveFromResult.h>
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Socket/CSocketCANSendToParameters.h>
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Socket/CSocketCANSendToResult.h>
#include <Framework/Foundation/Exceptions/CSocketException.h>
#include <Framework/Foundation/Exceptions/CUnknownException.h>
#include <Framework/Foundation/Threads/CLock.h>
#include <Framework/Platform/Sockets/CSocketWaitObject.h>
#include "CSocketCANManagerMessageResponseSocketAdd.h"
#include "CSocketCANManagerMessageResponseSocketClose.h"
#include "CSocketCANManagerMessageResponseSocketError.h"
#include "CSocketCANManagerMessageResponseSocketRead.h"
#include "CSocketCANManagerMessageResponseSocketRemove.h"
#include "CSocketCANManagerMessageResponseSocketWrite.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace CPPFoundation::Platform;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManager::CSocketCANManager(CLogWriter& LogWriter, Size ReadBufferSize)
		: CThread(LogWriter,CString::Format("SOCKET CAN MANAGER THREAD")), MLogCategorySocketManager(CString::Format("SOCKET CAN MANAGER")), MSocketManagerMutex(), MExitEvent(false), MCallbackDispatcher(GetLogWriter()), MSocketCollection(), MRequestTSCollection(), MWaitObject(new CSocketWaitObject()), MReadBuffer(new CByteBuffer(ReadBufferSize))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManager::~CSocketCANManager(void)
	{
		MCallbackDispatcher.ClearEvents();

		if (IsThreadRunning()==true)
		{
			StopThread();
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CLogCategory& CSocketCANManager::GetLogCategorySocketManager(void) const noexcept
	{
		return(MLogCategorySocketManager);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManager::FireEvent(CCSPSocketCANManagerMessageResponse MessageResponse) noexcept
	{
		try
		{
			MCallbackDispatcher.DispatchEvent(MessageResponse);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER FAILED to FIRE EVENT [",MessageResponse,"] !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER FAILED to FIRE EVENT [",MessageResponse,"] !"),CUnknownException()));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManager::SetThreadExitFlag(void)
	{
		// First EXIT EVENT MUST be SET.
		MExitEvent.Set();

		// Just after that THREAD MUST be AWAKEN.
		MWaitObject->SetEvent();
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketCANManager::HasThreadExitFlagSet(void)
	{
		if (MExitEvent.Wait(0)==true)
		{
			if (HasThreadExiting(CTimeout::GetInfinite())==true)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManager::ChangeSocketState(CSocketCANManagerSocketData& SocketData, CSocketCANManagerSocketData::ESocketCANManagerSocketState State, CSPSocketCANManagerMessageResponse MessageResponse)
	{
		if (SocketData.GetSocketState()!=State)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("CAN SOCKET MANAGER for SOCKET [",SocketData.GetSocket()->GetSocketID(),"] CHANGED STATE STATE [",CSocketCANManagerSocketData::SocketStateToString(SocketData.GetSocketState())," -> ",CSocketCANManagerSocketData::SocketStateToString(State),"] !")));

			SocketData.SetSocketState(State);

			if (MessageResponse!=nullptr)
			{
				FireEvent(MessageResponse);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManager::ChangeSocketStateToFailedState(CSocketCANManagerSocketData& SocketData)
	{
		if (SocketData.GetSocketState()!=CSocketCANManagerSocketData::ESocketCANManagerSocketState::E_FAILED)
		{
			ChangeSocketState(SocketData,CSocketCANManagerSocketData::ESocketCANManagerSocketState::E_FAILED,CSPSocketCANManagerMessageResponse(new CSocketCANManagerMessageResponseSocketError(SocketData.GetSocket()->GetSocketID())));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManager::RemoveExpiredWriteOperations(void)
	{
		CSteadyClock::Milliseconds								CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();

		for(CSocketCollection::CMapIterator Iterator1=MSocketCollection.Begin();Iterator1!=MSocketCollection.End();Iterator1++)
		{
			if (HasThreadExitFlagSet()==true)
			{
				return;
			}

			CSocketCANManagerSocketData&						SocketData=Iterator1->GetSecond();
			CSocketCANManagerWriteOperationCollection&			WriteOperationCollection=SocketData.GetWriteOperations();

			for(CSocketCANManagerWriteOperationCollection::CListIterator Iterator2=WriteOperationCollection.Begin();Iterator2!=WriteOperationCollection.End();)
			{
				if (Iterator2->GetPacket()->GetWriteExpirationTime().HasExpired(CurrentTimeInMS)==true)
				{
					MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("CAN SOCKET MANAGER FAILED to WRITE to SOCKET [",SocketData.GetSocket()->GetSocketID(),"] ! WRITE OPERATION EXPIRED !")));

					FireEvent(CCSPSocketCANManagerMessageResponse(new CSocketCANManagerMessageResponseSocketWrite(SocketData.GetSocket()->GetSocketID(),Iterator2->GetPacket()->GetMessageContext(),false,Iterator2->GetPacket()->GetDestinationAddress(),Iterator2->GetPacket()->GetData(),Iterator2->GetNumberOfBytesWritten())));

					CSocketCANManagerWriteOperationCollection::CListIterator	RemoveIterator=Iterator2++;

					WriteOperationCollection.Erase(RemoveIterator);
				}
				else
				{
					Iterator2++;
				}
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManager::WriteToSockets(void)
	{
		for(CSocketCollection::CMapIterator Iterator=MSocketCollection.Begin();Iterator!=MSocketCollection.End();Iterator++)
		{
			if (HasThreadExitFlagSet()==true)
			{
				return;
			}

			CSocketCANManagerSocketData&						SocketData=Iterator->GetSecond();
			
			try
			{
				CSocketCANManagerWriteOperationCollection&		WriteOperationCollection=SocketData.GetWriteOperations();

				if (SocketData.GetSocketState()==CSocketCANManagerSocketData::ESocketCANManagerSocketState::E_OPENED)
				{
					if (WriteOperationCollection.GetLength()>0)
					{
						CSocketCANManagerWriteOperation&		WriteOperation=WriteOperationCollection.Front();
						CCSPSocketCANManagerMessageRequestSocketWrite	Packet=WriteOperation.GetPacket();
						CSocketCANAddress						Address(Packet->GetDestinationAddress());
						Size									Length=WriteOperation.GetNumberOfBytesToWrite();
						CSocketCANSendToParameters				Parameters(Address,Packet->GetData(),WriteOperation.GetNumberOfBytesWritten(),Length);
						CSocketCANSendToResult					Result;
						
						SocketData.GetSocket()->SendTo(Parameters,Result);
						
						WriteOperation.AddNumberOfBytesWritten(Result.GetNumberOfSentBytes());

						if (WriteOperation.GetNumberOfBytesToWrite()<=0)
						{
							MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("CAN SOCKET MANAGER SUCCESSFULLY WRITTEN DATA to SOCKET [",Packet->GetSocketID(),"] ! ADDRESS [",Packet->GetDestinationAddress(),"] DATA [",Packet->GetData(),"] LENGTH [",Packet->GetData()->GetLength(),"] !")));
							
							FireEvent(CCSPSocketCANManagerMessageResponse(new CSocketCANManagerMessageResponseSocketWrite(Packet->GetSocketID(),Packet->GetMessageContext(),true,Packet->GetDestinationAddress(),Packet->GetData(),Packet->GetData()->GetLength())));

							WriteOperationCollection.PopFront();
						}
						else
						{
							MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER detected PARTIAL WRITE for SOCKET [",Packet->GetSocketID(),"] ! NUMBER of BYTES WRITTEN [",WriteOperation.GetNumberOfBytesWritten(),"] NUMBER of BYTES to WRITE [",WriteOperation.GetNumberOfBytesToWrite(),"] !")));
						}
					}
				}
			}
			catch(const CException& E)
			{
				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("CAN SOCKET MANAGER FAILED to WRITE DATA to SOCKET [",SocketData.GetSocket()->GetSocketID(),"] !"),E));

				CancelAllWriteOperations(SocketData.GetSocket()->GetSocketID());

				// CAN SOCKET is NOT FAILED because ERROR can occur even if PACKET was sent to INVALID ENDPOINT but SOCKET remains VALID.
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManager::ReadFromSockets(void)
	{
		for(CSocketCollection::CMapIterator Iterator=MSocketCollection.Begin();Iterator!=MSocketCollection.End();Iterator++)
		{
			if (HasThreadExitFlagSet()==true)
			{
				return;
			}

			CSocketCANManagerSocketData&						SocketData=Iterator->GetSecond();

			try
			{
				if (SocketData.GetSocketState()==CSocketCANManagerSocketData::ESocketCANManagerSocketState::E_OPENED)
				{
					CSocketCANReceiveFromParameters				Parameters(MReadBuffer,0,MReadBuffer->GetLength());
					CSPSocketCAN								Socket=SocketData.GetSocket().DynamicCast<CSocketCAN>();
					CSocketCANReceiveFromResult					Result;
					
					Socket->ReceiveFrom(Parameters,Result);

					if (Result.GetNumberOfReceivedBytes()>0)
					{
						const CSocketCANAddress&				Address=Result.GetCANAddress();
						CSPByteBuffer							Data(new CByteBuffer(MReadBuffer->GetRawData(),Result.GetNumberOfReceivedBytes()));

						MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("CAN SOCKET MANAGER SUCCESSFULLY READ DATA from SOCKET [",SocketData.GetSocket()->GetSocketID(),"] ! ADDRESS [",Address,"] DATA [",Data,"] LENGTH [",Data->GetLength(),"] !")));

						FireEvent(CCSPSocketCANManagerMessageResponse(new CSocketCANManagerMessageResponseSocketRead(Socket->GetSocketID(),Address,Data)));
					}
				}
			}
			catch(const CException& E)
			{
				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("CAN SOCKET MANAGER FAILED to READ DATA from SOCKET [",SocketData.GetSocket()->GetSocketID(),"] !"),E));

				// CAN SOCKET is FAILED if an ERROR occurs.
				ChangeSocketStateToFailedState(SocketData);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManager::WaitForSocketEvents(void)
	{
		try
		{
			CSteadyClock::Milliseconds							CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();
			CTimeout											Timeout=(MRequestTSCollection.GetLength()==0) ? CTimeout::GetInfinite() : CTimeout::GetZero();
			CVector<CSocketWaitState>							SocketStates;

			SocketStates.ReserveCapacity(MSocketCollection.GetLength());

			for(CSocketCollection::CKeyValuePair& Pair : MSocketCollection)
			{
				CSocketCANManagerSocketData&					SocketData=Pair.GetSecond();

				if (SocketData.GetSocketState()==CSocketCANManagerSocketData::ESocketCANManagerSocketState::E_OPENED)
				{
					ESocketWaitFlags							WaitFlags=ESocketWaitFlags::E_READ;

					if (SocketData.GetWriteOperations().GetLength()>0)
					{
						WaitFlags|=ESocketWaitFlags::E_WRITE;
					}

					SocketStates.Add(CSocketWaitState(SocketData.GetSocket(),WaitFlags));
				}

				if (Timeout.IsZero()==false)
				{
					for(const CSocketCANManagerWriteOperation& WriteOperation : SocketData.GetWriteOperations())
					{
						CTimeout								WriteOperationTimeout=WriteOperation.GetPacket()->GetWriteExpirationTime().CalculateTimeout(CurrentTimeInMS);

						Timeout=CTimeout::Min(Timeout,WriteOperationTimeout);
					}
				}
			}

			MWaitObject->WaitForEvent(SocketStates,Timeout);

			for(const CSocketWaitState& SocketState : SocketStates)
			{
				CSocketCANManagerSocketData&					SocketData=MSocketCollection[SocketState.GetSocket()->GetSocketID()];
				ESocketWaitResultFlags							ResultFlags=SocketState.GetWaitResultFlags();

				if ((ResultFlags & ESocketWaitResultFlags::E_ERROR)!=ESocketWaitResultFlags::E_NONE)
				{
					MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("CAN SOCKET MANAGER DETECTED that SOCKET [",SocketState.GetSocket()->GetSocketID(),"] FAILED !")));

					CancelAllWriteOperations(SocketState.GetSocket()->GetSocketID());

					ChangeSocketStateToFailedState(SocketData);
				}
				else if ((ResultFlags & ESocketWaitResultFlags::E_CLOSE)!=ESocketWaitResultFlags::E_NONE)
				{
					MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("CAN SOCKET MANAGER DETECTED that SOCKET [",SocketState.GetSocket()->GetSocketID(),"] was CLOSED !")));

					CancelAllWriteOperations(SocketState.GetSocket()->GetSocketID());

					ChangeSocketState(SocketData,CSocketCANManagerSocketData::ESocketCANManagerSocketState::E_CLOSED,CSPSocketCANManagerMessageResponse(new CSocketCANManagerMessageResponseSocketClose(SocketState.GetSocket()->GetSocketID())));
				}
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("CAN SOCKET MANAGER FAILED FATALLY ! ALL SOCKETS are DISABLED !"),E));

			for(CSocketCollection::CKeyValuePair& Pair : MSocketCollection)
			{
				CSocketCANManagerSocketData&					SocketData=Pair.GetSecond();

				CancelAllWriteOperations(SocketData.GetSocket()->GetSocketID());

				ChangeSocketStateToFailedState(SocketData);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManager::CancelAllWriteOperations(const CSocketID& SocketID)
	{
		CSocketCANManagerSocketData&							SocketData=MSocketCollection[SocketID];

		for(const CSocketCANManagerWriteOperation& WriteOperation : SocketData.GetWriteOperations())
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("CAN SOCKET MANAGER FAILED to WRITE DATA to SOCKET [",SocketData.GetSocket()->GetSocketID(),"] ! OPERATION was CANCELLED !")));

			FireEvent(CCSPSocketCANManagerMessageResponse(new CSocketCANManagerMessageResponseSocketWrite(SocketData.GetSocket()->GetSocketID(),WriteOperation.GetPacket()->GetMessageContext(),false,WriteOperation.GetPacket()->GetDestinationAddress(),WriteOperation.GetPacket()->GetData(),WriteOperation.GetNumberOfBytesWritten())));
		}

		SocketData.ClearWriteOperations();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManager::ProcessOperations(void)
	{
		if (HasThreadExitFlagSet()==true)
		{
			return;
		}

		RemoveExpiredWriteOperations();

		if (HasThreadExitFlagSet()==true)
		{
			return;
		}

		WriteToSockets();

		if (HasThreadExitFlagSet()==true)
		{
			return;
		}

		WaitForSocketEvents();

		if (HasThreadExitFlagSet()==true)
		{
			return;
		}

		ReadFromSockets();
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManager::ProcessSocketAdd(CCSPSocketCANManagerMessageRequestSocketAdd Request)
	{
		if (MSocketCollection.Contains(Request->GetSocketID())==false && MSocketCollection.GetLength()<MWaitObject->GetMaximumNumberOfSocket())
		{
			MSocketCollection.Add(Request->GetSocketID(),CSocketCANManagerSocketData(Request->GetSocket()));

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("CAN SOCKET MANAGER SUCCEESSFULLY ADDED SOCKET [",Request->GetSocketID(),"] !")));

			FireEvent(CCSPSocketCANManagerMessageResponse(new CSocketCANManagerMessageResponseSocketAdd(Request->GetMessageContext(),true,Request->GetSocket())));
		}
		else
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("CAN SOCKET MANAGER FAILED to ADD SOCKET [",Request->GetSocketID(),"] !")));

			FireEvent(CCSPSocketCANManagerMessageResponse(new CSocketCANManagerMessageResponseSocketAdd(Request->GetMessageContext(),false,Request->GetSocket())));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManager::ProcessSocketRemove(CCSPSocketCANManagerMessageRequestSocketRemove Request)
	{
		if (MSocketCollection.Contains(Request->GetSocketID())==true)
		{
			MSocketCollection.Erase(Request->GetSocketID());

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("CAN SOCKET MANAGER SUCCEESSFULLY REMOVED SOCKET [",Request->GetSocketID(),"] !")));

			FireEvent(CCSPSocketCANManagerMessageResponse(new CSocketCANManagerMessageResponseSocketRemove(Request->GetSocketID(),Request->GetMessageContext(),true)));
		}
		else
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("CAN SOCKET MANAGER FAILED to REMOVE SOCKET [",Request->GetSocketID(),"] !")));

			FireEvent(CCSPSocketCANManagerMessageResponse(new CSocketCANManagerMessageResponseSocketRemove(Request->GetSocketID(),Request->GetMessageContext(),false)));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManager::ProcessSocketWrite(CCSPSocketCANManagerMessageRequestSocketWrite Request)
	{
		if (MSocketCollection.Contains(Request->GetSocketID())==true)
		{
			CSocketCANManagerSocketData&						SocketData=MSocketCollection[Request->GetSocketID()];

			if (SocketData.GetSocketState()==CSocketCANManagerSocketData::ESocketCANManagerSocketState::E_OPENED)
			{
				MSocketCollection[Request->GetSocketID()].AddWriteOperation(Request);
			}
			else
			{
				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("CAN SOCKET MANAGER FAILED to WRITE to SOCKET [",Request->GetSocketID(),"] because SOCKET is NOT OPENED !")));

				FireEvent(CCSPSocketCANManagerMessageResponse(new CSocketCANManagerMessageResponseSocketWrite(Request->GetSocketID(),Request->GetMessageContext(),false,Request->GetDestinationAddress(),Request->GetData(),0)));
			}
		}
		else
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("CAN SOCKET MANAGER FAILED to WRITE to SOCKET [",Request->GetSocketID(),"] because SOCKET doesn't EXIST !")));

			FireEvent(CCSPSocketCANManagerMessageResponse(new CSocketCANManagerMessageResponseSocketWrite(Request->GetSocketID(),Request->GetMessageContext(),false,Request->GetDestinationAddress(),Request->GetData(),0)));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManager::ThreadMethod(bool)
	{
		try
		{
			if (HasThreadExitFlagSet()==true)
			{
				return;
			}

			while(true)
			{
				if (HasThreadExitFlagSet()==true)
				{
					return;
				}

				CCSPSocketCANManagerMessageRequest				Request;

				if (MRequestTSCollection.PopFront(Request)==false)
				{
					break;
				}

				if (Request.IsTypeOfAsConst<CSocketCANManagerMessageRequestSocketAdd>()==true)
				{
					ProcessSocketAdd(Request.DynamicCastAsConst<CSocketCANManagerMessageRequestSocketAdd>());
				}
				else if (Request.IsTypeOfAsConst<CSocketCANManagerMessageRequestSocketRemove>()==true)
				{
					ProcessSocketRemove(Request.DynamicCastAsConst<CSocketCANManagerMessageRequestSocketRemove>());
				}
				else if (Request.IsTypeOfAsConst<CSocketCANManagerMessageRequestSocketWrite>()==true)
				{
					ProcessSocketWrite(Request.DynamicCastAsConst<CSocketCANManagerMessageRequestSocketWrite>());
				}

				ProcessOperations();
			}

			ProcessOperations();
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("CAN SOCKET MANAGER DETECTED FATAL ERROR !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("CAN SOCKET MANAGER DETECTED FATAL ERROR !"),CUnknownException()));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CTimeout CSocketCANManager::GetTimeout(void)
	{
		return(CTimeout::GetZero());
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManager::ThreadSafeInitializationEvent(void)
	{
		MExitEvent.Reset();
		MSocketCollection.Clear();
		MWaitObject->ResetEvent();
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManager::ThreadSafeUninitializationEvent(void)
	{
		MExitEvent.Reset();
		MSocketCollection.Clear();
		MRequestTSCollection.Clear();
		MWaitObject->ResetEvent();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManager::AddEvent(const CEventID& EventID, ISocketCANManagerCallback& Callback)
	{
		try
		{
			CLock												Lock(MSocketManagerMutex);
			{
				MCallbackDispatcher.AddEvent(EventID,Callback);
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("CAN SOCKET MANAGER FAILED to ADD EVENT !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("CAN SOCKET MANAGER FAILED to ADD EVENT !"),CUnknownException()));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManager::RemoveEvent(const CEventID& EventID)
	{
		try
		{
			CLock												Lock(MSocketManagerMutex);
			{
				MCallbackDispatcher.RemoveEvent(EventID);
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("CAN SOCKET MANAGER FAILED to REMOVE EVENT !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("CAN SOCKET MANAGER FAILED to REMOVE EVENT !"),CUnknownException()));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketCANManager::HasEvent(const CEventID& EventID) const
	{
		CLock												Lock(MSocketManagerMutex);
		{
			return(MCallbackDispatcher.HasEvent(EventID));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManager::StartThread(void)
	{
		try
		{
			CLock												Lock(MSocketManagerMutex);
			{
				MCallbackDispatcher.StartDispatcher();

				InternalStartThread();

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET CAN MANAGER SUCCESSFULLY STARTED !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET CAN MANAGER FAILED to START !"),E));

			StopThread();
			throw;
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET CAN MANAGER FAILED to START !"),CUnknownException()));

			StopThread();
			throw;
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManager::StopThread(void) noexcept
	{
		try
		{
			CLock												Lock(MSocketManagerMutex);
			{
				SetThreadExitFlag();

				// METHOD is MARKED as 'noexcept'.
				InternalStopThread();

				// METHOD is MARKED as 'noexcept'.
				MCallbackDispatcher.StopDispatcher();

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET CAN MANAGER SUCCESSFULLY STOPPED !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET CAN MANAGER FAILED to STOP !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("SOCKET CAN MANAGER FAILED to STOP !"),CUnknownException()));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManager::SendRequest(CCSPSocketCANManagerMessageRequest MessageRequest)
	{
		CLock													Lock(MSocketManagerMutex);
		{
			if (IsThreadRunning()==true)
			{
				MRequestTSCollection.PushBack(MessageRequest);
				MWaitObject->SetEvent();
			}
			else
			{
				FireEvent(MessageRequest->CreateErrorResponse());
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CSocketCANManager::GetMaximumNumberOfSockets(void)
	{
		CLock													Lock(MSocketManagerMutex);
		{
			return(MWaitObject->GetMaximumNumberOfSocket());
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------