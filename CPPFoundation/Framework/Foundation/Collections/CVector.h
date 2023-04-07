//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <vector>
#include <algorithm>
#include <memory>
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Exceptions/CValueOutOfRangeException.h>
#include <Framework/Foundation/Operators/COperatorEqualTo.h>
#include "CIterators.h"
#include "IEnumerable.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CByteBuffer;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<typename TItemType>
	class CVector final : public CObject, public IEnumerable<TItemType>
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			class CVectorEnumerator : public IEnumerator<TItemType>
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					CVector<TItemType>&							MVector;
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

							if (MPosition<MVector.GetLength())
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
							if ((MPosition+1)<MVector.GetLength())
							{
								MPosition++;

								return(true);
							}
							else
							{
								MPosition=MVector.GetLength();

								return(false);
							}
						}
					}

					virtual const TItemType& GetCurrentConst(void) const override
					{
						if (MIsBeforeFirstItem==false && MPosition<MVector.GetLength())
						{
							return(MVector[MPosition]);
						}
						else
						{
							throw(CValueOutOfRangeException("ENUMERATOR is OUT of RANGE !"));
						}
					}

					virtual TItemType& GetCurrent(void) override
					{
						if (MIsBeforeFirstItem==false && MPosition<MVector.GetLength())
						{
							return(MVector[MPosition]);
						}
						else
						{
							throw(CValueOutOfRangeException("ENUMERATOR is OUT of RANGE !"));
						}
					}

				public:
					CVectorEnumerator(CVector<TItemType>& Vector)
						: MVector(Vector), MIsBeforeFirstItem(true), MPosition(0)
					{
					}

					virtual ~CVectorEnumerator(void) override
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
			class CVectorEnumeratorConst : public IEnumeratorConst<TItemType>
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					const CVector<TItemType>&					MVector;
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

							if (MPosition<MVector.GetLength())
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
							if ((MPosition+1)<MVector.GetLength())
							{
								MPosition++;

								return(true);
							}
							else
							{
								MPosition=MVector.GetLength();

								return(false);
							}
						}
					}

					virtual const TItemType& GetCurrentConst(void) const override
					{
						if (MIsBeforeFirstItem==false && MPosition<MVector.GetLength())
						{
							return(MVector[MPosition]);
						}
						else
						{
							throw(CValueOutOfRangeException("ENUMERATOR is OUT of RANGE !"));
						}
					}

				public:
					CVectorEnumeratorConst(const CVector<TItemType>& Vector)
						: MVector(Vector), MIsBeforeFirstItem(true), MPosition(0)
					{
					}

					virtual ~CVectorEnumeratorConst(void) override
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		static_assert(std::is_same<TItemType,bool>::value==false,"TYPE is NOT SUPPORTED for TEMPLATE [CVector<bool>] !");

		friend CByteBuffer;

		public:
			static const Size									END=static_cast<Size>(-1);

		public:
			using												CEnumeratorPointer=CSharedPointer<IEnumerator<TItemType>>;
			using												CEnumeratorConstPointer=CSharedPointer<IEnumeratorConst<TItemType>>;
			using												CVectorIterator=typename std::vector<TItemType>::iterator;
			using												CVectorIteratorConst=typename std::vector<TItemType>::const_iterator;
			using												CVectorReverseIterator=typename std::vector<TItemType>::reverse_iterator;
			using												CVectorReverseIteratorConst=typename std::vector<TItemType>::const_reverse_iterator;

		private:
			std::vector<TItemType>								MVector;

		public:
			CVector<TItemType>& operator=(const CVector<TItemType>& Other)
			{
				MVector=Other.MVector;

				return(*this);
			}

			CVector<TItemType>& operator=(CVector<TItemType>&& Other) noexcept
			{
				MVector=FUNCTION_MOVE(Other.MVector);
				Other.Clear();

				return(*this);
			}

			CVector<TItemType>& operator=(const std::vector<TItemType>& Other)
			{
				MVector=Other;

				return(*this);
			}

			CVector<TItemType>& operator=(std::vector<TItemType>&& Other)
			{
				MVector=FUNCTION_MOVE(Other);
				Other.clear();

				return(*this);
			}

			CVector<TItemType>& operator=(const IEnumerableConst<TItemType>& Other)
			{
				Clear();

				CEnumeratorConstPointer							Enumerator=Other.GetEnumeratorConst();

				while(Enumerator->MoveNext()==true)
				{
					MVector.push_back(Enumerator->GetCurrentConst());
				}

				return(*this);
			}

			CVector<TItemType>& operator=(std::initializer_list<TItemType> Other)
			{
				MVector=Other;

				return(*this);
			}

			TItemType& operator[](Size Index)
			{
				CheckIndex(Index,false);

				return(MVector[static_cast<typename std::vector<TItemType>::size_type>(Index)]);
			}

			const TItemType& operator[](Size Index) const
			{
				CheckIndex(Index,false);

				return(MVector[static_cast<typename std::vector<TItemType>::size_type>(Index)]);
			}

			bool operator==(const CVector<TItemType>& Other) const
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

			bool operator!=(const CVector<TItemType>& Other) const
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
				Size											Length=static_cast<Size>(MVector.size());
				
				return(Length);
			}

			TItemType GetItemByValue(Size Index) const
			{
				CheckIndex(Index,false);

				return(MVector[static_cast<typename std::vector<TItemType>::size_type>(Index)]);
			}

			bool IsEmpty(void) const noexcept
			{
				Size											Length=static_cast<Size>(MVector.size());
				
				if (Length==0)
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}

			void Add(const TItemType& Item)
			{
				MVector.push_back(Item);
			}

			void Add(TItemType&& Item)
			{
				MVector.push_back(FUNCTION_MOVE(Item));
			}

			void Insert(const TItemType& Item, Size Offset)
			{
				CheckIndex(Offset,true);

				MVector.insert(MVector.begin()+static_cast<typename std::vector<TItemType>::difference_type>(Offset),Item);
			}

			void Insert(TItemType&& Item, Size Offset)
			{
				CheckIndex(Offset,true);

				MVector.insert(MVector.begin()+static_cast<typename std::vector<TItemType>::difference_type>(Offset),FUNCTION_MOVE(Item));
			}

			void Erase(Size Offset)
			{
				// INDEX MUST NOT POINT BEHIND the END of VECTOR because METHOD erase() with a SINGLE PARAMETER forbids it.
				CheckIndex(Offset,false);

				MVector.erase(MVector.begin()+static_cast<typename std::vector<TItemType>::difference_type>(Offset));
			}

			void Erase(Size Offset, Size Length)
			{
				// INDEX CAN POINT BEHIND the END of VECTOR if LENGTH is 0 because METHOD erase() with a DOUBLE PARAMETERS allows it.
				CheckIndex(Offset+Length,true);

				MVector.erase(MVector.begin()+static_cast<typename std::vector<TItemType>::difference_type>(Offset),MVector.begin()+static_cast<typename std::vector<TItemType>::difference_type>(Offset)+static_cast<typename std::vector<TItemType>::difference_type>(Length));
			}

			void Clear(void) noexcept
			{
				MVector.clear();
			}

			void Resize(Size Length)
			{
				MVector.resize(static_cast<typename std::vector<TItemType>::size_type>(Length));
			}

			void Resize(Size Length, const TItemType& FillValue)
			{
				MVector.resize(static_cast<typename std::vector<TItemType>::size_type>(Length),FillValue);
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
				std::sort(MVector.begin(),MVector.end(),IsLessThanPredicate);
			}
			
			template<typename TIsLessThanPredicate>
			void SortStable(const TIsLessThanPredicate& IsLessThanPredicate)
			{
				std::stable_sort(MVector.begin(),MVector.end(),IsLessThanPredicate);
			}

			// COLLECTION MUST be ORDERED.
			template<typename TIsLessThanPredicate>
			bool BinarySearch(const TItemType& Item, const TIsLessThanPredicate& IsLessThanPredicate) const
			{
				bool											ItemFound=std::binary_search(MVector.begin(),MVector.end(),Item,IsLessThanPredicate);

				return(ItemFound);
			}

			Size GetCapacity(void) const
			{
				Size											Capacity=static_cast<Size>(MVector.capacity());

				return(Capacity);
			}

			void ReserveCapacity(Size Capacity)
			{
				MVector.reserve(static_cast<typename std::vector<TItemType>::size_type>(Capacity));
			}

			void Shrink(void)
			{
				MVector.shrink_to_fit();
			}

			virtual CEnumeratorPointer GetEnumerator(void) override
			{
				CEnumeratorPointer								Enumerator=CEnumeratorPointer(new CVectorEnumerator(*this));

				return(Enumerator);
			}

			virtual CEnumeratorConstPointer GetEnumeratorConst(void) const override
			{
				CEnumeratorConstPointer							Enumerator=CEnumeratorConstPointer(new CVectorEnumeratorConst(*this));

				return(Enumerator);
			}

			CVectorIterator Begin(void)
			{
				return(MVector.begin());
			}

			CVectorIterator End(void)
			{
				return(MVector.end());
			}

			CVectorIteratorConst Begin(void) const
			{
				return(MVector.cbegin());
			}

			CVectorIteratorConst End(void) const
			{
				return(MVector.cend());
			}

			CVectorReverseIterator ReverseBegin(void)
			{
				return(MVector.rbegin());
			}

			CVectorReverseIterator ReverseEnd(void)
			{
				return(MVector.rend());
			}

			CVectorReverseIteratorConst ReverseBegin(void) const
			{
				return(MVector.crbegin());
			}

			CVectorReverseIteratorConst ReverseEnd(void) const
			{
				return(MVector.crend());
			}

			CVectorIterator begin(void)
			{
				return(MVector.begin());
			}

			CVectorIterator end(void)
			{
				return(MVector.end());
			}

			CVectorIteratorConst begin(void) const
			{
				return(MVector.cbegin());
			}

			CVectorIteratorConst end(void) const
			{
				return(MVector.cend());
			}

			CVectorReverseIterator rbegin(void)
			{
				return(MVector.rbegin());
			}

			CVectorReverseIterator rend(void)
			{
				return(MVector.rend());
			}

			CVectorReverseIteratorConst rbegin(void) const
			{
				return(MVector.crbegin());
			}

			CVectorReverseIteratorConst rend(void) const
			{
				return(MVector.crend());
			}

		public:
			CVector(void)
				: MVector()
			{
			}

			explicit CVector(Size BufferSize)
				: MVector()
			{
				Resize(BufferSize);
			}

			CVector(const CVector<TItemType>& Other)
				: MVector(Other.MVector)
			{
			}

			CVector(CVector<TItemType>&& Other) noexcept
				: MVector(FUNCTION_MOVE(Other.MVector))
			{
				Other.Clear();
			}

			CVector(const std::vector<TItemType>& Other)
				: MVector(Other)
			{
			}

			CVector(std::vector<TItemType>&& Other)
				: MVector(FUNCTION_MOVE(Other))
			{
				Other.clear();
			}

			CVector(CVector<TItemType>::CVectorIteratorConst From, CVector<TItemType>::CVectorIteratorConst To)
				: MVector(From,To)
			{
			}

			CVector(const TItemType* From, const TItemType* To)
				: MVector()
			{
				while(From!=To)
				{
					Add(*From++);
				}
			}

			CVector(const IEnumerableConst<TItemType>& Other)
				: MVector()
			{
				CEnumeratorConstPointer							Enumerator=Other.GetEnumeratorConst();

				while(Enumerator->MoveNext()==true)
				{
					MVector.push_back(Enumerator->GetCurrentConst());
				}
			}

			CVector(std::initializer_list<TItemType> Other)
				: MVector(Other)
			{
			}

			virtual ~CVector(void) override
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------