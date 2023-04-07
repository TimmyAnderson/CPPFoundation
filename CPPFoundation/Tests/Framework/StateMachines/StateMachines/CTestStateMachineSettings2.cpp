//----------------------------------------------------------------------------------------------------------------------
#include "CTestStateMachineSettings2.h"
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
	CTestStateMachineSettings2::CTestStateMachineSettings2(const CStateMachineID& StateMachineID, const CPriority& StateMachinePriority, const CTimeout& StateMachineExpirationTimeout, const CExpirationTime& StateExpirationTime, bool ProcessStateInput1, bool ProcessStateInput2, bool ProcessStateInput3, bool ProcessStateInput4, bool ProcessStateOutput1, bool ProcessStateOutput2, bool ProcessStateOutput3, bool ProcessStateOutput4)
		: CStateMachineSettings(StateMachineID,StateMachinePriority,StateMachineExpirationTimeout), MStateExpirationTime(StateExpirationTime), MProcessStateInput1(ProcessStateInput1), MProcessStateInput2(ProcessStateInput2), MProcessStateInput3(ProcessStateInput3), MProcessStateInput4(ProcessStateInput4), MProcessStateOutput1(ProcessStateOutput1), MProcessStateOutput2(ProcessStateOutput2), MProcessStateOutput3(ProcessStateOutput3), MProcessStateOutput4(ProcessStateOutput4)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineSettings2::~CTestStateMachineSettings2(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CExpirationTime& CTestStateMachineSettings2::GetStateExpirationTime(void) const noexcept
	{
		return(MStateExpirationTime);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CTestStateMachineSettings2::GetProcessStateInput1(void) const noexcept
	{
		return(MProcessStateInput1);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CTestStateMachineSettings2::GetProcessStateInput2(void) const noexcept
	{
		return(MProcessStateInput2);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CTestStateMachineSettings2::GetProcessStateInput3(void) const noexcept
	{
		return(MProcessStateInput3);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CTestStateMachineSettings2::GetProcessStateInput4(void) const noexcept
	{
		return(MProcessStateInput4);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CTestStateMachineSettings2::GetProcessStateOutput1(void) const noexcept
	{
		return(MProcessStateOutput1);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CTestStateMachineSettings2::GetProcessStateOutput2(void) const noexcept
	{
		return(MProcessStateOutput2);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CTestStateMachineSettings2::GetProcessStateOutput3(void) const noexcept
	{
		return(MProcessStateOutput3);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CTestStateMachineSettings2::GetProcessStateOutput4(void) const noexcept
	{
		return(MProcessStateOutput4);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------