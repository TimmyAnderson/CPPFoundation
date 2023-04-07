//----------------------------------------------------------------------------------------------------------------------
#include "CStateMachineTest.h"
#include <Framework/Foundation/Collections/CVector.h>
#include <Framework/Foundation/Console/CConsoleHelper.h>
#include <Framework/Foundation/Threads/CThread.h>
#include <Framework/Foundation/Types/CMethod.h>
#include <Tests/Framework/StateMachines/StateInputs/CStateInput1.h>
#include <Tests/Framework/StateMachines/StateInputs/CStateInput2.h>
#include <Tests/Framework/StateMachines/StateInputs/CStateInput3.h>
#include <Tests/Framework/StateMachines/StateInputs/CStateInput4.h>
#include <Tests/Framework/StateMachines/StateInputs/CStateInputAddChildStateMachine.h>
#include <Tests/Framework/StateMachines/StateInputs/CStateInputChangeState.h>
#include <Tests/Framework/StateMachines/StateInputs/CStateInputSendStateOutput.h>
#include <Tests/Framework/StateMachines/StateInputs/CStateInputUnsupported.h>
#include <Tests/Framework/StateMachines/StateMachines/CTestStateMachineThrowException.h>
#include <Tests/Framework/StateMachines/StateMachinesProcessors/CTestStateMachinesProcessor.h>
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
	CStateMachineTest::CStateMachineTest(CLogWriter& LogWriter, const CLogCategory& LogCategoryTest, bool WriteStateMachineLogs)
		: CTest(LogWriter,LogCategoryTest,"STATE MACHINE TEST"), CLogWriter(LogWriter.GetLogSource()), MWriteStateMachineLogs(WriteStateMachineLogs), MOutputCollection(), MNumberOfWarningsAndErrors()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateMachineTest::~CStateMachineTest(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CStateMachineTest::ProcessStateOutput(CCSPStateOutput StateOutput)
	{
		MOutputCollection.Add(StateOutput);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CStateMachineTest::Reset(void)
	{
		MOutputCollection.Clear();
		MNumberOfWarningsAndErrors=0;
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::CheckStateMachineTimeout(const CTimeout& Timeout, bool IsZero, bool IsInfinite)
	{
		if (Timeout.IsZero()!=IsZero)
		{
			return(false);
		}

		if (Timeout.IsInfinite()!=IsInfinite)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::CheckStateMachineChildCollection(const CTestStateMachine::CTestStateMachineChildCollection& ChildCollection, const CStateMachineIDCollection& StateMachineIDCollection)
	{
		for(const CStateMachineID& StateMachineID : StateMachineIDCollection)
		{
			if (ChildCollection.Contains(StateMachineID)==false)
			{
				return(false);
			}
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::CheckStateMachineState(CSPTestStateMachineBasicTests StateMachine, Size InternalGetStateMachineStartState, Size InternalExecuteStateMachine, Size InternalTerminateStateMachine, Size InternalGetStateMachineTimeout, Size StateMachineStartedEvent, Size StateMachineFinishedEvent, Size StateMachineExpiredEvent, Size StateMachineStateChangedEvent, Size StateMachineStateOutputFiringEvent, Size ChildStateMachineAddedEvent, Size ChildStateMachineFinishedEvent, bool HasFinished)
	{
		Size													ActualValueInternalGetStateMachineStartState=StateMachine->GetInternalGetStateMachineStartState();
		Size													ActualValueInternalExecuteStateMachine=StateMachine->GetInternalExecuteStateMachine();
		Size													ActualValueInternalTerminateStateMachine=StateMachine->GetInternalTerminateStateMachine();
		Size													ActualValueInternalGetStateMachineTimeout=StateMachine->GetInternalGetStateMachineTimeout();
		Size													ActualValueStateMachineStartedEvent=StateMachine->GetStateMachineStartedEvent();
		Size													ActualValueStateMachineFinishedEvent=StateMachine->GetStateMachineFinishedEvent();
		Size													ActualValueStateMachineExpiredEvent=StateMachine->GetStateMachineExpiredEvent();
		Size													ActualValueStateMachineStateChangedEvent=StateMachine->GetStateMachineStateChangedEvent();
		Size													ActualValueStateMachineStateOutputFiringEvent=StateMachine->GetStateMachineStateOutputFiringEvent();
		Size													ActualValueChildStateMachineAddedEvent=StateMachine->GetChildStateMachineAddedEvent();
		Size													ActualValueChildStateMachineFinishedEvent=StateMachine->GetChildStateMachineFinishedEvent();
		bool													ActualValueHasFinished=StateMachine->HasFinished();

		if (ActualValueInternalGetStateMachineStartState!=InternalGetStateMachineStartState)
		{
			return(false);
		}

		if (ActualValueInternalExecuteStateMachine!=InternalExecuteStateMachine)
		{
			return(false);
		}

		if (ActualValueInternalTerminateStateMachine!=InternalTerminateStateMachine)
		{
			return(false);
		}

		if (ActualValueInternalGetStateMachineTimeout!=InternalGetStateMachineTimeout)
		{
			return(false);
		}

		if (ActualValueStateMachineStartedEvent!=StateMachineStartedEvent)
		{
			return(false);
		}

		if (ActualValueStateMachineFinishedEvent!=StateMachineFinishedEvent)
		{
			return(false);
		}

		if (ActualValueStateMachineExpiredEvent!=StateMachineExpiredEvent)
		{
			return(false);
		}

		if (ActualValueStateMachineStateChangedEvent!=StateMachineStateChangedEvent)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiringEvent!=StateMachineStateOutputFiringEvent)
		{
			return(false);
		}

		if (ActualValueChildStateMachineAddedEvent!=ChildStateMachineAddedEvent)
		{
			return(false);
		}

		if (ActualValueChildStateMachineFinishedEvent!=ChildStateMachineFinishedEvent)
		{
			return(false);
		}

		if (ActualValueHasFinished!=HasFinished)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::CheckStateMachineState1(CSPTestStateMachine1 StateMachine, Size InternalGetStateMachineStartState, Size InternalExecuteStateMachine, Size StateMachineExecuteStateMachineStateInput1Event, Size StateMachineExecuteStateMachineStateInput2Event, Size StateMachineExecuteStateMachineStateInput3Event, Size StateMachineExecuteStateMachineStateInput4Event, Size InternalTerminateStateMachine, Size InternalGetStateMachineTimeout, Size StateMachineStartedEvent, Size StateMachineFinishedEvent)
	{
		Size													ActualValueInternalGetStateMachineStartState=StateMachine->GetInternalGetStateMachineStartState();
		Size													ActualValueInternalExecuteStateMachine=StateMachine->GetInternalExecuteStateMachine();
		Size													ActualValueStateMachineExecuteStateMachineStateInput1Event=StateMachine->GetStateMachineExecuteStateMachineStateInput1Event();
		Size													ActualValueStateMachineExecuteStateMachineStateInput2Event=StateMachine->GetStateMachineExecuteStateMachineStateInput2Event();
		Size													ActualValueStateMachineExecuteStateMachineStateInput3Event=StateMachine->GetStateMachineExecuteStateMachineStateInput3Event();
		Size													ActualValueStateMachineExecuteStateMachineStateInput4Event=StateMachine->GetStateMachineExecuteStateMachineStateInput4Event();
		Size													ActualValueInternalTerminateStateMachine=StateMachine->GetInternalTerminateStateMachine();
		Size													ActualValueInternalGetStateMachineTimeout=StateMachine->GetInternalGetStateMachineTimeout();
		Size													ActualValueStateMachineStartedEvent=StateMachine->GetStateMachineStartedEvent();
		Size													ActualValueStateMachineFinishedEvent=StateMachine->GetStateMachineFinishedEvent();

		if (ActualValueInternalGetStateMachineStartState!=InternalGetStateMachineStartState)
		{
			return(false);
		}

		if (ActualValueInternalExecuteStateMachine!=InternalExecuteStateMachine)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput1Event!=StateMachineExecuteStateMachineStateInput1Event)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput2Event!=StateMachineExecuteStateMachineStateInput2Event)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput3Event!=StateMachineExecuteStateMachineStateInput3Event)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput4Event!=StateMachineExecuteStateMachineStateInput4Event)
		{
			return(false);
		}

		if (ActualValueInternalTerminateStateMachine!=InternalTerminateStateMachine)
		{
			return(false);
		}

		if (ActualValueInternalGetStateMachineTimeout!=InternalGetStateMachineTimeout)
		{
			return(false);
		}

		if (ActualValueStateMachineStartedEvent!=StateMachineStartedEvent)
		{
			return(false);
		}

		if (ActualValueStateMachineFinishedEvent!=StateMachineFinishedEvent)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::CheckStateMachineState2(CSPTestStateMachine1 StateMachine, Size StateMachineExpiredEvent, Size StateMachineStateChangedEvent, Size StateMachineStateOutputFiringEvent, Size StateMachineStateOutputFiredStateOutput1Event, Size StateMachineStateOutputFiredStateOutput2Event, Size StateMachineStateOutputFiredStateOutput3Event, Size StateMachineStateOutputFiredStateOutput4Event, Size ChildStateMachineAddedEvent, Size ChildStateMachineFinishedEvent, bool HasFinished)
	{
		Size													ActualValueStateMachineExpiredEvent=StateMachine->GetStateMachineExpiredEvent();
		Size													ActualValueStateMachineStateChangedEvent=StateMachine->GetStateMachineStateChangedEvent();
		Size													ActualValueStateMachineStateOutputFiringEvent=StateMachine->GetStateMachineStateOutputFiringEvent();
		Size													ActualValueStateMachineStateOutputFiredStateOutput1Event=StateMachine->GetStateMachineStateOutputFiredStateOutput1Event();
		Size													ActualValueStateMachineStateOutputFiredStateOutput2Event=StateMachine->GetStateMachineStateOutputFiredStateOutput2Event();
		Size													ActualValueStateMachineStateOutputFiredStateOutput3Event=StateMachine->GetStateMachineStateOutputFiredStateOutput3Event();
		Size													ActualValueStateMachineStateOutputFiredStateOutput4Event=StateMachine->GetStateMachineStateOutputFiredStateOutput4Event();
		Size													ActualValueChildStateMachineAddedEvent=StateMachine->GetChildStateMachineAddedEvent();
		Size													ActualValueChildStateMachineFinishedEvent=StateMachine->GetChildStateMachineFinishedEvent();
		bool													ActualValueHasFinished=StateMachine->HasFinished();

		if (ActualValueStateMachineStateChangedEvent!=StateMachineStateChangedEvent)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiringEvent!=StateMachineStateOutputFiringEvent)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput1Event!=StateMachineStateOutputFiredStateOutput1Event)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput2Event!=StateMachineStateOutputFiredStateOutput2Event)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput3Event!=StateMachineStateOutputFiredStateOutput3Event)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput4Event!=StateMachineStateOutputFiredStateOutput4Event)
		{
			return(false);
		}

		if (ActualValueChildStateMachineAddedEvent!=ChildStateMachineAddedEvent)
		{
			return(false);
		}

		if (ActualValueChildStateMachineFinishedEvent!=ChildStateMachineFinishedEvent)
		{
			return(false);
		}

		if (ActualValueStateMachineExpiredEvent!=StateMachineExpiredEvent)
		{
			return(false);
		}

		if (ActualValueHasFinished!=HasFinished)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::CheckStateMachineState1(CSPTestStateMachine2 StateMachine, Size InternalGetStateMachineStartState, Size InternalExecuteStateMachine, Size StateMachineExecuteStateMachineStateInput1Event, Size StateMachineExecuteStateMachineStateInput2Event, Size StateMachineExecuteStateMachineStateInput3Event, Size StateMachineExecuteStateMachineStateInput4Event, Size InternalTerminateStateMachine, Size InternalGetStateMachineTimeout, Size StateMachineStartedEvent, Size StateMachineFinishedEvent)
	{
		Size													ActualValueInternalGetStateMachineStartState=StateMachine->GetInternalGetStateMachineStartState();
		Size													ActualValueInternalExecuteStateMachine=StateMachine->GetInternalExecuteStateMachine();
		Size													ActualValueStateMachineExecuteStateMachineStateInput1Event=StateMachine->GetStateMachineExecuteStateMachineStateInput1Event();
		Size													ActualValueStateMachineExecuteStateMachineStateInput2Event=StateMachine->GetStateMachineExecuteStateMachineStateInput2Event();
		Size													ActualValueStateMachineExecuteStateMachineStateInput3Event=StateMachine->GetStateMachineExecuteStateMachineStateInput3Event();
		Size													ActualValueStateMachineExecuteStateMachineStateInput4Event=StateMachine->GetStateMachineExecuteStateMachineStateInput4Event();
		Size													ActualValueInternalTerminateStateMachine=StateMachine->GetInternalTerminateStateMachine();
		Size													ActualValueInternalGetStateMachineTimeout=StateMachine->GetInternalGetStateMachineTimeout();
		Size													ActualValueStateMachineStartedEvent=StateMachine->GetStateMachineStartedEvent();
		Size													ActualValueStateMachineFinishedEvent=StateMachine->GetStateMachineFinishedEvent();

		if (ActualValueInternalGetStateMachineStartState!=InternalGetStateMachineStartState)
		{
			return(false);
		}

		if (ActualValueInternalExecuteStateMachine!=InternalExecuteStateMachine)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput1Event!=StateMachineExecuteStateMachineStateInput1Event)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput2Event!=StateMachineExecuteStateMachineStateInput2Event)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput3Event!=StateMachineExecuteStateMachineStateInput3Event)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput4Event!=StateMachineExecuteStateMachineStateInput4Event)
		{
			return(false);
		}

		if (ActualValueInternalTerminateStateMachine!=InternalTerminateStateMachine)
		{
			return(false);
		}

		if (ActualValueInternalGetStateMachineTimeout!=InternalGetStateMachineTimeout)
		{
			return(false);
		}

		if (ActualValueStateMachineStartedEvent!=StateMachineStartedEvent)
		{
			return(false);
		}

		if (ActualValueStateMachineFinishedEvent!=StateMachineFinishedEvent)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::CheckStateMachineState2(CSPTestStateMachine2 StateMachine, Size StateMachineExpiredEvent, Size StateMachineStateChangedEvent, Size StateMachineStateOutputFiringEvent, Size StateMachineStateOutputFiredStateOutput1Event, Size StateMachineStateOutputFiredStateOutput2Event, Size StateMachineStateOutputFiredStateOutput3Event, Size StateMachineStateOutputFiredStateOutput4Event, Size ChildStateMachineAddedEvent, Size ChildStateMachineFinishedEvent, bool HasFinished)
	{
		Size													ActualValueStateMachineExpiredEvent=StateMachine->GetStateMachineExpiredEvent();
		Size													ActualValueStateMachineStateChangedEvent=StateMachine->GetStateMachineStateChangedEvent();
		Size													ActualValueStateMachineStateOutputFiringEvent=StateMachine->GetStateMachineStateOutputFiringEvent();
		Size													ActualValueStateMachineStateOutputFiredStateOutput1Event=StateMachine->GetStateMachineStateOutputFiredStateOutput1Event();
		Size													ActualValueStateMachineStateOutputFiredStateOutput2Event=StateMachine->GetStateMachineStateOutputFiredStateOutput2Event();
		Size													ActualValueStateMachineStateOutputFiredStateOutput3Event=StateMachine->GetStateMachineStateOutputFiredStateOutput3Event();
		Size													ActualValueStateMachineStateOutputFiredStateOutput4Event=StateMachine->GetStateMachineStateOutputFiredStateOutput4Event();
		Size													ActualValueChildStateMachineAddedEvent=StateMachine->GetChildStateMachineAddedEvent();
		Size													ActualValueChildStateMachineFinishedEvent=StateMachine->GetChildStateMachineFinishedEvent();
		bool													ActualValueHasFinished=StateMachine->HasFinished();

		if (ActualValueStateMachineStateChangedEvent!=StateMachineStateChangedEvent)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiringEvent!=StateMachineStateOutputFiringEvent)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput1Event!=StateMachineStateOutputFiredStateOutput1Event)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput2Event!=StateMachineStateOutputFiredStateOutput2Event)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput3Event!=StateMachineStateOutputFiredStateOutput3Event)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput4Event!=StateMachineStateOutputFiredStateOutput4Event)
		{
			return(false);
		}

		if (ActualValueChildStateMachineAddedEvent!=ChildStateMachineAddedEvent)
		{
			return(false);
		}

		if (ActualValueChildStateMachineFinishedEvent!=ChildStateMachineFinishedEvent)
		{
			return(false);
		}

		if (ActualValueStateMachineExpiredEvent!=StateMachineExpiredEvent)
		{
			return(false);
		}

		if (ActualValueHasFinished!=HasFinished)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::CheckStateMachineState1(CSPTestStateMachine3 StateMachine, Size InternalGetStateMachineStartState, Size InternalExecuteStateMachine, Size StateMachineExecuteStateMachineStateInput1Event, Size StateMachineExecuteStateMachineStateInput2Event, Size StateMachineExecuteStateMachineStateInput3Event, Size StateMachineExecuteStateMachineStateInput4Event, Size InternalTerminateStateMachine, Size InternalGetStateMachineTimeout, Size StateMachineStartedEvent, Size StateMachineFinishedEvent)
	{
		Size													ActualValueInternalGetStateMachineStartState=StateMachine->GetInternalGetStateMachineStartState();
		Size													ActualValueInternalExecuteStateMachine=StateMachine->GetInternalExecuteStateMachine();
		Size													ActualValueStateMachineExecuteStateMachineStateInput1Event=StateMachine->GetStateMachineExecuteStateMachineStateInput1Event();
		Size													ActualValueStateMachineExecuteStateMachineStateInput2Event=StateMachine->GetStateMachineExecuteStateMachineStateInput2Event();
		Size													ActualValueStateMachineExecuteStateMachineStateInput3Event=StateMachine->GetStateMachineExecuteStateMachineStateInput3Event();
		Size													ActualValueStateMachineExecuteStateMachineStateInput4Event=StateMachine->GetStateMachineExecuteStateMachineStateInput4Event();
		Size													ActualValueInternalTerminateStateMachine=StateMachine->GetInternalTerminateStateMachine();
		Size													ActualValueInternalGetStateMachineTimeout=StateMachine->GetInternalGetStateMachineTimeout();
		Size													ActualValueStateMachineStartedEvent=StateMachine->GetStateMachineStartedEvent();
		Size													ActualValueStateMachineFinishedEvent=StateMachine->GetStateMachineFinishedEvent();

		if (ActualValueInternalGetStateMachineStartState!=InternalGetStateMachineStartState)
		{
			return(false);
		}

		if (ActualValueInternalExecuteStateMachine!=InternalExecuteStateMachine)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput1Event!=StateMachineExecuteStateMachineStateInput1Event)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput2Event!=StateMachineExecuteStateMachineStateInput2Event)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput3Event!=StateMachineExecuteStateMachineStateInput3Event)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput4Event!=StateMachineExecuteStateMachineStateInput4Event)
		{
			return(false);
		}

		if (ActualValueInternalTerminateStateMachine!=InternalTerminateStateMachine)
		{
			return(false);
		}

		if (ActualValueInternalGetStateMachineTimeout!=InternalGetStateMachineTimeout)
		{
			return(false);
		}

		if (ActualValueStateMachineStartedEvent!=StateMachineStartedEvent)
		{
			return(false);
		}

		if (ActualValueStateMachineFinishedEvent!=StateMachineFinishedEvent)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::CheckStateMachineState2(CSPTestStateMachine3 StateMachine, Size StateMachineExpiredEvent, Size StateMachineStateChangedEvent, Size StateMachineStateOutputFiringEvent, Size StateMachineStateOutputFiredStateOutput1Event, Size StateMachineStateOutputFiredStateOutput2Event, Size StateMachineStateOutputFiredStateOutput3Event, Size StateMachineStateOutputFiredStateOutput4Event, Size ChildStateMachineAddedEvent, Size ChildStateMachineFinishedEvent, bool HasFinished)
	{
		Size													ActualValueStateMachineExpiredEvent=StateMachine->GetStateMachineExpiredEvent();
		Size													ActualValueStateMachineStateChangedEvent=StateMachine->GetStateMachineStateChangedEvent();
		Size													ActualValueStateMachineStateOutputFiringEvent=StateMachine->GetStateMachineStateOutputFiringEvent();
		Size													ActualValueStateMachineStateOutputFiredStateOutput1Event=StateMachine->GetStateMachineStateOutputFiredStateOutput1Event();
		Size													ActualValueStateMachineStateOutputFiredStateOutput2Event=StateMachine->GetStateMachineStateOutputFiredStateOutput2Event();
		Size													ActualValueStateMachineStateOutputFiredStateOutput3Event=StateMachine->GetStateMachineStateOutputFiredStateOutput3Event();
		Size													ActualValueStateMachineStateOutputFiredStateOutput4Event=StateMachine->GetStateMachineStateOutputFiredStateOutput4Event();
		Size													ActualValueChildStateMachineAddedEvent=StateMachine->GetChildStateMachineAddedEvent();
		Size													ActualValueChildStateMachineFinishedEvent=StateMachine->GetChildStateMachineFinishedEvent();
		bool													ActualValueHasFinished=StateMachine->HasFinished();

		if (ActualValueStateMachineStateChangedEvent!=StateMachineStateChangedEvent)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiringEvent!=StateMachineStateOutputFiringEvent)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput1Event!=StateMachineStateOutputFiredStateOutput1Event)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput2Event!=StateMachineStateOutputFiredStateOutput2Event)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput3Event!=StateMachineStateOutputFiredStateOutput3Event)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput4Event!=StateMachineStateOutputFiredStateOutput4Event)
		{
			return(false);
		}

		if (ActualValueChildStateMachineAddedEvent!=ChildStateMachineAddedEvent)
		{
			return(false);
		}

		if (ActualValueChildStateMachineFinishedEvent!=ChildStateMachineFinishedEvent)
		{
			return(false);
		}

		if (ActualValueStateMachineExpiredEvent!=StateMachineExpiredEvent)
		{
			return(false);
		}

		if (ActualValueHasFinished!=HasFinished)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::CheckStateMachineState1(CSPTestStateMachine4 StateMachine, Size InternalGetStateMachineStartState, Size InternalExecuteStateMachine, Size StateMachineExecuteStateMachineStateInput1Event, Size StateMachineExecuteStateMachineStateInput2Event, Size StateMachineExecuteStateMachineStateInput3Event, Size StateMachineExecuteStateMachineStateInput4Event, Size InternalTerminateStateMachine, Size InternalGetStateMachineTimeout, Size StateMachineStartedEvent, Size StateMachineFinishedEvent)
	{
		Size													ActualValueInternalGetStateMachineStartState=StateMachine->GetInternalGetStateMachineStartState();
		Size													ActualValueInternalExecuteStateMachine=StateMachine->GetInternalExecuteStateMachine();
		Size													ActualValueStateMachineExecuteStateMachineStateInput1Event=StateMachine->GetStateMachineExecuteStateMachineStateInput1Event();
		Size													ActualValueStateMachineExecuteStateMachineStateInput2Event=StateMachine->GetStateMachineExecuteStateMachineStateInput2Event();
		Size													ActualValueStateMachineExecuteStateMachineStateInput3Event=StateMachine->GetStateMachineExecuteStateMachineStateInput3Event();
		Size													ActualValueStateMachineExecuteStateMachineStateInput4Event=StateMachine->GetStateMachineExecuteStateMachineStateInput4Event();
		Size													ActualValueInternalTerminateStateMachine=StateMachine->GetInternalTerminateStateMachine();
		Size													ActualValueInternalGetStateMachineTimeout=StateMachine->GetInternalGetStateMachineTimeout();
		Size													ActualValueStateMachineStartedEvent=StateMachine->GetStateMachineStartedEvent();
		Size													ActualValueStateMachineFinishedEvent=StateMachine->GetStateMachineFinishedEvent();

		if (ActualValueInternalGetStateMachineStartState!=InternalGetStateMachineStartState)
		{
			return(false);
		}

		if (ActualValueInternalExecuteStateMachine!=InternalExecuteStateMachine)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput1Event!=StateMachineExecuteStateMachineStateInput1Event)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput2Event!=StateMachineExecuteStateMachineStateInput2Event)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput3Event!=StateMachineExecuteStateMachineStateInput3Event)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput4Event!=StateMachineExecuteStateMachineStateInput4Event)
		{
			return(false);
		}

		if (ActualValueInternalTerminateStateMachine!=InternalTerminateStateMachine)
		{
			return(false);
		}

		if (ActualValueInternalGetStateMachineTimeout!=InternalGetStateMachineTimeout)
		{
			return(false);
		}

		if (ActualValueStateMachineStartedEvent!=StateMachineStartedEvent)
		{
			return(false);
		}

		if (ActualValueStateMachineFinishedEvent!=StateMachineFinishedEvent)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::CheckStateMachineState2(CSPTestStateMachine4 StateMachine, Size StateMachineExpiredEvent, Size StateMachineStateChangedEvent, Size StateMachineStateOutputFiringEvent, Size StateMachineStateOutputFiredStateOutput1Event, Size StateMachineStateOutputFiredStateOutput2Event, Size StateMachineStateOutputFiredStateOutput3Event, Size StateMachineStateOutputFiredStateOutput4Event, Size ChildStateMachineAddedEvent, Size ChildStateMachineFinishedEvent, bool HasFinished)
	{
		Size													ActualValueStateMachineExpiredEvent=StateMachine->GetStateMachineExpiredEvent();
		Size													ActualValueStateMachineStateChangedEvent=StateMachine->GetStateMachineStateChangedEvent();
		Size													ActualValueStateMachineStateOutputFiringEvent=StateMachine->GetStateMachineStateOutputFiringEvent();
		Size													ActualValueStateMachineStateOutputFiredStateOutput1Event=StateMachine->GetStateMachineStateOutputFiredStateOutput1Event();
		Size													ActualValueStateMachineStateOutputFiredStateOutput2Event=StateMachine->GetStateMachineStateOutputFiredStateOutput2Event();
		Size													ActualValueStateMachineStateOutputFiredStateOutput3Event=StateMachine->GetStateMachineStateOutputFiredStateOutput3Event();
		Size													ActualValueStateMachineStateOutputFiredStateOutput4Event=StateMachine->GetStateMachineStateOutputFiredStateOutput4Event();
		Size													ActualValueChildStateMachineAddedEvent=StateMachine->GetChildStateMachineAddedEvent();
		Size													ActualValueChildStateMachineFinishedEvent=StateMachine->GetChildStateMachineFinishedEvent();
		bool													ActualValueHasFinished=StateMachine->HasFinished();

		if (ActualValueStateMachineStateChangedEvent!=StateMachineStateChangedEvent)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiringEvent!=StateMachineStateOutputFiringEvent)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput1Event!=StateMachineStateOutputFiredStateOutput1Event)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput2Event!=StateMachineStateOutputFiredStateOutput2Event)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput3Event!=StateMachineStateOutputFiredStateOutput3Event)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput4Event!=StateMachineStateOutputFiredStateOutput4Event)
		{
			return(false);
		}

		if (ActualValueChildStateMachineAddedEvent!=ChildStateMachineAddedEvent)
		{
			return(false);
		}

		if (ActualValueChildStateMachineFinishedEvent!=ChildStateMachineFinishedEvent)
		{
			return(false);
		}

		if (ActualValueStateMachineExpiredEvent!=StateMachineExpiredEvent)
		{
			return(false);
		}

		if (ActualValueHasFinished!=HasFinished)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::CheckStateMachineState1(CSPTestStateMachineException1 StateMachine, Size InternalGetStateMachineStartState1, Size InternalGetStateMachineStartState2, Size InternalExecuteStateMachine1, Size InternalExecuteStateMachine2, Size StateMachineExecuteStateMachineStateInput1Event1, Size StateMachineExecuteStateMachineStateInput1Event2, Size StateMachineExecuteStateMachineStateInput2Event1, Size StateMachineExecuteStateMachineStateInput2Event2, Size StateMachineExecuteStateMachineStateInput3Event1, Size StateMachineExecuteStateMachineStateInput3Event2, Size StateMachineExecuteStateMachineStateInput4Event1, Size StateMachineExecuteStateMachineStateInput4Event2)
	{
		Size													ActualValueInternalGetStateMachineStartState1=StateMachine->GetInternalGetStateMachineStartState1();
		Size													ActualValueInternalGetStateMachineStartState2=StateMachine->GetInternalGetStateMachineStartState2();
		Size													ActualValueInternalExecuteStateMachine1=StateMachine->GetInternalExecuteStateMachine1();
		Size													ActualValueInternalExecuteStateMachine2=StateMachine->GetInternalExecuteStateMachine2();
		Size													ActualValueStateMachineExecuteStateMachineStateInput1Event1=StateMachine->GetStateMachineExecuteStateMachineStateInput1Event1();
		Size													ActualValueStateMachineExecuteStateMachineStateInput1Event2=StateMachine->GetStateMachineExecuteStateMachineStateInput1Event2();
		Size													ActualValueStateMachineExecuteStateMachineStateInput2Event1=StateMachine->GetStateMachineExecuteStateMachineStateInput2Event1();
		Size													ActualValueStateMachineExecuteStateMachineStateInput2Event2=StateMachine->GetStateMachineExecuteStateMachineStateInput2Event2();
		Size													ActualValueStateMachineExecuteStateMachineStateInput3Event1=StateMachine->GetStateMachineExecuteStateMachineStateInput3Event1();
		Size													ActualValueStateMachineExecuteStateMachineStateInput3Event2=StateMachine->GetStateMachineExecuteStateMachineStateInput3Event2();
		Size													ActualValueStateMachineExecuteStateMachineStateInput4Event1=StateMachine->GetStateMachineExecuteStateMachineStateInput4Event1();
		Size													ActualValueStateMachineExecuteStateMachineStateInput4Event2=StateMachine->GetStateMachineExecuteStateMachineStateInput4Event2();

		if (ActualValueInternalGetStateMachineStartState1!=InternalGetStateMachineStartState1)
		{
			return(false);
		}

		if (ActualValueInternalGetStateMachineStartState2!=InternalGetStateMachineStartState2)
		{
			return(false);
		}

		if (ActualValueInternalExecuteStateMachine1!=InternalExecuteStateMachine1)
		{
			return(false);
		}

		if (ActualValueInternalExecuteStateMachine2!=InternalExecuteStateMachine2)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput1Event1!=StateMachineExecuteStateMachineStateInput1Event1)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput1Event2!=StateMachineExecuteStateMachineStateInput1Event2)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput2Event1!=StateMachineExecuteStateMachineStateInput2Event1)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput2Event2!=StateMachineExecuteStateMachineStateInput2Event2)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput3Event1!=StateMachineExecuteStateMachineStateInput3Event1)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput3Event2!=StateMachineExecuteStateMachineStateInput3Event2)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput4Event1!=StateMachineExecuteStateMachineStateInput4Event1)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput4Event2!=StateMachineExecuteStateMachineStateInput4Event2)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::CheckStateMachineState2(CSPTestStateMachineException1 StateMachine, Size InternalTerminateStateMachine1, Size InternalTerminateStateMachine2, Size InternalGetStateMachineTimeout1, Size InternalGetStateMachineTimeout2, Size StateMachineStartedEvent1, Size StateMachineStartedEvent2, Size StateMachineFinishedEvent1, Size StateMachineFinishedEvent2, Size StateMachineExpiredEvent1, Size StateMachineExpiredEvent2, Size StateMachineStateChangedEvent1, Size StateMachineStateChangedEvent2)
	{
		Size													ActualValueInternalTerminateStateMachine1=StateMachine->GetInternalTerminateStateMachine1();
		Size													ActualValueInternalTerminateStateMachine2=StateMachine->GetInternalTerminateStateMachine2();
		Size													ActualValueInternalGetStateMachineTimeout1=StateMachine->GetInternalGetStateMachineTimeout1();
		Size													ActualValueInternalGetStateMachineTimeout2=StateMachine->GetInternalGetStateMachineTimeout2();
		Size													ActualValueStateMachineStartedEvent1=StateMachine->GetStateMachineStartedEvent1();
		Size													ActualValueStateMachineStartedEvent2=StateMachine->GetStateMachineStartedEvent2();
		Size													ActualValueStateMachineFinishedEvent1=StateMachine->GetStateMachineFinishedEvent1();
		Size													ActualValueStateMachineFinishedEvent2=StateMachine->GetStateMachineFinishedEvent2();
		Size													ActualValueStateMachineExpiredEvent1=StateMachine->GetStateMachineExpiredEvent1();
		Size													ActualValueStateMachineExpiredEvent2=StateMachine->GetStateMachineExpiredEvent2();
		Size													ActualValueStateMachineStateChangedEvent1=StateMachine->GetStateMachineStateChangedEvent1();
		Size													ActualValueStateMachineStateChangedEvent2=StateMachine->GetStateMachineStateChangedEvent2();

		if (ActualValueInternalTerminateStateMachine1!=InternalTerminateStateMachine1)
		{
			return(false);
		}

		if (ActualValueInternalTerminateStateMachine2!=InternalTerminateStateMachine2)
		{
			return(false);
		}

		if (ActualValueInternalGetStateMachineTimeout1!=InternalGetStateMachineTimeout1)
		{
			return(false);
		}

		if (ActualValueInternalGetStateMachineTimeout2!=InternalGetStateMachineTimeout2)
		{
			return(false);
		}

		if (ActualValueStateMachineStartedEvent1!=StateMachineStartedEvent1)
		{
			return(false);
		}

		if (ActualValueStateMachineStartedEvent2!=StateMachineStartedEvent2)
		{
			return(false);
		}

		if (ActualValueStateMachineFinishedEvent1!=StateMachineFinishedEvent1)
		{
			return(false);
		}

		if (ActualValueStateMachineFinishedEvent2!=StateMachineFinishedEvent2)
		{
			return(false);
		}

		if (ActualValueStateMachineExpiredEvent1!=StateMachineExpiredEvent1)
		{
			return(false);
		}

		if (ActualValueStateMachineExpiredEvent2!=StateMachineExpiredEvent2)
		{
			return(false);
		}

		if (ActualValueStateMachineStateChangedEvent1!=StateMachineStateChangedEvent1)
		{
			return(false);
		}

		if (ActualValueStateMachineStateChangedEvent2!=StateMachineStateChangedEvent2)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::CheckStateMachineState3(CSPTestStateMachineException1 StateMachine, Size StateMachineStateOutputFiringEvent1, Size StateMachineStateOutputFiringEvent2, Size StateMachineStateOutputFiredStateOutput1Event1, Size StateMachineStateOutputFiredStateOutput1Event2, Size StateMachineStateOutputFiredStateOutput2Event1, Size StateMachineStateOutputFiredStateOutput2Event2, Size StateMachineStateOutputFiredStateOutput3Event1, Size StateMachineStateOutputFiredStateOutput3Event2, Size StateMachineStateOutputFiredStateOutput4Event1, Size StateMachineStateOutputFiredStateOutput4Event2)
	{
		Size													ActualValueStateMachineStateOutputFiringEvent1=StateMachine->GetStateMachineStateOutputFiringEvent1();
		Size													ActualValueStateMachineStateOutputFiringEvent2=StateMachine->GetStateMachineStateOutputFiringEvent2();
		Size													ActualValueStateMachineStateOutputFiredStateOutput1Event1=StateMachine->GetStateMachineStateOutputFiredStateOutput1Event1();
		Size													ActualValueStateMachineStateOutputFiredStateOutput1Event2=StateMachine->GetStateMachineStateOutputFiredStateOutput1Event2();
		Size													ActualValueStateMachineStateOutputFiredStateOutput2Event1=StateMachine->GetStateMachineStateOutputFiredStateOutput2Event1();
		Size													ActualValueStateMachineStateOutputFiredStateOutput2Event2=StateMachine->GetStateMachineStateOutputFiredStateOutput2Event2();
		Size													ActualValueStateMachineStateOutputFiredStateOutput3Event1=StateMachine->GetStateMachineStateOutputFiredStateOutput3Event1();
		Size													ActualValueStateMachineStateOutputFiredStateOutput3Event2=StateMachine->GetStateMachineStateOutputFiredStateOutput3Event2();
		Size													ActualValueStateMachineStateOutputFiredStateOutput4Event1=StateMachine->GetStateMachineStateOutputFiredStateOutput4Event1();
		Size													ActualValueStateMachineStateOutputFiredStateOutput4Event2=StateMachine->GetStateMachineStateOutputFiredStateOutput4Event2();

		if (ActualValueStateMachineStateOutputFiringEvent1!=StateMachineStateOutputFiringEvent1)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiringEvent2!=StateMachineStateOutputFiringEvent2)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput1Event1!=StateMachineStateOutputFiredStateOutput1Event1)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput1Event2!=StateMachineStateOutputFiredStateOutput1Event2)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput2Event1!=StateMachineStateOutputFiredStateOutput2Event1)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput2Event2!=StateMachineStateOutputFiredStateOutput2Event2)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput3Event1!=StateMachineStateOutputFiredStateOutput3Event1)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput3Event2!=StateMachineStateOutputFiredStateOutput3Event2)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput4Event1!=StateMachineStateOutputFiredStateOutput4Event1)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput4Event2!=StateMachineStateOutputFiredStateOutput4Event2)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::CheckStateMachineState4(CSPTestStateMachineException1 StateMachine, Size ChildStateMachineAddedEvent1, Size ChildStateMachineAddedEvent2, Size ChildStateMachineFinishedEvent1, Size ChildStateMachineFinishedEvent2, bool HasFinished)
	{
		Size													ActualValueChildStateMachineAddedEvent1=StateMachine->GetChildStateMachineAddedEvent1();
		Size													ActualValueChildStateMachineAddedEvent2=StateMachine->GetChildStateMachineAddedEvent2();
		Size													ActualValueChildStateMachineFinishedEvent1=StateMachine->GetChildStateMachineFinishedEvent1();
		Size													ActualValueChildStateMachineFinishedEvent2=StateMachine->GetChildStateMachineFinishedEvent2();
		bool													ActualValueHasFinished=StateMachine->HasFinished();

		if (ActualValueChildStateMachineAddedEvent1!=ChildStateMachineAddedEvent1)
		{
			return(false);
		}

		if (ActualValueChildStateMachineAddedEvent2!=ChildStateMachineAddedEvent2)
		{
			return(false);
		}

		if (ActualValueChildStateMachineFinishedEvent1!=ChildStateMachineFinishedEvent1)
		{
			return(false);
		}

		if (ActualValueChildStateMachineFinishedEvent2!=ChildStateMachineFinishedEvent2)
		{
			return(false);
		}

		if (ActualValueHasFinished!=HasFinished)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::CheckStateMachineState1(CSPTestStateMachineException2 StateMachine, Size InternalGetStateMachineStartState1, Size InternalGetStateMachineStartState2, Size InternalExecuteStateMachine1, Size InternalExecuteStateMachine2, Size StateMachineExecuteStateMachineStateInput1Event1, Size StateMachineExecuteStateMachineStateInput1Event2, Size StateMachineExecuteStateMachineStateInput2Event1, Size StateMachineExecuteStateMachineStateInput2Event2, Size StateMachineExecuteStateMachineStateInput3Event1, Size StateMachineExecuteStateMachineStateInput3Event2, Size StateMachineExecuteStateMachineStateInput4Event1, Size StateMachineExecuteStateMachineStateInput4Event2)
	{
		Size													ActualValueInternalGetStateMachineStartState1=StateMachine->GetInternalGetStateMachineStartState1();
		Size													ActualValueInternalGetStateMachineStartState2=StateMachine->GetInternalGetStateMachineStartState2();
		Size													ActualValueInternalExecuteStateMachine1=StateMachine->GetInternalExecuteStateMachine1();
		Size													ActualValueInternalExecuteStateMachine2=StateMachine->GetInternalExecuteStateMachine2();
		Size													ActualValueStateMachineExecuteStateMachineStateInput1Event1=StateMachine->GetStateMachineExecuteStateMachineStateInput1Event1();
		Size													ActualValueStateMachineExecuteStateMachineStateInput1Event2=StateMachine->GetStateMachineExecuteStateMachineStateInput1Event2();
		Size													ActualValueStateMachineExecuteStateMachineStateInput2Event1=StateMachine->GetStateMachineExecuteStateMachineStateInput2Event1();
		Size													ActualValueStateMachineExecuteStateMachineStateInput2Event2=StateMachine->GetStateMachineExecuteStateMachineStateInput2Event2();
		Size													ActualValueStateMachineExecuteStateMachineStateInput3Event1=StateMachine->GetStateMachineExecuteStateMachineStateInput3Event1();
		Size													ActualValueStateMachineExecuteStateMachineStateInput3Event2=StateMachine->GetStateMachineExecuteStateMachineStateInput3Event2();
		Size													ActualValueStateMachineExecuteStateMachineStateInput4Event1=StateMachine->GetStateMachineExecuteStateMachineStateInput4Event1();
		Size													ActualValueStateMachineExecuteStateMachineStateInput4Event2=StateMachine->GetStateMachineExecuteStateMachineStateInput4Event2();

		if (ActualValueInternalGetStateMachineStartState1!=InternalGetStateMachineStartState1)
		{
			return(false);
		}

		if (ActualValueInternalGetStateMachineStartState2!=InternalGetStateMachineStartState2)
		{
			return(false);
		}

		if (ActualValueInternalExecuteStateMachine1!=InternalExecuteStateMachine1)
		{
			return(false);
		}

		if (ActualValueInternalExecuteStateMachine2!=InternalExecuteStateMachine2)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput1Event1!=StateMachineExecuteStateMachineStateInput1Event1)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput1Event2!=StateMachineExecuteStateMachineStateInput1Event2)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput2Event1!=StateMachineExecuteStateMachineStateInput2Event1)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput2Event2!=StateMachineExecuteStateMachineStateInput2Event2)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput3Event1!=StateMachineExecuteStateMachineStateInput3Event1)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput3Event2!=StateMachineExecuteStateMachineStateInput3Event2)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput4Event1!=StateMachineExecuteStateMachineStateInput4Event1)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput4Event2!=StateMachineExecuteStateMachineStateInput4Event2)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::CheckStateMachineState2(CSPTestStateMachineException2 StateMachine, Size InternalTerminateStateMachine1, Size InternalTerminateStateMachine2, Size InternalGetStateMachineTimeout1, Size InternalGetStateMachineTimeout2, Size StateMachineStartedEvent1, Size StateMachineStartedEvent2, Size StateMachineFinishedEvent1, Size StateMachineFinishedEvent2, Size StateMachineExpiredEvent1, Size StateMachineExpiredEvent2, Size StateMachineStateChangedEvent1, Size StateMachineStateChangedEvent2)
	{
		Size													ActualValueInternalTerminateStateMachine1=StateMachine->GetInternalTerminateStateMachine1();
		Size													ActualValueInternalTerminateStateMachine2=StateMachine->GetInternalTerminateStateMachine2();
		Size													ActualValueInternalGetStateMachineTimeout1=StateMachine->GetInternalGetStateMachineTimeout1();
		Size													ActualValueInternalGetStateMachineTimeout2=StateMachine->GetInternalGetStateMachineTimeout2();
		Size													ActualValueStateMachineStartedEvent1=StateMachine->GetStateMachineStartedEvent1();
		Size													ActualValueStateMachineStartedEvent2=StateMachine->GetStateMachineStartedEvent2();
		Size													ActualValueStateMachineFinishedEvent1=StateMachine->GetStateMachineFinishedEvent1();
		Size													ActualValueStateMachineFinishedEvent2=StateMachine->GetStateMachineFinishedEvent2();
		Size													ActualValueStateMachineExpiredEvent1=StateMachine->GetStateMachineExpiredEvent1();
		Size													ActualValueStateMachineExpiredEvent2=StateMachine->GetStateMachineExpiredEvent2();
		Size													ActualValueStateMachineStateChangedEvent1=StateMachine->GetStateMachineStateChangedEvent1();
		Size													ActualValueStateMachineStateChangedEvent2=StateMachine->GetStateMachineStateChangedEvent2();

		if (ActualValueInternalTerminateStateMachine1!=InternalTerminateStateMachine1)
		{
			return(false);
		}

		if (ActualValueInternalTerminateStateMachine2!=InternalTerminateStateMachine2)
		{
			return(false);
		}

		if (ActualValueInternalGetStateMachineTimeout1!=InternalGetStateMachineTimeout1)
		{
			return(false);
		}

		if (ActualValueInternalGetStateMachineTimeout2!=InternalGetStateMachineTimeout2)
		{
			return(false);
		}

		if (ActualValueStateMachineStartedEvent1!=StateMachineStartedEvent1)
		{
			return(false);
		}

		if (ActualValueStateMachineStartedEvent2!=StateMachineStartedEvent2)
		{
			return(false);
		}

		if (ActualValueStateMachineFinishedEvent1!=StateMachineFinishedEvent1)
		{
			return(false);
		}

		if (ActualValueStateMachineFinishedEvent2!=StateMachineFinishedEvent2)
		{
			return(false);
		}

		if (ActualValueStateMachineExpiredEvent1!=StateMachineExpiredEvent1)
		{
			return(false);
		}

		if (ActualValueStateMachineExpiredEvent2!=StateMachineExpiredEvent2)
		{
			return(false);
		}

		if (ActualValueStateMachineStateChangedEvent1!=StateMachineStateChangedEvent1)
		{
			return(false);
		}

		if (ActualValueStateMachineStateChangedEvent2!=StateMachineStateChangedEvent2)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::CheckStateMachineState3(CSPTestStateMachineException2 StateMachine, Size StateMachineStateOutputFiringEvent1, Size StateMachineStateOutputFiringEvent2, Size StateMachineStateOutputFiredStateOutput1Event1, Size StateMachineStateOutputFiredStateOutput1Event2, Size StateMachineStateOutputFiredStateOutput2Event1, Size StateMachineStateOutputFiredStateOutput2Event2, Size StateMachineStateOutputFiredStateOutput3Event1, Size StateMachineStateOutputFiredStateOutput3Event2, Size StateMachineStateOutputFiredStateOutput4Event1, Size StateMachineStateOutputFiredStateOutput4Event2)
	{
		Size													ActualValueStateMachineStateOutputFiringEvent1=StateMachine->GetStateMachineStateOutputFiringEvent1();
		Size													ActualValueStateMachineStateOutputFiringEvent2=StateMachine->GetStateMachineStateOutputFiringEvent2();
		Size													ActualValueStateMachineStateOutputFiredStateOutput1Event1=StateMachine->GetStateMachineStateOutputFiredStateOutput1Event1();
		Size													ActualValueStateMachineStateOutputFiredStateOutput1Event2=StateMachine->GetStateMachineStateOutputFiredStateOutput1Event2();
		Size													ActualValueStateMachineStateOutputFiredStateOutput2Event1=StateMachine->GetStateMachineStateOutputFiredStateOutput2Event1();
		Size													ActualValueStateMachineStateOutputFiredStateOutput2Event2=StateMachine->GetStateMachineStateOutputFiredStateOutput2Event2();
		Size													ActualValueStateMachineStateOutputFiredStateOutput3Event1=StateMachine->GetStateMachineStateOutputFiredStateOutput3Event1();
		Size													ActualValueStateMachineStateOutputFiredStateOutput3Event2=StateMachine->GetStateMachineStateOutputFiredStateOutput3Event2();
		Size													ActualValueStateMachineStateOutputFiredStateOutput4Event1=StateMachine->GetStateMachineStateOutputFiredStateOutput4Event1();
		Size													ActualValueStateMachineStateOutputFiredStateOutput4Event2=StateMachine->GetStateMachineStateOutputFiredStateOutput4Event2();

		if (ActualValueStateMachineStateOutputFiringEvent1!=StateMachineStateOutputFiringEvent1)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiringEvent2!=StateMachineStateOutputFiringEvent2)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput1Event1!=StateMachineStateOutputFiredStateOutput1Event1)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput1Event2!=StateMachineStateOutputFiredStateOutput1Event2)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput2Event1!=StateMachineStateOutputFiredStateOutput2Event1)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput2Event2!=StateMachineStateOutputFiredStateOutput2Event2)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput3Event1!=StateMachineStateOutputFiredStateOutput3Event1)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput3Event2!=StateMachineStateOutputFiredStateOutput3Event2)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput4Event1!=StateMachineStateOutputFiredStateOutput4Event1)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput4Event2!=StateMachineStateOutputFiredStateOutput4Event2)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::CheckStateMachineState4(CSPTestStateMachineException2 StateMachine, Size ChildStateMachineAddedEvent1, Size ChildStateMachineAddedEvent2, Size ChildStateMachineFinishedEvent1, Size ChildStateMachineFinishedEvent2, bool HasFinished)
	{
		Size													ActualValueChildStateMachineAddedEvent1=StateMachine->GetChildStateMachineAddedEvent1();
		Size													ActualValueChildStateMachineAddedEvent2=StateMachine->GetChildStateMachineAddedEvent2();
		Size													ActualValueChildStateMachineFinishedEvent1=StateMachine->GetChildStateMachineFinishedEvent1();
		Size													ActualValueChildStateMachineFinishedEvent2=StateMachine->GetChildStateMachineFinishedEvent2();
		bool													ActualValueHasFinished=StateMachine->HasFinished();

		if (ActualValueChildStateMachineAddedEvent1!=ChildStateMachineAddedEvent1)
		{
			return(false);
		}

		if (ActualValueChildStateMachineAddedEvent2!=ChildStateMachineAddedEvent2)
		{
			return(false);
		}

		if (ActualValueChildStateMachineFinishedEvent1!=ChildStateMachineFinishedEvent1)
		{
			return(false);
		}

		if (ActualValueChildStateMachineFinishedEvent2!=ChildStateMachineFinishedEvent2)
		{
			return(false);
		}

		if (ActualValueHasFinished!=HasFinished)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::CheckStateMachineState1(CSPTestStateMachineException3 StateMachine, Size InternalGetStateMachineStartState1, Size InternalGetStateMachineStartState2, Size InternalExecuteStateMachine1, Size InternalExecuteStateMachine2, Size StateMachineExecuteStateMachineStateInput1Event1, Size StateMachineExecuteStateMachineStateInput1Event2, Size StateMachineExecuteStateMachineStateInput2Event1, Size StateMachineExecuteStateMachineStateInput2Event2, Size StateMachineExecuteStateMachineStateInput3Event1, Size StateMachineExecuteStateMachineStateInput3Event2, Size StateMachineExecuteStateMachineStateInput4Event1, Size StateMachineExecuteStateMachineStateInput4Event2)
	{
		Size													ActualValueInternalGetStateMachineStartState1=StateMachine->GetInternalGetStateMachineStartState1();
		Size													ActualValueInternalGetStateMachineStartState2=StateMachine->GetInternalGetStateMachineStartState2();
		Size													ActualValueInternalExecuteStateMachine1=StateMachine->GetInternalExecuteStateMachine1();
		Size													ActualValueInternalExecuteStateMachine2=StateMachine->GetInternalExecuteStateMachine2();
		Size													ActualValueStateMachineExecuteStateMachineStateInput1Event1=StateMachine->GetStateMachineExecuteStateMachineStateInput1Event1();
		Size													ActualValueStateMachineExecuteStateMachineStateInput1Event2=StateMachine->GetStateMachineExecuteStateMachineStateInput1Event2();
		Size													ActualValueStateMachineExecuteStateMachineStateInput2Event1=StateMachine->GetStateMachineExecuteStateMachineStateInput2Event1();
		Size													ActualValueStateMachineExecuteStateMachineStateInput2Event2=StateMachine->GetStateMachineExecuteStateMachineStateInput2Event2();
		Size													ActualValueStateMachineExecuteStateMachineStateInput3Event1=StateMachine->GetStateMachineExecuteStateMachineStateInput3Event1();
		Size													ActualValueStateMachineExecuteStateMachineStateInput3Event2=StateMachine->GetStateMachineExecuteStateMachineStateInput3Event2();
		Size													ActualValueStateMachineExecuteStateMachineStateInput4Event1=StateMachine->GetStateMachineExecuteStateMachineStateInput4Event1();
		Size													ActualValueStateMachineExecuteStateMachineStateInput4Event2=StateMachine->GetStateMachineExecuteStateMachineStateInput4Event2();

		if (ActualValueInternalGetStateMachineStartState1!=InternalGetStateMachineStartState1)
		{
			return(false);
		}

		if (ActualValueInternalGetStateMachineStartState2!=InternalGetStateMachineStartState2)
		{
			return(false);
		}

		if (ActualValueInternalExecuteStateMachine1!=InternalExecuteStateMachine1)
		{
			return(false);
		}

		if (ActualValueInternalExecuteStateMachine2!=InternalExecuteStateMachine2)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput1Event1!=StateMachineExecuteStateMachineStateInput1Event1)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput1Event2!=StateMachineExecuteStateMachineStateInput1Event2)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput2Event1!=StateMachineExecuteStateMachineStateInput2Event1)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput2Event2!=StateMachineExecuteStateMachineStateInput2Event2)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput3Event1!=StateMachineExecuteStateMachineStateInput3Event1)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput3Event2!=StateMachineExecuteStateMachineStateInput3Event2)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput4Event1!=StateMachineExecuteStateMachineStateInput4Event1)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput4Event2!=StateMachineExecuteStateMachineStateInput4Event2)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::CheckStateMachineState2(CSPTestStateMachineException3 StateMachine, Size InternalTerminateStateMachine1, Size InternalTerminateStateMachine2, Size InternalGetStateMachineTimeout1, Size InternalGetStateMachineTimeout2, Size StateMachineStartedEvent1, Size StateMachineStartedEvent2, Size StateMachineFinishedEvent1, Size StateMachineFinishedEvent2, Size StateMachineExpiredEvent1, Size StateMachineExpiredEvent2, Size StateMachineStateChangedEvent1, Size StateMachineStateChangedEvent2)
	{
		Size													ActualValueInternalTerminateStateMachine1=StateMachine->GetInternalTerminateStateMachine1();
		Size													ActualValueInternalTerminateStateMachine2=StateMachine->GetInternalTerminateStateMachine2();
		Size													ActualValueInternalGetStateMachineTimeout1=StateMachine->GetInternalGetStateMachineTimeout1();
		Size													ActualValueInternalGetStateMachineTimeout2=StateMachine->GetInternalGetStateMachineTimeout2();
		Size													ActualValueStateMachineStartedEvent1=StateMachine->GetStateMachineStartedEvent1();
		Size													ActualValueStateMachineStartedEvent2=StateMachine->GetStateMachineStartedEvent2();
		Size													ActualValueStateMachineFinishedEvent1=StateMachine->GetStateMachineFinishedEvent1();
		Size													ActualValueStateMachineFinishedEvent2=StateMachine->GetStateMachineFinishedEvent2();
		Size													ActualValueStateMachineExpiredEvent1=StateMachine->GetStateMachineExpiredEvent1();
		Size													ActualValueStateMachineExpiredEvent2=StateMachine->GetStateMachineExpiredEvent2();
		Size													ActualValueStateMachineStateChangedEvent1=StateMachine->GetStateMachineStateChangedEvent1();
		Size													ActualValueStateMachineStateChangedEvent2=StateMachine->GetStateMachineStateChangedEvent2();

		if (ActualValueInternalTerminateStateMachine1!=InternalTerminateStateMachine1)
		{
			return(false);
		}

		if (ActualValueInternalTerminateStateMachine2!=InternalTerminateStateMachine2)
		{
			return(false);
		}

		if (ActualValueInternalGetStateMachineTimeout1!=InternalGetStateMachineTimeout1)
		{
			return(false);
		}

		if (ActualValueInternalGetStateMachineTimeout2!=InternalGetStateMachineTimeout2)
		{
			return(false);
		}

		if (ActualValueStateMachineStartedEvent1!=StateMachineStartedEvent1)
		{
			return(false);
		}

		if (ActualValueStateMachineStartedEvent2!=StateMachineStartedEvent2)
		{
			return(false);
		}

		if (ActualValueStateMachineFinishedEvent1!=StateMachineFinishedEvent1)
		{
			return(false);
		}

		if (ActualValueStateMachineFinishedEvent2!=StateMachineFinishedEvent2)
		{
			return(false);
		}

		if (ActualValueStateMachineExpiredEvent1!=StateMachineExpiredEvent1)
		{
			return(false);
		}

		if (ActualValueStateMachineExpiredEvent2!=StateMachineExpiredEvent2)
		{
			return(false);
		}

		if (ActualValueStateMachineStateChangedEvent1!=StateMachineStateChangedEvent1)
		{
			return(false);
		}

		if (ActualValueStateMachineStateChangedEvent2!=StateMachineStateChangedEvent2)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::CheckStateMachineState3(CSPTestStateMachineException3 StateMachine, Size StateMachineStateOutputFiringEvent1, Size StateMachineStateOutputFiringEvent2, Size StateMachineStateOutputFiredStateOutput1Event1, Size StateMachineStateOutputFiredStateOutput1Event2, Size StateMachineStateOutputFiredStateOutput2Event1, Size StateMachineStateOutputFiredStateOutput2Event2, Size StateMachineStateOutputFiredStateOutput3Event1, Size StateMachineStateOutputFiredStateOutput3Event2, Size StateMachineStateOutputFiredStateOutput4Event1, Size StateMachineStateOutputFiredStateOutput4Event2)
	{
		Size													ActualValueStateMachineStateOutputFiringEvent1=StateMachine->GetStateMachineStateOutputFiringEvent1();
		Size													ActualValueStateMachineStateOutputFiringEvent2=StateMachine->GetStateMachineStateOutputFiringEvent2();
		Size													ActualValueStateMachineStateOutputFiredStateOutput1Event1=StateMachine->GetStateMachineStateOutputFiredStateOutput1Event1();
		Size													ActualValueStateMachineStateOutputFiredStateOutput1Event2=StateMachine->GetStateMachineStateOutputFiredStateOutput1Event2();
		Size													ActualValueStateMachineStateOutputFiredStateOutput2Event1=StateMachine->GetStateMachineStateOutputFiredStateOutput2Event1();
		Size													ActualValueStateMachineStateOutputFiredStateOutput2Event2=StateMachine->GetStateMachineStateOutputFiredStateOutput2Event2();
		Size													ActualValueStateMachineStateOutputFiredStateOutput3Event1=StateMachine->GetStateMachineStateOutputFiredStateOutput3Event1();
		Size													ActualValueStateMachineStateOutputFiredStateOutput3Event2=StateMachine->GetStateMachineStateOutputFiredStateOutput3Event2();
		Size													ActualValueStateMachineStateOutputFiredStateOutput4Event1=StateMachine->GetStateMachineStateOutputFiredStateOutput4Event1();
		Size													ActualValueStateMachineStateOutputFiredStateOutput4Event2=StateMachine->GetStateMachineStateOutputFiredStateOutput4Event2();

		if (ActualValueStateMachineStateOutputFiringEvent1!=StateMachineStateOutputFiringEvent1)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiringEvent2!=StateMachineStateOutputFiringEvent2)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput1Event1!=StateMachineStateOutputFiredStateOutput1Event1)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput1Event2!=StateMachineStateOutputFiredStateOutput1Event2)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput2Event1!=StateMachineStateOutputFiredStateOutput2Event1)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput2Event2!=StateMachineStateOutputFiredStateOutput2Event2)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput3Event1!=StateMachineStateOutputFiredStateOutput3Event1)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput3Event2!=StateMachineStateOutputFiredStateOutput3Event2)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput4Event1!=StateMachineStateOutputFiredStateOutput4Event1)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput4Event2!=StateMachineStateOutputFiredStateOutput4Event2)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::CheckStateMachineState4(CSPTestStateMachineException3 StateMachine, Size ChildStateMachineAddedEvent1, Size ChildStateMachineAddedEvent2, Size ChildStateMachineFinishedEvent1, Size ChildStateMachineFinishedEvent2, bool HasFinished)
	{
		Size													ActualValueChildStateMachineAddedEvent1=StateMachine->GetChildStateMachineAddedEvent1();
		Size													ActualValueChildStateMachineAddedEvent2=StateMachine->GetChildStateMachineAddedEvent2();
		Size													ActualValueChildStateMachineFinishedEvent1=StateMachine->GetChildStateMachineFinishedEvent1();
		Size													ActualValueChildStateMachineFinishedEvent2=StateMachine->GetChildStateMachineFinishedEvent2();
		bool													ActualValueHasFinished=StateMachine->HasFinished();

		if (ActualValueChildStateMachineAddedEvent1!=ChildStateMachineAddedEvent1)
		{
			return(false);
		}

		if (ActualValueChildStateMachineAddedEvent2!=ChildStateMachineAddedEvent2)
		{
			return(false);
		}

		if (ActualValueChildStateMachineFinishedEvent1!=ChildStateMachineFinishedEvent1)
		{
			return(false);
		}

		if (ActualValueChildStateMachineFinishedEvent2!=ChildStateMachineFinishedEvent2)
		{
			return(false);
		}

		if (ActualValueHasFinished!=HasFinished)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::CheckStateMachineState1(CSPTestStateMachineException4 StateMachine, Size InternalGetStateMachineStartState1, Size InternalGetStateMachineStartState2, Size InternalExecuteStateMachine1, Size InternalExecuteStateMachine2, Size StateMachineExecuteStateMachineStateInput1Event1, Size StateMachineExecuteStateMachineStateInput1Event2, Size StateMachineExecuteStateMachineStateInput2Event1, Size StateMachineExecuteStateMachineStateInput2Event2, Size StateMachineExecuteStateMachineStateInput3Event1, Size StateMachineExecuteStateMachineStateInput3Event2, Size StateMachineExecuteStateMachineStateInput4Event1, Size StateMachineExecuteStateMachineStateInput4Event2)
	{
		Size													ActualValueInternalGetStateMachineStartState1=StateMachine->GetInternalGetStateMachineStartState1();
		Size													ActualValueInternalGetStateMachineStartState2=StateMachine->GetInternalGetStateMachineStartState2();
		Size													ActualValueInternalExecuteStateMachine1=StateMachine->GetInternalExecuteStateMachine1();
		Size													ActualValueInternalExecuteStateMachine2=StateMachine->GetInternalExecuteStateMachine2();
		Size													ActualValueStateMachineExecuteStateMachineStateInput1Event1=StateMachine->GetStateMachineExecuteStateMachineStateInput1Event1();
		Size													ActualValueStateMachineExecuteStateMachineStateInput1Event2=StateMachine->GetStateMachineExecuteStateMachineStateInput1Event2();
		Size													ActualValueStateMachineExecuteStateMachineStateInput2Event1=StateMachine->GetStateMachineExecuteStateMachineStateInput2Event1();
		Size													ActualValueStateMachineExecuteStateMachineStateInput2Event2=StateMachine->GetStateMachineExecuteStateMachineStateInput2Event2();
		Size													ActualValueStateMachineExecuteStateMachineStateInput3Event1=StateMachine->GetStateMachineExecuteStateMachineStateInput3Event1();
		Size													ActualValueStateMachineExecuteStateMachineStateInput3Event2=StateMachine->GetStateMachineExecuteStateMachineStateInput3Event2();
		Size													ActualValueStateMachineExecuteStateMachineStateInput4Event1=StateMachine->GetStateMachineExecuteStateMachineStateInput4Event1();
		Size													ActualValueStateMachineExecuteStateMachineStateInput4Event2=StateMachine->GetStateMachineExecuteStateMachineStateInput4Event2();

		if (ActualValueInternalGetStateMachineStartState1!=InternalGetStateMachineStartState1)
		{
			return(false);
		}

		if (ActualValueInternalGetStateMachineStartState2!=InternalGetStateMachineStartState2)
		{
			return(false);
		}

		if (ActualValueInternalExecuteStateMachine1!=InternalExecuteStateMachine1)
		{
			return(false);
		}

		if (ActualValueInternalExecuteStateMachine2!=InternalExecuteStateMachine2)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput1Event1!=StateMachineExecuteStateMachineStateInput1Event1)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput1Event2!=StateMachineExecuteStateMachineStateInput1Event2)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput2Event1!=StateMachineExecuteStateMachineStateInput2Event1)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput2Event2!=StateMachineExecuteStateMachineStateInput2Event2)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput3Event1!=StateMachineExecuteStateMachineStateInput3Event1)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput3Event2!=StateMachineExecuteStateMachineStateInput3Event2)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput4Event1!=StateMachineExecuteStateMachineStateInput4Event1)
		{
			return(false);
		}

		if (ActualValueStateMachineExecuteStateMachineStateInput4Event2!=StateMachineExecuteStateMachineStateInput4Event2)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::CheckStateMachineState2(CSPTestStateMachineException4 StateMachine, Size InternalTerminateStateMachine1, Size InternalTerminateStateMachine2, Size InternalGetStateMachineTimeout1, Size InternalGetStateMachineTimeout2, Size StateMachineStartedEvent1, Size StateMachineStartedEvent2, Size StateMachineFinishedEvent1, Size StateMachineFinishedEvent2, Size StateMachineExpiredEvent1, Size StateMachineExpiredEvent2, Size StateMachineStateChangedEvent1, Size StateMachineStateChangedEvent2)
	{
		Size													ActualValueInternalTerminateStateMachine1=StateMachine->GetInternalTerminateStateMachine1();
		Size													ActualValueInternalTerminateStateMachine2=StateMachine->GetInternalTerminateStateMachine2();
		Size													ActualValueInternalGetStateMachineTimeout1=StateMachine->GetInternalGetStateMachineTimeout1();
		Size													ActualValueInternalGetStateMachineTimeout2=StateMachine->GetInternalGetStateMachineTimeout2();
		Size													ActualValueStateMachineStartedEvent1=StateMachine->GetStateMachineStartedEvent1();
		Size													ActualValueStateMachineStartedEvent2=StateMachine->GetStateMachineStartedEvent2();
		Size													ActualValueStateMachineFinishedEvent1=StateMachine->GetStateMachineFinishedEvent1();
		Size													ActualValueStateMachineFinishedEvent2=StateMachine->GetStateMachineFinishedEvent2();
		Size													ActualValueStateMachineExpiredEvent1=StateMachine->GetStateMachineExpiredEvent1();
		Size													ActualValueStateMachineExpiredEvent2=StateMachine->GetStateMachineExpiredEvent2();
		Size													ActualValueStateMachineStateChangedEvent1=StateMachine->GetStateMachineStateChangedEvent1();
		Size													ActualValueStateMachineStateChangedEvent2=StateMachine->GetStateMachineStateChangedEvent2();

		if (ActualValueInternalTerminateStateMachine1!=InternalTerminateStateMachine1)
		{
			return(false);
		}

		if (ActualValueInternalTerminateStateMachine2!=InternalTerminateStateMachine2)
		{
			return(false);
		}

		if (ActualValueInternalGetStateMachineTimeout1!=InternalGetStateMachineTimeout1)
		{
			return(false);
		}

		if (ActualValueInternalGetStateMachineTimeout2!=InternalGetStateMachineTimeout2)
		{
			return(false);
		}

		if (ActualValueStateMachineStartedEvent1!=StateMachineStartedEvent1)
		{
			return(false);
		}

		if (ActualValueStateMachineStartedEvent2!=StateMachineStartedEvent2)
		{
			return(false);
		}

		if (ActualValueStateMachineFinishedEvent1!=StateMachineFinishedEvent1)
		{
			return(false);
		}

		if (ActualValueStateMachineFinishedEvent2!=StateMachineFinishedEvent2)
		{
			return(false);
		}

		if (ActualValueStateMachineExpiredEvent1!=StateMachineExpiredEvent1)
		{
			return(false);
		}

		if (ActualValueStateMachineExpiredEvent2!=StateMachineExpiredEvent2)
		{
			return(false);
		}

		if (ActualValueStateMachineStateChangedEvent1!=StateMachineStateChangedEvent1)
		{
			return(false);
		}

		if (ActualValueStateMachineStateChangedEvent2!=StateMachineStateChangedEvent2)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::CheckStateMachineState3(CSPTestStateMachineException4 StateMachine, Size StateMachineStateOutputFiringEvent1, Size StateMachineStateOutputFiringEvent2, Size StateMachineStateOutputFiredStateOutput1Event1, Size StateMachineStateOutputFiredStateOutput1Event2, Size StateMachineStateOutputFiredStateOutput2Event1, Size StateMachineStateOutputFiredStateOutput2Event2, Size StateMachineStateOutputFiredStateOutput3Event1, Size StateMachineStateOutputFiredStateOutput3Event2, Size StateMachineStateOutputFiredStateOutput4Event1, Size StateMachineStateOutputFiredStateOutput4Event2)
	{
		Size													ActualValueStateMachineStateOutputFiringEvent1=StateMachine->GetStateMachineStateOutputFiringEvent1();
		Size													ActualValueStateMachineStateOutputFiringEvent2=StateMachine->GetStateMachineStateOutputFiringEvent2();
		Size													ActualValueStateMachineStateOutputFiredStateOutput1Event1=StateMachine->GetStateMachineStateOutputFiredStateOutput1Event1();
		Size													ActualValueStateMachineStateOutputFiredStateOutput1Event2=StateMachine->GetStateMachineStateOutputFiredStateOutput1Event2();
		Size													ActualValueStateMachineStateOutputFiredStateOutput2Event1=StateMachine->GetStateMachineStateOutputFiredStateOutput2Event1();
		Size													ActualValueStateMachineStateOutputFiredStateOutput2Event2=StateMachine->GetStateMachineStateOutputFiredStateOutput2Event2();
		Size													ActualValueStateMachineStateOutputFiredStateOutput3Event1=StateMachine->GetStateMachineStateOutputFiredStateOutput3Event1();
		Size													ActualValueStateMachineStateOutputFiredStateOutput3Event2=StateMachine->GetStateMachineStateOutputFiredStateOutput3Event2();
		Size													ActualValueStateMachineStateOutputFiredStateOutput4Event1=StateMachine->GetStateMachineStateOutputFiredStateOutput4Event1();
		Size													ActualValueStateMachineStateOutputFiredStateOutput4Event2=StateMachine->GetStateMachineStateOutputFiredStateOutput4Event2();

		if (ActualValueStateMachineStateOutputFiringEvent1!=StateMachineStateOutputFiringEvent1)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiringEvent2!=StateMachineStateOutputFiringEvent2)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput1Event1!=StateMachineStateOutputFiredStateOutput1Event1)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput1Event2!=StateMachineStateOutputFiredStateOutput1Event2)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput2Event1!=StateMachineStateOutputFiredStateOutput2Event1)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput2Event2!=StateMachineStateOutputFiredStateOutput2Event2)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput3Event1!=StateMachineStateOutputFiredStateOutput3Event1)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput3Event2!=StateMachineStateOutputFiredStateOutput3Event2)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput4Event1!=StateMachineStateOutputFiredStateOutput4Event1)
		{
			return(false);
		}

		if (ActualValueStateMachineStateOutputFiredStateOutput4Event2!=StateMachineStateOutputFiredStateOutput4Event2)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::CheckStateMachineState4(CSPTestStateMachineException4 StateMachine, Size ChildStateMachineAddedEvent1, Size ChildStateMachineAddedEvent2, Size ChildStateMachineFinishedEvent1, Size ChildStateMachineFinishedEvent2, bool HasFinished)
	{
		Size													ActualValueChildStateMachineAddedEvent1=StateMachine->GetChildStateMachineAddedEvent1();
		Size													ActualValueChildStateMachineAddedEvent2=StateMachine->GetChildStateMachineAddedEvent2();
		Size													ActualValueChildStateMachineFinishedEvent1=StateMachine->GetChildStateMachineFinishedEvent1();
		Size													ActualValueChildStateMachineFinishedEvent2=StateMachine->GetChildStateMachineFinishedEvent2();
		bool													ActualValueHasFinished=StateMachine->HasFinished();

		if (ActualValueChildStateMachineAddedEvent1!=ChildStateMachineAddedEvent1)
		{
			return(false);
		}

		if (ActualValueChildStateMachineAddedEvent2!=ChildStateMachineAddedEvent2)
		{
			return(false);
		}

		if (ActualValueChildStateMachineFinishedEvent1!=ChildStateMachineFinishedEvent1)
		{
			return(false);
		}

		if (ActualValueChildStateMachineFinishedEvent2!=ChildStateMachineFinishedEvent2)
		{
			return(false);
		}

		if (ActualValueHasFinished!=HasFinished)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestHelperMethods(void)
	{
		try
		{
			Reset();

			CSPTestStateMachineBasicTests						StateMachine(new CTestStateMachineBasicTests(*this,*this,CSPTestStateMachineSettingsBasicTests(new CTestStateMachineSettingsBasicTests(CStateMachineID(),CPriority(100),CTimeout(10*1000*1000),CExpirationTime(),true,true,true,true,true,true,true,true)),nullptr));
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(false)));

			StateMachine->TestHelperMethods();

			Processor.TestGetStateMachinesProcessorName();
			Processor.TestGetStateMachinesProcessorSettings();

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestBasicTestsStateMachine1(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID("SM");
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSteadyClock::Milliseconds							CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();
			CSPTestStateMachineBasicTests						StateMachine(new CTestStateMachineBasicTests(*this,*this,CSPTestStateMachineSettingsBasicTests(new CTestStateMachineSettingsBasicTests(StateMachineID,CPriority(100),CTimeout(10*1000*1000),CExpirationTime(),true,true,true,true,true,true,true,true)),nullptr));

			Processor.AddStateMachine(StateMachine);

			Processor.ExecuteStateMachines();

			CTimeout											Timeout1=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID,CTestStateMachineBasicTests::MStateFinished,false)));

			CTimeout											Timeout2=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.ExecuteStateMachines();

			CTimeout											Timeout3=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			if (CheckStateMachineTimeout(Timeout1,false,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout2,true,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout3,true,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineState(StateMachine,1,3,0,1,1,1,0,2,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=0)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestBasicTestsStateMachine2(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID("SM");
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSteadyClock::Milliseconds							CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();
			CSPTestStateMachineBasicTests						StateMachine(new CTestStateMachineBasicTests(*this,*this,CSPTestStateMachineSettingsBasicTests(new CTestStateMachineSettingsBasicTests(StateMachineID,CPriority(100),CTimeout(10*1000*1000),CExpirationTime(),true,true,true,true,true,true,true,true)),nullptr));

			Processor.AddStateMachine(StateMachine);

			Processor.ExecuteStateMachines();

			CTimeout											Timeout1=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.TerminateStateMachines();

			CTimeout											Timeout2=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.ExecuteStateMachines();

			CTimeout											Timeout3=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			if (CheckStateMachineTimeout(Timeout1,false,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout2,true,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout3,false,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState(StateMachine,1,2,1,1,1,1,0,2,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=0)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestBasicTestsStateMachine3(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID("SM");
			CTimeout											StateMachineTimeout(1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSteadyClock::Milliseconds							CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();
			CSPTestStateMachineBasicTests						StateMachine(new CTestStateMachineBasicTests(*this,*this,CSPTestStateMachineSettingsBasicTests(new CTestStateMachineSettingsBasicTests(StateMachineID,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true)),nullptr));

			Processor.AddStateMachine(StateMachine);

			Processor.ExecuteStateMachines();

			CTimeout											Timeout1=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			// Wait for STATE MACHINE EXPIRATION.
			CThread::Sleep(static_cast<uint64>(StateMachineTimeout.GetTimeoutInMS()));

			CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();

			CTimeout											Timeout2=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.ExecuteStateMachines();

			CTimeout											Timeout3=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			if (CheckStateMachineTimeout(Timeout1,false,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout2,true,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout3,true,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineState(StateMachine,1,2,1,2,1,1,1,2,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=0)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestBasicTestsStateMachineInvalidState(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID("SM");
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSteadyClock::Milliseconds							CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();
			CSPTestStateMachineBasicTests						StateMachine(new CTestStateMachineBasicTests(*this,*this,CSPTestStateMachineSettingsBasicTests(new CTestStateMachineSettingsBasicTests(StateMachineID,CPriority(100),CTimeout(10*1000*1000),CExpirationTime(),true,true,true,true,true,true,true,true)),nullptr));

			Processor.AddStateMachine(StateMachine);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID,CTestStateMachineBasicTests::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			StateMachine->ExecuteStateMachine(nullptr);

			CTimeout											Timeout=StateMachine->GetStateMachineTimeout(CurrentTimeInMS);

			if (CheckStateMachineTimeout(Timeout,true,false)==false)
			{
				return(false);
			}

			StateMachine->StartStateMachine();

			StateMachine->TerminateStateMachine();

			if (CheckStateMachineState(StateMachine,1,3,0,0,1,1,0,2,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=3)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestBasicTestsStateMachineInvalidChangeState(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID("SM");
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSteadyClock::Milliseconds							CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();
			CSPTestStateMachineBasicTests						StateMachine(new CTestStateMachineBasicTests(*this,*this,CSPTestStateMachineSettingsBasicTests(new CTestStateMachineSettingsBasicTests(StateMachineID,CPriority(100),CTimeout(10*1000*1000),CExpirationTime(),true,true,true,true,true,true,true,true)),nullptr));

			Processor.AddStateMachine(StateMachine);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID,CTestStateMachineBasicTests::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			// Change to the SAME STATE.
			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID,CTestStateMachineBasicTests::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			// Change to the SAME STATE.
			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID,CTestStateMachineBasicTests::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			CTimeout											Timeout1=StateMachine->GetStateMachineTimeout(CurrentTimeInMS);

			// Change to the SAME STATE. EMPTY REASON. EXECUTE IMMEDIATELY.
			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID,CTestStateMachineBasicTests::MStateRunning,true,"")));

			CTimeout											Timeout2=StateMachine->GetStateMachineTimeout(CurrentTimeInMS);

			Processor.ExecuteStateMachines();

			// Must return ZERO, because STATE MACHINE asked STATE MACHINE PROCESSOR for IMMEDIATE EXECUTION.
			CTimeout											Timeout3=StateMachine->GetStateMachineTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID,CTestStateMachineBasicTests::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (CheckStateMachineTimeout(Timeout1,false,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout2,false,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout3,true,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineState(StateMachine,1,11,0,2,1,1,0,3,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=0)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestBasicTestsStateMachineStateInput1(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID("SM");
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSteadyClock::Milliseconds							CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();
			CSPTestStateMachineBasicTests						StateMachine(new CTestStateMachineBasicTests(*this,*this,CSPTestStateMachineSettingsBasicTests(new CTestStateMachineSettingsBasicTests(StateMachineID,CPriority(100),CTimeout(10*1000*1000),CExpirationTime(),true,true,true,true,true,true,true,true)),nullptr));

			Processor.AddStateMachine(StateMachine);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID,CTestStateMachineBasicTests::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInput1(StateMachineID,"STATE 1")));

			CTimeout											Timeout1=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInput2(StateMachineID,"STATE 2")));

			CTimeout											Timeout2=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInput3(StateMachineID,"STATE 3")));

			CTimeout											Timeout3=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInput4(StateMachineID,"STATE 4")));

			CTimeout											Timeout4=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID,CTestStateMachineBasicTests::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (CheckStateMachineTimeout(Timeout1,true,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout2,true,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout3,true,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout4,true,false)==false)
			{
				return(false);
			}

			if (StateMachine->GetStateInputProcessedStateInput1()!=1)
			{
				return(false);
			}

			if (StateMachine->GetStateInputProcessedStateInput2()!=1)
			{
				return(false);
			}

			if (StateMachine->GetStateInputProcessedStateInput3()!=1)
			{
				return(false);
			}

			if (StateMachine->GetStateInputProcessedStateInput4()!=1)
			{
				return(false);
			}

			if (CheckStateMachineState(StateMachine,1,13,0,0,1,1,0,3,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=0)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestBasicTestsStateMachineStateInput2(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID("SM");
			CStateMachineID										StateMachineIDInvalid("INVALID SM");
			CStateMachineID										StateMachineIDEmpty("");
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSPTestStateMachineBasicTests						StateMachine(new CTestStateMachineBasicTests(*this,*this,CSPTestStateMachineSettingsBasicTests(new CTestStateMachineSettingsBasicTests(StateMachineID,CPriority(100),CTimeout(10*1000*1000),CExpirationTime(),true,true,true,true,true,true,true,true)),nullptr));

			Processor.AddStateMachine(StateMachine);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID,CTestStateMachineBasicTests::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInput1(StateMachineIDInvalid,"STATE 1")));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInput2(StateMachineIDEmpty,"STATE 2")));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputUnsupported(StateMachineID,"STATE UNSUPPORTED")));

			Processor.ExecuteStateMachines();

			// STATE INPUT with INVALID STATE MACHINE ID is DIRECTLY SENT to STATE MACHINE.
			StateMachine->ExecuteStateMachine(CSPStateInput(new CStateInput1(StateMachineIDInvalid,"STATE 1 DIRECTLY SENT")));

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID,CTestStateMachineBasicTests::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (StateMachine->GetStateInputProcessedStateInput1()!=0)
			{
				return(false);
			}

			if (CheckStateMachineState(StateMachine,1,10,0,0,1,1,0,3,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=4)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestBasicTestsStateMachineStateOutput(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID("SM");
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSPTestStateMachineBasicTests						StateMachine(new CTestStateMachineBasicTests(*this,*this,CSPTestStateMachineSettingsBasicTests(new CTestStateMachineSettingsBasicTests(StateMachineID,CPriority(100),CTimeout(10*1000*1000),CExpirationTime(),true,true,true,true,true,true,true,true)),nullptr));

			Processor.AddStateMachine(StateMachine);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID,CTestStateMachineBasicTests::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInputSendStateOutput(new CStateInputSendStateOutput(StateMachineID,StateMachineID,CSPStateOutput(new CStateOutput1(StateMachineID,"STATE 1")))));
				
			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInputSendStateOutput(new CStateInputSendStateOutput(StateMachineID,StateMachineID,CSPStateOutput(new CStateOutput2(StateMachineID,"STATE 2")))));
				
			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInputSendStateOutput(new CStateInputSendStateOutput(StateMachineID,StateMachineID,CSPStateOutput(new CStateOutput3(StateMachineID,"STATE 3")))));
				
			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInputSendStateOutput(new CStateInputSendStateOutput(StateMachineID,StateMachineID,CSPStateOutput(new CStateOutput4(StateMachineID,"STATE 4")))));
				
			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID,CTestStateMachineBasicTests::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (MOutputCollection.GetLength()!=4)
			{
				return(false);
			}

			if (CheckStateMachineState(StateMachine,1,13,0,0,1,1,0,3,4,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=0)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestExceptionStateMachineTerminated(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID("SM");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSteadyClock::Milliseconds							CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();
			CSPTestStateMachineExceptionSettings1				Settings(new CTestStateMachineExceptionSettings1(StateMachineID,CPriority(100),StateMachineTimeout,CTestStateMachineExceptionSettings(CTimeout(StateMachineTimeout)),CExpirationTime()));
			CSPTestStateMachineException1						StateMachine(new CTestStateMachineException1(*this,*this,Settings,nullptr));

			Processor.AddStateMachine(StateMachine);

			Processor.ExecuteStateMachines();

			StateMachine->TerminateStateMachine();

			CTimeout											Timeout1=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			// METHOD Processor.GetStateMachinesTimeout() SHOULD HAVE REMOVED TERMINATED STATE MACHINE.
			if (Processor.GetStateMachines().GetLength()>0)
			{
				return(false);
			}

			Processor.ExecuteStateMachines();

			CTimeout											Timeout2=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			if (CheckStateMachineTimeout(Timeout1,false,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout2,false,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine,1,1,2,2,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine,1,1,0,0,1,1,1,1,0,0,2,2)==false)
			{
				return(false);
			}

			if (CheckStateMachineState3(StateMachine,0,0,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState4(StateMachine,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=0)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestExceptionStateMachineExceptionStartedEvent1(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID("SM");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSteadyClock::Milliseconds							CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();
			CSPTestStateMachineExceptionSettings1				Settings(new CTestStateMachineExceptionSettings1(StateMachineID,CPriority(100),StateMachineTimeout,CTestStateMachineExceptionSettings(CTimeout(StateMachineTimeout)),CExpirationTime()));

			Settings->GetStateMachineExceptionSettings().SetThrowExceptionOnStateMachineStartedEvent(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_STATE_MACHINE,1,0));

			CSPTestStateMachineException1						StateMachine(new CTestStateMachineException1(*this,*this,Settings,nullptr));

			// Internally EXECUTES STATE MACHINE to START STATE.
			Processor.AddStateMachine(StateMachine);

			CTimeout											Timeout1=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.ExecuteStateMachines();

			CTimeout											Timeout2=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			if (CheckStateMachineTimeout(Timeout1,false,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout2,false,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine,1,1,0,0,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine,1,1,0,0,1,0,1,1,0,0,2,2)==false)
			{
				return(false);
			}

			if (CheckStateMachineState3(StateMachine,0,0,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState4(StateMachine,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=1)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestExceptionStateMachineExceptionStartedEvent2(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID("SM");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSteadyClock::Milliseconds							CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();
			CSPTestStateMachineExceptionSettings1				Settings(new CTestStateMachineExceptionSettings1(StateMachineID,CPriority(100),StateMachineTimeout,CTestStateMachineExceptionSettings(CTimeout(StateMachineTimeout)),CExpirationTime()));

			Settings->GetStateMachineExceptionSettings().SetThrowExceptionOnStateMachineStartedEvent(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_CSTRING,1,0));

			CSPTestStateMachineException1						StateMachine(new CTestStateMachineException1(*this,*this,Settings,nullptr));

			// Internally EXECUTES STATE MACHINE to START STATE.
			Processor.AddStateMachine(StateMachine);

			CTimeout											Timeout1=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.ExecuteStateMachines();

			CTimeout											Timeout2=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			if (CheckStateMachineTimeout(Timeout1,false,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout2,false,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine,1,1,0,0,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine,1,1,0,0,1,0,1,1,0,0,2,2)==false)
			{
				return(false);
			}

			if (CheckStateMachineState3(StateMachine,0,0,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState4(StateMachine,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=1)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestExceptionStateMachineExceptionExecuteStateMachine1(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID("SM");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSteadyClock::Milliseconds							CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();
			CSPTestStateMachineExceptionSettings1				Settings(new CTestStateMachineExceptionSettings1(StateMachineID,CPriority(100),StateMachineTimeout,CTestStateMachineExceptionSettings(CTimeout(StateMachineTimeout)),CExpirationTime()));

			Settings->GetStateMachineExceptionSettings().SetThrowExceptionOnInternalExecuteStateMachine(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_STATE_MACHINE,2,0));

			CSPTestStateMachineException1						StateMachine(new CTestStateMachineException1(*this,*this,Settings,nullptr));

			// Internally EXECUTES STATE MACHINE to START STATE.
			Processor.AddStateMachine(StateMachine);

			CTimeout											Timeout1=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.ExecuteStateMachines();

			CTimeout											Timeout2=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.ExecuteStateMachines();

			CTimeout											Timeout3=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			if (CheckStateMachineTimeout(Timeout1,false,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout2,true,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout3,false,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine,1,1,2,1,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine,1,1,1,1,1,1,1,1,0,0,2,2)==false)
			{
				return(false);
			}

			if (CheckStateMachineState3(StateMachine,0,0,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState4(StateMachine,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=1)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestExceptionStateMachineExceptionExecuteStateMachine2(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID("SM");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSteadyClock::Milliseconds							CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();
			CSPTestStateMachineExceptionSettings1				Settings(new CTestStateMachineExceptionSettings1(StateMachineID,CPriority(100),StateMachineTimeout,CTestStateMachineExceptionSettings(CTimeout(StateMachineTimeout)),CExpirationTime()));

			Settings->GetStateMachineExceptionSettings().SetThrowExceptionOnInternalExecuteStateMachine(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_CSTRING,2,0));

			CSPTestStateMachineException1						StateMachine(new CTestStateMachineException1(*this,*this,Settings,nullptr));

			// Internally EXECUTES STATE MACHINE to START STATE.
			Processor.AddStateMachine(StateMachine);

			CTimeout											Timeout1=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.ExecuteStateMachines();

			CTimeout											Timeout2=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.ExecuteStateMachines();

			CTimeout											Timeout3=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			if (CheckStateMachineTimeout(Timeout1,false,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout2,true,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout3,false,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine,1,1,2,1,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine,1,1,1,1,1,1,1,1,0,0,2,2)==false)
			{
				return(false);
			}

			if (CheckStateMachineState3(StateMachine,0,0,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState4(StateMachine,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=1)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestExceptionStateMachineExceptionGetStateMachineTimeout1(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID("SM");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSteadyClock::Milliseconds							CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();
			CSPTestStateMachineExceptionSettings1				Settings(new CTestStateMachineExceptionSettings1(StateMachineID,CPriority(100),StateMachineTimeout,CTestStateMachineExceptionSettings(CTimeout(StateMachineTimeout)),CExpirationTime()));

			Settings->GetStateMachineExceptionSettings().SetThrowExceptionOnInternalGetStateMachineTimeout(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_STATE_MACHINE,1,0));

			CSPTestStateMachineException1						StateMachine(new CTestStateMachineException1(*this,*this,Settings,nullptr));

			Processor.AddStateMachine(StateMachine);

			Processor.ExecuteStateMachines();

			CTimeout											Timeout1=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.ExecuteStateMachines();

			CTimeout											Timeout2=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.ExecuteStateMachines();

			CTimeout											Timeout3=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			if (CheckStateMachineTimeout(Timeout1,true,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout2,false,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout3,false,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine,1,1,2,2,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine,1,1,1,0,1,1,1,1,0,0,2,2)==false)
			{
				return(false);
			}

			if (CheckStateMachineState3(StateMachine,0,0,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState4(StateMachine,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=1)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestExceptionStateMachineExceptionGetStateMachineTimeout2(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID("SM");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSteadyClock::Milliseconds							CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();
			CSPTestStateMachineExceptionSettings1				Settings(new CTestStateMachineExceptionSettings1(StateMachineID,CPriority(100),StateMachineTimeout,CTestStateMachineExceptionSettings(CTimeout(StateMachineTimeout)),CExpirationTime()));

			Settings->GetStateMachineExceptionSettings().SetThrowExceptionOnInternalGetStateMachineTimeout(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_CSTRING,1,0));

			CSPTestStateMachineException1						StateMachine(new CTestStateMachineException1(*this,*this,Settings,nullptr));

			Processor.AddStateMachine(StateMachine);

			Processor.ExecuteStateMachines();

			CTimeout											Timeout1=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.ExecuteStateMachines();

			CTimeout											Timeout2=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.ExecuteStateMachines();

			CTimeout											Timeout3=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			if (CheckStateMachineTimeout(Timeout1,true,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout2,false,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout3,false,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine,1,1,2,2,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine,1,1,1,0,1,1,1,1,0,0,2,2)==false)
			{
				return(false);
			}

			if (CheckStateMachineState3(StateMachine,0,0,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState4(StateMachine,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=1)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestExceptionStateMachineExceptionStateOutputFiredEvent1(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID("SM");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSPTestStateMachineExceptionSettings1				Settings(new CTestStateMachineExceptionSettings1(StateMachineID,CPriority(100),StateMachineTimeout,CTestStateMachineExceptionSettings(CTimeout(StateMachineTimeout)),CExpirationTime()));

			Settings->GetStateMachineExceptionSettings().SetThrowExceptionOnStateMachineStateOutputFiringEvent(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_STATE_MACHINE,1,1));

			CSPTestStateMachineException1						StateMachine(new CTestStateMachineException1(*this,*this,Settings,nullptr));

			// Internally EXECUTES STATE MACHINE to START STATE.
			Processor.AddStateMachine(StateMachine);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID,CTestStateMachineException1::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInputSendStateOutput(new CStateInputSendStateOutput(StateMachineID,StateMachineID,CSPStateOutput(new CStateOutput1(StateMachineID,"STATE 1")))));
				
			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInputSendStateOutput(new CStateInputSendStateOutput(StateMachineID,StateMachineID,CSPStateOutput(new CStateOutput2(StateMachineID,"STATE 2")))));
				
			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInputSendStateOutput(new CStateInputSendStateOutput(StateMachineID,StateMachineID,CSPStateOutput(new CStateOutput3(StateMachineID,"STATE 3")))));
				
			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInputSendStateOutput(new CStateInputSendStateOutput(StateMachineID,StateMachineID,CSPStateOutput(new CStateOutput4(StateMachineID,"STATE 4")))));
				
			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID,CTestStateMachineBasicTests::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (MOutputCollection.GetLength()!=0)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine,1,1,13,13,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine,0,0,0,0,1,1,1,1,0,0,3,3)==false)
			{
				return(false);
			}

			if (CheckStateMachineState3(StateMachine,4,0,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState4(StateMachine,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=4)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestExceptionStateMachineExceptionStateOutputFiredEvent2(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID("SM");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSPTestStateMachineExceptionSettings1				Settings(new CTestStateMachineExceptionSettings1(StateMachineID,CPriority(100),StateMachineTimeout,CTestStateMachineExceptionSettings(CTimeout(StateMachineTimeout)),CExpirationTime()));

			Settings->GetStateMachineExceptionSettings().SetThrowExceptionOnStateMachineStateOutputFiringEvent(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_CSTRING,1,1));

			CSPTestStateMachineException1						StateMachine(new CTestStateMachineException1(*this,*this,Settings,nullptr));

			// Internally EXECUTES STATE MACHINE to START STATE.
			Processor.AddStateMachine(StateMachine);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID,CTestStateMachineException1::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInputSendStateOutput(new CStateInputSendStateOutput(StateMachineID,StateMachineID,CSPStateOutput(new CStateOutput1(StateMachineID,"STATE 1")))));
				
			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInputSendStateOutput(new CStateInputSendStateOutput(StateMachineID,StateMachineID,CSPStateOutput(new CStateOutput2(StateMachineID,"STATE 2")))));
				
			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInputSendStateOutput(new CStateInputSendStateOutput(StateMachineID,StateMachineID,CSPStateOutput(new CStateOutput3(StateMachineID,"STATE 3")))));
				
			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInputSendStateOutput(new CStateInputSendStateOutput(StateMachineID,StateMachineID,CSPStateOutput(new CStateOutput4(StateMachineID,"STATE 4")))));
				
			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID,CTestStateMachineBasicTests::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (MOutputCollection.GetLength()!=0)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine,1,1,13,13,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine,0,0,0,0,1,1,1,1,0,0,3,3)==false)
			{
				return(false);
			}

			if (CheckStateMachineState3(StateMachine,4,0,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState4(StateMachine,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=4)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestExceptionStateMachineExceptionExpiredEvent1(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID("SM");
			CTimeout											StateMachineTimeout(1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSteadyClock::Milliseconds							CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();
			CSPTestStateMachineExceptionSettings1				Settings(new CTestStateMachineExceptionSettings1(StateMachineID,CPriority(100),StateMachineTimeout,CTestStateMachineExceptionSettings(CTimeout(StateMachineTimeout)),CExpirationTime()));

			Settings->GetStateMachineExceptionSettings().SetThrowExceptionOnStateMachineExpiredEvent(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_STATE_MACHINE,1,0));

			CSPTestStateMachineException1						StateMachine(new CTestStateMachineException1(*this,*this,Settings,nullptr));

			Processor.AddStateMachine(StateMachine);

			Processor.ExecuteStateMachines();

			CTimeout											Timeout1=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			// Wait for STATE MACHINE EXPIRATION.
			CThread::Sleep(static_cast<uint64>(StateMachineTimeout.GetTimeoutInMS()));

			CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();

			CTimeout											Timeout2=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.ExecuteStateMachines();

			CTimeout											Timeout3=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			if (CheckStateMachineTimeout(Timeout1,false,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout2,true,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout3,true,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine,1,1,2,2,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine,1,1,2,2,1,1,1,1,1,0,2,2)==false)
			{
				return(false);
			}

			if (CheckStateMachineState3(StateMachine,0,0,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState4(StateMachine,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=1)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestExceptionStateMachineExceptionExpiredEvent2(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID("SM");
			CTimeout											StateMachineTimeout(1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSteadyClock::Milliseconds							CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();
			CSPTestStateMachineExceptionSettings1				Settings(new CTestStateMachineExceptionSettings1(StateMachineID,CPriority(100),StateMachineTimeout,CTestStateMachineExceptionSettings(CTimeout(StateMachineTimeout)),CExpirationTime()));

			Settings->GetStateMachineExceptionSettings().SetThrowExceptionOnStateMachineExpiredEvent(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_CSTRING,1,0));

			CSPTestStateMachineException1						StateMachine(new CTestStateMachineException1(*this,*this,Settings,nullptr));

			Processor.AddStateMachine(StateMachine);

			Processor.ExecuteStateMachines();

			CTimeout											Timeout1=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			// Wait for STATE MACHINE EXPIRATION.
			CThread::Sleep(static_cast<uint64>(StateMachineTimeout.GetTimeoutInMS()));

			CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();

			CTimeout											Timeout2=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.ExecuteStateMachines();

			CTimeout											Timeout3=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			if (CheckStateMachineTimeout(Timeout1,false,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout2,true,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout3,true,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine,1,1,2,2,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine,1,1,2,2,1,1,1,1,1,0,2,2)==false)
			{
				return(false);
			}

			if (CheckStateMachineState3(StateMachine,0,0,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState4(StateMachine,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=1)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestExceptionStateMachineExceptionInternalTerminate1(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID("SM");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSteadyClock::Milliseconds							CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();
			CSPTestStateMachineExceptionSettings1				Settings(new CTestStateMachineExceptionSettings1(StateMachineID,CPriority(100),StateMachineTimeout,CTestStateMachineExceptionSettings(CTimeout(StateMachineTimeout)),CExpirationTime()));

			Settings->GetStateMachineExceptionSettings().SetThrowExceptionOnInternalTerminateStateMachine(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_STATE_MACHINE,1,0));

			CSPTestStateMachineException1						StateMachine(new CTestStateMachineException1(*this,*this,Settings,nullptr));

			Processor.AddStateMachine(StateMachine);

			Processor.ExecuteStateMachines();

			Processor.TerminateStateMachines();

			CTimeout											Timeout1=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.ExecuteStateMachines();

			CTimeout											Timeout2=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			if (CheckStateMachineTimeout(Timeout1,true,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout2,false,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine,1,1,2,2,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine,1,0,0,0,1,1,1,1,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState3(StateMachine,0,0,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState4(StateMachine,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=1)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestExceptionStateMachineExceptionInternalTerminate2(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID("SM");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSteadyClock::Milliseconds							CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();
			CSPTestStateMachineExceptionSettings1				Settings(new CTestStateMachineExceptionSettings1(StateMachineID,CPriority(100),StateMachineTimeout,CTestStateMachineExceptionSettings(CTimeout(StateMachineTimeout)),CExpirationTime()));

			Settings->GetStateMachineExceptionSettings().SetThrowExceptionOnInternalTerminateStateMachine(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_CSTRING,1,0));

			CSPTestStateMachineException1						StateMachine(new CTestStateMachineException1(*this,*this,Settings,nullptr));

			Processor.AddStateMachine(StateMachine);

			Processor.ExecuteStateMachines();

			Processor.TerminateStateMachines([](CSPStateMachine)->bool{return(true);});

			CTimeout											Timeout1=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.ExecuteStateMachines();

			CTimeout											Timeout2=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			if (CheckStateMachineTimeout(Timeout1,true,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout2,false,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine,1,1,2,2,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine,1,0,0,0,1,1,1,1,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState3(StateMachine,0,0,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState4(StateMachine,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=1)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestExceptionStateMachineExceptionInternalTerminateFinished1(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID("SM");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSPTestStateMachineExceptionSettings1				Settings(new CTestStateMachineExceptionSettings1(StateMachineID,CPriority(100),StateMachineTimeout,CTestStateMachineExceptionSettings(CTimeout(StateMachineTimeout)),CExpirationTime()));

			Settings->GetStateMachineExceptionSettings().SetThrowExceptionOnInternalTerminateStateMachine(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_STATE_MACHINE,1,0));
			Settings->GetStateMachineExceptionSettings().SetThrowExceptionOnStateMachineFinishedEvent(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_STATE_MACHINE,1,0));

			CSPTestStateMachineException1						StateMachine(new CTestStateMachineException1(*this,*this,Settings,nullptr));

			Processor.AddStateMachine(StateMachine);

			Processor.ExecuteStateMachines();

			Processor.TerminateStateMachines();

			Processor.ExecuteStateMachines();

			if (CheckStateMachineState1(StateMachine,1,1,2,2,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine,1,0,0,0,1,1,1,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState3(StateMachine,0,0,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState4(StateMachine,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=2)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestExceptionStateMachineExceptionInternalTerminateFinished2(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID("SM");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSPTestStateMachineExceptionSettings1				Settings(new CTestStateMachineExceptionSettings1(StateMachineID,CPriority(100),StateMachineTimeout,CTestStateMachineExceptionSettings(CTimeout(StateMachineTimeout)),CExpirationTime()));

			Settings->GetStateMachineExceptionSettings().SetThrowExceptionOnInternalTerminateStateMachine(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_CSTRING,1,0));
			Settings->GetStateMachineExceptionSettings().SetThrowExceptionOnStateMachineFinishedEvent(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_CSTRING,1,0));

			CSPTestStateMachineException1						StateMachine(new CTestStateMachineException1(*this,*this,Settings,nullptr));

			Processor.AddStateMachine(StateMachine);

			Processor.ExecuteStateMachines();

			Processor.TerminateStateMachines();

			Processor.ExecuteStateMachines();

			if (CheckStateMachineState1(StateMachine,1,1,2,2,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine,1,0,0,0,1,1,1,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState3(StateMachine,0,0,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState4(StateMachine,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=2)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CStateMachineTest::InternalWriteToLog(const CLogCategory& LogCategory, ELogRecordLevel LogLevel, const Char* FunctionName, Size LineNumber, const CLogRecord& LogRecord)
	{
		if (LogLevel==ELogRecordLevel::E_WARNING || LogLevel==ELogRecordLevel::E_ERROR)
		{
			MNumberOfWarningsAndErrors++;
		}

		if (MWriteStateMachineLogs==true)
		{
			GetLogWriter().WriteToLog(LogCategory,LogLevel,FunctionName,LineNumber,LogRecord);
		}
		else
		{
			if (LogCategory==GetLogCategoryTest())
			{
				GetLogWriter().WriteToLog(LogCategory,LogLevel,FunctionName,LineNumber,LogRecord);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestExceptionStateMachineExceptionExpiredEventInternalTerminate(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID("SM");
			CTimeout											StateMachineTimeout(1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSteadyClock::Milliseconds							CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();
			CSPTestStateMachineExceptionSettings1				Settings(new CTestStateMachineExceptionSettings1(StateMachineID,CPriority(100),StateMachineTimeout,CTestStateMachineExceptionSettings(CTimeout(StateMachineTimeout)),CExpirationTime()));

			Settings->GetStateMachineExceptionSettings().SetThrowExceptionOnStateMachineExpiredEvent(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_STATE_MACHINE,1,0));
			Settings->GetStateMachineExceptionSettings().SetThrowExceptionOnInternalTerminateStateMachine(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_STATE_MACHINE,1,0));

			CSPTestStateMachineException1						StateMachine(new CTestStateMachineException1(*this,*this,Settings,nullptr));

			Processor.AddStateMachine(StateMachine);

			Processor.ExecuteStateMachines();

			CTimeout											Timeout1=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			// Wait for STATE MACHINE EXPIRATION.
			CThread::Sleep(static_cast<uint64>(StateMachineTimeout.GetTimeoutInMS()));

			CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();

			CTimeout											Timeout2=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.ExecuteStateMachines();

			CTimeout											Timeout3=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			if (CheckStateMachineTimeout(Timeout1,false,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout2,true,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout3,true,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine,1,1,2,2,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine,1,0,2,2,1,1,1,1,1,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState3(StateMachine,0,0,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState4(StateMachine,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=2)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestExceptionStateMachineExceptionExpiredEventInternalTerminateFinshed(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID("SM");
			CTimeout											StateMachineTimeout(1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSteadyClock::Milliseconds							CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();
			CSPTestStateMachineExceptionSettings1				Settings(new CTestStateMachineExceptionSettings1(StateMachineID,CPriority(100),StateMachineTimeout,CTestStateMachineExceptionSettings(CTimeout(StateMachineTimeout)),CExpirationTime()));

			Settings->GetStateMachineExceptionSettings().SetThrowExceptionOnStateMachineExpiredEvent(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_STATE_MACHINE,1,0));
			Settings->GetStateMachineExceptionSettings().SetThrowExceptionOnInternalTerminateStateMachine(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_STATE_MACHINE,1,0));
			Settings->GetStateMachineExceptionSettings().SetThrowExceptionOnStateMachineFinishedEvent(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_STATE_MACHINE,1,0));

			CSPTestStateMachineException1						StateMachine(new CTestStateMachineException1(*this,*this,Settings,nullptr));

			Processor.AddStateMachine(StateMachine);

			Processor.ExecuteStateMachines();

			CTimeout											Timeout1=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			// Wait for STATE MACHINE EXPIRATION.
			CThread::Sleep(static_cast<uint64>(StateMachineTimeout.GetTimeoutInMS()));

			CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();

			CTimeout											Timeout2=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.ExecuteStateMachines();

			CTimeout											Timeout3=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			if (CheckStateMachineTimeout(Timeout1,false,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout2,true,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout3,true,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine,1,1,2,2,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine,1,0,2,2,1,1,1,0,1,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState3(StateMachine,0,0,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState4(StateMachine,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=3)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestChildStateMachineLevel1(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID1("SM1");
			CStateMachineID										StateMachineID2("SM2");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSPTestStateMachineSettings1						Settings1(new CTestStateMachineSettings1(StateMachineID1,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings2						Settings2(new CTestStateMachineSettings2(StateMachineID2,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachine1								StateMachine1(new CTestStateMachine1(*this,*this,Settings1,nullptr));
			CSPTestStateMachine2								StateMachine2(new CTestStateMachine2(*this,*this,Settings2,StateMachine1.GetPointer()));

			// Internally EXECUTES STATE MACHINE to START STATE.
			Processor.AddStateMachine(StateMachine1);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID1,StateMachineID1,StateMachine2)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (CheckStateMachineState1(StateMachine1,1,11,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine1,0,3,0,0,0,0,0,1,1,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine2,1,5,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine2,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID2}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID2}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (StateMachine1->TestGetChildStateMachineByID(StateMachineID2)==nullptr)
			{
				return(false);
			}

			if (StateMachine1->TestHasChildStateMachineByID(StateMachineID2)==false)
			{
				return(false);
			}

			if (StateMachine2->TestHasChildStateMachineByID(StateMachineID2)==true)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=0)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestChildStateMachineLevel2(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID1("SM1");
			CStateMachineID										StateMachineID2("SM2");
			CStateMachineID										StateMachineID3("SM3");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSPTestStateMachineSettings1						Settings1(new CTestStateMachineSettings1(StateMachineID1,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings2						Settings2(new CTestStateMachineSettings2(StateMachineID2,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings3						Settings3(new CTestStateMachineSettings3(StateMachineID3,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachine1								StateMachine1(new CTestStateMachine1(*this,*this,Settings1,nullptr));
			CSPTestStateMachine2								StateMachine2(new CTestStateMachine2(*this,*this,Settings2,StateMachine1.GetPointer()));
			CSPTestStateMachine3								StateMachine3(new CTestStateMachine3(*this,*this,Settings3,StateMachine2.GetPointer()));

			// Internally EXECUTES STATE MACHINE to START STATE.
			Processor.AddStateMachine(StateMachine1);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID1,StateMachineID1,StateMachine2)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID2,StateMachineID2,StateMachine3)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (CheckStateMachineState1(StateMachine1,1,17,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine1,0,3,0,0,0,0,0,2,2,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine2,1,11,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine2,0,3,0,0,0,0,0,1,1,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine3,1,5,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine3,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID2,StateMachineID3}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID3}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID2}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID3}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=0)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestChildStateMachineLevel3(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID1("SM1");
			CStateMachineID										StateMachineID2("SM2");
			CStateMachineID										StateMachineID3("SM3");
			CStateMachineID										StateMachineID4("SM4");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSteadyClock::Milliseconds							CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();
			CSPTestStateMachineSettings1						Settings1(new CTestStateMachineSettings1(StateMachineID1,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings2						Settings2(new CTestStateMachineSettings2(StateMachineID2,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings3						Settings3(new CTestStateMachineSettings3(StateMachineID3,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings4(new CTestStateMachineSettings4(StateMachineID4,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachine1								StateMachine1(new CTestStateMachine1(*this,*this,Settings1,nullptr));
			CSPTestStateMachine2								StateMachine2(new CTestStateMachine2(*this,*this,Settings2,StateMachine1.GetPointer()));
			CSPTestStateMachine3								StateMachine3(new CTestStateMachine3(*this,*this,Settings3,StateMachine2.GetPointer()));
			CSPTestStateMachine4								StateMachine4(new CTestStateMachine4(*this,*this,Settings4,StateMachine3.GetPointer()));

			// Internally EXECUTES STATE MACHINE to START STATE.
			Processor.AddStateMachine(StateMachine1);

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID1,StateMachineID1,StateMachine2)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID2,StateMachineID2,StateMachine3)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID3,StateMachineID3,StateMachine4)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			CTimeout											Timeout1=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			CTimeout											Timeout2=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			if (StateMachine4->TestGetStateMachineRoot()!=StateMachine1.GetPointer())
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout1,false,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout2,false,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine1,1,23,0,0,0,0,0,12,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine1,0,3,0,0,0,0,0,3,3,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine2,1,17,0,0,0,0,0,9,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine2,0,3,0,0,0,0,0,2,2,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine3,1,11,0,0,0,0,0,6,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine3,0,3,0,0,0,0,0,1,1,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine4,1,5,0,0,0,0,0,3,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine4,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID2,StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID2}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID3}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=0)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestChildStateMachineTimeoutExpiration1(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID1("SM1");
			CStateMachineID										StateMachineID2("SM2");
			CStateMachineID										StateMachineID3("SM3");
			CStateMachineID										StateMachineID4("SM4");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSteadyClock::Milliseconds							CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();
			CSPTestStateMachineSettings1						Settings1(new CTestStateMachineSettings1(StateMachineID1,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings2						Settings2(new CTestStateMachineSettings2(StateMachineID2,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings3						Settings3(new CTestStateMachineSettings3(StateMachineID3,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			// EXPIRATION TIME is SET.
			CSPTestStateMachineSettings4						Settings4(new CTestStateMachineSettings4(StateMachineID4,CPriority(100),StateMachineTimeout,CExpirationTime(2000,CurrentTimeInMS),true,true,true,true,true,true,true,true));
			CSPTestStateMachine1								StateMachine1(new CTestStateMachine1(*this,*this,Settings1,nullptr));
			CSPTestStateMachine2								StateMachine2(new CTestStateMachine2(*this,*this,Settings2,StateMachine1.GetPointer()));
			CSPTestStateMachine3								StateMachine3(new CTestStateMachine3(*this,*this,Settings3,StateMachine2.GetPointer()));
			CSPTestStateMachine4								StateMachine4(new CTestStateMachine4(*this,*this,Settings4,StateMachine3.GetPointer()));

			// Internally EXECUTES STATE MACHINE to START STATE.
			Processor.AddStateMachine(StateMachine1);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID1,StateMachineID1,StateMachine2)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID2,StateMachineID2,StateMachine3)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID3,StateMachineID3,StateMachine4)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			CTimeout											Timeout1=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			CThread::Sleep(2100);

			CSteadyClock::Milliseconds							AdjustedCurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();

			CTimeout											Timeout2=Processor.GetStateMachinesTimeout(AdjustedCurrentTimeInMS);

			// EXPIRED STATE MECHINE will be FINISHED.
			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (StateMachine4->TestGetStateMachineRoot()!=StateMachine1.GetPointer())
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout1,false,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout2,true,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine1,1,24,0,0,0,0,0,2,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine1,0,3,0,0,0,0,0,3,3,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine2,1,18,0,0,0,0,0,2,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine2,0,3,0,0,0,0,0,2,2,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine3,1,12,0,0,0,0,0,2,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine3,0,3,0,0,0,0,0,1,1,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine4,1,5,0,0,0,0,0,2,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine4,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID2,StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID2}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID3}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=1)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestChildStateMachineTimeoutExpiration2(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID1("SM1");
			CStateMachineID										StateMachineID2("SM2");
			CStateMachineID										StateMachineID3("SM3");
			CStateMachineID										StateMachineID4("SM4");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSteadyClock::Milliseconds							CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();
			CSPTestStateMachineSettings1						Settings1(new CTestStateMachineSettings1(StateMachineID1,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings2						Settings2(new CTestStateMachineSettings2(StateMachineID2,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			// EXPIRATION TIME is SET.
			CSPTestStateMachineSettings3						Settings3(new CTestStateMachineSettings3(StateMachineID3,CPriority(100),StateMachineTimeout,CExpirationTime(2000,CurrentTimeInMS),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings4(new CTestStateMachineSettings4(StateMachineID4,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachine1								StateMachine1(new CTestStateMachine1(*this,*this,Settings1,nullptr));
			CSPTestStateMachine2								StateMachine2(new CTestStateMachine2(*this,*this,Settings2,StateMachine1.GetPointer()));
			CSPTestStateMachine3								StateMachine3(new CTestStateMachine3(*this,*this,Settings3,StateMachine2.GetPointer()));
			CSPTestStateMachine4								StateMachine4(new CTestStateMachine4(*this,*this,Settings4,StateMachine3.GetPointer()));

			// Internally EXECUTES STATE MACHINE to START STATE.
			Processor.AddStateMachine(StateMachine1);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID1,StateMachineID1,StateMachine2)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID2,StateMachineID2,StateMachine3)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID3,StateMachineID3,StateMachine4)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			CTimeout											Timeout1=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			CThread::Sleep(2100);

			CSteadyClock::Milliseconds							AdjustedCurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();

			CTimeout											Timeout2=Processor.GetStateMachinesTimeout(AdjustedCurrentTimeInMS);

			// EXPIRED STATE MECHINE will be FINISHED.
			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (StateMachine4->TestGetStateMachineRoot()!=StateMachine1.GetPointer())
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout1,false,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineTimeout(Timeout2,true,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine1,1,24,0,0,0,0,0,2,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine1,0,3,0,0,0,0,0,3,3,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine2,1,18,0,0,0,0,0,2,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine2,0,3,0,0,0,0,0,2,2,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine3,1,9,0,0,0,0,0,2,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine3,0,3,0,0,0,0,0,1,1,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine4,1,6,0,0,0,0,0,2,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine4,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID2,StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID2}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID3}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=1)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestChildStateMachineReversedFinalStates(void)
	{
		try
		{
			Reset();

			CSteadyClock::Milliseconds							CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();
			CStateMachineID										StateMachineID1("SM1");
			CStateMachineID										StateMachineID2("SM2");
			CStateMachineID										StateMachineID3("SM3");
			CStateMachineID										StateMachineID4("SM4");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSPTestStateMachineSettings1						Settings1(new CTestStateMachineSettings1(StateMachineID1,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings2						Settings2(new CTestStateMachineSettings2(StateMachineID2,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings3						Settings3(new CTestStateMachineSettings3(StateMachineID3,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings4(new CTestStateMachineSettings4(StateMachineID4,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachine1								StateMachine1(new CTestStateMachine1(*this,*this,Settings1,nullptr));
			CSPTestStateMachine2								StateMachine2(new CTestStateMachine2(*this,*this,Settings2,StateMachine1.GetPointer()));
			CSPTestStateMachine3								StateMachine3(new CTestStateMachine3(*this,*this,Settings3,StateMachine2.GetPointer()));
			CSPTestStateMachine4								StateMachine4(new CTestStateMachine4(*this,*this,Settings4,StateMachine3.GetPointer()));

			// Internally EXECUTES STATE MACHINE to START STATE.
			Processor.AddStateMachine(StateMachine1);

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID1,StateMachineID1,StateMachine2)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID2,StateMachineID2,StateMachine3)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID3,StateMachineID3,StateMachine4)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			if (CheckStateMachineState1(StateMachine1,1,17,0,0,0,0,0,11,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine1,0,3,0,0,0,0,0,3,3,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine2,1,14,0,0,0,0,0,9,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine2,0,3,0,0,0,0,0,2,2,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine3,1,11,0,0,0,0,0,7,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine3,0,3,0,0,0,0,0,1,1,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine4,1,8,0,0,0,0,0,5,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine4,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID2,StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID2}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID3}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=0)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestChildStateMachineMultipleChildStateMachines1(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID1("SM1");
			CStateMachineID										StateMachineID21("SM21");
			CStateMachineID										StateMachineID22("SM22");
			CStateMachineID										StateMachineID31("SM31");
			CStateMachineID										StateMachineID32("SM32");
			CStateMachineID										StateMachineID33("SM33");
			CStateMachineID										StateMachineID34("SM34");
			CStateMachineID										StateMachineID41("SM41");
			CStateMachineID										StateMachineID42("SM42");
			CStateMachineID										StateMachineID43("SM43");
			CStateMachineID										StateMachineID44("SM44");
			CStateMachineID										StateMachineID45("SM45");
			CStateMachineID										StateMachineID46("SM46");
			CStateMachineID										StateMachineID47("SM47");
			CStateMachineID										StateMachineID48("SM48");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSPTestStateMachineSettings1						Settings1(new CTestStateMachineSettings1(StateMachineID1,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings2						Settings21(new CTestStateMachineSettings2(StateMachineID21,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings2						Settings22(new CTestStateMachineSettings2(StateMachineID22,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings3						Settings31(new CTestStateMachineSettings3(StateMachineID31,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings3						Settings32(new CTestStateMachineSettings3(StateMachineID32,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings3						Settings33(new CTestStateMachineSettings3(StateMachineID33,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings3						Settings34(new CTestStateMachineSettings3(StateMachineID34,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings41(new CTestStateMachineSettings4(StateMachineID41,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings42(new CTestStateMachineSettings4(StateMachineID42,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings43(new CTestStateMachineSettings4(StateMachineID43,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings44(new CTestStateMachineSettings4(StateMachineID44,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings45(new CTestStateMachineSettings4(StateMachineID45,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings46(new CTestStateMachineSettings4(StateMachineID46,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings47(new CTestStateMachineSettings4(StateMachineID47,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings48(new CTestStateMachineSettings4(StateMachineID48,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachine1								StateMachine1(new CTestStateMachine1(*this,*this,Settings1,nullptr));
			CSPTestStateMachine2								StateMachine21(new CTestStateMachine2(*this,*this,Settings21,StateMachine1.GetPointer()));
			CSPTestStateMachine2								StateMachine22(new CTestStateMachine2(*this,*this,Settings22,StateMachine1.GetPointer()));
			CSPTestStateMachine3								StateMachine31(new CTestStateMachine3(*this,*this,Settings31,StateMachine21.GetPointer()));
			CSPTestStateMachine3								StateMachine32(new CTestStateMachine3(*this,*this,Settings32,StateMachine21.GetPointer()));
			CSPTestStateMachine3								StateMachine33(new CTestStateMachine3(*this,*this,Settings33,StateMachine22.GetPointer()));
			CSPTestStateMachine3								StateMachine34(new CTestStateMachine3(*this,*this,Settings34,StateMachine22.GetPointer()));
			CSPTestStateMachine4								StateMachine41(new CTestStateMachine4(*this,*this,Settings41,StateMachine31.GetPointer()));
			CSPTestStateMachine4								StateMachine42(new CTestStateMachine4(*this,*this,Settings42,StateMachine31.GetPointer()));
			CSPTestStateMachine4								StateMachine43(new CTestStateMachine4(*this,*this,Settings43,StateMachine32.GetPointer()));
			CSPTestStateMachine4								StateMachine44(new CTestStateMachine4(*this,*this,Settings44,StateMachine32.GetPointer()));
			CSPTestStateMachine4								StateMachine45(new CTestStateMachine4(*this,*this,Settings45,StateMachine33.GetPointer()));
			CSPTestStateMachine4								StateMachine46(new CTestStateMachine4(*this,*this,Settings46,StateMachine33.GetPointer()));
			CSPTestStateMachine4								StateMachine47(new CTestStateMachine4(*this,*this,Settings47,StateMachine34.GetPointer()));
			CSPTestStateMachine4								StateMachine48(new CTestStateMachine4(*this,*this,Settings48,StateMachine34.GetPointer()));

			// Internally EXECUTES STATE MACHINE to START STATE.
			Processor.AddStateMachine(StateMachine1);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID1,StateMachineID1,StateMachine21)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID21,CTestStateMachine2::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID1,StateMachineID1,StateMachine22)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID22,CTestStateMachine2::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID21,StateMachineID21,StateMachine31)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID31,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID21,StateMachineID21,StateMachine32)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID32,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID22,StateMachineID22,StateMachine33)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID33,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID22,StateMachineID22,StateMachine34)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID34,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID31,StateMachineID31,StateMachine41)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID41,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID31,StateMachineID31,StateMachine42)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID42,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID32,StateMachineID32,StateMachine43)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID43,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID32,StateMachineID32,StateMachine44)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID44,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID33,StateMachineID33,StateMachine45)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID45,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID33,StateMachineID33,StateMachine46)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID46,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID34,StateMachineID34,StateMachine47)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID47,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID34,StateMachineID34,StateMachine48)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID48,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			// ALL STATE MACHINES are RUNNING.
			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID41,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID42,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID43,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID44,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID45,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID46,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID47,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID48,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID31,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID32,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID33,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID34,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID21,CTestStateMachine2::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID22,CTestStateMachine2::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID21,StateMachineID22,StateMachineID31,StateMachineID32,StateMachineID33,StateMachineID34,StateMachineID41,StateMachineID42,StateMachineID43,StateMachineID44,StateMachineID45,StateMachineID46,StateMachineID47,StateMachineID48}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine21->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID31,StateMachineID32,StateMachineID41,StateMachineID42,StateMachineID43,StateMachineID44}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine22->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID33,StateMachineID34,StateMachineID45,StateMachineID46,StateMachineID47,StateMachineID48}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine31->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID41,StateMachineID42}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine32->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID43,StateMachineID44}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine33->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID45,StateMachineID46}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine34->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID47,StateMachineID48}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine41->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine42->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine43->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine44->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine45->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine46->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine47->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine48->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID21,StateMachineID22}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine21->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID31,StateMachineID32}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine22->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID33,StateMachineID34}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine31->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID41,StateMachineID42}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine32->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID43,StateMachineID44}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine33->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID45,StateMachineID46}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine34->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID47,StateMachineID48}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine41->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine42->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine43->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine44->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine45->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine46->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine47->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine48->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine1,1,90,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine1,0,3,0,0,0,0,0,14,14,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine21,1,62,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine21,0,3,0,0,0,0,0,6,6,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine22,1,61,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine22,0,3,0,0,0,0,0,6,6,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine31,1,42,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine31,0,3,0,0,0,0,0,2,2,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine32,1,41,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine32,0,3,0,0,0,0,0,2,2,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine33,1,40,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine33,0,3,0,0,0,0,0,2,2,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine34,1,39,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine34,0,3,0,0,0,0,0,2,2,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine41,1,20,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine41,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine42,1,19,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine42,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine43,1,18,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine43,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine44,1,17,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine44,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine45,1,16,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine45,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine46,1,15,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine46,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine47,1,14,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine47,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine48,1,13,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine48,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=0)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestChildStateMachineMultipleChildStateMachines2(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID1("SM1");
			CStateMachineID										StateMachineID21("SM21");
			CStateMachineID										StateMachineID22("SM22");
			CStateMachineID										StateMachineID31("SM31");
			CStateMachineID										StateMachineID32("SM32");
			CStateMachineID										StateMachineID33("SM33");
			CStateMachineID										StateMachineID34("SM34");
			CStateMachineID										StateMachineID41("SM41");
			CStateMachineID										StateMachineID42("SM42");
			CStateMachineID										StateMachineID43("SM43");
			CStateMachineID										StateMachineID44("SM44");
			CStateMachineID										StateMachineID45("SM45");
			CStateMachineID										StateMachineID46("SM46");
			CStateMachineID										StateMachineID47("SM47");
			CStateMachineID										StateMachineID48("SM48");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSPTestStateMachineSettings1						Settings1(new CTestStateMachineSettings1(StateMachineID1,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings2						Settings21(new CTestStateMachineSettings2(StateMachineID21,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings2						Settings22(new CTestStateMachineSettings2(StateMachineID22,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings3						Settings31(new CTestStateMachineSettings3(StateMachineID31,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings3						Settings32(new CTestStateMachineSettings3(StateMachineID32,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings3						Settings33(new CTestStateMachineSettings3(StateMachineID33,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings3						Settings34(new CTestStateMachineSettings3(StateMachineID34,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings41(new CTestStateMachineSettings4(StateMachineID41,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings42(new CTestStateMachineSettings4(StateMachineID42,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings43(new CTestStateMachineSettings4(StateMachineID43,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings44(new CTestStateMachineSettings4(StateMachineID44,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings45(new CTestStateMachineSettings4(StateMachineID45,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings46(new CTestStateMachineSettings4(StateMachineID46,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings47(new CTestStateMachineSettings4(StateMachineID47,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings48(new CTestStateMachineSettings4(StateMachineID48,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachine1								StateMachine1(new CTestStateMachine1(*this,*this,Settings1,nullptr));
			CSPTestStateMachine2								StateMachine21(new CTestStateMachine2(*this,*this,Settings21,StateMachine1.GetPointer()));
			CSPTestStateMachine2								StateMachine22(new CTestStateMachine2(*this,*this,Settings22,StateMachine1.GetPointer()));
			CSPTestStateMachine3								StateMachine31(new CTestStateMachine3(*this,*this,Settings31,StateMachine21.GetPointer()));
			CSPTestStateMachine3								StateMachine32(new CTestStateMachine3(*this,*this,Settings32,StateMachine21.GetPointer()));
			CSPTestStateMachine3								StateMachine33(new CTestStateMachine3(*this,*this,Settings33,StateMachine22.GetPointer()));
			CSPTestStateMachine3								StateMachine34(new CTestStateMachine3(*this,*this,Settings34,StateMachine22.GetPointer()));
			CSPTestStateMachine4								StateMachine41(new CTestStateMachine4(*this,*this,Settings41,StateMachine31.GetPointer()));
			CSPTestStateMachine4								StateMachine42(new CTestStateMachine4(*this,*this,Settings42,StateMachine31.GetPointer()));
			CSPTestStateMachine4								StateMachine43(new CTestStateMachine4(*this,*this,Settings43,StateMachine32.GetPointer()));
			CSPTestStateMachine4								StateMachine44(new CTestStateMachine4(*this,*this,Settings44,StateMachine32.GetPointer()));
			CSPTestStateMachine4								StateMachine45(new CTestStateMachine4(*this,*this,Settings45,StateMachine33.GetPointer()));
			CSPTestStateMachine4								StateMachine46(new CTestStateMachine4(*this,*this,Settings46,StateMachine33.GetPointer()));
			CSPTestStateMachine4								StateMachine47(new CTestStateMachine4(*this,*this,Settings47,StateMachine34.GetPointer()));
			CSPTestStateMachine4								StateMachine48(new CTestStateMachine4(*this,*this,Settings48,StateMachine34.GetPointer()));

			// Internally EXECUTES STATE MACHINE to START STATE.
			Processor.AddStateMachine(StateMachine1);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID1,StateMachineID1,StateMachine21)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID21,CTestStateMachine2::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID1,StateMachineID1,StateMachine22)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID22,CTestStateMachine2::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID21,StateMachineID21,StateMachine31)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID31,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID21,StateMachineID21,StateMachine32)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID32,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID22,StateMachineID22,StateMachine33)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID33,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID22,StateMachineID22,StateMachine34)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID34,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID31,StateMachineID31,StateMachine41)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID41,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID31,StateMachineID31,StateMachine42)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID42,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID32,StateMachineID32,StateMachine43)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID43,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID32,StateMachineID32,StateMachine44)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID44,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID33,StateMachineID33,StateMachine45)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID45,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID33,StateMachineID33,StateMachine46)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID46,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID34,StateMachineID34,StateMachine47)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID47,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID34,StateMachineID34,StateMachine48)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID48,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			// ALL STATE MACHINES are RUNNING.
			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID21,CTestStateMachine2::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID22,CTestStateMachine2::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID31,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID32,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID33,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID34,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID41,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID42,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID43,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID44,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID45,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID46,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID47,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID48,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID21,StateMachineID22,StateMachineID31,StateMachineID32,StateMachineID33,StateMachineID34,StateMachineID41,StateMachineID42,StateMachineID43,StateMachineID44,StateMachineID45,StateMachineID46,StateMachineID47,StateMachineID48}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine21->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID31,StateMachineID32,StateMachineID41,StateMachineID42,StateMachineID43,StateMachineID44}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine22->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID33,StateMachineID34,StateMachineID45,StateMachineID46,StateMachineID47,StateMachineID48}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine31->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID41,StateMachineID42}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine32->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID43,StateMachineID44}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine33->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID45,StateMachineID46}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine34->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID47,StateMachineID48}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine41->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine42->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine43->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine44->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine45->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine46->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine47->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine48->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID21,StateMachineID22}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine21->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID31,StateMachineID32}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine22->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID33,StateMachineID34}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine31->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID41,StateMachineID42}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine32->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID43,StateMachineID44}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine33->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID45,StateMachineID46}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine34->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID47,StateMachineID48}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine41->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine42->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine43->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine44->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine45->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine46->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine47->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine48->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine1,1,62,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine1,0,3,0,0,0,0,0,14,14,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine21,1,45,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine21,0,3,0,0,0,0,0,6,6,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine22,1,44,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine22,0,3,0,0,0,0,0,6,6,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine31,1,35,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine31,0,3,0,0,0,0,0,2,2,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine32,1,34,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine32,0,3,0,0,0,0,0,2,2,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine33,1,33,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine33,0,3,0,0,0,0,0,2,2,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine34,1,32,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine34,0,3,0,0,0,0,0,2,2,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine41,1,27,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine41,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine42,1,26,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine42,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine43,1,25,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine43,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine44,1,24,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine44,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine45,1,23,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine45,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine46,1,22,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine46,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine47,1,21,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine47,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine48,1,20,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine48,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=0)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestChildStateMachineInput(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID1("SM1");
			CStateMachineID										StateMachineID2("SM2");
			CStateMachineID										StateMachineID3("SM3");
			CStateMachineID										StateMachineID4("SM4");
			CStateMachineID										StateMachineIDInvalid("SM INVALID");
			CStateMachineID										StateMachineIDEmpty("");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSteadyClock::Milliseconds							CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();
			// STATE INPUT 4 is NOT PROCESSED if NOT SENT with VALID STATE MACHINE ID.
			CSPTestStateMachineSettings1						Settings1(new CTestStateMachineSettings1(StateMachineID1,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,false,true,true,true,true));
			CSPTestStateMachineSettings2						Settings2(new CTestStateMachineSettings2(StateMachineID2,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,false,true,true,true,true));
			CSPTestStateMachineSettings3						Settings3(new CTestStateMachineSettings3(StateMachineID3,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,false,true,true,true,true));
			CSPTestStateMachineSettings4						Settings4(new CTestStateMachineSettings4(StateMachineID4,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,false,true,true,true,true));
			CSPTestStateMachine1								StateMachine1(new CTestStateMachine1(*this,*this,Settings1,nullptr));
			CSPTestStateMachine2								StateMachine2(new CTestStateMachine2(*this,*this,Settings2,StateMachine1.GetPointer()));
			CSPTestStateMachine3								StateMachine3(new CTestStateMachine3(*this,*this,Settings3,StateMachine2.GetPointer()));
			CSPTestStateMachine4								StateMachine4(new CTestStateMachine4(*this,*this,Settings4,StateMachine3.GetPointer()));

			// Internally EXECUTES STATE MACHINE to START STATE.
			Processor.AddStateMachine(StateMachine1);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID1,StateMachineID1,StateMachine2)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID2,StateMachineID2,StateMachine3)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID3,StateMachineID3,StateMachine4)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInput1(StateMachineID1,"STATE 1")));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInput2(StateMachineID2,"STATE 2")));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInput3(StateMachineID3,"STATE 3")));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInput4(StateMachineID4,"STATE 4")));

			Processor.ExecuteStateMachines();

			// !!! INVALID STATE MACHINE ID.
			Processor.AddStateInput(CSPStateInput(new CStateInput1(StateMachineIDInvalid,"STATE 1")));

			Processor.ExecuteStateMachines();

			// !!! EMPTY STATE MACHINE ID. STATE INPUT 1 is NOT PROCESSED by ALL STATE MACHINES.
			Processor.AddStateInput(CSPStateInput(new CStateInput1(StateMachineIDEmpty,"STATE 1")));

			Processor.ExecuteStateMachines();
			
			// !!! EMPTY STATE MACHINE ID. STATE INPUT 4 is NOT PROCESSED by ANY STATE MACHINE.
			Processor.AddStateInput(CSPStateInput(new CStateInput4(StateMachineIDEmpty,"STATE 4")));

			Processor.ExecuteStateMachines();

			CTimeout											Timeout=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (CheckStateMachineTimeout(Timeout,false,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine1,1,36,2,0,0,1,0,1,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine1,0,3,0,0,0,0,0,3,3,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine2,1,29,1,1,0,1,0,1,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine2,0,3,0,0,0,0,0,2,2,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine3,1,22,1,0,1,1,0,1,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine3,0,3,0,0,0,0,0,1,1,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine4,1,15,1,0,0,2,0,1,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine4,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID2,StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID2}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID3}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=3)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestChildStateMachineSendOutput(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID1("SM1");
			CStateMachineID										StateMachineID2("SM2");
			CStateMachineID										StateMachineID3("SM3");
			CStateMachineID										StateMachineID4("SM4");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSteadyClock::Milliseconds							CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();
			CSPTestStateMachineSettings1						Settings1(new CTestStateMachineSettings1(StateMachineID1,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings2						Settings2(new CTestStateMachineSettings2(StateMachineID2,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,false,true,true,true));
			CSPTestStateMachineSettings3						Settings3(new CTestStateMachineSettings3(StateMachineID3,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,false,true,true));
			CSPTestStateMachineSettings4						Settings4(new CTestStateMachineSettings4(StateMachineID4,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,false,true));
			CSPTestStateMachine1								StateMachine1(new CTestStateMachine1(*this,*this,Settings1,nullptr));
			CSPTestStateMachine2								StateMachine2(new CTestStateMachine2(*this,*this,Settings2,StateMachine1.GetPointer()));
			CSPTestStateMachine3								StateMachine3(new CTestStateMachine3(*this,*this,Settings3,StateMachine2.GetPointer()));
			CSPTestStateMachine4								StateMachine4(new CTestStateMachine4(*this,*this,Settings4,StateMachine3.GetPointer()));

			// Internally EXECUTES STATE MACHINE to START STATE.
			Processor.AddStateMachine(StateMachine1);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID1,StateMachineID1,StateMachine2)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID2,StateMachineID2,StateMachine3)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID3,StateMachineID3,StateMachine4)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInputSendStateOutput(new CStateInputSendStateOutput(StateMachineID1,StateMachineID1,CSPStateOutput(new CStateOutput1(StateMachineID1,"STATE 1")))));
				
			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInputSendStateOutput(new CStateInputSendStateOutput(StateMachineID2,StateMachineID2,CSPStateOutput(new CStateOutput2(StateMachineID2,"STATE 2")))));
				
			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInputSendStateOutput(new CStateInputSendStateOutput(StateMachineID3,StateMachineID3,CSPStateOutput(new CStateOutput3(StateMachineID3,"STATE 3")))));
				
			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInputSendStateOutput(new CStateInputSendStateOutput(StateMachineID4,StateMachineID4,CSPStateOutput(new CStateOutput4(StateMachineID4,"STATE 4")))));
				
			Processor.ExecuteStateMachines();

			// STATE OUTPUT is NOT FIRED because it's STOPPED in STATE MACHINE 2.
			Processor.AddStateInput(CSPStateInputSendStateOutput(new CStateInputSendStateOutput(StateMachineID4,StateMachineID4,CSPStateOutput(new CStateOutput1(StateMachineID1,"STATE 1")))));
				
			Processor.ExecuteStateMachines();

			// STATE OUTPUT is NOT FIRED because it's STOPPED in STATE MACHINE 3.
			Processor.AddStateInput(CSPStateInputSendStateOutput(new CStateInputSendStateOutput(StateMachineID4,StateMachineID4,CSPStateOutput(new CStateOutput2(StateMachineID2,"STATE 2")))));
				
			Processor.ExecuteStateMachines();

			// STATE OUTPUT is NOT FIRED because it's STOPPED in STATE MACHINE 4.
			Processor.AddStateInput(CSPStateInputSendStateOutput(new CStateInputSendStateOutput(StateMachineID4,StateMachineID4,CSPStateOutput(new CStateOutput3(StateMachineID3,"STATE 3")))));
				
			Processor.ExecuteStateMachines();

			CTimeout											Timeout=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (CheckStateMachineTimeout(Timeout,false,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine1,1,37,0,0,0,0,0,1,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine1,0,3,4,1,1,1,1,3,3,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine2,1,30,0,0,0,0,0,1,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine2,0,3,4,1,1,1,1,2,2,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine3,1,23,0,0,0,0,0,1,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine3,0,3,4,1,1,1,1,1,1,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine4,1,16,0,0,0,0,0,1,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine4,0,3,4,1,1,1,1,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID2,StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID2}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID3}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (MOutputCollection.GetLength()!=4)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=0)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestChildStateMachineInvalidChildStateMachine1(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID1("SM1");
			CStateMachineID										StateMachineID2("SM2");
			CTimeout											StateMachineTimeout(10*1000*1000);
			// STATE MACHINES PROCESSOR doesn't START STATE MACHINES implicitly.
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(false)));
			CSPTestStateMachineSettings1						Settings1(new CTestStateMachineSettings1(StateMachineID1,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings2						Settings2(new CTestStateMachineSettings2(StateMachineID2,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachine1								StateMachine1(new CTestStateMachine1(*this,*this,Settings1,nullptr));
			CSPTestStateMachine2								StateMachine2(new CTestStateMachine2(*this,*this,Settings2,StateMachine1.GetPointer()));

			// Internally doesn't EXECUTE STATE MACHINE to START STATE.
			Processor.AddStateMachine(StateMachine1);

			Processor.ExecuteStateMachines();

			// CHILD STATE MACHINE can't be ADDED to NON RUNNING STATE MACHINE.
			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID1,StateMachineID1,StateMachine2)));

			Processor.ExecuteStateMachines();

			// START STATE MACHINE.
			StateMachine1->StartStateMachine();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			// START STATE MACHINE.
			StateMachine2->StartStateMachine();

			// STARTED STATE MACHINE can't be ADDED as CHILD STATE MACHINE.
			// EXCEPTION is THROWN and STATE MACHINE 1 is TERMINATED.
			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID1,StateMachineID1,StateMachine2)));

			Processor.ExecuteStateMachines();

			if (CheckStateMachineState1(StateMachine1,1,4,0,0,0,0,1,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine1,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (StateMachine1->TestGetChildStateMachineByID(StateMachineID2)!=nullptr)
			{
				return(false);
			}

			if (StateMachine1->TestHasChildStateMachineByID(StateMachineID2)==true)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=3)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestChildStateMachineInvalidChildStateMachine2(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID1("SM1");
			CStateMachineID										StateMachineID2("SM2");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSPTestStateMachineSettings1						Settings1(new CTestStateMachineSettings1(StateMachineID1,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings2						Settings2(new CTestStateMachineSettings2(StateMachineID2,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachine1								StateMachine1(new CTestStateMachine1(*this,*this,Settings1,nullptr));
			// PARENT STATE MACHINE ID is NOT SET.
			CSPTestStateMachine2								StateMachine2(new CTestStateMachine2(*this,*this,Settings2,nullptr));

			// Internally EXECUTES STATE MACHINE to START STATE.
			Processor.AddStateMachine(StateMachine1);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			// STATE MACHINE can't be ADDED as CHILD STATE MACHINE because INVALID PARENT STATE MACHINE ID is SET.
			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID1,StateMachineID1,StateMachine2)));

			Processor.ExecuteStateMachines();

			if (CheckStateMachineState1(StateMachine1,1,5,0,0,0,0,1,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine1,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (StateMachine1->TestGetChildStateMachineByID(StateMachineID2)!=nullptr)
			{
				return(false);
			}

			if (StateMachine1->TestHasChildStateMachineByID(StateMachineID2)==true)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=2)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestChildStateMachineInvalidChildStateMachine3(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID1("SM1");
			CStateMachineID										StateMachineID2("SM2");
			// DUPLICATE STATE MACHINE ID.
			CStateMachineID										StateMachineID3("SM2");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSPTestStateMachineSettings1						Settings1(new CTestStateMachineSettings1(StateMachineID1,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings2						Settings2(new CTestStateMachineSettings2(StateMachineID2,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings3						Settings3(new CTestStateMachineSettings3(StateMachineID3,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachine1								StateMachine1(new CTestStateMachine1(*this,*this,Settings1,nullptr));
			CSPTestStateMachine2								StateMachine2(new CTestStateMachine2(*this,*this,Settings2,StateMachine1.GetPointer()));
			CSPTestStateMachine3								StateMachine3(new CTestStateMachine3(*this,*this,Settings3,StateMachine2.GetPointer()));

			// Internally EXECUTES STATE MACHINE to START STATE.
			Processor.AddStateMachine(StateMachine1);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID1,StateMachineID1,StateMachine2)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			// STATE MACHINE can't be ADDED as CHILD STATE MACHINE because it has SAME STATE MACHINE ID as PARENT STATE MACHINE.
			// STATE MACHINE 2 thows EXCEPTION and will be TERMINATED.
			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID2,StateMachineID2,StateMachine3)));

			Processor.ExecuteStateMachines();

			// STATE INPUT won't be PROCESSED, because STATE MACHINE was TERMINATED.
			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (CheckStateMachineState1(StateMachine1,1,13,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine1,0,3,0,0,0,0,0,1,1,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine2,1,5,0,0,0,0,1,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine2,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID2}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID2}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (StateMachine1->TestGetChildStateMachineByID(StateMachineID2)==nullptr)
			{
				return(false);
			}

			if (StateMachine1->TestHasChildStateMachineByID(StateMachineID2)==false)
			{
				return(false);
			}

			if (StateMachine2->TestHasChildStateMachineByID(StateMachineID2)==true)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=3)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestChildStateMachineInvalidChildStateMachine4(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID1("SM1");
			CStateMachineID										StateMachineID2("SM2");
			// DUPLICATE STATE MACHINE ID.
			CStateMachineID										StateMachineID3("SM2");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSPTestStateMachineSettings1						Settings1(new CTestStateMachineSettings1(StateMachineID1,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings2						Settings2(new CTestStateMachineSettings2(StateMachineID2,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings3						Settings3(new CTestStateMachineSettings3(StateMachineID3,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachine1								StateMachine1(new CTestStateMachine1(*this,*this,Settings1,nullptr));
			CSPTestStateMachine2								StateMachine2(new CTestStateMachine2(*this,*this,Settings2,StateMachine1.GetPointer()));
			CSPTestStateMachine3								StateMachine3(new CTestStateMachine3(*this,*this,Settings3,StateMachine1.GetPointer()));

			// Internally EXECUTES STATE MACHINE to START STATE.
			Processor.AddStateMachine(StateMachine1);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID1,StateMachineID1,StateMachine2)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			// STATE MACHINE can't be ADDED as CHILD STATE MACHINE because it has SAME STATE MACHINE ID as PARENT STATE MACHINE.
			// STATE MACHINE 2 is ALSO TERMINATED because it's CHILD MACHINE to STATE MACHINE 1.
			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID1,StateMachineID1,StateMachine3)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (CheckStateMachineState1(StateMachine1,1,9,0,0,0,0,1,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine1,0,3,0,0,0,0,0,1,1,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine2,1,4,0,0,0,0,1,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine2,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID2}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID2}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (StateMachine1->TestGetChildStateMachineByID(StateMachineID2)==nullptr)
			{
				return(false);
			}

			if (StateMachine1->TestHasChildStateMachineByID(StateMachineID2)==false)
			{
				return(false);
			}

			if (StateMachine2->TestHasChildStateMachineByID(StateMachineID2)==true)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=6)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestChildStateMachineTerminate1(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID1("SM1");
			CStateMachineID										StateMachineID2("SM2");
			CStateMachineID										StateMachineID3("SM3");
			CStateMachineID										StateMachineID4("SM4");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSPTestStateMachineSettings1						Settings1(new CTestStateMachineSettings1(StateMachineID1,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings2						Settings2(new CTestStateMachineSettings2(StateMachineID2,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings3						Settings3(new CTestStateMachineSettings3(StateMachineID3,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings4(new CTestStateMachineSettings4(StateMachineID4,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachine1								StateMachine1(new CTestStateMachine1(*this,*this,Settings1,nullptr));
			CSPTestStateMachine2								StateMachine2(new CTestStateMachine2(*this,*this,Settings2,StateMachine1.GetPointer()));
			CSPTestStateMachine3								StateMachine3(new CTestStateMachine3(*this,*this,Settings3,StateMachine2.GetPointer()));
			CSPTestStateMachine4								StateMachine4(new CTestStateMachine4(*this,*this,Settings4,StateMachine3.GetPointer()));

			// Internally EXECUTES STATE MACHINE to START STATE.
			Processor.AddStateMachine(StateMachine1);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID1,StateMachineID1,StateMachine2)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID2,StateMachineID2,StateMachine3)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID3,StateMachineID3,StateMachine4)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			// Doesn't TERMINATE ANY STATEM MACHINE, because STATE MACHINES PROCESSOR doesn't contain STATE MACHINE with ID 'StateMachineID4'.
			Processor.TerminateStateMachines([StateMachineID4](CSPStateMachine StateMachine)->bool{return(StateMachine->GetStateMachineID()==StateMachineID4);});

			StateMachine4->TerminateStateMachine();

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (CheckStateMachineState1(StateMachine1,1,24,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine1,0,3,0,0,0,0,0,3,3,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine2,1,18,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine2,0,3,0,0,0,0,0,2,2,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine3,1,12,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine3,0,3,0,0,0,0,0,1,1,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine4,1,4,0,0,0,0,1,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine4,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID2,StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID2}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID3}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=1)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestChildStateMachineTerminate2(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID1("SM1");
			CStateMachineID										StateMachineID2("SM2");
			CStateMachineID										StateMachineID3("SM3");
			CStateMachineID										StateMachineID4("SM4");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSPTestStateMachineSettings1						Settings1(new CTestStateMachineSettings1(StateMachineID1,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings2						Settings2(new CTestStateMachineSettings2(StateMachineID2,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings3						Settings3(new CTestStateMachineSettings3(StateMachineID3,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings4(new CTestStateMachineSettings4(StateMachineID4,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachine1								StateMachine1(new CTestStateMachine1(*this,*this,Settings1,nullptr));
			CSPTestStateMachine2								StateMachine2(new CTestStateMachine2(*this,*this,Settings2,StateMachine1.GetPointer()));
			CSPTestStateMachine3								StateMachine3(new CTestStateMachine3(*this,*this,Settings3,StateMachine2.GetPointer()));
			CSPTestStateMachine4								StateMachine4(new CTestStateMachine4(*this,*this,Settings4,StateMachine3.GetPointer()));

			// Internally EXECUTES STATE MACHINE to START STATE.
			Processor.AddStateMachine(StateMachine1);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID1,StateMachineID1,StateMachine2)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID2,StateMachineID2,StateMachine3)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID3,StateMachineID3,StateMachine4)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			StateMachine3->TerminateStateMachine();

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (CheckStateMachineState1(StateMachine1,1,24,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine1,0,3,0,0,0,0,0,3,3,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine2,1,18,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine2,0,3,0,0,0,0,0,2,2,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine3,1,8,0,0,0,0,1,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine3,0,3,0,0,0,0,0,1,1,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine4,1,4,0,0,0,0,1,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine4,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID2,StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID2}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID3}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=2)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestChildStateMachineTerminate3(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID1("SM1");
			CStateMachineID										StateMachineID2("SM2");
			CStateMachineID										StateMachineID3("SM3");
			CStateMachineID										StateMachineID4("SM4");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSPTestStateMachineSettings1						Settings1(new CTestStateMachineSettings1(StateMachineID1,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings2						Settings2(new CTestStateMachineSettings2(StateMachineID2,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings3						Settings3(new CTestStateMachineSettings3(StateMachineID3,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings4(new CTestStateMachineSettings4(StateMachineID4,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachine1								StateMachine1(new CTestStateMachine1(*this,*this,Settings1,nullptr));
			CSPTestStateMachine2								StateMachine2(new CTestStateMachine2(*this,*this,Settings2,StateMachine1.GetPointer()));
			CSPTestStateMachine3								StateMachine3(new CTestStateMachine3(*this,*this,Settings3,StateMachine2.GetPointer()));
			CSPTestStateMachine4								StateMachine4(new CTestStateMachine4(*this,*this,Settings4,StateMachine3.GetPointer()));

			// Internally EXECUTES STATE MACHINE to START STATE.
			Processor.AddStateMachine(StateMachine1);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID1,StateMachineID1,StateMachine2)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID2,StateMachineID2,StateMachine3)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID3,StateMachineID3,StateMachine4)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			StateMachine2->TerminateStateMachine();

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (CheckStateMachineState1(StateMachine1,1,24,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine1,0,3,0,0,0,0,0,3,3,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine2,1,12,0,0,0,0,1,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine2,0,3,0,0,0,0,0,2,2,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine3,1,8,0,0,0,0,1,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine3,0,3,0,0,0,0,0,1,1,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine4,1,4,0,0,0,0,1,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine4,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID2,StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID2}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID3}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=3)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestChildStateMachineTerminate4(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID1("SM1");
			CStateMachineID										StateMachineID2("SM2");
			CStateMachineID										StateMachineID3("SM3");
			CStateMachineID										StateMachineID4("SM4");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSPTestStateMachineSettings1						Settings1(new CTestStateMachineSettings1(StateMachineID1,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings2						Settings2(new CTestStateMachineSettings2(StateMachineID2,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings3						Settings3(new CTestStateMachineSettings3(StateMachineID3,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings4(new CTestStateMachineSettings4(StateMachineID4,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachine1								StateMachine1(new CTestStateMachine1(*this,*this,Settings1,nullptr));
			CSPTestStateMachine2								StateMachine2(new CTestStateMachine2(*this,*this,Settings2,StateMachine1.GetPointer()));
			CSPTestStateMachine3								StateMachine3(new CTestStateMachine3(*this,*this,Settings3,StateMachine2.GetPointer()));
			CSPTestStateMachine4								StateMachine4(new CTestStateMachine4(*this,*this,Settings4,StateMachine3.GetPointer()));

			// Internally EXECUTES STATE MACHINE to START STATE.
			Processor.AddStateMachine(StateMachine1);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID1,StateMachineID1,StateMachine2)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID2,StateMachineID2,StateMachine3)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID3,StateMachineID3,StateMachine4)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			StateMachine1->TerminateStateMachine();

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (CheckStateMachineState1(StateMachine1,1,16,0,0,0,0,1,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine1,0,3,0,0,0,0,0,3,3,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine2,1,12,0,0,0,0,1,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine2,0,3,0,0,0,0,0,2,2,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine3,1,8,0,0,0,0,1,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine3,0,3,0,0,0,0,0,1,1,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine4,1,4,0,0,0,0,1,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine4,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID2,StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID2}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID3}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=8)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestChildStateMachineTerminate5(void)
	{
		try
		{
			Reset();

			CSteadyClock::Milliseconds							CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();
			CStateMachineID										StateMachineID1("SM1");
			CStateMachineID										StateMachineID21("SM21");
			CStateMachineID										StateMachineID22("SM22");
			CStateMachineID										StateMachineID31("SM31");
			CStateMachineID										StateMachineID32("SM32");
			CStateMachineID										StateMachineID33("SM33");
			CStateMachineID										StateMachineID34("SM34");
			CStateMachineID										StateMachineID41("SM41");
			CStateMachineID										StateMachineID42("SM42");
			CStateMachineID										StateMachineID43("SM43");
			CStateMachineID										StateMachineID44("SM44");
			CStateMachineID										StateMachineID45("SM45");
			CStateMachineID										StateMachineID46("SM46");
			CStateMachineID										StateMachineID47("SM47");
			CStateMachineID										StateMachineID48("SM48");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSPTestStateMachineSettings1						Settings1(new CTestStateMachineSettings1(StateMachineID1,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings2						Settings21(new CTestStateMachineSettings2(StateMachineID21,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings2						Settings22(new CTestStateMachineSettings2(StateMachineID22,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings3						Settings31(new CTestStateMachineSettings3(StateMachineID31,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings3						Settings32(new CTestStateMachineSettings3(StateMachineID32,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings3						Settings33(new CTestStateMachineSettings3(StateMachineID33,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings3						Settings34(new CTestStateMachineSettings3(StateMachineID34,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings41(new CTestStateMachineSettings4(StateMachineID41,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings42(new CTestStateMachineSettings4(StateMachineID42,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings43(new CTestStateMachineSettings4(StateMachineID43,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings44(new CTestStateMachineSettings4(StateMachineID44,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings45(new CTestStateMachineSettings4(StateMachineID45,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings46(new CTestStateMachineSettings4(StateMachineID46,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings47(new CTestStateMachineSettings4(StateMachineID47,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings48(new CTestStateMachineSettings4(StateMachineID48,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachine1								StateMachine1(new CTestStateMachine1(*this,*this,Settings1,nullptr));
			CSPTestStateMachine2								StateMachine21(new CTestStateMachine2(*this,*this,Settings21,StateMachine1.GetPointer()));
			CSPTestStateMachine2								StateMachine22(new CTestStateMachine2(*this,*this,Settings22,StateMachine1.GetPointer()));
			CSPTestStateMachine3								StateMachine31(new CTestStateMachine3(*this,*this,Settings31,StateMachine21.GetPointer()));
			CSPTestStateMachine3								StateMachine32(new CTestStateMachine3(*this,*this,Settings32,StateMachine21.GetPointer()));
			CSPTestStateMachine3								StateMachine33(new CTestStateMachine3(*this,*this,Settings33,StateMachine22.GetPointer()));
			CSPTestStateMachine3								StateMachine34(new CTestStateMachine3(*this,*this,Settings34,StateMachine22.GetPointer()));
			CSPTestStateMachine4								StateMachine41(new CTestStateMachine4(*this,*this,Settings41,StateMachine31.GetPointer()));
			CSPTestStateMachine4								StateMachine42(new CTestStateMachine4(*this,*this,Settings42,StateMachine31.GetPointer()));
			CSPTestStateMachine4								StateMachine43(new CTestStateMachine4(*this,*this,Settings43,StateMachine32.GetPointer()));
			CSPTestStateMachine4								StateMachine44(new CTestStateMachine4(*this,*this,Settings44,StateMachine32.GetPointer()));
			CSPTestStateMachine4								StateMachine45(new CTestStateMachine4(*this,*this,Settings45,StateMachine33.GetPointer()));
			CSPTestStateMachine4								StateMachine46(new CTestStateMachine4(*this,*this,Settings46,StateMachine33.GetPointer()));
			CSPTestStateMachine4								StateMachine47(new CTestStateMachine4(*this,*this,Settings47,StateMachine34.GetPointer()));
			CSPTestStateMachine4								StateMachine48(new CTestStateMachine4(*this,*this,Settings48,StateMachine34.GetPointer()));

			// Internally EXECUTES STATE MACHINE to START STATE.
			Processor.AddStateMachine(StateMachine1);

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID1,StateMachineID1,StateMachine21)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID21,CTestStateMachine2::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID1,StateMachineID1,StateMachine22)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID22,CTestStateMachine2::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID21,StateMachineID21,StateMachine31)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID31,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID21,StateMachineID21,StateMachine32)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID32,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID22,StateMachineID22,StateMachine33)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID33,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID22,StateMachineID22,StateMachine34)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID34,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID31,StateMachineID31,StateMachine41)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID41,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID31,StateMachineID31,StateMachine42)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID42,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID32,StateMachineID32,StateMachine43)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID43,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID32,StateMachineID32,StateMachine44)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID44,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID33,StateMachineID33,StateMachine45)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID45,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID33,StateMachineID33,StateMachine46)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID46,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID34,StateMachineID34,StateMachine47)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID47,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID34,StateMachineID34,StateMachine48)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID48,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			// ALL STATE MACHINES are RUNNING.
			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			StateMachine21->TerminateStateMachine();

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			// STATE MACHINE has already been TERMINATED.
			StateMachine31->TerminateStateMachine();

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			StateMachine33->TerminateStateMachine();

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID41,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID42,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID43,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID44,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID45,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID46,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID47,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID48,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID31,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID32,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID33,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID34,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID21,CTestStateMachine2::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID22,CTestStateMachine2::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID21,StateMachineID22,StateMachineID31,StateMachineID32,StateMachineID33,StateMachineID34,StateMachineID41,StateMachineID42,StateMachineID43,StateMachineID44,StateMachineID45,StateMachineID46,StateMachineID47,StateMachineID48}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine21->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID31,StateMachineID32,StateMachineID41,StateMachineID42,StateMachineID43,StateMachineID44}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine22->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID33,StateMachineID34,StateMachineID45,StateMachineID46,StateMachineID47,StateMachineID48}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine31->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID41,StateMachineID42}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine32->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID43,StateMachineID44}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine33->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID45,StateMachineID46}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine34->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID47,StateMachineID48}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine41->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine42->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine43->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine44->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine45->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine46->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine47->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine48->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID21,StateMachineID22}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine21->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID31,StateMachineID32}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine22->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID33,StateMachineID34}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine31->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID41,StateMachineID42}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine32->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID43,StateMachineID44}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine33->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID45,StateMachineID46}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine34->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID47,StateMachineID48}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine41->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine42->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine43->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine44->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine45->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine46->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine47->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine48->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine1,1,93,0,0,0,0,0,48,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine1,0,3,0,0,0,0,0,14,14,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine21,1,43,0,0,0,0,1,29,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine21,0,3,0,0,0,0,0,6,6,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine22,1,64,0,0,0,0,0,43,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine22,0,3,0,0,0,0,0,6,6,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine31,1,31,0,0,0,0,1,25,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine31,0,3,0,0,0,0,0,2,2,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine32,1,29,0,0,0,0,1,23,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine32,0,3,0,0,0,0,0,2,2,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine33,1,29,0,0,0,0,1,23,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine33,0,3,0,0,0,0,0,2,2,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine34,1,42,0,0,0,0,0,33,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine34,0,3,0,0,0,0,0,2,2,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine41,1,19,0,0,0,0,1,17,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine41,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine42,1,17,0,0,0,0,1,15,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine42,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine43,1,15,0,0,0,0,1,13,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine43,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine44,1,13,0,0,0,0,1,11,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine44,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine45,1,13,0,0,0,0,1,11,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine45,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine46,1,11,0,0,0,0,1,9,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine46,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine47,1,17,0,0,0,0,0,14,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine47,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine48,1,16,0,0,0,0,0,13,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine48,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=10)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestChildStateMachineExpire1(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID1("SM1");
			CStateMachineID										StateMachineID2("SM2");
			CStateMachineID										StateMachineID3("SM3");
			CStateMachineID										StateMachineID4("SM4");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTimeout											StateMachineTimeoutShort(1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSPTestStateMachineSettings1						Settings1(new CTestStateMachineSettings1(StateMachineID1,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings2						Settings2(new CTestStateMachineSettings2(StateMachineID2,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings3						Settings3(new CTestStateMachineSettings3(StateMachineID3,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings4(new CTestStateMachineSettings4(StateMachineID4,CPriority(100),StateMachineTimeoutShort,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachine1								StateMachine1(new CTestStateMachine1(*this,*this,Settings1,nullptr));
			CSPTestStateMachine2								StateMachine2(new CTestStateMachine2(*this,*this,Settings2,StateMachine1.GetPointer()));
			CSPTestStateMachine3								StateMachine3(new CTestStateMachine3(*this,*this,Settings3,StateMachine2.GetPointer()));
			// STATE MACHINE has SHORT EXPIRATION TIMEOUT.
			CSPTestStateMachine4								StateMachine4(new CTestStateMachine4(*this,*this,Settings4,StateMachine3.GetPointer()));

			// Internally EXECUTES STATE MACHINE to START STATE.
			Processor.AddStateMachine(StateMachine1);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID1,StateMachineID1,StateMachine2)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID2,StateMachineID2,StateMachine3)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID3,StateMachineID3,StateMachine4)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			// Wait for STATE MACHINE EXPIRATION.
			CThread::Sleep(static_cast<uint64>(StateMachineTimeoutShort.GetTimeoutInMS()));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (CheckStateMachineState1(StateMachine1,1,24,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine1,0,3,0,0,0,0,0,3,3,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine2,1,18,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine2,0,3,0,0,0,0,0,2,2,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine3,1,12,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine3,0,3,0,0,0,0,0,1,1,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine4,1,4,0,0,0,0,1,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine4,1,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID2,StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID2}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID3}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=1)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestChildStateMachineExpire2(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID1("SM1");
			CStateMachineID										StateMachineID2("SM2");
			CStateMachineID										StateMachineID3("SM3");
			CStateMachineID										StateMachineID4("SM4");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTimeout											StateMachineTimeoutShort(1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSPTestStateMachineSettings1						Settings1(new CTestStateMachineSettings1(StateMachineID1,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings2						Settings2(new CTestStateMachineSettings2(StateMachineID2,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings3						Settings3(new CTestStateMachineSettings3(StateMachineID3,CPriority(100),StateMachineTimeoutShort,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings4(new CTestStateMachineSettings4(StateMachineID4,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachine1								StateMachine1(new CTestStateMachine1(*this,*this,Settings1,nullptr));
			CSPTestStateMachine2								StateMachine2(new CTestStateMachine2(*this,*this,Settings2,StateMachine1.GetPointer()));
			// STATE MACHINE has SHORT EXPIRATION TIMEOUT.
			CSPTestStateMachine3								StateMachine3(new CTestStateMachine3(*this,*this,Settings3,StateMachine2.GetPointer()));
			CSPTestStateMachine4								StateMachine4(new CTestStateMachine4(*this,*this,Settings4,StateMachine3.GetPointer()));

			// Internally EXECUTES STATE MACHINE to START STATE.
			Processor.AddStateMachine(StateMachine1);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID1,StateMachineID1,StateMachine2)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID2,StateMachineID2,StateMachine3)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID3,StateMachineID3,StateMachine4)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			// Wait for STATE MACHINE EXPIRATION.
			CThread::Sleep(static_cast<uint64>(StateMachineTimeoutShort.GetTimeoutInMS()));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (CheckStateMachineState1(StateMachine1,1,24,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine1,0,3,0,0,0,0,0,3,3,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine2,1,18,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine2,0,3,0,0,0,0,0,2,2,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine3,1,8,0,0,0,0,1,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine3,1,3,0,0,0,0,0,1,1,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine4,1,4,0,0,0,0,1,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine4,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID2,StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID2}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID3}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=2)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestChildStateMachineExpire3(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID1("SM1");
			CStateMachineID										StateMachineID2("SM2");
			CStateMachineID										StateMachineID3("SM3");
			CStateMachineID										StateMachineID4("SM4");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTimeout											StateMachineTimeoutShort(1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSPTestStateMachineSettings1						Settings1(new CTestStateMachineSettings1(StateMachineID1,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings2						Settings2(new CTestStateMachineSettings2(StateMachineID2,CPriority(100),StateMachineTimeoutShort,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings3						Settings3(new CTestStateMachineSettings3(StateMachineID3,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings4(new CTestStateMachineSettings4(StateMachineID4,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachine1								StateMachine1(new CTestStateMachine1(*this,*this,Settings1,nullptr));
			// STATE MACHINE has SHORT EXPIRATION TIMEOUT.
			CSPTestStateMachine2								StateMachine2(new CTestStateMachine2(*this,*this,Settings2,StateMachine1.GetPointer()));
			CSPTestStateMachine3								StateMachine3(new CTestStateMachine3(*this,*this,Settings3,StateMachine2.GetPointer()));
			CSPTestStateMachine4								StateMachine4(new CTestStateMachine4(*this,*this,Settings4,StateMachine3.GetPointer()));

			// Internally EXECUTES STATE MACHINE to START STATE.
			Processor.AddStateMachine(StateMachine1);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID1,StateMachineID1,StateMachine2)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID2,StateMachineID2,StateMachine3)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID3,StateMachineID3,StateMachine4)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			// Wait for STATE MACHINE EXPIRATION.
			CThread::Sleep(static_cast<uint64>(StateMachineTimeoutShort.GetTimeoutInMS()));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (CheckStateMachineState1(StateMachine1,1,24,0,0,0,0,0,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine1,0,3,0,0,0,0,0,3,3,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine2,1,12,0,0,0,0,1,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine2,1,3,0,0,0,0,0,2,2,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine3,1,8,0,0,0,0,1,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine3,0,3,0,0,0,0,0,1,1,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine4,1,4,0,0,0,0,1,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine4,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID2,StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID2}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID3}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=3)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestChildStateMachineExpire4(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID1("SM1");
			CStateMachineID										StateMachineID2("SM2");
			CStateMachineID										StateMachineID3("SM3");
			CStateMachineID										StateMachineID4("SM4");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTimeout											StateMachineTimeoutShort(1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSPTestStateMachineSettings1						Settings1(new CTestStateMachineSettings1(StateMachineID1,CPriority(100),StateMachineTimeoutShort,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings2						Settings2(new CTestStateMachineSettings2(StateMachineID2,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings3						Settings3(new CTestStateMachineSettings3(StateMachineID3,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings4(new CTestStateMachineSettings4(StateMachineID4,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			// STATE MACHINE has SHORT EXPIRATION TIMEOUT.
			CSPTestStateMachine1								StateMachine1(new CTestStateMachine1(*this,*this,Settings1,nullptr));
			CSPTestStateMachine2								StateMachine2(new CTestStateMachine2(*this,*this,Settings2,StateMachine1.GetPointer()));
			CSPTestStateMachine3								StateMachine3(new CTestStateMachine3(*this,*this,Settings3,StateMachine2.GetPointer()));
			CSPTestStateMachine4								StateMachine4(new CTestStateMachine4(*this,*this,Settings4,StateMachine3.GetPointer()));

			// Internally EXECUTES STATE MACHINE to START STATE.
			Processor.AddStateMachine(StateMachine1);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID1,StateMachineID1,StateMachine2)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID2,StateMachineID2,StateMachine3)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID3,StateMachineID3,StateMachine4)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			// Wait for STATE MACHINE EXPIRATION.
			CThread::Sleep(static_cast<uint64>(StateMachineTimeoutShort.GetTimeoutInMS()));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (CheckStateMachineState1(StateMachine1,1,16,0,0,0,0,1,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine1,1,3,0,0,0,0,0,3,3,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine2,1,12,0,0,0,0,1,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine2,0,3,0,0,0,0,0,2,2,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine3,1,8,0,0,0,0,1,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine3,0,3,0,0,0,0,0,1,1,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine4,1,4,0,0,0,0,1,0,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine4,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID2,StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID2}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID3}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=8)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestChildStateMachineExpire5(void)
	{
		try
		{
			Reset();

			CSteadyClock::Milliseconds							CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();
			CStateMachineID										StateMachineID1("SM1");
			CStateMachineID										StateMachineID21("SM21");
			CStateMachineID										StateMachineID22("SM22");
			CStateMachineID										StateMachineID31("SM31");
			CStateMachineID										StateMachineID32("SM32");
			CStateMachineID										StateMachineID33("SM33");
			CStateMachineID										StateMachineID34("SM34");
			CStateMachineID										StateMachineID41("SM41");
			CStateMachineID										StateMachineID42("SM42");
			CStateMachineID										StateMachineID43("SM43");
			CStateMachineID										StateMachineID44("SM44");
			CStateMachineID										StateMachineID45("SM45");
			CStateMachineID										StateMachineID46("SM46");
			CStateMachineID										StateMachineID47("SM47");
			CStateMachineID										StateMachineID48("SM48");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTimeout											StateMachineTimeoutShort(1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSPTestStateMachineSettings1						Settings1(new CTestStateMachineSettings1(StateMachineID1,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings2						Settings21(new CTestStateMachineSettings2(StateMachineID21,CPriority(100),StateMachineTimeoutShort,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings2						Settings22(new CTestStateMachineSettings2(StateMachineID22,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings3						Settings31(new CTestStateMachineSettings3(StateMachineID31,CPriority(100),StateMachineTimeoutShort,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings3						Settings32(new CTestStateMachineSettings3(StateMachineID32,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings3						Settings33(new CTestStateMachineSettings3(StateMachineID33,CPriority(100),StateMachineTimeoutShort,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings3						Settings34(new CTestStateMachineSettings3(StateMachineID34,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings41(new CTestStateMachineSettings4(StateMachineID41,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings42(new CTestStateMachineSettings4(StateMachineID42,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings43(new CTestStateMachineSettings4(StateMachineID43,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings44(new CTestStateMachineSettings4(StateMachineID44,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings45(new CTestStateMachineSettings4(StateMachineID45,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings46(new CTestStateMachineSettings4(StateMachineID46,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings47(new CTestStateMachineSettings4(StateMachineID47,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineSettings4						Settings48(new CTestStateMachineSettings4(StateMachineID48,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachine1								StateMachine1(new CTestStateMachine1(*this,*this,Settings1,nullptr));
			// STATE MACHINE has SHORT EXPIRATION TIMEOUT.
			CSPTestStateMachine2								StateMachine21(new CTestStateMachine2(*this,*this,Settings21,StateMachine1.GetPointer()));
			CSPTestStateMachine2								StateMachine22(new CTestStateMachine2(*this,*this,Settings22,StateMachine1.GetPointer()));
			// STATE MACHINE has SHORT EXPIRATION TIMEOUT.
			CSPTestStateMachine3								StateMachine31(new CTestStateMachine3(*this,*this,Settings31,StateMachine21.GetPointer()));
			CSPTestStateMachine3								StateMachine32(new CTestStateMachine3(*this,*this,Settings32,StateMachine21.GetPointer()));
			// STATE MACHINE has SHORT EXPIRATION TIMEOUT.
			CSPTestStateMachine3								StateMachine33(new CTestStateMachine3(*this,*this,Settings33,StateMachine22.GetPointer()));
			CSPTestStateMachine3								StateMachine34(new CTestStateMachine3(*this,*this,Settings34,StateMachine22.GetPointer()));
			CSPTestStateMachine4								StateMachine41(new CTestStateMachine4(*this,*this,Settings41,StateMachine31.GetPointer()));
			CSPTestStateMachine4								StateMachine42(new CTestStateMachine4(*this,*this,Settings42,StateMachine31.GetPointer()));
			CSPTestStateMachine4								StateMachine43(new CTestStateMachine4(*this,*this,Settings43,StateMachine32.GetPointer()));
			CSPTestStateMachine4								StateMachine44(new CTestStateMachine4(*this,*this,Settings44,StateMachine32.GetPointer()));
			CSPTestStateMachine4								StateMachine45(new CTestStateMachine4(*this,*this,Settings45,StateMachine33.GetPointer()));
			CSPTestStateMachine4								StateMachine46(new CTestStateMachine4(*this,*this,Settings46,StateMachine33.GetPointer()));
			CSPTestStateMachine4								StateMachine47(new CTestStateMachine4(*this,*this,Settings47,StateMachine34.GetPointer()));
			CSPTestStateMachine4								StateMachine48(new CTestStateMachine4(*this,*this,Settings48,StateMachine34.GetPointer()));

			// Internally EXECUTES STATE MACHINE to START STATE.
			Processor.AddStateMachine(StateMachine1);

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID1,StateMachineID1,StateMachine21)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID21,CTestStateMachine2::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID1,StateMachineID1,StateMachine22)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID22,CTestStateMachine2::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID21,StateMachineID21,StateMachine31)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID31,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID21,StateMachineID21,StateMachine32)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID32,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID22,StateMachineID22,StateMachine33)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID33,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID22,StateMachineID22,StateMachine34)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID34,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID31,StateMachineID31,StateMachine41)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID41,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID31,StateMachineID31,StateMachine42)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID42,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID32,StateMachineID32,StateMachine43)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID43,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID32,StateMachineID32,StateMachine44)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID44,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID33,StateMachineID33,StateMachine45)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID45,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID33,StateMachineID33,StateMachine46)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID46,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID34,StateMachineID34,StateMachine47)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID47,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID34,StateMachineID34,StateMachine48)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID48,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			// ALL STATE MACHINES are RUNNING.
			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			// Wait for STATE MACHINE EXPIRATION.
			CThread::Sleep(static_cast<uint64>(StateMachineTimeoutShort.GetTimeoutInMS()));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID41,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID42,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID43,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID44,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID45,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID46,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID47,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID48,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID31,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID32,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID33,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID34,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID21,CTestStateMachine2::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID22,CTestStateMachine2::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID21,StateMachineID22,StateMachineID31,StateMachineID32,StateMachineID33,StateMachineID34,StateMachineID41,StateMachineID42,StateMachineID43,StateMachineID44,StateMachineID45,StateMachineID46,StateMachineID47,StateMachineID48}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine21->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID31,StateMachineID32,StateMachineID41,StateMachineID42,StateMachineID43,StateMachineID44}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine22->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID33,StateMachineID34,StateMachineID45,StateMachineID46,StateMachineID47,StateMachineID48}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine31->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID41,StateMachineID42}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine32->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID43,StateMachineID44}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine33->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID45,StateMachineID46}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine34->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID47,StateMachineID48}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine41->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine42->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine43->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine44->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine45->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine46->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine47->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine48->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID21,StateMachineID22}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine21->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID31,StateMachineID32}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine22->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID33,StateMachineID34}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine31->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID41,StateMachineID42}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine32->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID43,StateMachineID44}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine33->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID45,StateMachineID46}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine34->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID47,StateMachineID48}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine41->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine42->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine43->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine44->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine45->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine46->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine47->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine48->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine1,1,91,0,0,0,0,0,46,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine1,0,3,0,0,0,0,0,14,14,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine21,1,43,0,0,0,0,1,29,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine21,1,3,0,0,0,0,0,6,6,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine22,1,62,0,0,0,0,0,41,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine22,0,3,0,0,0,0,0,6,6,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine31,1,31,0,0,0,0,1,25,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine31,0,3,0,0,0,0,0,2,2,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine32,1,29,0,0,0,0,1,23,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine32,0,3,0,0,0,0,0,2,2,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine33,1,27,0,0,0,0,1,21,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine33,1,3,0,0,0,0,0,2,2,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine34,1,40,0,0,0,0,0,31,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine34,0,3,0,0,0,0,0,2,2,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine41,1,19,0,0,0,0,1,17,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine41,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine42,1,17,0,0,0,0,1,15,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine42,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine43,1,15,0,0,0,0,1,13,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine43,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine44,1,13,0,0,0,0,1,11,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine44,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine45,1,11,0,0,0,0,1,9,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine45,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine46,1,9,0,0,0,0,1,7,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine46,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine47,1,15,0,0,0,0,0,12,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine47,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine48,1,14,0,0,0,0,0,11,1,1)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine48,0,3,0,0,0,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=10)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestExceptionChildStateMachineExceptionExpiredEventInternalTerminateFinshed(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID1("SM1");
			CStateMachineID										StateMachineID2("SM2");
			CStateMachineID										StateMachineID3("SM3");
			CStateMachineID										StateMachineID4("SM4");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTimeout											StateMachineTimeoutShort(1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSteadyClock::Milliseconds							CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();
			CSPTestStateMachineExceptionSettings1				Settings1(new CTestStateMachineExceptionSettings1(StateMachineID1,CPriority(100),StateMachineTimeout,CTestStateMachineExceptionSettings(CTimeout(StateMachineTimeout)),CExpirationTime()));
			CSPTestStateMachineExceptionSettings2				Settings2(new CTestStateMachineExceptionSettings2(StateMachineID2,CPriority(100),StateMachineTimeoutShort,CTestStateMachineExceptionSettings(CTimeout(StateMachineTimeout)),CExpirationTime()));
			CSPTestStateMachineExceptionSettings3				Settings3(new CTestStateMachineExceptionSettings3(StateMachineID3,CPriority(100),StateMachineTimeout,CTestStateMachineExceptionSettings(CTimeout(StateMachineTimeout)),CExpirationTime()));
			CSPTestStateMachineExceptionSettings4				Settings4(new CTestStateMachineExceptionSettings4(StateMachineID4,CPriority(100),StateMachineTimeout,CTestStateMachineExceptionSettings(CTimeout(StateMachineTimeout)),CExpirationTime()));

			Settings2->GetStateMachineExceptionSettings().SetThrowExceptionOnStateMachineExpiredEvent(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_STATE_MACHINE,1,0));
			Settings3->GetStateMachineExceptionSettings().SetThrowExceptionOnInternalTerminateStateMachine(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_STATE_MACHINE,1,0));
			Settings4->GetStateMachineExceptionSettings().SetThrowExceptionOnStateMachineFinishedEvent(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_STATE_MACHINE,1,0));

			CSPTestStateMachineException1						StateMachine1(new CTestStateMachineException1(*this,*this,Settings1,nullptr));
			// STATE MACHINE has SHORT EXPIRATION TIMEOUT.
			CSPTestStateMachineException2						StateMachine2(new CTestStateMachineException2(*this,*this,Settings2,StateMachine1.GetPointer()));
			CSPTestStateMachineException3						StateMachine3(new CTestStateMachineException3(*this,*this,Settings3,StateMachine2.GetPointer()));
			CSPTestStateMachineException4						StateMachine4(new CTestStateMachineException4(*this,*this,Settings4,StateMachine3.GetPointer()));

			// Internally EXECUTES STATE MACHINE to START STATE.
			Processor.AddStateMachine(StateMachine1);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID1,StateMachineID1,StateMachine2)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID2,StateMachineID2,StateMachine3)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID3,StateMachineID3,StateMachine4)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			CTimeout											Timeout=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			// Wait for STATE MACHINE EXPIRATION.
			CThread::Sleep(static_cast<uint64>(StateMachineTimeoutShort.GetTimeoutInMS()));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (CheckStateMachineTimeout(Timeout,false,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine1,1,1,24,24,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine1,0,0,1,1,1,1,1,1,0,0,3,3)==false)
			{
				return(false);
			}

			if (CheckStateMachineState3(StateMachine1,0,0,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState4(StateMachine1,3,3,3,3,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine2,1,1,12,12,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine2,1,1,1,1,1,1,1,1,1,0,3,3)==false)
			{
				return(false);
			}

			if (CheckStateMachineState3(StateMachine2,0,0,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState4(StateMachine2,2,2,2,2,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine3,1,1,8,8,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine3,1,0,1,1,1,1,1,1,0,0,2,2)==false)
			{
				return(false);
			}

			if (CheckStateMachineState3(StateMachine3,0,0,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState4(StateMachine3,1,1,1,1,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine4,1,1,4,4,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine4,1,1,1,1,1,1,1,0,0,0,3,3)==false)
			{
				return(false);
			}

			if (CheckStateMachineState3(StateMachine4,0,0,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState4(StateMachine4,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID2,StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID2}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID3}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=6)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestExceptionChildStateMachineExceptionAddChildStateMachine(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID1("SM1");
			CStateMachineID										StateMachineID2("SM2");
			CStateMachineID										StateMachineID3("SM3");
			CStateMachineID										StateMachineID4("SM4");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSteadyClock::Milliseconds							CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();
			CSPTestStateMachineExceptionSettings1				Settings1(new CTestStateMachineExceptionSettings1(StateMachineID1,CPriority(100),StateMachineTimeout,CTestStateMachineExceptionSettings(CTimeout(StateMachineTimeout)),CExpirationTime()));
			CSPTestStateMachineExceptionSettings2				Settings2(new CTestStateMachineExceptionSettings2(StateMachineID2,CPriority(100),StateMachineTimeout,CTestStateMachineExceptionSettings(CTimeout(StateMachineTimeout)),CExpirationTime()));
			CSPTestStateMachineExceptionSettings3				Settings3(new CTestStateMachineExceptionSettings3(StateMachineID3,CPriority(100),StateMachineTimeout,CTestStateMachineExceptionSettings(CTimeout(StateMachineTimeout)),CExpirationTime()));
			CSPTestStateMachineExceptionSettings4				Settings4(new CTestStateMachineExceptionSettings4(StateMachineID4,CPriority(100),StateMachineTimeout,CTestStateMachineExceptionSettings(CTimeout(StateMachineTimeout)),CExpirationTime()));

			Settings2->GetStateMachineExceptionSettings().SetThrowExceptionOnChildStateMachineAddedEvent(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_STATE_MACHINE,1,1));
			Settings3->GetStateMachineExceptionSettings().SetThrowExceptionOnChildStateMachineAddedEvent(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_CSTRING,1,0));

			CSPTestStateMachineException1						StateMachine1(new CTestStateMachineException1(*this,*this,Settings1,nullptr));
			CSPTestStateMachineException2						StateMachine2(new CTestStateMachineException2(*this,*this,Settings2,StateMachine1.GetPointer()));
			CSPTestStateMachineException3						StateMachine3(new CTestStateMachineException3(*this,*this,Settings3,StateMachine2.GetPointer()));
			CSPTestStateMachineException4						StateMachine4(new CTestStateMachineException4(*this,*this,Settings4,StateMachine3.GetPointer()));

			// Internally EXECUTES STATE MACHINE to START STATE.
			Processor.AddStateMachine(StateMachine1);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID1,StateMachineID1,StateMachine2)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID2,StateMachineID2,StateMachine3)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID3,StateMachineID3,StateMachine4)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			CTimeout											Timeout=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (CheckStateMachineTimeout(Timeout,false,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine1,1,1,23,23,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine1,0,0,1,1,1,1,1,1,0,0,3,3)==false)
			{
				return(false);
			}

			if (CheckStateMachineState3(StateMachine1,0,0,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState4(StateMachine1,3,3,3,3,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine2,1,1,17,17,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine2,0,0,1,1,1,1,1,1,0,0,3,3)==false)
			{
				return(false);
			}

			if (CheckStateMachineState3(StateMachine2,0,0,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState4(StateMachine2,2,0,2,2,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine3,1,1,11,11,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine3,0,0,1,1,1,1,1,1,0,0,3,3)==false)
			{
				return(false);
			}

			if (CheckStateMachineState3(StateMachine3,0,0,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState4(StateMachine3,1,0,1,1,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine4,1,1,5,5,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine4,0,0,1,1,1,1,1,1,0,0,3,3)==false)
			{
				return(false);
			}

			if (CheckStateMachineState3(StateMachine4,0,0,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState4(StateMachine4,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID2,StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID2}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID3}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=3)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestExceptionChildStateMachineExceptionFinishedChildStateMachine(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID1("SM1");
			CStateMachineID										StateMachineID2("SM2");
			CStateMachineID										StateMachineID3("SM3");
			CStateMachineID										StateMachineID4("SM4");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(true)));
			CSteadyClock::Milliseconds							CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();
			CSPTestStateMachineExceptionSettings1				Settings1(new CTestStateMachineExceptionSettings1(StateMachineID1,CPriority(100),StateMachineTimeout,CTestStateMachineExceptionSettings(CTimeout(StateMachineTimeout)),CExpirationTime()));
			CSPTestStateMachineExceptionSettings2				Settings2(new CTestStateMachineExceptionSettings2(StateMachineID2,CPriority(100),StateMachineTimeout,CTestStateMachineExceptionSettings(CTimeout(StateMachineTimeout)),CExpirationTime()));
			CSPTestStateMachineExceptionSettings3				Settings3(new CTestStateMachineExceptionSettings3(StateMachineID3,CPriority(100),StateMachineTimeout,CTestStateMachineExceptionSettings(CTimeout(StateMachineTimeout)),CExpirationTime()));
			CSPTestStateMachineExceptionSettings4				Settings4(new CTestStateMachineExceptionSettings4(StateMachineID4,CPriority(100),StateMachineTimeout,CTestStateMachineExceptionSettings(CTimeout(StateMachineTimeout)),CExpirationTime()));

			Settings2->GetStateMachineExceptionSettings().SetThrowExceptionOnChildStateMachineFinishedEvent(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_STATE_MACHINE,1,1));
			Settings3->GetStateMachineExceptionSettings().SetThrowExceptionOnChildStateMachineFinishedEvent(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_CSTRING,1,0));

			CSPTestStateMachineException1						StateMachine1(new CTestStateMachineException1(*this,*this,Settings1,nullptr));
			CSPTestStateMachineException2						StateMachine2(new CTestStateMachineException2(*this,*this,Settings2,StateMachine1.GetPointer()));
			CSPTestStateMachineException3						StateMachine3(new CTestStateMachineException3(*this,*this,Settings3,StateMachine2.GetPointer()));
			CSPTestStateMachineException4						StateMachine4(new CTestStateMachineException4(*this,*this,Settings4,StateMachine3.GetPointer()));

			// Internally EXECUTES STATE MACHINE to START STATE.
			Processor.AddStateMachine(StateMachine1);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID1,StateMachineID1,StateMachine2)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID2,StateMachineID2,StateMachine3)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputAddChildStateMachine(StateMachineID3,StateMachineID3,StateMachine4)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			CTimeout											Timeout=Processor.GetStateMachinesTimeout(CurrentTimeInMS);

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID4,CTestStateMachine4::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID3,CTestStateMachine3::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID2,CTestStateMachine2::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID1,CTestStateMachine1::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (CheckStateMachineTimeout(Timeout,false,false)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine1,1,1,23,23,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine1,0,0,1,1,1,1,1,1,0,0,3,3)==false)
			{
				return(false);
			}

			if (CheckStateMachineState3(StateMachine1,0,0,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState4(StateMachine1,3,3,3,3,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine2,1,1,17,17,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine2,0,0,1,1,1,1,1,1,0,0,3,3)==false)
			{
				return(false);
			}

			if (CheckStateMachineState3(StateMachine2,0,0,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState4(StateMachine2,2,2,2,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine3,1,1,11,11,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine3,0,0,1,1,1,1,1,1,0,0,3,3)==false)
			{
				return(false);
			}

			if (CheckStateMachineState3(StateMachine3,0,0,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState4(StateMachine3,1,1,1,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineState1(StateMachine4,1,1,5,5,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState2(StateMachine4,0,0,1,1,1,1,1,1,0,0,3,3)==false)
			{
				return(false);
			}

			if (CheckStateMachineState3(StateMachine4,0,0,0,0,0,0,0,0,0,0)==false)
			{
				return(false);
			}

			if (CheckStateMachineState4(StateMachine4,0,0,0,0,true)==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID2,StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID3,StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachineTree(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachineTree(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine1->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID2}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine2->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID3}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine3->TestGetChildStateMachines(),CStateMachineIDCollection({StateMachineID4}))==false)
			{
				return(false);
			}

			if (CheckStateMachineChildCollection(StateMachine4->TestGetChildStateMachines(),CStateMachineIDCollection())==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=3)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestDuplicateStateMachines(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID1("SM1");
			CStateMachineID										StateMachineIDInvalid("SM INVALID");
			CTimeout											StateMachineTimeout(10*1000*1000);
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(false)));
			CSPTestStateMachineSettingsBasicTests				Settings1(new CTestStateMachineSettingsBasicTests(StateMachineID1,CPriority(100),StateMachineTimeout,CExpirationTime(),true,true,true,true,true,true,true,true));
			CSPTestStateMachineBasicTests						StateMachine1(new CTestStateMachineBasicTests(*this,*this,Settings1,nullptr));

			Processor.AddStateMachine(StateMachine1);

			try
			{
				// ADD STATE MACHINE with SAME STATE MACHINE ID.
				Processor.AddStateMachine(StateMachine1);

				return(false);
			}
			catch(...)
			{
				// IGNORE.
			}

			if (Processor.HasStateMachine(StateMachineID1)==false)
			{
				return(false);
			}

			if (Processor.HasStateMachine(StateMachineIDInvalid)==true)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=0)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestStateMachinesStart(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID("SM");
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",CSPTestStateMachinesProcessorSettings(new CTestStateMachinesProcessorSettings(false)));
			CSPTestStateMachineBasicTests						StateMachine(new CTestStateMachineBasicTests(*this,*this,CSPTestStateMachineSettingsBasicTests(new CTestStateMachineSettingsBasicTests(StateMachineID,CPriority(100),CTimeout(10*1000*1000),CExpirationTime(),true,true,true,true,true,true,true,true)),nullptr));

			Processor.AddStateMachine(StateMachine);

			Processor.ExecuteStateMachines();

			Processor.TestStartStateMachine(StateMachine);

			try
			{
				Processor.TestStartStateMachine(nullptr);

				return(false);
			}
			catch(...)
			{
				// IGNORE.
			}

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID,CTestStateMachineBasicTests::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (CheckStateMachineState(StateMachine,1,2,0,0,1,1,0,2,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=0)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestStateMachinesInputNotProcessedEventException1(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID("SM");
			CSPTestStateMachinesProcessorSettings				ProcessorSettings(new CTestStateMachinesProcessorSettings(true));

			ProcessorSettings->SetThrowExceptionOnStateInputNotProcessed(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_STATE_MACHINE,1,1));

			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",ProcessorSettings);
			CSPTestStateMachineBasicTests						StateMachine(new CTestStateMachineBasicTests(*this,*this,CSPTestStateMachineSettingsBasicTests(new CTestStateMachineSettingsBasicTests(StateMachineID,CPriority(100),CTimeout(10*1000*1000),CExpirationTime(),true,true,true,true,true,true,true,true)),nullptr));

			Processor.AddStateMachine(StateMachine);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID,CTestStateMachineBasicTests::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputUnsupported(StateMachineID,"STATE UNSUPPORTED")));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID,CTestStateMachineBasicTests::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (CheckStateMachineState(StateMachine,1,7,0,0,1,1,0,3,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=2)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestStateMachinesInputNotProcessedEventException2(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID("SM");
			CSPTestStateMachinesProcessorSettings				ProcessorSettings(new CTestStateMachinesProcessorSettings(true));

			ProcessorSettings->SetThrowExceptionOnStateInputNotProcessed(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_CSTRING,1,1));

			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",ProcessorSettings);
			CSPTestStateMachineBasicTests						StateMachine(new CTestStateMachineBasicTests(*this,*this,CSPTestStateMachineSettingsBasicTests(new CTestStateMachineSettingsBasicTests(StateMachineID,CPriority(100),CTimeout(10*1000*1000),CExpirationTime(),true,true,true,true,true,true,true,true)),nullptr));

			Processor.AddStateMachine(StateMachine);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID,CTestStateMachineBasicTests::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputUnsupported(StateMachineID,"STATE UNSUPPORTED")));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID,CTestStateMachineBasicTests::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (CheckStateMachineState(StateMachine,1,7,0,0,1,1,0,3,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=2)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestStateMachinesStateMachineAddedEventException1(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID("SM");
			CSPTestStateMachinesProcessorSettings				ProcessorSettings(new CTestStateMachinesProcessorSettings(true));

			ProcessorSettings->SetThrowExceptionOnStateMachineAdded(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_STATE_MACHINE,1,1));

			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",ProcessorSettings);
			CSPTestStateMachineBasicTests						StateMachine(new CTestStateMachineBasicTests(*this,*this,CSPTestStateMachineSettingsBasicTests(new CTestStateMachineSettingsBasicTests(StateMachineID,CPriority(100),CTimeout(10*1000*1000),CExpirationTime(),true,true,true,true,true,true,true,true)),nullptr));

			Processor.AddStateMachine(StateMachine);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID,CTestStateMachineBasicTests::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID,CTestStateMachineBasicTests::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (CheckStateMachineState(StateMachine,1,5,0,0,1,1,0,3,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=1)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestStateMachinesStateMachineAddedEventException2(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID("SM");
			CSPTestStateMachinesProcessorSettings				ProcessorSettings(new CTestStateMachinesProcessorSettings(true));

			ProcessorSettings->SetThrowExceptionOnStateMachineAdded(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_CSTRING,1,1));

			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",ProcessorSettings);
			CSPTestStateMachineBasicTests						StateMachine(new CTestStateMachineBasicTests(*this,*this,CSPTestStateMachineSettingsBasicTests(new CTestStateMachineSettingsBasicTests(StateMachineID,CPriority(100),CTimeout(10*1000*1000),CExpirationTime(),true,true,true,true,true,true,true,true)),nullptr));

			Processor.AddStateMachine(StateMachine);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID,CTestStateMachineBasicTests::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID,CTestStateMachineBasicTests::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (CheckStateMachineState(StateMachine,1,5,0,0,1,1,0,3,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=1)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestStateMachinesStateMachineFinishedEventException1(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID("SM");
			CSPTestStateMachinesProcessorSettings				ProcessorSettings(new CTestStateMachinesProcessorSettings(true));

			ProcessorSettings->SetThrowExceptionOnStateMachineFinished(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_STATE_MACHINE,1,1));

			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",ProcessorSettings);
			CSPTestStateMachineBasicTests						StateMachine(new CTestStateMachineBasicTests(*this,*this,CSPTestStateMachineSettingsBasicTests(new CTestStateMachineSettingsBasicTests(StateMachineID,CPriority(100),CTimeout(10*1000*1000),CExpirationTime(),true,true,true,true,true,true,true,true)),nullptr));

			Processor.AddStateMachine(StateMachine);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID,CTestStateMachineBasicTests::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID,CTestStateMachineBasicTests::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (CheckStateMachineState(StateMachine,1,5,0,0,1,1,0,3,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=1)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestStateMachinesStateMachineFinishedEventException2(void)
	{
		try
		{
			Reset();

			CStateMachineID										StateMachineID("SM");
			CSPTestStateMachinesProcessorSettings				ProcessorSettings(new CTestStateMachinesProcessorSettings(true));

			ProcessorSettings->SetThrowExceptionOnStateMachineFinished(CTestStateMachineThrowException(ETestStateMachineThrowExceptionType::E_EXCEPTION_CSTRING,1,1));

			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",ProcessorSettings);
			CSPTestStateMachineBasicTests						StateMachine(new CTestStateMachineBasicTests(*this,*this,CSPTestStateMachineSettingsBasicTests(new CTestStateMachineSettingsBasicTests(StateMachineID,CPriority(100),CTimeout(10*1000*1000),CExpirationTime(),true,true,true,true,true,true,true,true)),nullptr));

			Processor.AddStateMachine(StateMachine);

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID,CTestStateMachineBasicTests::MStateRunning,false)));

			Processor.ExecuteStateMachines();

			Processor.AddStateInput(CSPStateInput(new CStateInputChangeState(StateMachineID,CTestStateMachineBasicTests::MStateFinished,false)));

			Processor.ExecuteStateMachines();

			if (CheckStateMachineState(StateMachine,1,5,0,0,1,1,0,3,0,0,0,true)==false)
			{
				return(false);
			}

			if (MNumberOfWarningsAndErrors!=1)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::TestStateMachinesStateMachinesProcessorOperations(void)
	{
		try
		{
			Reset();

			CSPTestStateMachinesProcessorSettings				ProcessorSettings(new CTestStateMachinesProcessorSettings(true));
			CTestStateMachinesProcessor							Processor(*this,"PROCESSOR",ProcessorSettings);

			CStateMachineID										StateMachineID1("SM1");
			CSPTestStateMachineBasicTests						StateMachine1(new CTestStateMachineBasicTests(*this,*this,CSPTestStateMachineSettingsBasicTests(new CTestStateMachineSettingsBasicTests(StateMachineID1,CPriority(100),CTimeout(10*1000*1000),CExpirationTime(),true,true,true,true,true,true,true,true)),nullptr));

			CStateMachineID										StateMachineID2("SM2");
			CSPTestStateMachineBasicTests						StateMachine2(new CTestStateMachineBasicTests(*this,*this,CSPTestStateMachineSettingsBasicTests(new CTestStateMachineSettingsBasicTests(StateMachineID2,CPriority(100),CTimeout(10*1000*1000),CExpirationTime(),true,true,true,true,true,true,true,true)),nullptr));

			Processor.ToString();

			Processor.AddStateMachine(StateMachine1);
			Processor.AddStateMachine(StateMachine2);

			if (Processor.CountStateMachines<CTestStateMachineBasicTests>([](CSPTestStateMachineBasicTests)->bool{return(true);})!=2)
			{
				return(false);
			}

			Size												Counter=0;

			Processor.ExecuteActionOnStateMachines<CTestStateMachineBasicTests>([&Counter](CSPTestStateMachineBasicTests)->void{Counter++;});

			if (Counter!=2)
			{
				return(false);
			}

			return(true);
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",E));

			return(false);
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategoryTest(),ELogRecordLevel::E_WARNING,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord("TEST FAILED !",CUnknownException()));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CStateMachineTest::ExecuteTest(void)
	{
		CVector<CTestMethod<CStateMachineTest>>					Tests;

		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestHelperMethods));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestBasicTestsStateMachine1));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestBasicTestsStateMachine2));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestBasicTestsStateMachine3));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestBasicTestsStateMachineInvalidState));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestBasicTestsStateMachineInvalidChangeState));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestBasicTestsStateMachineStateInput1));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestBasicTestsStateMachineStateInput2));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestBasicTestsStateMachineStateOutput));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestExceptionStateMachineTerminated));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestExceptionStateMachineExceptionStartedEvent1));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestExceptionStateMachineExceptionStartedEvent2));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestExceptionStateMachineExceptionExecuteStateMachine1));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestExceptionStateMachineExceptionExecuteStateMachine2));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestExceptionStateMachineExceptionGetStateMachineTimeout1));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestExceptionStateMachineExceptionGetStateMachineTimeout2));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestExceptionStateMachineExceptionStateOutputFiredEvent1));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestExceptionStateMachineExceptionStateOutputFiredEvent2));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestExceptionStateMachineExceptionExpiredEvent1));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestExceptionStateMachineExceptionExpiredEvent2));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestExceptionStateMachineExceptionInternalTerminate1));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestExceptionStateMachineExceptionInternalTerminate2));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestExceptionStateMachineExceptionInternalTerminateFinished1));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestExceptionStateMachineExceptionInternalTerminateFinished2));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestExceptionStateMachineExceptionExpiredEventInternalTerminate));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestExceptionStateMachineExceptionExpiredEventInternalTerminateFinshed));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestChildStateMachineLevel1));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestChildStateMachineLevel2));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestChildStateMachineLevel3));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestChildStateMachineTimeoutExpiration1));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestChildStateMachineTimeoutExpiration2));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestChildStateMachineReversedFinalStates));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestChildStateMachineMultipleChildStateMachines1));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestChildStateMachineMultipleChildStateMachines2));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestChildStateMachineInput));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestChildStateMachineSendOutput));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestChildStateMachineInvalidChildStateMachine1));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestChildStateMachineInvalidChildStateMachine2));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestChildStateMachineInvalidChildStateMachine3));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestChildStateMachineInvalidChildStateMachine4));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestChildStateMachineTerminate1));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestChildStateMachineTerminate2));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestChildStateMachineTerminate3));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestChildStateMachineTerminate4));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestChildStateMachineTerminate5));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestChildStateMachineExpire1));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestChildStateMachineExpire2));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestChildStateMachineExpire3));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestChildStateMachineExpire4));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestChildStateMachineExpire5));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestExceptionChildStateMachineExceptionExpiredEventInternalTerminateFinshed));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestExceptionChildStateMachineExceptionAddChildStateMachine));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestExceptionChildStateMachineExceptionFinishedChildStateMachine));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestDuplicateStateMachines));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestStateMachinesStart));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestStateMachinesInputNotProcessedEventException1));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestStateMachinesInputNotProcessedEventException2));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestStateMachinesStateMachineAddedEventException1));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestStateMachinesStateMachineAddedEventException2));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestStateMachinesStateMachineFinishedEventException1));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestStateMachinesStateMachineFinishedEventException2));
		Tests.Add(CTestMethod<CStateMachineTest>(this,&CStateMachineTest::TestStateMachinesStateMachinesProcessorOperations));

		bool													AllTestPassed=true;
		Size													TestNumber=0;

		for(CTestMethod<CStateMachineTest>& Method : Tests)
		{
			if (Method()==true)
			{
				CString											Output;

				Output+=GetSeparator(true);
				Output+="\tSUBTEST [";
				Output+=CString(++TestNumber);
				Output+="] PASSED SUCCESSFULLY !\n";
				Output+=GetSeparator(true);

				CConsoleHelper::WriteLine(Output,EConsoleColor::E_LIGHT_GREEN,EConsoleColor::E_DEFAULT,false);
			}
			else
			{
				CString											Output;

				Output+=GetSeparator(true);
				Output+="\tSUBTEST [";
				Output+=CString(++TestNumber);
				Output+="] FAILED !\n";
				Output+=GetSeparator(true);

				AllTestPassed=false;

				CConsoleHelper::WriteLine(Output,EConsoleColor::E_LIGHT_RED,EConsoleColor::E_DEFAULT,false);
			}
		}

		CConsoleHelper::WriteLine(GetSeparator(false));
		CConsoleHelper::WriteLine(GetSeparator(false));
		CConsoleHelper::WriteLine(GetSeparator(false));

		if (AllTestPassed==true)
		{
			CConsoleHelper::WriteLine("ALL TESTS PASSED SUCCESSFULLY !",EConsoleColor::E_LIGHT_GREEN,EConsoleColor::E_DEFAULT,false);
		}
		else
		{
			CConsoleHelper::WriteLine("SOME TESTS FAILED !",EConsoleColor::E_LIGHT_RED,EConsoleColor::E_DEFAULT,false);
		}

		CConsoleHelper::WriteLine(GetSeparator(false));
		CConsoleHelper::WriteLine(GetSeparator(false));
		CConsoleHelper::WriteLine(GetSeparator(false));

		return(AllTestPassed);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------