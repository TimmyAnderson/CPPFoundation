//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <type_traits>
#include <Framework/Foundation/Exceptions/CInvalidOperationException.h>
#include <Framework/Foundation/Objects/CObject.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType>
	class CNullable final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		template<class TLocalType>
		friend class CNullable;

		private:
			bool												MHasValue;
			TType												MValue;

		public:
			CNullable<TType>& operator=(const TType* Value)
			{
				if (Value==nullptr)
				{
					MHasValue=false;
					MValue=TType();
				}
				else
				{
					MHasValue=true;
					MValue=*Value;
				}

				return(*this);
			}

			CNullable<TType>& operator=(const TType& Value)
			{
				MHasValue=true;
				MValue=Value;

				return(*this);
			}

			CNullable<TType>& operator=(TType&& Value)
			{
				MHasValue=true;
				MValue=FUNCTION_MOVE(Value);

				return(*this);
			}

			template<typename TLocalType,typename=typename std::enable_if<std::is_convertible<TLocalType,TType>::value==true,void>::type>
			CNullable<TType>& operator=(const TLocalType& Value)
			{
				MHasValue=true;
				MValue=Value;

				return(*this);
			}

			template<typename TLocalType,typename=typename std::enable_if<std::is_convertible<TLocalType,TType>::value==true,void>::type>
			CNullable<TType>& operator=(TLocalType&& Value)
			{
				MHasValue=true;
				MValue=FUNCTION_MOVE(Value);

				return(*this);
			}

			CNullable<TType>& operator=(const CNullable<TType>& Other)
			{
				MHasValue=Other.MHasValue;
				MValue=Other.MValue;

				return(*this);
			}

			CNullable<TType>& operator=(CNullable<TType>&& Other)
			{
				MHasValue=Other.MHasValue;
				MValue=FUNCTION_MOVE(Other.MValue);

				return(*this);
			}

			template<typename TLocalType,typename=typename std::enable_if<std::is_convertible<TLocalType,TType>::value==true,void>::type>
			CNullable<TType>& operator=(const CNullable<TLocalType>& Other)
			{
				MHasValue=Other.MHasValue;
				MValue=Other.MValue;

				return(*this);
			}

			template<typename TLocalType,typename=typename std::enable_if<std::is_convertible<TLocalType,TType>::value==true,void>::type>
			CNullable<TType>& operator=(CNullable<TLocalType>&& Other)
			{
				MHasValue=Other.MHasValue;
				MValue=FUNCTION_MOVE(Other.MValue);

				return(*this);
			}

		public:
			virtual CString ToString(void) const override
			{
				if (MHasValue==true)
				{
					return(CString::Format(MValue));
				}
				else
				{
					return(CString());
				}
			}

			TType& GetValue(void)
			{
				if (MHasValue==true)
				{
					return(MValue);
				}
				else
				{
					throw(CInvalidOperationException("NULLABLE OBJECT has NO VALUE !"));
				}
			}

			const TType& GetValue(void) const
			{
				if (MHasValue==true)
				{
					return(MValue);
				}
				else
				{
					throw(CInvalidOperationException("NULLABLE OBJECT has NO VALUE !"));
				}
			}

			const TType& GetValueOrDefault(const TType& DefaultValue) const
			{
				if (MHasValue==true)
				{
					return(MValue);
				}
				else
				{
					return(DefaultValue);
				}
			}

			TType* GetValueAsPointer(void)
			{
				if (MHasValue==true)
				{
					return(&MValue);
				}
				else
				{
					return(nullptr);
				}
			}

			const TType* GetValueAsPointer(void) const
			{
				if (MHasValue==true)
				{
					return(&MValue);
				}
				else
				{
					return(nullptr);
				}
			}

			bool GetHasValue(void) const noexcept
			{
				return(MHasValue);
			}

			void Reset(void)
			{
				MHasValue=false;
				MValue=TType();
			}

		public:
			CNullable(void)
				: MHasValue(false), MValue()
			{
			}

			CNullable(const TType* Value)
				: MHasValue((Value!=nullptr)), MValue((Value!=nullptr) ? *Value : TType())
			{
			}

			CNullable(const TType& Value)
				: MHasValue(true), MValue(Value)
			{
			}

			CNullable(TType&& Value)
				: MHasValue(true), MValue(Value)
			{
			}

			template<typename TLocalType,typename=typename std::enable_if<std::is_convertible<TLocalType,TType>::value==true,void>::type>
			CNullable(const TLocalType& Value)
				: MHasValue(true), MValue(Value)
			{
			}

			template<typename TLocalType,typename=typename std::enable_if<std::is_convertible<TLocalType,TType>::value==true,void>::type>
			CNullable(TLocalType&& Value)
				: MHasValue(true), MValue(FUNCTION_MOVE(Value))
			{
			}

			CNullable(const CNullable<TType>& Other)
				: MHasValue(Other.MHasValue), MValue(Other.MValue)
			{
			}

			CNullable(CNullable<TType>&& Other)
				: MHasValue(Other.MHasValue), MValue(FUNCTION_MOVE(Other.MValue))
			{
			}

			template<typename TLocalType,typename=typename std::enable_if<std::is_convertible<TLocalType,TType>::value==true,void>::type>
			CNullable(const CNullable<TLocalType>& Other)
				: MHasValue(Other.MHasValue), MValue(Other.MValue)
			{
			}

			template<typename TLocalType,typename=typename std::enable_if<std::is_convertible<TLocalType,TType>::value==true,void>::type>
			CNullable(CNullable<TLocalType>&& Other)
				: MHasValue(Other.MHasValue), MValue(FUNCTION_MOVE(Other.MValue))
			{
			}

			virtual ~CNullable(void) override
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CNullableInt8=CNullable<int8>;
	using														CNullableUInt8=CNullable<uint8>;
	using														CNullableInt16=CNullable<int16>;
	using														CNullableUInt16=CNullable<uint16>;
	using														CNullableInt32=CNullable<int32>;
	using														CNullableUInt32=CNullable<uint32>;
	using														CNullableInt64=CNullable<int64>;
	using														CNullableUInt64=CNullable<uint64>;
	using														CNullableFloat32=CNullable<float32>;
	using														CNullableFloat64=CNullable<float64>;
	using														CNullableFloat80=CNullable<float80>;
	using														CNullableSize=CNullable<Size>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------