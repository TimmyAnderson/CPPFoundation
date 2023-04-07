//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPClientManagerMessageResponseSocketRemove.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketRemove::CSocketTCPClientManagerMessageResponseSocketRemove(const CSocketID& SocketID, CCSPSocketTCPClientManagerMessageContext MessageContext, bool OperationSucceeded)
		: CSocketTCPClientManagerMessageResponse(SocketID), MMessageContext(MessageContext), MOperationSucceeded(OperationSucceeded)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketRemove::CSocketTCPClientManagerMessageResponseSocketRemove(const CSocketTCPClientManagerMessageResponseSocketRemove& Other)
		: CSocketTCPClientManagerMessageResponse(Other.MSocketID), MMessageContext(Other.MMessageContext), MOperationSucceeded(Other.MOperationSucceeded)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketRemove::CSocketTCPClientManagerMessageResponseSocketRemove(CSocketTCPClientManagerMessageResponseSocketRemove&& Other) noexcept
		: CSocketTCPClientManagerMessageResponse(FUNCTION_MOVE(Other.MSocketID)), MMessageContext(FUNCTION_MOVE(Other.MMessageContext)), MOperationSucceeded(Other.MOperationSucceeded)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketRemove::~CSocketTCPClientManagerMessageResponseSocketRemove(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketRemove& CSocketTCPClientManagerMessageResponseSocketRemove::operator=(const CSocketTCPClientManagerMessageResponseSocketRemove& Other)
	{
		CSocketTCPClientManagerMessageResponse::operator=(Other);

		MMessageContext=Other.MMessageContext;
		MOperationSucceeded=Other.MOperationSucceeded;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketRemove& CSocketTCPClientManagerMessageResponseSocketRemove::operator=(CSocketTCPClientManagerMessageResponseSocketRemove&& Other) noexcept
	{
		CSocketTCPClientManagerMessageResponse::operator=(FUNCTION_MOVE(Other));

		MMessageContext=FUNCTION_MOVE(Other.MMessageContext);
		MOperationSucceeded=Other.MOperationSucceeded;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketTCPClientManagerMessageResponseSocketRemove::ToString(void) const
	{
		return(CString::Format("TCP CLIENT MANAGER MESSAGE RESPONSE SOCKET REMOVE - SOCKET ID [",MSocketID,"] MESSAGE CONTEXT [",MMessageContext,"] OPERATION SUCCEEDED [",MOperationSucceeded,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketTCPClientManagerMessageContext CSocketTCPClientManagerMessageResponseSocketRemove::GetMessageContext(void) const noexcept
	{
		return(MMessageContext);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketTCPClientManagerMessageResponseSocketRemove::GetOperationSucceeded(void) const noexcept
	{
		return(MOperationSucceeded);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------