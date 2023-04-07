//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPClientManagerCallbackDispatcher.h"
#include "CSocketTCPClientManagerEventContext.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerCallbackDispatcher::CSocketTCPClientManagerCallbackDispatcher(CLogWriter& LogWriter)
		: CEventThread<CCSPSocketTCPClientManagerMessageResponse,void>(LogWriter,"TCP CLIENT MANAGER CALLBACK DISPATCHER")
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerCallbackDispatcher::~CSocketTCPClientManagerCallbackDispatcher(void)
	{
		ClearAllCallbacks();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClientManagerCallbackDispatcher::ProcessMessageResponseCallback(const CEventContext& EventContext, CCSPSocketTCPClientManagerMessageResponse MessageResponse)
	{
		if (EventContext.IsTypeOf<CSocketTCPClientManagerEventContext>()==true)
		{
			const CSocketTCPClientManagerEventContext&			TypedEventContext=EventContext.DynamicCastReference<CSocketTCPClientManagerEventContext>();
			ISocketTCPClientManagerCallback&					Callback=TypedEventContext.GetCallback();

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
	void CSocketTCPClientManagerCallbackDispatcher::AddEvent(const CEventID& EventID, ISocketTCPClientManagerCallback& Callback)
	{
		AddCallbackMethod(CSPEventContext(new CSocketTCPClientManagerEventContext(EventID,Callback)),CEventCallbackMethod<CSocketTCPClientManagerCallbackDispatcher,CCSPSocketTCPClientManagerMessageResponse,void>(this,&CSocketTCPClientManagerCallbackDispatcher::ProcessMessageResponseCallback));
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClientManagerCallbackDispatcher::RemoveEvent(const CEventID& EventID)
	{
		RemoveCallback(EventID);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketTCPClientManagerCallbackDispatcher::HasEvent(const CEventID& EventID) const
	{
		return(HasCallback(EventID));
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClientManagerCallbackDispatcher::ClearEvents(void)
	{
		ClearAllCallbacks();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClientManagerCallbackDispatcher::StartDispatcher(void)
	{
		StartThread();
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClientManagerCallbackDispatcher::StopDispatcher(void) noexcept
	{
		StopThread();
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketTCPClientManagerCallbackDispatcher::DispatchEvent(CCSPSocketTCPClientManagerMessageResponse MessageResponse)
	{
		SendEventData(MessageResponse);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------