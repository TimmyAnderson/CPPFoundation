//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPClientManagerMessageRequestSocketAdd.h"
#include "CSocketTCPClientManagerMessageResponseSocketAdd.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequestSocketAdd::CSocketTCPClientManagerMessageRequestSocketAdd(CCSPSocketTCPClientManagerMessageContext MessageContext, CSPSocketTCPClient Socket)
		: CSocketTCPClientManagerMessageRequest(Socket->GetSocketID()), MMessageContext(MessageContext), MSocket(Socket)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequestSocketAdd::CSocketTCPClientManagerMessageRequestSocketAdd(const CSocketTCPClientManagerMessageRequestSocketAdd& Other)
		: CSocketTCPClientManagerMessageRequest(Other.MSocketID), MMessageContext(Other.MMessageContext), MSocket(Other.MSocket)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequestSocketAdd::CSocketTCPClientManagerMessageRequestSocketAdd(CSocketTCPClientManagerMessageRequestSocketAdd&& Other) noexcept
		: CSocketTCPClientManagerMessageRequest(FUNCTION_MOVE(Other.MSocketID)), MMessageContext(FUNCTION_MOVE(Other.MMessageContext)), MSocket(FUNCTION_MOVE(Other.MSocket))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequestSocketAdd::~CSocketTCPClientManagerMessageRequestSocketAdd(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequestSocketAdd& CSocketTCPClientManagerMessageRequestSocketAdd::operator=(const CSocketTCPClientManagerMessageRequestSocketAdd& Other)
	{
		CSocketTCPClientManagerMessageRequest::operator=(Other);

		MMessageContext=Other.MMessageContext;
		MSocket=Other.MSocket;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageRequestSocketAdd& CSocketTCPClientManagerMessageRequestSocketAdd::operator=(CSocketTCPClientManagerMessageRequestSocketAdd&& Other) noexcept
	{
		CSocketTCPClientManagerMessageRequest::operator=(FUNCTION_MOVE(Other));

		MMessageContext=FUNCTION_MOVE(Other.MMessageContext);
		MSocket=FUNCTION_MOVE(Other.MSocket);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketTCPClientManagerMessageRequestSocketAdd::ToString(void) const
	{
		return(CString::Format("TCP CLIENT MANAGER MESSAGE REQUEST SOCKET ADD - SOCKET ID [",MSocketID,"] MESSAGE CONTEXT [",MMessageContext,"] SOCKET [",MSocket,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketTCPClientManagerMessageResponse CSocketTCPClientManagerMessageRequestSocketAdd::CreateErrorResponse(void) const
	{
		return(CCSPSocketTCPClientManagerMessageResponse(new CSocketTCPClientManagerMessageResponseSocketAdd(MMessageContext,false,MSocket)));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketTCPClientManagerMessageContext CSocketTCPClientManagerMessageRequestSocketAdd::GetMessageContext(void) const noexcept
	{
		return(MMessageContext);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSPSocketTCPClient CSocketTCPClientManagerMessageRequestSocketAdd::GetSocket(void) const noexcept
	{
		return(MSocket);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------