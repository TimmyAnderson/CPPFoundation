//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPClientManagerMessageResponseSocketError.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketError::CSocketTCPClientManagerMessageResponseSocketError(const CSocketID& SocketID)
		: CSocketTCPClientManagerMessageResponse(SocketID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketError::CSocketTCPClientManagerMessageResponseSocketError(const CSocketTCPClientManagerMessageResponseSocketError& Other)
		: CSocketTCPClientManagerMessageResponse(Other.MSocketID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketError::CSocketTCPClientManagerMessageResponseSocketError(CSocketTCPClientManagerMessageResponseSocketError&& Other)
		: CSocketTCPClientManagerMessageResponse(FUNCTION_MOVE(Other.MSocketID))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketError::~CSocketTCPClientManagerMessageResponseSocketError(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketError& CSocketTCPClientManagerMessageResponseSocketError::operator=(const CSocketTCPClientManagerMessageResponseSocketError& Other)
	{
		CSocketTCPClientManagerMessageResponse::operator=(Other);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketError& CSocketTCPClientManagerMessageResponseSocketError::operator=(CSocketTCPClientManagerMessageResponseSocketError&& Other)
	{
		CSocketTCPClientManagerMessageResponse::operator=(FUNCTION_MOVE(Other));

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketTCPClientManagerMessageResponseSocketError::ToString(void) const
	{
		return(CString::Format("TCP CLIENT MANAGER MESSAGE RESPONSE SOCKET ERROR - SOCKET ID [",MSocketID,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------