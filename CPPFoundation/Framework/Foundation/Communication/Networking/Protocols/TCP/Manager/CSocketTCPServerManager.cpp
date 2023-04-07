//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPServerManager.h"
#include <Framework/Foundation/Exceptions/CSocketException.h>
#include <Framework/Foundation/Exceptions/CUnknownException.h>
#include <Framework/Foundation/Threads/CLock.h>
#include <Framework/Platform/Sockets/CSocketWaitObject.h>
#include "CSocketTCPServerManagerMessageResponseSocketAccept.h"
#include "CSocketTCPServerManagerMessageResponseSocketAdd.h"
#include "CSocketTCPServerManagerMessageResponseSocketClose.h"
#include "CSocketTCPServerManagerMessageResponseSocketError.h"
#include "CSocketTCPServerManagerMessageResponseSocketRemove.h"
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
	CSocketTCPServerManager::CSocketTCPServerManager(CLogWriter& LogWriter)
		: CThread(LogWriter,CString::Format("SOCKET TCP SERVER MANAGER THREAD")), MLogCategorySocketManager(CString::Format("SOCKET TCP SERVER MANAGER")), MSocketManagerMutex(), MExitEvent(false), MCallbackDispatcher(GetLogWriter()), MSocketCollection(), MRequestTSCollection(), MWaitObject(new CSocketWaitObject())
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManager::~CSocketTCPServerManager(void)
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
	const CLogCategory& CSocketTCPServerManager::GetLogCategorySocketManager(void) const noexcept
	{
		return(MLogCategorySocketManager);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPServerManager::FireEvent(CCSPSocketTCPServerManagerMessageResponse MessageResponse)
	{
		try
		{
			MCallbackDispatcher.DispatchEvent(MessageResponse);
		}
		catch(...)
		{
			// IGNORE EXCEPTIONS.
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPServerManager::SetThreadExitFlag(void)
	{
		// First EXIT EVENT MUST be SET.
		MExitEvent.Set();

		// Just after that THREAD MUST be AWAKEN.
		MWaitObject->SetEvent();
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketTCPServerManager::HasThreadExitFlagSet(void)
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
	void CSocketTCPServerManager::ChangeSocketState(CSocketTCPServerManagerSocketData& SocketData, CSocketTCPServerManagerSocketData::ESocketTCPServerManagerSocketState State, CSPSocketTCPServerManagerMessageResponse MessageResponse)
	{
		if (SocketData.GetSocketState()!=State)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP SERVER SOCKET MANAGER for SOCKET [",SocketData.GetSocket()->GetSocketID(),"] CHANGED STATE STATE [",CSocketTCPServerManagerSocketData::SocketStateToString(SocketData.GetSocketState())," -> ",CSocketTCPServerManagerSocketData::SocketStateToString(State),"] !")));

			SocketData.SetSocketState(State);

			if (MessageResponse!=nullptr)
			{
				FireEvent(MessageResponse);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPServerManager::ChangeSocketStateToFailedState(CSocketTCPServerManagerSocketData& SocketData)
	{
		if (SocketData.GetSocketState()!=CSocketTCPServerManagerSocketData::ESocketTCPServerManagerSocketState::E_FAILED)
		{
			ChangeSocketState(SocketData,CSocketTCPServerManagerSocketData::ESocketTCPServerManagerSocketState::E_FAILED,CSPSocketTCPServerManagerMessageResponse(new CSocketTCPServerManagerMessageResponseSocketError(SocketData.GetSocket()->GetSocketID())));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPServerManager::AcceptSocket(CSPSocketTCPServer Socket)
	{
		try
		{
			CSocketTCPAddress									DestinationAddress;
			ISPSocketTCPWrapper									SocketTCPWrapper=Socket->Accept(DestinationAddress);

			if (SocketTCPWrapper!=nullptr)
			{
				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP SERVER SOCKET MANAGER ACCEPTED SOCKET [",SocketTCPWrapper,"] from ADDRESS [",DestinationAddress,"] !")));

				FireEvent(CCSPSocketTCPServerManagerMessageResponse(new CSocketTCPServerManagerMessageResponseSocketAccept(SocketTCPWrapper,DestinationAddress)));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP SERVER SOCKET MANAGER FAILED to ACCEPT SOCKET [",Socket,"] !"),E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPServerManager::WaitForSocketEvents(void)
	{
		try
		{
			CTimeout											Timeout=(MRequestTSCollection.GetLength()==0) ? CTimeout::GetInfinite() : CTimeout::GetZero();
			CVector<CSocketWaitState>							SocketStates;

			SocketStates.ReserveCapacity(MSocketCollection.GetLength());

			for(CSocketCollection::CKeyValuePair& Pair : MSocketCollection)
			{
				CSocketTCPServerManagerSocketData&				SocketData=Pair.GetSecond();

				if (SocketData.GetSocketState()==CSocketTCPServerManagerSocketData::ESocketTCPServerManagerSocketState::E_OPENED)
				{
					SocketStates.Add(CSocketWaitState(SocketData.GetSocket(),ESocketWaitFlags::E_READ));
				}
			}

			MWaitObject->WaitForEvent(SocketStates,Timeout);

			for(const CSocketWaitState& SocketState : SocketStates)
			{
				CSocketTCPServerManagerSocketData&				SocketData=MSocketCollection[SocketState.GetSocket()->GetSocketID()];
				ESocketWaitResultFlags							ResultFlags=SocketState.GetWaitResultFlags();

				if ((ResultFlags & ESocketWaitResultFlags::E_ERROR)!=ESocketWaitResultFlags::E_NONE)
				{
					MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP SERVER SOCKET MANAGER DETECTED that SOCKET [",SocketState.GetSocket()->GetSocketID(),"] FAILED !")));

					ChangeSocketStateToFailedState(SocketData);
				}
				else if ((ResultFlags & ESocketWaitResultFlags::E_CLOSE)!=ESocketWaitResultFlags::E_NONE)
				{
					MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP SERVER SOCKET MANAGER DETECTED that SOCKET [",SocketState.GetSocket()->GetSocketID(),"] was CLOSED !")));

					ChangeSocketState(SocketData,CSocketTCPServerManagerSocketData::ESocketTCPServerManagerSocketState::E_CLOSED,CSPSocketTCPServerManagerMessageResponse(new CSocketTCPServerManagerMessageResponseSocketClose(SocketState.GetSocket()->GetSocketID())));
				}
				else if ((ResultFlags & ESocketWaitResultFlags::E_READ)!=ESocketWaitResultFlags::E_NONE)
				{
					MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP SERVER SOCKET MANAGER DETECTED READ EVENT for SOCKET [",SocketState.GetSocket()->GetSocketID(),"] !")));

					CSPSocketTCPServer							Socket=SocketState.GetSocket().DynamicCast<CSocketTCPServer>();

					AcceptSocket(Socket);
				}
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP SERVER SOCKET MANAGER FAILED FATALLY ! ALL SOCKETS are DISABLED !"),E));

			for(CSocketCollection::CKeyValuePair& Pair : MSocketCollection)
			{
				CSocketTCPServerManagerSocketData&				SocketData=Pair.GetSecond();

				ChangeSocketStateToFailedState(SocketData);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPServerManager::ProcessOperations(void)
	{
		if (HasThreadExitFlagSet()==true)
		{
			return;
		}

		WaitForSocketEvents();
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPServerManager::ProcessSocketAdd(CCSPSocketTCPServerManagerMessageRequestSocketAdd Request)
	{
		if (MSocketCollection.Contains(Request->GetSocketID())==false && MSocketCollection.GetLength()<MWaitObject->GetMaximumNumberOfSocket())
		{
			MSocketCollection.Add(Request->GetSocketID(),CSocketTCPServerManagerSocketData(Request->GetSocket()));

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP SERVER SOCKET MANAGER SUCCEESSFULLY ADDED SOCKET [",Request->GetSocketID(),"] !")));

			FireEvent(CCSPSocketTCPServerManagerMessageResponse(new CSocketTCPServerManagerMessageResponseSocketAdd(Request->GetMessageContext(),true,Request->GetSocket())));
		}
		else
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP SERVER SOCKET MANAGER FAILED to ADD SOCKET [",Request->GetSocketID(),"] because SOCKET already EXISTS !")));

			FireEvent(CCSPSocketTCPServerManagerMessageResponse(new CSocketTCPServerManagerMessageResponseSocketAdd(Request->GetMessageContext(),false,Request->GetSocket())));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPServerManager::ProcessSocketRemove(CCSPSocketTCPServerManagerMessageRequestSocketRemove Request)
	{
		if (MSocketCollection.Contains(Request->GetSocketID())==true)
		{
			MSocketCollection.Erase(Request->GetSocketID());

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP SERVER SOCKET MANAGER SUCCEESSFULLY REMOVED SOCKET [",Request->GetSocketID(),"] !")));

			FireEvent(CCSPSocketTCPServerManagerMessageResponse(new CSocketTCPServerManagerMessageResponseSocketRemove(Request->GetSocketID(),Request->GetMessageContext(),true)));
		}
		else
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP SERVER SOCKET MANAGER FAILED to REMOVE SOCKET [",Request->GetSocketID(),"] because SOCKET doesn't EXIST !")));

			FireEvent(CCSPSocketTCPServerManagerMessageResponse(new CSocketTCPServerManagerMessageResponseSocketRemove(Request->GetSocketID(),Request->GetMessageContext(),false)));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPServerManager::ThreadMethod(bool)
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

				CCSPSocketTCPServerManagerMessageRequest		Request;

				if (MRequestTSCollection.PopFront(Request)==false)
				{
					break;
				}

				if (Request.IsTypeOfAsConst<CSocketTCPServerManagerMessageRequestSocketAdd>()==true)
				{
					ProcessSocketAdd(Request.DynamicCastAsConst<CSocketTCPServerManagerMessageRequestSocketAdd>());
				}
				else if (Request.IsTypeOfAsConst<CSocketTCPServerManagerMessageRequestSocketRemove>()==true)
				{
					ProcessSocketRemove(Request.DynamicCastAsConst<CSocketTCPServerManagerMessageRequestSocketRemove>());
				}

				ProcessOperations();
			}

			ProcessOperations();
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP SERVER SOCKET MANAGER DETECTED FATAL ERROR !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP SERVER SOCKET MANAGER DETECTED FATAL ERROR !"),CUnknownException()));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CTimeout CSocketTCPServerManager::GetTimeout(void)
	{
		return(CTimeout::GetZero());
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPServerManager::ThreadSafeInitializationEvent(void)
	{
		MExitEvent.Reset();
		MSocketCollection.Clear();
		MWaitObject->ResetEvent();
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPServerManager::ThreadSafeUninitializationEvent(void)
	{
		MExitEvent.Reset();
		MSocketCollection.Clear();
		MRequestTSCollection.Clear();
		MWaitObject->ResetEvent();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPServerManager::AddEvent(const CEventID& EventID, ISocketTCPServerManagerCallback& Callback)
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
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP SERVER SOCKET MANAGER FAILED to ADD EVENT !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP SERVER SOCKET MANAGER FAILED to ADD EVENT !"),CUnknownException()));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPServerManager::RemoveEvent(const CEventID& EventID)
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
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP SERVER SOCKET MANAGER FAILED to REMOVE EVENT !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP SERVER SOCKET MANAGER FAILED to REMOVE EVENT !"),CUnknownException()));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketTCPServerManager::HasEvent(const CEventID& EventID) const
	{
		CLock												Lock(MSocketManagerMutex);
		{
			return(MCallbackDispatcher.HasEvent(EventID));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPServerManager::StartThread(void)
	{
		try
		{
			CLock												Lock(MSocketManagerMutex);
			{
				MCallbackDispatcher.StartDispatcher();

				InternalStartThread();

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP SERVER SOCKET MANAGER SUCCESSFULLY STARTED !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP SERVER SOCKET MANAGER FAILED to START !"),E));

			StopThread();
			throw;
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP SERVER SOCKET MANAGER FAILED to START !"),CUnknownException()));

			StopThread();
			throw;
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPServerManager::StopThread(void) noexcept
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

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP SERVER SOCKET MANAGER SUCCESSFULLY STOPPED !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP SERVER SOCKET MANAGER FAILED to STOP !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySocketManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("TCP SERVER SOCKET MANAGER FAILED to STOP !"),CUnknownException()));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPServerManager::SendRequest(CCSPSocketTCPServerManagerMessageRequest MessageRequest)
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
	Size CSocketTCPServerManager::GetMaximumNumberOfSockets(void)
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