//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPClientManagerMessageRequest.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequest::CSocketTCPClientManagerMessageRequest(const CSocketID& SocketID)
		: MSocketID(SocketID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequest::CSocketTCPClientManagerMessageRequest(const CSocketTCPClientManagerMessageRequest& Other)
		: MSocketID(Other.MSocketID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequest::CSocketTCPClientManagerMessageRequest(CSocketTCPClientManagerMessageRequest&& Other) noexcept
		: MSocketID(FUNCTION_MOVE(Other.MSocketID))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequest::~CSocketTCPClientManagerMessageRequest(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequest& CSocketTCPClientManagerMessageRequest::operator=(const CSocketTCPClientManagerMessageRequest& Other)
	{
		MSocketID=Other.MSocketID;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequest& CSocketTCPClientManagerMessageRequest::operator=(CSocketTCPClientManagerMessageRequest&& Other) noexcept
	{
		MSocketID=FUNCTION_MOVE(Other.MSocketID);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CSocketID& CSocketTCPClientManagerMessageRequest::GetSocketID(void) const noexcept
	{
		return(MSocketID);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------