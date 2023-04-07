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
	class CStateInput4 final : public CPPFoundation::Foundation::CStateInput
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CPPFoundation::Foundation::CString						MData;

		public:
			CStateInput4& operator=(const CStateInput4& Other);
			CStateInput4& operator=(CStateInput4&& Other) noexcept;

		public:
			const CPPFoundation::Foundation::CString& GetData(void) const noexcept;

		public:
			CStateInput4(const CPPFoundation::Foundation::CString& Data);
			CStateInput4(const CPPFoundation::Foundation::CStateMachineID& StateMachineID, const CPPFoundation::Foundation::CString& Data);
			CStateInput4(CPPFoundation::Foundation::CStateMachineID&& StateMachineID, const CPPFoundation::Foundation::CString& Data);
			CStateInput4(const CStateInput4& Other);
			CStateInput4(CStateInput4&& Other) noexcept;
			virtual ~CStateInput4(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPStateInput4=CPPFoundation::Foundation::CSharedPointer<CStateInput4>;
	using														CCSPStateInput4=CPPFoundation::Foundation::CSharedPointer<const CStateInput4>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------