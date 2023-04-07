//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPServerManagerMessageResponseSocketAdd.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponseSocketAdd::CSocketTCPServerManagerMessageResponseSocketAdd(CCSPSocketTCPServerManagerMessageContext MessageContext, bool OperationSucceeded, CSPSocketTCPServer Socket)
		: CSocketTCPServerManagerMessageResponse(Socket->GetSocketID()), MMessageContext(MessageContext), MOperationSucceeded(OperationSucceeded), MSocket(Socket)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponseSocketAdd::CSocketTCPServerManagerMessageResponseSocketAdd(const CSocketTCPServerManagerMessageResponseSocketAdd& Other)
		: CSocketTCPServerManagerMessageResponse(Other.MSocketID), MMessageContext(Other.MMessageContext), MOperationSucceeded(Other.MOperationSucceeded), MSocket(Other.MSocket)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponseSocketAdd::CSocketTCPServerManagerMessageResponseSocketAdd(CSocketTCPServerManagerMessageResponseSocketAdd&& Other) noexcept
		: CSocketTCPServerManagerMessageResponse(FUNCTION_MOVE(Other.MSocketID)), MMessageContext(FUNCTION_MOVE(Other.MMessageContext)), MOperationSucceeded(Other.MOperationSucceeded), MSocket(FUNCTION_MOVE(Other.MSocket))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponseSocketAdd::~CSocketTCPServerManagerMessageResponseSocketAdd(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponseSocketAdd& CSocketTCPServerManagerMessageResponseSocketAdd::operator=(const CSocketTCPServerManagerMessageResponseSocketAdd& Other)
	{
		CSocketTCPServerManagerMessageResponse::operator=(Other);

		MMessageContext=Other.MMessageContext;
		MOperationSucceeded=Other.MOperationSucceeded;
		MSocket=Other.MSocket;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageResponseSocketAdd& CSocketTCPServerManagerMessageResponseSocketAdd::operator=(CSocketTCPServerManagerMessageResponseSocketAdd&& Other) noexcept
	{
		CSocketTCPServerManagerMessageResponse::operator=(FUNCTION_MOVE(Other));

		MMessageContext=FUNCTION_MOVE(Other.MMessageContext);
		MOperationSucceeded=Other.MOperationSucceeded;
		MSocket=FUNCTION_MOVE(Other.MSocket);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketTCPServerManagerMessageResponseSocketAdd::ToString(void) const
	{
		return(CString::Format("TCP SERVER MANAGER MESSAGE RESPONSE SOCKET ADD - SOCKET ID [",MSocketID,"] MESSAGE CONTEXT [",MMessageContext,"] OPERATION SUCCEEDED [",MOperationSucceeded,"] SOCKET [",MSocket,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketTCPServerManagerMessageContext CSocketTCPServerManagerMessageResponseSocketAdd::GetMessageContext(void) const noexcept
	{
		return(MMessageContext);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketTCPServerManagerMessageResponseSocketAdd::GetOperationSucceeded(void) const noexcept
	{
		return(MOperationSucceeded);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSPSocketTCPServer CSocketTCPServerManagerMessageResponseSocketAdd::GetSocket(void) const noexcept
	{
		return(MSocket);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------