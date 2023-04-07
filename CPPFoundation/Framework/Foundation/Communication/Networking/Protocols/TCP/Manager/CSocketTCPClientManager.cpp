//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPClientManager.h"
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Socket/CSocketTCPReceiveParameters.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Socket/CSocketTCPReceiveResult.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Socket/CSocketTCPSendParameters.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Socket/CSocketTCPSendResult.h>
#include <Framework/Foundation/Exceptions/CSocketException.h>
#include <Framework/Foundation/Exceptions/CUnknownException.h>
#include <Framework/Foundation/Threads/CLock.h>
#include <Framework/Platform/Sockets/CSocketWaitObject.h>
#include "CSocketTCPClientManagerMessageResponseSocketAdd.h"
#include "CSocketTCPClientManagerMessageResponseSocketClosed.h"
#include "CSocketTCPClientManagerMessageResponseSocketClosing.h"
#include "CSocketTCPClientManagerMessageResponseSocketError.h"
#include "CSocketTCPClientManagerMessageResponseSocketConnect.h"
#include "CSocketTCPClientManagerMessageResponseSocketShutdown.h"
#include "CSocketTCPClientManagerMessageResponseSocketRead.h"
#include "CSocketTCPClientManagerMessageResponseSocketRemove.h"
#include "CSocketTCPClientManagerMessageResponseSocketWrite.h"
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
	CSocketTCPClientManager::CSocketTCPClientManager(CLogWriter& LogWriter, Size ReadBufferSize)
		: CThread(LogWriter,CString::Format("SOCKET TCP CLIENT MANAGER THREAD")), MLogCategorySocketManager(CString::Format("SOCKET TCP CLIENT MANAGER")), MSocketManagerMutex(), MExitEvent(false), MCallbackDispatcher(GetLogWriter()), MSocketCollection(), MRequestTSCollection(), MWaitObject(new CSocketWaitObject()), MReadBuffer(new CByteBuffer(ReadBufferSize))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManager::~CSocketTCPClientManager(void)
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
	const CLogCategory& CSocketTCPClientManager::GetLogCategorySocketManager(void) const noexcept
	{
		return(MLogCategorySocketManager);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClientManager::FireEvent(CCSPSocketTCPClientManagerMessageResponse MessageResponse) noexcept
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
	void CSocketTCPClientManager::SetThreadExitFlag(void)
	{
		// First EXIT EVENT MUST be SET.
		MExitEvent.Set();

		// Just after that THREAD MUST be AWAKEN.
		MWaitObject->SetEvent();
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketTCPClientManager::HasThreadExitFlagSet(void)
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
	void CSocketTCPClientManager::ChangeSocketState(CSocketTCPClientManagerSocketData& SocketData, CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState State, CSPSocketTCPClientManagerMessageResponse MessageResponse)
	{
		if (SocketData.GetSocketState()!=State)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER for SOCKET [",SocketData.GetSocket()->GetSocketID(),"] CHANGED STATE STATE [",CSocketTCPClientManagerSocketData::SocketStateToString(SocketData.GetSocketState())," -> ",CSocketTCPClientManagerSocketData::SocketStateToString(State),"] !")));

			SocketData.SetSocketState(State);

			if (MessageResponse!=nullptr)
			{
				FireEvent(MessageResponse);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClientManager::ChangeSocketStateToFailedState(CSocketTCPClientManagerSocketData& SocketData)
	{
		if (SocketData.GetSocketState()!=CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_FAILED)
		{
			ChangeSocketState(SocketData,CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_FAILED,CSPSocketTCPClientManagerMessageResponse(new CSocketTCPClientManagerMessageResponseSocketError(SocketData.GetSocket()->GetSocketID())));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClientManager::RemoveExpiredWriteOperations(void)
	{
		CSteadyClock::Milliseconds								CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();

		for(CSocketCollection::CMapIterator Iterator1=MSocketCollection.Begin();Iterator1!=MSocketCollection.End();Iterator1++)
		{
			if (HasThreadExitFlagSet()==true)
			{
				return;
			}

			CSocketTCPClientManagerSocketData&					SocketData=Iterator1->GetSecond();
			CSocketTCPClientManagerWriteOperationCollection&	WriteOperationCollection=SocketData.GetWriteOperations();

			for(CSocketTCPClientManagerWriteOperationCollection::CListIterator Iterator2=WriteOperationCollection.Begin();Iterator2!=WriteOperationCollection.End();)
			{
				if (Iterator2->GetPacket()->GetWriteExpirationTime().HasExpired(CurrentTimeInMS)==true)
				{
					MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER FAILED to WRITE to SOCKET [",SocketData.GetSocket()->GetSocketID(),"] ! WRITE OPERATION EXPIRED !")));

					FireEvent(CCSPSocketTCPClientManagerMessageResponse(new CSocketTCPClientManagerMessageResponseSocketWrite(SocketData.GetSocket()->GetSocketID(),Iterator2->GetPacket()->GetMessageContext(),false,Iterator2->GetPacket()->GetData(),Iterator2->GetNumberOfBytesWritten())));

					CSocketTCPClientManagerWriteOperationCollection::CListIterator	RemoveIterator=Iterator2++;

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
	bool CSocketTCPClientManager::WriteToSockets(void)
	{
		bool													ExecuteLoop=false;

		for(CSocketCollection::CMapIterator Iterator=MSocketCollection.Begin();Iterator!=MSocketCollection.End();Iterator++)
		{
			if (HasThreadExitFlagSet()==true)
			{
				break;
			}

			CSocketTCPClientManagerSocketData&					SocketData=Iterator->GetSecond();
			CSocketTCPClientManagerWriteOperationCollection&	WriteOperationCollection=SocketData.GetWriteOperations();

			try
			{
				if (SocketData.GetSocketState()==CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_CONNECTED || SocketData.GetSocketState()==CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_HALF_CLOSED_READ)
				{
					if (WriteOperationCollection.GetLength()>0)
					{
						CSocketTCPClientManagerWriteOperation&	WriteOperation=WriteOperationCollection.Front();
						CCSPSocketTCPClientManagerMessageRequestSocketWrite	Packet=WriteOperation.GetPacket();
						Size									Length=WriteOperation.GetNumberOfBytesToWrite();
						CSocketTCPSendParameters				Parameters(Packet->GetData(),WriteOperation.GetNumberOfBytesWritten(),Length);
						CSocketTCPSendResult					Result;
						
						SocketData.GetSocket()->Send(Parameters,Result);
						
						WriteOperation.AddNumberOfBytesWritten(Result.GetNumberOfSentBytes());

						if (WriteOperation.WriteOperationCompleted()==true)
						{
							MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER SUCCESSFULLY WRITTEN DATA to SOCKET [",Packet->GetSocketID(),"] ! DATA [",Packet->GetData(),"] LENGTH [",Packet->GetData()->GetLength(),"] !")));

							WriteOperationCollection.PopFront();

							FireEvent(CCSPSocketTCPClientManagerMessageResponse(new CSocketTCPClientManagerMessageResponseSocketWrite(Packet->GetSocketID(),Packet->GetMessageContext(),true,Packet->GetData(),Packet->GetData()->GetLength())));
						}
						else
						{
							MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER detected PARTIAL WRITE for SOCKET [",Packet->GetSocketID(),"] ! NUMBER of BYTES WRITTEN [",WriteOperation.GetNumberOfBytesWritten(),"] NUMBER of BYTES to WRITE [",WriteOperation.GetNumberOfBytesToWrite(),"] !")));
						}

						if (WriteOperationCollection.GetLength()>0)
						{
							ExecuteLoop=true;
						}
					}
				}
			}
			catch(const CException& E)
			{
				// FATAL ERROR. SOCKET FAILED. CLIENT should REMOVE it from SOCKET MANAGER.

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER FAILED to WRITE DATA to SOCKET [",SocketData.GetSocket()->GetSocketID(),"] !"),E));

				CancelAllWriteOperations(SocketData.GetSocket()->GetSocketID());

				ChangeSocketStateToFailedState(SocketData);
			}
		}

		return(ExecuteLoop);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketTCPClientManager::ReadFromSockets(void)
	{
		bool													ExecuteLoop=false;

		for(CSocketCollection::CMapIterator Iterator=MSocketCollection.Begin();Iterator!=MSocketCollection.End();Iterator++)
		{
			if (HasThreadExitFlagSet()==true)
			{
				break;
			}

			CSocketTCPClientManagerSocketData&					SocketData=Iterator->GetSecond();

			try
			{
				if (SocketData.GetSocketState()==CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_CONNECTED || SocketData.GetSocketState()==CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_HALF_CLOSED_WRITE)
				{
					CSocketTCPReceiveParameters					Parameters(MReadBuffer,0,MReadBuffer->GetLength());
					CSPSocketTCPClient							Socket=SocketData.GetSocket().DynamicCast<CSocketTCPClient>();
					CSocketTCPReceiveResult						Result;
					
					Socket->Receive(Parameters,Result);

					// Check if some BYTES were READ. If OPERATION_SUCCEEDED==FALSE it means that NO DATA were READ and CONNECTION is STILL VALID. If ERROR occured EXCEPTION is THROWN.
					if (Result.GetOperationSucceeded()==true)
					{
						if (Result.GetNumberOfReceivedBytes()>0)
						{
							CSPByteBuffer						Data(new CByteBuffer(MReadBuffer->GetRawData(),Result.GetNumberOfReceivedBytes()));

							MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER SUCCESSFULLY READ DATA from SOCKET [",SocketData.GetSocket()->GetSocketID(),"] ! DATA [",Data,"] LENGTH [",Data->GetLength(),"] !")));

							FireEvent(CCSPSocketTCPClientManagerMessageResponse(new CSocketTCPClientManagerMessageResponseSocketRead(Socket->GetSocketID(),Data)));

							ExecuteLoop=true;
						}
						else
						{
							MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER SUCCESSFULLY DETECTED on SOCKET [",SocketData.GetSocket()->GetSocketID(),"] END of DATA STREAM !")));

							if (SocketData.GetSocketState()!=CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_HALF_CLOSED_WRITE)
							{
								ChangeSocketState(SocketData,CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_HALF_CLOSED_READ,CSPSocketTCPClientManagerMessageResponse(new CSocketTCPClientManagerMessageResponseSocketClosing(SocketData.GetSocket()->GetSocketID(),CSocketTCPClientManagerMessageResponseSocketClosing::EClosingEnd::E_READ)));
							}
							else
							{
								ChangeSocketState(SocketData,CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_CLOSED,CSPSocketTCPClientManagerMessageResponse(new CSocketTCPClientManagerMessageResponseSocketClosed(SocketData.GetSocket()->GetSocketID())));
							}
						}
					}
				}
			}
			catch(const CException& E)
			{
				// FATAL ERROR. SOCKET FAILED. CLIENT should REMOVE it from SOCKET MANAGER.

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER FAILED to READ DATA from SOCKET [",SocketData.GetSocket()->GetSocketID(),"] !"),E));

				ChangeSocketStateToFailedState(SocketData);
			}
		}

		return(ExecuteLoop);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClientManager::WaitForSocketEvents(bool PeekWait)
	{
		try
		{
			CSteadyClock::Milliseconds							CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();
			CTimeout											Timeout=(MRequestTSCollection.GetLength()>0 || PeekWait==true) ? CTimeout::GetZero() : CTimeout::GetInfinite();
			CVector<CSocketWaitState>							SocketStates;

			SocketStates.ReserveCapacity(MSocketCollection.GetLength());

			for(const CSocketCollection::CKeyValuePair& Pair : MSocketCollection)
			{
				const CSocketTCPClientManagerSocketData&		SocketData=Pair.GetSecond();

				if (SocketData.GetSocketState()==CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_WAITING_FOR_CONNECTION)
				{
					ESocketWaitFlags							WaitFlags=ESocketWaitFlags::E_READ | ESocketWaitFlags::E_WRITE | ESocketWaitFlags::E_CLOSE;

					SocketStates.Add(CSocketWaitState(SocketData.GetSocket(),WaitFlags));
				}
				else if (SocketData.GetSocketState()==CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_CONNECTED || SocketData.GetSocketState()==CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_HALF_CLOSED_WRITE)
				{
					ESocketWaitFlags							WaitFlags=ESocketWaitFlags::E_READ | ESocketWaitFlags::E_CLOSE;

					if (SocketData.GetWriteOperations().GetLength()>0)
					{
						WaitFlags|=ESocketWaitFlags::E_WRITE;
					}

					SocketStates.Add(CSocketWaitState(SocketData.GetSocket(),WaitFlags));
				}
				else if (SocketData.GetSocketState()==CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_HALF_CLOSED_READ)
				{
					ESocketWaitFlags							WaitFlags=ESocketWaitFlags::E_NONE;

					if (SocketData.GetWriteOperations().GetLength()>0)
					{
						WaitFlags|=ESocketWaitFlags::E_WRITE;
					}

					SocketStates.Add(CSocketWaitState(SocketData.GetSocket(),WaitFlags));
				}

				if (Timeout.IsZero()==false)
				{
					for(const CSocketTCPClientManagerWriteOperation& WriteOperation : SocketData.GetWriteOperations())
					{
						CTimeout								WriteOperationTimeout=WriteOperation.GetPacket()->GetWriteExpirationTime().CalculateTimeout(CurrentTimeInMS);

						Timeout=CTimeout::Min(Timeout,WriteOperationTimeout);
					}
				}
			}

			ESocketWaitEvent									WaitResult=MWaitObject->WaitForEvent(SocketStates,Timeout);

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER WAITING FINISHED with RESULT [",WaitResult,"] !")));

			for(const CSocketWaitState& SocketState : SocketStates)
			{
				CSocketTCPClientManagerSocketData&				SocketData=MSocketCollection[SocketState.GetSocket()->GetSocketID()];
				ESocketWaitResultFlags							ResultFlags=SocketState.GetWaitResultFlags();
				
				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER for SOCKET [",SocketData.GetSocket()->GetSocketID(),"] received EVENTS [",ResultFlags,"] !")));

				// NO ERROR.
				if ((ResultFlags & ESocketWaitResultFlags::E_ERROR)==ESocketWaitResultFlags::E_NONE)
				{
					if ((ResultFlags & ESocketWaitResultFlags::E_WRITE)!=ESocketWaitResultFlags::E_NONE)
					{
						if (SocketData.GetSocketState()==CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_WAITING_FOR_CONNECTION)
						{
							MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER DETECTED that SOCKET [",SocketState.GetSocket()->GetSocketID(),"] was CONNECTED !")));

							ChangeSocketState(SocketData,CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_CONNECTED,CSPSocketTCPClientManagerMessageResponse(new CSocketTCPClientManagerMessageResponseSocketConnect(SocketData.GetConnectOperation()->GetMessageContext(),true,SocketData.GetSocket(),SocketData.GetConnectOperation()->GetDestinationAddress())));
						}
					}

					// CLOSE EVENTS are just LOGGED because IT'S not POSSIBLE to determine which SIDE of CONNECTION was CLOSED. This can be only determined after the detection of END of STREAM (READ SIDE CLOSED) or WRITE ERROR (WRITE SIDE CLOSED).
					if ((ResultFlags & ESocketWaitResultFlags::E_CLOSE)!=ESocketWaitResultFlags::E_NONE)
					{
						MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER DETECTED that SOCKET [",SocketState.GetSocket()->GetSocketID(),"] was CLOSED !")));
					}
				}
				// ERROR.
				else
				{
					if ((ResultFlags & ESocketWaitResultFlags::E_CLOSE)!=ESocketWaitResultFlags::E_NONE)
					{
						MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER DETECTED that SOCKET [",SocketState.GetSocket()->GetSocketID(),"] was CLOSED !")));
					}

					MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER DETECTED that SOCKET [",SocketState.GetSocket()->GetSocketID(),"] FAILED !")));

					if (SocketData.GetSocketState()==CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_WAITING_FOR_CONNECTION)
					{
						FireEvent(CCSPSocketTCPClientManagerMessageResponse(new CSocketTCPClientManagerMessageResponseSocketConnect(SocketData.GetConnectOperation()->GetMessageContext(),false,SocketData.GetSocket(),SocketData.GetConnectOperation()->GetDestinationAddress())));
					}

					CancelAllWriteOperations(SocketState.GetSocket()->GetSocketID());

					ChangeSocketStateToFailedState(SocketData);
				}
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER FAILED FATALLY ! ALL SOCKETS are DISABLED !"),E));

			for(CSocketCollection::CKeyValuePair& Pair : MSocketCollection)
			{
				CSocketTCPClientManagerSocketData&				SocketData=Pair.GetSecond();

				if (SocketData.GetSocketState()==CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_WAITING_FOR_CONNECTION)
				{
					FireEvent(CCSPSocketTCPClientManagerMessageResponse(new CSocketTCPClientManagerMessageResponseSocketConnect(SocketData.GetConnectOperation()->GetMessageContext(),false,SocketData.GetSocket(),SocketData.GetConnectOperation()->GetDestinationAddress())));
				}

				CancelAllWriteOperations(SocketData.GetSocket()->GetSocketID());

				ChangeSocketStateToFailedState(SocketData);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClientManager::CancelAllWriteOperations(const CSocketID& SocketID)
	{
		CSocketTCPClientManagerSocketData&						SocketData=MSocketCollection[SocketID];

		for(const CSocketTCPClientManagerWriteOperation& WriteOperation : SocketData.GetWriteOperations())
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER FAILED to WRITE DATA to SOCKET [",SocketData.GetSocket()->GetSocketID(),"] ! OPERATION was CANCELLED !")));

			FireEvent(CCSPSocketTCPClientManagerMessageResponse(new CSocketTCPClientManagerMessageResponseSocketWrite(SocketData.GetSocket()->GetSocketID(),WriteOperation.GetPacket()->GetMessageContext(),false,WriteOperation.GetPacket()->GetData(),WriteOperation.GetNumberOfBytesWritten())));
		}

		SocketData.ClearWriteOperations();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClientManager::ProcessOperations(void)
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

		bool													WriteExecuteLoop=WriteToSockets();

		if (HasThreadExitFlagSet()==true)
		{
			return;
		}

		bool													ReadExecuteLoop=ReadFromSockets();

		if (HasThreadExitFlagSet()==true)
		{
			return;
		}

		bool													PeekWait=(WriteExecuteLoop==true || ReadExecuteLoop==true) ? true : false;

		WaitForSocketEvents(PeekWait);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClientManager::ProcessSocketAdd(CCSPSocketTCPClientManagerMessageRequestSocketAdd Request)
	{
		if (MSocketCollection.Contains(Request->GetSocketID())==false && MSocketCollection.GetLength()<MWaitObject->GetMaximumNumberOfSocket())
		{
			MSocketCollection.Add(Request->GetSocketID(),CSocketTCPClientManagerSocketData(Request->GetSocket(),CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_CONNECTED,nullptr));

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER SUCCEESSFULLY ADDED SOCKET [",Request->GetSocketID(),"] !")));

			FireEvent(CCSPSocketTCPClientManagerMessageResponse(new CSocketTCPClientManagerMessageResponseSocketAdd(Request->GetMessageContext(),true,Request->GetSocket())));
		}
		else
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER FAILED to ADD SOCKET [",Request->GetSocketID(),"] because SOCKET already EXISTS !")));

			FireEvent(CCSPSocketTCPClientManagerMessageResponse(new CSocketTCPClientManagerMessageResponseSocketAdd(Request->GetMessageContext(),false,Request->GetSocket())));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClientManager::ProcessSocketRemove(CCSPSocketTCPClientManagerMessageRequestSocketRemove Request)
	{
		if (MSocketCollection.Contains(Request->GetSocketID())==true)
		{
			MSocketCollection.Erase(Request->GetSocketID());

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER SUCCEESSFULLY REMOVED SOCKET [",Request->GetSocketID(),"] !")));

			FireEvent(CCSPSocketTCPClientManagerMessageResponse(new CSocketTCPClientManagerMessageResponseSocketRemove(Request->GetSocketID(),Request->GetMessageContext(),true)));
		}
		else
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER FAILED to REMOVE SOCKET [",Request->GetSocketID(),"] because SOCKET doesn't EXIST !")));

			FireEvent(CCSPSocketTCPClientManagerMessageResponse(new CSocketTCPClientManagerMessageResponseSocketRemove(Request->GetSocketID(),Request->GetMessageContext(),false)));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClientManager::ProcessSocketConnect(CCSPSocketTCPClientManagerMessageRequestSocketConnect Request)
	{
		if (MSocketCollection.Contains(Request->GetSocketID())==false)
		{
			try
			{
				// CONNECTION SUCCEEDED.
				if (Request->GetSocket()->ConnectToAddress(Request->GetDestinationAddress())==true)
				{
					MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER CONNECTED SOCKET [",Request->GetSocketID(),"] to ADDRESS [",Request->GetDestinationAddress(),"] !")));

					FireEvent(CCSPSocketTCPClientManagerMessageResponse(new CSocketTCPClientManagerMessageResponseSocketConnect(Request->GetMessageContext(),true,Request->GetSocket(),Request->GetDestinationAddress())));

					MSocketCollection.Add(Request->GetSocketID(),CSocketTCPClientManagerSocketData(Request->GetSocket(),CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_CONNECTED,nullptr));
				}
				// CONNECTION in PROGRESS.
				else
				{
					MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER is CONNECTING SOCKET [",Request->GetSocketID(),"] to ADDRESS [",Request->GetDestinationAddress(),"] !")));

					MSocketCollection.Add(Request->GetSocketID(),CSocketTCPClientManagerSocketData(Request->GetSocket(),CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_WAITING_FOR_CONNECTION,Request));
				}
			}
			catch(const CException& E)
			{
				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER FAILED to CONNECT SOCKET [",Request->GetSocketID(),"] to ADDRESS [",Request->GetDestinationAddress(),"] !"),E));

				FireEvent(CCSPSocketTCPClientManagerMessageResponse(new CSocketTCPClientManagerMessageResponseSocketConnect(Request->GetMessageContext(),false,Request->GetSocket(),Request->GetDestinationAddress())));
			}
		}
		else
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER FAILED to CONNECT SOCKET [",Request->GetSocketID(),"] to ADDRESS [",Request->GetDestinationAddress(),"] because SOCKET already EXISTS !")));

			FireEvent(CCSPSocketTCPClientManagerMessageResponse(new CSocketTCPClientManagerMessageResponseSocketConnect(Request->GetMessageContext(),false,Request->GetSocket(),Request->GetDestinationAddress())));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClientManager::ProcessSocketShutdown(CCSPSocketTCPClientManagerMessageRequestSocketShutdown Request)
	{
		if (MSocketCollection.Contains(Request->GetSocketID())==true)
		{
			CSocketTCPClientManagerSocketData&					SocketData=MSocketCollection[Request->GetSocketID()];

			try
			{
				if (SocketData.GetSocketState()==CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_WAITING_FOR_CONNECTION || SocketData.GetSocketState()==CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_CONNECTED || SocketData.GetSocketState()==CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_HALF_CLOSED_READ)
				{
					SocketData.GetSocket()->Shutdown(ESocketTCPShutdownFlags::E_WRITE);

					FireEvent(CCSPSocketTCPClientManagerMessageResponse(new CSocketTCPClientManagerMessageResponseSocketShutdown(Request->GetSocketID(),Request->GetMessageContext(),true)));

					if (SocketData.GetSocketState()==CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_WAITING_FOR_CONNECTION)
					{
						FireEvent(CCSPSocketTCPClientManagerMessageResponse(new CSocketTCPClientManagerMessageResponseSocketConnect(SocketData.GetConnectOperation()->GetMessageContext(),false,SocketData.GetSocket(),SocketData.GetConnectOperation()->GetDestinationAddress())));
					}

					if (SocketData.GetSocketState()!=CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_HALF_CLOSED_READ)
					{
						ChangeSocketState(SocketData,CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_HALF_CLOSED_WRITE,CSPSocketTCPClientManagerMessageResponse(new CSocketTCPClientManagerMessageResponseSocketClosing(Request->GetSocketID(),CSocketTCPClientManagerMessageResponseSocketClosing::EClosingEnd::E_WRITE)));
					}
					else
					{
						ChangeSocketState(SocketData,CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_CLOSED,CSPSocketTCPClientManagerMessageResponse(new CSocketTCPClientManagerMessageResponseSocketClosed(Request->GetSocketID())));
					}
				}
				else
				{
					MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER FAILED to SHUTDOWN SOCKET [",Request->GetSocketID(),"] because SOCKET is NOT CONNECTED !")));

					FireEvent(CCSPSocketTCPClientManagerMessageResponse(new CSocketTCPClientManagerMessageResponseSocketShutdown(Request->GetSocketID(),Request->GetMessageContext(),false)));
				}
			}
			catch(const CException& E)
			{
				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER FAILED to SHUTDOWN SOCKET [",Request->GetSocketID(),"] !"),E));

				FireEvent(CCSPSocketTCPClientManagerMessageResponse(new CSocketTCPClientManagerMessageResponseSocketShutdown(Request->GetSocketID(),Request->GetMessageContext(),false)));

				if (SocketData.GetSocketState()==CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_WAITING_FOR_CONNECTION)
				{
					FireEvent(CCSPSocketTCPClientManagerMessageResponse(new CSocketTCPClientManagerMessageResponseSocketConnect(SocketData.GetConnectOperation()->GetMessageContext(),false,SocketData.GetSocket(),SocketData.GetConnectOperation()->GetDestinationAddress())));
				}

				ChangeSocketStateToFailedState(SocketData);
			}
		}
		else
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER FAILED to SHUTDOWN SOCKET [",Request->GetSocketID(),"] because SOCKET doesn't EXIST !")));

			FireEvent(CCSPSocketTCPClientManagerMessageResponse(new CSocketTCPClientManagerMessageResponseSocketShutdown(Request->GetSocketID(),Request->GetMessageContext(),false)));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClientManager::ProcessSocketWrite(CCSPSocketTCPClientManagerMessageRequestSocketWrite Request)
	{
		if (MSocketCollection.Contains(Request->GetSocketID())==true)
		{
			CSocketTCPClientManagerSocketData&					SocketData=MSocketCollection[Request->GetSocketID()];

			if (SocketData.GetSocketState()==CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_CONNECTED || SocketData.GetSocketState()==CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState::E_HALF_CLOSED_READ)
			{
				MSocketCollection[Request->GetSocketID()].AddWriteOperation(Request);
			}
			else
			{
				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER FAILED to WRITE to SOCKET [",Request->GetSocketID(),"] because SOCKET is NOT CONNECTED !")));

				FireEvent(CCSPSocketTCPClientManagerMessageResponse(new CSocketTCPClientManagerMessageResponseSocketWrite(Request->GetSocketID(),Request->GetMessageContext(),false,Request->GetData(),0)));
			}
		}
		else
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER FAILED to WRITE to SOCKET [",Request->GetSocketID(),"] because SOCKET doesn't EXIST !")));

			FireEvent(CCSPSocketTCPClientManagerMessageResponse(new CSocketTCPClientManagerMessageResponseSocketWrite(Request->GetSocketID(),Request->GetMessageContext(),false,Request->GetData(),0)));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClientManager::ThreadMethod(bool)
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

				CCSPSocketTCPClientManagerMessageRequest		Request;

				if (MRequestTSCollection.PopFront(Request)==false)
				{
					break;
				}

				if (Request.IsTypeOfAsConst<CSocketTCPClientManagerMessageRequestSocketAdd>()==true)
				{
					ProcessSocketAdd(Request.DynamicCastAsConst<CSocketTCPClientManagerMessageRequestSocketAdd>());
				}
				else if (Request.IsTypeOfAsConst<CSocketTCPClientManagerMessageRequestSocketRemove>()==true)
				{
					ProcessSocketRemove(Request.DynamicCastAsConst<CSocketTCPClientManagerMessageRequestSocketRemove>());
				}
				else if (Request.IsTypeOfAsConst<CSocketTCPClientManagerMessageRequestSocketConnect>()==true)
				{
					ProcessSocketConnect(Request.DynamicCastAsConst<CSocketTCPClientManagerMessageRequestSocketConnect>());
				}
				else if (Request.IsTypeOfAsConst<CSocketTCPClientManagerMessageRequestSocketShutdown>()==true)
				{
					ProcessSocketShutdown(Request.DynamicCastAsConst<CSocketTCPClientManagerMessageRequestSocketShutdown>());
				}
				else if (Request.IsTypeOfAsConst<CSocketTCPClientManagerMessageRequestSocketWrite>()==true)
				{
					ProcessSocketWrite(Request.DynamicCastAsConst<CSocketTCPClientManagerMessageRequestSocketWrite>());
				}

				ProcessOperations();
			}

			ProcessOperations();
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER DETECTED FATAL ERROR !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER DETECTED FATAL ERROR !"),CUnknownException()));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CTimeout CSocketTCPClientManager::GetTimeout(void)
	{
		return(CTimeout::GetZero());
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClientManager::ThreadSafeInitializationEvent(void)
	{
		MExitEvent.Reset();
		MSocketCollection.Clear();
		MWaitObject->ResetEvent();
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClientManager::ThreadSafeUninitializationEvent(void)
	{
		MExitEvent.Reset();
		MSocketCollection.Clear();
		MRequestTSCollection.Clear();
		MWaitObject->ResetEvent();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClientManager::AddEvent(const CEventID& EventID, ISocketTCPClientManagerCallback& Callback)
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
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER FAILED to ADD EVENT !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER FAILED to ADD EVENT !"),CUnknownException()));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClientManager::RemoveEvent(const CEventID& EventID)
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
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER FAILED to REMOVE EVENT !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER FAILED to REMOVE EVENT !"),CUnknownException()));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketTCPClientManager::HasEvent(const CEventID& EventID) const
	{
		CLock												Lock(MSocketManagerMutex);
		{
			return(MCallbackDispatcher.HasEvent(EventID));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClientManager::StartThread(void)
	{
		try
		{
			CLock												Lock(MSocketManagerMutex);
			{
				MCallbackDispatcher.StartDispatcher();

				InternalStartThread();

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER SUCCESSFULLY STARTED !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER FAILED to START !"),E));

			StopThread();
			throw;
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER FAILED to START !"),CUnknownException()));

			StopThread();
			throw;
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClientManager::StopThread(void) noexcept
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

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER SUCCESSFULLY STOPPED !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER FAILED to STOP !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER FAILED to STOP !"),CUnknownException()));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClientManager::SendRequest(CCSPSocketTCPClientManagerMessageRequest MessageRequest)
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
	Size CSocketTCPClientManager::GetMaximumNumberOfSockets(void)
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