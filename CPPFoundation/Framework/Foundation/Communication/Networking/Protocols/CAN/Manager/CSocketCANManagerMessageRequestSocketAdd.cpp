//----------------------------------------------------------------------------------------------------------------------
#include "CSocketCANManagerMessageRequestSocketAdd.h"
#include "CSocketCANManagerMessageResponseSocketAdd.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageRequestSocketAdd::CSocketCANManagerMessageRequestSocketAdd(CCSPSocketCANManagerMessageContext MessageContext, CSPSocketCAN Socket)
		: CSocketCANManagerMessageRequest(Socket->GetSocketID()), MMessageContext(MessageContext), MSocket(Socket)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageRequestSocketAdd::CSocketCANManagerMessageRequestSocketAdd(const CSocketCANManagerMessageRequestSocketAdd& Other)
		: CSocketCANManagerMessageRequest(Other.MSocketID), MMessageContext(Other.MMessageContext), MSocket(Other.MSocket)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageRequestSocketAdd::CSocketCANManagerMessageRequestSocketAdd(CSocketCANManagerMessageRequestSocketAdd&& Other)
		: CSocketCANManagerMessageRequest(FUNCTION_MOVE(Other.MSocketID)), MMessageContext(FUNCTION_MOVE(Other.MMessageContext)), MSocket(FUNCTION_MOVE(Other.MSocket))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageRequestSocketAdd::~CSocketCANManagerMessageRequestSocketAdd(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageRequestSocketAdd& CSocketCANManagerMessageRequestSocketAdd::operator=(const CSocketCANManagerMessageRequestSocketAdd& Other)
	{
		CSocketCANManagerMessageRequest::operator=(Other);

		MMessageContext=Other.MMessageContext;
		MSocket=Other.MSocket;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageRequestSocketAdd& CSocketCANManagerMessageRequestSocketAdd::operator=(CSocketCANManagerMessageRequestSocketAdd&& Other)
	{
		CSocketCANManagerMessageRequest::operator=(FUNCTION_MOVE(Other));

		MMessageContext=FUNCTION_MOVE(Other.MMessageContext);
		MSocket=FUNCTION_MOVE(Other.MSocket);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketCANManagerMessageRequestSocketAdd::ToString(void) const
	{
		return(CString::Format("CAN MANAGER MESSAGE REQUEST SOCKET ADD - SOCKET ID [",MSocketID,"] MESSAGE CONTEXT [",MMessageContext,"] SOCKET [",MSocket,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketCANManagerMessageResponse CSocketCANManagerMessageRequestSocketAdd::CreateErrorResponse(void) const
	{
		return(CCSPSocketCANManagerMessageResponse(new CSocketCANManagerMessageResponseSocketAdd(MMessageContext,false,MSocket)));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketCANManagerMessageContext CSocketCANManagerMessageRequestSocketAdd::GetMessageContext(void) const noexcept
	{
		return(MMessageContext);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSPSocketCAN CSocketCANManagerMessageRequestSocketAdd::GetSocket(void) const noexcept
	{
		return(MSocket);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------