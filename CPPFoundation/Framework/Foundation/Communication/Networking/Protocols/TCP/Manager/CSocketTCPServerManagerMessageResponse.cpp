//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPServerManagerMessageResponse.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponse::CSocketTCPServerManagerMessageResponse(const CSocketID& SocketID)
		: MSocketID(SocketID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponse::CSocketTCPServerManagerMessageResponse(const CSocketTCPServerManagerMessageResponse& Other)
		: MSocketID(Other.MSocketID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponse::CSocketTCPServerManagerMessageResponse(CSocketTCPServerManagerMessageResponse&& Other) noexcept
		: MSocketID(FUNCTION_MOVE(Other.MSocketID))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponse::~CSocketTCPServerManagerMessageResponse(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponse& CSocketTCPServerManagerMessageResponse::operator=(const CSocketTCPServerManagerMessageResponse& Other)
	{
		MSocketID=Other.MSocketID;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponse& CSocketTCPServerManagerMessageResponse::operator=(CSocketTCPServerManagerMessageResponse&& Other) noexcept
	{
		MSocketID=FUNCTION_MOVE(Other.MSocketID);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CSocketID& CSocketTCPServerManagerMessageResponse::GetSocketID(void) const noexcept
	{
		return(MSocketID);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------