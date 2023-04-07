//----------------------------------------------------------------------------------------------------------------------
#include "CState.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CState::CState(void)
		: MIsValidState(false), MState(0), MIsFinalState(false), MStateName()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CState::CState(int32 State, bool IsFinalState, const CString& StateName)
		: MIsValidState(true), MState(State), MIsFinalState(IsFinalState), MStateName(StateName)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CState::CState(const CState& Other)
		: MIsValidState(true), MState(Other.MState), MIsFinalState(Other.MIsFinalState), MStateName(Other.MStateName)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CState::CState(CState&& Other) noexcept
		: MIsValidState(true), MState(Other.MState), MIsFinalState(Other.MIsFinalState), MStateName(FUNCTION_MOVE(Other.MStateName))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CState::~CState(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CState& CState::operator=(const CState& Other)
	{
		MIsValidState=Other.MIsValidState;
		MState=Other.MState;
		MIsFinalState=Other.MIsFinalState;
		MStateName=Other.MStateName;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CState& CState::operator=(CState&& Other) noexcept
	{
		MIsValidState=Other.MIsValidState;
		MState=Other.MState;
		MIsFinalState=Other.MIsFinalState;
		MStateName=FUNCTION_MOVE(Other.MStateName);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CState::operator==(const CState& Other) const
	{
		if (MState==Other.MState)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CState::operator!=(const CState& Other) const
	{
		if (MState!=Other.MState)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CState::operator<(const CState& Other) const
	{
		if (MState<Other.MState)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CState::operator>(const CState& Other) const
	{
		if (MState>Other.MState)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CState::operator<=(const CState& Other) const
	{
		if (MState<=Other.MState)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CState::operator>=(const CState& Other) const
	{
		if (MState>=Other.MState)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CState::ToString(void) const
	{
		return(CString::Format(MState," ",MStateName));
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CState::GetState(void) const noexcept
	{
		return(MState);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CState::SetState(int32 State) noexcept
	{
		MState=State;
	}
//----------------------------------------------------------------------------------------------------------------------
	void CState::ResetState(void) noexcept
	{
		MState=0;
		MIsValidState=false;
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CState::IsValidState(void) const noexcept
	{
		return(MIsValidState);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CState::IsFinalState(void) const noexcept
	{
		return(MIsFinalState);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CString& CState::GetStateName(void) const noexcept
	{
		return(MStateName);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CState::IsEqual(const CState& Other) const noexcept
	{
		if (MIsValidState!=Other.MIsValidState)
		{
			return(false);
		}

		if (MState!=Other.MState)
		{
			return(false);
		}

		if (MIsFinalState!=Other.MIsFinalState)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------