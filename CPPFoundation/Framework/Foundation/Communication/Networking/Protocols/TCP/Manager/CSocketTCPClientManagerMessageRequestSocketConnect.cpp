//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPClientManagerMessageRequestSocketConnect.h"
#include "CSocketTCPClientManagerMessageResponseSocketConnect.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequestSocketConnect::CSocketTCPClientManagerMessageRequestSocketConnect(CCSPSocketTCPClientManagerMessageContext MessageContext, CSPSocketTCPClient Socket, const CSocketTCPAddress& DestinationAddress)
		: CSocketTCPClientManagerMessageRequest(Socket->GetSocketID()), MMessageContext(MessageContext), MSocket(Socket), MDestinationAddress(DestinationAddress)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequestSocketConnect::CSocketTCPClientManagerMessageRequestSocketConnect(const CSocketTCPClientManagerMessageRequestSocketConnect& Other)
		: CSocketTCPClientManagerMessageRequest(Other.MSocketID), MMessageContext(Other.MMessageContext), MSocket(Other.MSocket), MDestinationAddress(Other.MDestinationAddress)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequestSocketConnect::CSocketTCPClientManagerMessageRequestSocketConnect(CSocketTCPClientManagerMessageRequestSocketConnect&& Other)
		: CSocketTCPClientManagerMessageRequest(FUNCTION_MOVE(Other.MSocketID)), MMessageContext(FUNCTION_MOVE(Other.MMessageContext)), MSocket(FUNCTION_MOVE(Other.MSocket)), MDestinationAddress(FUNCTION_MOVE(Other.MDestinationAddress))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequestSocketConnect::~CSocketTCPClientManagerMessageRequestSocketConnect(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequestSocketConnect& CSocketTCPClientManagerMessageRequestSocketConnect::operator=(const CSocketTCPClientManagerMessageRequestSocketConnect& Other)
	{
		CSocketTCPClientManagerMessageRequest::operator=(Other);

		MMessageContext=Other.MMessageContext;
		MSocket=Other.MSocket;
		MDestinationAddress=Other.MDestinationAddress;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequestSocketConnect& CSocketTCPClientManagerMessageRequestSocketConnect::operator=(CSocketTCPClientManagerMessageRequestSocketConnect&& Other)
	{
		CSocketTCPClientManagerMessageRequest::operator=(FUNCTION_MOVE(Other));

		MMessageContext=FUNCTION_MOVE(Other.MMessageContext);
		MSocket=FUNCTION_MOVE(Other.MSocket);
		MDestinationAddress=FUNCTION_MOVE(Other.MDestinationAddress);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketTCPClientManagerMessageRequestSocketConnect::ToString(void) const
	{
		return(CString::Format("TCP CLIENT MANAGER MESSAGE REQUEST SOCKET CONNECT - SOCKET ID [",MSocketID,"] MESSAGE CONTEXT [",MMessageContext,"] SOCKET [",MSocket,"] DESTINATION ADDRESS [",MDestinationAddress,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketTCPClientManagerMessageResponse CSocketTCPClientManagerMessageRequestSocketConnect::CreateErrorResponse(void) const
	{
		return(CCSPSocketTCPClientManagerMessageResponse(new CSocketTCPClientManagerMessageResponseSocketConnect(MMessageContext,false,MSocket,MDestinationAddress)));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketTCPClientManagerMessageContext CSocketTCPClientManagerMessageRequestSocketConnect::GetMessageContext(void) const noexcept
	{
		return(MMessageContext);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSPSocketTCPClient CSocketTCPClientManagerMessageRequestSocketConnect::GetSocket(void) const noexcept
	{
		return(MSocket);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CSocketTCPAddress& CSocketTCPClientManagerMessageRequestSocketConnect::GetDestinationAddress(void) const noexcept
	{
		return(MDestinationAddress);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------