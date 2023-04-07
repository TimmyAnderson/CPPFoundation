//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Miscellaneous/CPriority.h>
#include <Framework/Foundation/Time/CTimeout.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
#include "CStateMachineID.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CStateMachineSettings : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CStateMachineID									MStateMachineID;
			CPriority										MStateMachinePriority;
			CTimeout										MStateMachineExpirationTimeout;

		public:
			const CStateMachineID& GetStateMachineID(void) const noexcept;
			const CPriority& GetStateMachinePriority(void) const noexcept;
			const CTimeout& GetStateMachineExpirationTimeout(void) const noexcept;

		public:
			CStateMachineSettings(const CStateMachineID& StateMachineID, const CPriority& StateMachinePriority, const CTimeout& StateMachineExpirationTimeout);
			CStateMachineSettings(CStateMachineID&& StateMachineID, const CPriority& StateMachinePriority, const CTimeout& StateMachineExpirationTimeout);
			virtual ~CStateMachineSettings(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPStateMachineSettings=CSharedPointer<CStateMachineSettings>;
	using														CCSPStateMachineSettings=CSharedPointer<const CStateMachineSettings>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------