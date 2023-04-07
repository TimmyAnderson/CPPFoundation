//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/StateMachines/StateMachines/CStateMachine.h>
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
	class CTestStateMachine : public CPPFoundation::Foundation::CStateMachine
	{
//----------------------------------------------------------------------------------------------------------------------
		friend CStateMachineTest;

		public:
			using												CTestStateMachineChildCollection=CPPFoundation::Foundation::CMap<CPPFoundation::Foundation::CStateMachineID,CPPFoundation::Foundation::CSPStateMachine>;

		public:
			CTestStateMachine& operator=(const CTestStateMachine& Other)=delete;

		protected:
			virtual void ChildStateMachineAddedEvent(void) override;
			virtual void ChildStateMachineFinishedEvent(void) override;

		public:
			bool TestHasChildStateMachineByID(const CPPFoundation::Foundation::CStateMachineID& StateMachineID) const;
			const CTestStateMachineChildCollection& TestGetChildStateMachines(void) const noexcept;
			const CTestStateMachineChildCollection& TestGetChildStateMachineTree(void) const;
			CPPFoundation::Foundation::CSPStateMachine TestGetChildStateMachineByID(const CPPFoundation::Foundation::CStateMachineID& StateMachineID) const;
			const CStateMachine* TestGetStateMachineRoot(void) const;

		public:
			CTestStateMachine(CPPFoundation::Foundation::CLogWriter& LogWriter, const CPPFoundation::Foundation::CString& StateMachineName, CPPFoundation::Foundation::IStateMachineCallback& StateMachineCallback, CPPFoundation::Foundation::CCSPStateMachineSettings StateMachineSettings, CPPFoundation::Foundation::CStateMachine* StateMachineParent);
			CTestStateMachine(const CTestStateMachine& Other)=delete;
			virtual ~CTestStateMachine(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPTestStateMachine=CPPFoundation::Foundation::CSharedPointer<CTestStateMachine>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------