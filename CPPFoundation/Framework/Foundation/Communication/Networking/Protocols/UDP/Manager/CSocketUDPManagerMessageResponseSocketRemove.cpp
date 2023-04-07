//----------------------------------------------------------------------------------------------------------------------
#include "CSocketUDPManagerMessageResponseSocketRemove.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponseSocketRemove::CSocketUDPManagerMessageResponseSocketRemove(const CSocketID& SocketID, CCSPSocketUDPManagerMessageContext MessageContext, bool OperationSucceeded)
		: CSocketUDPManagerMessageResponse(SocketID), MMessageContext(MessageContext), MOperationSucceeded(OperationSucceeded)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponseSocketRemove::CSocketUDPManagerMessageResponseSocketRemove(const CSocketUDPManagerMessageResponseSocketRemove& Other)
		: CSocketUDPManagerMessageResponse(Other.MSocketID), MMessageContext(Other.MMessageContext), MOperationSucceeded(Other.MOperationSucceeded)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponseSocketRemove::CSocketUDPManagerMessageResponseSocketRemove(CSocketUDPManagerMessageResponseSocketRemove&& Other) noexcept
		: CSocketUDPManagerMessageResponse(FUNCTION_MOVE(Other.MSocketID)), MMessageContext(FUNCTION_MOVE(Other.MMessageContext)), MOperationSucceeded(Other.MOperationSucceeded)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponseSocketRemove::~CSocketUDPManagerMessageResponseSocketRemove(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponseSocketRemove& CSocketUDPManagerMessageResponseSocketRemove::operator=(const CSocketUDPManagerMessageResponseSocketRemove& Other)
	{
		CSocketUDPManagerMessageResponse::operator=(Other);

		MMessageContext=Other.MMessageContext;
		MOperationSucceeded=Other.MOperationSucceeded;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageResponseSocketRemove& CSocketUDPManagerMessageResponseSocketRemove::operator=(CSocketUDPManagerMessageResponseSocketRemove&& Other) noexcept
	{
		CSocketUDPManagerMessageResponse::operator=(FUNCTION_MOVE(Other));

		MMessageContext=FUNCTION_MOVE(Other.MMessageContext);
		MOperationSucceeded=Other.MOperationSucceeded;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketUDPManagerMessageResponseSocketRemove::ToString(void) const
	{
		return(CString::Format("UDP MANAGER MESSAGE RESPONSE SOCKET REMOVE - SOCKET ID [",MSocketID,"] MESSAGE CONTEXT [",MMessageContext,"] OPERATION SUCCEEDED [",MOperationSucceeded,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketUDPManagerMessageContext CSocketUDPManagerMessageResponseSocketRemove::GetMessageContext(void) const noexcept
	{
		return(MMessageContext);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketUDPManagerMessageResponseSocketRemove::GetOperationSucceeded(void) const noexcept
	{
		return(MOperationSucceeded);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------