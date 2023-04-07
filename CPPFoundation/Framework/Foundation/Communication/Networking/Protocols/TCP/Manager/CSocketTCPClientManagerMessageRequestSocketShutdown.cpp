//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPClientManagerMessageRequestSocketShutdown.h"
#include "CSocketTCPClientManagerMessageResponseSocketShutdown.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequestSocketShutdown::CSocketTCPClientManagerMessageRequestSocketShutdown(const CSocketID& SocketID, CCSPSocketTCPClientManagerMessageContext MessageContext)
		: CSocketTCPClientManagerMessageRequest(SocketID), MMessageContext(MessageContext)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequestSocketShutdown::CSocketTCPClientManagerMessageRequestSocketShutdown(const CSocketTCPClientManagerMessageRequestSocketShutdown& Other)
		: CSocketTCPClientManagerMessageRequest(Other.MSocketID), MMessageContext(Other.MMessageContext)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequestSocketShutdown::CSocketTCPClientManagerMessageRequestSocketShutdown(CSocketTCPClientManagerMessageRequestSocketShutdown&& Other)
		: CSocketTCPClientManagerMessageRequest(FUNCTION_MOVE(Other.MSocketID)), MMessageContext(FUNCTION_MOVE(Other.MMessageContext))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequestSocketShutdown::~CSocketTCPClientManagerMessageRequestSocketShutdown(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequestSocketShutdown& CSocketTCPClientManagerMessageRequestSocketShutdown::operator=(const CSocketTCPClientManagerMessageRequestSocketShutdown& Other)
	{
		CSocketTCPClientManagerMessageRequest::operator=(Other);

		MMessageContext=Other.MMessageContext;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequestSocketShutdown& CSocketTCPClientManagerMessageRequestSocketShutdown::operator=(CSocketTCPClientManagerMessageRequestSocketShutdown&& Other)
	{
		CSocketTCPClientManagerMessageRequest::operator=(FUNCTION_MOVE(Other));

		MMessageContext=FUNCTION_MOVE(Other.MMessageContext);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketTCPClientManagerMessageRequestSocketShutdown::ToString(void) const
	{
		return(CString::Format("TCP CLIENT MANAGER MESSAGE REQUEST SOCKET SHUTDOWN - SOCKET ID [",MSocketID,"] MESSAGE CONTEXT [",MMessageContext,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketTCPClientManagerMessageResponse CSocketTCPClientManagerMessageRequestSocketShutdown::CreateErrorResponse(void) const
	{
		return(CCSPSocketTCPClientManagerMessageResponse(new CSocketTCPClientManagerMessageResponseSocketShutdown(GetSocketID(),MMessageContext,false)));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketTCPClientManagerMessageContext CSocketTCPClientManagerMessageRequestSocketShutdown::GetMessageContext(void) const noexcept
	{
		return(MMessageContext);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------