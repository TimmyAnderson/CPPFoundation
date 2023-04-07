//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/StateMachines/StateInputs/CStateInput.h>
#include <Framework/Foundation/StateMachines/StateMachines/CStateMachine.h>
#include <Framework/Foundation/Strings/CString.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CStateInputAddChildStateMachine final : public CPPFoundation::Foundation::CStateInput
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CPPFoundation::Foundation::CStateMachineID				MParentStateMachineID;
			CPPFoundation::Foundation::CSPStateMachine				MStateMachineToAdd;

		public:
			CStateInputAddChildStateMachine& operator=(const CStateInputAddChildStateMachine& Other);
			CStateInputAddChildStateMachine& operator=(CStateInputAddChildStateMachine&& Other) noexcept;

		public:
			const CPPFoundation::Foundation::CStateMachineID& GetParentStateMachineID(void) const noexcept;
			CPPFoundation::Foundation::CSPStateMachine GetStateMachineToAdd(void) const noexcept;

		public:
			CStateInputAddChildStateMachine(const CPPFoundation::Foundation::CStateMachineID& ParentStateMachineID, CPPFoundation::Foundation::CSPStateMachine StateMachineToAdd);
			CStateInputAddChildStateMachine(const CPPFoundation::Foundation::CStateMachineID& StateMachineID, const CPPFoundation::Foundation::CStateMachineID& ParentStateMachineID, CPPFoundation::Foundation::CSPStateMachine StateMachineToAdd);
			CStateInputAddChildStateMachine(CPPFoundation::Foundation::CStateMachineID&& StateMachineID, CPPFoundation::Foundation::CStateMachineID&& ParentStateMachineID, CPPFoundation::Foundation::CSPStateMachine StateMachineToAdd);
			CStateInputAddChildStateMachine(const CStateInputAddChildStateMachine& Other);
			CStateInputAddChildStateMachine(CStateInputAddChildStateMachine&& Other) noexcept;
			virtual ~CStateInputAddChildStateMachine(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPStateInputAddChildStateMachine=CPPFoundation::Foundation::CSharedPointer<CStateInputAddChildStateMachine>;
	using														CCSPStateInputAddChildStateMachine=CPPFoundation::Foundation::CSharedPointer<const CStateInputAddChildStateMachine>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------