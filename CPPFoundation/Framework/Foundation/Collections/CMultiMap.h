//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <map>
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Foundation/Exceptions/CValueOutOfRangeException.h>
#include <Framework/Foundation/Exceptions/CInvalidValueException.h>
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Types/TypeTraits.h>
#include "CIterators.h"
#include "CPair.h"
#include "CVector.h"
#include "IIsBeforeComparator.h"
#include "IEnumerable.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	template<typename TKeyType, typename TValueType, typename TComparator=CIsBeforeComparatorLess<TKeyType>>
	class CMultiMap final : public CObject, public IEnumerable<CPair<const TKeyType,TValueType>>
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			class CMultiMapEnumerator final : public IEnumerator<CPair<const TKeyType,TValueType>>
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					using										CMultiMapValueType=CPair<const TKeyType,TValueType>;
					using										CMultiMapType=CMultiMap<TKeyType,TValueType,TComparator>;
					using										CMultiMapTypeIterator=typename CMultiMapType::CMultiMapIterator;

				private:
					CMultiMapType&								MMultiMap;
					bool										MIsBeforeFirstItem;
					CMultiMapTypeIterator						MIterator;

				public:
					virtual void Reset(void) override
					{
						MIsBeforeFirstItem=true;
						MIterator=MMultiMap.Begin();
					}

					virtual bool MoveNext(void) override
					{
						if (MIsBeforeFirstItem==true)
						{
							MIsBeforeFirstItem=false;

							if (MIterator!=MMultiMap.End())
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
							if (MIterator!=MMultiMap.End())
							{
								if (++MIterator!=MMultiMap.End())
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

					virtual const CMultiMapValueType& GetCurrentConst(void) const override
					{
						if (MIsBeforeFirstItem==false && MIterator!=MMultiMap.End())
						{
							return(*MIterator);
						}
						else
						{
							throw(CValueOutOfRangeException("ENUMERATOR is OUT of RANGE !"));
						}
					}

					virtual CMultiMapValueType& GetCurrent(void) override
					{
						if (MIsBeforeFirstItem==false && MIterator!=MMultiMap.End())
						{
							return(*MIterator);
						}
						else
						{
							throw(CValueOutOfRangeException("ENUMERATOR is OUT of RANGE !"));
						}
					}

				public:
					CMultiMapEnumerator(CMultiMapType& Map)
						: MMultiMap(Map), MIsBeforeFirstItem(true), MIterator(Map.Begin())
					{
						Reset();
					}

					virtual ~CMultiMapEnumerator(void) override
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
			class CMultiMapEnumeratorConst final : public IEnumeratorConst<CPair<const TKeyType,TValueType>>
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					using										CMultiMapValueType=CPair<const TKeyType,TValueType>;
					using										CMultiMapType=CMultiMap<TKeyType,TValueType,TComparator>;
					using										CMultiMapTypeIteratorConst=typename CMultiMapType::CMultiMapIteratorConst;

				private:
					const CMultiMapType&						MMultiMap;
					bool										MIsBeforeFirstItem;
					CMultiMapTypeIteratorConst					MIterator;

				public:
					virtual void Reset(void) override
					{
						MIsBeforeFirstItem=true;
						MIterator=MMultiMap.Begin();
					}

					virtual bool MoveNext(void) override
					{
						if (MIsBeforeFirstItem==true)
						{
							MIsBeforeFirstItem=false;

							if (MIterator!=MMultiMap.End())
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
							if (MIterator!=MMultiMap.End())
							{
								if (++MIterator!=MMultiMap.End())
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

					virtual const CMultiMapValueType& GetCurrentConst(void) const override
					{
						if (MIsBeforeFirstItem==false && MIterator!=MMultiMap.End())
						{
							return(*MIterator);
						}
						else
						{
							throw(CValueOutOfRangeException("ENUMERATOR is OUT of RANGE !"));
						}
					}

				public:
					CMultiMapEnumeratorConst(const CMultiMapType& Map)
						: MMultiMap(Map), MIsBeforeFirstItem(true), MIterator(Map.Begin())
					{
						Reset();
					}

					virtual ~CMultiMapEnumeratorConst(void) override
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public:
			class CMultiMapIterator final
			{
//----------------------------------------------------------------------------------------------------------------------
				friend CMultiMap<TKeyType,TValueType,TComparator>;

				private:
					using										CMultiMapValueType=CPair<const TKeyType,TValueType>;
					using										CMultiMapTypeIterator=typename std::multimap<TKeyType,CMultiMapValueType,TComparator>::iterator;

				public:
					CMultiMapTypeIterator						MIterator;

				public:
					bool operator==(const CMultiMapIterator& Right) const
					{
						if (MIterator==Right.MIterator)
						{
							return(true);
						}
						else
						{
							return(false);
						}
					}
	
					bool operator!=(const CMultiMapIterator& Right) const
					{
						if (MIterator!=Right.MIterator)
						{
							return(true);
						}
						else
						{
							return(false);
						}
					}

					CMultiMapIterator& operator++(void)
					{
						++MIterator;

						return(*this);
					}

					CMultiMapIterator operator++(int32)
					{
						CMultiMapIterator						Value(*this);

						++MIterator;

						return(Value);
					}

					CMultiMapIterator& operator--(void)
					{
						--MIterator;

						return(*this);
					}

					CMultiMapIterator operator--(int32)
					{
						CMultiMapIterator						Value(*this);

						--MIterator;

						return(Value);
					}

					CMultiMapValueType& operator*(void)
					{
						return(MIterator->second);
					}

					const CMultiMapValueType& operator*(void) const
					{
						return(MIterator->second);
					}

					CMultiMapValueType* operator->(void)
					{
						return(&MIterator->second);
					}

					const CMultiMapValueType* operator->(void) const
					{
						return(&MIterator->second);
					}

				public:
					CMultiMapIterator(const CMultiMapTypeIterator& Iterator)
						: MIterator(Iterator)
					{
					}

					~CMultiMapIterator(void)
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public:
			class CMultiMapIteratorConst final
			{
//----------------------------------------------------------------------------------------------------------------------
				friend CMultiMap<TKeyType,TValueType,TComparator>;

				private:
					using										CMultiMapValueType=CPair<const TKeyType,TValueType>;
					using										CMultiMapTypeIterator=typename std::multimap<TKeyType,CMultiMapValueType,TComparator>::const_iterator;

				private:
					CMultiMapTypeIterator						MIterator;

				public:
					bool operator==(const CMultiMapIteratorConst& Right) const
					{
						if (MIterator==Right.MIterator)
						{
							return(true);
						}
						else
						{
							return(false);
						}
					}
	
					bool operator!=(const CMultiMapIteratorConst& Right) const
					{
						if (MIterator!=Right.MIterator)
						{
							return(true);
						}
						else
						{
							return(false);
						}
					}

					CMultiMapIteratorConst& operator++(void)
					{
						++MIterator;

						return(*this);
					}

					CMultiMapIteratorConst operator++(int32)
					{
						CMultiMapIteratorConst					Value(*this);

						++MIterator;

						return(Value);
					}

					CMultiMapIteratorConst& operator--(void)
					{
						--MIterator;

						return(*this);
					}

					CMultiMapIteratorConst operator--(int32)
					{
						CMultiMapIteratorConst					Value(*this);

						--MIterator;

						return(Value);
					}

					const CMultiMapValueType& operator*(void) const
					{
						return(MIterator->second);
					}

					const CMultiMapValueType* operator->(void) const
					{
						return(&MIterator->second);
					}

				public:
					CMultiMapIteratorConst(const CMultiMapTypeIterator& Iterator)
						: MIterator(Iterator)
					{
					}

					~CMultiMapIteratorConst(void)
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public:
			class CMultiMapReverseIterator final
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					using										CMultiMapValueType=CPair<const TKeyType,TValueType>;
					using										CMultiMapTypeReverseIterator=typename std::multimap<TKeyType,CMultiMapValueType,TComparator>::reverse_iterator;

				private:
					CMultiMapTypeReverseIterator				MIterator;

				public:
					bool operator==(const CMultiMapReverseIterator& Right) const
					{
						if (MIterator==Right.MIterator)
						{
							return(true);
						}
						else
						{
							return(false);
						}
					}
	
					bool operator!=(const CMultiMapReverseIterator& Right) const
					{
						if (MIterator!=Right.MIterator)
						{
							return(true);
						}
						else
						{
							return(false);
						}
					}

					CMultiMapReverseIterator& operator++(void)
					{
						++MIterator;

						return(*this);
					}

					CMultiMapReverseIterator operator++(int32)
					{
						CMultiMapReverseIterator				Value(*this);

						++MIterator;

						return(Value);
					}

					CMultiMapReverseIterator& operator--(void)
					{
						--MIterator;

						return(*this);
					}

					CMultiMapReverseIterator operator--(int32)
					{
						CMultiMapReverseIterator				Value(*this);

						--MIterator;

						return(Value);
					}

					CMultiMapValueType& operator*(void)
					{
						return(MIterator->second);
					}

					const CMultiMapValueType& operator*(void) const
					{
						return(MIterator->second);
					}

					CMultiMapValueType* operator->(void)
					{
						return(&MIterator->second);
					}

					const CMultiMapValueType* operator->(void) const
					{
						return(&MIterator->second);
					}

				public:
					CMultiMapReverseIterator(const CMultiMapTypeReverseIterator& Iterator)
						: MIterator(Iterator)
					{
					}

					~CMultiMapReverseIterator(void)
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public:
			class CMultiMapReverseIteratorConst final
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					using										CMultiMapValueType=CPair<const TKeyType,TValueType>;
					using										CMultiMapTypeReverseIterator=typename std::multimap<TKeyType,CMultiMapValueType,TComparator>::const_reverse_iterator;

				private:
					CMultiMapTypeReverseIterator				MIterator;

				public:
					bool operator==(const CMultiMapReverseIteratorConst& Right) const
					{
						if (MIterator==Right.MIterator)
						{
							return(true);
						}
						else
						{
							return(false);
						}
					}
	
					bool operator!=(const CMultiMapReverseIteratorConst& Right) const
					{
						if (MIterator!=Right.MIterator)
						{
							return(true);
						}
						else
						{
							return(false);
						}
					}

					CMultiMapReverseIteratorConst& operator++(void)
					{
						++MIterator;

						return(*this);
					}

					CMultiMapReverseIteratorConst operator++(int32)
					{
						CMultiMapReverseIteratorConst			Value(*this);

						++MIterator;

						return(Value);
					}

					CMultiMapReverseIteratorConst& operator--(void)
					{
						--MIterator;

						return(*this);
					}

					CMultiMapReverseIteratorConst operator--(int32)
					{
						CMultiMapReverseIteratorConst			Value(*this);

						--MIterator;

						return(Value);
					}

					const CMultiMapValueType& operator*(void) const
					{
						return(MIterator->second);
					}

					const CMultiMapValueType* operator->(void) const
					{
						return(&MIterator->second);
					}

				public:
					CMultiMapReverseIteratorConst(const CMultiMapTypeReverseIterator& Iterator)
						: MIterator(Iterator)
					{
					}

					~CMultiMapReverseIteratorConst(void)
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public:
			class CMultiMapValueIterator final
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					using										CValueType=TValueType;
					using										CMultiMapValueType=CPair<const TKeyType,TValueType>;
					using										CMultiMapTypeIterator=typename std::multimap<TKeyType,CMultiMapValueType,TComparator>::iterator;

				private:
					CMultiMapTypeIterator						MIterator;

				public:
					bool operator==(const CMultiMapValueIterator& Right) const
					{
						if (MIterator==Right.MIterator)
						{
							return(true);
						}
						else
						{
							return(false);
						}
					}
	
					bool operator!=(const CMultiMapValueIterator& Right) const
					{
						if (MIterator!=Right.MIterator)
						{
							return(true);
						}
						else
						{
							return(false);
						}
					}

					CMultiMapValueIterator& operator++(void)
					{
						++MIterator;

						return(*this);
					}

					CMultiMapValueIterator operator++(int32)
					{
						CMultiMapValueIterator					Value(*this);

						++MIterator;

						return(Value);
					}

					CMultiMapValueIterator& operator--(void)
					{
						--MIterator;

						return(*this);
					}

					CMultiMapValueIterator operator--(int32)
					{
						CMultiMapValueIterator					Value(*this);

						--MIterator;

						return(Value);
					}

					CValueType& operator*(void)
					{
						return(MIterator->second.GetSecond());
					}

					const CValueType& operator*(void) const
					{
						return(MIterator->second.GetSecond());
					}

					CValueType* operator->(void)
					{
						return(&MIterator->second.GetSecond());
					}

					const CValueType* operator->(void) const
					{
						return(&MIterator->second.GetSecond());
					}

				public:
					CMultiMapValueIterator(const CMultiMapTypeIterator& Iterator)
						: MIterator(Iterator)
					{
					}

					~CMultiMapValueIterator(void)
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public:
			class CMultiMapValueIteratorConst final
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					using										CValueType=TValueType;
					using										CMultiMapValueType=CPair<const TKeyType,TValueType>;
					using										CMultiMapTypeIterator=typename std::multimap<TKeyType,CMultiMapValueType,TComparator>::const_iterator;

				private:
					CMultiMapTypeIterator						MIterator;

				public:
					bool operator==(const CMultiMapValueIteratorConst& Right) const
					{
						if (MIterator==Right.MIterator)
						{
							return(true);
						}
						else
						{
							return(false);
						}
					}
	
					bool operator!=(const CMultiMapValueIteratorConst& Right) const
					{
						if (MIterator!=Right.MIterator)
						{
							return(true);
						}
						else
						{
							return(false);
						}
					}

					CMultiMapValueIteratorConst& operator++(void)
					{
						++MIterator;

						return(*this);
					}

					CMultiMapValueIteratorConst operator++(int32)
					{
						CMultiMapValueIteratorConst				Value(*this);

						++MIterator;

						return(Value);
					}

					CMultiMapValueIteratorConst& operator--(void)
					{
						--MIterator;

						return(*this);
					}

					CMultiMapValueIteratorConst operator--(int32)
					{
						CMultiMapValueIteratorConst				Value(*this);

						--MIterator;

						return(Value);
					}

					const CValueType& operator*(void) const
					{
						return(MIterator->second.GetSecond());
					}

					const CValueType* operator->(void) const
					{
						return(&MIterator->second.GetSecond());
					}

				public:
					CMultiMapValueIteratorConst(const CMultiMapTypeIterator& Iterator)
						: MIterator(Iterator)
					{
					}

					~CMultiMapValueIteratorConst(void)
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public:
			class CMultiMapValueReverseIterator final
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					using										CValueType=TValueType;
					using										CMultiMapValueType=CPair<const TKeyType,TValueType>;
					using										CMultiMapTypeReverseIterator=typename std::multimap<TKeyType,CMultiMapValueType,TComparator>::reverse_iterator;

				private:
					CMultiMapTypeReverseIterator				MIterator;

				public:
					bool operator==(const CMultiMapValueReverseIterator& Right) const
					{
						if (MIterator==Right.MIterator)
						{
							return(true);
						}
						else
						{
							return(false);
						}
					}
	
					bool operator!=(const CMultiMapValueReverseIterator& Right) const
					{
						if (MIterator!=Right.MIterator)
						{
							return(true);
						}
						else
						{
							return(false);
						}
					}

					CMultiMapValueReverseIterator& operator++(void)
					{
						++MIterator;

						return(*this);
					}

					CMultiMapValueReverseIterator operator++(int32)
					{
						CMultiMapValueReverseIterator			Value(*this);

						++MIterator;

						return(Value);
					}

					CMultiMapValueReverseIterator& operator--(void)
					{
						--MIterator;

						return(*this);
					}

					CMultiMapValueReverseIterator operator--(int32)
					{
						CMultiMapValueReverseIterator			Value(*this);

						--MIterator;

						return(Value);
					}

					CValueType& operator*(void)
					{
						return(MIterator->second.GetSecond());
					}

					const CValueType& operator*(void) const
					{
						return(MIterator->second.GetSecond());
					}

					CValueType* operator->(void)
					{
						return(&MIterator->second.GetSecond());
					}

					const CValueType* operator->(void) const
					{
						return(&MIterator->second.GetSecond());
					}

				public:
					CMultiMapValueReverseIterator(const CMultiMapTypeReverseIterator& Iterator)
						: MIterator(Iterator)
					{
					}

					~CMultiMapValueReverseIterator(void)
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public:
			class CMultiMapValueReverseIteratorConst final
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					using										CValueType=TValueType;
					using										CMultiMapValueType=CPair<const TKeyType,TValueType>;
					using										CMultiMapTypeReverseIterator=typename std::multimap<TKeyType,CMultiMapValueType,TComparator>::const_reverse_iterator;

				private:
					CMultiMapTypeReverseIterator				MIterator;

				public:
					bool operator==(const CMultiMapValueReverseIteratorConst& Right) const
					{
						if (MIterator==Right.MIterator)
						{
							return(true);
						}
						else
						{
							return(false);
						}
					}
	
					bool operator!=(const CMultiMapValueReverseIteratorConst& Right) const
					{
						if (MIterator!=Right.MIterator)
						{
							return(true);
						}
						else
						{
							return(false);
						}
					}

					CMultiMapValueReverseIteratorConst& operator++(void)
					{
						++MIterator;

						return(*this);
					}

					CMultiMapValueReverseIteratorConst operator++(int32)
					{
						CMultiMapValueReverseIteratorConst		Value(*this);

						++MIterator;

						return(Value);
					}

					CMultiMapValueReverseIteratorConst& operator--(void)
					{
						--MIterator;

						return(*this);
					}

					CMultiMapValueReverseIteratorConst operator--(int32)
					{
						CMultiMapValueReverseIteratorConst		Value(*this);

						--MIterator;

						return(Value);
					}

					const CValueType& operator*(void) const
					{
						return(MIterator->second.GetSecond());
					}

					const CValueType* operator->(void) const
					{
						return(&MIterator->second.GetSecond());
					}

				public:
					CMultiMapValueReverseIteratorConst(const CMultiMapTypeReverseIterator& Iterator)
						: MIterator(Iterator)
					{
					}

					~CMultiMapValueReverseIteratorConst(void)
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		static_assert(STypeTraitIsBaseOf<IIsBeforeComparator<TKeyType>,TComparator>::Value()==true,"KEY TYPE MUST implement INTERFACE [IIsBeforeComparator<TKeyType>] !");

		private:
			using												CMultiMapValueType=CPair<const TKeyType,TValueType>;
			using												CMultiMapType=std::multimap<TKeyType,CMultiMapValueType,TComparator>;
			using												CMultiMapTypeIterator=typename std::multimap<TKeyType,CMultiMapValueType,TComparator>::iterator;
			using												CMultiMapTypeIteratorConst=typename std::multimap<TKeyType,CMultiMapValueType,TComparator>::const_iterator;
			using												CMultiMapTypeReverseIterator=typename std::multimap<TKeyType,CMultiMapValueType,TComparator>::reverse_iterator;

		public:
			using												CEnumeratorPointer=CSharedPointer<IEnumerator<CMultiMapValueType>>;
			using												CEnumeratorConstPointer=CSharedPointer<IEnumeratorConst<CMultiMapValueType>>;
			using												CKeyCollection=CSharedPointer<CVector<TKeyType>>;
			using												CValueCollection=CSharedPointer<CVector<TValueType>>;
			using												CKeyValuePair=CMultiMapValueType;

		private:
			CMultiMapType										MMultiMap;

		public:
			CMultiMap<TKeyType,TValueType>& operator=(const CMultiMap<TKeyType,TValueType>& Other)
			{
				MMultiMap=Other.MMultiMap;

				return(*this);
			}

			CMultiMap<TKeyType,TValueType>& operator=(CMultiMap<TKeyType,TValueType>&& Other) noexcept
			{
				MMultiMap=FUNCTION_MOVE(Other.MMultiMap);
				Other.Clear();

				return(*this);
			}

		public:
			void Add(const TKeyType& Key, const TValueType& Value)
			{
				MMultiMap.insert(std::pair<const TKeyType,CMultiMapValueType>(Key,CMultiMapValueType(Key,FUNCTION_FORWARD<const TValueType>(Value))));
			}

			void Add(const TKeyType& Key, TValueType&& Value)
			{
				MMultiMap.insert(std::pair<const TKeyType,CMultiMapValueType>(Key,CMultiMapValueType(Key,FUNCTION_FORWARD<TValueType>(Value))));
			}

			void Add(const CPair<TKeyType,TValueType>& Pair)
			{
				MMultiMap.insert(std::pair<TKeyType,CMultiMapValueType>(Pair.GetFirst(),CMultiMapValueType(Pair.GetFirst(),FUNCTION_FORWARD<const TValueType>(Pair.GetSecond()))));
			}

			void Add(CPair<TKeyType,TValueType>&& Pair)
			{
				MMultiMap.insert(std::pair<TKeyType,CMultiMapValueType>(Pair.GetFirst(),CMultiMapValueType(Pair.GetFirst(),FUNCTION_FORWARD<const TValueType>(Pair.GetSecond()))));
			}

			void Insert(const TKeyType& Key, const TValueType& Value)
			{
				MMultiMap.insert(std::pair<TKeyType,CMultiMapValueType>(Key,CMultiMapValueType(Key,FUNCTION_FORWARD<const TValueType>(Value))));
			}

			void Insert(const TKeyType& Key, TValueType&& Value)
			{
				MMultiMap.insert(std::pair<TKeyType,CMultiMapValueType>(Key,CMultiMapValueType(Key,FUNCTION_FORWARD<const TValueType>(Value))));
			}

			void Insert(const CPair<TKeyType,TValueType>& Pair)
			{
				MMultiMap.insert(std::pair<TKeyType,CMultiMapValueType>(Pair.GetFirst(),CMultiMapValueType(Pair.GetFirst(),FUNCTION_FORWARD<const TValueType>(Pair.GetSecond()))));
			}

			void Insert(CPair<TKeyType,TValueType>&& Pair)
			{
				MMultiMap.insert(std::pair<TKeyType,CMultiMapValueType>(Pair.GetFirst(),CMultiMapValueType(Pair.GetFirst(),FUNCTION_FORWARD<const TValueType>(Pair.GetSecond()))));
			}

			Size Erase(const TKeyType& Key)
			{
				Size											NumberOfRemovedItems=static_cast<Size>(MMultiMap.erase(Key));

				return(NumberOfRemovedItems);
			}

			void Erase(CMultiMapIteratorConst Iterator)
			{
				MMultiMap.erase(Iterator.MIterator);
			}

			void Erase(CMultiMapIterator Iterator)
			{
				MMultiMap.erase(Iterator.MIterator);
			}

			void Clear(void) noexcept
			{
				MMultiMap.clear();
			}

		public:
			Size GetLength(void) const noexcept
			{
				Size											Length=static_cast<Size>(MMultiMap.size());
				
				return(Length);
			}

			bool IsEmpty(void) const noexcept
			{
				Size											Length=static_cast<Size>(MMultiMap.size());

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
				if (MMultiMap.find(Key)!=MMultiMap.end())
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}

			Size Count(const TKeyType& Key) const
			{
				Size											NumberOfItems=static_cast<Size>(MMultiMap.count(Key));

				return(NumberOfItems);
			}

			CKeyCollection GetKeys(void) const
			{
				CKeyCollection									VectorPointer(new CVector<TKeyType>());
				const IEnumerableConst<CMultiMapValueType>&		Enumerable=*this;
				CSharedPointer<IEnumeratorConst<CMultiMapValueType>>	Enumerator=Enumerable.GetEnumeratorConst();

				while(Enumerator->MoveNext()==true)
				{
					VectorPointer->Add(Enumerator->GetCurrentConst().GetFirst());
				}

				return(VectorPointer);
			}

			CValueCollection GetValues(void) const
			{
				CValueCollection								VectorPointer(new CVector<TValueType>());
				const IEnumerableConst<CMultiMapValueType>&		Enumerable=*this;
				CSharedPointer<IEnumeratorConst<CMultiMapValueType>>	Enumerator=Enumerable.GetEnumeratorConst();

				while(Enumerator->MoveNext()==true)
				{
					VectorPointer->Add(Enumerator->GetCurrentConst().GetSecond());
				}

				return(VectorPointer);
			}

			virtual CEnumeratorPointer GetEnumerator(void) override
			{
				CEnumeratorPointer								Enumerator=CEnumeratorPointer(new CMultiMapEnumerator(*this));

				return(Enumerator);
			}

			virtual CEnumeratorConstPointer GetEnumeratorConst(void) const override
			{
				CEnumeratorConstPointer							Enumerator=CEnumeratorConstPointer(new CMultiMapEnumeratorConst(*this));

				return(Enumerator);
			}

			CMultiMapIterator Find(const TKeyType& Key)
			{
				return(CMultiMapIterator(MMultiMap.find(Key)));
			}

			CMultiMapIteratorConst Find(const TKeyType& Key) const
			{
				return(CMultiMapIteratorConst(MMultiMap.find(Key)));
			}

			CMultiMapIterator LowerBound(const TKeyType& Key)
			{
				CMultiMapTypeIterator							Iterator=MMultiMap.lower_bound(Key);

				return(CMultiMapIterator(Iterator));
			}

			CMultiMapIteratorConst LowerBound(const TKeyType& Key) const
			{
				CMultiMapTypeIteratorConst						Iterator=MMultiMap.lower_bound(Key);

				return(CMultiMapIteratorConst(Iterator));
			}

			CMultiMapIterator UpperBound(const TKeyType& Key)
			{
				CMultiMapTypeIterator							Iterator=MMultiMap.upper_bound(Key);

				return(CMultiMapIterator(Iterator));
			}

			CMultiMapIteratorConst UpperBound(const TKeyType& Key) const
			{
				CMultiMapTypeIteratorConst						Iterator=MMultiMap.upper_bound(Key);

				return(CMultiMapIteratorConst(Iterator));
			}

			CPair<CMultiMapIterator,CMultiMapIterator> Range(const TKeyType& Key)
			{
				std::pair<CMultiMapTypeIterator,CMultiMapTypeIterator>	Pair=MMultiMap.equal_range(Key);

				return(CPair<CMultiMapIterator,CMultiMapIterator>(Pair.first,Pair.second));
			}

			CPair<CMultiMapIteratorConst,CMultiMapIteratorConst> Range(const TKeyType& Key) const
			{
				std::pair<CMultiMapTypeIteratorConst,CMultiMapTypeIteratorConst>	Pair=MMultiMap.equal_range(Key);

				return(CPair<CMultiMapIteratorConst,CMultiMapIteratorConst>(Pair.first,Pair.second));
			}

			CMultiMapIterator Begin(void)
			{
				return(CMultiMapIterator(MMultiMap.begin()));
			}

			CMultiMapIterator End(void)
			{
				return(CMultiMapIterator(MMultiMap.end()));
			}

			CMultiMapIteratorConst ConstBegin(void) const
			{
				return(CMultiMapIteratorConst(MMultiMap.cbegin()));
			}

			CMultiMapIteratorConst ConstEnd(void) const
			{
				return(CMultiMapIteratorConst(MMultiMap.cend()));
			}

			CMultiMapIteratorConst Begin(void) const
			{
				return(CMultiMapIteratorConst(MMultiMap.cbegin()));
			}

			CMultiMapIteratorConst End(void) const
			{
				return(CMultiMapIteratorConst(MMultiMap.cend()));
			}

			CMultiMapReverseIterator ReverseBegin(void)
			{
				return(CMultiMapReverseIterator(MMultiMap.rbegin()));
			}

			CMultiMapReverseIterator ReverseEnd(void)
			{
				return(CMultiMapReverseIterator(MMultiMap.rend()));
			}

			CMultiMapReverseIteratorConst ConstReverseBegin(void) const
			{
				return(CMultiMapReverseIteratorConst(MMultiMap.crbegin()));
			}

			CMultiMapReverseIteratorConst ConstReverseEnd(void) const
			{
				return(CMultiMapReverseIteratorConst(MMultiMap.crend()));
			}

			CMultiMapReverseIteratorConst ReverseBegin(void) const
			{
				return(CMultiMapReverseIteratorConst(MMultiMap.crbegin()));
			}

			CMultiMapReverseIteratorConst ReverseEnd(void) const
			{
				return(CMultiMapReverseIteratorConst(MMultiMap.crend()));
			}

			CMultiMapValueIterator BeginValue(void)
			{
				return(CMultiMapValueIterator(MMultiMap.begin()));
			}

			CMultiMapValueIterator EndValue(void)
			{
				return(CMultiMapValueIterator(MMultiMap.end()));
			}

			CMultiMapValueIteratorConst BeginValue(void) const
			{
				return(CMultiMapValueIteratorConst(MMultiMap.cbegin()));
			}

			CMultiMapValueIteratorConst EndValue(void) const
			{
				return(CMultiMapValueIteratorConst(MMultiMap.cend()));
			}

			CMultiMapValueReverseIterator ReverseBeginValue(void)
			{
				return(CMultiMapValueReverseIterator(MMultiMap.rbegin()));
			}

			CMultiMapValueReverseIterator ReverseEndValue(void)
			{
				return(CMultiMapValueReverseIterator(MMultiMap.rend()));
			}

			CMultiMapValueReverseIteratorConst ReverseBeginValue(void) const
			{
				return(CMultiMapValueReverseIteratorConst(MMultiMap.crbegin()));
			}

			CMultiMapValueReverseIteratorConst ReverseEndValue(void) const
			{
				return(CMultiMapValueReverseIteratorConst(MMultiMap.crend()));
			}

			CMultiMapIterator begin(void)
			{
				return(CMultiMapIterator(MMultiMap.begin()));
			}

			CMultiMapIterator end(void)
			{
				return(CMultiMapIterator(MMultiMap.end()));
			}

			CMultiMapIteratorConst begin(void) const
			{
				return(CMultiMapIteratorConst(MMultiMap.cbegin()));
			}

			CMultiMapIteratorConst end(void) const
			{
				return(CMultiMapIteratorConst(MMultiMap.cend()));
			}

			CMultiMapReverseIterator rbegin(void)
			{
				return(CMultiMapReverseIterator(MMultiMap.rbegin()));
			}

			CMultiMapReverseIterator rend(void)
			{
				return(CMultiMapReverseIterator(MMultiMap.rend()));
			}

			CMultiMapReverseIteratorConst rbegin(void) const
			{
				return(CMultiMapReverseIteratorConst(MMultiMap.crbegin()));
			}

			CMultiMapReverseIteratorConst rend(void) const
			{
				return(CMultiMapReverseIteratorConst(MMultiMap.crend()));
			}

		public:
			CMultiMap(void)
				: MMultiMap()
			{
			}

			CMultiMap(const CMultiMap<TKeyType,TValueType>& Other)
				: MMultiMap(Other.MMultiMap)
			{
			}

			CMultiMap(CMultiMap<TKeyType,TValueType>&& Other) noexcept
				: MMultiMap(FUNCTION_MOVE(Other.MMultiMap))
			{
				Other.Clear();
			}

			CMultiMap(std::initializer_list<CPair<TKeyType,TValueType>> Other)
				: MMultiMap()
			{
				for(const CPair<TKeyType,TValueType>& Pair : Other)
				{
					Add(Pair);
				}
			}

			virtual ~CMultiMap(void) override
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------