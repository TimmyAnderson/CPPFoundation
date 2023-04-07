//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CTestStateMachine.h"
#include "CTestStateMachineSettingsBasicTests.h"
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
	class CTestStateMachineBasicTests final : public CTestStateMachine
	{
//----------------------------------------------------------------------------------------------------------------------
		friend CStateMachineTest;

		private:
			static const CPPFoundation::Foundation::CState			MStateStarted;
			static const CPPFoundation::Foundation::CState			MStateRunning;
			static const CPPFoundation::Foundation::CState			MStateFinished;

		private:
			CCSPTestStateMachineSettingsBasicTests				MSettings;
			CPPFoundation::Foundation::CExpirationTime				MExpirationTime;
			Size												MInternalGetStateMachineStartState;
			Size												MInternalExecuteStateMachine;
			Size												MInternalTerminateStateMachine;
			Size												MInternalGetStateMachineTimeout;
			Size												MStateMachineStartedEvent;
			Size												MStateMachineFinishedEvent;
			Size												MStateMachineExpiredEvent;
			Size												MStateMachineStateChangedEvent;
			Size												MStateMachineStateOutputFiringEvent;
			Size												MChildStateMachineAddedEvent;
			Size												MChildStateMachineFinishedEvent;
			Size												MStateInputProcessedStateInput1;
			Size												MStateInputProcessedStateInput2;
			Size												MStateInputProcessedStateInput3;
			Size												MStateInputProcessedStateInput4;

		public:
			CTestStateMachineBasicTests& operator=(const CTestStateMachineBasicTests& Other)=delete;

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
			Size GetInternalTerminateStateMachine(void) const noexcept;
			Size GetInternalGetStateMachineTimeout(void) const noexcept;
			Size GetStateMachineStartedEvent(void) const noexcept;
			Size GetStateMachineFinishedEvent(void) const noexcept;
			Size GetStateMachineExpiredEvent(void) const noexcept;
			Size GetStateMachineStateChangedEvent(void) const noexcept;
			Size GetStateMachineStateOutputFiringEvent(void) const noexcept;
			Size GetChildStateMachineAddedEvent(void) const noexcept;
			Size GetChildStateMachineFinishedEvent(void) const noexcept;
			Size GetStateInputProcessedStateInput1(void) const noexcept;
			Size GetStateInputProcessedStateInput2(void) const noexcept;
			Size GetStateInputProcessedStateInput3(void) const noexcept;
			Size GetStateInputProcessedStateInput4(void) const noexcept;

		public:
			void TestHelperMethods(void) const;

		public:
			CTestStateMachineBasicTests(CPPFoundation::Foundation::CLogWriter& LogWriter, CPPFoundation::Foundation::IStateMachineCallback& StateMachineCallback, CCSPTestStateMachineSettingsBasicTests StateMachineSettings, CPPFoundation::Foundation::CStateMachine* StateMachineParent);
			CTestStateMachineBasicTests(const CTestStateMachineBasicTests& Other)=delete;
			virtual ~CTestStateMachineBasicTests(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPTestStateMachineBasicTests=CPPFoundation::Foundation::CSharedPointer<CTestStateMachineBasicTests>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------