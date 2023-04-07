//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <deque>
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Foundation/Collections/CVector.h>
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Exceptions/CInvalidOperationException.h>
#include <Framework/Foundation/Exceptions/CValueOutOfRangeException.h>
#include <Framework/Foundation/Threads/CMutex.h>
#include <Framework/Foundation/Threads/CLock.h>
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
	class CTSDequeue final : public CObject, public IEnumerable<TItemType>
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			class CTSDequeueEnumerator : public IEnumerator<TItemType>
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					CTSDequeue<TItemType>&						MDequeue;
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
					CTSDequeueEnumerator(CTSDequeue<TItemType>& Vector)
						: MDequeue(Vector), MIsBeforeFirstItem(true), MPosition(0)
					{
						Reset();
					}

					virtual ~CTSDequeueEnumerator(void) override
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
			class CTSDequeueEnumeratorConst : public IEnumeratorConst<TItemType>
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					const CTSDequeue<TItemType>&				MDequeue;
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
					CTSDequeueEnumeratorConst(const CTSDequeue<TItemType>& Vector)
						: MDequeue(Vector), MIsBeforeFirstItem(true), MPosition(0)
					{
						Reset();
					}

					virtual ~CTSDequeueEnumeratorConst(void) override
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
			using												CTSDequeueIterator=typename std::deque<TItemType>::iterator;
			using												CTSDequeueIteratorConst=typename std::deque<TItemType>::const_iterator;

		private:
			std::deque<TItemType>								MDequeue;
			mutable CMutex										MMutex;

		public:
			CTSDequeue<TItemType>& operator=(const CTSDequeue<TItemType>& Other)
			{
				CLock											Lock(MMutex);
				{
					MDequeue=Other.MDequeue;

					return(*this);
				}
			}

			CTSDequeue<TItemType>& operator=(CTSDequeue<TItemType>&& Other)
			{
				CLock											Lock(MMutex);
				{
					MDequeue=FUNCTION_MOVE(Other.MDequeue);
				}

				Other.Clear();

				return(*this);
			}

			CTSDequeue<TItemType>& operator=(const std::deque<TItemType>& Other)
			{
				CLock											Lock(MMutex);
				{
					MDequeue=Other;

					return(*this);
				}
			}

			CTSDequeue<TItemType>& operator=(std::deque<TItemType>&& Other)
			{
				CLock											Lock(MMutex);
				{
					MDequeue=FUNCTION_MOVE(Other);
				}

				Other.clear();

				return(*this);
			}

			CTSDequeue<TItemType>& operator=(const IEnumerableConst<TItemType>& Other)
			{
				CLock											Lock(MMutex);
				{
					Clear();

					CEnumeratorConstPointer						Enumerator=Other.GetEnumeratorConst();

					while(Enumerator->MoveNext()==true)
					{
						MDequeue.push_back(Enumerator->GetCurrentConst());
					}

					return(*this);
				}
			}

			CTSDequeue<TItemType>& operator=(std::initializer_list<TItemType> Other)
			{
				CLock											Lock(MMutex);
				{
					MDequeue=Other;

					return(*this);
				}
			}

			TItemType& operator[](Size Index)
			{
				CLock											Lock(MMutex);
				{
					CheckIndex(Index,false);

					return(MDequeue[static_cast<typename std::deque<TItemType>::size_type>(Index)]);
				}
			}

			const TItemType& operator[](Size Index) const
			{
				CLock											Lock(MMutex);
				{
					CheckIndex(Index,false);

					return(MDequeue[static_cast<typename std::deque<TItemType>::size_type>(Index)]);
				}
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
			Size GetLength(void) const
			{
				CLock											Lock(MMutex);
				{
					Size										Length=static_cast<Size>(MDequeue.size());
				
					return(Length);
				}
			}

			bool IsEmpty(void) const
			{
				CLock											Lock(MMutex);
				{
					Size										Length=static_cast<Size>(MDequeue.size());
				
					if (Length==0)
					{
						return(true);
					}
					else
					{
						return(false);
					}
				}
			}

			// If COLLECTION is EMPTY, METHOD throws the EXCEPTION [CInvalidOperationException].
			TItemType& Front(void)
			{
				CLock											Lock(MMutex);
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
			}

			// If COLLECTION is EMPTY, METHOD throws the EXCEPTION [CInvalidOperationException].
			const TItemType& Front(void) const
			{
				CLock											Lock(MMutex);
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
			}

			// If COLLECTION is EMPTY, METHOD throws the EXCEPTION [CInvalidOperationException].
			TItemType& Back(void)
			{
				CLock											Lock(MMutex);
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
			}

			// If COLLECTION is EMPTY, METHOD throws the EXCEPTION [CInvalidOperationException].
			const TItemType& Back(void) const
			{
				CLock											Lock(MMutex);
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
			}

			void PushFront(const TItemType& Item)
			{
				CLock											Lock(MMutex);
				{
					MDequeue.push_front(Item);
				}
			}

			void PushFront(TItemType&& Item)
			{
				CLock											Lock(MMutex);
				{
					MDequeue.push_front(FUNCTION_MOVE(Item));
				}
			}

			void PushFrontAll(CVector<TItemType>& Items)
			{
				CLock											Lock(MMutex);
				{
					for(TItemType& Item : Items)
					{
						MDequeue.push_front(FUNCTION_MOVE(Item));
					}
				}
			}

			void PushFrontAll(const CVector<TItemType>& Items)
			{
				CLock											Lock(MMutex);
				{
					for(const TItemType& Item : Items)
					{
						MDequeue.push_front(Item);
					}
				}
			}

			void PushBack(const TItemType& Item)
			{
				CLock											Lock(MMutex);
				{
					MDequeue.push_back(Item);
				}
			}

			void PushBack(TItemType&& Item)
			{
				CLock											Lock(MMutex);
				{
					MDequeue.push_back(FUNCTION_MOVE(Item));
				}
			}

			void PushBackAll(const CVector<TItemType>& Items)
			{
				CLock											Lock(MMutex);
				{
					for(const TItemType& Item : Items)
					{
						MDequeue.push_back(Item);
					}
				}
			}

			void PushBackAll(CVector<TItemType>& Items)
			{
				CLock											Lock(MMutex);
				{
					for(TItemType& Item : Items)
					{
						MDequeue.push_back(FUNCTION_MOVE(Item));
					}
				}
			}

			// If COLLECTION is EMPTY, METHOD throws the EXCEPTION [CInvalidOperationException].
			void PopFront(void)
			{
				CLock											Lock(MMutex);
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
			}

			// METHOD uses COPY or MOVE OPERATOR=.
			bool PopFront(TItemType& Item)
			{
				CLock											Lock(MMutex);
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
			}

			CVector<TItemType> PopFrontAll(void)
			{
				CLock											Lock(MMutex);
				{
					CVector<TItemType>							Items;

					while(MDequeue.empty()==false)
					{
						Items.Add(FUNCTION_MOVE(MDequeue.front()));

						MDequeue.pop_front();
					}

					return(Items);
				}
			}

			// If COLLECTION is EMPTY, METHOD throws the EXCEPTION [CInvalidOperationException].
			void PopBack(void)
			{
				CLock											Lock(MMutex);
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
			}

			// METHOD uses COPY or MOVE OPERATOR=.
			bool PopBack(TItemType& Item)
			{
				CLock											Lock(MMutex);
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
			}

			CVector<TItemType> PopBackAll(void)
			{
				CLock											Lock(MMutex);
				{
					CVector<TItemType>							Items;

					while(MDequeue.empty()==false)
					{
						Items.Add(FUNCTION_MOVE(MDequeue.back()));

						MDequeue.pop_back();
					}

					return(Items);
				}
			}

			void Insert(const TItemType& Item, Size Offset)
			{
				CLock											Lock(MMutex);
				{
					CheckIndex(Offset,true);

					MDequeue.insert(MDequeue.begin()+static_cast<typename std::deque<TItemType>::size_type>(Offset),Item);
				}
			}

			CTSDequeueIterator Insert(CTSDequeueIterator Position, const TItemType& Item)
			{
				CLock											Lock(MMutex);
				{
					return(MDequeue.insert(Position,Item));
				}
			}

			CTSDequeueIterator Insert(CTSDequeueIteratorConst Position, const TItemType& Item)
			{
				CLock											Lock(MMutex);
				{
					return(MDequeue.insert(Position,Item));
				}
			}

			CTSDequeueIterator Insert(CTSDequeueIterator Position, TItemType&& Item)
			{
				CLock											Lock(MMutex);
				{
					return(MDequeue.insert(Position,FUNCTION_MOVE(Item)));
				}
			}

			CTSDequeueIterator Insert(CTSDequeueIteratorConst Position, TItemType&& Item)
			{
				CLock											Lock(MMutex);
				{
					return(MDequeue.insert(Position,FUNCTION_MOVE(Item)));
				}
			}

			void Erase(Size Offset)
			{
				CLock											Lock(MMutex);
				{
					CheckIndex(Offset,false);

					MDequeue.erase(MDequeue.begin()+static_cast<typename std::deque<TItemType>::size_type>(Offset));
				}
			}

			void Erase(Size Offset, Size Length)
			{
				CLock											Lock(MMutex);
				{
					CheckIndex(Offset,false);
					CheckIndex(Offset+Length,true);

					MDequeue.erase(MDequeue.begin()+static_cast<typename std::deque<TItemType>::size_type>(Offset),MDequeue.begin()+static_cast<typename std::deque<TItemType>::size_type>(Offset)+static_cast<typename std::deque<TItemType>::size_type>(Length));
				}
			}

			CTSDequeueIterator Erase(CTSDequeueIterator Position)
			{
				CLock											Lock(MMutex);
				{
					return(MDequeue.erase(Position));
				}
			}

			CTSDequeueIterator Erase(CTSDequeueIteratorConst Position)
			{
				CLock											Lock(MMutex);
				{
					return(MDequeue.erase(Position));
				}
			}

			CTSDequeueIterator Erase(CTSDequeueIterator First, CTSDequeueIterator Last)
			{
				CLock											Lock(MMutex);
				{
					return(MDequeue.erase(First,Last));
				}
			}

			CTSDequeueIterator Erase(CTSDequeueIteratorConst First, CTSDequeueIteratorConst Last)
			{
				CLock											Lock(MMutex);
				{
					return(MDequeue.erase(First,Last));
				}
			}

			void Clear(void)
			{
				CLock											Lock(MMutex);
				{
					MDequeue.clear();
				}
			}

			template<typename TComparePredicate>
			bool Contains(const TComparePredicate& ComparePredicate) const
			{
				CLock											Lock(MMutex);
				{
					Size										Length=GetLength();

					for(Size Index=0;Index<Length;Index++)
					{
						if (ComparePredicate((*this)[Index])==true)
						{
							return(true);
						}
					}

					return(false);
				}
			}

			Size FindFirstIndex(const TItemType& Value, Size Offset=0) const
			{
				CLock											Lock(MMutex);
				{
					CheckOffset(Offset);

					Size										Length=GetLength();

					for(Size Index=Offset;Index<Length;Index++)
					{
						if (Value==(*this)[Index])
						{
							return(Index);
						}
					}

					return(END);
				}
			}

			template<typename TComparePredicate>
			Size FindFirstIndex(const TComparePredicate& ComparePredicate, Size Offset=0) const
			{
				CLock											Lock(MMutex);
				{
					CheckOffset(Offset);

					Size										Length=GetLength();

					for(Size Index=Offset;Index<Length;Index++)
					{
						if (ComparePredicate((*this)[Index])==true)
						{
							return(Index);
						}
					}

					return(END);
				}
			}

			Size FindLastIndex(const TItemType& Value, Size Offset=END) const
			{
				CLock											Lock(MMutex);
				{
					CheckOffset(Offset);

					Size										Length=GetLength();

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
			}

			template<typename TComparePredicate>
			Size FindLastIndex(const TComparePredicate& ComparePredicate, Size Offset=END) const
			{
				CLock											Lock(MMutex);
				{
					CheckOffset(Offset);

					Size										Length=GetLength();

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
			}

			void Shrink(void)
			{
				CLock											Lock(MMutex);
				{
					MDequeue.shrink_to_fit();
				}
			}

			virtual CEnumeratorPointer GetEnumerator(void) override
			{
				CLock											Lock(MMutex);
				{
					CEnumeratorPointer							Enumerator=CEnumeratorPointer(new CTSDequeueEnumerator(*this));

					return(Enumerator);
				}
			}

			virtual CEnumeratorConstPointer GetEnumeratorConst(void) const override
			{
				CLock											Lock(MMutex);
				{
					CEnumeratorConstPointer						Enumerator=CEnumeratorConstPointer(new CTSDequeueEnumeratorConst(*this));

					return(Enumerator);
				}
			}

			CTSDequeueIterator Begin(void)
			{
				CLock											Lock(MMutex);
				{
					return(MDequeue.begin());
				}
			}

			CTSDequeueIterator End(void)
			{
				CLock											Lock(MMutex);
				{
					return(MDequeue.end());
				}
			}

			CTSDequeueIteratorConst Begin(void) const
			{
				CLock											Lock(MMutex);
				{
					return(MDequeue.begin());
				}
			}

			CTSDequeueIteratorConst End(void) const
			{
				CLock											Lock(MMutex);
				{
					return(MDequeue.end());
				}
			}

			CTSDequeueIterator begin(void)
			{
				CLock											Lock(MMutex);
				{
					return(MDequeue.begin());
				}
			}

			CTSDequeueIterator end(void)
			{
				CLock											Lock(MMutex);
				{
					return(MDequeue.end());
				}
			}

			CTSDequeueIteratorConst begin(void) const
			{
				CLock											Lock(MMutex);
				{
					return(MDequeue.begin());
				}
			}

			CTSDequeueIteratorConst end(void) const
			{
				CLock											Lock(MMutex);
				{
					return(MDequeue.end());
				}
			}

		public:
			CTSDequeue(void)
				: MDequeue(), MMutex()
			{
			}

			CTSDequeue(const CTSDequeue<TItemType>& Other)
				: MDequeue(Other.MDequeue), MMutex()
			{
			}

			CTSDequeue(CTSDequeue<TItemType>&& Other)
				: MDequeue(FUNCTION_MOVE(Other.MDequeue)), MMutex()
			{
				Other.Clear();
			}

			CTSDequeue(const std::deque<TItemType>& Other)
				: MDequeue(Other), MMutex()
			{
			}

			CTSDequeue(std::deque<TItemType>&& Other)
				: MDequeue(FUNCTION_MOVE(Other)), MMutex()
			{
				Other.clear();
			}

			CTSDequeue(const IEnumerableConst<TItemType>& Other)
				: MDequeue(), MMutex()
			{
				CEnumeratorConstPointer							Enumerator=Other.GetEnumeratorConst();

				while(Enumerator->MoveNext()==true)
				{
					MDequeue.push_back(Enumerator->GetCurrentConst());
				}
			}

			CTSDequeue(std::initializer_list<TItemType> Other)
				: MDequeue(Other), MMutex()
			{
			}

			virtual ~CTSDequeue(void) override
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------