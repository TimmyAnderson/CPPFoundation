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
	class CTestStateMachineExceptionSettings3 final : public CPPFoundation::Foundation::CStateMachineSettings
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
			CTestStateMachineExceptionSettings3(const CPPFoundation::Foundation::CStateMachineID& StateMachineID, const CPPFoundation::Foundation::CPriority& StateMachinePriority, const CPPFoundation::Foundation::CTimeout& StateMachineExpirationTimeout, const CTestStateMachineExceptionSettings& StateMachineExceptionSettings, const CPPFoundation::Foundation::CExpirationTime& StateExpirationTime);
			virtual ~CTestStateMachineExceptionSettings3(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPTestStateMachineExceptionSettings3=CPPFoundation::Foundation::CSharedPointer<CTestStateMachineExceptionSettings3>;
	using														CCSPTestStateMachineExceptionSettings3=CPPFoundation::Foundation::CSharedPointer<const CTestStateMachineExceptionSettings3>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------