//----------------------------------------------------------------------------------------------------------------------
#include "CSocketUDPManager.h"
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Socket/CSocketUDPReceiveFromParameters.h>
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Socket/CSocketUDPReceiveFromResult.h>
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Socket/CSocketUDPSendToParameters.h>
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Socket/CSocketUDPSendToResult.h>
#include <Framework/Foundation/Exceptions/CUnknownException.h>
#include <Framework/Foundation/Threads/CLock.h>
#include <Framework/Platform/Sockets/CSocketWaitObject.h>
#include "CSocketUDPManagerMessageResponseSocketAdd.h"
#include "CSocketUDPManagerMessageResponseSocketClose.h"
#include "CSocketUDPManagerMessageResponseSocketError.h"
#include "CSocketUDPManagerMessageResponseSocketRead.h"
#include "CSocketUDPManagerMessageResponseSocketRemove.h"
#include "CSocketUDPManagerMessageResponseSocketWrite.h"
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
	CSocketUDPManager::CSocketUDPManager(CLogWriter& LogWriter, Size ReadBufferSize)
		: CThread(LogWriter,CString::Format("SOCKET UDP MANAGER THREAD")), MLogCategorySocketManager(CString::Format("SOCKET UDP MANAGER")), MSocketManagerMutex(), MExitEvent(false), MCallbackDispatcher(GetLogWriter()), MSocketCollection(), MRequestTSCollection(), MWaitObject(new CSocketWaitObject()), MReadBuffer(new CByteBuffer(ReadBufferSize))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManager::~CSocketUDPManager(void)
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
	bool CSocketUDPManager::IsFatalReadError(ESocketExceptionCode Value)
	{
		switch(Value)
		{
			case ESocketExceptionCode::E_UNKNOWN:
			case ESocketExceptionCode::E_NETWORK_DOWN:
			case ESocketExceptionCode::E_NETWORK_IS_UNREACHABLE:
			{
				return(true);
			}

			case ESocketExceptionCode::E_NETWORK_RESET:
			case ESocketExceptionCode::E_CONNECTION_ABORTED:
			case ESocketExceptionCode::E_CONNECTION_RESET:
			case ESocketExceptionCode::E_NO_BUFFER_SPACE_AVAILABLE:
			case ESocketExceptionCode::E_SOCKET_IS_ALREADY_CONNECTED:
			case ESocketExceptionCode::E_SOCKET_IS_NOT_CONNECTED:
			case ESocketExceptionCode::E_SOCKET_IS_SHUTDOWN:
			case ESocketExceptionCode::E_TOO_MANY_REFERENCES:
			case ESocketExceptionCode::E_CONNECTION_TIMEOUT:
			case ESocketExceptionCode::E_CONNECTION_REFUSED:
			case ESocketExceptionCode::E_HOST_IS_DOWN:
			case ESocketExceptionCode::E_HOST_IS_UNREACHABLE:
			case ESocketExceptionCode::E_SOCKET_OPERATION_ON_NON_SOCKET:
			case ESocketExceptionCode::E_DESTINATION_ADDRESS_IS_REQUIRED:
			case ESocketExceptionCode::E_MESSAGE_TOO_LONG:
			case ESocketExceptionCode::E_WRONG_PROTOCOL_TYPE_FOR_SOCKET:
			case ESocketExceptionCode::E_WRONG_PROTOCOL_OPTION:
			case ESocketExceptionCode::E_PROTOCOL_NOT_SUPPORTED:
			case ESocketExceptionCode::E_SOCKET_TYPE_NOT_SUPPORTED:
			case ESocketExceptionCode::E_OPERATION_NOT_SUPPORTED_ON_TRANSPORT_ENDPOINT:
			case ESocketExceptionCode::E_PROTOCOL_FAMILY_NOT_SUPPORTED:
			case ESocketExceptionCode::E_ADDRESS_FAMILY_NOT_SUPPORTED_BY_PROTOCOL:
			case ESocketExceptionCode::E_ADDRESS_ALREADY_IN_USE:
			case ESocketExceptionCode::E_CAN_NOT_ASSIGN_REQUESTED_ADDRESS:
			{
				return(false);
			}

			default:
			{
				return(false);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketUDPManager::IsFatalWriteError(ESocketExceptionCode Value)
	{
		switch(Value)
		{
			case ESocketExceptionCode::E_UNKNOWN:
			case ESocketExceptionCode::E_NETWORK_DOWN:
			{
				return(true);
			}

			case ESocketExceptionCode::E_NETWORK_IS_UNREACHABLE:
			case ESocketExceptionCode::E_NETWORK_RESET:
			case ESocketExceptionCode::E_CONNECTION_ABORTED:
			case ESocketExceptionCode::E_CONNECTION_RESET:
			case ESocketExceptionCode::E_NO_BUFFER_SPACE_AVAILABLE:
			case ESocketExceptionCode::E_SOCKET_IS_ALREADY_CONNECTED:
			case ESocketExceptionCode::E_SOCKET_IS_NOT_CONNECTED:
			case ESocketExceptionCode::E_SOCKET_IS_SHUTDOWN:
			case ESocketExceptionCode::E_TOO_MANY_REFERENCES:
			case ESocketExceptionCode::E_CONNECTION_TIMEOUT:
			case ESocketExceptionCode::E_CONNECTION_REFUSED:
			case ESocketExceptionCode::E_HOST_IS_DOWN:
			case ESocketExceptionCode::E_HOST_IS_UNREACHABLE:
			case ESocketExceptionCode::E_SOCKET_OPERATION_ON_NON_SOCKET:
			case ESocketExceptionCode::E_DESTINATION_ADDRESS_IS_REQUIRED:
			case ESocketExceptionCode::E_MESSAGE_TOO_LONG:
			case ESocketExceptionCode::E_WRONG_PROTOCOL_TYPE_FOR_SOCKET:
			case ESocketExceptionCode::E_WRONG_PROTOCOL_OPTION:
			case ESocketExceptionCode::E_PROTOCOL_NOT_SUPPORTED:
			case ESocketExceptionCode::E_SOCKET_TYPE_NOT_SUPPORTED:
			case ESocketExceptionCode::E_OPERATION_NOT_SUPPORTED_ON_TRANSPORT_ENDPOINT:
			case ESocketExceptionCode::E_PROTOCOL_FAMILY_NOT_SUPPORTED:
			case ESocketExceptionCode::E_ADDRESS_FAMILY_NOT_SUPPORTED_BY_PROTOCOL:
			case ESocketExceptionCode::E_ADDRESS_ALREADY_IN_USE:
			case ESocketExceptionCode::E_CAN_NOT_ASSIGN_REQUESTED_ADDRESS:
			{
				return(false);
			}

			default:
			{
				return(false);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketUDPManager::IsFatalWaitError(ESocketExceptionCode Value)
	{
		switch(Value)
		{
			case ESocketExceptionCode::E_UNKNOWN:
			case ESocketExceptionCode::E_NETWORK_DOWN:
			case ESocketExceptionCode::E_NETWORK_IS_UNREACHABLE:
			{
				return(true);
			}

			case ESocketExceptionCode::E_NETWORK_RESET:
			case ESocketExceptionCode::E_CONNECTION_ABORTED:
			case ESocketExceptionCode::E_CONNECTION_RESET:
			case ESocketExceptionCode::E_NO_BUFFER_SPACE_AVAILABLE:
			case ESocketExceptionCode::E_SOCKET_IS_ALREADY_CONNECTED:
			case ESocketExceptionCode::E_SOCKET_IS_NOT_CONNECTED:
			case ESocketExceptionCode::E_SOCKET_IS_SHUTDOWN:
			case ESocketExceptionCode::E_TOO_MANY_REFERENCES:
			case ESocketExceptionCode::E_CONNECTION_TIMEOUT:
			case ESocketExceptionCode::E_CONNECTION_REFUSED:
			case ESocketExceptionCode::E_HOST_IS_DOWN:
			case ESocketExceptionCode::E_HOST_IS_UNREACHABLE:
			case ESocketExceptionCode::E_SOCKET_OPERATION_ON_NON_SOCKET:
			case ESocketExceptionCode::E_DESTINATION_ADDRESS_IS_REQUIRED:
			case ESocketExceptionCode::E_MESSAGE_TOO_LONG:
			case ESocketExceptionCode::E_WRONG_PROTOCOL_TYPE_FOR_SOCKET:
			case ESocketExceptionCode::E_WRONG_PROTOCOL_OPTION:
			case ESocketExceptionCode::E_PROTOCOL_NOT_SUPPORTED:
			case ESocketExceptionCode::E_SOCKET_TYPE_NOT_SUPPORTED:
			case ESocketExceptionCode::E_OPERATION_NOT_SUPPORTED_ON_TRANSPORT_ENDPOINT:
			case ESocketExceptionCode::E_PROTOCOL_FAMILY_NOT_SUPPORTED:
			case ESocketExceptionCode::E_ADDRESS_FAMILY_NOT_SUPPORTED_BY_PROTOCOL:
			case ESocketExceptionCode::E_ADDRESS_ALREADY_IN_USE:
			case ESocketExceptionCode::E_CAN_NOT_ASSIGN_REQUESTED_ADDRESS:
			{
				return(false);
			}

			default:
			{
				return(false);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CLogCategory& CSocketUDPManager::GetLogCategorySocketManager(void) const noexcept
	{
		return(MLogCategorySocketManager);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManager::FireEvent(CCSPSocketUDPManagerMessageResponse MessageResponse) noexcept
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
	void CSocketUDPManager::SetThreadExitFlag(void)
	{
		// First EXIT EVENT MUST be SET.
		MExitEvent.Set();

		// Just after that THREAD MUST be AWAKEN.
		MWaitObject->SetEvent();
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketUDPManager::HasThreadExitFlagSet(void)
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
	void CSocketUDPManager::ChangeSocketState(CSocketUDPManagerSocketData& SocketData, CSocketUDPManagerSocketData::ESocketUDPManagerSocketState State, CSPSocketUDPManagerMessageResponse MessageResponse)
	{
		if (SocketData.GetSocketState()!=State)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("UDP SOCKET MANAGER for SOCKET [",SocketData.GetSocket()->GetSocketID(),"] CHANGED STATE STATE [",CSocketUDPManagerSocketData::SocketStateToString(SocketData.GetSocketState())," -> ",CSocketUDPManagerSocketData::SocketStateToString(State),"] !")));

			SocketData.SetSocketState(State);

			if (MessageResponse!=nullptr)
			{
				FireEvent(MessageResponse);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManager::ChangeSocketStateToFailedState(CSocketUDPManagerSocketData& SocketData)
	{
		if (SocketData.GetSocketState()!=CSocketUDPManagerSocketData::ESocketUDPManagerSocketState::E_FAILED)
		{
			ChangeSocketState(SocketData,CSocketUDPManagerSocketData::ESocketUDPManagerSocketState::E_FAILED,CSPSocketUDPManagerMessageResponse(new CSocketUDPManagerMessageResponseSocketError(SocketData.GetSocket()->GetSocketID())));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManager::RemoveExpiredWriteOperations(void)
	{
		CSteadyClock::Milliseconds								CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();

		for(CSocketCollection::CMapIterator Iterator1=MSocketCollection.Begin();Iterator1!=MSocketCollection.End();Iterator1++)
		{
			if (HasThreadExitFlagSet()==true)
			{
				return;
			}

			CSocketUDPManagerSocketData&						SocketData=Iterator1->GetSecond();
			CSocketUDPManagerWriteOperationCollection&			WriteOperationCollection=SocketData.GetWriteOperations();

			for(CSocketUDPManagerWriteOperationCollection::CListIterator Iterator2=WriteOperationCollection.Begin();Iterator2!=WriteOperationCollection.End();)
			{
				if (Iterator2->GetPacket()->GetWriteExpirationTime().HasExpired(CurrentTimeInMS)==true)
				{
					MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("UDP SOCKET MANAGER FAILED to WRITE to SOCKET [",SocketData.GetSocket()->GetSocketID(),"] ! WRITE OPERATION EXPIRED !")));

					FireEvent(CCSPSocketUDPManagerMessageResponse(new CSocketUDPManagerMessageResponseSocketWrite(SocketData.GetSocket()->GetSocketID(),Iterator2->GetPacket()->GetMessageContext(),false,Iterator2->GetPacket()->GetDestinationAddress(),Iterator2->GetPacket()->GetData(),Iterator2->GetNumberOfBytesWritten())));

					CSocketUDPManagerWriteOperationCollection::CListIterator	RemoveIterator=Iterator2++;

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
	void CSocketUDPManager::WriteToSockets(void)
	{
		for(CSocketCollection::CMapIterator Iterator=MSocketCollection.Begin();Iterator!=MSocketCollection.End();Iterator++)
		{
			if (HasThreadExitFlagSet()==true)
			{
				return;
			}

			CSocketUDPManagerSocketData&						SocketData=Iterator->GetSecond();
			
			try
			{
				CSocketUDPManagerWriteOperationCollection&		WriteOperationCollection=SocketData.GetWriteOperations();

				if (SocketData.GetSocketState()==CSocketUDPManagerSocketData::ESocketUDPManagerSocketState::E_OPENED)
				{
					if (WriteOperationCollection.GetLength()>0)
					{
						CSocketUDPManagerWriteOperation&		WriteOperation=WriteOperationCollection.Front();
						CCSPSocketUDPManagerMessageRequestSocketWrite	Packet=WriteOperation.GetPacket();
						CSocketUDPAddress						Address(Packet->GetDestinationAddress());
						Size									Length=WriteOperation.GetNumberOfBytesToWrite();
						CSocketUDPSendToParameters				Parameters(Address,Packet->GetData(),WriteOperation.GetNumberOfBytesWritten(),Length);
						CSocketUDPSendToResult					Result;
						
						SocketData.GetSocket()->SendTo(Parameters,Result);
						
						WriteOperation.AddNumberOfBytesWritten(Result.GetNumberOfSentBytes());

						if (WriteOperation.GetNumberOfBytesToWrite()<=0)
						{
							MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("UDP SOCKET MANAGER SUCCESSFULLY WRITTEN DATA to SOCKET [",Packet->GetSocketID(),"] ! ADDRESS [",Packet->GetDestinationAddress(),"] DATA [",Packet->GetData(),"] LENGTH [",Packet->GetData()->GetLength(),"] !")));
							
							FireEvent(CCSPSocketUDPManagerMessageResponse(new CSocketUDPManagerMessageResponseSocketWrite(Packet->GetSocketID(),Packet->GetMessageContext(),true,Packet->GetDestinationAddress(),Packet->GetData(),Packet->GetData()->GetLength())));

							WriteOperationCollection.PopFront();
						}
						else
						{
							MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP CLIENT SOCKET MANAGER detected PARTIAL WRITE for SOCKET [",Packet->GetSocketID(),"] ! NUMBER of BYTES WRITTEN [",WriteOperation.GetNumberOfBytesWritten(),"] NUMBER of BYTES to WRITE [",WriteOperation.GetNumberOfBytesToWrite(),"] !")));
						}
					}
				}
			}
			catch(const CSocketException& E)
			{
				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("UDP SOCKET MANAGER FAILED to WRITE DATA to SOCKET [",SocketData.GetSocket()->GetSocketID(),"] !"),E));

				CancelAllWriteOperations(SocketData.GetSocket()->GetSocketID());

				// If FATAL SOCKET ERROR has OCCURED while WRITING from UDP SOCKET, UDP SOCKET will FAIL.
				if (IsFatalWriteError(E.GetSocketExceptionCode())==true)
				{
					ChangeSocketStateToFailedState(SocketData);
				}
			}
			catch(const CException& E)
			{
				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("UDP SOCKET MANAGER FAILED to WRITE DATA to SOCKET [",SocketData.GetSocket()->GetSocketID(),"] !"),E));

				CancelAllWriteOperations(SocketData.GetSocket()->GetSocketID());

				// If ANY NON-SOCKET ERROR has OCCURED while WRITING from UDP SOCKET, UDP SOCKET will FAIL.
				ChangeSocketStateToFailedState(SocketData);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManager::ReadFromSockets(void)
	{
		for(CSocketCollection::CMapIterator Iterator=MSocketCollection.Begin();Iterator!=MSocketCollection.End();Iterator++)
		{
			if (HasThreadExitFlagSet()==true)
			{
				return;
			}

			CSocketUDPManagerSocketData&						SocketData=Iterator->GetSecond();

			try
			{
				if (SocketData.GetSocketState()==CSocketUDPManagerSocketData::ESocketUDPManagerSocketState::E_OPENED)
				{
					CSocketUDPReceiveFromParameters				Parameters(MReadBuffer,0,MReadBuffer->GetLength());
					CSPSocketUDP								Socket=SocketData.GetSocket().DynamicCast<CSocketUDP>();
					CSocketUDPReceiveFromResult					Result;
					
					Socket->ReceiveFrom(Parameters,Result);

					if (Result.GetNumberOfReceivedBytes()>0)
					{
						const CSocketUDPAddress&				Address=Result.GetUDPAddress();
						CSPByteBuffer							Data(new CByteBuffer(MReadBuffer->GetRawData(),Result.GetNumberOfReceivedBytes()));

						MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("UDP SOCKET MANAGER SUCCESSFULLY READ DATA from SOCKET [",SocketData.GetSocket()->GetSocketID(),"] ! ADDRESS [",Address,"] DATA [",Data,"] LENGTH [",Data->GetLength(),"] !")));

						FireEvent(CCSPSocketUDPManagerMessageResponse(new CSocketUDPManagerMessageResponseSocketRead(Socket->GetSocketID(),Address,Data)));
					}
				}
			}
			catch(const CSocketException& E)
			{
				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("UDP SOCKET MANAGER FAILED to READ DATA from SOCKET [",SocketData.GetSocket()->GetSocketID(),"] !"),E));

				// If FATAL SOCKET ERROR has OCCURED while READING from UDP SOCKET, UDP SOCKET will FAIL.
				if (IsFatalReadError(E.GetSocketExceptionCode())==true)
				{
					ChangeSocketStateToFailedState(SocketData);
				}
			}
			catch(const CException& E)
			{
				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("UDP SOCKET MANAGER FAILED to READ DATA from SOCKET [",SocketData.GetSocket()->GetSocketID(),"] !"),E));

				// If ANY NON-SOCKET ERROR has OCCURED while READING from UDP SOCKET, UDP SOCKET will FAIL.
				ChangeSocketStateToFailedState(SocketData);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManager::WaitForSocketEvents(void)
	{
		try
		{
			CSteadyClock::Milliseconds							CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();
			CTimeout											Timeout=(MRequestTSCollection.GetLength()==0) ? CTimeout::GetInfinite() : CTimeout::GetZero();
			CVector<CSocketWaitState>							SocketStates;

			SocketStates.ReserveCapacity(MSocketCollection.GetLength());

			for(CSocketCollection::CKeyValuePair& Pair : MSocketCollection)
			{
				CSocketUDPManagerSocketData&					SocketData=Pair.GetSecond();

				if (SocketData.GetSocketState()==CSocketUDPManagerSocketData::ESocketUDPManagerSocketState::E_OPENED)
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
					for(const CSocketUDPManagerWriteOperation& WriteOperation : SocketData.GetWriteOperations())
					{
						CTimeout								WriteOperationTimeout=WriteOperation.GetPacket()->GetWriteExpirationTime().CalculateTimeout(CurrentTimeInMS);

						Timeout=CTimeout::Min(Timeout,WriteOperationTimeout);
					}
				}
			}

			MWaitObject->WaitForEvent(SocketStates,Timeout);

			for(const CSocketWaitState& SocketState : SocketStates)
			{
				CSocketUDPManagerSocketData&					SocketData=MSocketCollection[SocketState.GetSocket()->GetSocketID()];
				ESocketWaitResultFlags							ResultFlags=SocketState.GetWaitResultFlags();

				if ((ResultFlags & ESocketWaitResultFlags::E_ERROR)!=ESocketWaitResultFlags::E_NONE)
				{
					MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("UDP SOCKET MANAGER DETECTED that SOCKET [",SocketState.GetSocket()->GetSocketID(),"] FAILED !")));

					CancelAllWriteOperations(SocketState.GetSocket()->GetSocketID());

					// If UDP SOCKET ERROR DETECTED, UDP SOCKET will FAIL.
					ChangeSocketStateToFailedState(SocketData);
				}
				else if ((ResultFlags & ESocketWaitResultFlags::E_CLOSE)!=ESocketWaitResultFlags::E_NONE)
				{
					MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("UDP SOCKET MANAGER DETECTED that SOCKET [",SocketState.GetSocket()->GetSocketID(),"] was CLOSED !")));

					CancelAllWriteOperations(SocketState.GetSocket()->GetSocketID());

					ChangeSocketState(SocketData,CSocketUDPManagerSocketData::ESocketUDPManagerSocketState::E_CLOSED,CSPSocketUDPManagerMessageResponse(new CSocketUDPManagerMessageResponseSocketClose(SocketState.GetSocket()->GetSocketID())));
				}
			}
		}
		catch(const CSocketException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("UDP SOCKET MANAGER FAILED FATALLY ! ALL SOCKETS are DISABLED !"),E));

			for(CSocketCollection::CKeyValuePair& Pair : MSocketCollection)
			{
				CSocketUDPManagerSocketData&					SocketData=Pair.GetSecond();

				CancelAllWriteOperations(SocketData.GetSocket()->GetSocketID());

				// If FATAL SOCKET ERROR has OCCURED while WAITING for UDP SOCKET EVENTS, UDP SOCKET will FAIL.
				if (IsFatalWaitError(E.GetSocketExceptionCode())==true)
				{
					ChangeSocketStateToFailedState(SocketData);
				}
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("UDP SOCKET MANAGER FAILED FATALLY ! ALL SOCKETS are DISABLED !"),E));

			for(CSocketCollection::CKeyValuePair& Pair : MSocketCollection)
			{
				CSocketUDPManagerSocketData&					SocketData=Pair.GetSecond();

				CancelAllWriteOperations(SocketData.GetSocket()->GetSocketID());

				// If ANY NON-SOCKET ERROR has OCCURED while WAITING for UDP SOCKET EVENTS, UDP SOCKET will FAIL.
				ChangeSocketStateToFailedState(SocketData);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManager::CancelAllWriteOperations(const CSocketID& SocketID)
	{
		CSocketUDPManagerSocketData&							SocketData=MSocketCollection[SocketID];

		for(const CSocketUDPManagerWriteOperation& WriteOperation : SocketData.GetWriteOperations())
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("UDP SOCKET MANAGER FAILED to WRITE DATA to SOCKET [",SocketData.GetSocket()->GetSocketID(),"] ! OPERATION was CANCELLED !")));

			FireEvent(CCSPSocketUDPManagerMessageResponse(new CSocketUDPManagerMessageResponseSocketWrite(SocketData.GetSocket()->GetSocketID(),WriteOperation.GetPacket()->GetMessageContext(),false,WriteOperation.GetPacket()->GetDestinationAddress(),WriteOperation.GetPacket()->GetData(),WriteOperation.GetNumberOfBytesWritten())));
		}

		SocketData.ClearWriteOperations();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManager::ProcessOperations(void)
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
	void CSocketUDPManager::ProcessSocketAdd(CCSPSocketUDPManagerMessageRequestSocketAdd Request)
	{
		if (MSocketCollection.Contains(Request->GetSocketID())==false && MSocketCollection.GetLength()<MWaitObject->GetMaximumNumberOfSocket())
		{
			MSocketCollection.Add(Request->GetSocketID(),CSocketUDPManagerSocketData(Request->GetSocket()));

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("UDP SOCKET MANAGER SUCCEESSFULLY ADDED SOCKET [",Request->GetSocketID(),"] !")));

			FireEvent(CCSPSocketUDPManagerMessageResponse(new CSocketUDPManagerMessageResponseSocketAdd(Request->GetMessageContext(),true,Request->GetSocket())));
		}
		else
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("UDP SOCKET MANAGER FAILED to ADD SOCKET [",Request->GetSocketID(),"] because SOCKET already EXISTS !")));

			FireEvent(CCSPSocketUDPManagerMessageResponse(new CSocketUDPManagerMessageResponseSocketAdd(Request->GetMessageContext(),false,Request->GetSocket())));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManager::ProcessSocketRemove(CCSPSocketUDPManagerMessageRequestSocketRemove Request)
	{
		if (MSocketCollection.Contains(Request->GetSocketID())==true)
		{
			MSocketCollection.Erase(Request->GetSocketID());

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("UDP SOCKET MANAGER SUCCEESSFULLY REMOVED SOCKET [",Request->GetSocketID(),"] !")));

			FireEvent(CCSPSocketUDPManagerMessageResponse(new CSocketUDPManagerMessageResponseSocketRemove(Request->GetSocketID(),Request->GetMessageContext(),true)));
		}
		else
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("UDP SOCKET MANAGER FAILED to REMOVE SOCKET [",Request->GetSocketID(),"] because SOCKET doesn't EXIST !")));

			FireEvent(CCSPSocketUDPManagerMessageResponse(new CSocketUDPManagerMessageResponseSocketRemove(Request->GetSocketID(),Request->GetMessageContext(),false)));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManager::ProcessSocketWrite(CCSPSocketUDPManagerMessageRequestSocketWrite Request)
	{
		if (MSocketCollection.Contains(Request->GetSocketID())==true)
		{
			CSocketUDPManagerSocketData&						SocketData=MSocketCollection[Request->GetSocketID()];

			if (SocketData.GetSocketState()==CSocketUDPManagerSocketData::ESocketUDPManagerSocketState::E_OPENED)
			{
				MSocketCollection[Request->GetSocketID()].AddWriteOperation(Request);
			}
			else
			{
				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("UDP SOCKET MANAGER FAILED to WRITE to SOCKET [",Request->GetSocketID(),"] because SOCKET is NOT OPENED !")));

				FireEvent(CCSPSocketUDPManagerMessageResponse(new CSocketUDPManagerMessageResponseSocketWrite(Request->GetSocketID(),Request->GetMessageContext(),false,Request->GetDestinationAddress(),Request->GetData(),0)));
			}
		}
		else
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("UDP SOCKET MANAGER FAILED to WRITE to SOCKET [",Request->GetSocketID(),"] because SOCKET doesn't EXIST !")));

			FireEvent(CCSPSocketUDPManagerMessageResponse(new CSocketUDPManagerMessageResponseSocketWrite(Request->GetSocketID(),Request->GetMessageContext(),false,Request->GetDestinationAddress(),Request->GetData(),0)));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManager::ThreadMethod(bool)
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

				CCSPSocketUDPManagerMessageRequest				Request;

				if (MRequestTSCollection.PopFront(Request)==false)
				{
					break;
				}

				if (Request.IsTypeOfAsConst<CSocketUDPManagerMessageRequestSocketAdd>()==true)
				{
					ProcessSocketAdd(Request.DynamicCastAsConst<CSocketUDPManagerMessageRequestSocketAdd>());
				}
				else if (Request.IsTypeOfAsConst<CSocketUDPManagerMessageRequestSocketRemove>()==true)
				{
					ProcessSocketRemove(Request.DynamicCastAsConst<CSocketUDPManagerMessageRequestSocketRemove>());
				}
				else if (Request.IsTypeOfAsConst<CSocketUDPManagerMessageRequestSocketWrite>()==true)
				{
					ProcessSocketWrite(Request.DynamicCastAsConst<CSocketUDPManagerMessageRequestSocketWrite>());
				}

				ProcessOperations();
			}

			ProcessOperations();
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("UDP SOCKET MANAGER DETECTED FATAL ERROR !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("UDP SOCKET MANAGER DETECTED FATAL ERROR !"),CUnknownException()));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CTimeout CSocketUDPManager::GetTimeout(void)
	{
		return(CTimeout::GetZero());
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManager::ThreadSafeInitializationEvent(void)
	{
		MExitEvent.Reset();
		MSocketCollection.Clear();
		MWaitObject->ResetEvent();
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManager::ThreadSafeUninitializationEvent(void)
	{
		MExitEvent.Reset();
		MSocketCollection.Clear();
		MRequestTSCollection.Clear();
		MWaitObject->ResetEvent();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManager::AddEvent(const CEventID& EventID, ISocketUDPManagerCallback& Callback)
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
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("UDP SOCKET MANAGER FAILED to ADD EVENT !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("UDP SOCKET MANAGER FAILED to ADD EVENT !"),CUnknownException()));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManager::RemoveEvent(const CEventID& EventID)
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
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("UDP SOCKET MANAGER FAILED to REMOVE EVENT !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("UDP SOCKET MANAGER FAILED to REMOVE EVENT !"),CUnknownException()));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketUDPManager::HasEvent(const CEventID& EventID) const
	{
		CLock													Lock(MSocketManagerMutex);
		{
			return(MCallbackDispatcher.HasEvent(EventID));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManager::StartThread(void)
	{
		try
		{
			CLock												Lock(MSocketManagerMutex);
			{
				MCallbackDispatcher.StartDispatcher();

				InternalStartThread();

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("UDP SOCKET MANAGER SUCCESSFULLY STARTED !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("UDP SOCKET MANAGER FAILED to START !"),E));

			StopThread();
			throw;
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("UDP SOCKET MANAGER FAILED to START !"),CUnknownException()));

			StopThread();
			throw;
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManager::StopThread(void) noexcept
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

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("UDP SOCKET MANAGER SUCCESSFULLY STOPPED !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("UDP SOCKET MANAGER FAILED to STOP !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("UDP SOCKET MANAGER FAILED to STOP !"),CUnknownException()));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManager::SendRequest(CCSPSocketUDPManagerMessageRequest MessageRequest)
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
	Size CSocketUDPManager::GetMaximumNumberOfSockets(void)
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