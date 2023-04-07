//----------------------------------------------------------------------------------------------------------------------
#include "CTestStateMachineExceptionSettings2.h"
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
	CTestStateMachineExceptionSettings2::CTestStateMachineExceptionSettings2(const CStateMachineID& StateMachineID, const CPriority& StateMachinePriority, const CTimeout& StateMachineExpirationTimeout, const CTestStateMachineExceptionSettings& StateMachineExceptionSettings, const CExpirationTime& StateExpirationTime)
		: CStateMachineSettings(StateMachineID,StateMachinePriority,StateMachineExpirationTimeout), MStateMachineExceptionSettings(StateMachineExceptionSettings), MStateExpirationTime(StateExpirationTime)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineExceptionSettings2::~CTestStateMachineExceptionSettings2(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CTestStateMachineExceptionSettings& CTestStateMachineExceptionSettings2::GetStateMachineExceptionSettings(void) const noexcept
	{
		return(MStateMachineExceptionSettings);
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineExceptionSettings& CTestStateMachineExceptionSettings2::GetStateMachineExceptionSettings(void) noexcept
	{
		return(MStateMachineExceptionSettings);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CExpirationTime& CTestStateMachineExceptionSettings2::GetStateExpirationTime(void) const noexcept
	{
		return(MStateExpirationTime);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------