//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <set>
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Foundation/Exceptions/CValueOutOfRangeException.h>
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Types/TypeTraits.h>
#include "CIterators.h"
#include "IIsBeforeComparator.h"
#include "IEnumerable.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	template<typename TKeyType, typename TComparator=CIsBeforeComparatorLess<TKeyType>>
	class CSet final : public CObject, public IEnumerableConst<TKeyType>
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			class CSetKeyEnumeratorConst : public IEnumeratorConst<TKeyType>
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					using										CSetType=CSet<TKeyType,TComparator>;
					using										CSetTypeIteratorConst=typename std::set<TKeyType,TComparator>::const_iterator;

				private:
					const CSetType&								MSet;
					bool										MIsBeforeFirstItem;
					CSetTypeIteratorConst						MIterator;

				public:
					virtual void Reset(void) override
					{
						MIsBeforeFirstItem=true;
						MIterator=MSet.Begin();
					}

					virtual bool MoveNext(void) override
					{
						if (MIsBeforeFirstItem==true)
						{
							MIsBeforeFirstItem=false;

							if (MIterator!=MSet.End())
							{
								return(true);
							}
							else
							{
								return(false);
							}
						}
						else
						{
							if (MIterator!=MSet.End())
							{
								if (++MIterator!=MSet.End())
								{
									return(true);
								}
								else
								{
									return(false);
								}
							}
							else
							{
								return(false);
							}
						}
					}

					virtual const TKeyType& GetCurrentConst(void) const override
					{
						if (MIsBeforeFirstItem==false && MIterator!=MSet.End())
						{
							return(*MIterator);
						}
						else
						{
							throw(CValueOutOfRangeException("ENUMERATOR is OUT of RANGE !"));
						}
					}

				public:
					CSetKeyEnumeratorConst(const CSetType& Set)
						: MSet(Set), MIsBeforeFirstItem(true), MIterator(Set.Begin())
					{
						Reset();
					}

					virtual ~CSetKeyEnumeratorConst(void) override
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		static_assert(STypeTraitIsBaseOf<IIsBeforeComparator<TKeyType>,TComparator>::Value()==true,"KEY TYPE MUST implement INTERFACE [IIsBeforeComparator<TKeyType>] !");

		private:
			using												CSetType=std::set<TKeyType,TComparator>;
			using												CSetTypeIterator=typename std::set<TKeyType,TComparator>::iterator;
			using												CSetTypeIteratorConst=typename std::set<TKeyType,TComparator>::const_iterator;

		public:
			using												CEnumeratorPointer=CSharedPointer<IEnumerator<TKeyType>>;
			using												CEnumeratorConstPointer=CSharedPointer<IEnumeratorConst<TKeyType>>;
			using												CSetIterator=typename std::set<TKeyType,TComparator>::iterator;
			using												CSetIteratorConst=typename std::set<TKeyType,TComparator>::const_iterator;
			using												CSetReverseIterator=typename std::set<TKeyType,TComparator>::reverse_iterator;
			using												CSetReverseIteratorConst=typename std::set<TKeyType,TComparator>::const_reverse_iterator;

		private:
			CSetType											MSet;

		public:
			CSet<TKeyType>& operator=(const CSet<TKeyType>& Other)
			{
				MSet=Other.MSet;

				return(*this);
			}

			CSet<TKeyType>& operator=(CSet<TKeyType>&& Other) noexcept
			{
				MSet=FUNCTION_MOVE(Other.MSet);
				Other.Clear();

				return(*this);
			}

			CSet<TKeyType>& operator=(IEnumerable<TKeyType>& Other)
			{
				Clear();

				CEnumeratorPointer								Enumerator=Other.GetEnumerator();

				while(Enumerator->MoveNext()==true)
				{
					MSet.insert(Enumerator->GetCurrent());
				}

				return(*this);
			}

			CSet<TKeyType>& operator=(const IEnumerableConst<TKeyType>& Other)
			{
				Clear();

				CEnumeratorConstPointer							Enumerator=Other.GetEnumeratorConst();

				while(Enumerator->MoveNext()==true)
				{
					MSet.insert(Enumerator->GetCurrentConst());
				}

				return(*this);
			}

			CSet<TKeyType>& operator=(std::initializer_list<TKeyType> Other)
			{
				MSet=Other;

				return(*this);
			}

		public:
			void Add(const TKeyType& Key)
			{
				MSet.insert(Key);
			}

			void Add(TKeyType&& Key)
			{
				MSet.insert(FUNCTION_MOVE(Key));
			}

			bool Insert(const TKeyType& Key)
			{
				bool											ContainsValue=Contains(Key);
				
				MSet.insert(Key);

				return(ContainsValue);
			}

			bool Insert(TKeyType&& Key)
			{
				bool											ContainsValue=Contains(Key);
				
				MSet.insert(FUNCTION_MOVE(Key));

				return(ContainsValue);
			}

			bool Erase(const TKeyType& Key)
			{
				Size											NumberOfRemovedItems=MSet.erase(Key);

				if (NumberOfRemovedItems>0)
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}

			void Clear(void) noexcept
			{
				MSet.clear();
			}

		public:
			Size GetLength(void) const noexcept
			{
				Size											Length=static_cast<Size>(MSet.size());
				
				return(Length);
			}

			bool IsEmpty(void) const noexcept
			{
				Size											Length=static_cast<Size>(MSet.size());

				if (Length==0)
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}

			bool Contains(const TKeyType& Key) const
			{
				if (MSet.find(Key)!=MSet.end())
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}

			CSetIterator LowerBound(const TKeyType& Key)
			{
				CSetTypeIterator								Iterator=MSet.lower_bound(Key);

				return(CSetIterator(Iterator));
			}

			CSetIteratorConst LowerBound(const TKeyType& Key) const
			{
				CSetTypeIteratorConst							Iterator=MSet.lower_bound(Key);

				return(CSetIteratorConst(Iterator));
			}

			CSetIterator UpperBound(const TKeyType& Key)
			{
				CSetTypeIterator								Iterator=MSet.upper_bound(Key);

				return(CSetIterator(Iterator));
			}

			CSetIteratorConst UpperBound(const TKeyType& Key) const
			{
				CSetTypeIteratorConst							Iterator=MSet.upper_bound(Key);

				return(CSetIteratorConst(Iterator));
			}

			virtual CEnumeratorConstPointer GetEnumeratorConst(void) const override
			{
				CEnumeratorConstPointer							Enumerator=CEnumeratorConstPointer(new CSetKeyEnumeratorConst(*this));

				return(Enumerator);
			}

			CSetIterator Begin(void)
			{
				return(MSet.begin());
			}

			CSetIterator End(void)
			{
				return(MSet.end());
			}

			CSetIteratorConst ConstBegin(void) const
			{
				return(MSet.cbegin());
			}

			CSetIteratorConst ConstEnd(void) const
			{
				return(MSet.cend());
			}

			CSetIteratorConst Begin(void) const
			{
				return(MSet.cbegin());
			}

			CSetIteratorConst End(void) const
			{
				return(MSet.cend());
			}

			CSetReverseIterator ReverseBegin(void)
			{
				return(MSet.rbegin());
			}

			CSetReverseIterator ReverseEnd(void)
			{
				return(MSet.rend());
			}

			CSetReverseIteratorConst ConstReverseBegin(void) const
			{
				return(MSet.crbegin());
			}

			CSetReverseIteratorConst ConstReverseEnd(void) const
			{
				return(MSet.crend());
			}

			CSetReverseIteratorConst ReverseBegin(void) const
			{
				return(MSet.crbegin());
			}

			CSetReverseIteratorConst ReverseEnd(void) const
			{
				return(MSet.crend());
			}

			CSetIterator begin(void)
			{
				return(MSet.begin());
			}

			CSetIterator end(void)
			{
				return(MSet.end());
			}

			CSetIteratorConst begin(void) const
			{
				return(MSet.cbegin());
			}

			CSetIteratorConst end(void) const
			{
				return(MSet.cend());
			}

			CSetReverseIterator rbegin(void)
			{
				return(MSet.rbegin());
			}

			CSetReverseIterator rend(void)
			{
				return(MSet.rend());
			}

			CSetReverseIteratorConst rbegin(void) const
			{
				return(MSet.crbegin());
			}

			CSetReverseIteratorConst rend(void) const
			{
				return(MSet.crend());
			}

		public:
			CSet(void)
				: MSet()
			{
			}

			CSet(const CSet<TKeyType>& Other)
				: MSet(Other.MSet)
			{
			}

			CSet(CSet<TKeyType>&& Other) noexcept
				: MSet(FUNCTION_MOVE(Other.MSet))
			{
				Other.Clear();
			}

			CSet(const IEnumerableConst<TKeyType>& Other)
				: MSet()
			{
				CEnumeratorConstPointer							Enumerator=Other.GetEnumeratorConst();

				while(Enumerator->MoveNext()==true)
				{
					MSet.insert(Enumerator->GetCurrentConst());
				}
			}

			CSet(std::initializer_list<TKeyType> Other)
				: MSet(Other)
			{
			}

			virtual ~CSet(void) override
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------