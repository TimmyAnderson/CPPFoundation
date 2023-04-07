//----------------------------------------------------------------------------------------------------------------------
#include "CSocketCANManagerMessageContext.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageContext::CSocketCANManagerMessageContext(const CSocketCANManagerMessageID& MessageID)
		: MMessageID(MessageID), MStateMachineID(CStateMachineID::CreateEmptyStateMachineID())
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageContext::CSocketCANManagerMessageContext(CSocketCANManagerMessageID&& MessageID)
		: MMessageID(FUNCTION_MOVE(MessageID)), MStateMachineID(CStateMachineID::CreateEmptyStateMachineID())
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageContext::CSocketCANManagerMessageContext(const CSocketCANManagerMessageID& MessageID, const CStateMachineID& StateMachineID)
		: MMessageID(MessageID), MStateMachineID(StateMachineID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageContext::CSocketCANManagerMessageContext(CSocketCANManagerMessageID&& MessageID, const CStateMachineID& StateMachineID)
		: MMessageID(FUNCTION_MOVE(MessageID)), MStateMachineID(StateMachineID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageContext::CSocketCANManagerMessageContext(const CSocketCANManagerMessageContext& Other)
		: MMessageID(Other.MMessageID), MStateMachineID(Other.MStateMachineID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageContext::CSocketCANManagerMessageContext(CSocketCANManagerMessageContext&& Other) noexcept
		: MMessageID(FUNCTION_MOVE(Other.MMessageID)), MStateMachineID(FUNCTION_MOVE(Other.MStateMachineID))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageContext::~CSocketCANManagerMessageContext(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketCANManagerMessageContext::ToString(void) const
	{
		return(CString::Format("MESSAGE ID [",MMessageID,"] STATE MACHINE ID [",MStateMachineID,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageContext& CSocketCANManagerMessageContext::operator=(const CSocketCANManagerMessageContext& Other)
	{
		MMessageID=Other.MMessageID;
		MStateMachineID=Other.MStateMachineID;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANManagerMessageContext& CSocketCANManagerMessageContext::operator=(CSocketCANManagerMessageContext&& Other) noexcept
	{
		MMessageID=FUNCTION_MOVE(Other.MMessageID);
		MStateMachineID=FUNCTION_MOVE(Other.MStateMachineID);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CSocketCANManagerMessageID& CSocketCANManagerMessageContext::GetMessageID(void) const noexcept
	{
		return(MMessageID);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CStateMachineID& CSocketCANManagerMessageContext::GetStateMachineID(void) const noexcept
	{
		return(MStateMachineID);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------