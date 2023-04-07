//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CVector.h>
#include <Framework/Foundation/StateMachines/StateMachines/IStateMachineCallback.h>
#include <Framework/Testing/CTest.h>
#include <Tests/Framework/StateMachines/StateMachines/CTestStateMachine1.h>
#include <Tests/Framework/StateMachines/StateMachines/CTestStateMachine2.h>
#include <Tests/Framework/StateMachines/StateMachines/CTestStateMachine3.h>
#include <Tests/Framework/StateMachines/StateMachines/CTestStateMachine4.h>
#include <Tests/Framework/StateMachines/StateMachines/CTestStateMachineException1.h>
#include <Tests/Framework/StateMachines/StateMachines/CTestStateMachineException2.h>
#include <Tests/Framework/StateMachines/StateMachines/CTestStateMachineException3.h>
#include <Tests/Framework/StateMachines/StateMachines/CTestStateMachineException4.h>
#include <Tests/Framework/StateMachines/StateMachines/CTestStateMachineBasicTests.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CStateMachineTest final : public CTest, private CPPFoundation::Foundation::CLogWriter, private CPPFoundation::Foundation::IStateMachineCallback
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			using												CStateOutputCollection=CPPFoundation::Foundation::CVector<CPPFoundation::Foundation::CCSPStateOutput>;
			using												CStateMachineIDCollection=CPPFoundation::Foundation::CVector<CPPFoundation::Foundation::CStateMachineID>;

		private:
			bool												MWriteStateMachineLogs;
			CStateOutputCollection								MOutputCollection;
			Size												MNumberOfWarningsAndErrors;

		private:
			virtual void ProcessStateOutput(CPPFoundation::Foundation::CCSPStateOutput StateOutput) override;

		private:
			void Reset(void);
			bool CheckStateMachineTimeout(const CPPFoundation::Foundation::CTimeout& Timeout, bool IsZero, bool IsInfinite);
			bool CheckStateMachineChildCollection(const CTestStateMachine::CTestStateMachineChildCollection& ChildCollection, const CStateMachineIDCollection& StateMachineIDCollection);

		private:
			bool CheckStateMachineState(CSPTestStateMachineBasicTests StateMachine, Size InternalGetStateMachineStartState, Size InternalExecuteStateMachine, Size InternalTerminateStateMachine, Size InternalGetStateMachineTimeout, Size StateMachineStartedEvent, Size StateMachineFinishedEvent, Size StateMachineExpiredEvent, Size StateMachineStateChangedEvent, Size StateMachineStateOutputFiringEvent, Size ChildStateMachineAddedEvent, Size ChildStateMachineFinishedEvent, bool HasFinished);
			bool CheckStateMachineState1(CSPTestStateMachine1 StateMachine, Size InternalGetStateMachineStartState, Size InternalExecuteStateMachine, Size StateMachineExecuteStateMachineStateInput1Event, Size StateMachineExecuteStateMachineStateInput2Event, Size StateMachineExecuteStateMachineStateInput3Event, Size StateMachineExecuteStateMachineStateInput4Event, Size InternalTerminateStateMachine, Size InternalGetStateMachineTimeout, Size StateMachineStartedEvent, Size StateMachineFinishedEvent);
			bool CheckStateMachineState2(CSPTestStateMachine1 StateMachine, Size StateMachineExpiredEvent, Size StateMachineStateChangedEvent, Size StateMachineStateOutputFiringEvent, Size StateMachineStateOutputFiredStateOutput1Event, Size StateMachineStateOutputFiredStateOutput2Event, Size StateMachineStateOutputFiredStateOutput3Event, Size StateMachineStateOutputFiredStateOutput4Event, Size ChildStateMachineAddedEvent, Size ChildStateMachineFinishedEvent, bool HasFinished);
			bool CheckStateMachineState1(CSPTestStateMachine2 StateMachine, Size InternalGetStateMachineStartState, Size InternalExecuteStateMachine, Size StateMachineExecuteStateMachineStateInput1Event, Size StateMachineExecuteStateMachineStateInput2Event, Size StateMachineExecuteStateMachineStateInput3Event, Size StateMachineExecuteStateMachineStateInput4Event, Size InternalTerminateStateMachine, Size InternalGetStateMachineTimeout, Size StateMachineStartedEvent, Size StateMachineFinishedEvent);
			bool CheckStateMachineState2(CSPTestStateMachine2 StateMachine, Size StateMachineExpiredEvent, Size StateMachineStateChangedEvent, Size StateMachineStateOutputFiringEvent, Size StateMachineStateOutputFiredStateOutput1Event, Size StateMachineStateOutputFiredStateOutput2Event, Size StateMachineStateOutputFiredStateOutput3Event, Size StateMachineStateOutputFiredStateOutput4Event, Size ChildStateMachineAddedEvent, Size ChildStateMachineFinishedEvent, bool HasFinished);
			bool CheckStateMachineState1(CSPTestStateMachine3 StateMachine, Size InternalGetStateMachineStartState, Size InternalExecuteStateMachine, Size StateMachineExecuteStateMachineStateInput1Event, Size StateMachineExecuteStateMachineStateInput2Event, Size StateMachineExecuteStateMachineStateInput3Event, Size StateMachineExecuteStateMachineStateInput4Event, Size InternalTerminateStateMachine, Size InternalGetStateMachineTimeout, Size StateMachineStartedEvent, Size StateMachineFinishedEvent);
			bool CheckStateMachineState2(CSPTestStateMachine3 StateMachine, Size StateMachineExpiredEvent, Size StateMachineStateChangedEvent, Size StateMachineStateOutputFiringEvent, Size StateMachineStateOutputFiredStateOutput1Event, Size StateMachineStateOutputFiredStateOutput2Event, Size StateMachineStateOutputFiredStateOutput3Event, Size StateMachineStateOutputFiredStateOutput4Event, Size ChildStateMachineAddedEvent, Size ChildStateMachineFinishedEvent, bool HasFinished);
			bool CheckStateMachineState1(CSPTestStateMachine4 StateMachine, Size InternalGetStateMachineStartState, Size InternalExecuteStateMachine, Size StateMachineExecuteStateMachineStateInput1Event, Size StateMachineExecuteStateMachineStateInput2Event, Size StateMachineExecuteStateMachineStateInput3Event, Size StateMachineExecuteStateMachineStateInput4Event, Size InternalTerminateStateMachine, Size InternalGetStateMachineTimeout, Size StateMachineStartedEvent, Size StateMachineFinishedEvent);
			bool CheckStateMachineState2(CSPTestStateMachine4 StateMachine, Size StateMachineExpiredEvent, Size StateMachineStateChangedEvent, Size StateMachineStateOutputFiringEvent, Size StateMachineStateOutputFiredStateOutput1Event, Size StateMachineStateOutputFiredStateOutput2Event, Size StateMachineStateOutputFiredStateOutput3Event, Size StateMachineStateOutputFiredStateOutput4Event, Size ChildStateMachineAddedEvent, Size ChildStateMachineFinishedEvent, bool HasFinished);
			bool CheckStateMachineState1(CSPTestStateMachineException1 StateMachine, Size InternalGetStateMachineStartState1, Size InternalGetStateMachineStartState2, Size InternalExecuteStateMachine1, Size InternalExecuteStateMachine2, Size StateMachineExecuteStateMachineStateInput1Event1, Size StateMachineExecuteStateMachineStateInput1Event2, Size StateMachineExecuteStateMachineStateInput2Event1, Size StateMachineExecuteStateMachineStateInput2Event2, Size StateMachineExecuteStateMachineStateInput3Event1, Size StateMachineExecuteStateMachineStateInput3Event2, Size StateMachineExecuteStateMachineStateInput4Event1, Size StateMachineExecuteStateMachineStateInput4Event2);
			bool CheckStateMachineState2(CSPTestStateMachineException1 StateMachine, Size InternalTerminateStateMachine1, Size InternalTerminateStateMachine2, Size InternalGetStateMachineTimeout1, Size InternalGetStateMachineTimeout2, Size StateMachineStartedEvent1, Size StateMachineStartedEvent2, Size StateMachineFinishedEvent1, Size StateMachineFinishedEvent2, Size StateMachineExpiredEvent1, Size StateMachineExpiredEvent2, Size StateMachineStateChangedEvent1, Size StateMachineStateChangedEvent2);
			bool CheckStateMachineState3(CSPTestStateMachineException1 StateMachine, Size StateMachineStateOutputFiringEvent1, Size StateMachineStateOutputFiringEvent2, Size StateMachineStateOutputFiredStateOutput1Event1, Size StateMachineStateOutputFiredStateOutput1Event2, Size StateMachineStateOutputFiredStateOutput2Event1, Size StateMachineStateOutputFiredStateOutput2Event2, Size StateMachineStateOutputFiredStateOutput3Event1, Size StateMachineStateOutputFiredStateOutput3Event2, Size StateMachineStateOutputFiredStateOutput4Event1, Size StateMachineStateOutputFiredStateOutput4Event2);
			bool CheckStateMachineState4(CSPTestStateMachineException1 StateMachine, Size ChildStateMachineAddedEvent1, Size ChildStateMachineAddedEvent2, Size ChildStateMachineFinishedEvent1, Size ChildStateMachineFinishedEvent2, bool HasFinished);
			bool CheckStateMachineState1(CSPTestStateMachineException2 StateMachine, Size InternalGetStateMachineStartState1, Size InternalGetStateMachineStartState2, Size InternalExecuteStateMachine1, Size InternalExecuteStateMachine2, Size StateMachineExecuteStateMachineStateInput1Event1, Size StateMachineExecuteStateMachineStateInput1Event2, Size StateMachineExecuteStateMachineStateInput2Event1, Size StateMachineExecuteStateMachineStateInput2Event2, Size StateMachineExecuteStateMachineStateInput3Event1, Size StateMachineExecuteStateMachineStateInput3Event2, Size StateMachineExecuteStateMachineStateInput4Event1, Size StateMachineExecuteStateMachineStateInput4Event2);
			bool CheckStateMachineState2(CSPTestStateMachineException2 StateMachine, Size InternalTerminateStateMachine1, Size InternalTerminateStateMachine2, Size InternalGetStateMachineTimeout1, Size InternalGetStateMachineTimeout2, Size StateMachineStartedEvent1, Size StateMachineStartedEvent2, Size StateMachineFinishedEvent1, Size StateMachineFinishedEvent2, Size StateMachineExpiredEvent1, Size StateMachineExpiredEvent2, Size StateMachineStateChangedEvent1, Size StateMachineStateChangedEvent2);
			bool CheckStateMachineState3(CSPTestStateMachineException2 StateMachine, Size StateMachineStateOutputFiringEvent1, Size StateMachineStateOutputFiringEvent2, Size StateMachineStateOutputFiredStateOutput1Event1, Size StateMachineStateOutputFiredStateOutput1Event2, Size StateMachineStateOutputFiredStateOutput2Event1, Size StateMachineStateOutputFiredStateOutput2Event2, Size StateMachineStateOutputFiredStateOutput3Event1, Size StateMachineStateOutputFiredStateOutput3Event2, Size StateMachineStateOutputFiredStateOutput4Event1, Size StateMachineStateOutputFiredStateOutput4Event2);
			bool CheckStateMachineState4(CSPTestStateMachineException2 StateMachine, Size ChildStateMachineAddedEvent1, Size ChildStateMachineAddedEvent2, Size ChildStateMachineFinishedEvent1, Size ChildStateMachineFinishedEvent2, bool HasFinished);
			bool CheckStateMachineState1(CSPTestStateMachineException3 StateMachine, Size InternalGetStateMachineStartState1, Size InternalGetStateMachineStartState2, Size InternalExecuteStateMachine1, Size InternalExecuteStateMachine2, Size StateMachineExecuteStateMachineStateInput1Event1, Size StateMachineExecuteStateMachineStateInput1Event2, Size StateMachineExecuteStateMachineStateInput2Event1, Size StateMachineExecuteStateMachineStateInput2Event2, Size StateMachineExecuteStateMachineStateInput3Event1, Size StateMachineExecuteStateMachineStateInput3Event2, Size StateMachineExecuteStateMachineStateInput4Event1, Size StateMachineExecuteStateMachineStateInput4Event2);
			bool CheckStateMachineState2(CSPTestStateMachineException3 StateMachine, Size InternalTerminateStateMachine1, Size InternalTerminateStateMachine2, Size InternalGetStateMachineTimeout1, Size InternalGetStateMachineTimeout2, Size StateMachineStartedEvent1, Size StateMachineStartedEvent2, Size StateMachineFinishedEvent1, Size StateMachineFinishedEvent2, Size StateMachineExpiredEvent1, Size StateMachineExpiredEvent2, Size StateMachineStateChangedEvent1, Size StateMachineStateChangedEvent2);
			bool CheckStateMachineState3(CSPTestStateMachineException3 StateMachine, Size StateMachineStateOutputFiringEvent1, Size StateMachineStateOutputFiringEvent2, Size StateMachineStateOutputFiredStateOutput1Event1, Size StateMachineStateOutputFiredStateOutput1Event2, Size StateMachineStateOutputFiredStateOutput2Event1, Size StateMachineStateOutputFiredStateOutput2Event2, Size StateMachineStateOutputFiredStateOutput3Event1, Size StateMachineStateOutputFiredStateOutput3Event2, Size StateMachineStateOutputFiredStateOutput4Event1, Size StateMachineStateOutputFiredStateOutput4Event2);
			bool CheckStateMachineState4(CSPTestStateMachineException3 StateMachine, Size ChildStateMachineAddedEvent1, Size ChildStateMachineAddedEvent2, Size ChildStateMachineFinishedEvent1, Size ChildStateMachineFinishedEvent2, bool HasFinished);
			bool CheckStateMachineState1(CSPTestStateMachineException4 StateMachine, Size InternalGetStateMachineStartState1, Size InternalGetStateMachineStartState2, Size InternalExecuteStateMachine1, Size InternalExecuteStateMachine2, Size StateMachineExecuteStateMachineStateInput1Event1, Size StateMachineExecuteStateMachineStateInput1Event2, Size StateMachineExecuteStateMachineStateInput2Event1, Size StateMachineExecuteStateMachineStateInput2Event2, Size StateMachineExecuteStateMachineStateInput3Event1, Size StateMachineExecuteStateMachineStateInput3Event2, Size StateMachineExecuteStateMachineStateInput4Event1, Size StateMachineExecuteStateMachineStateInput4Event2);
			bool CheckStateMachineState2(CSPTestStateMachineException4 StateMachine, Size InternalTerminateStateMachine1, Size InternalTerminateStateMachine2, Size InternalGetStateMachineTimeout1, Size InternalGetStateMachineTimeout2, Size StateMachineStartedEvent1, Size StateMachineStartedEvent2, Size StateMachineFinishedEvent1, Size StateMachineFinishedEvent2, Size StateMachineExpiredEvent1, Size StateMachineExpiredEvent2, Size StateMachineStateChangedEvent1, Size StateMachineStateChangedEvent2);
			bool CheckStateMachineState3(CSPTestStateMachineException4 StateMachine, Size StateMachineStateOutputFiringEvent1, Size StateMachineStateOutputFiringEvent2, Size StateMachineStateOutputFiredStateOutput1Event1, Size StateMachineStateOutputFiredStateOutput1Event2, Size StateMachineStateOutputFiredStateOutput2Event1, Size StateMachineStateOutputFiredStateOutput2Event2, Size StateMachineStateOutputFiredStateOutput3Event1, Size StateMachineStateOutputFiredStateOutput3Event2, Size StateMachineStateOutputFiredStateOutput4Event1, Size StateMachineStateOutputFiredStateOutput4Event2);
			bool CheckStateMachineState4(CSPTestStateMachineException4 StateMachine, Size ChildStateMachineAddedEvent1, Size ChildStateMachineAddedEvent2, Size ChildStateMachineFinishedEvent1, Size ChildStateMachineFinishedEvent2, bool HasFinished);

		private:
			bool TestHelperMethods(void);
			bool TestBasicTestsStateMachine1(void);
			bool TestBasicTestsStateMachine2(void);
			bool TestBasicTestsStateMachine3(void);
			bool TestBasicTestsStateMachineInvalidState(void);
			bool TestBasicTestsStateMachineInvalidChangeState(void);
			bool TestBasicTestsStateMachineStateInput1(void);
			bool TestBasicTestsStateMachineStateInput2(void);
			bool TestBasicTestsStateMachineStateOutput(void);
			bool TestExceptionStateMachineTerminated(void);
			bool TestExceptionStateMachineExceptionStartedEvent1(void);
			bool TestExceptionStateMachineExceptionStartedEvent2(void);
			bool TestExceptionStateMachineExceptionExecuteStateMachine1(void);
			bool TestExceptionStateMachineExceptionExecuteStateMachine2(void);
			bool TestExceptionStateMachineExceptionGetStateMachineTimeout1(void);
			bool TestExceptionStateMachineExceptionGetStateMachineTimeout2(void);
			bool TestExceptionStateMachineExceptionStateOutputFiredEvent1(void);
			bool TestExceptionStateMachineExceptionStateOutputFiredEvent2(void);
			bool TestExceptionStateMachineExceptionExpiredEvent1(void);
			bool TestExceptionStateMachineExceptionExpiredEvent2(void);
			bool TestExceptionStateMachineExceptionInternalTerminate1(void);
			bool TestExceptionStateMachineExceptionInternalTerminate2(void);
			bool TestExceptionStateMachineExceptionInternalTerminateFinished1(void);
			bool TestExceptionStateMachineExceptionInternalTerminateFinished2(void);
			bool TestExceptionStateMachineExceptionExpiredEventInternalTerminate(void);
			bool TestExceptionStateMachineExceptionExpiredEventInternalTerminateFinshed(void);
			bool TestChildStateMachineLevel1(void);
			bool TestChildStateMachineLevel2(void);
			bool TestChildStateMachineLevel3(void);
			bool TestChildStateMachineTimeoutExpiration1(void);
			bool TestChildStateMachineTimeoutExpiration2(void);
			bool TestChildStateMachineReversedFinalStates(void);
			bool TestChildStateMachineMultipleChildStateMachines1(void);
			bool TestChildStateMachineMultipleChildStateMachines2(void);
			bool TestChildStateMachineInput(void);
			bool TestChildStateMachineSendOutput(void);
			bool TestChildStateMachineInvalidChildStateMachine1(void);
			bool TestChildStateMachineInvalidChildStateMachine2(void);
			bool TestChildStateMachineInvalidChildStateMachine3(void);
			bool TestChildStateMachineInvalidChildStateMachine4(void);
			bool TestChildStateMachineTerminate1(void);
			bool TestChildStateMachineTerminate2(void);
			bool TestChildStateMachineTerminate3(void);
			bool TestChildStateMachineTerminate4(void);
			bool TestChildStateMachineTerminate5(void);
			bool TestChildStateMachineExpire1(void);
			bool TestChildStateMachineExpire2(void);
			bool TestChildStateMachineExpire3(void);
			bool TestChildStateMachineExpire4(void);
			bool TestChildStateMachineExpire5(void);
			bool TestExceptionChildStateMachineExceptionExpiredEventInternalTerminateFinshed(void);
			bool TestExceptionChildStateMachineExceptionAddChildStateMachine(void);
			bool TestExceptionChildStateMachineExceptionFinishedChildStateMachine(void);
			bool TestDuplicateStateMachines(void);
			bool TestStateMachinesStart(void);
			bool TestStateMachinesInputNotProcessedEventException1(void);
			bool TestStateMachinesInputNotProcessedEventException2(void);
			bool TestStateMachinesStateMachineAddedEventException1(void);
			bool TestStateMachinesStateMachineAddedEventException2(void);
			bool TestStateMachinesStateMachineFinishedEventException1(void);
			bool TestStateMachinesStateMachineFinishedEventException2(void);
			bool TestStateMachinesStateMachinesProcessorOperations(void);

		protected:
			virtual void InternalWriteToLog(const CPPFoundation::Foundation::CLogCategory& LogCategory, CPPFoundation::Foundation::ELogRecordLevel LogLevel, const Char* FunctionName, Size LineNumber, const CPPFoundation::Foundation::CLogRecord& LogRecord) override;

		public:
			virtual bool ExecuteTest(void) override;

		public:
			CStateMachineTest(CPPFoundation::Foundation::CLogWriter& LogWriter, const CPPFoundation::Foundation::CLogCategory& LogCategoryTest, bool WriteStateMachineLogs);
			virtual ~CStateMachineTest(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------