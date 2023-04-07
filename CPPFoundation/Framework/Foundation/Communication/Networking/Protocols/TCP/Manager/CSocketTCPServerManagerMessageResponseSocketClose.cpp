//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPServerManagerMessageResponseSocketClose.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponseSocketClose::CSocketTCPServerManagerMessageResponseSocketClose(const CSocketID& SocketID)
		: CSocketTCPServerManagerMessageResponse(SocketID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponseSocketClose::CSocketTCPServerManagerMessageResponseSocketClose(const CSocketTCPServerManagerMessageResponseSocketClose& Other)
		: CSocketTCPServerManagerMessageResponse(Other.MSocketID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponseSocketClose::CSocketTCPServerManagerMessageResponseSocketClose(CSocketTCPServerManagerMessageResponseSocketClose&& Other) noexcept
		: CSocketTCPServerManagerMessageResponse(FUNCTION_MOVE(Other.MSocketID))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponseSocketClose::~CSocketTCPServerManagerMessageResponseSocketClose(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponseSocketClose& CSocketTCPServerManagerMessageResponseSocketClose::operator=(const CSocketTCPServerManagerMessageResponseSocketClose& Other)
	{
		CSocketTCPServerManagerMessageResponse::operator=(Other);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponseSocketClose& CSocketTCPServerManagerMessageResponseSocketClose::operator=(CSocketTCPServerManagerMessageResponseSocketClose&& Other) noexcept
	{
		CSocketTCPServerManagerMessageResponse::operator=(FUNCTION_MOVE(Other));

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketTCPServerManagerMessageResponseSocketClose::ToString(void) const
	{
		return(CString::Format("TCP SERVER MANAGER MESSAGE RESPONSE SOCKET CLOSE - SOCKET ID [",MSocketID,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------