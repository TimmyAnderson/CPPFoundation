//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/StateMachines/StateMachinesProcessor/CStateMachinesProcessor.h>
#include "CTestStateMachinesProcessorSettings.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CTestStateMachinesProcessor final : public CPPFoundation::Foundation::CStateMachinesProcessor
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CTestStateMachinesProcessorSettings					MStateMachinesProcessorSettings;

		protected:
			virtual void StateMachineAdded(CPPFoundation::Foundation::CSPStateMachine StateMachine) override;
			virtual void StateMachineFinished(CPPFoundation::Foundation::CSPStateMachine StateMachine) override;
			virtual void StateInputNotProcessed(CPPFoundation::Foundation::CCSPStateInput StateInput) override;

		public:
			const CPPFoundation::Foundation::CString& TestGetStateMachinesProcessorName(void) const noexcept;
			CPPFoundation::Foundation::CCSPStateMachinesProcessorSettings TestGetStateMachinesProcessorSettings(void) const noexcept;
			void TestStartStateMachine(CPPFoundation::Foundation::CSPStateMachine StateMachine);

		public:
			CTestStateMachinesProcessor(CPPFoundation::Foundation::CLogWriter& LogWriter, const CPPFoundation::Foundation::CString& StateMachinesProcessorName, CCSPTestStateMachinesProcessorSettings StateMachinesProcessorSettings);
			virtual ~CTestStateMachinesProcessor(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPTestStateMachinesProcessor=CPPFoundation::Foundation::CSharedPointer<CTestStateMachinesProcessor>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------