//----------------------------------------------------------------------------------------------------------------------
#include "CSocketCANManagerMessageResponseSocketRemove.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketRemove::CSocketCANManagerMessageResponseSocketRemove(const CSocketID& SocketID, CCSPSocketCANManagerMessageContext MessageContext, bool OperationSucceeded)
		: CSocketCANManagerMessageResponse(SocketID), MMessageContext(MessageContext), MOperationSucceeded(OperationSucceeded)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketRemove::CSocketCANManagerMessageResponseSocketRemove(const CSocketCANManagerMessageResponseSocketRemove& Other)
		: CSocketCANManagerMessageResponse(Other.MSocketID), MMessageContext(Other.MMessageContext), MOperationSucceeded(Other.MOperationSucceeded)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketRemove::CSocketCANManagerMessageResponseSocketRemove(CSocketCANManagerMessageResponseSocketRemove&& Other) noexcept
		: CSocketCANManagerMessageResponse(FUNCTION_MOVE(Other.MSocketID)), MMessageContext(FUNCTION_MOVE(Other.MMessageContext)), MOperationSucceeded(Other.MOperationSucceeded)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketRemove::~CSocketCANManagerMessageResponseSocketRemove(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketRemove& CSocketCANManagerMessageResponseSocketRemove::operator=(const CSocketCANManagerMessageResponseSocketRemove& Other)
	{
		CSocketCANManagerMessageResponse::operator=(Other);

		MMessageContext=Other.MMessageContext;
		MOperationSucceeded=Other.MOperationSucceeded;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketRemove& CSocketCANManagerMessageResponseSocketRemove::operator=(CSocketCANManagerMessageResponseSocketRemove&& Other) noexcept
	{
		CSocketCANManagerMessageResponse::operator=(FUNCTION_MOVE(Other));

		MMessageContext=FUNCTION_MOVE(Other.MMessageContext);
		MOperationSucceeded=Other.MOperationSucceeded;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketCANManagerMessageResponseSocketRemove::ToString(void) const
	{
		return(CString::Format("CAN MANAGER MESSAGE RESPONSE SOCKET REMOVE - SOCKET ID [",MSocketID,"] MESSAGE CONTEXT [",MMessageContext,"] OPERATION SUCCEEDED [",MOperationSucceeded,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketCANManagerMessageContext CSocketCANManagerMessageResponseSocketRemove::GetMessageContext(void) const noexcept
	{
		return(MMessageContext);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketCANManagerMessageResponseSocketRemove::GetOperationSucceeded(void) const noexcept
	{
		return(MOperationSucceeded);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------