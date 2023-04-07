//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPClientManagerMessageResponseSocketShutdown.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketShutdown::CSocketTCPClientManagerMessageResponseSocketShutdown(const CSocketID& SocketID, CCSPSocketTCPClientManagerMessageContext MessageContext, bool OperationSucceeded)
		: CSocketTCPClientManagerMessageResponse(SocketID), MMessageContext(MessageContext), MOperationSucceeded(OperationSucceeded)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketShutdown::CSocketTCPClientManagerMessageResponseSocketShutdown(const CSocketTCPClientManagerMessageResponseSocketShutdown& Other)
		: CSocketTCPClientManagerMessageResponse(Other.MSocketID), MMessageContext(Other.MMessageContext), MOperationSucceeded(Other.MOperationSucceeded)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketShutdown::CSocketTCPClientManagerMessageResponseSocketShutdown(CSocketTCPClientManagerMessageResponseSocketShutdown&& Other) noexcept
		: CSocketTCPClientManagerMessageResponse(FUNCTION_MOVE(Other.MSocketID)), MMessageContext(FUNCTION_MOVE(Other.MMessageContext)), MOperationSucceeded(Other.MOperationSucceeded)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketShutdown::~CSocketTCPClientManagerMessageResponseSocketShutdown(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketShutdown& CSocketTCPClientManagerMessageResponseSocketShutdown::operator=(const CSocketTCPClientManagerMessageResponseSocketShutdown& Other)
	{
		CSocketTCPClientManagerMessageResponse::operator=(Other);

		MMessageContext=Other.MMessageContext;
		MOperationSucceeded=Other.MOperationSucceeded;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageResponseSocketShutdown& CSocketTCPClientManagerMessageResponseSocketShutdown::operator=(CSocketTCPClientManagerMessageResponseSocketShutdown&& Other) noexcept
	{
		CSocketTCPClientManagerMessageResponse::operator=(FUNCTION_MOVE(Other));

		MMessageContext=FUNCTION_MOVE(Other.MMessageContext);
		MOperationSucceeded=Other.MOperationSucceeded;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketTCPClientManagerMessageResponseSocketShutdown::ToString(void) const
	{
		return(CString::Format("TCP CLIENT MANAGER MESSAGE RESPONSE SOCKET SHUTDOWN - SOCKET ID [",MSocketID,"] MESSAGE CONTEXT [",MMessageContext,"] OPERATION SUCCEEDED [",MOperationSucceeded,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketTCPClientManagerMessageContext CSocketTCPClientManagerMessageResponseSocketShutdown::GetMessageContext(void) const noexcept
	{
		return(MMessageContext);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketTCPClientManagerMessageResponseSocketShutdown::GetOperationSucceeded(void) const noexcept
	{
		return(MOperationSucceeded);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------