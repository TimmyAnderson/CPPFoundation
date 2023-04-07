//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPClientManagerMessageResponseSocketClosed.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketClosed::CSocketTCPClientManagerMessageResponseSocketClosed(const CSocketID& SocketID)
		: CSocketTCPClientManagerMessageResponse(SocketID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketClosed::CSocketTCPClientManagerMessageResponseSocketClosed(const CSocketTCPClientManagerMessageResponseSocketClosed& Other)
		: CSocketTCPClientManagerMessageResponse(Other.MSocketID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketClosed::CSocketTCPClientManagerMessageResponseSocketClosed(CSocketTCPClientManagerMessageResponseSocketClosed&& Other) noexcept
		: CSocketTCPClientManagerMessageResponse(FUNCTION_MOVE(Other.MSocketID))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketClosed::~CSocketTCPClientManagerMessageResponseSocketClosed(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketClosed& CSocketTCPClientManagerMessageResponseSocketClosed::operator=(const CSocketTCPClientManagerMessageResponseSocketClosed& Other)
	{
		CSocketTCPClientManagerMessageResponse::operator=(Other);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketClosed& CSocketTCPClientManagerMessageResponseSocketClosed::operator=(CSocketTCPClientManagerMessageResponseSocketClosed&& Other) noexcept
	{
		CSocketTCPClientManagerMessageResponse::operator=(FUNCTION_MOVE(Other));

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketTCPClientManagerMessageResponseSocketClosed::ToString(void) const
	{
		return(CString::Format("TCP CLIENT MANAGER MESSAGE RESPONSE SOCKET CLOSED - SOCKET ID [",MSocketID,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------