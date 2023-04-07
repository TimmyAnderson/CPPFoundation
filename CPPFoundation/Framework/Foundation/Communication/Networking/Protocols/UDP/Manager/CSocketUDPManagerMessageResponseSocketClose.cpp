//----------------------------------------------------------------------------------------------------------------------
#include "CSocketUDPManagerMessageResponseSocketClose.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponseSocketClose::CSocketUDPManagerMessageResponseSocketClose(const CSocketID& SocketID)
		: CSocketUDPManagerMessageResponse(SocketID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponseSocketClose::CSocketUDPManagerMessageResponseSocketClose(const CSocketUDPManagerMessageResponseSocketClose& Other)
		: CSocketUDPManagerMessageResponse(Other.MSocketID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponseSocketClose::CSocketUDPManagerMessageResponseSocketClose(CSocketUDPManagerMessageResponseSocketClose&& Other)
		: CSocketUDPManagerMessageResponse(FUNCTION_MOVE(Other.MSocketID))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponseSocketClose::~CSocketUDPManagerMessageResponseSocketClose(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponseSocketClose& CSocketUDPManagerMessageResponseSocketClose::operator=(const CSocketUDPManagerMessageResponseSocketClose& Other)
	{
		CSocketUDPManagerMessageResponse::operator=(Other);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponseSocketClose& CSocketUDPManagerMessageResponseSocketClose::operator=(CSocketUDPManagerMessageResponseSocketClose&& Other)
	{
		CSocketUDPManagerMessageResponse::operator=(FUNCTION_MOVE(Other));

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketUDPManagerMessageResponseSocketClose::ToString(void) const
	{
		return(CString::Format("UDP MANAGER MESSAGE RESPONSE SOCKET CLOSE - SOCKET ID [",MSocketID,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------