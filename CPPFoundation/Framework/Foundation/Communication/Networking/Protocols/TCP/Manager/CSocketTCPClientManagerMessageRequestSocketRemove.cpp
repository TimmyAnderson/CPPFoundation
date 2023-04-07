//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPClientManagerMessageRequestSocketRemove.h"
#include "CSocketTCPClientManagerMessageResponseSocketRemove.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequestSocketRemove::CSocketTCPClientManagerMessageRequestSocketRemove(const CSocketID& SocketID, CCSPSocketTCPClientManagerMessageContext MessageContext)
		: CSocketTCPClientManagerMessageRequest(SocketID), MMessageContext(MessageContext)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequestSocketRemove::CSocketTCPClientManagerMessageRequestSocketRemove(const CSocketTCPClientManagerMessageRequestSocketRemove& Other)
		: CSocketTCPClientManagerMessageRequest(Other.MSocketID), MMessageContext(Other.MMessageContext)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequestSocketRemove::CSocketTCPClientManagerMessageRequestSocketRemove(CSocketTCPClientManagerMessageRequestSocketRemove&& Other) noexcept
		: CSocketTCPClientManagerMessageRequest(FUNCTION_MOVE(Other.MSocketID)), MMessageContext(FUNCTION_MOVE(Other.MMessageContext))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequestSocketRemove::~CSocketTCPClientManagerMessageRequestSocketRemove(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequestSocketRemove& CSocketTCPClientManagerMessageRequestSocketRemove::operator=(const CSocketTCPClientManagerMessageRequestSocketRemove& Other)
	{
		CSocketTCPClientManagerMessageRequest::operator=(Other);

		MMessageContext=Other.MMessageContext;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequestSocketRemove& CSocketTCPClientManagerMessageRequestSocketRemove::operator=(CSocketTCPClientManagerMessageRequestSocketRemove&& Other) noexcept
	{
		CSocketTCPClientManagerMessageRequest::operator=(FUNCTION_MOVE(Other));

		MMessageContext=FUNCTION_MOVE(Other.MMessageContext);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketTCPClientManagerMessageRequestSocketRemove::ToString(void) const
	{
		return(CString::Format("TCP CLIENT MANAGER MESSAGE REQUEST SOCKET REMOVE - SOCKET ID [",MSocketID,"] MESSAGE CONTEXT [",MMessageContext,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketTCPClientManagerMessageResponse CSocketTCPClientManagerMessageRequestSocketRemove::CreateErrorResponse(void) const
	{
		return(CCSPSocketTCPClientManagerMessageResponse(new CSocketTCPClientManagerMessageResponseSocketRemove(GetSocketID(),MMessageContext,false)));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketTCPClientManagerMessageContext CSocketTCPClientManagerMessageRequestSocketRemove::GetMessageContext(void) const noexcept
	{
		return(MMessageContext);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------