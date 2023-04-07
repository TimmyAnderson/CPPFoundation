//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPClientManagerMessageResponse.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponse::CSocketTCPClientManagerMessageResponse(const CSocketID& SocketID)
		: MSocketID(SocketID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponse::CSocketTCPClientManagerMessageResponse(const CSocketTCPClientManagerMessageResponse& Other)
		: MSocketID(Other.MSocketID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponse::CSocketTCPClientManagerMessageResponse(CSocketTCPClientManagerMessageResponse&& Other) noexcept
		: MSocketID(FUNCTION_MOVE(Other.MSocketID))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponse::~CSocketTCPClientManagerMessageResponse(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponse& CSocketTCPClientManagerMessageResponse::operator=(const CSocketTCPClientManagerMessageResponse& Other)
	{
		MSocketID=Other.MSocketID;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponse& CSocketTCPClientManagerMessageResponse::operator=(CSocketTCPClientManagerMessageResponse&& Other) noexcept
	{
		MSocketID=FUNCTION_MOVE(Other.MSocketID);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CSocketID& CSocketTCPClientManagerMessageResponse::GetSocketID(void) const noexcept
	{
		return(MSocketID);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------