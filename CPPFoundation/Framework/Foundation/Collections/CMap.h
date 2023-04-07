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
	class CMap final : public CObject, public IEnumerable<CPair<const TKeyType,TValueType>>
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			class CMapEnumerator final : public IEnumerator<CPair<const TKeyType,TValueType>>
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					using										CMapValueType=CPair<const TKeyType,TValueType>;
					using										CMapType=CMap<TKeyType,TValueType,TComparator>;
					using										CMapTypeIterator=typename CMapType::CMapIterator;

				private:
					CMapType&									MMap;
					bool										MIsBeforeFirstItem;
					CMapTypeIterator							MIterator;

				public:
					virtual void Reset(void) override
					{
						MIsBeforeFirstItem=true;
						MIterator=MMap.Begin();
					}

					virtual bool MoveNext(void) override
					{
						if (MIsBeforeFirstItem==true)
						{
							MIsBeforeFirstItem=false;

							if (MIterator!=MMap.End())
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
							if (MIterator!=MMap.End())
							{
								if (++MIterator!=MMap.End())
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

					virtual const CMapValueType& GetCurrentConst(void) const override
					{
						if (MIsBeforeFirstItem==false && MIterator!=MMap.End())
						{
							return(*MIterator);
						}
						else
						{
							throw(CValueOutOfRangeException("ENUMERATOR is OUT of RANGE !"));
						}
					}

					virtual CMapValueType& GetCurrent(void) override
					{
						if (MIsBeforeFirstItem==false && MIterator!=MMap.End())
						{
							return(*MIterator);
						}
						else
						{
							throw(CValueOutOfRangeException("ENUMERATOR is OUT of RANGE !"));
						}
					}

				public:
					CMapEnumerator(CMapType& Map)
						: MMap(Map), MIsBeforeFirstItem(true), MIterator(Map.Begin())
					{
						Reset();
					}

					virtual ~CMapEnumerator(void) override
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
			class CMapEnumeratorConst final : public IEnumeratorConst<CPair<const TKeyType,TValueType>>
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					using										CMapValueType=CPair<const TKeyType,TValueType>;
					using										CMapType=CMap<TKeyType,TValueType,TComparator>;
					using										CMapTypeIteratorConst=typename CMapType::CMapIteratorConst;

				private:
					const CMapType&								MMap;
					bool										MIsBeforeFirstItem;
					CMapTypeIteratorConst						MIterator;

				public:
					virtual void Reset(void) override
					{
						MIsBeforeFirstItem=true;
						MIterator=MMap.Begin();
					}

					virtual bool MoveNext(void) override
					{
						if (MIsBeforeFirstItem==true)
						{
							MIsBeforeFirstItem=false;

							if (MIterator!=MMap.End())
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
							if (MIterator!=MMap.End())
							{
								if (++MIterator!=MMap.End())
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

					virtual const CMapValueType& GetCurrentConst(void) const override
					{
						if (MIsBeforeFirstItem==false && MIterator!=MMap.End())
						{
							return(*MIterator);
						}
						else
						{
							throw(CValueOutOfRangeException("ENUMERATOR is OUT of RANGE !"));
						}
					}

				public:
					CMapEnumeratorConst(const CMapType& Map)
						: MMap(Map), MIsBeforeFirstItem(true), MIterator(Map.Begin())
					{
						Reset();
					}

					virtual ~CMapEnumeratorConst(void) override
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public:
			class CMapIterator final
			{
//----------------------------------------------------------------------------------------------------------------------
				friend CMap<TKeyType,TValueType,TComparator>;

				private:
					using										CMapValueType=CPair<const TKeyType,TValueType>;
					using										CMapTypeIterator=typename std::map<TKeyType,CMapValueType,TComparator>::iterator;

				private:
					CMapTypeIterator							MIterator;

				public:
					bool operator==(const CMapIterator& Right) const
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
	
					bool operator!=(const CMapIterator& Right) const
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

					CMapIterator& operator++(void)
					{
						++MIterator;

						return(*this);
					}

					CMapIterator operator++(int32)
					{
						CMapIterator							Value(*this);

						++MIterator;

						return(Value);
					}

					CMapIterator& operator--(void)
					{
						--MIterator;

						return(*this);
					}

					CMapIterator operator--(int32)
					{
						CMapIterator							Value(*this);

						--MIterator;

						return(Value);
					}

					CMapValueType& operator*(void)
					{
						return(MIterator->second);
					}

					const CMapValueType& operator*(void) const
					{
						return(MIterator->second);
					}

					CMapValueType* operator->(void)
					{
						return(&MIterator->second);
					}

					const CMapValueType* operator->(void) const
					{
						return(&MIterator->second);
					}

				public:
					CMapIterator(const CMapTypeIterator& Iterator)
						: MIterator(Iterator)
					{
					}

					~CMapIterator(void)
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public:
			class CMapIteratorConst final
			{
//----------------------------------------------------------------------------------------------------------------------
				friend CMap<TKeyType,TValueType,TComparator>;

				private:
					using										CMapValueType=CPair<const TKeyType,TValueType>;
					using										CMapTypeIterator=typename std::map<TKeyType,CMapValueType,TComparator>::const_iterator;

				private:
					CMapTypeIterator							MIterator;

				public:
					bool operator==(const CMapIteratorConst& Right) const
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
	
					bool operator!=(const CMapIteratorConst& Right) const
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

					CMapIteratorConst& operator++(void)
					{
						++MIterator;

						return(*this);
					}

					CMapIteratorConst operator++(int32)
					{
						CMapIteratorConst						Value(*this);

						++MIterator;

						return(Value);
					}

					CMapIteratorConst& operator--(void)
					{
						--MIterator;

						return(*this);
					}

					CMapIteratorConst operator--(int32)
					{
						CMapIteratorConst						Value(*this);

						--MIterator;

						return(Value);
					}

					const CMapValueType& operator*(void) const
					{
						return(MIterator->second);
					}

					const CMapValueType* operator->(void) const
					{
						return(&MIterator->second);
					}

				public:
					CMapIteratorConst(const CMapTypeIterator& Iterator)
						: MIterator(Iterator)
					{
					}

					~CMapIteratorConst(void)
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public:
			class CMapReverseIterator final
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					using										CMapValueType=CPair<const TKeyType,TValueType>;
					using										CMapTypeReverseIterator=typename std::map<TKeyType,CMapValueType,TComparator>::reverse_iterator;

				private:
					CMapTypeReverseIterator						MIterator;

				public:
					bool operator==(const CMapReverseIterator& Right) const
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
	
					bool operator!=(const CMapReverseIterator& Right) const
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

					CMapReverseIterator& operator++(void)
					{
						++MIterator;

						return(*this);
					}

					CMapReverseIterator operator++(int32)
					{
						CMapReverseIterator						Value(*this);

						++MIterator;

						return(Value);
					}

					CMapReverseIterator& operator--(void)
					{
						--MIterator;

						return(*this);
					}

					CMapReverseIterator operator--(int32)
					{
						CMapReverseIterator						Value(*this);

						--MIterator;

						return(Value);
					}

					CMapValueType& operator*(void)
					{
						return(MIterator->second);
					}

					const CMapValueType& operator*(void) const
					{
						return(MIterator->second);
					}

					CMapValueType* operator->(void)
					{
						return(&MIterator->second);
					}

					const CMapValueType* operator->(void) const
					{
						return(&MIterator->second);
					}

				public:
					CMapReverseIterator(const CMapTypeReverseIterator& Iterator)
						: MIterator(Iterator)
					{
					}

					~CMapReverseIterator(void)
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public:
			class CMapReverseIteratorConst final
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					using										CMapValueType=CPair<const TKeyType,TValueType>;
					using										CMapTypeReverseIterator=typename std::map<TKeyType,CMapValueType,TComparator>::const_reverse_iterator;

				private:
					CMapTypeReverseIterator						MIterator;

				public:
					bool operator==(const CMapReverseIteratorConst& Right) const
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
	
					bool operator!=(const CMapReverseIteratorConst& Right) const
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

					CMapReverseIteratorConst& operator++(void)
					{
						++MIterator;

						return(*this);
					}

					CMapReverseIteratorConst operator++(int32)
					{
						CMapReverseIteratorConst				Value(*this);

						++MIterator;

						return(Value);
					}

					CMapReverseIteratorConst& operator--(void)
					{
						--MIterator;

						return(*this);
					}

					CMapReverseIteratorConst operator--(int32)
					{
						CMapReverseIteratorConst				Value(*this);

						--MIterator;

						return(Value);
					}

					const CMapValueType& operator*(void) const
					{
						return(MIterator->second);
					}

					const CMapValueType* operator->(void) const
					{
						return(&MIterator->second);
					}

				public:
					CMapReverseIteratorConst(const CMapTypeReverseIterator& Iterator)
						: MIterator(Iterator)
					{
					}

					~CMapReverseIteratorConst(void)
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public:
			class CMapValueIterator final
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					using										CValueType=TValueType;
					using										CMapValueType=CPair<const TKeyType,TValueType>;
					using										CMapTypeIterator=typename std::map<TKeyType,CMapValueType,TComparator>::iterator;

				private:
					CMapTypeIterator							MIterator;

				public:
					bool operator==(const CMapValueIterator& Right) const
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
	
					bool operator!=(const CMapValueIterator& Right) const
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

					CMapValueIterator& operator++(void)
					{
						++MIterator;

						return(*this);
					}

					CMapValueIterator operator++(int32)
					{
						CMapValueIterator						Value(*this);

						++MIterator;

						return(Value);
					}

					CMapValueIterator& operator--(void)
					{
						--MIterator;

						return(*this);
					}

					CMapValueIterator operator--(int32)
					{
						CMapValueIterator						Value(*this);

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
					CMapValueIterator(const CMapTypeIterator& Iterator)
						: MIterator(Iterator)
					{
					}

					~CMapValueIterator(void)
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public:
			class CMapValueIteratorConst final
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					using										CValueType=TValueType;
					using										CMapValueType=CPair<const TKeyType,TValueType>;
					using										CMapTypeIterator=typename std::map<TKeyType,CMapValueType,TComparator>::const_iterator;

				private:
					CMapTypeIterator							MIterator;

				public:
					bool operator==(const CMapValueIteratorConst& Right) const
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
	
					bool operator!=(const CMapValueIteratorConst& Right) const
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

					CMapValueIteratorConst& operator++(void)
					{
						++MIterator;

						return(*this);
					}

					CMapValueIteratorConst operator++(int32)
					{
						CMapValueIteratorConst					Value(*this);

						++MIterator;

						return(Value);
					}

					CMapValueIteratorConst& operator--(void)
					{
						--MIterator;

						return(*this);
					}

					CMapValueIteratorConst operator--(int32)
					{
						CMapValueIteratorConst					Value(*this);

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
					CMapValueIteratorConst(const CMapTypeIterator& Iterator)
						: MIterator(Iterator)
					{
					}

					~CMapValueIteratorConst(void)
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public:
			class CMapValueReverseIterator final
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					using										CValueType=TValueType;
					using										CMapValueType=CPair<const TKeyType,TValueType>;
					using										CMapTypeReverseIterator=typename std::map<TKeyType,CMapValueType,TComparator>::reverse_iterator;

				private:
					CMapTypeReverseIterator						MIterator;

				public:
					bool operator==(const CMapValueReverseIterator& Right) const
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
	
					bool operator!=(const CMapValueReverseIterator& Right) const
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

					CMapValueReverseIterator& operator++(void)
					{
						++MIterator;

						return(*this);
					}

					CMapValueReverseIterator operator++(int32)
					{
						CMapValueReverseIterator				Value(*this);

						++MIterator;

						return(Value);
					}

					CMapValueReverseIterator& operator--(void)
					{
						--MIterator;

						return(*this);
					}

					CMapValueReverseIterator operator--(int32)
					{
						CMapValueReverseIterator				Value(*this);

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
					CMapValueReverseIterator(const CMapTypeReverseIterator& Iterator)
						: MIterator(Iterator)
					{
					}

					~CMapValueReverseIterator(void)
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public:
			class CMapValueReverseIteratorConst final
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					using										CValueType=TValueType;
					using										CMapValueType=CPair<const TKeyType,TValueType>;
					using										CMapTypeReverseIterator=typename std::map<TKeyType,CMapValueType,TComparator>::const_reverse_iterator;

				private:
					CMapTypeReverseIterator						MIterator;

				public:
					bool operator==(const CMapValueReverseIteratorConst& Right) const
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
	
					bool operator!=(const CMapValueReverseIteratorConst& Right) const
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

					CMapValueReverseIteratorConst& operator++(void)
					{
						++MIterator;

						return(*this);
					}

					CMapValueReverseIteratorConst operator++(int32)
					{
						CMapValueReverseIteratorConst			Value(*this);

						++MIterator;

						return(Value);
					}

					CMapValueReverseIteratorConst& operator--(void)
					{
						--MIterator;

						return(*this);
					}

					CMapValueReverseIteratorConst operator--(int32)
					{
						CMapValueReverseIteratorConst			Value(*this);

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
					CMapValueReverseIteratorConst(const CMapTypeReverseIterator& Iterator)
						: MIterator(Iterator)
					{
					}

					~CMapValueReverseIteratorConst(void)
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		static_assert(STypeTraitIsBaseOf<IIsBeforeComparator<TKeyType>,TComparator>::Value()==true,"KEY TYPE MUST implement INTERFACE [IIsBeforeComparator<TKeyType>] !");

		private:
			using												CMapValueType=CPair<const TKeyType,TValueType>;
			using												CMapType=std::map<TKeyType,CMapValueType,TComparator>;
			using												CMapTypeIterator=typename std::map<TKeyType,CMapValueType,TComparator>::iterator;
			using												CMapTypeIteratorConst=typename std::map<TKeyType,CMapValueType,TComparator>::const_iterator;
			using												CMapTypeReverseIterator=typename std::map<TKeyType,CMapValueType,TComparator>::reverse_iterator;

		public:
			using												CEnumeratorPointer=CSharedPointer<IEnumerator<CMapValueType>>;
			using												CEnumeratorConstPointer=CSharedPointer<IEnumeratorConst<CMapValueType>>;
			using												CKeyCollection=CSharedPointer<CVector<TKeyType>>;
			using												CValueCollection=CSharedPointer<CVector<TValueType>>;
			using												CKeyValuePair=CMapValueType;

		private:
			CMapType											MMap;

		public:
			CMap<TKeyType,TValueType>& operator=(const CMap<TKeyType,TValueType>& Other)
			{
				MMap=Other.MMap;

				return(*this);
			}

			CMap<TKeyType,TValueType>& operator=(CMap<TKeyType,TValueType>&& Other)
			{
				MMap=FUNCTION_MOVE(Other.MMap);
				Other.Clear();

				return(*this);
			}

			TValueType& operator[](const TKeyType& Key)
			{
				if (Contains(Key)==true)
				{
					return(MMap.at(Key).GetSecond());
				}
				else
				{
					throw(CInvalidValueException(CString::Format("MAP doesn't CONTAIN KEY [",Key,"] !")));
				}
			}

			TValueType& operator[](TKeyType&& Key)
			{
				if (Contains(Key)==true)
				{
					return(MMap.at(FUNCTION_FORWARD<TKeyType>(Key)).GetSecond());
				}
				else
				{
					throw(CInvalidValueException(CString::Format("MAP doesn't CONTAIN KEY [",Key,"] !")));
				}
			}

			const TValueType& operator[](const TKeyType& Key) const
			{
				if (Contains(Key)==true)
				{
					return(MMap.at(Key).GetSecond());
				}
				else
				{
					throw(CInvalidValueException(CString::Format("MAP doesn't CONTAIN KEY [",Key,"] !")));
				}
			}

			const TValueType& operator[](TKeyType&& Key) const
			{
				if (Contains(Key)==true)
				{
					return(MMap.at(FUNCTION_FORWARD<TKeyType>(Key)).GetSecond());
				}
				else
				{
					throw(CInvalidValueException(CString::Format("MAP already CONTAINS KEY [",Key,"] !")));
				}
			}

		public:
			void Add(const TKeyType& Key, const TValueType& Value)
			{
				if (Contains(Key)==false)
				{
					MMap.insert(std::pair<const TKeyType,CMapValueType>(Key,CMapValueType(Key,FUNCTION_FORWARD<const TValueType>(Value))));
				}
				else
				{
					throw(CInvalidValueException(CString::Format("MAP already CONTAINS KEY [",Key,"] !")));
				}
			}

			void Add(const TKeyType& Key, TValueType&& Value)
			{
				if (Contains(Key)==false)
				{
					MMap.insert(std::pair<const TKeyType,CMapValueType>(Key,CMapValueType(Key,FUNCTION_FORWARD<TValueType>(Value))));
				}
				else
				{
					throw(CInvalidValueException(CString::Format("MAP already CONTAINS KEY [",Key,"] !")));
				}
			}

			void Add(const CPair<TKeyType,TValueType>& Pair)
			{
				if (Contains(Pair.GetFirst())==false)
				{
					MMap.insert(std::pair<TKeyType,CMapValueType>(Pair.GetFirst(),CMapValueType(Pair.GetFirst(),FUNCTION_FORWARD<const TValueType>(Pair.GetSecond()))));
				}
				else
				{
					throw(CInvalidValueException(CString::Format("MAP already CONTAINS KEY [",Pair.GetFirst(),"] !")));
				}
			}

			void Add(CPair<TKeyType,TValueType>&& Pair)
			{
				if (Contains(Pair.GetFirst())==false)
				{
					MMap.insert(std::pair<TKeyType,CMapValueType>(Pair.GetFirst(),CMapValueType(Pair.GetFirst(),FUNCTION_FORWARD<const TValueType>(Pair.GetSecond()))));
				}
				else
				{
					throw(CInvalidValueException(CString::Format("MAP already CONTAINS KEY [",Pair.GetFirst(),"] !")));
				}
			}

			void AddOrReplace(const TKeyType& Key, const TValueType& Value)
			{
				if (Contains(Key)==false)
				{
					MMap.insert(std::pair<const TKeyType,CMapValueType>(Key,CMapValueType(Key,FUNCTION_FORWARD<const TValueType>(Value))));
				}
				else
				{
					MMap.at(FUNCTION_FORWARD<const TKeyType>(Key)).GetSecond()=FUNCTION_FORWARD<const TValueType>(Value);
				}
			}

			void AddOrReplace(const TKeyType& Key, TValueType&& Value)
			{
				if (Contains(Key)==false)
				{
					MMap.insert(std::pair<const TKeyType,CMapValueType>(Key,CMapValueType(Key,FUNCTION_FORWARD<TValueType>(Value))));
				}
				else
				{
					MMap.at(FUNCTION_FORWARD<const TKeyType>(Key)).GetSecond()=FUNCTION_FORWARD<TValueType>(Value);
				}
			}

			void AddOrReplace(const CPair<TKeyType,TValueType>& Pair)
			{
				if (Contains(Pair.GetFirst())==false)
				{
					MMap.insert(std::pair<TKeyType,CMapValueType>(Pair.GetFirst(),CMapValueType(Pair.GetFirst(),FUNCTION_FORWARD<const TValueType>(Pair.GetSecond()))));
				}
				else
				{
					MMap.at(FUNCTION_FORWARD<const TKeyType>(Pair.GetFirst())).SetSecond(Pair.GetSecond());
				}
			}

			void AddOrReplace(CPair<TKeyType,TValueType>&& Pair)
			{
				if (Contains(Pair.GetFirst())==false)
				{
					MMap.insert(std::pair<TKeyType,CMapValueType>(Pair.GetFirst(),CMapValueType(Pair.GetFirst(),FUNCTION_FORWARD<const TValueType>(Pair.GetSecond()))));
				}
				else
				{
					MMap.at(FUNCTION_FORWARD<const TKeyType>(Pair.GetFirst())).SetSecond(Pair.GetSecond());
				}
			}

			bool Insert(const TKeyType& Key, const TValueType& Value)
			{
				std::pair<CMapTypeIterator,bool>				Result=MMap.insert(std::pair<TKeyType,CMapValueType>(Key,CMapValueType(Key,FUNCTION_FORWARD<const TValueType>(Value))));

				return(Result.second);
			}

			bool Insert(const TKeyType& Key, TValueType&& Value)
			{
				std::pair<CMapTypeIterator,bool>				Result=MMap.insert(std::pair<TKeyType,CMapValueType>(Key,CMapValueType(Key,FUNCTION_FORWARD<const TValueType>(Value))));

				return(Result.second);
			}

			bool Insert(const CPair<TKeyType,TValueType>& Pair)
			{
				std::pair<CMapTypeIterator,bool>				Result=MMap.insert(std::pair<TKeyType,CMapValueType>(Pair.GetFirst(),CMapValueType(Pair.GetFirst(),FUNCTION_FORWARD<const TValueType>(Pair.GetSecond()))));

				return(Result.second);
			}

			bool Insert(CPair<TKeyType,TValueType>&& Pair)
			{
				std::pair<CMapTypeIterator,bool>				Result=MMap.insert(std::pair<TKeyType,CMapValueType>(Pair.GetFirst(),CMapValueType(Pair.GetFirst(),FUNCTION_FORWARD<const TValueType>(Pair.GetSecond()))));

				return(Result.second);
			}

			bool Erase(const TKeyType& Key)
			{
				Size											NumberOfRemovedItems=static_cast<Size>(MMap.erase(Key));

				if (NumberOfRemovedItems>0)
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}

			void Erase(CMapIteratorConst Iterator)
			{
				MMap.erase(Iterator.MIterator);
			}

			void Erase(CMapIterator Iterator)
			{
				MMap.erase(Iterator.MIterator);
			}

			void Clear(void) noexcept
			{
				MMap.clear();
			}

		public:
			Size GetLength(void) const noexcept
			{
				Size											Length=static_cast<Size>(MMap.size());
				
				return(Length);
			}

			bool IsEmpty(void) const noexcept
			{
				Size											Length=static_cast<Size>(MMap.size());

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
				if (MMap.find(Key)!=MMap.end())
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}

			TValueType GetValueOrDefault(const TKeyType& Key) const
			{
				static_assert(STypeTraitIsDefaultConstructible<TValueType>::Value()==true,"VALUE TYPE doesn't have a DEFAULT CONTRUCTOR !");

				if (MMap.find(Key)!=MMap.end())
				{
					return(MMap.at(Key).GetSecond());
				}
				else
				{
					return(TValueType());
				}
			}

			CKeyCollection GetKeys(void) const
			{
				CKeyCollection									VectorPointer(new CVector<TKeyType>());
				const IEnumerableConst<CMapValueType>&			Enumerable=*this;
				CSharedPointer<IEnumeratorConst<CMapValueType>>	Enumerator=Enumerable.GetEnumeratorConst();

				while(Enumerator->MoveNext()==true)
				{
					VectorPointer->Add(Enumerator->GetCurrentConst().GetFirst());
				}

				return(VectorPointer);
			}

			CValueCollection GetValues(void) const
			{
				CValueCollection								VectorPointer(new CVector<TValueType>());
				const IEnumerableConst<CMapValueType>&			Enumerable=*this;
				CSharedPointer<IEnumeratorConst<CMapValueType>>	Enumerator=Enumerable.GetEnumeratorConst();

				while(Enumerator->MoveNext()==true)
				{
					VectorPointer->Add(Enumerator->GetCurrentConst().GetSecond());
				}

				return(VectorPointer);
			}

			virtual CEnumeratorPointer GetEnumerator(void) override
			{
				CEnumeratorPointer								Enumerator=CEnumeratorPointer(new CMapEnumerator(*this));

				return(Enumerator);
			}

			virtual CEnumeratorConstPointer GetEnumeratorConst(void) const override
			{
				CEnumeratorConstPointer							Enumerator=CEnumeratorConstPointer(new CMapEnumeratorConst(*this));

				return(Enumerator);
			}

			CMapIterator Find(const TKeyType& Key)
			{
				return(CMapIterator(MMap.find(Key)));
			}

			CMapIteratorConst Find(const TKeyType& Key) const
			{
				return(CMapIteratorConst(MMap.find(Key)));
			}

			CMapIterator LowerBound(const TKeyType& Key)
			{
				CMapTypeIterator								Iterator=MMap.lower_bound(Key);

				return(CMapIterator(Iterator));
			}

			CMapIteratorConst LowerBound(const TKeyType& Key) const
			{
				CMapTypeIteratorConst							Iterator=MMap.lower_bound(Key);

				return(CMapIteratorConst(Iterator));
			}

			CMapIterator UpperBound(const TKeyType& Key)
			{
				CMapTypeIterator								Iterator=MMap.upper_bound(Key);

				return(CMapIterator(Iterator));
			}

			CMapIteratorConst UpperBound(const TKeyType& Key) const
			{
				CMapTypeIteratorConst							Iterator=MMap.upper_bound(Key);

				return(CMapIteratorConst(Iterator));
			}

			CMapIterator Begin(void)
			{
				return(CMapIterator(MMap.begin()));
			}

			CMapIterator End(void)
			{
				return(CMapIterator(MMap.end()));
			}

			CMapIteratorConst ConstBegin(void) const
			{
				return(CMapIteratorConst(MMap.cbegin()));
			}

			CMapIteratorConst ConstEnd(void) const
			{
				return(CMapIteratorConst(MMap.cend()));
			}

			CMapIteratorConst Begin(void) const
			{
				return(CMapIteratorConst(MMap.cbegin()));
			}

			CMapIteratorConst End(void) const
			{
				return(CMapIteratorConst(MMap.cend()));
			}

			CMapReverseIterator ReverseBegin(void)
			{
				return(CMapReverseIterator(MMap.rbegin()));
			}

			CMapReverseIterator ReverseEnd(void)
			{
				return(CMapReverseIterator(MMap.rend()));
			}

			CMapReverseIteratorConst ConstReverseBegin(void) const
			{
				return(CMapReverseIteratorConst(MMap.crbegin()));
			}

			CMapReverseIteratorConst ConstReverseEnd(void) const
			{
				return(CMapReverseIteratorConst(MMap.crend()));
			}

			CMapReverseIteratorConst ReverseBegin(void) const
			{
				return(CMapReverseIteratorConst(MMap.crbegin()));
			}

			CMapReverseIteratorConst ReverseEnd(void) const
			{
				return(CMapReverseIteratorConst(MMap.crend()));
			}

			CMapValueIterator BeginValue(void)
			{
				return(CMapValueIterator(MMap.begin()));
			}

			CMapValueIterator EndValue(void)
			{
				return(CMapValueIterator(MMap.end()));
			}

			CMapValueIteratorConst BeginValue(void) const
			{
				return(CMapValueIteratorConst(MMap.cbegin()));
			}

			CMapValueIteratorConst EndValue(void) const
			{
				return(CMapValueIteratorConst(MMap.cend()));
			}

			CMapValueReverseIterator ReverseBeginValue(void)
			{
				return(CMapValueReverseIterator(MMap.rbegin()));
			}

			CMapValueReverseIterator ReverseEndValue(void)
			{
				return(CMapValueReverseIterator(MMap.rend()));
			}

			CMapValueReverseIteratorConst ReverseBeginValue(void) const
			{
				return(CMapValueReverseIteratorConst(MMap.crbegin()));
			}

			CMapValueReverseIteratorConst ReverseEndValue(void) const
			{
				return(CMapValueReverseIteratorConst(MMap.crend()));
			}

			CMapIterator begin(void)
			{
				return(CMapIterator(MMap.begin()));
			}

			CMapIterator end(void)
			{
				return(CMapIterator(MMap.end()));
			}

			CMapIteratorConst begin(void) const
			{
				return(CMapIteratorConst(MMap.cbegin()));
			}

			CMapIteratorConst end(void) const
			{
				return(CMapIteratorConst(MMap.cend()));
			}

			CMapReverseIterator rbegin(void)
			{
				return(CMapReverseIterator(MMap.rbegin()));
			}

			CMapReverseIterator rend(void)
			{
				return(CMapReverseIterator(MMap.rend()));
			}

			CMapReverseIteratorConst rbegin(void) const
			{
				return(CMapReverseIteratorConst(MMap.crbegin()));
			}

			CMapReverseIteratorConst rend(void) const
			{
				return(CMapReverseIteratorConst(MMap.crend()));
			}

		public:
			CMap(void)
				: MMap()
			{
			}

			CMap(const CMap<TKeyType,TValueType>& Other)
				: MMap(Other.MMap)
			{
			}

			CMap(CMap<TKeyType,TValueType>&& Other)
				: MMap(FUNCTION_MOVE(Other.MMap))
			{
				Other.Clear();
			}

			CMap(std::initializer_list<CPair<TKeyType,TValueType>> Other)
				: MMap()
			{
				for(const CPair<TKeyType,TValueType>& Pair : Other)
				{
					Add(Pair);
				}
			}

			virtual ~CMap(void) override
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------