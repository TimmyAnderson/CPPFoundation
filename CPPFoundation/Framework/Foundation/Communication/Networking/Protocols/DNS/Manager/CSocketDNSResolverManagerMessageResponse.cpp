//----------------------------------------------------------------------------------------------------------------------
#include "CSocketDNSResolverManagerMessageResponse.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageResponse::CSocketDNSResolverManagerMessageResponse(CCSPSocketDNSResolverManagerMessageContext MessageContext, bool OperationSucceeded)
		: MMessageContext(MessageContext), MOperationSucceeded(OperationSucceeded)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageResponse::CSocketDNSResolverManagerMessageResponse(const CSocketDNSResolverManagerMessageResponse& Other)
		: MMessageContext(Other.MMessageContext), MOperationSucceeded(Other.MOperationSucceeded)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageResponse::CSocketDNSResolverManagerMessageResponse(CSocketDNSResolverManagerMessageResponse&& Other)
		: MMessageContext(FUNCTION_MOVE(Other.MMessageContext)), MOperationSucceeded(Other.MOperationSucceeded)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageResponse::~CSocketDNSResolverManagerMessageResponse(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageResponse& CSocketDNSResolverManagerMessageResponse::operator=(const CSocketDNSResolverManagerMessageResponse& Other)
	{
		MMessageContext=Other.MMessageContext;
		MOperationSucceeded=Other.MOperationSucceeded;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageResponse& CSocketDNSResolverManagerMessageResponse::operator=(CSocketDNSResolverManagerMessageResponse&& Other)
	{
		MMessageContext=FUNCTION_MOVE(Other.MMessageContext);
		MOperationSucceeded=Other.MOperationSucceeded;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketDNSResolverManagerMessageContext CSocketDNSResolverManagerMessageResponse::GetMessageContext(void) const noexcept
	{
		return(MMessageContext);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketDNSResolverManagerMessageResponse::GetOperationSucceeded(void) const noexcept
	{
		return(MOperationSucceeded);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------