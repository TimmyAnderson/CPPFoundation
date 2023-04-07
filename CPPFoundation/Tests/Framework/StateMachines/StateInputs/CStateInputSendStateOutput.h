//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/StateMachines/StateInputs/CStateInput.h>
#include <Framework/Foundation/StateMachines/StateOutputs/CStateOutput.h>
#include <Framework/Foundation/Strings/CString.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CStateInputSendStateOutput final : public CPPFoundation::Foundation::CStateInput
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CPPFoundation::Foundation::CStateMachineID				MSendingStateMachineID;
			CPPFoundation::Foundation::CSPStateOutput				MStateOutputToSend;

		public:
			CStateInputSendStateOutput& operator=(const CStateInputSendStateOutput& Other);
			CStateInputSendStateOutput& operator=(CStateInputSendStateOutput&& Other) noexcept;

		public:
			const CPPFoundation::Foundation::CStateMachineID& GetSendingStateMachineID(void) const noexcept;
			CPPFoundation::Foundation::CSPStateOutput GetStateOutputToSend(void) const noexcept;

		public:
			CStateInputSendStateOutput(const CPPFoundation::Foundation::CStateMachineID& StateMachineID, const CPPFoundation::Foundation::CStateMachineID& SendingStateMachineID, CPPFoundation::Foundation::CSPStateOutput StateOutputToSend);
			CStateInputSendStateOutput(CPPFoundation::Foundation::CStateMachineID&& StateMachineID, CPPFoundation::Foundation::CStateMachineID&& SendingStateMachineID, CPPFoundation::Foundation::CSPStateOutput StateOutputToSend);
			CStateInputSendStateOutput(const CStateInputSendStateOutput& Other);
			CStateInputSendStateOutput(CStateInputSendStateOutput&& Other) noexcept;
			virtual ~CStateInputSendStateOutput(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPStateInputSendStateOutput=CPPFoundation::Foundation::CSharedPointer<CStateInputSendStateOutput>;
	using														CCSPStateInputSendStateOutput=CPPFoundation::Foundation::CSharedPointer<const CStateInputSendStateOutput>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------