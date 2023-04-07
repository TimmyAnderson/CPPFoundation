//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/StateMachines/StateInputs/CStateInput.h>
#include <Framework/Foundation/Strings/CString.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CStateInput1 final : public CPPFoundation::Foundation::CStateInput
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CPPFoundation::Foundation::CString						MData;

		public:
			CStateInput1& operator=(const CStateInput1& Other);
			CStateInput1& operator=(CStateInput1&& Other) noexcept;

		public:
			const CPPFoundation::Foundation::CString& GetData(void) const noexcept;

		public:
			CStateInput1(const CPPFoundation::Foundation::CString& Data);
			CStateInput1(const CPPFoundation::Foundation::CStateMachineID& StateMachineID, const CPPFoundation::Foundation::CString& Data);
			CStateInput1(CPPFoundation::Foundation::CStateMachineID&& StateMachineID, const CPPFoundation::Foundation::CString& Data);
			CStateInput1(const CStateInput1& Other);
			CStateInput1(CStateInput1&& Other) noexcept;
			virtual ~CStateInput1(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPStateInput1=CPPFoundation::Foundation::CSharedPointer<CStateInput1>;
	using														CCSPStateInput1=CPPFoundation::Foundation::CSharedPointer<const CStateInput1>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------