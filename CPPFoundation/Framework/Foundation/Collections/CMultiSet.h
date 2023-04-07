//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <set>
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Foundation/Exceptions/CValueOutOfRangeException.h>
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Types/TypeTraits.h>
#include "CIterators.h"
#include "CPair.h"
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
	class CMultiSet final : public CObject, public IEnumerableConst<TKeyType>
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			class CMultiSetKeyEnumeratorConst : public IEnumeratorConst<TKeyType>
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					using										CMultiSetType=CMultiSet<TKeyType,TComparator>;
					using										CMultiSetTypeIteratorConst=typename std::multiset<TKeyType,TComparator>::const_iterator;

				private:
					const CMultiSetType&						MMultiSet;
					bool										MIsBeforeFirstItem;
					CMultiSetTypeIteratorConst					MIterator;

				public:
					virtual void Reset(void) override
					{
						MIsBeforeFirstItem=true;
						MIterator=MMultiSet.Begin();
					}

					virtual bool MoveNext(void) override
					{
						if (MIsBeforeFirstItem==true)
						{
							MIsBeforeFirstItem=false;

							if (MIterator!=MMultiSet.End())
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
							if (MIterator!=MMultiSet.End())
							{
								if (++MIterator!=MMultiSet.End())
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
						if (MIsBeforeFirstItem==false && MIterator!=MMultiSet.End())
						{
							return(*MIterator);
						}
						else
						{
							throw(CValueOutOfRangeException("ENUMERATOR is OUT of RANGE !"));
						}
					}

				public:
					CMultiSetKeyEnumeratorConst(const CMultiSetType& Set)
						: MMultiSet(Set), MIsBeforeFirstItem(true), MIterator(Set.Begin())
					{
						Reset();
					}

					virtual ~CMultiSetKeyEnumeratorConst(void) override
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		static_assert(STypeTraitIsBaseOf<IIsBeforeComparator<TKeyType>,TComparator>::Value()==true,"KEY TYPE MUST implement INTERFACE [IIsBeforeComparator<TKeyType>] !");

		private:
			using												CMultiSetType=std::multiset<TKeyType,TComparator>;
			using												CMultiSetTypeIterator=typename std::multiset<TKeyType,TComparator>::iterator;
			using												CMultiSetTypeIteratorConst=typename std::multiset<TKeyType,TComparator>::const_iterator;

		public:
			using												CEnumeratorPointer=CSharedPointer<IEnumerator<TKeyType>>;
			using												CEnumeratorConstPointer=CSharedPointer<IEnumeratorConst<TKeyType>>;
			using												CMultiSetIterator=typename std::multiset<TKeyType,TComparator>::iterator;
			using												CMultiSetIteratorConst=typename std::multiset<TKeyType,TComparator>::const_iterator;
			using												CMultiSetReverseIterator=typename std::multiset<TKeyType,TComparator>::reverse_iterator;
			using												CMultiSetReverseIteratorConst=typename std::multiset<TKeyType,TComparator>::const_reverse_iterator;

		private:
			CMultiSetType										MMultiSet;

		public:
			CMultiSet<TKeyType>& operator=(const CMultiSet<TKeyType>& Other)
			{
				MMultiSet=Other.MMultiSet;

				return(*this);
			}

			CMultiSet<TKeyType>& operator=(CMultiSet<TKeyType>&& Other) noexcept
			{
				MMultiSet=FUNCTION_MOVE(Other.MMultiSet);
				Other.Clear();

				return(*this);
			}

			CMultiSet<TKeyType>& operator=(IEnumerable<TKeyType>& Other)
			{
				Clear();

				CEnumeratorPointer								Enumerator=Other.GetEnumerator();

				while(Enumerator->MoveNext()==true)
				{
					MMultiSet.insert(Enumerator->GetCurrent());
				}

				return(*this);
			}

			CMultiSet<TKeyType>& operator=(const IEnumerableConst<TKeyType>& Other)
			{
				Clear();

				CEnumeratorConstPointer							Enumerator=Other.GetEnumeratorConst();

				while(Enumerator->MoveNext()==true)
				{
					MMultiSet.insert(Enumerator->GetCurrentConst());
				}

				return(*this);
			}

			CMultiSet<TKeyType>& operator=(std::initializer_list<TKeyType> Other)
			{
				MMultiSet=Other;

				return(*this);
			}

		public:
			void Add(const TKeyType& Key)
			{
				MMultiSet.insert(Key);
			}

			void Add(TKeyType&& Key)
			{
				MMultiSet.insert(FUNCTION_MOVE(Key));
			}

			void Insert(const TKeyType& Key)
			{
				MMultiSet.insert(Key);
			}

			void Insert(TKeyType&& Key)
			{
				MMultiSet.insert(FUNCTION_MOVE(Key));
			}

			Size Erase(const TKeyType& Key)
			{
				Size											NumberOfRemovedItems=MMultiSet.erase(Key);

				return(NumberOfRemovedItems);
			}

			void Clear(void) noexcept
			{
				MMultiSet.clear();
			}

		public:
			Size GetLength(void) const noexcept
			{
				Size											Length=static_cast<Size>(MMultiSet.size());
				
				return(Length);
			}

			bool IsEmpty(void) const noexcept
			{
				Size											Length=static_cast<Size>(MMultiSet.size());

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
				if (MMultiSet.find(Key)!=MMultiSet.end())
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}

			CMultiSetIterator LowerBound(const TKeyType& Key)
			{
				CMultiSetTypeIterator							Iterator=MMultiSet.lower_bound(Key);

				return(CMultiSetIterator(Iterator));
			}

			CMultiSetIteratorConst LowerBound(const TKeyType& Key) const
			{
				CMultiSetTypeIteratorConst						Iterator=MMultiSet.lower_bound(Key);

				return(CMultiSetIteratorConst(Iterator));
			}

			CMultiSetIterator UpperBound(const TKeyType& Key)
			{
				CMultiSetTypeIterator							Iterator=MMultiSet.upper_bound(Key);

				return(CMultiSetIterator(Iterator));
			}

			CMultiSetIteratorConst UpperBound(const TKeyType& Key) const
			{
				CMultiSetTypeIteratorConst						Iterator=MMultiSet.upper_bound(Key);

				return(CMultiSetIteratorConst(Iterator));
			}

			CPair<CMultiSetIterator,CMultiSetIterator> Range(const TKeyType& Key)
			{
				std::pair<CMultiSetTypeIterator,CMultiSetTypeIterator>	Pair=MMultiSet.equal_range(Key);

				return(CPair<CMultiSetIterator,CMultiSetIterator>(Pair.first,Pair.second));
			}

			CPair<CMultiSetIteratorConst,CMultiSetIteratorConst> Range(const TKeyType& Key) const
			{
				std::pair<CMultiSetTypeIteratorConst,CMultiSetTypeIteratorConst>	Pair=MMultiSet.equal_range(Key);

				return(CPair<CMultiSetIteratorConst,CMultiSetIteratorConst>(Pair.first,Pair.second));
			}

			virtual CEnumeratorConstPointer GetEnumeratorConst(void) const override
			{
				CEnumeratorConstPointer							Enumerator=CEnumeratorConstPointer(new CMultiSetKeyEnumeratorConst(*this));

				return(Enumerator);
			}

			CMultiSetIterator Begin(void)
			{
				return(MMultiSet.begin());
			}

			CMultiSetIterator End(void)
			{
				return(MMultiSet.end());
			}

			CMultiSetIteratorConst ConstBegin(void) const
			{
				return(MMultiSet.cbegin());
			}

			CMultiSetIteratorConst ConstEnd(void) const
			{
				return(MMultiSet.cend());
			}

			CMultiSetIteratorConst Begin(void) const
			{
				return(MMultiSet.cbegin());
			}

			CMultiSetIteratorConst End(void) const
			{
				return(MMultiSet.cend());
			}

			CMultiSetReverseIterator ReverseBegin(void)
			{
				return(MMultiSet.rbegin());
			}

			CMultiSetReverseIterator ReverseEnd(void)
			{
				return(MMultiSet.rend());
			}

			CMultiSetReverseIteratorConst ConstReverseBegin(void) const
			{
				return(MMultiSet.crbegin());
			}

			CMultiSetReverseIteratorConst ConstReverseEnd(void) const
			{
				return(MMultiSet.crend());
			}

			CMultiSetReverseIteratorConst ReverseBegin(void) const
			{
				return(MMultiSet.crbegin());
			}

			CMultiSetReverseIteratorConst ReverseEnd(void) const
			{
				return(MMultiSet.crend());
			}

			CMultiSetIterator begin(void)
			{
				return(MMultiSet.begin());
			}

			CMultiSetIterator end(void)
			{
				return(MMultiSet.end());
			}

			CMultiSetIteratorConst begin(void) const
			{
				return(MMultiSet.cbegin());
			}

			CMultiSetIteratorConst end(void) const
			{
				return(MMultiSet.cend());
			}

			CMultiSetReverseIterator rbegin(void)
			{
				return(MMultiSet.rbegin());
			}

			CMultiSetReverseIterator rend(void)
			{
				return(MMultiSet.rend());
			}

			CMultiSetReverseIteratorConst rbegin(void) const
			{
				return(MMultiSet.crbegin());
			}

			CMultiSetReverseIteratorConst rend(void) const
			{
				return(MMultiSet.crend());
			}

		public:
			CMultiSet(void)
				: MMultiSet()
			{
			}

			CMultiSet(const CMultiSet<TKeyType>& Other)
				: MMultiSet(Other.MMultiSet)
			{
			}

			CMultiSet(CMultiSet<TKeyType>&& Other) noexcept
				: MMultiSet(FUNCTION_MOVE(Other.MMultiSet))
			{
				Other.Clear();
			}

			CMultiSet(const IEnumerableConst<TKeyType>& Other)
				: MMultiSet()
			{
				CEnumeratorConstPointer							Enumerator=Other.GetEnumeratorConst();

				while(Enumerator->MoveNext()==true)
				{
					MMultiSet.insert(Enumerator->GetCurrentConst());
				}
			}

			CMultiSet(std::initializer_list<TKeyType> Other)
				: MMultiSet(Other)
			{
			}

			virtual ~CMultiSet(void) override
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------