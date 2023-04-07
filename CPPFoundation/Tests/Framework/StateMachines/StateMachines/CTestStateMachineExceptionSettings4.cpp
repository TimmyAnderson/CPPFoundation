//----------------------------------------------------------------------------------------------------------------------
#include "CTestStateMachineExceptionSettings4.h"
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
	CTestStateMachineExceptionSettings4::CTestStateMachineExceptionSettings4(const CStateMachineID& StateMachineID, const CPriority& StateMachinePriority, const CTimeout& StateMachineExpirationTimeout, const CTestStateMachineExceptionSettings& StateMachineExceptionSettings, const CExpirationTime& StateExpirationTime)
		: CStateMachineSettings(StateMachineID,StateMachinePriority,StateMachineExpirationTimeout), MStateMachineExceptionSettings(StateMachineExceptionSettings), MStateExpirationTime(StateExpirationTime)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineExceptionSettings4::~CTestStateMachineExceptionSettings4(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CTestStateMachineExceptionSettings& CTestStateMachineExceptionSettings4::GetStateMachineExceptionSettings(void) const noexcept
	{
		return(MStateMachineExceptionSettings);
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineExceptionSettings& CTestStateMachineExceptionSettings4::GetStateMachineExceptionSettings(void) noexcept
	{
		return(MStateMachineExceptionSettings);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CExpirationTime& CTestStateMachineExceptionSettings4::GetStateExpirationTime(void) const noexcept
	{
		return(MStateExpirationTime);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------