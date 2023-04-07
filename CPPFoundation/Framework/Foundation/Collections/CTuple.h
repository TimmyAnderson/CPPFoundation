//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Exceptions/CValueOutOfRangeException.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	template<typename... TParameters>
	class CTuple;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<Size Index, typename... TParameters>
	class CTupleElement
	{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<typename TFirstParameter, typename... TOtherParameters>
	class CTupleElement<0,TFirstParameter,TOtherParameters...>
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			using												TTuple=CTuple<TFirstParameter,TOtherParameters...>;
			using												TValue=TFirstParameter;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<Size Index, typename TFirstParameter, typename... TOtherParameters>
	class CTupleElement<Index,TFirstParameter,TOtherParameters...> : public CTupleElement<Index-1,TOtherParameters...>
	{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<typename... TParameters>
	class CTuple : CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CTuple& operator=(const CTuple&)
			{
				return(*this);
			}

			CTuple& operator=(CTuple&&)
			{
				return(*this);
			}

		public:
			bool operator==(const CTuple&) const
			{
				return(true);
			}

			bool operator!=(const CTuple&) const
			{
				return(false);
			}

			bool operator<(const CTuple&) const
			{
				return(false);
			}

			bool operator>(const CTuple&) const
			{
				return(false);
			}

			bool operator<=(const CTuple&) const
			{
				return(true);
			}

			bool operator>=(const CTuple&) const
			{
				return(true);
			}

		public:
			CString GetString(void) const
			{
				return("");
			}

			virtual CString ToString(void) const override
			{
				return("");
			}

		public:
			bool Equal(const CTuple&) const
			{
				return(true);
			}

			bool Less(const CTuple&) const
			{
				return(false);
			}

		public:
			template<typename TType, Size Index>
			TType& GetItem(void)
			{
				throw(CValueOutOfRangeException("INDEX is OUT of RANGE !"));
			}

			template<typename TType, Size Index>
			const TType& GetItem(void) const
			{
				throw(CValueOutOfRangeException("INDEX is OUT of RANGE !"));
			}

			template<typename TType, Size Index>
			void SetItem(const TType&) const
			{
				throw(CValueOutOfRangeException("INDEX is OUT of RANGE !"));
			}

			template<typename TType, Size Index>
			void SetItem(TType&&) const
			{
				throw(CValueOutOfRangeException("INDEX is OUT of RANGE !"));
			}

		public:
			CTuple(void)
			{
			}

			CTuple(const CTuple&)
			{
			}

			CTuple(CTuple&&)
			{
			}

			virtual ~CTuple(void) override
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<typename TFirstParameter, typename... TOtherParameters>
	class CTuple<TFirstParameter,TOtherParameters...> : private CTuple<TOtherParameters...>
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			using												TBase=CTuple<TOtherParameters...>;

		private:
			TFirstParameter										MValue;

		public:
			CTuple<TFirstParameter,TOtherParameters...>& operator=(const CTuple<TFirstParameter,TOtherParameters...>& Other)
			{
				TBase::operator=(Other);

				MValue=Other.MValue;

				return(*this);
			}

			CTuple<TFirstParameter,TOtherParameters...>& operator=(CTuple<TFirstParameter,TOtherParameters...>&& Other)
			{
				TBase::operator=(FUNCTION_MOVE(Other));

				MValue=FUNCTION_MOVE(Other.MValue);

				return(*this);
			}

		public:
			bool operator==(const CTuple<TFirstParameter,TOtherParameters...>& Other) const
			{
				if (Equal(Other)==true)
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}

			bool operator!=(const CTuple<TFirstParameter,TOtherParameters...>& Other) const
			{
				if (Equal(Other)==false)
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}

			bool operator<(const CTuple<TFirstParameter,TOtherParameters...>& Other) const
			{
				if (Less(Other)==true)
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}

			bool operator>(const CTuple<TFirstParameter,TOtherParameters...>& Other) const
			{
				if (Other.Less(*this)==true)
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}

			bool operator<=(const CTuple<TFirstParameter,TOtherParameters...>& Other) const
			{
				if (Other.Less(*this)==false)
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}

			bool operator>=(const CTuple<TFirstParameter,TOtherParameters...>& Other) const
			{
				if (Less(Other)==false)
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}

		private:
			const TBase& GetBase(void) const
			{
				const TBase&									Base=dynamic_cast<const CTuple<TOtherParameters...>&>(*this);

				return(Base);
			}

		public:
			virtual CString ToString(void) const override
			{
				CString											Text=GetString();

				return(Text);
			}
			
		public:
			// METHOD MUST be NON-VIRTUAL.
			CString GetString(void) const
			{
				const TBase&									Base=GetBase();
				CString											Text=Base.GetString();

				if (Text.IsEmpty()==true)
				{
					Text=CString::Format("[",MValue,"]");
				}
				else
				{
					Text=CString::Format("[",MValue,"] ",Text);
				}
				
				return(Text);
			}

		public:
			TFirstParameter& GetValue(void)
			{
				return(MValue);
			}

			const TFirstParameter& GetValue(void) const
			{
				return(MValue);
			}

			void SetValue(const TFirstParameter& Value)
			{
				MValue=Value;
			}

			void SetValue(TFirstParameter&& Value)
			{
				MValue=FUNCTION_MOVE(Value);
			}

			bool Equal(const CTuple<TFirstParameter,TOtherParameters...>& Other) const
			{
				if (MValue==Other.MValue)
				{
					const TBase&								OtherBase=Other.GetBase();
					
					if (TBase::Equal(OtherBase)==true)
					{
						return(true);
					}
				}

				return(false);
			}

			bool Less(const CTuple<TFirstParameter,TOtherParameters...>& Other) const
			{
				if (MValue<Other.MValue)
				{
					return(true);
				}

				if ((Other.MValue<MValue)==false)
				{
					const TBase&								OtherBase=Other.GetBase();

					if (TBase::Less(OtherBase)==true)
					{
						return(true);
					}
				}

				return(false);
			}

		public:
			template<Size Index>
			typename CTupleElement<Index,TFirstParameter,TOtherParameters...>::TValue& GetItem(void)
			{
				static_assert(Index>=0 && Index<(sizeof...(TOtherParameters)+1),"INDEX is OUT of RANGE !");

				using											TTuple=typename CTupleElement<Index,TFirstParameter,TOtherParameters...>::TTuple;

				TTuple&											This=reinterpret_cast<TTuple&>(*this);

				return(This.GetValue());
			}

			template<Size Index>
			const typename CTupleElement<Index,TFirstParameter,TOtherParameters...>::TValue& GetItem(void) const
			{
				static_assert(Index>=0 && Index<(sizeof...(TOtherParameters)+1),"INDEX is OUT of RANGE !");

				using											TTuple=typename CTupleElement<Index,TFirstParameter,TOtherParameters...>::TTuple;

				const TTuple&									This=reinterpret_cast<const TTuple&>(*this);

				return(This.GetValue());
			}

			template<Size Index>
			void SetItem(const typename CTupleElement<Index,TFirstParameter,TOtherParameters...>::TValue& Value)
			{
				static_assert(Index>=0 && Index<(sizeof...(TOtherParameters)+1),"INDEX is OUT of RANGE !");

				using											TTuple=typename CTupleElement<Index,TFirstParameter,TOtherParameters...>::TTuple;

				TTuple&											This=reinterpret_cast<TTuple&>(*this);

				This.SetValue(Value);
			}

			template<Size Index>
			void SetItem(typename CTupleElement<Index,TFirstParameter,TOtherParameters...>::TValue&& Value)
			{
				static_assert(Index>=0 && Index<(sizeof...(TOtherParameters)+1),"INDEX is OUT of RANGE !");

				using											TTuple=typename CTupleElement<Index,TFirstParameter,TOtherParameters...>::TTuple;

				TTuple&											This=reinterpret_cast<TTuple&>(*this);

				This.SetValue(FUNCTION_MOVE(Value));
			}

		public:
			CTuple(void)
				: TBase(), MValue()
			{
			}

			CTuple(const TFirstParameter& Value, const TOtherParameters&... Values)
				: TBase(Values...), MValue(Value)
			{
			}

			CTuple(TFirstParameter&& Value, TOtherParameters&&... Values)
				: TBase(FUNCTION_MOVE(Values)...), MValue(FUNCTION_MOVE(Value))
			{
			}

			CTuple(const CTuple<TFirstParameter,TOtherParameters...>& Other)
				: TBase(Other), MValue(Other.MValue)
			{
			}

			CTuple(CTuple<TFirstParameter,TOtherParameters...>&& Other)
				: TBase(FUNCTION_MOVE(Other)), MValue(FUNCTION_MOVE(Other.MValue))
			{
			}

			virtual ~CTuple(void) override
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------