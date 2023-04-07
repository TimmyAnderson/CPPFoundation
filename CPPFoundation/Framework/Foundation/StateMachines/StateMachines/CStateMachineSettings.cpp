//----------------------------------------------------------------------------------------------------------------------
#include "CStateMachineSettings.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CStateMachineSettings::CStateMachineSettings(const CStateMachineID& StateMachineID, const CPriority& StateMachinePriority, const CTimeout& StateMachineExpirationTimeout)
		: MStateMachineID(StateMachineID), MStateMachinePriority(StateMachinePriority), MStateMachineExpirationTimeout(StateMachineExpirationTimeout)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateMachineSettings::CStateMachineSettings(CStateMachineID&& StateMachineID, const CPriority& StateMachinePriority, const CTimeout& StateMachineExpirationTimeout)
		: MStateMachineID(FUNCTION_MOVE(StateMachineID)), MStateMachinePriority(StateMachinePriority), MStateMachineExpirationTimeout(StateMachineExpirationTimeout)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateMachineSettings::~CStateMachineSettings(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CStateMachineID& CStateMachineSettings::GetStateMachineID(void) const noexcept
	{
		return(MStateMachineID);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CPriority& CStateMachineSettings::GetStateMachinePriority(void) const noexcept
	{
		return(MStateMachinePriority);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CTimeout& CStateMachineSettings::GetStateMachineExpirationTimeout(void) const noexcept
	{
		return(MStateMachineExpirationTimeout);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------