//----------------------------------------------------------------------------------------------------------------------
#include "CTestStateMachineException1.h"
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
	const CState												CTestStateMachineException1::MStateStarted(1,false,"STATE STARTED");
	const CState												CTestStateMachineException1::MStateRunning(2,false,"STATE RUNNING");
	const CState												CTestStateMachineException1::MStateFinished(0,true,"STATE FINSHED");
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineException1::CTestStateMachineException1(CLogWriter& LogWriter, IStateMachineCallback& StateMachineCallback, CCSPTestStateMachineExceptionSettings1 StateMachineSettings, CStateMachine* StateMachineParent)
		: CTestStateMachine(LogWriter,"TEST STATE MACHINE EXCEPTION 1",StateMachineCallback,StateMachineSettings,StateMachineParent), MSettings(StateMachineSettings), MExceptionSettings(StateMachineSettings->GetStateMachineExceptionSettings()), MExpirationTime(), MInternalGetStateMachineStartState1(0), MInternalGetStateMachineStartState2(0), MInternalExecuteStateMachine1(0), MInternalExecuteStateMachine2(0), MStateMachineExecuteStateMachineStateInput1Event1(0), MStateMachineExecuteStateMachineStateInput1Event2(0), MStateMachineExecuteStateMachineStateInput2Event1(0), MStateMachineExecuteStateMachineStateInput2Event2(0), MStateMachineExecuteStateMachineStateInput3Event1(0), MStateMachineExecuteStateMachineStateInput3Event2(0), MStateMachineExecuteStateMachineStateInput4Event1(0), MStateMachineExecuteStateMachineStateInput4Event2(0), MInternalTerminateStateMachine1(0), MInternalTerminateStateMachine2(0), MInternalGetStateMachineTimeout1(0), MInternalGetStateMachineTimeout2(0), MStateMachineStartedEvent1(0), MStateMachineStartedEvent2(0), MStateMachineFinishedEvent1(0), MStateMachineFinishedEvent2(0), MStateMachineExpiredEvent1(0), MStateMachineExpiredEvent2(0), MStateMachineStateChangedEvent1(0), MStateMachineStateChangedEvent2(0), MStateMachineStateOutputFiringEvent1(0), MStateMachineStateOutputFiringEvent2(0), MStateMachineStateOutputFiredStateOutput1Event1(0), MStateMachineStateOutputFiredStateOutput1Event2(0), MStateMachineStateOutputFiredStateOutput2Event1(0), MStateMachineStateOutputFiredStateOutput2Event2(0), MStateMachineStateOutputFiredStateOutput3Event1(0), MStateMachineStateOutputFiredStateOutput3Event2(0), MStateMachineStateOutputFiredStateOutput4Event1(0), MStateMachineStateOutputFiredStateOutput4Event2(0), MChildStateMachineAddedEvent1(0), MChildStateMachineAddedEvent2(0), MChildStateMachineFinishedEvent1(0), MChildStateMachineFinishedEvent2(0)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachineException1::~CTestStateMachineException1(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CState CTestStateMachineException1::InternalGetStateMachineStartState(void) const
	{
		CTestStateMachineThrowException&						ThrowExceptionOnInternalGetStateMachineStartState=const_cast<CTestStateMachineExceptionSettings&>(MExceptionSettings).GetThrowExceptionOnInternalGetStateMachineStartState();
		Size&													InternalGetStateMachineStartState1=const_cast<Size&>(MInternalGetStateMachineStartState1);
		Size&													InternalGetStateMachineStartState2=const_cast<Size&>(MInternalGetStateMachineStartState2);

		InternalGetStateMachineStartState1++;

		ThrowExceptionOnInternalGetStateMachineStartState.DecrementExceptionCounterCurrentValueAndThrowException();

		InternalGetStateMachineStartState2++;

		return(MStateStarted);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CTestStateMachineException1::InternalExecuteStateMachine(CCSPStateInput StateInput)
	{
		MInternalExecuteStateMachine1++;

		MExceptionSettings.GetThrowExceptionOnInternalExecuteStateMachine().DecrementExceptionCounterCurrentValueAndThrowException();

		MInternalExecuteStateMachine2++;

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
				ChangeState(TypedStateInput->GetStateToChange(),"STATE CHANGED STATE INPUT ARRIVED",TypedStateInput->GetExecuteImmediately());

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

			MStateMachineExecuteStateMachineStateInput1Event1++;

			MExceptionSettings.GetThrowExceptionOnInternalExecuteStateMachineStateInput1().DecrementExceptionCounterCurrentValueAndThrowException();

			MStateMachineExecuteStateMachineStateInput1Event2++;

			if (GetStateMachineID()==TypedStateInput->GetStateMachineID())
			{
				return(true);
			}
			else
			{
				return(MExceptionSettings.GetProcessStateInput1());
			}
		}
		else if (StateInput.IsTypeOfAsConst<CStateInput2>()==true)
		{
			CCSPStateInput2										TypedStateInput=StateInput.DynamicCastAsConst<CStateInput2>();

			MStateMachineExecuteStateMachineStateInput2Event1++;

			MExceptionSettings.GetThrowExceptionOnInternalExecuteStateMachineStateInput2().DecrementExceptionCounterCurrentValueAndThrowException();

			MStateMachineExecuteStateMachineStateInput2Event2++;

			if (GetStateMachineID()==TypedStateInput->GetStateMachineID())
			{
				return(true);
			}
			else
			{
				return(MExceptionSettings.GetProcessStateInput2());
			}
		}
		else if (StateInput.IsTypeOfAsConst<CStateInput3>()==true)
		{
			CCSPStateInput3										TypedStateInput=StateInput.DynamicCastAsConst<CStateInput3>();

			MStateMachineExecuteStateMachineStateInput3Event1++;

			MExceptionSettings.GetThrowExceptionOnInternalExecuteStateMachineStateInput3().DecrementExceptionCounterCurrentValueAndThrowException();

			MStateMachineExecuteStateMachineStateInput3Event2++;

			if (GetStateMachineID()==TypedStateInput->GetStateMachineID())
			{
				return(true);
			}
			else
			{
				return(MExceptionSettings.GetProcessStateInput3());
			}
		}
		else if (StateInput.IsTypeOfAsConst<CStateInput4>()==true)
		{
			CCSPStateInput4										TypedStateInput=StateInput.DynamicCastAsConst<CStateInput4>();

			MStateMachineExecuteStateMachineStateInput4Event1++;

			MExceptionSettings.GetThrowExceptionOnInternalExecuteStateMachineStateInput4().DecrementExceptionCounterCurrentValueAndThrowException();

			MStateMachineExecuteStateMachineStateInput4Event2++;

			if (GetStateMachineID()==TypedStateInput->GetStateMachineID())
			{
				return(true);
			}
			else
			{
				return(MExceptionSettings.GetProcessStateInput4());
			}
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineException1::InternalTerminateStateMachine(void)
	{
		MInternalTerminateStateMachine1++;

		MExceptionSettings.GetThrowExceptionOnInternalTerminateStateMachine().DecrementExceptionCounterCurrentValueAndThrowException();

		ChangeState(MStateFinished,"STATE MACHINE TERMINATED !",false);

		MInternalTerminateStateMachine2++;
	}
//----------------------------------------------------------------------------------------------------------------------
	CTimeout CTestStateMachineException1::InternalGetStateMachineTimeout(CSteadyClock::Milliseconds TimeInMS) const
	{
		CTestStateMachineThrowException&						ThrowExceptionOnInternalGetStateMachineTimeout=const_cast<CTestStateMachineExceptionSettings&>(MExceptionSettings).GetThrowExceptionOnInternalGetStateMachineTimeout();
		Size&													InternalGetStateMachineTimeout1=const_cast<Size&>(MInternalGetStateMachineTimeout1);
		Size&													InternalGetStateMachineTimeout2=const_cast<Size&>(MInternalGetStateMachineTimeout2);

		InternalGetStateMachineTimeout1++;

		ThrowExceptionOnInternalGetStateMachineTimeout.DecrementExceptionCounterCurrentValueAndThrowException();

		InternalGetStateMachineTimeout2++;

		CTimeout												Timeout1=MExceptionSettings.GetTimeout();
		CTimeout												Timeout2=MExpirationTime.CalculateTimeout(TimeInMS);
		CTimeout												Timeout=CTimeout::Min(Timeout1,Timeout2);

		return(Timeout);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineException1::StateMachineStartedEvent(void)
	{
		MStateMachineStartedEvent1++;

		MExceptionSettings.GetThrowExceptionOnStateMachineStartedEvent().DecrementExceptionCounterCurrentValueAndThrowException();

		MStateMachineStartedEvent2++;

		MExpirationTime=MSettings->GetStateExpirationTime();
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineException1::StateMachineFinishedEvent(void)
	{
		MStateMachineFinishedEvent1++;

		MExceptionSettings.GetThrowExceptionOnStateMachineFinishedEvent().DecrementExceptionCounterCurrentValueAndThrowException();

		MStateMachineFinishedEvent2++;
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineException1::StateMachineExpiredEvent(void)
	{
		MStateMachineExpiredEvent1++;

		MExceptionSettings.GetThrowExceptionOnStateMachineExpiredEvent().DecrementExceptionCounterCurrentValueAndThrowException();

		MStateMachineExpiredEvent2++;
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineException1::StateMachineStateChangedEvent(const CState&, const CString&)
	{
		MStateMachineStateChangedEvent1++;

		MExceptionSettings.GetThrowExceptionOnStateMachineStateChangedEvent().DecrementExceptionCounterCurrentValueAndThrowException();

		MStateMachineStateChangedEvent2++;
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CTestStateMachineException1::StateMachineStateOutputFiringEvent(CCSPStateOutput StateOutput)
	{
		MStateMachineStateOutputFiringEvent1++;

		MExceptionSettings.GetThrowExceptionOnStateMachineStateOutputFiringEvent().DecrementExceptionCounterCurrentValueAndThrowException();

		MStateMachineStateOutputFiringEvent2++;

		if (StateOutput.IsTypeOfAsConst<CStateOutput1>()==true)
		{
			CCSPStateOutput1									TypedStateOutput=StateOutput.DynamicCastAsConst<CStateOutput1>();

			MStateMachineStateOutputFiredStateOutput1Event1++;

			MExceptionSettings.GetThrowExceptionOnStateMachineStateOutputFiringEvent1().DecrementExceptionCounterCurrentValueAndThrowException();

			MStateMachineStateOutputFiredStateOutput1Event2++;

			if (GetStateMachineID()==TypedStateOutput->GetStateMachineID())
			{
				return(true);
			}
			else
			{
				return(MExceptionSettings.GetProcessStateOutput1());
			}
		}
		else if (StateOutput.IsTypeOfAsConst<CStateOutput2>()==true)
		{
			CCSPStateOutput2									TypedStateOutput=StateOutput.DynamicCastAsConst<CStateOutput2>();

			MStateMachineStateOutputFiredStateOutput2Event1++;

			MExceptionSettings.GetThrowExceptionOnStateMachineStateOutputFiringEvent2().DecrementExceptionCounterCurrentValueAndThrowException();

			MStateMachineStateOutputFiredStateOutput2Event2++;

			if (GetStateMachineID()==TypedStateOutput->GetStateMachineID())
			{
				return(true);
			}
			else
			{
				return(MExceptionSettings.GetProcessStateOutput2());
			}
		}
		else if (StateOutput.IsTypeOfAsConst<CStateOutput3>()==true)
		{
			CCSPStateOutput3									TypedStateOutput=StateOutput.DynamicCastAsConst<CStateOutput3>();

			MStateMachineStateOutputFiredStateOutput3Event1++;

			MExceptionSettings.GetThrowExceptionOnStateMachineStateOutputFiringEvent3().DecrementExceptionCounterCurrentValueAndThrowException();

			MStateMachineStateOutputFiredStateOutput3Event2++;

			if (GetStateMachineID()==TypedStateOutput->GetStateMachineID())
			{
				return(true);
			}
			else
			{
				return(MExceptionSettings.GetProcessStateOutput3());
			}
		}
		else if (StateOutput.IsTypeOfAsConst<CStateOutput4>()==true)
		{
			CCSPStateOutput4									TypedStateOutput=StateOutput.DynamicCastAsConst<CStateOutput4>();

			MStateMachineStateOutputFiredStateOutput4Event1++;

			MExceptionSettings.GetThrowExceptionOnStateMachineStateOutputFiringEvent4().DecrementExceptionCounterCurrentValueAndThrowException();

			MStateMachineStateOutputFiredStateOutput4Event2++;

			if (GetStateMachineID()==TypedStateOutput->GetStateMachineID())
			{
				return(true);
			}
			else
			{
				return(MExceptionSettings.GetProcessStateOutput4());
			}
		}
		else
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineException1::ChildStateMachineAddedEvent(void)
	{
		CTestStateMachine::ChildStateMachineAddedEvent();

		MChildStateMachineAddedEvent1++;

		MExceptionSettings.GetThrowExceptionOnChildStateMachineAddedEvent().DecrementExceptionCounterCurrentValueAndThrowException();

		MChildStateMachineAddedEvent2++;
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachineException1::ChildStateMachineFinishedEvent(void)
	{
		CTestStateMachine::ChildStateMachineFinishedEvent();

		MChildStateMachineFinishedEvent1++;

		MExceptionSettings.GetThrowExceptionOnChildStateMachineFinishedEvent().DecrementExceptionCounterCurrentValueAndThrowException();

		MChildStateMachineFinishedEvent2++;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetInternalGetStateMachineStartState1(void) const noexcept
	{
		return(MInternalGetStateMachineStartState1);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetInternalGetStateMachineStartState2(void) const noexcept
	{
		return(MInternalGetStateMachineStartState2);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetInternalExecuteStateMachine1(void) const noexcept
	{
		return(MInternalExecuteStateMachine1);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetInternalExecuteStateMachine2(void) const noexcept
	{
		return(MInternalExecuteStateMachine2);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetStateMachineExecuteStateMachineStateInput1Event1(void) const noexcept
	{
		return(MStateMachineExecuteStateMachineStateInput1Event1);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetStateMachineExecuteStateMachineStateInput1Event2(void) const noexcept
	{
		return(MStateMachineExecuteStateMachineStateInput1Event2);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetStateMachineExecuteStateMachineStateInput2Event1(void) const noexcept
	{
		return(MStateMachineExecuteStateMachineStateInput2Event1);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetStateMachineExecuteStateMachineStateInput2Event2(void) const noexcept
	{
		return(MStateMachineExecuteStateMachineStateInput2Event2);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetStateMachineExecuteStateMachineStateInput3Event1(void) const noexcept
	{
		return(MStateMachineExecuteStateMachineStateInput3Event1);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetStateMachineExecuteStateMachineStateInput3Event2(void) const noexcept
	{
		return(MStateMachineExecuteStateMachineStateInput3Event2);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetStateMachineExecuteStateMachineStateInput4Event1(void) const noexcept
	{
		return(MStateMachineExecuteStateMachineStateInput4Event1);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetStateMachineExecuteStateMachineStateInput4Event2(void) const noexcept
	{
		return(MStateMachineExecuteStateMachineStateInput4Event2);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetInternalTerminateStateMachine1(void) const noexcept
	{
		return(MInternalTerminateStateMachine1);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetInternalTerminateStateMachine2(void) const noexcept
	{
		return(MInternalTerminateStateMachine2);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetInternalGetStateMachineTimeout1(void) const noexcept
	{
		return(MInternalGetStateMachineTimeout1);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetInternalGetStateMachineTimeout2(void) const noexcept
	{
		return(MInternalGetStateMachineTimeout2);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetStateMachineStartedEvent1(void) const noexcept
	{
		return(MStateMachineStartedEvent1);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetStateMachineStartedEvent2(void) const noexcept
	{
		return(MStateMachineStartedEvent2);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetStateMachineFinishedEvent1(void) const noexcept
	{
		return(MStateMachineFinishedEvent1);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetStateMachineFinishedEvent2(void) const noexcept
	{
		return(MStateMachineFinishedEvent2);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetStateMachineExpiredEvent1(void) const noexcept
	{
		return(MStateMachineExpiredEvent1);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetStateMachineExpiredEvent2(void) const noexcept
	{
		return(MStateMachineExpiredEvent2);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetStateMachineStateChangedEvent1(void) const noexcept
	{
		return(MStateMachineStateChangedEvent1);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetStateMachineStateChangedEvent2(void) const noexcept
	{
		return(MStateMachineStateChangedEvent2);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetStateMachineStateOutputFiringEvent1(void) const noexcept
	{
		return(MStateMachineStateOutputFiringEvent1);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetStateMachineStateOutputFiringEvent2(void) const noexcept
	{
		return(MStateMachineStateOutputFiringEvent2);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetStateMachineStateOutputFiredStateOutput1Event1(void) const noexcept
	{
		return(MStateMachineStateOutputFiredStateOutput1Event1);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetStateMachineStateOutputFiredStateOutput1Event2(void) const noexcept
	{
		return(MStateMachineStateOutputFiredStateOutput1Event2);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetStateMachineStateOutputFiredStateOutput2Event1(void) const noexcept
	{
		return(MStateMachineStateOutputFiredStateOutput2Event1);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetStateMachineStateOutputFiredStateOutput2Event2(void) const noexcept
	{
		return(MStateMachineStateOutputFiredStateOutput2Event2);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetStateMachineStateOutputFiredStateOutput3Event1(void) const noexcept
	{
		return(MStateMachineStateOutputFiredStateOutput3Event1);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetStateMachineStateOutputFiredStateOutput3Event2(void) const noexcept
	{
		return(MStateMachineStateOutputFiredStateOutput3Event2);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetStateMachineStateOutputFiredStateOutput4Event1(void) const noexcept
	{
		return(MStateMachineStateOutputFiredStateOutput4Event1);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetStateMachineStateOutputFiredStateOutput4Event2(void) const noexcept
	{
		return(MStateMachineStateOutputFiredStateOutput4Event2);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetChildStateMachineAddedEvent1(void) const noexcept
	{
		return(MChildStateMachineAddedEvent1);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetChildStateMachineAddedEvent2(void) const noexcept
	{
		return(MChildStateMachineAddedEvent2);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetChildStateMachineFinishedEvent1(void) const noexcept
	{
		return(MChildStateMachineFinishedEvent1);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachineException1::GetChildStateMachineFinishedEvent2(void) const noexcept
	{
		return(MChildStateMachineFinishedEvent2);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------