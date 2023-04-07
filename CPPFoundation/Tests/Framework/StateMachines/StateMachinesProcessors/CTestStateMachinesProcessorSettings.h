//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/StateMachines/StateMachinesProcessor/CStateMachinesProcessorSettings.h>
#include <Tests/Framework/StateMachines/StateMachines/CTestStateMachineThrowException.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CTestStateMachinesProcessorSettings final : public CPPFoundation::Foundation::CStateMachinesProcessorSettings
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			bool												MAutoStartStateMachine;
			CTestStateMachineThrowException						MThrowExceptionOnStateInputNotProcessed;
			CTestStateMachineThrowException						MThrowExceptionOnStateMachineAdded;
			CTestStateMachineThrowException						MThrowExceptionOnStateMachineFinished;

		public:
			bool GetAutoStartStateMachine(void) const noexcept;
			CTestStateMachineThrowException& GetThrowExceptionOnStateInputNotProcessed(void) noexcept;
			void SetThrowExceptionOnStateInputNotProcessed(const CTestStateMachineThrowException& Value) noexcept;
			CTestStateMachineThrowException& GetThrowExceptionOnStateMachineAdded(void) noexcept;
			void SetThrowExceptionOnStateMachineAdded(const CTestStateMachineThrowException& Value) noexcept;
			CTestStateMachineThrowException& GetThrowExceptionOnStateMachineFinished(void) noexcept;
			void SetThrowExceptionOnStateMachineFinished(const CTestStateMachineThrowException& Value) noexcept;

		public:
			CTestStateMachinesProcessorSettings(bool AutoStartStateMachine);
			virtual ~CTestStateMachinesProcessorSettings(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPTestStateMachinesProcessorSettings=CPPFoundation::Foundation::CSharedPointer<CTestStateMachinesProcessorSettings>;
	using														CCSPTestStateMachinesProcessorSettings=CPPFoundation::Foundation::CSharedPointer<const CTestStateMachinesProcessorSettings>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------