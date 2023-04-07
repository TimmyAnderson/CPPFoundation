//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CMap.h>
#include <Framework/Foundation/Collections/CSet.h>
#include <Framework/Foundation/Collections/CVector.h>
#include <Framework/Foundation/Exceptions/CStateMachineException.h>
#include <Framework/Foundation/Logger/CLogWriter.h>
#include <Framework/Foundation/Miscellaneous/CPriority.h>
#include <Framework/Foundation/StateMachines/States/CState.h>
#include <Framework/Foundation/StateMachines/StateInputs/CStateInput.h>
#include <Framework/Foundation/Time/CTimeout.h>
#include <Framework/Foundation/Time/CExpirationTime.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
#include <Framework/Foundation/Types/TypeTraits.h>
#include "CStateMachineID.h"
#include "IStateMachineCallback.h"
#include "CStateMachineSettings.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CStateMachine;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPStateMachine=CSharedPointer<CStateMachine>;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	class CStateMachine : virtual public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			enum class EStateMachineInternalState
			{
//----------------------------------------------------------------------------------------------------------------------
				E_CREATED=1,
				E_RUNNING=2,
				E_FINISHED=3,
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		protected:
			using												CStateMachineChildCollection=CMap<CStateMachineID,CSPStateMachine>;
			using												CStateMachineChildCollectionIterator=CStateMachineChildCollection::CMapIterator;
			using												CStateMachineChildCollectionIteratorConst=CStateMachineChildCollection::CMapIteratorConst;

		private:
			CLogWriter&											MLogWriter;
			const CLogCategory									MLogCategoryStateMachine;
			const CString										MStateMachineName;
			IStateMachineCallback&								MStateMachineCallback;
			CCSPStateMachineSettings							MStateMachineSettings;
			EStateMachineInternalState							MStateMachineInternalCurrentState;
			CState												MStateMachineCurrentState;
			CExpirationTime										MStateMachineExpirationTime;
			bool												MStateMachineExecuteImmediately;
			CStateMachine*										MStateMachineParent;
			CStateMachineChildCollection						MStateMachineChildCollection;
			CStateMachineChildCollection						MStateMachineChildCollectionTree;

		public:
			CStateMachine& operator=(const CStateMachine& Other)=delete;

		private:
			bool CallInternalExecuteStateMachine(CCSPStateInput StateInput);
			void ChildStateMachineAdded(CSPStateMachine StateMachine);
			void ChildStateMachineFinished(void) noexcept;
			void StateMachineFinished(void) noexcept;
			void StateMachineExpired(void) noexcept;
			bool CheckStateMachineFinished(void) noexcept;
			bool ExecuteChildStateMachine(CStateMachine* StateMachine, CCSPStateInput StateInput) noexcept;
			bool ExecuteChildStateMachine(CSPStateMachine StateMachine, CCSPStateInput StateInput) noexcept;
			bool ExecuteChildStateMachines(CCSPStateInput StateInput);
			void TerminateChildStateMachines(void) noexcept;
			CTimeout GetChildStateMachinesTimeout(CSteadyClock::Milliseconds TimeInMS) const;
			bool IsStateMachineIDUnique(const CStateMachineID& StateMachineID) const;
			void InitializeState(const CState& NewState);

		protected:
			virtual CState InternalGetStateMachineStartState(void) const=0;
			virtual bool InternalExecuteStateMachine(CCSPStateInput StateInput)=0;
			virtual void InternalTerminateStateMachine(void)=0;
			virtual CTimeout InternalGetStateMachineTimeout(CSteadyClock::Milliseconds TimeInMS) const=0;

		protected:
			virtual void StateMachineStartedEvent(void);
			virtual void StateMachineFinishedEvent(void);
			virtual void StateMachineExpiredEvent(void);
			virtual void StateMachineStateChangedEvent(const CState& NewState, const CString& Reason);
			virtual bool StateMachineStateOutputFiringEvent(CCSPStateOutput StateOutput);
			virtual void ChildStateMachineAddedEvent(void);
			virtual void ChildStateMachineFinishedEvent(void);

		protected:
			CLogWriter& GetLogWriter(void) const noexcept;
			const CLogCategory& GetLogCategoryStateMachine(void) const noexcept;
			const CString& GetStateMachineName(void) const noexcept;
			IStateMachineCallback& GetStateMachineCallback(void) const noexcept;
			const CState& GetState(void) const noexcept;
			const CStateMachine* GetStateMachineRoot(void) const;
			CStateMachine* GetStateMachineParent(void) const noexcept;
			void AddChildStateMachine(CSPStateMachine StateMachine);
			bool HasChildStateMachineByID(const CStateMachineID& StateMachineID) const;
			const CStateMachineChildCollection& GetChildStateMachines(void) const noexcept;
			const CStateMachineChildCollection& GetChildStateMachineTree(void) const noexcept;
			CSPStateMachine GetChildStateMachineByID(const CStateMachineID& StateMachineID) const;
			bool HaveAllChildStateMachinesFinished(void) const noexcept;
			bool ExecuteStateMachine(CCSPStateInput StateInput, bool ExecuteInternalExecuteStateMachine) noexcept;

		protected:
			template<typename TStateMachine>
			CSharedPointer<TStateMachine> GetChildStateMachineByID(const CStateMachineID& StateMachineID) const
			{
				static_assert(STypeTraitIsBaseOf<CStateMachine,TStateMachine>::Value()==true,"TYPE PARAMETER MUST be a CLASS DERIVED from CLASS [CStateMachine] !");

				if (MStateMachineChildCollection.Contains(StateMachineID)==true)
				{
					CSPStateMachine								StateMachine=MStateMachineChildCollection[StateMachineID];

					if (StateMachine->IsTypeOf<TStateMachine>()==true)
					{
						CSharedPointer<TStateMachine>			TypedStateMachine=StateMachine.DynamicCast<TStateMachine>();

						return(TypedStateMachine);
					}
				}

				return(nullptr);
			}

		protected:
			void ChangeState(const CState& NewState, bool ExecuteImmediately=false);
			void ChangeState(const CState& NewState, const CString& Reason, bool ExecuteImmediately=false);
			bool StateMachineTimeoutHasExpired(void) const;
			bool StateMachineTimeoutHasExpired(CSteadyClock::Milliseconds TimeInMS) const;
			[[noreturn]] void ThrowStateMachineException(const CString& Message);
			void FireStateOutput(CCSPStateOutput StateOutput);

		public:
			virtual CString ToString(void) const override;
			const CStateMachineID& GetStateMachineID(void) const noexcept;
			const CPriority& GetStateMachinePriority(void) const noexcept;
			const CTimeout& GetStateMachineExpirationTimeout(void) const noexcept;
			CCSPStateMachineSettings GetStateMachineSettings(void) const noexcept;
			bool HasStarted(void) const noexcept;
			bool HasFinished(void) const noexcept;
			bool HasChildStateMachineInChildMachineTree(const CStateMachineID& StateMachineID) const;

		public:
			void StartStateMachine(void) noexcept;
			bool ExecuteStateMachine(CCSPStateInput StateInput) noexcept;
			void TerminateStateMachine(void) noexcept;
			CTimeout GetStateMachineTimeout(CSteadyClock::Milliseconds TimeInMS) noexcept;

		public:
			CStateMachine(CLogWriter& LogWriter, const CString& StateMachineName, IStateMachineCallback& StateMachineCallback, CCSPStateMachineSettings StateMachineSettings, CStateMachine* StateMachineParent);
			CStateMachine(const CStateMachine& Other)=delete;
			virtual ~CStateMachine(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------