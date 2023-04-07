//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/StateMachines/StateInputs/CStateInput.h>
#include <Framework/Foundation/StateMachines/States/CState.h>
#include <Framework/Foundation/Strings/CString.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CStateInputChangeState final : public CPPFoundation::Foundation::CStateInput
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CPPFoundation::Foundation::CState						MStateToChange;
			bool												MExecuteImmediately;
			CPPFoundation::Foundation::CString						MReason;

		public:
			CStateInputChangeState& operator=(const CStateInputChangeState& Other);
			CStateInputChangeState& operator=(CStateInputChangeState&& Other) noexcept;

		public:
			const CPPFoundation::Foundation::CState& GetStateToChange(void) const noexcept;
			bool GetExecuteImmediately(void) const noexcept;
			const CPPFoundation::Foundation::CString& GetReason(void) const noexcept;

		public:
			CStateInputChangeState(const CPPFoundation::Foundation::CStateMachineID& StateMachineID, const CPPFoundation::Foundation::CState& StateToChange, bool ExecuteImmediately, const CPPFoundation::Foundation::CString& Reason="STATE CHANGED STATE INPUT ARRIVED !");
			CStateInputChangeState(CPPFoundation::Foundation::CStateMachineID&& StateMachineID, CPPFoundation::Foundation::CState&& StateToChange, bool ExecuteImmediately, CPPFoundation::Foundation::CString&& Reason="STATE CHANGED STATE INPUT ARRIVED !");
			CStateInputChangeState(const CStateInputChangeState& Other);
			CStateInputChangeState(CStateInputChangeState&& Other) noexcept;
			virtual ~CStateInputChangeState(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPStateInputChangeState=CPPFoundation::Foundation::CSharedPointer<CStateInputChangeState>;
	using														CCSPStateInputChangeState=CPPFoundation::Foundation::CSharedPointer<const CStateInputChangeState>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------