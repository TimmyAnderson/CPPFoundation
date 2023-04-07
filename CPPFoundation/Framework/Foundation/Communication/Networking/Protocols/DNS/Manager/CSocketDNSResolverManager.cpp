//----------------------------------------------------------------------------------------------------------------------
#include "CSocketDNSResolverManager.h"
#include <Framework/Foundation/Exceptions/CSocketException.h>
#include <Framework/Foundation/Exceptions/CUnknownException.h>
#include <Framework/Foundation/Threads/CLock.h>
#include "CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress.h"
#include "CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManager::CSocketDNSResolverManager(CLogWriter& LogWriter, ISocketDNSResolverManagerCallback& Callback)
		: CThread(LogWriter,CString::Format("DNS RESOLVER SOCKET MANAGER THREAD")), MLogCategoryDNSResolverManager(CString::Format("DNS RESOLVER SOCKET MANAGER")), MSocketDNSResolverManagerMutex(), MExitEvent(false), MCallbackDispatcher(GetLogWriter(),Callback), MDNSResolver(), MRequestTSCollection(), MRequestCollection()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManager::~CSocketDNSResolverManager(void)
	{
		if (IsThreadRunning()==true)
		{
			StopThread();
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CLogCategory& CSocketDNSResolverManager::GetLogCategoryDNSResolverManager(void) const noexcept
	{
		return(MLogCategoryDNSResolverManager);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketDNSResolverManager::FireEvent(CCSPSocketDNSResolverManagerMessageResponse MessageResponse) noexcept
	{
		try
		{
			MCallbackDispatcher.SendEventData(MessageResponse);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryDNSResolverManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("DNS RESOLVER SOCKET MANAGER FAILED to FIRE EVENT [",MessageResponse,"] !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryDNSResolverManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("DNS RESOLVER SOCKET MANAGER FAILED to FIRE EVENT [",MessageResponse,"] !"),CUnknownException()));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketDNSResolverManager::ProcessDNSAddressToIPAddress(CCSPSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress MessageRequest)
	{
		try
		{
			CVector<CSocketIPAddress>							IPAddresses=MDNSResolver.ConvertDNSAddressToIPAddress(MessageRequest->GetDNSAddress(),MessageRequest->GetAddressType(),MessageRequest->GetProtocolType());
			CCSPSocketDNSResolverManagerMessageResponse			MessageResponse(new CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress(MessageRequest->GetMessageContext(),true,MessageRequest->GetDNSAddress(),FUNCTION_MOVE(IPAddresses)));

			FireEvent(MessageResponse);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryDNSResolverManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("DNS RESOLVER SOCKET MANAGER FAILED to PROCESS MESSAGE [",MessageRequest,"] !"),E));

			CCSPSocketDNSResolverManagerMessageResponse			MessageResponse=MessageRequest->CreateErrorResponse();

			FireEvent(MessageResponse);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryDNSResolverManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("DNS RESOLVER SOCKET MANAGER FAILED to PROCESS MESSAGE [",MessageRequest,"] !"),CUnknownException()));

			CCSPSocketDNSResolverManagerMessageResponse			MessageResponse=MessageRequest->CreateErrorResponse();

			FireEvent(MessageResponse);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketDNSResolverManager::ProcessIPAddressToDNSAddress(CCSPSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress MessageRequest)
	{
		try
		{
			CSocketDNSAddress									DNSAddress=MDNSResolver.ConvertIPAddressToDNSAddress(MessageRequest->GetIPAddress(),MessageRequest->GetDNSAddressRequired());
			CCSPSocketDNSResolverManagerMessageResponse			MessageResponse(new CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress(MessageRequest->GetMessageContext(),true,FUNCTION_MOVE(DNSAddress)));

			FireEvent(MessageResponse);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryDNSResolverManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("DNS RESOLVER SOCKET MANAGER FAILED to PROCESS MESSAGE [",MessageRequest,"] !"),E));

			CCSPSocketDNSResolverManagerMessageResponse			MessageResponse=MessageRequest->CreateErrorResponse();

			FireEvent(MessageResponse);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryDNSResolverManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("DNS RESOLVER SOCKET MANAGER FAILED to PROCESS MESSAGE [",MessageRequest,"] !"),CUnknownException()));

			CCSPSocketDNSResolverManagerMessageResponse			MessageResponse=MessageRequest->CreateErrorResponse();

			FireEvent(MessageResponse);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketDNSResolverManager::ProcessOperations(void)
	{
		while(true)
		{
			if (HasThreadExiting()==true)
			{
				return;
			}

			CCSPSocketDNSResolverManagerMessageRequest			Request;

			if (MRequestCollection.PopFront(Request)==true)
			{
				if (Request.IsTypeOfAsConst<CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress>()==true)
				{
					ProcessDNSAddressToIPAddress(Request.DynamicCastAsConst<CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress>());
				}
				else if (Request.IsTypeOfAsConst<CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress>()==true)
				{
					ProcessIPAddressToDNSAddress(Request.DynamicCastAsConst<CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress>());
				}
				else
				{
					MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryDNSResolverManager(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("DNS RESOLVER SOCKET MANAGER DETECTED INVALID REQUEST MESSAGE [",Request,"] !")));

					CCSPSocketDNSResolverManagerMessageResponse		MessageResponse=Request->CreateErrorResponse();

					FireEvent(MessageResponse);
				}
			}
			else
			{
				break;
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketDNSResolverManager::ThreadMethod(bool)
	{
		try
		{
			if (HasThreadExiting()==true)
			{
				return;
			}

			while(true)
			{
				CCSPSocketDNSResolverManagerMessageRequest		Request;

				if (MRequestTSCollection.PopFront(Request)==false)
				{
					break;
				}

				MRequestCollection.PushBack(Request);
			}

			ProcessOperations();
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryDNSResolverManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("DNS RESOLVER SOCKET MANAGER DETECTED FATAL ERROR !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryDNSResolverManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("DNS RESOLVER SOCKET MANAGER DETECTED FATAL ERROR !"),CUnknownException()));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CTimeout CSocketDNSResolverManager::GetTimeout(void)
	{
		return(CTimeout::GetInfinite());
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketDNSResolverManager::ThreadSafeInitializationEvent(void)
	{
		MExitEvent.Reset();
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketDNSResolverManager::ThreadSafeUninitializationEvent(void)
	{
		MExitEvent.Reset();
		MRequestTSCollection.Clear();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketDNSResolverManager::StartThread(void)
	{
		try
		{
			CLock												Lock(MSocketDNSResolverManagerMutex);
			{
				MCallbackDispatcher.StartThread();

				InternalStartThread();

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryDNSResolverManager(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("DNS RESOLVER SOCKET MANAGER SUCCESSFULLY STARTED !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryDNSResolverManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("DNS RESOLVER SOCKET MANAGER FAILED to START !"),E));

			StopThread();
			throw;
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryDNSResolverManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("DNS RESOLVER SOCKET MANAGER FAILED to START !"),CUnknownException()));

			StopThread();
			throw;
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketDNSResolverManager::StopThread(void) noexcept
	{
		try
		{
			CLock												Lock(MSocketDNSResolverManagerMutex);
			{
				// METHOD is MARKED as 'noexcept'.
				InternalStopThread();

				// METHOD is MARKED as 'noexcept'.
				MCallbackDispatcher.StopThread();

				MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryDNSResolverManager(),ELogRecordLevel::E_INFORMATION,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("DNS RESOLVER SOCKET MANAGER SUCCESSFULLY STOPPED !")));
			}
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryDNSResolverManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("DNS RESOLVER SOCKET MANAGER FAILED to STOP !"),E));
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryDNSResolverManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("DNS RESOLVER SOCKET MANAGER FAILED to STOP !"),CUnknownException()));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketDNSResolverManager::SendRequest(CCSPSocketDNSResolverManagerMessageRequest MessageRequest)
	{
		CLock													Lock(MSocketDNSResolverManagerMutex);
		{
			if (IsThreadRunning()==true)
			{
				MRequestTSCollection.PushBack(MessageRequest);
				SetEvent();
			}
			else
			{
				FireEvent(MessageRequest->CreateErrorResponse());
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------