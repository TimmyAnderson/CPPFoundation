//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CTestStateMachine.h"
#include "CTestStateMachineThrowException.h"
#include "CTestStateMachineExceptionSettings2.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CStateMachineTest;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	class CTestStateMachineException2 final : public CTestStateMachine
	{
//----------------------------------------------------------------------------------------------------------------------
		friend CStateMachineTest;

		private:
			static const CPPFoundation::Foundation::CState			MStateStarted;
			static const CPPFoundation::Foundation::CState			MStateRunning;
			static const CPPFoundation::Foundation::CState			MStateFinished;

		private:
			CCSPTestStateMachineExceptionSettings2				MSettings;
			CTestStateMachineExceptionSettings					MExceptionSettings;
			CPPFoundation::Foundation::CExpirationTime				MExpirationTime;
			Size												MInternalGetStateMachineStartState1;
			Size												MInternalGetStateMachineStartState2;
			Size												MInternalExecuteStateMachine1;
			Size												MInternalExecuteStateMachine2;
			Size												MStateMachineExecuteStateMachineStateInput1Event1;
			Size												MStateMachineExecuteStateMachineStateInput1Event2;
			Size												MStateMachineExecuteStateMachineStateInput2Event1;
			Size												MStateMachineExecuteStateMachineStateInput2Event2;
			Size												MStateMachineExecuteStateMachineStateInput3Event1;
			Size												MStateMachineExecuteStateMachineStateInput3Event2;
			Size												MStateMachineExecuteStateMachineStateInput4Event1;
			Size												MStateMachineExecuteStateMachineStateInput4Event2;
			Size												MInternalTerminateStateMachine1;
			Size												MInternalTerminateStateMachine2;
			Size												MInternalGetStateMachineTimeout1;
			Size												MInternalGetStateMachineTimeout2;
			Size												MStateMachineStartedEvent1;
			Size												MStateMachineStartedEvent2;
			Size												MStateMachineFinishedEvent1;
			Size												MStateMachineFinishedEvent2;
			Size												MStateMachineExpiredEvent1;
			Size												MStateMachineExpiredEvent2;
			Size												MStateMachineStateChangedEvent1;
			Size												MStateMachineStateChangedEvent2;
			Size												MStateMachineStateOutputFiringEvent1;
			Size												MStateMachineStateOutputFiringEvent2;
			Size												MStateMachineStateOutputFiredStateOutput1Event1;
			Size												MStateMachineStateOutputFiredStateOutput1Event2;
			Size												MStateMachineStateOutputFiredStateOutput2Event1;
			Size												MStateMachineStateOutputFiredStateOutput2Event2;
			Size												MStateMachineStateOutputFiredStateOutput3Event1;
			Size												MStateMachineStateOutputFiredStateOutput3Event2;
			Size												MStateMachineStateOutputFiredStateOutput4Event1;
			Size												MStateMachineStateOutputFiredStateOutput4Event2;
			Size												MChildStateMachineAddedEvent1;
			Size												MChildStateMachineAddedEvent2;
			Size												MChildStateMachineFinishedEvent1;
			Size												MChildStateMachineFinishedEvent2;

		public:
			CTestStateMachineException2& operator=(const CTestStateMachineException2& Other)=delete;

		protected:
			virtual CPPFoundation::Foundation::CState InternalGetStateMachineStartState(void) const override;
			virtual bool InternalExecuteStateMachine(CPPFoundation::Foundation::CCSPStateInput StateInput) override;
			virtual void InternalTerminateStateMachine(void) override;
			virtual CPPFoundation::Foundation::CTimeout InternalGetStateMachineTimeout(CPPFoundation::Foundation::CSteadyClock::Milliseconds TimeInMS) const override;

		protected:
			virtual void StateMachineStartedEvent(void) override;
			virtual void StateMachineFinishedEvent(void) override;
			virtual void StateMachineExpiredEvent(void) override;
			virtual void StateMachineStateChangedEvent(const CPPFoundation::Foundation::CState& NewState, const CPPFoundation::Foundation::CString& Reason) override;
			virtual bool StateMachineStateOutputFiringEvent(CPPFoundation::Foundation::CCSPStateOutput StateOutput) override;
			virtual void ChildStateMachineAddedEvent(void) override;
			virtual void ChildStateMachineFinishedEvent(void) override;

		public:
			Size GetInternalGetStateMachineStartState1(void) const noexcept;
			Size GetInternalGetStateMachineStartState2(void) const noexcept;
			Size GetInternalExecuteStateMachine1(void) const noexcept;
			Size GetInternalExecuteStateMachine2(void) const noexcept;
			Size GetStateMachineExecuteStateMachineStateInput1Event1(void) const noexcept;
			Size GetStateMachineExecuteStateMachineStateInput1Event2(void) const noexcept;
			Size GetStateMachineExecuteStateMachineStateInput2Event1(void) const noexcept;
			Size GetStateMachineExecuteStateMachineStateInput2Event2(void) const noexcept;
			Size GetStateMachineExecuteStateMachineStateInput3Event1(void) const noexcept;
			Size GetStateMachineExecuteStateMachineStateInput3Event2(void) const noexcept;
			Size GetStateMachineExecuteStateMachineStateInput4Event1(void) const noexcept;
			Size GetStateMachineExecuteStateMachineStateInput4Event2(void) const noexcept;
			Size GetInternalTerminateStateMachine1(void) const noexcept;
			Size GetInternalTerminateStateMachine2(void) const noexcept;
			Size GetInternalGetStateMachineTimeout1(void) const noexcept;
			Size GetInternalGetStateMachineTimeout2(void) const noexcept;
			Size GetStateMachineStartedEvent1(void) const noexcept;
			Size GetStateMachineStartedEvent2(void) const noexcept;
			Size GetStateMachineFinishedEvent1(void) const noexcept;
			Size GetStateMachineFinishedEvent2(void) const noexcept;
			Size GetStateMachineExpiredEvent1(void) const noexcept;
			Size GetStateMachineExpiredEvent2(void) const noexcept;
			Size GetStateMachineStateChangedEvent1(void) const noexcept;
			Size GetStateMachineStateChangedEvent2(void) const noexcept;
			Size GetStateMachineStateOutputFiringEvent1(void) const noexcept;
			Size GetStateMachineStateOutputFiringEvent2(void) const noexcept;
			Size GetStateMachineStateOutputFiredStateOutput1Event1(void) const noexcept;
			Size GetStateMachineStateOutputFiredStateOutput1Event2(void) const noexcept;
			Size GetStateMachineStateOutputFiredStateOutput2Event1(void) const noexcept;
			Size GetStateMachineStateOutputFiredStateOutput2Event2(void) const noexcept;
			Size GetStateMachineStateOutputFiredStateOutput3Event1(void) const noexcept;
			Size GetStateMachineStateOutputFiredStateOutput3Event2(void) const noexcept;
			Size GetStateMachineStateOutputFiredStateOutput4Event1(void) const noexcept;
			Size GetStateMachineStateOutputFiredStateOutput4Event2(void) const noexcept;
			Size GetChildStateMachineAddedEvent1(void) const noexcept;
			Size GetChildStateMachineAddedEvent2(void) const noexcept;
			Size GetChildStateMachineFinishedEvent1(void) const noexcept;
			Size GetChildStateMachineFinishedEvent2(void) const noexcept;

		public:
			CTestStateMachineException2(CPPFoundation::Foundation::CLogWriter& LogWriter, CPPFoundation::Foundation::IStateMachineCallback& StateMachineCallback, CCSPTestStateMachineExceptionSettings2 StateMachineSettings, CPPFoundation::Foundation::CStateMachine* StateMachineParent);
			CTestStateMachineException2(const CTestStateMachineException2& Other)=delete;
			virtual ~CTestStateMachineException2(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPTestStateMachineException2=CPPFoundation::Foundation::CSharedPointer<CTestStateMachineException2>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------