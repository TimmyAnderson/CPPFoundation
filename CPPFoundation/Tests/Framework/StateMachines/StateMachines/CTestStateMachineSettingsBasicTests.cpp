//----------------------------------------------------------------------------------------------------------------------
#include "CTestStateMachineSettingsBasicTests.h"
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
	CTestStateMachineSettingsBasicTests::CTestStateMachineSettingsBasicTests(const CStateMachineID& StateMachineID, const CPriority& StateMachinePriority, const CTimeout& StateMachineExpirationTimeout, const CExpirationTime& StateExpirationTime, bool ProcessStateInput1, bool ProcessStateInput2, bool ProcessStateInput3, bool ProcessStateInput4, bool ProcessStateOutput1, bool ProcessStateOutput2, bool ProcessStateOutput3, bool ProcessStateOutput4)
		: CStateMachineSettings(StateMachineID,StateMachinePriority,StateMachineExpirationTimeout), MStateExpirationTime(StateExpirationTime), MProcessStateInput1(ProcessStateInput1), MProcessStateInput2(ProcessStateInput2), MProcessStateInput3(ProcessStateInput3), MProcessStateInput4(ProcessStateInput4), MProcessStateOutput1(ProcessStateOutput1), MProcessStateOutput2(ProcessStateOutput2), MProcessStateOutput3(ProcessStateOutput3), MProcessStateOutput4(ProcessStateOutput4)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineSettingsBasicTests::~CTestStateMachineSettingsBasicTests(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CExpirationTime& CTestStateMachineSettingsBasicTests::GetStateExpirationTime(void) const noexcept
	{
		return(MStateExpirationTime);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CTestStateMachineSettingsBasicTests::GetProcessStateInput1(void) const noexcept
	{
		return(MProcessStateInput1);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CTestStateMachineSettingsBasicTests::GetProcessStateInput2(void) const noexcept
	{
		return(MProcessStateInput2);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CTestStateMachineSettingsBasicTests::GetProcessStateInput3(void) const noexcept
	{
		return(MProcessStateInput3);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CTestStateMachineSettingsBasicTests::GetProcessStateInput4(void) const noexcept
	{
		return(MProcessStateInput4);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CTestStateMachineSettingsBasicTests::GetProcessStateOutput1(void) const noexcept
	{
		return(MProcessStateOutput1);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CTestStateMachineSettingsBasicTests::GetProcessStateOutput2(void) const noexcept
	{
		return(MProcessStateOutput2);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CTestStateMachineSettingsBasicTests::GetProcessStateOutput3(void) const noexcept
	{
		return(MProcessStateOutput3);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CTestStateMachineSettingsBasicTests::GetProcessStateOutput4(void) const noexcept
	{
		return(MProcessStateOutput4);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------