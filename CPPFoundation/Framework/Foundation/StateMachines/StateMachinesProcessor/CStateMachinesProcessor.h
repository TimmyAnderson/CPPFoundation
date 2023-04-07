//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/StateMachines/StateMachines/CStateMachine.h>
#include <Framework/Foundation/StateMachines/StateMachines/CStateMachineCollection.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
#include <Framework/Foundation/Types/ICallableObject.h>
#include "CStateMachinesProcessorSettings.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CStateMachinesProcessor : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CLogWriter&											MLogWriter;
			const CLogCategory									MLogCategoryStateMachinesProcessor;
			const CString										MStateMachinesProcessorName;
			CCSPStateMachinesProcessorSettings					MStateMachinesProcessorSettings;
			CStateMachineCollection								MStateMachines;
			CStateInputCollection								MStateInputs;
			bool												MExecuteImmediately;

		public:
			CStateMachinesProcessor& operator=(const CStateMachinesProcessor&)=delete;

		private:
			void RemoveFinishedStateMachines(void);
			void ProcessAllInputs(void);
			void ProcessTimeout(void);

		protected:
			virtual void StateMachineAdded(CSPStateMachine StateMachine);
			virtual void StateMachineFinished(CSPStateMachine StateMachine);
			virtual void StateInputNotProcessed(CCSPStateInput StateInput);

		protected:
			CLogWriter& GetLogWriter(void) const noexcept;
			const CLogCategory& GetLogCategoryStateMachinesProcessor(void) const noexcept;
			const CString& GetStateMachinesProcessorName(void) const noexcept;
			CCSPStateMachinesProcessorSettings GetStateMachinesProcessorSettings(void) const noexcept;
			[[noreturn]] void ThrowStateMachineException(const CString& Message);

		protected:
			void StartStateMachine(CSPStateMachine StateMachine);

		public:
			virtual CString ToString(void) const override;
			void AddStateMachine(CSPStateMachine StateMachine);
			void AddStateInput(CCSPStateInput Input);
			bool HasStateMachine(const CStateMachineID& StateMachineID) const;
			void ExecuteStateMachines(void);
			void TerminateStateMachines(void);
			CTimeout GetStateMachinesTimeout(CSteadyClock::Milliseconds TimeInMS);
			const CStateMachineCollection& GetStateMachines(void) const noexcept;

		public:
			template<typename TStateMachine, typename TAction>
			void ExecuteActionOnStateMachines(TAction Action)
			{
				static_assert(STypeTraitIsBaseOf<CStateMachine,TStateMachine>::Value()==true,"TYPE PARAMETER MUST be a CLASS DERIVED from CLASS [CStateMachine] !");

				for(CSPStateMachine StateMachine : CreateMapValueIterator(MStateMachines))
				{
					if (StateMachine.IsTypeOf<TStateMachine>()==true)
					{
						CSharedPointer<TStateMachine>			TypedStateMachine=StateMachine.DynamicCast<TStateMachine>();

						Action(TypedStateMachine);
					}
				}
			}

			template<typename TStateMachine, typename TPredicate>
			Size CountStateMachines(TPredicate Predicate)
			{
				static_assert(STypeTraitIsBaseOf<CStateMachine,TStateMachine>::Value()==true,"TYPE PARAMETER MUST be a CLASS DERIVED from CLASS [CStateMachine] !");

				Size											Count=0;

				for(CSPStateMachine StateMachine : CreateMapValueIterator(MStateMachines))
				{
					if (StateMachine.IsTypeOf<TStateMachine>()==true)
					{
						CSharedPointer<TStateMachine>			TypedStateMachine=StateMachine.DynamicCast<TStateMachine>();

						if (Predicate(TypedStateMachine)==true)
						{
							Count++;
						}
					}
				}

				return(Count);
			}

			template<typename TPredicate>
			void TerminateStateMachines(TPredicate Predicate)
			{
				for(CSPStateMachine StateMachine : CreateMapValueIterator(MStateMachines))
				{
					if (Predicate(StateMachine)==true)
					{
						StateMachine->TerminateStateMachine();
					}
				}

				RemoveFinishedStateMachines();
			}

		public:
			CStateMachinesProcessor(CLogWriter& LogWriter, const CString& StateMachinesProcessorName, CCSPStateMachinesProcessorSettings StateMachinesProcessorSettings);
			CStateMachinesProcessor(const CStateMachinesProcessor&)=delete;
			virtual ~CStateMachinesProcessor(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPStateMachinesProcessor=CSharedPointer<CStateMachinesProcessor>;
	using														CCSPStateMachinesProcessor=CSharedPointer<const CStateMachinesProcessor>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------