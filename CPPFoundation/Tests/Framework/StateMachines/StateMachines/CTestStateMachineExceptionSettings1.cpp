//----------------------------------------------------------------------------------------------------------------------
#include "CTestStateMachineExceptionSettings1.h"
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
	CTestStateMachineExceptionSettings1::CTestStateMachineExceptionSettings1(const CStateMachineID& StateMachineID, const CPriority& StateMachinePriority, const CTimeout& StateMachineExpirationTimeout, const CTestStateMachineExceptionSettings& StateMachineExceptionSettings, const CExpirationTime& StateExpirationTime)
		: CStateMachineSettings(StateMachineID,StateMachinePriority,StateMachineExpirationTimeout), MStateMachineExceptionSettings(StateMachineExceptionSettings), MStateExpirationTime(StateExpirationTime)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineExceptionSettings1::~CTestStateMachineExceptionSettings1(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CTestStateMachineExceptionSettings& CTestStateMachineExceptionSettings1::GetStateMachineExceptionSettings(void) const noexcept
	{
		return(MStateMachineExceptionSettings);
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineExceptionSettings& CTestStateMachineExceptionSettings1::GetStateMachineExceptionSettings(void) noexcept
	{
		return(MStateMachineExceptionSettings);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CExpirationTime& CTestStateMachineExceptionSettings1::GetStateExpirationTime(void) const noexcept
	{
		return(MStateExpirationTime);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------