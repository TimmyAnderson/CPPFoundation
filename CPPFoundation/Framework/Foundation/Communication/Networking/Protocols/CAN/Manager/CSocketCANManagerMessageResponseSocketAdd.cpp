//----------------------------------------------------------------------------------------------------------------------
#include "CSocketCANManagerMessageResponseSocketAdd.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketAdd::CSocketCANManagerMessageResponseSocketAdd(CCSPSocketCANManagerMessageContext MessageContext, bool OperationSucceeded, CSPSocket Socket)
		: CSocketCANManagerMessageResponse(Socket->GetSocketID()), MMessageContext(MessageContext), MOperationSucceeded(OperationSucceeded), MSocket(Socket)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketAdd::CSocketCANManagerMessageResponseSocketAdd(const CSocketCANManagerMessageResponseSocketAdd& Other)
		: CSocketCANManagerMessageResponse(Other.MSocketID), MMessageContext(Other.MMessageContext), MOperationSucceeded(Other.MOperationSucceeded), MSocket(Other.MSocket)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketAdd::CSocketCANManagerMessageResponseSocketAdd(CSocketCANManagerMessageResponseSocketAdd&& Other) noexcept
		: CSocketCANManagerMessageResponse(FUNCTION_MOVE(Other.MSocketID)), MMessageContext(FUNCTION_MOVE(Other.MMessageContext)), MOperationSucceeded(Other.MOperationSucceeded), MSocket(FUNCTION_MOVE(Other.MSocket))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketAdd::~CSocketCANManagerMessageResponseSocketAdd(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketAdd& CSocketCANManagerMessageResponseSocketAdd::operator=(const CSocketCANManagerMessageResponseSocketAdd& Other)
	{
		CSocketCANManagerMessageResponse::operator=(Other);

		MMessageContext=Other.MMessageContext;
		MOperationSucceeded=Other.MOperationSucceeded;
		MSocket=Other.MSocket;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageResponseSocketAdd& CSocketCANManagerMessageResponseSocketAdd::operator=(CSocketCANManagerMessageResponseSocketAdd&& Other) noexcept
	{
		CSocketCANManagerMessageResponse::operator=(FUNCTION_MOVE(Other));

		MMessageContext=FUNCTION_MOVE(Other.MMessageContext);
		MOperationSucceeded=Other.MOperationSucceeded;
		MSocket=FUNCTION_MOVE(Other.MSocket);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketCANManagerMessageResponseSocketAdd::ToString(void) const
	{
		return(CString::Format("CAN MANAGER MESSAGE RESPONSE SOCKET ADD - SOCKET ID [",MSocketID,"] MESSAGE CONTEXT [",MMessageContext,"] OPERATION SUCCEEDED [",MOperationSucceeded,"] SOCKET [",MSocket,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketCANManagerMessageContext CSocketCANManagerMessageResponseSocketAdd::GetMessageContext(void) const noexcept
	{
		return(MMessageContext);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketCANManagerMessageResponseSocketAdd::GetOperationSucceeded(void) const noexcept
	{
		return(MOperationSucceeded);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSPSocket CSocketCANManagerMessageResponseSocketAdd::GetSocket(void) const noexcept
	{
		return(MSocket);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------