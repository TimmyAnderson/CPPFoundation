//----------------------------------------------------------------------------------------------------------------------
#include "CSocketUDPManagerMessageRequestSocketRemove.h"
#include "CSocketUDPManagerMessageResponseSocketRemove.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageRequestSocketRemove::CSocketUDPManagerMessageRequestSocketRemove(const CSocketID& SocketID, CCSPSocketUDPManagerMessageContext MessageContext)
		: CSocketUDPManagerMessageRequest(SocketID), MMessageContext(MessageContext)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageRequestSocketRemove::CSocketUDPManagerMessageRequestSocketRemove(const CSocketUDPManagerMessageRequestSocketRemove& Other)
		: CSocketUDPManagerMessageRequest(Other.MSocketID), MMessageContext(Other.MMessageContext)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageRequestSocketRemove::CSocketUDPManagerMessageRequestSocketRemove(CSocketUDPManagerMessageRequestSocketRemove&& Other)
		: CSocketUDPManagerMessageRequest(FUNCTION_MOVE(Other.MSocketID)), MMessageContext(FUNCTION_MOVE(Other.MMessageContext))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageRequestSocketRemove::~CSocketUDPManagerMessageRequestSocketRemove(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageRequestSocketRemove& CSocketUDPManagerMessageRequestSocketRemove::operator=(const CSocketUDPManagerMessageRequestSocketRemove& Other)
	{
		CSocketUDPManagerMessageRequest::operator=(Other);

		MMessageContext=Other.MMessageContext;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageRequestSocketRemove& CSocketUDPManagerMessageRequestSocketRemove::operator=(CSocketUDPManagerMessageRequestSocketRemove&& Other)
	{
		CSocketUDPManagerMessageRequest::operator=(FUNCTION_MOVE(Other));

		MMessageContext=FUNCTION_MOVE(Other.MMessageContext);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketUDPManagerMessageRequestSocketRemove::ToString(void) const
	{
		return(CString::Format("UDP MANAGER MESSAGE REQUEST SOCKET REMOVE - SOCKET ID [",MSocketID,"] MESSAGE CONTEXT [",MMessageContext,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketUDPManagerMessageResponse CSocketUDPManagerMessageRequestSocketRemove::CreateErrorResponse(void) const
	{
		return(CCSPSocketUDPManagerMessageResponse(new CSocketUDPManagerMessageResponseSocketRemove(GetSocketID(),MMessageContext,false)));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketUDPManagerMessageContext CSocketUDPManagerMessageRequestSocketRemove::GetMessageContext(void) const noexcept
	{
		return(MMessageContext);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------