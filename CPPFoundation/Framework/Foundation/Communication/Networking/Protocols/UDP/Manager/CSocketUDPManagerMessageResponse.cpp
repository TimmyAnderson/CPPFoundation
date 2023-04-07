//----------------------------------------------------------------------------------------------------------------------
#include "CSocketUDPManagerMessageResponse.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponse::CSocketUDPManagerMessageResponse(const CSocketID& SocketID)
		: MSocketID(SocketID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponse::CSocketUDPManagerMessageResponse(const CSocketUDPManagerMessageResponse& Other)
		: MSocketID(Other.MSocketID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponse::CSocketUDPManagerMessageResponse(CSocketUDPManagerMessageResponse&& Other) noexcept
		: MSocketID(FUNCTION_MOVE(Other.MSocketID))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponse::~CSocketUDPManagerMessageResponse(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponse& CSocketUDPManagerMessageResponse::operator=(const CSocketUDPManagerMessageResponse& Other)
	{
		MSocketID=Other.MSocketID;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponse& CSocketUDPManagerMessageResponse::operator=(CSocketUDPManagerMessageResponse&& Other) noexcept
	{
		MSocketID=FUNCTION_MOVE(Other.MSocketID);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CSocketID& CSocketUDPManagerMessageResponse::GetSocketID(void) const noexcept
	{
		return(MSocketID);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------