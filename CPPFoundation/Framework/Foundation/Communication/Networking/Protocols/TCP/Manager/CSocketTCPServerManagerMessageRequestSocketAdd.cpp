//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPServerManagerMessageRequestSocketAdd.h"
#include "CSocketTCPServerManagerMessageResponseSocketAdd.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageRequestSocketAdd::CSocketTCPServerManagerMessageRequestSocketAdd(CCSPSocketTCPServerManagerMessageContext MessageContext, CSPSocketTCPServer Socket)
		: CSocketTCPServerManagerMessageRequest(Socket->GetSocketID()), MMessageContext(MessageContext), MSocket(Socket)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageRequestSocketAdd::CSocketTCPServerManagerMessageRequestSocketAdd(const CSocketTCPServerManagerMessageRequestSocketAdd& Other)
		: CSocketTCPServerManagerMessageRequest(Other.MSocketID), MMessageContext(Other.MMessageContext), MSocket(Other.MSocket)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageRequestSocketAdd::CSocketTCPServerManagerMessageRequestSocketAdd(CSocketTCPServerManagerMessageRequestSocketAdd&& Other) noexcept
		: CSocketTCPServerManagerMessageRequest(FUNCTION_MOVE(Other.MSocketID)), MMessageContext(FUNCTION_MOVE(Other.MMessageContext)), MSocket(FUNCTION_MOVE(Other.MSocket))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageRequestSocketAdd::~CSocketTCPServerManagerMessageRequestSocketAdd(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageRequestSocketAdd& CSocketTCPServerManagerMessageRequestSocketAdd::operator=(const CSocketTCPServerManagerMessageRequestSocketAdd& Other)
	{
		CSocketTCPServerManagerMessageRequest::operator=(Other);

		MMessageContext=Other.MMessageContext;
		MSocket=Other.MSocket;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageRequestSocketAdd& CSocketTCPServerManagerMessageRequestSocketAdd::operator=(CSocketTCPServerManagerMessageRequestSocketAdd&& Other) noexcept
	{
		CSocketTCPServerManagerMessageRequest::operator=(FUNCTION_MOVE(Other));

		MMessageContext=FUNCTION_MOVE(Other.MMessageContext);
		MSocket=FUNCTION_MOVE(Other.MSocket);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketTCPServerManagerMessageRequestSocketAdd::ToString(void) const
	{
		return(CString::Format("TCP SERVER MANAGER MESSAGE REQUEST SOCKET ADD - SOCKET ID [",MSocketID,"] MESSAGE CONTEXT [",MMessageContext,"] SOCKET [",MSocket,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketTCPServerManagerMessageResponse CSocketTCPServerManagerMessageRequestSocketAdd::CreateErrorResponse(void) const
	{
		return(CCSPSocketTCPServerManagerMessageResponse(new CSocketTCPServerManagerMessageResponseSocketAdd(MMessageContext,false,MSocket)));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketTCPServerManagerMessageContext CSocketTCPServerManagerMessageRequestSocketAdd::GetMessageContext(void) const noexcept
	{
		return(MMessageContext);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSPSocketTCPServer CSocketTCPServerManagerMessageRequestSocketAdd::GetSocket(void) const noexcept
	{
		return(MSocket);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------