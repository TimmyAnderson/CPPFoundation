//----------------------------------------------------------------------------------------------------------------------
#include "CSocketUDPManagerMessageRequestSocketAdd.h"
#include "CSocketUDPManagerMessageResponseSocketAdd.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageRequestSocketAdd::CSocketUDPManagerMessageRequestSocketAdd(CCSPSocketUDPManagerMessageContext MessageContext, CSPSocketUDP Socket)
		: CSocketUDPManagerMessageRequest(Socket->GetSocketID()), MMessageContext(MessageContext), MSocket(Socket)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageRequestSocketAdd::CSocketUDPManagerMessageRequestSocketAdd(const CSocketUDPManagerMessageRequestSocketAdd& Other)
		: CSocketUDPManagerMessageRequest(Other.MSocketID), MMessageContext(Other.MMessageContext), MSocket(Other.MSocket)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageRequestSocketAdd::CSocketUDPManagerMessageRequestSocketAdd(CSocketUDPManagerMessageRequestSocketAdd&& Other)
		: CSocketUDPManagerMessageRequest(FUNCTION_MOVE(Other.MSocketID)), MMessageContext(FUNCTION_MOVE(Other.MMessageContext)), MSocket(FUNCTION_MOVE(Other.MSocket))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageRequestSocketAdd::~CSocketUDPManagerMessageRequestSocketAdd(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageRequestSocketAdd& CSocketUDPManagerMessageRequestSocketAdd::operator=(const CSocketUDPManagerMessageRequestSocketAdd& Other)
	{
		CSocketUDPManagerMessageRequest::operator=(Other);

		MMessageContext=Other.MMessageContext;
		MSocket=Other.MSocket;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageRequestSocketAdd& CSocketUDPManagerMessageRequestSocketAdd::operator=(CSocketUDPManagerMessageRequestSocketAdd&& Other)
	{
		CSocketUDPManagerMessageRequest::operator=(FUNCTION_MOVE(Other));

		MMessageContext=FUNCTION_MOVE(Other.MMessageContext);
		MSocket=FUNCTION_MOVE(Other.MSocket);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketUDPManagerMessageRequestSocketAdd::ToString(void) const
	{
		return(CString::Format("UDP MANAGER MESSAGE REQUEST SOCKET ADD - SOCKET ID [",MSocketID,"] MESSAGE CONTEXT [",MMessageContext,"] SOCKET [",MSocket,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketUDPManagerMessageResponse CSocketUDPManagerMessageRequestSocketAdd::CreateErrorResponse(void) const
	{
		return(CCSPSocketUDPManagerMessageResponse(new CSocketUDPManagerMessageResponseSocketAdd(MMessageContext,false,MSocket)));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketUDPManagerMessageContext CSocketUDPManagerMessageRequestSocketAdd::GetMessageContext(void) const noexcept
	{
		return(MMessageContext);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSPSocketUDP CSocketUDPManagerMessageRequestSocketAdd::GetSocket(void) const noexcept
	{
		return(MSocket);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------