//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Collections/CMap.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
#include <Framework/Foundation/Types/TypeTraits.h>
#include "CStateMachineID.h"
#include "CStateMachine.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CStateMachineCollection final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			using												CStateMachineMap=CMap<CStateMachineID,CSPStateMachine>;
			using												CStateMachineMapValue=CStateMachineMap::CKeyValuePair;
			using												CStateMachineMapIterator=CStateMachineMap::CMapIterator;
			using												CStateMachineMapIteratorConst=CStateMachineMap::CMapIteratorConst;
			using												CStateMachineMapValueIterator=CStateMachineMap::CMapValueIterator;
			using												CStateMachineMapValueIteratorConst=CStateMachineMap::CMapValueIteratorConst;

		private:
			CStateMachineMap									MCollection;

		public:
			CStateMachineCollection& operator=(const CStateMachineCollection&)=delete;

		public:
			Size GetLength(void) const;
			bool IsEmpty(void) const;
			void AddStateMachine(CSPStateMachine StateMachine);
			bool RemoveStateMachine(const CStateMachineID& StateMachineID);
			bool HasStateMachineByID(const CStateMachineID& StateMachineID) const;
			CSPStateMachine GetStateMachineByID(const CStateMachineID& StateMachineID) const;
			CSPStateMachine GetRootStateMachineForStateMachineID(const CStateMachineID& StateMachineID) const;

		public:
			template<typename TStateMachine, typename TPredicate>
			CVector<CSharedPointer<TStateMachine>> GetStateMachines(TPredicate Predicate) const
			{
				static_assert(STypeTraitIsBaseOf<CStateMachine,TStateMachine>::Value()==true,"TYPE PARAMETER MUST be a CLASS DERIVED from CLASS [CStateMachine] !");

				CVector<CSharedPointer<TStateMachine>>			StateMachines;

				for(CSPStateMachine StateMachine : CreateMapValueIterator(MCollection))
				{
					if (StateMachine->IsTypeOf<TStateMachine>()==true)
					{
						if (Predicate(StateMachine)==true)
						{
							CSharedPointer<TStateMachine>		TypedStateMachine=StateMachine.DynamicCast<TStateMachine>();

							StateMachines.Add(TypedStateMachine);
						}
					}
				}

				return(StateMachines);
			}

			template<typename TStateMachine, typename TPredicate>
			Size CountStateMachines(TPredicate Predicate) const
			{
				static_assert(STypeTraitIsBaseOf<CStateMachine,TStateMachine>::Value()==true,"TYPE PARAMETER MUST be a CLASS DERIVED from CLASS [CStateMachine] !");

				Size											NumberOfStateMachines=0;

				for(CSPStateMachine StateMachine : CreateMapValueIterator(MCollection))
				{
					if (StateMachine->IsTypeOf<TStateMachine>()==true)
					{
						if (Predicate(StateMachine)==true)
						{
							NumberOfStateMachines++;
						}
					}
				}

				return(NumberOfStateMachines);
			}

		public:
			CStateMachineMapIterator Begin(void);
			CStateMachineMapIterator End(void);
			CStateMachineMapIteratorConst Begin(void) const;
			CStateMachineMapIteratorConst End(void) const;
			CStateMachineMapValueIterator BeginValue(void);
			CStateMachineMapValueIterator EndValue(void);
			CStateMachineMapValueIteratorConst BeginValue(void) const;
			CStateMachineMapValueIteratorConst EndValue(void) const;
			CStateMachineMapIterator begin(void);
			CStateMachineMapIterator end(void);
			CStateMachineMapIteratorConst begin(void) const;
			CStateMachineMapIteratorConst end(void) const;

		public:
			CStateMachineCollection(void);
			CStateMachineCollection(const CStateMachineCollection&)=delete;
			virtual ~CStateMachineCollection(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPStateMachineCollection=CSharedPointer<CStateMachineCollection>;
	using														CCSPStateMachineCollection=CSharedPointer<const CStateMachineCollection>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------