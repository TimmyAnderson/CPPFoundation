//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <list>
#include <algorithm>
#include <memory>
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Exceptions/CInvalidOperationException.h>
#include <Framework/Foundation/Exceptions/CValueOutOfRangeException.h>
#include "CIterators.h"
#include "IEnumerable.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	template<typename TItemType>
	class CList final : public CObject, public IEnumerable<TItemType>
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			class CListEnumerator : public IEnumerator<TItemType>
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					using										CListType=CList<TItemType>;
					using										CListTypeIterator=typename CListType::CListIterator;

				private:
					CList<TItemType>&							MList;
					bool										MIsBeforeFirstItem;
					CListTypeIterator							MIterator;

				public:
					virtual void Reset(void) override
					{
						MIsBeforeFirstItem=true;
						MIterator=MList.Begin();
					}

					virtual bool MoveNext(void) override
					{
						if (MIsBeforeFirstItem==true)
						{
							MIsBeforeFirstItem=false;

							if (MIterator!=MList.End())
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
							if (MIterator!=MList.End())
							{
								if (++MIterator!=MList.End())
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

					virtual const TItemType& GetCurrentConst(void) const override
					{
						if (MIsBeforeFirstItem==false && MIterator!=MList.End())
						{
							return(*MIterator);
						}
						else
						{
							throw(CValueOutOfRangeException("ENUMERATOR is OUT of RANGE !"));
						}
					}

					virtual TItemType& GetCurrent(void) override
					{
						if (MIsBeforeFirstItem==false && MIterator!=MList.End())
						{
							return(*MIterator);
						}
						else
						{
							throw(CValueOutOfRangeException("ENUMERATOR is OUT of RANGE !"));
						}
					}

				public:
					CListEnumerator(CListType& List)
						: MList(List), MIsBeforeFirstItem(true), MIterator(List.Begin())
					{
						Reset();
					}

					virtual ~CListEnumerator(void) override
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
			class CListEnumeratorConst : public IEnumeratorConst<TItemType>
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					using										CListType=CList<TItemType>;
					using										CListTypeIteratorConst=typename CListType::CListIteratorConst;

				private:
					const CList<TItemType>&						MList;
					bool										MIsBeforeFirstItem;
					CListTypeIteratorConst						MIterator;

				public:
					virtual void Reset(void) override
					{
						MIsBeforeFirstItem=true;
						MIterator=MList.Begin();
					}

					virtual bool MoveNext(void) override
					{
						if (MIsBeforeFirstItem==true)
						{
							MIsBeforeFirstItem=false;

							if (MIterator!=MList.End())
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
							if (MIterator!=MList.End())
							{
								if (++MIterator!=MList.End())
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

					virtual const TItemType& GetCurrentConst(void) const override
					{
						if (MIsBeforeFirstItem==false && MIterator!=MList.End())
						{
							return(*MIterator);
						}
						else
						{
							throw(CValueOutOfRangeException("ENUMERATOR is OUT of RANGE !"));
						}
					}

				public:
					CListEnumeratorConst(const CListType& List)
						: MList(List), MIsBeforeFirstItem(true), MIterator(List.Begin())
					{
						Reset();
					}

					virtual ~CListEnumeratorConst(void) override
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private:
			using												CListType=std::list<TItemType>;

		public:
			using												CEnumeratorPointer=CSharedPointer<IEnumerator<TItemType>>;
			using												CEnumeratorConstPointer=CSharedPointer<IEnumeratorConst<TItemType>>;
			using												CListIterator=typename std::list<TItemType>::iterator;
			using												CListIteratorConst=typename std::list<TItemType>::const_iterator;
			using												CListReverseIterator=typename std::list<TItemType>::reverse_iterator;
			using												CListReverseIteratorConst=typename std::list<TItemType>::const_reverse_iterator;

		private:
			CListType											MList;

		public:
			CList<TItemType>& operator=(const CList<TItemType>& Other)
			{
				MList=Other.MList;

				return(*this);
			}

			CList<TItemType>& operator=(CList<TItemType>&& Other)
			{
				MList=FUNCTION_MOVE(Other.MList);
				Other.Clear();

				return(*this);
			}

			CList<TItemType>& operator=(const std::list<TItemType>& Other)
			{
				MList=Other;

				return(*this);
			}

			CList<TItemType>& operator=(std::list<TItemType>&& Other)
			{
				MList=FUNCTION_MOVE(Other);
				Other.clear();

				return(*this);
			}

			CList<TItemType>& operator=(const IEnumerableConst<TItemType>& Other)
			{
				Clear();

				CEnumeratorConstPointer							Enumerator=Other.GetEnumeratorConst();

				while(Enumerator->MoveNext()==true)
				{
					MList.push_back(Enumerator->GetCurrentConst());
				}

				return(*this);
			}

			CList<TItemType>& operator=(std::initializer_list<TItemType> Other)
			{
				MList=Other;

				return(*this);
			}

		public:
			Size GetLength(void) const noexcept
			{
				Size											Length=static_cast<Size>(MList.size());
				
				return(Length);
			}

			bool IsEmpty(void) const noexcept
			{
				Size											Length=static_cast<Size>(MList.size());
				
				if (Length==0)
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}

			// If COLLECTION is EMPTY, METHOD throws the EXCEPTION [CInvalidOperationException].
			TItemType& Front(void)
			{
				if (MList.empty()==true)
				{
					throw(CInvalidOperationException("COLLECTION is EMPTY !"));
				}
				else
				{
					return(MList.front());
				}
			}

			// If COLLECTION is EMPTY, METHOD throws the EXCEPTION [CInvalidOperationException].
			const TItemType& Front(void) const
			{
				if (MList.empty()==true)
				{
					throw(CInvalidOperationException("COLLECTION is EMPTY !"));
				}
				else
				{
					return(MList.front());
				}
			}

			// If COLLECTION is EMPTY, METHOD throws the EXCEPTION [CInvalidOperationException].
			TItemType& Back(void)
			{
				if (MList.empty()==true)
				{
					throw(CInvalidOperationException("COLLECTION is EMPTY !"));
				}
				else
				{
					return(MList.back());
				}
			}

			// If COLLECTION is EMPTY, METHOD throws the EXCEPTION [CInvalidOperationException].
			const TItemType& Back(void) const
			{
				if (MList.empty()==true)
				{
					throw(CInvalidOperationException("COLLECTION is EMPTY !"));
				}
				else
				{
					return(MList.back());
				}
			}

			void PushFront(const TItemType& Item)
			{
				MList.push_front(Item);
			}

			void PushFront(TItemType&& Item)
			{
				MList.push_front(FUNCTION_MOVE(Item));
			}

			void PushBack(const TItemType& Item)
			{
				MList.push_back(Item);
			}

			void PushBack(TItemType&& Item)
			{
				MList.push_back(FUNCTION_MOVE(Item));
			}

			// If COLLECTION is EMPTY, METHOD throws the EXCEPTION [CInvalidOperationException].
			void PopFront(void)
			{
				if (MList.empty()==true)
				{
					throw(CInvalidOperationException("COLLECTION is EMPTY !"));
				}
				else
				{
					MList.pop_front();
				}
			}

			// METHOD uses COPY or MOVE OPERATOR=.
			bool PopFront(TItemType& Item)
			{
				if (MList.empty()==true)
				{
					return(false);
				}
				else
				{
					// Can use MOVE OPERATOR= (if implemented by the CLASS [TItemType]) because, OBJECT will be REMOVED from COLLECTION in the following line of code. If MOVE OPERATOR= is NOT IMPLEMENTED by the CLASS [TItemType] COPY OPERATOR is used.
					Item=FUNCTION_MOVE(MList.front());
					MList.pop_front();

					return(true);
				}
			}

			// If COLLECTION is EMPTY, METHOD throws the EXCEPTION [CInvalidOperationException].
			void PopBack(void)
			{
				if (MList.empty()==true)
				{
					throw(CInvalidOperationException("COLLECTION is EMPTY !"));
				}
				else
				{
					MList.pop_back();
				}
			}

			// METHOD uses COPY or MOVE OPERATOR=.
			bool PopBack(TItemType& Item)
			{
				if (MList.empty()==true)
				{
					return(false);
				}
				else
				{
					// Can use MOVE OPERATOR= (if implemented by the CLASS [TItemType]) because, OBJECT will be REMOVED from COLLECTION in the following line of code. If MOVE OPERATOR= is NOT IMPLEMENTED by the CLASS [TItemType] COPY OPERATOR is used.
					Item=FUNCTION_MOVE(MList.back());
					MList.pop_back();

					return(true);
				}
			}

			CListIterator Insert(CListIterator Position, const TItemType& Item)
			{
				return(MList.insert(Position,Item));
			}

			CListIterator Insert(CListIteratorConst Position, const TItemType& Item)
			{
				return(MList.insert(Position,Item));
			}

			CListIterator Insert(CListIterator Position, TItemType&& Item)
			{
				return(MList.insert(Position,FUNCTION_MOVE(Item)));
			}

			CListIterator Insert(CListIteratorConst Position, TItemType&& Item)
			{
				return(MList.insert(Position,FUNCTION_MOVE(Item)));
			}

			CListIterator Erase(CListIterator Position)
			{
				return(MList.erase(Position));
			}

			CListIterator Erase(CListIteratorConst Position)
			{
				return(MList.erase(Position));
			}

			CListIterator Erase(CListIterator First, CListIterator Last)
			{
				return(MList.erase(First,Last));
			}

			CListIterator Erase(CListIteratorConst First, CListIteratorConst Last)
			{
				return(MList.erase(First,Last));
			}

			void Remove(const TItemType& Value)
			{
				MList.remove(Value);
			}

			template<typename TComparePredicate>
			void RemoveIf(const TComparePredicate& ComparePredicate)
			{
				MList.remove_if(ComparePredicate);
			}

			void Clear(void) noexcept
			{
				MList.clear();
			}

			template<typename TComparePredicate>
			bool Contains(const TComparePredicate& ComparePredicate) const
			{
				CListIteratorConst								Iterator=Begin();

				while(Iterator!=End())
				{
					if (ComparePredicate(*Iterator)==true)
					{
						return(true);
					}

					Iterator++;
				}

				return(false);
			}

			template<typename TComparePredicate>
			CListIteratorConst FindFirstIterator(const TComparePredicate& ComparePredicate, CListIteratorConst Iterator) const
			{
				while(Iterator!=End())
				{
					if (ComparePredicate(*Iterator)==true)
					{
						return(Iterator);
					}

					Iterator++;
				}

				return(Iterator);
			}

			template<typename TComparePredicate>
			CListReverseIteratorConst FindLastIterator(const TComparePredicate& ComparePredicate, CListReverseIteratorConst Iterator) const
			{
				while(Iterator!=ReverseEnd())
				{
					if (ComparePredicate(*Iterator)==true)
					{
						return(Iterator);
					}

					Iterator++;
				}

				return(Iterator);
			}

			template<typename TComparePredicate>
			bool FindFirst(const TComparePredicate& ComparePredicate, TItemType& Value, CListIteratorConst Iterator) const
			{
				while(Iterator!=End())
				{
					if (ComparePredicate(*Iterator)==true)
					{
						Value=*Iterator;

						return(true);
					}

					Iterator++;
				}

				return(false);
			}

			template<typename TComparePredicate>
			bool FindLast(const TComparePredicate& ComparePredicate, TItemType& Value, CListReverseIteratorConst Iterator) const
			{
				while(Iterator!=ReverseEnd())
				{
					if (ComparePredicate(*Iterator)==true)
					{
						Value=*Iterator;

						return(true);
					}

					Iterator++;
				}

				return(false);
			}

			void Sort(void)
			{
				MList.sort();
			}

			template<typename TIsLessThanPredicate>
			void Sort(const TIsLessThanPredicate& IsLessThanPredicate)
			{
				MList.sort(IsLessThanPredicate);
			}

			void Resize(Size Count)
			{
				MList.resize(Count);
			}

			void Reverse(void)
			{
				MList.reverse();
			}

			virtual CEnumeratorPointer GetEnumerator(void) override
			{
				CEnumeratorPointer								Enumerator=CEnumeratorPointer(new CListEnumerator(*this));

				return(Enumerator);
			}

			virtual CEnumeratorConstPointer GetEnumeratorConst(void) const override
			{
				CEnumeratorConstPointer							Enumerator=CEnumeratorConstPointer(new CListEnumeratorConst(*this));

				return(Enumerator);
			}

			CListIterator Begin(void)
			{
				return(MList.begin());
			}

			CListIterator End(void)
			{
				return(MList.end());
			}

			CListIteratorConst Begin(void) const
			{
				return(MList.cbegin());
			}

			CListIteratorConst End(void) const
			{
				return(MList.cend());
			}

			CListReverseIterator ReverseBegin(void)
			{
				return(MList.rbegin());
			}

			CListReverseIterator ReverseEnd(void)
			{
				return(MList.rend());
			}

			CListReverseIteratorConst ReverseBegin(void) const
			{
				return(MList.crbegin());
			}

			CListReverseIteratorConst ReverseEnd(void) const
			{
				return(MList.crend());
			}

			CListIterator begin(void)
			{
				return(MList.begin());
			}

			CListIterator end(void)
			{
				return(MList.end());
			}

			CListIteratorConst begin(void) const
			{
				return(MList.cbegin());
			}

			CListIteratorConst end(void) const
			{
				return(MList.cend());
			}

			CListReverseIterator rbegin(void)
			{
				return(MList.rbegin());
			}

			CListReverseIterator rend(void)
			{
				return(MList.rend());
			}

			CListReverseIteratorConst rbegin(void) const
			{
				return(MList.crbegin());
			}

			CListReverseIteratorConst rend(void) const
			{
				return(MList.crend());
			}

		public:
			CList(void)
				: MList()
			{
			}

			CList(const CList<TItemType>& Other)
				: MList(Other.MList)
			{
			}

			CList(CList<TItemType>&& Other)
				: MList(FUNCTION_MOVE(Other.MList))
			{
				Other.Clear();
			}

			CList(const std::list<TItemType>& Other)
				: MList(Other)
			{
			}

			CList(std::list<TItemType>&& Other)
				: MList(FUNCTION_MOVE(Other))
			{
				Other.clear();
			}

			CList(const IEnumerableConst<TItemType>& Other)
				: MList()
			{
				CEnumeratorConstPointer							Enumerator=Other.GetEnumeratorConst();

				while(Enumerator->MoveNext()==true)
				{
					MList.push_back(Enumerator->GetCurrentConst());
				}
			}

			CList(std::initializer_list<TItemType> Other)
				: MList(Other)
			{
			}

			virtual ~CList(void) override
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------