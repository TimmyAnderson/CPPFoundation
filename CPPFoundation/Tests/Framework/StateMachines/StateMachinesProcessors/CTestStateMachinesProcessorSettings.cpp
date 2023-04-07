//----------------------------------------------------------------------------------------------------------------------
#include "CTestStateMachinesProcessorSettings.h"
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
	CTestStateMachinesProcessorSettings::CTestStateMachinesProcessorSettings(bool AutoStartStateMachine)
		: MAutoStartStateMachine(AutoStartStateMachine), MThrowExceptionOnStateInputNotProcessed(), MThrowExceptionOnStateMachineAdded(), MThrowExceptionOnStateMachineFinished()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachinesProcessorSettings::~CTestStateMachinesProcessorSettings(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CTestStateMachinesProcessorSettings::GetAutoStartStateMachine(void) const noexcept
	{
		return(MAutoStartStateMachine);
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineThrowException& CTestStateMachinesProcessorSettings::GetThrowExceptionOnStateInputNotProcessed(void) noexcept
	{
		return(MThrowExceptionOnStateInputNotProcessed);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachinesProcessorSettings::SetThrowExceptionOnStateInputNotProcessed(const CTestStateMachineThrowException& Value) noexcept
	{
		MThrowExceptionOnStateInputNotProcessed=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineThrowException& CTestStateMachinesProcessorSettings::GetThrowExceptionOnStateMachineAdded(void) noexcept
	{
		return(MThrowExceptionOnStateMachineAdded);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachinesProcessorSettings::SetThrowExceptionOnStateMachineAdded(const CTestStateMachineThrowException& Value) noexcept
	{
		MThrowExceptionOnStateMachineAdded=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineThrowException& CTestStateMachinesProcessorSettings::GetThrowExceptionOnStateMachineFinished(void) noexcept
	{
		return(MThrowExceptionOnStateMachineFinished);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachinesProcessorSettings::SetThrowExceptionOnStateMachineFinished(const CTestStateMachineThrowException& Value) noexcept
	{
		MThrowExceptionOnStateMachineFinished=Value;
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------