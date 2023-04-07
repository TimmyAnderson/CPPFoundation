//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPServerManagerCallbackDispatcher.h"
#include "CSocketTCPServerManagerEventContext.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerCallbackDispatcher::CSocketTCPServerManagerCallbackDispatcher(CLogWriter& LogWriter)
		: CEventThread<CCSPSocketTCPServerManagerMessageResponse,void>(LogWriter,"TCP SERVER MANAGER CALLBACK DISPATCHER")
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerCallbackDispatcher::~CSocketTCPServerManagerCallbackDispatcher(void)
	{
		ClearAllCallbacks();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPServerManagerCallbackDispatcher::ProcessMessageResponseCallback(const CEventContext& EventContext, CCSPSocketTCPServerManagerMessageResponse MessageResponse)
	{
		if (EventContext.IsTypeOf<CSocketTCPServerManagerEventContext>()==true)
		{
			const CSocketTCPServerManagerEventContext&			TypedEventContext=EventContext.DynamicCastReference<CSocketTCPServerManagerEventContext>();
			ISocketTCPServerManagerCallback&					Callback=TypedEventContext.GetCallback();

			Callback.ProcessMessageResponse(MessageResponse);
		}
		else
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryEventThread(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("EVENT THREAD [",GetThreadName(),"] FAILED to SENT MESSAGE RESPONSE [",MessageResponse,"] ! INVALID CONTEXT TYPE [",EventContext,"] !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPServerManagerCallbackDispatcher::AddEvent(const CEventID& EventID, ISocketTCPServerManagerCallback& Callback)
	{
		AddCallbackMethod(CSPEventContext(new CSocketTCPServerManagerEventContext(EventID,Callback)),CEventCallbackMethod<CSocketTCPServerManagerCallbackDispatcher,CCSPSocketTCPServerManagerMessageResponse,void>(this,&CSocketTCPServerManagerCallbackDispatcher::ProcessMessageResponseCallback));
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPServerManagerCallbackDispatcher::RemoveEvent(const CEventID& EventID)
	{
		RemoveCallback(EventID);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketTCPServerManagerCallbackDispatcher::HasEvent(const CEventID& EventID) const
	{
		return(HasCallback(EventID));
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPServerManagerCallbackDispatcher::ClearEvents(void)
	{
		ClearAllCallbacks();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPServerManagerCallbackDispatcher::StartDispatcher(void)
	{
		StartThread();
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPServerManagerCallbackDispatcher::StopDispatcher(void) noexcept
	{
		StopThread();
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPServerManagerCallbackDispatcher::DispatchEvent(CCSPSocketTCPServerManagerMessageResponse MessageResponse)
	{
		SendEventData(MessageResponse);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------