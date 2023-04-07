//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/StateMachines/StateMachines/CStateMachineSettings.h>
#include <Framework/Foundation/Time/CExpirationTime.h>
#include "CTestStateMachineExceptionSettings.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CTestStateMachineExceptionSettings2 final : public CPPFoundation::Foundation::CStateMachineSettings
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CTestStateMachineExceptionSettings					MStateMachineExceptionSettings;
			CPPFoundation::Foundation::CExpirationTime				MStateExpirationTime;

		public:
			const CTestStateMachineExceptionSettings& GetStateMachineExceptionSettings(void) const noexcept;
			CTestStateMachineExceptionSettings& GetStateMachineExceptionSettings(void) noexcept;
			const CPPFoundation::Foundation::CExpirationTime& GetStateExpirationTime(void) const noexcept;

		public:
			CTestStateMachineExceptionSettings2(const CPPFoundation::Foundation::CStateMachineID& StateMachineID, const CPPFoundation::Foundation::CPriority& StateMachinePriority, const CPPFoundation::Foundation::CTimeout& StateMachineExpirationTimeout, const CTestStateMachineExceptionSettings& StateMachineExceptionSettings, const CPPFoundation::Foundation::CExpirationTime& StateExpirationTime);
			virtual ~CTestStateMachineExceptionSettings2(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPTestStateMachineExceptionSettings2=CPPFoundation::Foundation::CSharedPointer<CTestStateMachineExceptionSettings2>;
	using														CCSPTestStateMachineExceptionSettings2=CPPFoundation::Foundation::CSharedPointer<const CTestStateMachineExceptionSettings2>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------