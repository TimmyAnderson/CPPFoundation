//----------------------------------------------------------------------------------------------------------------------
#include "CSocketCANManagerMessageRequestSocketRemove.h"
#include "CSocketCANManagerMessageResponseSocketRemove.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageRequestSocketRemove::CSocketCANManagerMessageRequestSocketRemove(const CSocketID& SocketID, CCSPSocketCANManagerMessageContext MessageContext)
		: CSocketCANManagerMessageRequest(SocketID), MMessageContext(MessageContext)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageRequestSocketRemove::CSocketCANManagerMessageRequestSocketRemove(const CSocketCANManagerMessageRequestSocketRemove& Other)
		: CSocketCANManagerMessageRequest(Other.MSocketID), MMessageContext(Other.MMessageContext)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageRequestSocketRemove::CSocketCANManagerMessageRequestSocketRemove(CSocketCANManagerMessageRequestSocketRemove&& Other) noexcept
		: CSocketCANManagerMessageRequest(FUNCTION_MOVE(Other.MSocketID)), MMessageContext(FUNCTION_MOVE(Other.MMessageContext))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageRequestSocketRemove::~CSocketCANManagerMessageRequestSocketRemove(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageRequestSocketRemove& CSocketCANManagerMessageRequestSocketRemove::operator=(const CSocketCANManagerMessageRequestSocketRemove& Other)
	{
		CSocketCANManagerMessageRequest::operator=(Other);

		MMessageContext=Other.MMessageContext;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageRequestSocketRemove& CSocketCANManagerMessageRequestSocketRemove::operator=(CSocketCANManagerMessageRequestSocketRemove&& Other) noexcept
	{
		CSocketCANManagerMessageRequest::operator=(FUNCTION_MOVE(Other));

		MMessageContext=FUNCTION_MOVE(Other.MMessageContext);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketCANManagerMessageRequestSocketRemove::ToString(void) const
	{
		return(CString::Format("CAN MANAGER MESSAGE REQUEST SOCKET REMOVE - SOCKET ID [",MSocketID,"] MESSAGE CONTEXT [",MMessageContext,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketCANManagerMessageResponse CSocketCANManagerMessageRequestSocketRemove::CreateErrorResponse(void) const
	{
		return(CCSPSocketCANManagerMessageResponse(new CSocketCANManagerMessageResponseSocketRemove(GetSocketID(),MMessageContext,false)));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketCANManagerMessageContext CSocketCANManagerMessageRequestSocketRemove::GetMessageContext(void) const noexcept
	{
		return(MMessageContext);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------