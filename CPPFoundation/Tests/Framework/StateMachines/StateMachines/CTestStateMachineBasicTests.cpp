//----------------------------------------------------------------------------------------------------------------------
#include "CTestStateMachineBasicTests.h"
#include <Tests/Framework/StateMachines/StateInputs/CStateInputAddChildStateMachine.h>
#include <Tests/Framework/StateMachines/StateInputs/CStateInputChangeState.h>
#include <Tests/Framework/StateMachines/StateInputs/CStateInputSendStateOutput.h>
#include <Tests/Framework/StateMachines/StateInputs/CStateInput1.h>
#include <Tests/Framework/StateMachines/StateInputs/CStateInput2.h>
#include <Tests/Framework/StateMachines/StateInputs/CStateInput3.h>
#include <Tests/Framework/StateMachines/StateInputs/CStateInput4.h>
#include <Tests/Framework/StateMachines/StateOutputs/CStateOutput1.h>
#include <Tests/Framework/StateMachines/StateOutputs/CStateOutput2.h>
#include <Tests/Framework/StateMachines/StateOutputs/CStateOutput3.h>
#include <Tests/Framework/StateMachines/StateOutputs/CStateOutput4.h>
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
	const CState												CTestStateMachineBasicTests::MStateStarted(1,false,"STATE STARTED");
	const CState												CTestStateMachineBasicTests::MStateRunning(2,false,"STATE RUNNING");
	const CState												CTestStateMachineBasicTests::MStateFinished(0,true,"STATE FINSHED");
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineBasicTests::CTestStateMachineBasicTests(CLogWriter& LogWriter, IStateMachineCallback& StateMachineCallback, CCSPTestStateMachineSettingsBasicTests StateMachineSettings, CStateMachine* StateMachineParent)
		: CTestStateMachine(LogWriter,"BASIC TESTS STATE MACHINE",StateMachineCallback,StateMachineSettings,StateMachineParent), MSettings(StateMachineSettings), MExpirationTime(), MInternalGetStateMachineStartState(0), MInternalExecuteStateMachine(0), MInternalTerminateStateMachine(0), MInternalGetStateMachineTimeout(0), MStateMachineStartedEvent(0), MStateMachineFinishedEvent(0), MStateMachineExpiredEvent(0), MStateMachineStateChangedEvent(0), MStateMachineStateOutputFiringEvent(0), MChildStateMachineAddedEvent(0), MChildStateMachineFinishedEvent(0), MStateInputProcessedStateInput1(0), MStateInputProcessedStateInput2(0), MStateInputProcessedStateInput3(0), MStateInputProcessedStateInput4(0)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineBasicTests::~CTestStateMachineBasicTests(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CState CTestStateMachineBasicTests::InternalGetStateMachineStartState(void) const
	{
		Size&													InternalGetStateMachineStartState=const_cast<Size&>(MInternalGetStateMachineStartState);

		InternalGetStateMachineStartState++;

		return(MStateStarted);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CTestStateMachineBasicTests::InternalExecuteStateMachine(CCSPStateInput StateInput)
	{
		MInternalExecuteStateMachine++;

		if (MExpirationTime.HasExpired()==true)
		{
			ChangeState(MStateFinished,"TIMEOUT EXPIRED",true);
			return(false);
		}

		if (StateInput.IsTypeOfAsConst<CStateInputAddChildStateMachine>()==true)
		{
			CCSPStateInputAddChildStateMachine					TypedStateInput=StateInput.DynamicCastAsConst<CStateInputAddChildStateMachine>();

			if (TypedStateInput->GetParentStateMachineID()==GetStateMachineID())
			{
				AddChildStateMachine(TypedStateInput->GetStateMachineToAdd());

				return(true);
			}
			else
			{
				return(false);
			}
		}
		else if (StateInput.IsTypeOfAsConst<CStateInputChangeState>()==true)
		{
			CCSPStateInputChangeState							TypedStateInput=StateInput.DynamicCastAsConst<CStateInputChangeState>();

			if (TypedStateInput->GetStateMachineID()==GetStateMachineID())
			{
				ChangeState(TypedStateInput->GetStateToChange(),TypedStateInput->GetReason(),TypedStateInput->GetExecuteImmediately());

				return(true);
			}
			else
			{
				return(false);
			}
		}
		else if (StateInput.IsTypeOfAsConst<CStateInputSendStateOutput>()==true)
		{
			CCSPStateInputSendStateOutput						TypedStateInput=StateInput.DynamicCastAsConst<CStateInputSendStateOutput>();

			if (TypedStateInput->GetSendingStateMachineID()==GetStateMachineID())
			{
				FireStateOutput(TypedStateInput->GetStateOutputToSend());

				return(true);
			}
			else
			{
				return(false);
			}
		}
		else if (StateInput.IsTypeOfAsConst<CStateInput1>()==true)
		{
			CCSPStateInput1										TypedStateInput=StateInput.DynamicCastAsConst<CStateInput1>();

			MStateInputProcessedStateInput1++;

			if (GetStateMachineID()==TypedStateInput->GetStateMachineID())
			{
				return(true);
			}
			else
			{
				return(MSettings->GetProcessStateInput1());
			}
		}
		else if (StateInput.IsTypeOfAsConst<CStateInput2>()==true)
		{
			CCSPStateInput2										TypedStateInput=StateInput.DynamicCastAsConst<CStateInput2>();

			MStateInputProcessedStateInput2++;

			if (GetStateMachineID()==TypedStateInput->GetStateMachineID())
			{
				return(true);
			}
			else
			{
				return(MSettings->GetProcessStateInput2());
			}
		}
		else if (StateInput.IsTypeOfAsConst<CStateInput3>()==true)
		{
			CCSPStateInput3										TypedStateInput=StateInput.DynamicCastAsConst<CStateInput3>();

			MStateInputProcessedStateInput3++;

			if (GetStateMachineID()==TypedStateInput->GetStateMachineID())
			{
				return(true);
			}
			else
			{
				return(MSettings->GetProcessStateInput3());
			}
		}
		else if (StateInput.IsTypeOfAsConst<CStateInput4>()==true)
		{
			CCSPStateInput4										TypedStateInput=StateInput.DynamicCastAsConst<CStateInput4>();

			MStateInputProcessedStateInput4++;

			if (GetStateMachineID()==TypedStateInput->GetStateMachineID())
			{
				return(true);
			}
			else
			{
				return(MSettings->GetProcessStateInput4());
			}
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineBasicTests::InternalTerminateStateMachine(void)
	{
		MInternalTerminateStateMachine++;

		ChangeState(MStateFinished,"STATE MACHINE TERMINATED !",false);
	}
//----------------------------------------------------------------------------------------------------------------------
	CTimeout CTestStateMachineBasicTests::InternalGetStateMachineTimeout(CSteadyClock::Milliseconds TimeInMS) const
	{
		Size&													InternalGetStateMachineTimeout=const_cast<Size&>(MInternalGetStateMachineTimeout);

		InternalGetStateMachineTimeout++;

		return(MExpirationTime.CalculateTimeout(TimeInMS));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineBasicTests::StateMachineStartedEvent(void)
	{
		CTestStateMachine::StateMachineStartedEvent();

		MStateMachineStartedEvent++;

		MExpirationTime=MSettings->GetStateExpirationTime();
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineBasicTests::StateMachineFinishedEvent(void)
	{
		CTestStateMachine::StateMachineFinishedEvent();

		MStateMachineFinishedEvent++;
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineBasicTests::StateMachineExpiredEvent(void)
	{
		CTestStateMachine::StateMachineExpiredEvent();

		MStateMachineExpiredEvent++;
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineBasicTests::StateMachineStateChangedEvent(const CState& NewState, const CString& Reason)
	{
		CTestStateMachine::StateMachineStateChangedEvent(NewState,Reason);

		MStateMachineStateChangedEvent++;
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CTestStateMachineBasicTests::StateMachineStateOutputFiringEvent(CCSPStateOutput StateOutput)
	{
		CTestStateMachine::StateMachineStateOutputFiringEvent(StateOutput);

		MStateMachineStateOutputFiringEvent++;

		if (StateOutput.IsTypeOfAsConst<CStateOutput1>()==true)
		{
			CCSPStateOutput1									TypedStateOutput=StateOutput.DynamicCastAsConst<CStateOutput1>();

			if (GetStateMachineID()==TypedStateOutput->GetStateMachineID())
			{
				return(true);
			}
			else
			{
				return(MSettings->GetProcessStateOutput1());
			}
		}
		else if (StateOutput.IsTypeOfAsConst<CStateOutput2>()==true)
		{
			CCSPStateOutput2									TypedStateOutput=StateOutput.DynamicCastAsConst<CStateOutput2>();

			if (GetStateMachineID()==TypedStateOutput->GetStateMachineID())
			{
				return(true);
			}
			else
			{
				return(MSettings->GetProcessStateOutput2());
			}
		}
		else if (StateOutput.IsTypeOfAsConst<CStateOutput3>()==true)
		{
			CCSPStateOutput3									TypedStateOutput=StateOutput.DynamicCastAsConst<CStateOutput3>();

			if (GetStateMachineID()==TypedStateOutput->GetStateMachineID())
			{
				return(true);
			}
			else
			{
				return(MSettings->GetProcessStateOutput3());
			}
		}
		else if (StateOutput.IsTypeOfAsConst<CStateOutput4>()==true)
		{
			CCSPStateOutput4									TypedStateOutput=StateOutput.DynamicCastAsConst<CStateOutput4>();

			if (GetStateMachineID()==TypedStateOutput->GetStateMachineID())
			{
				return(true);
			}
			else
			{
				return(MSettings->GetProcessStateOutput4());
			}
		}
		else
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineBasicTests::ChildStateMachineAddedEvent(void)
	{
		CTestStateMachine::ChildStateMachineAddedEvent();

		MChildStateMachineAddedEvent++;
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineBasicTests::ChildStateMachineFinishedEvent(void)
	{
		CTestStateMachine::ChildStateMachineFinishedEvent();

		MChildStateMachineFinishedEvent++;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineBasicTests::GetInternalGetStateMachineStartState(void) const noexcept
	{
		return(MInternalGetStateMachineStartState);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineBasicTests::GetInternalExecuteStateMachine(void) const noexcept
	{
		return(MInternalExecuteStateMachine);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineBasicTests::GetInternalTerminateStateMachine(void) const noexcept
	{
		return(MInternalTerminateStateMachine);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineBasicTests::GetInternalGetStateMachineTimeout(void) const noexcept
	{
		return(MInternalGetStateMachineTimeout);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineBasicTests::GetStateMachineStartedEvent(void) const noexcept
	{
		return(MStateMachineStartedEvent);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineBasicTests::GetStateMachineFinishedEvent(void) const noexcept
	{
		return(MStateMachineFinishedEvent);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineBasicTests::GetStateMachineExpiredEvent(void) const noexcept
	{
		return(MStateMachineExpiredEvent);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineBasicTests::GetStateMachineStateChangedEvent(void) const noexcept
	{
		return(MStateMachineStateChangedEvent);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineBasicTests::GetStateMachineStateOutputFiringEvent(void) const noexcept
	{
		return(MStateMachineStateOutputFiringEvent);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineBasicTests::GetChildStateMachineAddedEvent(void) const noexcept
	{
		return(MChildStateMachineAddedEvent);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineBasicTests::GetChildStateMachineFinishedEvent(void) const noexcept
	{
		return(MChildStateMachineFinishedEvent);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineBasicTests::GetStateInputProcessedStateInput1(void) const noexcept
	{
		return(MStateInputProcessedStateInput1);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineBasicTests::GetStateInputProcessedStateInput2(void) const noexcept
	{
		return(MStateInputProcessedStateInput2);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineBasicTests::GetStateInputProcessedStateInput3(void) const noexcept
	{
		return(MStateInputProcessedStateInput3);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineBasicTests::GetStateInputProcessedStateInput4(void) const noexcept
	{
		return(MStateInputProcessedStateInput4);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineBasicTests::TestHelperMethods(void) const
	{
		GetLogWriter();
		GetLogCategoryStateMachine();
		GetStateMachineName();
		GetStateMachineCallback();
		GetState();
		GetStateMachineID();
		GetStateMachinePriority();
		GetStateMachineExpirationTimeout();
		GetStateMachineSettings();
		GetStateMachineParent();
		GetStateMachineRoot();
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------