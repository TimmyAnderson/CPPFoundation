//----------------------------------------------------------------------------------------------------------------------
#include "CTestStateMachinesProcessor.h"
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
	CTestStateMachinesProcessor::CTestStateMachinesProcessor(CLogWriter& LogWriter, const CString& StateMachinesProcessorName, CCSPTestStateMachinesProcessorSettings StateMachinesProcessorSettings)
		: CStateMachinesProcessor(LogWriter,StateMachinesProcessorName,StateMachinesProcessorSettings), MStateMachinesProcessorSettings(*StateMachinesProcessorSettings)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachinesProcessor::~CTestStateMachinesProcessor(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachinesProcessor::StateMachineAdded(CSPStateMachine StateMachine)
	{
		CStateMachinesProcessor::StateMachineAdded(StateMachine);

		if (MStateMachinesProcessorSettings.GetAutoStartStateMachine()==true)
		{
			StateMachine->StartStateMachine();
		}

		MStateMachinesProcessorSettings.GetThrowExceptionOnStateMachineAdded().DecrementExceptionCounterCurrentValueAndThrowException();
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachinesProcessor::StateMachineFinished(CSPStateMachine StateMachine)
	{
		CStateMachinesProcessor::StateMachineFinished(StateMachine);

		MStateMachinesProcessorSettings.GetThrowExceptionOnStateMachineFinished().DecrementExceptionCounterCurrentValueAndThrowException();
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachinesProcessor::StateInputNotProcessed(CCSPStateInput StateInput)
	{
		CStateMachinesProcessor::StateInputNotProcessed(StateInput);

		MStateMachinesProcessorSettings.GetThrowExceptionOnStateInputNotProcessed().DecrementExceptionCounterCurrentValueAndThrowException();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CString& CTestStateMachinesProcessor::TestGetStateMachinesProcessorName(void) const noexcept
	{
		return(GetStateMachinesProcessorName());
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPStateMachinesProcessorSettings CTestStateMachinesProcessor::TestGetStateMachinesProcessorSettings(void) const noexcept
	{
		return(GetStateMachinesProcessorSettings());
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachinesProcessor::TestStartStateMachine(CSPStateMachine StateMachine)
	{
		StartStateMachine(StateMachine);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------