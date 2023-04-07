//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CTestStateMachine.h"
#include "CTestStateMachineSettings4.h"
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
	class CTestStateMachine4 final : public CTestStateMachine
	{
//----------------------------------------------------------------------------------------------------------------------
		friend CStateMachineTest;

		private:
			static const CPPFoundation::Foundation::CState			MStateStarted;
			static const CPPFoundation::Foundation::CState			MStateRunning;
			static const CPPFoundation::Foundation::CState			MStateFinished;

		private:
			CCSPTestStateMachineSettings4						MSettings;
			CPPFoundation::Foundation::CExpirationTime				MExpirationTime;
			Size												MInternalGetStateMachineStartState;
			Size												MInternalExecuteStateMachine;
			Size												MStateMachineExecuteStateMachineStateInput1Event;
			Size												MStateMachineExecuteStateMachineStateInput2Event;
			Size												MStateMachineExecuteStateMachineStateInput3Event;
			Size												MStateMachineExecuteStateMachineStateInput4Event;
			Size												MInternalTerminateStateMachine;
			Size												MInternalGetStateMachineTimeout;
			Size												MStateMachineStartedEvent;
			Size												MStateMachineFinishedEvent;
			Size												MStateMachineExpiredEvent;
			Size												MStateMachineStateChangedEvent;
			Size												MStateMachineStateOutputFiringEvent;
			Size												MStateMachineStateOutputFiredStateOutput1Event;
			Size												MStateMachineStateOutputFiredStateOutput2Event;
			Size												MStateMachineStateOutputFiredStateOutput3Event;
			Size												MStateMachineStateOutputFiredStateOutput4Event;
			Size												MChildStateMachineAddedEvent;
			Size												MChildStateMachineFinishedEvent;

		public:
			CTestStateMachine4& operator=(const CTestStateMachine4& Other)=delete;

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
			Size GetInternalGetStateMachineStartState(void) const noexcept;
			Size GetInternalExecuteStateMachine(void) const noexcept;
			Size GetStateMachineExecuteStateMachineStateInput1Event(void) const noexcept;
			Size GetStateMachineExecuteStateMachineStateInput2Event(void) const noexcept;
			Size GetStateMachineExecuteStateMachineStateInput3Event(void) const noexcept;
			Size GetStateMachineExecuteStateMachineStateInput4Event(void) const noexcept;
			Size GetInternalTerminateStateMachine(void) const noexcept;
			Size GetInternalGetStateMachineTimeout(void) const noexcept;
			Size GetStateMachineStartedEvent(void) const noexcept;
			Size GetStateMachineFinishedEvent(void) const noexcept;
			Size GetStateMachineExpiredEvent(void) const noexcept;
			Size GetStateMachineStateChangedEvent(void) const noexcept;
			Size GetStateMachineStateOutputFiringEvent(void) const noexcept;
			Size GetStateMachineStateOutputFiredStateOutput1Event(void) const noexcept;
			Size GetStateMachineStateOutputFiredStateOutput2Event(void) const noexcept;
			Size GetStateMachineStateOutputFiredStateOutput3Event(void) const noexcept;
			Size GetStateMachineStateOutputFiredStateOutput4Event(void) const noexcept;
			Size GetChildStateMachineAddedEvent(void) const noexcept;
			Size GetChildStateMachineFinishedEvent(void) const noexcept;

		public:
			CTestStateMachine4(CPPFoundation::Foundation::CLogWriter& LogWriter, CPPFoundation::Foundation::IStateMachineCallback& StateMachineCallback, CCSPTestStateMachineSettings4 StateMachineSettings, CPPFoundation::Foundation::CStateMachine* StateMachineParent);
			CTestStateMachine4(const CTestStateMachine4& Other)=delete;
			virtual ~CTestStateMachine4(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPTestStateMachine4=CPPFoundation::Foundation::CSharedPointer<CTestStateMachine4>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------