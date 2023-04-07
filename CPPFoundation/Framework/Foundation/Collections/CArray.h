//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <array>
#include <algorithm>
#include <memory>
#include <utility>
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Foundation/Objects/CObject.h>
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
	template<typename TItemType, Size ARRAY_LENGTH>
	class CArray final : public CObject, public IEnumerable<TItemType>
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			class CArrayEnumerator : public IEnumerator<TItemType>
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					CArray<TItemType,ARRAY_LENGTH>&				MArray;
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

							if (MPosition<MArray.GetLength())
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
							if ((MPosition+1)<MArray.GetLength())
							{
								MPosition++;

								return(true);
							}
							else
							{
								MPosition=MArray.GetLength();

								return(false);
							}
						}
					}

					virtual const TItemType& GetCurrentConst(void) const override
					{
						if (MIsBeforeFirstItem==false && MPosition<MArray.GetLength())
						{
							return(MArray[MPosition]);
						}
						else
						{
							throw(CValueOutOfRangeException("ENUMERATOR is OUT of RANGE !"));
						}
					}

					virtual TItemType& GetCurrent(void) override
					{
						if (MIsBeforeFirstItem==false && MPosition<MArray.GetLength())
						{
							return(MArray[MPosition]);
						}
						else
						{
							throw(CValueOutOfRangeException("ENUMERATOR is OUT of RANGE !"));
						}
					}

				public:
					CArrayEnumerator(CArray<TItemType,ARRAY_LENGTH>& Array)
						: MArray(Array), MIsBeforeFirstItem(true), MPosition(0)
					{
					}

					virtual ~CArrayEnumerator(void) override
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
			class CArrayEnumeratorConst : public IEnumeratorConst<TItemType>
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					const CArray<TItemType,ARRAY_LENGTH>&		MArray;
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

							if (MPosition<MArray.GetLength())
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
							if ((MPosition+1)<MArray.GetLength())
							{
								MPosition++;

								return(true);
							}
							else
							{
								MPosition=MArray.GetLength();

								return(false);
							}
						}
					}

					virtual const TItemType& GetCurrentConst(void) const override
					{
						if (MIsBeforeFirstItem==false && MPosition<MArray.GetLength())
						{
							return(MArray[MPosition]);
						}
						else
						{
							throw(CValueOutOfRangeException("ENUMERATOR is OUT of RANGE !"));
						}
					}

				public:
					CArrayEnumeratorConst(const CArray<TItemType,ARRAY_LENGTH>& Array)
						: MArray(Array), MIsBeforeFirstItem(true), MPosition(0)
					{
					}

					virtual ~CArrayEnumeratorConst(void) override
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
			using												CArrayIterator=typename std::array<TItemType,ARRAY_LENGTH>::iterator;
			using												CArrayIteratorConst=typename std::array<TItemType,ARRAY_LENGTH>::const_iterator;
			using												CArrayReverseIterator=typename std::array<TItemType,ARRAY_LENGTH>::reverse_iterator;
			using												CArrayReverseIteratorConst=typename std::array<TItemType,ARRAY_LENGTH>::const_reverse_iterator;

		private:
			std::array<TItemType,ARRAY_LENGTH>					MArray;

		public:
			CArray<TItemType,ARRAY_LENGTH>& operator=(const CArray<TItemType,ARRAY_LENGTH>& Other)
			{
				MArray=Other.MArray;

				return(*this);
			}

			CArray<TItemType,ARRAY_LENGTH>& operator=(CArray<TItemType,ARRAY_LENGTH>&& Other)
			{
				MArray=FUNCTION_MOVE(Other.MArray);

				return(*this);
			}

			CArray<TItemType,ARRAY_LENGTH>& operator=(const std::array<TItemType,ARRAY_LENGTH>& Other)
			{
				MArray=Other;

				return(*this);
			}

			CArray<TItemType,ARRAY_LENGTH>& operator=(std::array<TItemType,ARRAY_LENGTH>&& Other)
			{
				MArray=FUNCTION_MOVE(Other);

				return(*this);
			}

			CArray<TItemType,ARRAY_LENGTH>& operator=(const IEnumerableConst<TItemType>& Other)
			{
				Size											Index=0;
				CEnumeratorConstPointer							Enumerator=Other.GetEnumeratorConst();

				while(Index<GetLength() && Enumerator->MoveNext()==true)
				{
					MArray[Index++]=Enumerator->GetCurrentConst();
				}

				return(*this);
			}

			TItemType& operator[](Size Index)
			{
				CheckIndex(Index);

				return(MArray[static_cast<typename std::array<TItemType,ARRAY_LENGTH>::size_type>(Index)]);
			}

			const TItemType& operator[](Size Index) const
			{
				CheckIndex(Index);

				return(MArray[static_cast<typename std::array<TItemType,ARRAY_LENGTH>::size_type>(Index)]);
			}

			bool operator==(const CArray<TItemType,ARRAY_LENGTH>& Other) const
			{
				if (GetLength()!=Other.GetLength())
				{
					return(false);
				}

				for(Size Index=0;Index<GetLength();Index++)
				{
					if ((*this)[Index]!=Other[Index])
					{
						return(false);
					}
				}

				return(true);
			}

			bool operator!=(const CArray<TItemType,ARRAY_LENGTH>& Other) const
			{
				if (GetLength()!=Other.GetLength())
				{
					return(true);
				}

				for(Size Index=0;Index<GetLength();Index++)
				{
					if ((*this)[Index]!=Other[Index])
					{
						return(true);
					}
				}

				return(false);
			}

		private:
			void CheckIndex(Size Index) const
			{
				if (Index>=GetLength())
				{
					throw(CValueOutOfRangeException("INDEX is OUT of RANGE !"));
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
			constexpr Size GetConstLength(void) const noexcept
			{
				return(ARRAY_LENGTH);
			}

			Size GetLength(void) const noexcept
			{
				Size											Length=static_cast<Size>(MArray.size());
				
				return(Length);
			}

			bool IsEmpty(void) const
			{
				Size											Length=static_cast<Size>(MArray.size());
				
				if (Length==0)
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}

			TItemType* GetRawData(void)
			{
				TItemType*										RawData=MArray.data();
				
				return(RawData);
			}

			const TItemType* GetRawData(void) const
			{
				const TItemType*								RawData=MArray.data();
				
				return(RawData);
			}

			TItemType* GetRawData(Size Index)
			{
				CheckIndex(Index);

				TItemType*										RawData=MArray.data()+Index;
				
				return(RawData);
			}

			const TItemType* GetRawData(Size Index) const
			{
				CheckIndex(Index);

				const TItemType*								RawData=MArray.data()+Index;
				
				return(RawData);
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
			bool FindFirst(const TComparePredicate& ComparePredicate, TItemType& Value, Size Offset=0) const
			{
				CheckOffset(Offset);

				Size											Length=GetLength();

				for(Size Index=Offset;Index<Length;Index++)
				{
					if (ComparePredicate((*this)[Index])==true)
					{
						Value=(*this)[Index];

						return(true);
					}
				}

				return(false);
			}

			template<typename TComparePredicate>
			bool FindLast(const TComparePredicate& ComparePredicate, TItemType& Value, Size Offset=END) const
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
						Value=(*this)[Index];

						return(true);
					}

					if (Index==0)
					{
						break;
					}
				}

				return(false);
			}

			template<typename TIsLessThanPredicate>
			void Sort(const TIsLessThanPredicate& IsLessThanPredicate)
			{
				std::sort(MArray.begin(),MArray.end(),IsLessThanPredicate);
			}
			
			template<typename TIsLessThanPredicate>
			void SortStable(const TIsLessThanPredicate& IsLessThanPredicate)
			{
				std::stable_sort(MArray.begin(),MArray.end(),IsLessThanPredicate);
			}

			// COLLECTION MUST be ORDERED.
			template<typename TIsLessThanPredicate>
			bool BinarySearch(const TItemType& Item, const TIsLessThanPredicate& IsLessThanPredicate) const
			{
				bool											ItemFound=std::binary_search(MArray.begin(),MArray.end(),Item,IsLessThanPredicate);

				return(ItemFound);
			}

			void Fill(const TItemType& Value)
			{
				MArray.fill(Value);
			}

		public:
			virtual CEnumeratorPointer GetEnumerator(void) override
			{
				CEnumeratorPointer								Enumerator=CEnumeratorPointer(new CArrayEnumerator(*this));

				return(Enumerator);
			}

			virtual CEnumeratorConstPointer GetEnumeratorConst(void) const override
			{
				CEnumeratorConstPointer							Enumerator=CEnumeratorConstPointer(new CArrayEnumeratorConst(*this));

				return(Enumerator);
			}

			CArrayIterator Begin(void)
			{
				return(MArray.begin());
			}

			CArrayIterator End(void)
			{
				return(MArray.end());
			}

			CArrayIteratorConst Begin(void) const
			{
				return(MArray.cbegin());
			}

			CArrayIteratorConst End(void) const
			{
				return(MArray.cend());
			}

			CArrayReverseIterator ReverseBegin(void)
			{
				return(MArray.rbegin());
			}

			CArrayReverseIterator ReverseEnd(void)
			{
				return(MArray.rend());
			}

			CArrayReverseIteratorConst ReverseBegin(void) const
			{
				return(MArray.crbegin());
			}

			CArrayReverseIteratorConst ReverseEnd(void) const
			{
				return(MArray.crend());
			}

			CArrayIterator begin(void)
			{
				return(MArray.begin());
			}

			CArrayIterator end(void)
			{
				return(MArray.end());
			}

			CArrayIteratorConst begin(void) const
			{
				return(MArray.cbegin());
			}

			CArrayIteratorConst end(void) const
			{
				return(MArray.cend());
			}

			CArrayReverseIterator rbegin(void)
			{
				return(MArray.rbegin());
			}

			CArrayReverseIterator rend(void)
			{
				return(MArray.rend());
			}

			CArrayReverseIteratorConst rbegin(void) const
			{
				return(MArray.crbegin());
			}

			CArrayReverseIteratorConst rend(void) const
			{
				return(MArray.crend());
			}

		public:
			CArray(void)
				: MArray()
			{
			}

			CArray(const TItemType* Array, Size ArrayLength)
				: MArray()
			{
				for(Size Index=0;Index<ArrayLength;Index++)
				{
					MArray[Index]=Array[Index];
				}
			}

			CArray(const CArray<TItemType,ARRAY_LENGTH>& Other)
				: MArray(Other.MArray)
			{
			}

			CArray(CArray<TItemType,ARRAY_LENGTH>&& Other)
				: MArray(FUNCTION_MOVE(Other.MArray))
			{
			}

			CArray(const std::array<TItemType,ARRAY_LENGTH>& Other)
				: MArray(Other)
			{
			}

			CArray(std::array<TItemType,ARRAY_LENGTH>&& Other)
				: MArray(FUNCTION_MOVE(Other))
			{
			}

			CArray(const IEnumerableConst<TItemType>& Other)
				: MArray()
			{
				Size											Index=0;
				CEnumeratorConstPointer							Enumerator=Other.GetEnumeratorConst();

				while(Index<GetLength() && Enumerator->MoveNext()==true)
				{
					MArray[Index++]=Enumerator->GetCurrentConst();
				}
			}

			virtual ~CArray(void) override
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------