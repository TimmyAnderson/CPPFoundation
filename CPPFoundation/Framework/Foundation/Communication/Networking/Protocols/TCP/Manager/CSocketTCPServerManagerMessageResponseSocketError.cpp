//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPServerManagerMessageResponseSocketError.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponseSocketError::CSocketTCPServerManagerMessageResponseSocketError(const CSocketID& SocketID)
		: CSocketTCPServerManagerMessageResponse(SocketID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponseSocketError::CSocketTCPServerManagerMessageResponseSocketError(const CSocketTCPServerManagerMessageResponseSocketError& Other)
		: CSocketTCPServerManagerMessageResponse(Other.MSocketID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponseSocketError::CSocketTCPServerManagerMessageResponseSocketError(CSocketTCPServerManagerMessageResponseSocketError&& Other) noexcept
		: CSocketTCPServerManagerMessageResponse(FUNCTION_MOVE(Other.MSocketID))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponseSocketError::~CSocketTCPServerManagerMessageResponseSocketError(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponseSocketError& CSocketTCPServerManagerMessageResponseSocketError::operator=(const CSocketTCPServerManagerMessageResponseSocketError& Other)
	{
		CSocketTCPServerManagerMessageResponse::operator=(Other);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponseSocketError& CSocketTCPServerManagerMessageResponseSocketError::operator=(CSocketTCPServerManagerMessageResponseSocketError&& Other) noexcept
	{
		CSocketTCPServerManagerMessageResponse::operator=(FUNCTION_MOVE(Other));

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketTCPServerManagerMessageResponseSocketError::ToString(void) const
	{
		return(CString::Format("TCP SERVER MANAGER MESSAGE RESPONSE SOCKET ERROR - SOCKET ID [",MSocketID,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------