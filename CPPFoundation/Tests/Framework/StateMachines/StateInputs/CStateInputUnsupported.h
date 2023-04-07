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
	class CStateInputUnsupported final : public CPPFoundation::Foundation::CStateInput
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CPPFoundation::Foundation::CString						MData;

		public:
			CStateInputUnsupported& operator=(const CStateInputUnsupported& Other);
			CStateInputUnsupported& operator=(CStateInputUnsupported&& Other);

		public:
			const CPPFoundation::Foundation::CString& GetData(void) const noexcept;

		public:
			CStateInputUnsupported(const CPPFoundation::Foundation::CString& Data);
			CStateInputUnsupported(const CPPFoundation::Foundation::CStateMachineID& StateMachineID, const CPPFoundation::Foundation::CString& Data);
			CStateInputUnsupported(CPPFoundation::Foundation::CStateMachineID&& StateMachineID, const CPPFoundation::Foundation::CString& Data);
			CStateInputUnsupported(const CStateInputUnsupported& Other);
			CStateInputUnsupported(CStateInputUnsupported&& Other);
			virtual ~CStateInputUnsupported(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPStateInputUnsupported=CPPFoundation::Foundation::CSharedPointer<CStateInputUnsupported>;
	using														CCSPStateInputUnsupported=CPPFoundation::Foundation::CSharedPointer<const CStateInputUnsupported>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------