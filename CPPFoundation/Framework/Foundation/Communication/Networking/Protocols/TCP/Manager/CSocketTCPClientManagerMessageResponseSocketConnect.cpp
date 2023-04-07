//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPClientManagerMessageResponseSocketConnect.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketConnect::CSocketTCPClientManagerMessageResponseSocketConnect(CCSPSocketTCPClientManagerMessageContext MessageContext, bool OperationSucceeded, CSPSocket Socket, const CSocketTCPAddress& DestinationAddress)
		: CSocketTCPClientManagerMessageResponse(Socket->GetSocketID()), MMessageContext(MessageContext), MOperationSucceeded(OperationSucceeded), MSocket(Socket), MDestinationAddress(DestinationAddress)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketConnect::CSocketTCPClientManagerMessageResponseSocketConnect(const CSocketTCPClientManagerMessageResponseSocketConnect& Other)
		: CSocketTCPClientManagerMessageResponse(Other.MSocketID), MMessageContext(Other.MMessageContext), MOperationSucceeded(Other.MOperationSucceeded), MSocket(Other.MSocket), MDestinationAddress(Other.MDestinationAddress)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketConnect::CSocketTCPClientManagerMessageResponseSocketConnect(CSocketTCPClientManagerMessageResponseSocketConnect&& Other) noexcept
		: CSocketTCPClientManagerMessageResponse(FUNCTION_MOVE(Other.MSocketID)), MMessageContext(FUNCTION_MOVE(Other.MMessageContext)), MOperationSucceeded(Other.MOperationSucceeded), MSocket(FUNCTION_MOVE(Other.MSocket)), MDestinationAddress(FUNCTION_MOVE(Other.MDestinationAddress))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketConnect::~CSocketTCPClientManagerMessageResponseSocketConnect(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketConnect& CSocketTCPClientManagerMessageResponseSocketConnect::operator=(const CSocketTCPClientManagerMessageResponseSocketConnect& Other)
	{
		CSocketTCPClientManagerMessageResponse::operator=(Other);

		MMessageContext=Other.MMessageContext;
		MOperationSucceeded=Other.MOperationSucceeded;
		MSocket=Other.MSocket;
		MDestinationAddress=Other.MDestinationAddress;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketConnect& CSocketTCPClientManagerMessageResponseSocketConnect::operator=(CSocketTCPClientManagerMessageResponseSocketConnect&& Other) noexcept
	{
		CSocketTCPClientManagerMessageResponse::operator=(FUNCTION_MOVE(Other));

		MMessageContext=FUNCTION_MOVE(Other.MMessageContext);
		MOperationSucceeded=Other.MOperationSucceeded;
		MSocket=FUNCTION_MOVE(Other.MSocket);
		MDestinationAddress=FUNCTION_MOVE(Other.MDestinationAddress);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketTCPClientManagerMessageResponseSocketConnect::ToString(void) const
	{
		return(CString::Format("TCP CLIENT MANAGER MESSAGE RESPONSE SOCKET CONNECT - SOCKET ID [",MSocketID,"] MESSAGE CONTEXT [",MMessageContext,"] OPERATION SUCCEEDED [",MOperationSucceeded,"] SOCKET [",MSocket,"] DESTINATION ADDRESS [",MDestinationAddress,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketTCPClientManagerMessageContext CSocketTCPClientManagerMessageResponseSocketConnect::GetMessageContext(void) const noexcept
	{
		return(MMessageContext);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketTCPClientManagerMessageResponseSocketConnect::GetOperationSucceeded(void) const noexcept
	{
		return(MOperationSucceeded);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSPSocket CSocketTCPClientManagerMessageResponseSocketConnect::GetSocket(void) const noexcept
	{
		return(MSocket);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CSocketTCPAddress& CSocketTCPClientManagerMessageResponseSocketConnect::GetDestinationAddress(void) const noexcept
	{
		return(MDestinationAddress);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------