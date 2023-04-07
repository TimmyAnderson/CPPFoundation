//----------------------------------------------------------------------------------------------------------------------
#include "CSocketUDPManagerMessageContext.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageContext::CSocketUDPManagerMessageContext(const CSocketUDPManagerMessageID& MessageID)
		: MMessageID(MessageID), MStateMachineID(CStateMachineID::CreateEmptyStateMachineID())
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageContext::CSocketUDPManagerMessageContext(CSocketUDPManagerMessageID&& MessageID)
		: MMessageID(FUNCTION_MOVE(MessageID)), MStateMachineID(CStateMachineID::CreateEmptyStateMachineID())
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageContext::CSocketUDPManagerMessageContext(const CSocketUDPManagerMessageID& MessageID, const CStateMachineID& StateMachineID)
		: MMessageID(MessageID), MStateMachineID(StateMachineID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageContext::CSocketUDPManagerMessageContext(CSocketUDPManagerMessageID&& MessageID, const CStateMachineID& StateMachineID)
		: MMessageID(FUNCTION_MOVE(MessageID)), MStateMachineID(StateMachineID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageContext::CSocketUDPManagerMessageContext(const CSocketUDPManagerMessageContext& Other)
		: MMessageID(Other.MMessageID), MStateMachineID(Other.MStateMachineID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageContext::CSocketUDPManagerMessageContext(CSocketUDPManagerMessageContext&& Other) noexcept
		: MMessageID(FUNCTION_MOVE(Other.MMessageID)), MStateMachineID(FUNCTION_MOVE(Other.MStateMachineID))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageContext::~CSocketUDPManagerMessageContext(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketUDPManagerMessageContext::ToString(void) const
	{
		return(CString::Format("MESSAGE ID [",MMessageID,"] STATE MACHINE ID [",MStateMachineID,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageContext& CSocketUDPManagerMessageContext::operator=(const CSocketUDPManagerMessageContext& Other)
	{
		MMessageID=Other.MMessageID;
		MStateMachineID=Other.MStateMachineID;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPManagerMessageContext& CSocketUDPManagerMessageContext::operator=(CSocketUDPManagerMessageContext&& Other) noexcept
	{
		MMessageID=FUNCTION_MOVE(Other.MMessageID);
		MStateMachineID=FUNCTION_MOVE(Other.MStateMachineID);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CSocketUDPManagerMessageID& CSocketUDPManagerMessageContext::GetMessageID(void) const noexcept
	{
		return(MMessageID);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CStateMachineID& CSocketUDPManagerMessageContext::GetStateMachineID(void) const noexcept
	{
		return(MStateMachineID);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------