//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <deque>
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
	class CDequeue final : public CObject, public IEnumerable<TItemType>
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			class CDequeueEnumerator : public IEnumerator<TItemType>
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					CDequeue<TItemType>&						MDequeue;
					bool										MIsBeforeFirstItem;
					Size										MPosition;

				public:
					virtual void Reset(void) override
					{
						MIsBeforeFirstItem=true;
						MPosition=0;
					}

					virtual bool MoveNext(void) override
					{
						if (MIsBeforeFirstItem==true)
						{
							MIsBeforeFirstItem=false;

							if (MPosition<MDequeue.GetLength())
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
							if ((MPosition+1)<MDequeue.GetLength())
							{
								MPosition++;

								return(true);
							}
							else
							{
								MPosition=MDequeue.GetLength();

								return(false);
							}
						}
					}

					virtual const TItemType& GetCurrentConst(void) const override
					{
						if (MIsBeforeFirstItem==false && MPosition<MDequeue.GetLength())
						{
							return(MDequeue[MPosition]);
						}
						else
						{
							throw(CValueOutOfRangeException("ENUMERATOR is OUT of RANGE !"));
						}
					}

					virtual TItemType& GetCurrent(void) override
					{
						if (MIsBeforeFirstItem==false && MPosition<MDequeue.GetLength())
						{
							return(MDequeue[MPosition]);
						}
						else
						{
							throw(CValueOutOfRangeException("ENUMERATOR is OUT of RANGE !"));
						}
					}

				public:
					CDequeueEnumerator(CDequeue<TItemType>& Vector)
						: MDequeue(Vector), MIsBeforeFirstItem(true), MPosition(0)
					{
						Reset();
					}

					virtual ~CDequeueEnumerator(void) override
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
			class CDequeueEnumeratorConst : public IEnumeratorConst<TItemType>
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					const CDequeue<TItemType>&					MDequeue;
					bool										MIsBeforeFirstItem;
					Size										MPosition;

				public:
					virtual void Reset(void) override
					{
						MIsBeforeFirstItem=true;
						MPosition=0;
					}

					virtual bool MoveNext(void) override
					{
						if (MIsBeforeFirstItem==true)
						{
							MIsBeforeFirstItem=false;

							if (MPosition<MDequeue.GetLength())
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
							if ((MPosition+1)<MDequeue.GetLength())
							{
								MPosition++;

								return(true);
							}
							else
							{
								MPosition=MDequeue.GetLength();

								return(false);
							}
						}
					}

					virtual const TItemType& GetCurrentConst(void) const override
					{
						if (MIsBeforeFirstItem==false && MPosition<MDequeue.GetLength())
						{
							return(MDequeue[MPosition]);
						}
						else
						{
							throw(CValueOutOfRangeException("ENUMERATOR is OUT of RANGE !"));
						}
					}

				public:
					CDequeueEnumeratorConst(const CDequeue<TItemType>& Vector)
						: MDequeue(Vector), MIsBeforeFirstItem(true), MPosition(0)
					{
						Reset();
					}

					virtual ~CDequeueEnumeratorConst(void) override
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public:
			static const Size									END=static_cast<Size>(-1);

		public:
			using												CEnumeratorPointer=CSharedPointer<IEnumerator<TItemType>>;
			using												CEnumeratorConstPointer=CSharedPointer<IEnumeratorConst<TItemType>>;
			using												CDequeueIterator=typename std::deque<TItemType>::iterator;
			using												CDequeueIteratorConst=typename std::deque<TItemType>::const_iterator;
			using												CDequeueReverseIterator=typename std::deque<TItemType>::reverse_iterator;
			using												CDequeueReverseIteratorConst=typename std::deque<TItemType>::const_reverse_iterator;

		private:
			std::deque<TItemType>								MDequeue;

		public:
			CDequeue<TItemType>& operator=(const CDequeue<TItemType>& Other)
			{
				MDequeue=Other.MDequeue;

				return(*this);
			}

			CDequeue<TItemType>& operator=(CDequeue<TItemType>&& Other)
			{
				MDequeue=FUNCTION_MOVE(Other.MDequeue);

				return(*this);
			}

			CDequeue<TItemType>& operator=(const std::deque<TItemType>& Other)
			{
				MDequeue=Other;

				return(*this);
			}

			CDequeue<TItemType>& operator=(std::deque<TItemType>&& Other)
			{
				MDequeue=FUNCTION_MOVE(Other);

				return(*this);
			}

			CDequeue<TItemType>& operator=(IEnumerable<TItemType>& Other)
			{
				Clear();

				CEnumeratorPointer								Enumerator=Other.GetEnumerator();

				while(Enumerator->MoveNext()==true)
				{
					MDequeue.push_back(Enumerator->GetCurrent());
				}

				return(*this);
			}

			CDequeue<TItemType>& operator=(const IEnumerableConst<TItemType>& Other)
			{
				Clear();

				CEnumeratorConstPointer							Enumerator=Other.GetEnumeratorConst();

				while(Enumerator->MoveNext()==true)
				{
					MDequeue.push_back(Enumerator->GetCurrentConst());
				}

				return(*this);
			}

			CDequeue<TItemType>& operator=(std::initializer_list<TItemType> Other)
			{
				MDequeue=Other;

				return(*this);
			}

			TItemType& operator[](Size Index)
			{
				CheckIndex(Index,false);

				return(MDequeue[static_cast<typename std::deque<TItemType>::size_type>(Index)]);
			}

			const TItemType& operator[](Size Index) const
			{
				CheckIndex(Index,false);

				return(MDequeue[static_cast<typename std::deque<TItemType>::size_type>(Index)]);
			}

		private:
			void CheckIndex(Size Index, bool AllowAfterLastPosition) const
			{
				if (AllowAfterLastPosition==false)
				{
					if (Index>=GetLength())
					{
						throw(CValueOutOfRangeException("INDEX is OUT of RANGE !"));
					}
				}
				else
				{
					if (Index>GetLength())
					{
						throw(CValueOutOfRangeException("INDEX is OUT of RANGE !"));
					}
				}
			}

			void CheckOffset(Size Offset) const
			{
				if (Offset>GetLength() && Offset!=END)
				{
					throw(CValueOutOfRangeException("OFFSET is OUT of RANGE !"));
				}
			}

		public:
			Size GetLength(void) const noexcept
			{
				Size											Length=static_cast<Size>(MDequeue.size());
				
				return(Length);
			}

			bool IsEmpty(void) const noexcept
			{
				Size											Length=static_cast<Size>(MDequeue.size());
				
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
				if (MDequeue.empty()==true)
				{
					throw(CInvalidOperationException("COLLECTION is EMPTY !"));
				}
				else
				{
					return(MDequeue.front());
				}
			}

			// If COLLECTION is EMPTY, METHOD throws the EXCEPTION [CInvalidOperationException].
			const TItemType& Front(void) const
			{
				if (MDequeue.empty()==true)
				{
					throw(CInvalidOperationException("COLLECTION is EMPTY !"));
				}
				else
				{
					return(MDequeue.front());
				}
			}

			// If COLLECTION is EMPTY, METHOD throws the EXCEPTION [CInvalidOperationException].
			TItemType& Back(void)
			{
				if (MDequeue.empty()==true)
				{
					throw(CInvalidOperationException("COLLECTION is EMPTY !"));
				}
				else
				{
					return(MDequeue.back());
				}
			}

			// If COLLECTION is EMPTY, METHOD throws the EXCEPTION [CInvalidOperationException].
			const TItemType& Back(void) const
			{
				if (MDequeue.empty()==true)
				{
					throw(CInvalidOperationException("COLLECTION is EMPTY !"));
				}
				else
				{
					return(MDequeue.back());
				}
			}

			void PushFront(const TItemType& Item)
			{
				MDequeue.push_front(Item);
			}

			void PushFront(TItemType&& Item)
			{
				MDequeue.push_front(FUNCTION_MOVE(Item));
			}

			void PushBack(const TItemType& Item)
			{
				MDequeue.push_back(Item);
			}

			void PushBack(TItemType&& Item)
			{
				MDequeue.push_back(FUNCTION_MOVE(Item));
			}

			// If COLLECTION is EMPTY, METHOD throws the EXCEPTION [CInvalidOperationException].
			void PopFront(void)
			{
				if (MDequeue.empty()==true)
				{
					throw(CInvalidOperationException("COLLECTION is EMPTY !"));
				}
				else
				{
					MDequeue.pop_front();
				}
			}

			// METHOD uses COPY or MOVE OPERATOR=.
			bool PopFront(TItemType& Item)
			{
				if (MDequeue.empty()==true)
				{
					return(false);
				}
				else
				{
					// Can use MOVE OPERATOR= (if implemented by the CLASS [TItemType]) because, OBJECT will be REMOVED from COLLECTION in the following line of code. If MOVE OPERATOR= is NOT IMPLEMENTED by the CLASS [TItemType] COPY OPERATOR is used.
					Item=FUNCTION_MOVE(MDequeue.front());
					MDequeue.pop_front();

					return(true);
				}
			}

			// If COLLECTION is EMPTY, METHOD throws the EXCEPTION [CInvalidOperationException].
			void PopBack(void)
			{
				if (MDequeue.empty()==true)
				{
					throw(CInvalidOperationException("COLLECTION is EMPTY !"));
				}
				else
				{
					MDequeue.pop_back();
				}
			}

			// METHOD uses COPY or MOVE OPERATOR=.
			bool PopBack(TItemType& Item)
			{
				if (MDequeue.empty()==true)
				{
					return(false);
				}
				else
				{
					// Can use MOVE OPERATOR= (if implemented by the CLASS [TItemType]) because, OBJECT will be REMOVED from COLLECTION in the following line of code. If MOVE OPERATOR= is NOT IMPLEMENTED by the CLASS [TItemType] COPY OPERATOR is used.
					Item=FUNCTION_MOVE(MDequeue.back());
					MDequeue.pop_back();

					return(true);
				}
			}

			void Insert(const TItemType& Item, Size Offset)
			{
				CheckIndex(Offset,true);

				MDequeue.insert(MDequeue.begin()+static_cast<typename std::deque<TItemType>::size_type>(Offset),Item);
			}

			CDequeueIterator Insert(CDequeueIterator Position, const TItemType& Item)
			{
				return(MDequeue.insert(Position,Item));
			}

			CDequeueIterator Insert(CDequeueIteratorConst Position, const TItemType& Item)
			{
				return(MDequeue.insert(Position,Item));
			}

			CDequeueIterator Insert(CDequeueIterator Position, TItemType&& Item)
			{
				return(MDequeue.insert(Position,FUNCTION_MOVE(Item)));
			}

			CDequeueIterator Insert(CDequeueIteratorConst Position, TItemType&& Item)
			{
				return(MDequeue.insert(Position,FUNCTION_MOVE(Item)));
			}

			void Erase(Size Offset)
			{
				CheckIndex(Offset,false);

				MDequeue.erase(MDequeue.begin()+static_cast<typename std::deque<TItemType>::size_type>(Offset));
			}

			void Erase(Size Offset, Size Length)
			{
				CheckIndex(Offset,false);
				CheckIndex(Offset+Length,true);

				MDequeue.erase(MDequeue.begin()+static_cast<typename std::deque<TItemType>::size_type>(Offset),MDequeue.begin()+static_cast<typename std::deque<TItemType>::size_type>(Offset)+static_cast<typename std::deque<TItemType>::size_type>(Length));
			}

			CDequeueIterator Erase(CDequeueIterator Position)
			{
				return(MDequeue.erase(Position));
			}

			CDequeueIterator Erase(CDequeueIteratorConst Position)
			{
				return(MDequeue.erase(Position));
			}

			CDequeueIterator Erase(CDequeueIterator First, CDequeueIterator Last)
			{
				return(MDequeue.erase(First,Last));
			}

			CDequeueIterator Erase(CDequeueIteratorConst First, CDequeueIteratorConst Last)
			{
				return(MDequeue.erase(First,Last));
			}

			void Clear(void) noexcept
			{
				MDequeue.clear();
			}

			template<typename TComparePredicate>
			bool Contains(const TComparePredicate& ComparePredicate) const
			{
				Size											Length=GetLength();

				for(Size Index=0;Index<Length;Index++)
				{
					if (ComparePredicate((*this)[Index])==true)
					{
						return(true);
					}
				}

				return(false);
			}

			Size FindFirstIndex(const TItemType& Value, Size Offset=0) const
			{
				CheckOffset(Offset);

				Size											Length=GetLength();

				for(Size Index=Offset;Index<Length;Index++)
				{
					if (Value==(*this)[Index])
					{
						return(Index);
					}
				}

				return(END);
			}

			template<typename TComparePredicate>
			Size FindFirstIndex(const TComparePredicate& ComparePredicate, Size Offset=0) const
			{
				CheckOffset(Offset);

				Size											Length=GetLength();

				for(Size Index=Offset;Index<Length;Index++)
				{
					if (ComparePredicate((*this)[Index])==true)
					{
						return(Index);
					}
				}

				return(END);
			}

			Size FindLastIndex(const TItemType& Value, Size Offset=END) const
			{
				CheckOffset(Offset);

				Size											Length=GetLength();

				if (Offset==END || Offset==Length)
				{
					Offset=Length-1;
				}

				for(Size Index=Offset;;Index--)
				{
					if (Value==(*this)[Index])
					{
						return(Index);
					}

					if (Index==0)
					{
						break;
					}
				}

				return(END);
			}

			template<typename TComparePredicate>
			Size FindLastIndex(const TComparePredicate& ComparePredicate, Size Offset=END) const
			{
				CheckOffset(Offset);

				Size											Length=GetLength();

				if (Offset==END || Offset==Length)
				{
					Offset=Length-1;
				}

				for(Size Index=Offset;;Index--)
				{
					if (ComparePredicate((*this)[Index])==true)
					{
						return(Index);
					}

					if (Index==0)
					{
						break;
					}
				}

				return(END);
			}

			void Shrink(void)
			{
				MDequeue.shrink_to_fit();
			}

			virtual CEnumeratorPointer GetEnumerator(void) override
			{
				CEnumeratorPointer								Enumerator=CEnumeratorPointer(new CDequeueEnumerator(*this));

				return(Enumerator);
			}

			virtual CEnumeratorConstPointer GetEnumeratorConst(void) const override
			{
				CEnumeratorConstPointer							Enumerator=CEnumeratorConstPointer(new CDequeueEnumeratorConst(*this));

				return(Enumerator);
			}

			CDequeueIterator Begin(void)
			{
				return(MDequeue.begin());
			}

			CDequeueIterator End(void)
			{
				return(MDequeue.end());
			}

			CDequeueIteratorConst Begin(void) const
			{
				return(MDequeue.cbegin());
			}

			CDequeueIteratorConst End(void) const
			{
				return(MDequeue.cend());
			}

			CDequeueReverseIterator ReverseBegin(void)
			{
				return(MDequeue.rbegin());
			}

			CDequeueReverseIterator ReverseEnd(void)
			{
				return(MDequeue.rend());
			}

			CDequeueReverseIteratorConst ReverseBegin(void) const
			{
				return(MDequeue.crbegin());
			}

			CDequeueReverseIteratorConst ReverseEnd(void) const
			{
				return(MDequeue.crend());
			}

			CDequeueIterator begin(void)
			{
				return(MDequeue.begin());
			}

			CDequeueIterator end(void)
			{
				return(MDequeue.end());
			}

			CDequeueIteratorConst begin(void) const
			{
				return(MDequeue.cbegin());
			}

			CDequeueIteratorConst end(void) const
			{
				return(MDequeue.cend());
			}

			CDequeueReverseIterator rbegin(void)
			{
				return(MDequeue.rbegin());
			}

			CDequeueReverseIterator rend(void)
			{
				return(MDequeue.rend());
			}

			CDequeueReverseIteratorConst rbegin(void) const
			{
				return(MDequeue.crbegin());
			}

			CDequeueReverseIteratorConst rend(void) const
			{
				return(MDequeue.crend());
			}

		public:
			CDequeue(void)
				: MDequeue()
			{
			}

			CDequeue(const CDequeue<TItemType>& Other)
				: MDequeue(Other.MDequeue)
			{
			}

			CDequeue(CDequeue<TItemType>&& Other)
				: MDequeue(FUNCTION_MOVE(Other.MDequeue))
			{
			}

			CDequeue(const std::deque<TItemType>& Other)
				: MDequeue(Other)
			{
			}

			CDequeue(std::deque<TItemType>&& Other)
				: MDequeue(FUNCTION_MOVE(Other))
			{
			}

			CDequeue(IEnumerable<TItemType>& Other)
				: MDequeue()
			{
				CEnumeratorPointer								Enumerator=Other.GetEnumerator();

				while(Enumerator->MoveNext()==true)
				{
					MDequeue.push_back(Enumerator->GetCurrent());
				}
			}

			CDequeue(const IEnumerableConst<TItemType>& Other)
				: MDequeue()
			{
				CEnumeratorConstPointer							Enumerator=Other.GetEnumeratorConst();

				while(Enumerator->MoveNext()==true)
				{
					MDequeue.push_back(Enumerator->GetCurrentConst());
				}
			}

			CDequeue(std::initializer_list<TItemType> Other)
				: MDequeue(Other)
			{
			}

			virtual ~CDequeue(void) override
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------