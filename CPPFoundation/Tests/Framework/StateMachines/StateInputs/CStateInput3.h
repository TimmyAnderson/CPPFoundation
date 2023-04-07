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
	class CStateInput3 final : public CPPFoundation::Foundation::CStateInput
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CPPFoundation::Foundation::CString						MData;

		public:
			CStateInput3& operator=(const CStateInput3& Other);
			CStateInput3& operator=(CStateInput3&& Other);

		public:
			const CPPFoundation::Foundation::CString& GetData(void) const noexcept;

		public:
			CStateInput3(const CPPFoundation::Foundation::CString& Data);
			CStateInput3(const CPPFoundation::Foundation::CStateMachineID& StateMachineID, const CPPFoundation::Foundation::CString& Data);
			CStateInput3(CPPFoundation::Foundation::CStateMachineID&& StateMachineID, const CPPFoundation::Foundation::CString& Data);
			CStateInput3(const CStateInput3& Other);
			CStateInput3(CStateInput3&& Other);
			virtual ~CStateInput3(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPStateInput3=CPPFoundation::Foundation::CSharedPointer<CStateInput3>;
	using														CCSPStateInput3=CPPFoundation::Foundation::CSharedPointer<const CStateInput3>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------