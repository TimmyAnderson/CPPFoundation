//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPServerManagerMessageResponseSocketRemove.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponseSocketRemove::CSocketTCPServerManagerMessageResponseSocketRemove(const CSocketID& SocketID, CCSPSocketTCPServerManagerMessageContext MessageContext, bool OperationSucceeded)
		: CSocketTCPServerManagerMessageResponse(SocketID), MMessageContext(MessageContext), MOperationSucceeded(OperationSucceeded)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponseSocketRemove::CSocketTCPServerManagerMessageResponseSocketRemove(const CSocketTCPServerManagerMessageResponseSocketRemove& Other)
		: CSocketTCPServerManagerMessageResponse(Other.MSocketID), MMessageContext(Other.MMessageContext), MOperationSucceeded(Other.MOperationSucceeded)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponseSocketRemove::CSocketTCPServerManagerMessageResponseSocketRemove(CSocketTCPServerManagerMessageResponseSocketRemove&& Other)
		: CSocketTCPServerManagerMessageResponse(FUNCTION_MOVE(Other.MSocketID)), MMessageContext(FUNCTION_MOVE(Other.MMessageContext)), MOperationSucceeded(Other.MOperationSucceeded)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponseSocketRemove::~CSocketTCPServerManagerMessageResponseSocketRemove(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponseSocketRemove& CSocketTCPServerManagerMessageResponseSocketRemove::operator=(const CSocketTCPServerManagerMessageResponseSocketRemove& Other)
	{
		CSocketTCPServerManagerMessageResponse::operator=(Other);

		MMessageContext=Other.MMessageContext;
		MOperationSucceeded=Other.MOperationSucceeded;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponseSocketRemove& CSocketTCPServerManagerMessageResponseSocketRemove::operator=(CSocketTCPServerManagerMessageResponseSocketRemove&& Other)
	{
		CSocketTCPServerManagerMessageResponse::operator=(FUNCTION_MOVE(Other));

		MMessageContext=FUNCTION_MOVE(Other.MMessageContext);
		MOperationSucceeded=Other.MOperationSucceeded;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketTCPServerManagerMessageResponseSocketRemove::ToString(void) const
	{
		return(CString::Format("TCP SERVER MANAGER MESSAGE RESPONSE SOCKET REMOVE - SOCKET ID [",MSocketID,"] MESSAGE CONTEXT [",MMessageContext,"] OPERATION SUCCEEDED [",MOperationSucceeded,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketTCPServerManagerMessageContext CSocketTCPServerManagerMessageResponseSocketRemove::GetMessageContext(void) const noexcept
	{
		return(MMessageContext);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketTCPServerManagerMessageResponseSocketRemove::GetOperationSucceeded(void) const noexcept
	{
		return(MOperationSucceeded);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------