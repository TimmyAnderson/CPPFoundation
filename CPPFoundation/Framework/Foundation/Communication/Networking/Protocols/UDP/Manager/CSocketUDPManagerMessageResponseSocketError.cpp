//----------------------------------------------------------------------------------------------------------------------
#include "CSocketUDPManagerMessageResponseSocketError.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponseSocketError::CSocketUDPManagerMessageResponseSocketError(const CSocketID& SocketID)
		: CSocketUDPManagerMessageResponse(SocketID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponseSocketError::CSocketUDPManagerMessageResponseSocketError(const CSocketUDPManagerMessageResponseSocketError& Other)
		: CSocketUDPManagerMessageResponse(Other.MSocketID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponseSocketError::CSocketUDPManagerMessageResponseSocketError(CSocketUDPManagerMessageResponseSocketError&& Other) noexcept
		: CSocketUDPManagerMessageResponse(FUNCTION_MOVE(Other.MSocketID))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponseSocketError::~CSocketUDPManagerMessageResponseSocketError(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponseSocketError& CSocketUDPManagerMessageResponseSocketError::operator=(const CSocketUDPManagerMessageResponseSocketError& Other)
	{
		CSocketUDPManagerMessageResponse::operator=(Other);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponseSocketError& CSocketUDPManagerMessageResponseSocketError::operator=(CSocketUDPManagerMessageResponseSocketError&& Other) noexcept
	{
		CSocketUDPManagerMessageResponse::operator=(FUNCTION_MOVE(Other));

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketUDPManagerMessageResponseSocketError::ToString(void) const
	{
		return(CString::Format("UDP MANAGER MESSAGE RESPONSE SOCKET ERROR - SOCKET ID [",MSocketID,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------