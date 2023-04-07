//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CDequeue.h>
#include <Framework/Foundation/StateMachines/StateMachines/CStateMachineID.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CStateOutput : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CStateMachineID										MStateMachineID;

		public:
			CStateOutput& operator=(const CStateOutput& Other);
			CStateOutput& operator=(CStateOutput&& Other) noexcept;

		public:
			const CStateMachineID& GetStateMachineID(void) const noexcept;

		public:
			CStateOutput(void);
			CStateOutput(const CStateMachineID& StateMachineID);
			CStateOutput(CStateMachineID&& StateMachineID) noexcept;
			CStateOutput(const CStateOutput& Other);
			CStateOutput(CStateOutput&& Other) noexcept;
			virtual ~CStateOutput(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPStateOutput=CSharedPointer<CStateOutput>;
	using														CCSPStateOutput=CSharedPointer<const CStateOutput>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------