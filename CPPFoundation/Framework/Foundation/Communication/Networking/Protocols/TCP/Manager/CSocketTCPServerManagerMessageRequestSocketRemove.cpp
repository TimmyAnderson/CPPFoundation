//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPServerManagerMessageRequestSocketRemove.h"
#include "CSocketTCPServerManagerMessageResponseSocketRemove.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageRequestSocketRemove::CSocketTCPServerManagerMessageRequestSocketRemove(const CSocketID& SocketID, CCSPSocketTCPServerManagerMessageContext MessageContext)
		: CSocketTCPServerManagerMessageRequest(SocketID), MMessageContext(MessageContext)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageRequestSocketRemove::CSocketTCPServerManagerMessageRequestSocketRemove(const CSocketTCPServerManagerMessageRequestSocketRemove& Other)
		: CSocketTCPServerManagerMessageRequest(Other.MSocketID), MMessageContext(Other.MMessageContext)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageRequestSocketRemove::CSocketTCPServerManagerMessageRequestSocketRemove(CSocketTCPServerManagerMessageRequestSocketRemove&& Other)
		: CSocketTCPServerManagerMessageRequest(FUNCTION_MOVE(Other.MSocketID)), MMessageContext(FUNCTION_MOVE(Other.MMessageContext))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageRequestSocketRemove::~CSocketTCPServerManagerMessageRequestSocketRemove(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageRequestSocketRemove& CSocketTCPServerManagerMessageRequestSocketRemove::operator=(const CSocketTCPServerManagerMessageRequestSocketRemove& Other)
	{
		CSocketTCPServerManagerMessageRequest::operator=(Other);

		MMessageContext=Other.MMessageContext;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageRequestSocketRemove& CSocketTCPServerManagerMessageRequestSocketRemove::operator=(CSocketTCPServerManagerMessageRequestSocketRemove&& Other)
	{
		CSocketTCPServerManagerMessageRequest::operator=(FUNCTION_MOVE(Other));

		MMessageContext=FUNCTION_MOVE(Other.MMessageContext);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketTCPServerManagerMessageRequestSocketRemove::ToString(void) const
	{
		return(CString::Format("TCP SERVER MANAGER MESSAGE REQUEST SOCKET REMOVE - SOCKET ID [",MSocketID,"] MESSAGE CONTEXT [",MMessageContext,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketTCPServerManagerMessageResponse CSocketTCPServerManagerMessageRequestSocketRemove::CreateErrorResponse(void) const
	{
		return(CCSPSocketTCPServerManagerMessageResponse(new CSocketTCPServerManagerMessageResponseSocketRemove(GetSocketID(),MMessageContext,false)));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketTCPServerManagerMessageContext CSocketTCPServerManagerMessageRequestSocketRemove::GetMessageContext(void) const noexcept
	{
		return(MMessageContext);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------