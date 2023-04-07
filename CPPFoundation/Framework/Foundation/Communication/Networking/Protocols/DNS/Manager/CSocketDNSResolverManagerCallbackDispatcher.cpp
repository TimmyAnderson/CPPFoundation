//----------------------------------------------------------------------------------------------------------------------
#include "CSocketDNSResolverManagerCallbackDispatcher.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerCallbackDispatcher::CSocketDNSResolverManagerCallbackDispatcher(CLogWriter& LogWriter, ISocketDNSResolverManagerCallback& Callback)
		: CEventThread<CCSPSocketDNSResolverManagerMessageResponse,void>(LogWriter,"DNS RESOLVER MANAGER CALLBACK DISPATCHER"), MCallback(Callback)
	{
		AddCallbackMethod(CSPEventContext(new CEventContext(CEventID("EVENT"))),CEventCallbackMethod<CSocketDNSResolverManagerCallbackDispatcher,CCSPSocketDNSResolverManagerMessageResponse,void>(this,&CSocketDNSResolverManagerCallbackDispatcher::ProcessMessageResponseCallback));
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerCallbackDispatcher::~CSocketDNSResolverManagerCallbackDispatcher(void)
	{
		RemoveCallback(CEventID("EVENT"));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketDNSResolverManagerCallbackDispatcher::ProcessMessageResponseCallback(const CEventContext&, CCSPSocketDNSResolverManagerMessageResponse MessageResponse)
	{
		MCallback.ProcessMessageResponse(MessageResponse);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------