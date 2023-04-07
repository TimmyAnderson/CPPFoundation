//----------------------------------------------------------------------------------------------------------------------
#include "CSocketDNSResolverManagerMessageRequest.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageRequest::CSocketDNSResolverManagerMessageRequest(CCSPSocketDNSResolverManagerMessageContext MessageContext)
		: MMessageContext(MessageContext)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageRequest::CSocketDNSResolverManagerMessageRequest(const CSocketDNSResolverManagerMessageRequest& Other)
		: MMessageContext(Other.MMessageContext)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageRequest::CSocketDNSResolverManagerMessageRequest(CSocketDNSResolverManagerMessageRequest&& Other) noexcept
		: MMessageContext(FUNCTION_MOVE(Other.MMessageContext))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageRequest::~CSocketDNSResolverManagerMessageRequest(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageRequest& CSocketDNSResolverManagerMessageRequest::operator=(const CSocketDNSResolverManagerMessageRequest& Other)
	{
		MMessageContext=Other.MMessageContext;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageRequest& CSocketDNSResolverManagerMessageRequest::operator=(CSocketDNSResolverManagerMessageRequest&& Other) noexcept
	{
		MMessageContext=FUNCTION_MOVE(Other.MMessageContext);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketDNSResolverManagerMessageContext CSocketDNSResolverManagerMessageRequest::GetMessageContext(void) const noexcept
	{
		return(MMessageContext);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------