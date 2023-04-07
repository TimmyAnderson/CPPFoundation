//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/StateMachines/StateMachines/CStateMachineSettings.h>
#include <Framework/Foundation/Time/CExpirationTime.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CTestStateMachineSettingsBasicTests final : public CPPFoundation::Foundation::CStateMachineSettings
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CPPFoundation::Foundation::CExpirationTime				MStateExpirationTime;
			bool												MProcessStateInput1;
			bool												MProcessStateInput2;
			bool												MProcessStateInput3;
			bool												MProcessStateInput4;
			bool												MProcessStateOutput1;
			bool												MProcessStateOutput2;
			bool												MProcessStateOutput3;
			bool												MProcessStateOutput4;

		public:
			const CPPFoundation::Foundation::CExpirationTime& GetStateExpirationTime(void) const noexcept;
			bool GetProcessStateInput1(void) const noexcept;
			bool GetProcessStateInput2(void) const noexcept;
			bool GetProcessStateInput3(void) const noexcept;
			bool GetProcessStateInput4(void) const noexcept;
			bool GetProcessStateOutput1(void) const noexcept;
			bool GetProcessStateOutput2(void) const noexcept;
			bool GetProcessStateOutput3(void) const noexcept;
			bool GetProcessStateOutput4(void) const noexcept;

		public:
			CTestStateMachineSettingsBasicTests(const CPPFoundation::Foundation::CStateMachineID& StateMachineID, const CPPFoundation::Foundation::CPriority& StateMachinePriority, const CPPFoundation::Foundation::CTimeout& StateMachineExpirationTimeout, const CPPFoundation::Foundation::CExpirationTime& StateExpirationTime, bool ProcessStateInput1, bool ProcessStateInput2, bool ProcessStateInput3, bool ProcessStateInput4, bool ProcessStateOutput1, bool ProcessStateOutput2, bool ProcessStateOutput3, bool ProcessStateOutput4);
			virtual ~CTestStateMachineSettingsBasicTests(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPTestStateMachineSettingsBasicTests=CPPFoundation::Foundation::CSharedPointer<CTestStateMachineSettingsBasicTests>;
	using														CCSPTestStateMachineSettingsBasicTests=CPPFoundation::Foundation::CSharedPointer<const CTestStateMachineSettingsBasicTests>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------