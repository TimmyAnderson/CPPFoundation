//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/StateMachines/StateOutputs/CStateOutput.h>
#include <Framework/Foundation/Strings/CString.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CStateOutput2 final : public CPPFoundation::Foundation::CStateOutput
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CPPFoundation::Foundation::CString						MData;

		public:
			CStateOutput2& operator=(const CStateOutput2& Other);
			CStateOutput2& operator=(CStateOutput2&& Other) noexcept;

		public:
			const CPPFoundation::Foundation::CString& GetData(void) const noexcept;

		public:
			CStateOutput2(const CPPFoundation::Foundation::CStateMachineID& StateMachineID, const CPPFoundation::Foundation::CString& Data);
			CStateOutput2(const CStateOutput2& Other);
			CStateOutput2(CStateOutput2&& Other) noexcept;
			virtual ~CStateOutput2(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPStateOutput2=CPPFoundation::Foundation::CSharedPointer<CStateOutput2>;
	using														CCSPStateOutput2=CPPFoundation::Foundation::CSharedPointer<const CStateOutput2>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------