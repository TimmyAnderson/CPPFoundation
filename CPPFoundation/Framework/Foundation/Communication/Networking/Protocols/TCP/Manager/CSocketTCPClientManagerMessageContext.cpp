//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPClientManagerMessageContext.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageContext::CSocketTCPClientManagerMessageContext(const CSocketTCPClientManagerMessageID& MessageID)
		: MMessageID(MessageID), MStateMachineID(CStateMachineID::CreateEmptyStateMachineID())
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageContext::CSocketTCPClientManagerMessageContext(CSocketTCPClientManagerMessageID&& MessageID)
		: MMessageID(FUNCTION_MOVE(MessageID)), MStateMachineID(CStateMachineID::CreateEmptyStateMachineID())
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageContext::CSocketTCPClientManagerMessageContext(const CSocketTCPClientManagerMessageID& MessageID, const CStateMachineID& StateMachineID)
		: MMessageID(MessageID), MStateMachineID(StateMachineID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageContext::CSocketTCPClientManagerMessageContext(CSocketTCPClientManagerMessageID&& MessageID, const CStateMachineID& StateMachineID)
		: MMessageID(FUNCTION_MOVE(MessageID)), MStateMachineID(StateMachineID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageContext::CSocketTCPClientManagerMessageContext(const CSocketTCPClientManagerMessageContext& Other)
		: MMessageID(Other.MMessageID), MStateMachineID(Other.MStateMachineID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageContext::CSocketTCPClientManagerMessageContext(CSocketTCPClientManagerMessageContext&& Other)
		: MMessageID(FUNCTION_MOVE(Other.MMessageID)), MStateMachineID(FUNCTION_MOVE(Other.MStateMachineID))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageContext::~CSocketTCPClientManagerMessageContext(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketTCPClientManagerMessageContext::ToString(void) const
	{
		return(CString::Format("MESSAGE ID [",MMessageID,"] STATE MACHINE ID [",MStateMachineID,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageContext& CSocketTCPClientManagerMessageContext::operator=(const CSocketTCPClientManagerMessageContext& Other)
	{
		MMessageID=Other.MMessageID;
		MStateMachineID=Other.MStateMachineID;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageContext& CSocketTCPClientManagerMessageContext::operator=(CSocketTCPClientManagerMessageContext&& Other)
	{
		MMessageID=FUNCTION_MOVE(Other.MMessageID);
		MStateMachineID=FUNCTION_MOVE(Other.MStateMachineID);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CSocketTCPClientManagerMessageID& CSocketTCPClientManagerMessageContext::GetMessageID(void) const noexcept
	{
		return(MMessageID);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CStateMachineID& CSocketTCPClientManagerMessageContext::GetStateMachineID(void) const noexcept
	{
		return(MStateMachineID);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------