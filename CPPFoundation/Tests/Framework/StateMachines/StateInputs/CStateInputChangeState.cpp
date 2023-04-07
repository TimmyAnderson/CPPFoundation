//----------------------------------------------------------------------------------------------------------------------
#include "CStateInputChangeState.h"
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
	CStateInputChangeState::CStateInputChangeState(const CStateMachineID& StateMachineID, const CState& StateToChange, bool ExecuteImmediately, const CString& Reason)
		: CStateInput(StateMachineID), MStateToChange(StateToChange), MExecuteImmediately(ExecuteImmediately), MReason(Reason)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateInputChangeState::CStateInputChangeState(CStateMachineID&& StateMachineID, CState&& StateToChange, bool ExecuteImmediately, CString&& Reason)
		: CStateInput(FUNCTION_MOVE(StateMachineID)), MStateToChange(FUNCTION_MOVE(StateToChange)), MExecuteImmediately(ExecuteImmediately), MReason(FUNCTION_MOVE(Reason))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateInputChangeState::CStateInputChangeState(const CStateInputChangeState& Other)
		: CStateInput(Other), MStateToChange(Other.MStateToChange), MExecuteImmediately(Other.MExecuteImmediately), MReason(Other.MReason)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateInputChangeState::CStateInputChangeState(CStateInputChangeState&& Other) noexcept
		: CStateInput(FUNCTION_MOVE(Other)), MStateToChange(FUNCTION_MOVE(Other.MStateToChange)), MExecuteImmediately(Other.MExecuteImmediately), MReason(FUNCTION_MOVE(Other.MReason))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateInputChangeState::~CStateInputChangeState(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CStateInputChangeState& CStateInputChangeState::operator=(const CStateInputChangeState& Other)
	{
		CStateInput::operator=(Other);

		MStateToChange=Other.MStateToChange;
		MExecuteImmediately=Other.MExecuteImmediately;
		MReason=Other.MReason;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateInputChangeState& CStateInputChangeState::operator=(CStateInputChangeState&& Other) noexcept
	{
		CStateInput::operator=(FUNCTION_MOVE(Other));

		MStateToChange=FUNCTION_MOVE(Other.MStateToChange);
		MExecuteImmediately=Other.MExecuteImmediately;
		MReason=FUNCTION_MOVE(Other.MReason);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CState& CStateInputChangeState::GetStateToChange(void) const noexcept
	{
		return(MStateToChange);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateInputChangeState::GetExecuteImmediately(void) const noexcept
	{
		return(MExecuteImmediately);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CString& CStateInputChangeState::GetReason(void) const noexcept
	{
		return(MReason);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------