//----------------------------------------------------------------------------------------------------------------------
#include "CSocketCANManagerCallbackDispatcher.h"
#include "CSocketCANManagerEventContext.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerCallbackDispatcher::CSocketCANManagerCallbackDispatcher(CLogWriter& LogWriter)
		: CEventThread<CCSPSocketCANManagerMessageResponse,void>(LogWriter,"CAN MANAGER CALLBACK DISPATCHER")
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerCallbackDispatcher::~CSocketCANManagerCallbackDispatcher(void)
	{
		ClearAllCallbacks();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManagerCallbackDispatcher::ProcessMessageResponseCallback(const CEventContext& EventContext, CCSPSocketCANManagerMessageResponse MessageResponse)
	{
		if (EventContext.IsTypeOf<CSocketCANManagerEventContext>()==true)
		{
			const CSocketCANManagerEventContext&				TypedEventContext=EventContext.DynamicCastReference<CSocketCANManagerEventContext>();
			ISocketCANManagerCallback&							Callback=TypedEventContext.GetCallback();

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
	void CSocketCANManagerCallbackDispatcher::AddEvent(const CEventID& EventID, ISocketCANManagerCallback& Callback)
	{
		AddCallbackMethod(CSPEventContext(new CSocketCANManagerEventContext(EventID,Callback)),CEventCallbackMethod<CSocketCANManagerCallbackDispatcher,CCSPSocketCANManagerMessageResponse,void>(this,&CSocketCANManagerCallbackDispatcher::ProcessMessageResponseCallback));
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManagerCallbackDispatcher::RemoveEvent(const CEventID& EventID)
	{
		RemoveCallback(EventID);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketCANManagerCallbackDispatcher::HasEvent(const CEventID& EventID) const
	{
		return(HasCallback(EventID));
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManagerCallbackDispatcher::ClearEvents(void)
	{
		ClearAllCallbacks();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManagerCallbackDispatcher::StartDispatcher(void)
	{
		StartThread();
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManagerCallbackDispatcher::StopDispatcher(void) noexcept
	{
		StopThread();
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANManagerCallbackDispatcher::DispatchEvent(CCSPSocketCANManagerMessageResponse MessageResponse)
	{
		SendEventData(MessageResponse);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------