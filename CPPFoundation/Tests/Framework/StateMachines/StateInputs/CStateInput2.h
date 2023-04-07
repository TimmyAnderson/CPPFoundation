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
	class CStateInput2 final : public CPPFoundation::Foundation::CStateInput
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CPPFoundation::Foundation::CString						MData;

		public:
			CStateInput2& operator=(const CStateInput2& Other);
			CStateInput2& operator=(CStateInput2&& Other) noexcept;

		public:
			const CPPFoundation::Foundation::CString& GetData(void) const noexcept;

		public:
			CStateInput2(const CPPFoundation::Foundation::CString& Data);
			CStateInput2(const CPPFoundation::Foundation::CStateMachineID& StateMachineID, const CPPFoundation::Foundation::CString& Data);
			CStateInput2(CPPFoundation::Foundation::CStateMachineID&& StateMachineID, const CPPFoundation::Foundation::CString& Data);
			CStateInput2(const CStateInput2& Other);
			CStateInput2(CStateInput2&& Other) noexcept;
			virtual ~CStateInput2(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPStateInput2=CPPFoundation::Foundation::CSharedPointer<CStateInput2>;
	using														CCSPStateInput2=CPPFoundation::Foundation::CSharedPointer<const CStateInput2>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------