//----------------------------------------------------------------------------------------------------------------------
#include "CTestStateMachine3.h"
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
	const CState												CTestStateMachine3::MStateStarted(1,false,"STATE STARTED");
	const CState												CTestStateMachine3::MStateRunning(2,false,"STATE RUNNING");
	const CState												CTestStateMachine3::MStateFinished(0,true,"STATE FINSHED");
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachine3::CTestStateMachine3(CLogWriter& LogWriter, IStateMachineCallback& StateMachineCallback, CCSPTestStateMachineSettings3 StateMachineSettings, CStateMachine* StateMachineParent)
		: CTestStateMachine(LogWriter,"TEST STATE MACHINE 3",StateMachineCallback,StateMachineSettings,StateMachineParent), MSettings(StateMachineSettings), MExpirationTime(), MInternalGetStateMachineStartState(0), MInternalExecuteStateMachine(0), MStateMachineExecuteStateMachineStateInput1Event(0), MStateMachineExecuteStateMachineStateInput2Event(0), MStateMachineExecuteStateMachineStateInput3Event(0), MStateMachineExecuteStateMachineStateInput4Event(0), MInternalTerminateStateMachine(0), MInternalGetStateMachineTimeout(0), MStateMachineStartedEvent(0), MStateMachineFinishedEvent(0), MStateMachineExpiredEvent(0), MStateMachineStateChangedEvent(0), MStateMachineStateOutputFiringEvent(0), MStateMachineStateOutputFiredStateOutput1Event(0), MStateMachineStateOutputFiredStateOutput2Event(0), MStateMachineStateOutputFiredStateOutput3Event(0), MStateMachineStateOutputFiredStateOutput4Event(0), MChildStateMachineAddedEvent(0), MChildStateMachineFinishedEvent(0)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestStateMachine3::~CTestStateMachine3(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CState CTestStateMachine3::InternalGetStateMachineStartState(void) const
	{
		Size&													InternalGetStateMachineStartState=const_cast<Size&>(MInternalGetStateMachineStartState);

		InternalGetStateMachineStartState++;

		return(MStateStarted);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CTestStateMachine3::InternalExecuteStateMachine(CCSPStateInput StateInput)
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

			MStateMachineExecuteStateMachineStateInput1Event++;

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

			MStateMachineExecuteStateMachineStateInput2Event++;

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

			MStateMachineExecuteStateMachineStateInput3Event++;

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

			MStateMachineExecuteStateMachineStateInput4Event++;

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
	void CTestStateMachine3::InternalTerminateStateMachine(void)
	{
		MInternalTerminateStateMachine++;

		ChangeState(MStateFinished,"STATE MACHINE TERMINATED !",false);
	}
//----------------------------------------------------------------------------------------------------------------------
	CTimeout CTestStateMachine3::InternalGetStateMachineTimeout(CSteadyClock::Milliseconds TimeInMS) const
	{
		Size&													InternalGetStateMachineTimeout=const_cast<Size&>(MInternalGetStateMachineTimeout);

		InternalGetStateMachineTimeout++;

		return(MExpirationTime.CalculateTimeout(TimeInMS));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachine3::StateMachineStartedEvent(void)
	{
		MStateMachineStartedEvent++;

		MExpirationTime=MSettings->GetStateExpirationTime();
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachine3::StateMachineFinishedEvent(void)
	{
		MStateMachineFinishedEvent++;
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachine3::StateMachineExpiredEvent(void)
	{
		MStateMachineExpiredEvent++;
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachine3::StateMachineStateChangedEvent(const CState&, const CString&)
	{
		MStateMachineStateChangedEvent++;
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CTestStateMachine3::StateMachineStateOutputFiringEvent(CCSPStateOutput StateOutput)
	{
		MStateMachineStateOutputFiringEvent++;

		if (StateOutput.IsTypeOfAsConst<CStateOutput1>()==true)
		{
			CCSPStateOutput1									TypedStateOutput=StateOutput.DynamicCastAsConst<CStateOutput1>();

			MStateMachineStateOutputFiredStateOutput1Event++;

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

			MStateMachineStateOutputFiredStateOutput2Event++;

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

			MStateMachineStateOutputFiredStateOutput3Event++;

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

			MStateMachineStateOutputFiredStateOutput4Event++;

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
	void CTestStateMachine3::ChildStateMachineAddedEvent(void)
	{
		CTestStateMachine::ChildStateMachineAddedEvent();

		MChildStateMachineAddedEvent++;
	}
//----------------------------------------------------------------------------------------------------------------------
	void CTestStateMachine3::ChildStateMachineFinishedEvent(void)
	{
		CTestStateMachine::ChildStateMachineFinishedEvent();

		MChildStateMachineFinishedEvent++;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachine3::GetInternalGetStateMachineStartState(void) const noexcept
	{
		return(MInternalGetStateMachineStartState);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachine3::GetInternalExecuteStateMachine(void) const noexcept
	{
		return(MInternalExecuteStateMachine);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachine3::GetStateMachineExecuteStateMachineStateInput1Event(void) const noexcept
	{
		return(MStateMachineExecuteStateMachineStateInput1Event);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachine3::GetStateMachineExecuteStateMachineStateInput2Event(void) const noexcept
	{
		return(MStateMachineExecuteStateMachineStateInput2Event);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachine3::GetStateMachineExecuteStateMachineStateInput3Event(void) const noexcept
	{
		return(MStateMachineExecuteStateMachineStateInput3Event);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachine3::GetStateMachineExecuteStateMachineStateInput4Event(void) const noexcept
	{
		return(MStateMachineExecuteStateMachineStateInput4Event);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachine3::GetInternalTerminateStateMachine(void) const noexcept
	{
		return(MInternalTerminateStateMachine);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachine3::GetInternalGetStateMachineTimeout(void) const noexcept
	{
		return(MInternalGetStateMachineTimeout);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachine3::GetStateMachineStartedEvent(void) const noexcept
	{
		return(MStateMachineStartedEvent);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachine3::GetStateMachineFinishedEvent(void) const noexcept
	{
		return(MStateMachineFinishedEvent);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachine3::GetStateMachineExpiredEvent(void) const noexcept
	{
		return(MStateMachineExpiredEvent);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachine3::GetStateMachineStateChangedEvent(void) const noexcept
	{
		return(MStateMachineStateChangedEvent);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachine3::GetStateMachineStateOutputFiringEvent(void) const noexcept
	{
		return(MStateMachineStateOutputFiringEvent);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachine3::GetStateMachineStateOutputFiredStateOutput1Event(void) const noexcept
	{
		return(MStateMachineStateOutputFiredStateOutput1Event);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachine3::GetStateMachineStateOutputFiredStateOutput2Event(void) const noexcept
	{
		return(MStateMachineStateOutputFiredStateOutput2Event);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachine3::GetStateMachineStateOutputFiredStateOutput3Event(void) const noexcept
	{
		return(MStateMachineStateOutputFiredStateOutput3Event);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachine3::GetStateMachineStateOutputFiredStateOutput4Event(void) const noexcept
	{
		return(MStateMachineStateOutputFiredStateOutput4Event);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachine3::GetChildStateMachineAddedEvent(void) const noexcept
	{
		return(MChildStateMachineAddedEvent);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CTestStateMachine3::GetChildStateMachineFinishedEvent(void) const noexcept
	{
		return(MChildStateMachineFinishedEvent);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------