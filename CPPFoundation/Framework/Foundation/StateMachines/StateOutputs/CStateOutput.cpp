//----------------------------------------------------------------------------------------------------------------------
#include "CStateOutput.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CStateOutput::CStateOutput(void)
		: MStateMachineID(CID::CreateEmptyIDAsString())
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateOutput::CStateOutput(const CStateMachineID& StateMachineID)
		: MStateMachineID(StateMachineID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateOutput::CStateOutput(CStateMachineID&& StateMachineID) noexcept
		: MStateMachineID(FUNCTION_MOVE(StateMachineID))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateOutput::CStateOutput(const CStateOutput& Other)
		: MStateMachineID(Other.MStateMachineID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateOutput::CStateOutput(CStateOutput&& Other) noexcept
		: MStateMachineID(FUNCTION_MOVE(Other.MStateMachineID))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateOutput::~CStateOutput(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CStateOutput& CStateOutput::operator=(const CStateOutput& Other)
	{
		MStateMachineID=Other.MStateMachineID;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateOutput& CStateOutput::operator=(CStateOutput&& Other) noexcept
	{
		MStateMachineID=FUNCTION_MOVE(Other.MStateMachineID);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CStateMachineID& CStateOutput::GetStateMachineID(void) const noexcept
	{
		return(MStateMachineID);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------