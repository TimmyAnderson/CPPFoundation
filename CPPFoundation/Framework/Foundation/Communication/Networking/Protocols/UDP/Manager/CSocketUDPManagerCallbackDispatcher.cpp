//----------------------------------------------------------------------------------------------------------------------
#include "CSocketUDPManagerCallbackDispatcher.h"
#include "CSocketUDPManagerEventContext.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerCallbackDispatcher::CSocketUDPManagerCallbackDispatcher(CLogWriter& LogWriter)
		: CEventThread<CCSPSocketUDPManagerMessageResponse,void>(LogWriter,"UDP MANAGER CALLBACK DISPATCHER")
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerCallbackDispatcher::~CSocketUDPManagerCallbackDispatcher(void)
	{
		ClearAllCallbacks();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManagerCallbackDispatcher::ProcessMessageResponseCallback(const CEventContext& EventContext, CCSPSocketUDPManagerMessageResponse MessageResponse)
	{
		if (EventContext.IsTypeOf<CSocketUDPManagerEventContext>()==true)
		{
			const CSocketUDPManagerEventContext&				TypedEventContext=EventContext.DynamicCastReference<CSocketUDPManagerEventContext>();
			ISocketUDPManagerCallback&							Callback=TypedEventContext.GetCallback();

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
	void CSocketUDPManagerCallbackDispatcher::AddEvent(const CEventID& EventID, ISocketUDPManagerCallback& Callback)
	{
		AddCallbackMethod(CSPEventContext(new CSocketUDPManagerEventContext(EventID,Callback)),CEventCallbackMethod<CSocketUDPManagerCallbackDispatcher,CCSPSocketUDPManagerMessageResponse,void>(this,&CSocketUDPManagerCallbackDispatcher::ProcessMessageResponseCallback));
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManagerCallbackDispatcher::RemoveEvent(const CEventID& EventID)
	{
		RemoveCallback(EventID);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketUDPManagerCallbackDispatcher::HasEvent(const CEventID& EventID) const
	{
		return(HasCallback(EventID));
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManagerCallbackDispatcher::ClearEvents(void)
	{
		ClearAllCallbacks();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManagerCallbackDispatcher::StartDispatcher(void)
	{
		StartThread();
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManagerCallbackDispatcher::StopDispatcher(void) noexcept
	{
		StopThread();
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketUDPManagerCallbackDispatcher::DispatchEvent(CCSPSocketUDPManagerMessageResponse MessageResponse)
	{
		SendEventData(MessageResponse);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------