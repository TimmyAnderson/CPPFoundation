//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Objects/CObject.h>
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
	class CStateInput : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CStateMachineID										MStateMachineID;

		public:
			CStateInput& operator=(const CStateInput& Other);
			CStateInput& operator=(CStateInput&& Other) noexcept;

		public:
			bool HasStateMachineID(void) const;
			const CStateMachineID& GetStateMachineID(void) const;

		public:
			CStateInput(void);
			CStateInput(const CStateMachineID& StateMachineID);
			CStateInput(CStateMachineID&& StateMachineID);
			CStateInput(const CStateInput& Other);
			CStateInput(CStateInput&& Other) noexcept;
			virtual ~CStateInput(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPStateInput=CSharedPointer<CStateInput>;
	using														CCSPStateInput=CSharedPointer<const CStateInput>;
	using														CStateInputCollection=CDequeue<CCSPStateInput>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------