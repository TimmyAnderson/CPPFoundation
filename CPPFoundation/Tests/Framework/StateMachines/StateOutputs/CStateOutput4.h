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
	class CStateOutput4 final : public CPPFoundation::Foundation::CStateOutput
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CPPFoundation::Foundation::CString						MData;

		public:
			CStateOutput4& operator=(const CStateOutput4& Other);
			CStateOutput4& operator=(CStateOutput4&& Other) noexcept;

		public:
			const CPPFoundation::Foundation::CString& GetData(void) const noexcept;

		public:
			CStateOutput4(const CPPFoundation::Foundation::CStateMachineID& StateMachineID, const CPPFoundation::Foundation::CString& Data);
			CStateOutput4(const CStateOutput4& Other);
			CStateOutput4(CStateOutput4&& Other) noexcept;
			virtual ~CStateOutput4(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPStateOutput4=CPPFoundation::Foundation::CSharedPointer<CStateOutput4>;
	using														CCSPStateOutput4=CPPFoundation::Foundation::CSharedPointer<const CStateOutput4>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------