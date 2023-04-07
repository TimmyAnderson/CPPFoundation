//----------------------------------------------------------------------------------------------------------------------
#include "CTestStateMachineExceptionSettings3.h"
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
	CTestStateMachineExceptionSettings3::CTestStateMachineExceptionSettings3(const CStateMachineID& StateMachineID, const CPriority& StateMachinePriority, const CTimeout& StateMachineExpirationTimeout, const CTestStateMachineExceptionSettings& StateMachineExceptionSettings, const CExpirationTime& StateExpirationTime)
		: CStateMachineSettings(StateMachineID,StateMachinePriority,StateMachineExpirationTimeout), MStateMachineExceptionSettings(StateMachineExceptionSettings), MStateExpirationTime(StateExpirationTime)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineExceptionSettings3::~CTestStateMachineExceptionSettings3(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CTestStateMachineExceptionSettings& CTestStateMachineExceptionSettings3::GetStateMachineExceptionSettings(void) const noexcept
	{
		return(MStateMachineExceptionSettings);
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineExceptionSettings& CTestStateMachineExceptionSettings3::GetStateMachineExceptionSettings(void) noexcept
	{
		return(MStateMachineExceptionSettings);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CExpirationTime& CTestStateMachineExceptionSettings3::GetStateExpirationTime(void) const noexcept
	{
		return(MStateExpirationTime);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------