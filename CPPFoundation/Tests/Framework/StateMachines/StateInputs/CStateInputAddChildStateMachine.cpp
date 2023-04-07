//----------------------------------------------------------------------------------------------------------------------
#include "CStateInputAddChildStateMachine.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace CPPFoundation::Foundation;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CStateInputAddChildStateMachine::CStateInputAddChildStateMachine(const CStateMachineID& ParentStateMachineID, CSPStateMachine StateMachineToAdd)
		: MParentStateMachineID(ParentStateMachineID), MStateMachineToAdd(StateMachineToAdd)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateInputAddChildStateMachine::CStateInputAddChildStateMachine(const CStateMachineID& StateMachineID, const CStateMachineID& ParentStateMachineID, CSPStateMachine StateMachineToAdd)
		: CStateInput(StateMachineID), MParentStateMachineID(ParentStateMachineID), MStateMachineToAdd(StateMachineToAdd)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateInputAddChildStateMachine::CStateInputAddChildStateMachine(CStateMachineID&& StateMachineID, CStateMachineID&& ParentStateMachineID, CSPStateMachine StateMachineToAdd)
		: CStateInput(FUNCTION_MOVE(StateMachineID)), MParentStateMachineID(ParentStateMachineID), MStateMachineToAdd(FUNCTION_MOVE(StateMachineToAdd))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateInputAddChildStateMachine::CStateInputAddChildStateMachine(const CStateInputAddChildStateMachine& Other)
		: CStateInput(Other), MParentStateMachineID(Other.MParentStateMachineID), MStateMachineToAdd(Other.MStateMachineToAdd)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateInputAddChildStateMachine::CStateInputAddChildStateMachine(CStateInputAddChildStateMachine&& Other) noexcept
		: CStateInput(FUNCTION_MOVE(Other)), MParentStateMachineID(FUNCTION_MOVE(Other.MParentStateMachineID)), MStateMachineToAdd(FUNCTION_MOVE(Other.MStateMachineToAdd))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateInputAddChildStateMachine::~CStateInputAddChildStateMachine(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CStateInputAddChildStateMachine& CStateInputAddChildStateMachine::operator=(const CStateInputAddChildStateMachine& Other)
	{
		CStateInput::operator=(Other);

		MParentStateMachineID=Other.MParentStateMachineID;
		MStateMachineToAdd=Other.MStateMachineToAdd;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateInputAddChildStateMachine& CStateInputAddChildStateMachine::operator=(CStateInputAddChildStateMachine&& Other) noexcept
	{
		CStateInput::operator=(FUNCTION_MOVE(Other));

		MParentStateMachineID=FUNCTION_MOVE(Other.MParentStateMachineID);
		MStateMachineToAdd=FUNCTION_MOVE(Other.MStateMachineToAdd);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CStateMachineID& CStateInputAddChildStateMachine::GetParentStateMachineID(void) const noexcept
	{
		return(MParentStateMachineID);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSPStateMachine CStateInputAddChildStateMachine::GetStateMachineToAdd(void) const noexcept
	{
		return(MStateMachineToAdd);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------