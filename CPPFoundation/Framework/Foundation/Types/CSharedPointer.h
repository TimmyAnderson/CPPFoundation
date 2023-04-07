//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <memory>
#include <type_traits>
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Foundation/Exceptions/CNullPointerException.h>
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Strings/CString.h>
#include "ICallableObject.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType>
	class CSharedPointer final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		template<class TLocalType>
		friend class CSharedPointer;

		private:
			std::shared_ptr<TType>								MPointer;

		public:
			CSharedPointer<TType>& operator=(const CSharedPointer<TType>& Other) noexcept
			{
				MPointer=Other.MPointer;

				return(*this);
			}

			CSharedPointer<TType>& operator=(CSharedPointer<TType>&& Other) noexcept
			{
				MPointer=FUNCTION_MOVE(Other.MPointer);

				return(*this);
			}

			template<typename TLocalType,typename=typename std::enable_if<std::is_convertible<TLocalType*,TType*>::value==true,void>::type>
			CSharedPointer<TType>& operator=(const CSharedPointer<TLocalType>& Other) noexcept
			{
				MPointer=Other.MPointer;

				return(*this);
			}

			template<typename TLocalType,typename=typename std::enable_if<std::is_convertible<TLocalType*,TType*>::value==true,void>::type>
			CSharedPointer<TType>& operator=(CSharedPointer<TLocalType>&& Other) noexcept
			{
				MPointer=FUNCTION_MOVE(Other.MPointer);

				return(*this);
			}

			typename std::add_lvalue_reference<TType>::type operator*(void) const
			{
				if (IsNotNULL()==true)
				{
					return(*GetPointer());
				}
				else
				{
					throw(CNullPointerException("SHARED POINTER contains NULL !"));
				}
			}

			TType* operator->(void) const
			{
				if (IsNotNULL()==true)
				{
					return(GetPointer());
				}
				else
				{
					throw(CNullPointerException("SHARED POINTER contains NULL !"));
				}
			}

		private:
			CString PointerToString(const CObject* Pointer) const
			{
				return(Pointer->ToString());
			}

			CString PointerToString(const void* Pointer) const
			{
				Size											PointerValue=reinterpret_cast<Size>(Pointer);

				return(ToHexaDecimalString(PointerValue,true));
			}

		public:
			virtual CString ToString(void) const override
			{
				if (IsNotNULL()==true)
				{
					return(PointerToString(MPointer.get()));
				}
				else
				{
					return(CString("NULL"));
				}
			}

			bool IsNULL(void) const noexcept
			{
				if (MPointer.get()==nullptr)
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}

			bool IsNotNULL(void) const noexcept
			{
				if (MPointer.get()==nullptr)
				{
					return(false);
				}
				else
				{
					return(true);
				}
			}

			void VerifyNotNULL(const CString& SharedPointerName) const
			{
				if (MPointer.get()==nullptr)
				{
					throw(CNullPointerException(CString::Format("SHARED POINTER [",SharedPointerName,"] contains NULL !")));
				}
			}

			TType* GetPointer(void) const noexcept
			{
				return(MPointer.get());
			}

			void Reset(void) noexcept
			{
				MPointer.reset();
			}

			template<typename TLocalType>
			void Reset(TLocalType* Pointer)
			{
				MPointer.reset(Pointer);
			}

			Size GetCounter(void) const noexcept
			{
				return(static_cast<Size>(MPointer.use_count()));
			}

			template<typename TDestinationType> 
			CSharedPointer<TDestinationType> StaticCast(void) const noexcept
			{
				std::shared_ptr<TDestinationType>				Pointer=std::static_pointer_cast<TDestinationType,TType>(MPointer);

				if (static_cast<bool>(Pointer)==true)
				{
					CSharedPointer<TDestinationType>			SharedPointer(Pointer);

					return(SharedPointer);
				}
				else
				{
					return(CSharedPointer<TDestinationType>(nullptr));
				}
			}

			template<typename TDestinationType> 
			CSharedPointer<TDestinationType> DynamicCast(void) const noexcept
			{
				std::shared_ptr<TDestinationType>				Pointer=std::dynamic_pointer_cast<TDestinationType,TType>(MPointer);

				if (static_cast<bool>(Pointer)==true)
				{
					CSharedPointer<TDestinationType>			SharedPointer(Pointer);

					return(SharedPointer);
				}
				else
				{
					return(CSharedPointer<TDestinationType>(nullptr));
				}
			}

			template<typename TDestinationType> 
			CSharedPointer<const TDestinationType> DynamicCastAsConst(void) const noexcept
			{
				std::shared_ptr<const TDestinationType>			Pointer=std::dynamic_pointer_cast<const TDestinationType,TType>(MPointer);

				if (static_cast<bool>(Pointer)==true)
				{
					CSharedPointer<const TDestinationType>		SharedPointer(Pointer);

					return(SharedPointer);
				}
				else
				{
					return(CSharedPointer<const TDestinationType>(nullptr));
				}
			}

			template<typename TDestinationType> 
			CSharedPointer<TDestinationType> ConstCast(void) const noexcept
			{
				std::shared_ptr<TDestinationType>				Pointer=std::const_pointer_cast<TDestinationType,TType>(MPointer);

				if (static_cast<bool>(Pointer)==true)
				{
					CSharedPointer<TDestinationType>			SharedPointer(Pointer);

					return(SharedPointer);
				}
				else
				{
					return(CSharedPointer<TDestinationType>(nullptr));
				}
			}

			template<typename TDestinationType> 
			bool IsTypeOf(void) const noexcept
			{
				std::shared_ptr<TDestinationType>				Pointer=std::dynamic_pointer_cast<TDestinationType,TType>(MPointer);

				if (static_cast<bool>(Pointer)==true)
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}

			template<typename TDestinationType> 
			bool IsTypeOfAsConst(void) const noexcept
			{
				std::shared_ptr<const TDestinationType>			Pointer=std::dynamic_pointer_cast<const TDestinationType,TType>(MPointer);

				if (static_cast<bool>(Pointer)==true)
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}

		public:
			CSharedPointer(void) noexcept
				: MPointer(nullptr)
			{
			}

			CSharedPointer(const CSharedPointer<TType>& Other) noexcept
				: MPointer(Other.MPointer)
			{
			}

			CSharedPointer(CSharedPointer<TType>&& Other) noexcept
				: MPointer(FUNCTION_MOVE(Other.MPointer))
			{
			}

			constexpr CSharedPointer(std::nullptr_t) noexcept
				: MPointer(nullptr)
			{
			}

			template<typename TLocalType>
			explicit CSharedPointer(TLocalType* Pointer)
				: MPointer(Pointer)
			{
			}

			template<typename TLocalType,typename=typename std::enable_if<std::is_convertible<TLocalType*,TType*>::value==true,void>::type>
			CSharedPointer(const CSharedPointer<TLocalType>& Other) noexcept
				: MPointer(Other.MPointer)
			{
			}

			template<typename TLocalType,typename=typename std::enable_if<std::is_convertible<TLocalType*,TType*>::value==true,void>::type>
			CSharedPointer(CSharedPointer<TLocalType>&& Other) noexcept
				: MPointer(FUNCTION_MOVE(Other.MPointer))
			{
			}

			template<typename TLocalType,typename=typename std::enable_if<std::is_convertible<TLocalType*,TType*>::value==true,void>::type>
			CSharedPointer(const std::shared_ptr<TLocalType>& Other) noexcept
				: MPointer(Other)
			{
			}

			template<typename TLocalType,typename=typename std::enable_if<std::is_convertible<TLocalType*,TType*>::value==true,void>::type>
			CSharedPointer(std::shared_ptr<TLocalType>&& Other) noexcept
				: MPointer(FUNCTION_MOVE(Other))
			{
			}

			virtual ~CSharedPointer(void) override
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPObject=CSharedPointer<CObject>;
	using														CCSPObject=CSharedPointer<const CObject>;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType1, typename TType2>
	inline bool operator==(const CSharedPointer<TType1>& Left, const CSharedPointer<TType2>& Right)
	{
		return(Left.GetPointer()==Right.GetPointer());
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType1, typename TType2>
	inline bool operator!=(const CSharedPointer<TType1>& Left, const CSharedPointer<TType2>& Right)
	{
		return(Left.GetPointer()!=Right.GetPointer());
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType1, typename TType2>
	inline bool operator<(const CSharedPointer<TType1>& Left, const CSharedPointer<TType2>& Right)
	{
		return(Left.GetPointer()<Right.GetPointer());
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType1, typename TType2>
	inline bool operator>(const CSharedPointer<TType1>& Left, const CSharedPointer<TType2>& Right)
	{
		return(Left.GetPointer()>Right.GetPointer());
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType1, typename TType2>
	inline bool operator<=(const CSharedPointer<TType1>& Left, const CSharedPointer<TType2>& Right)
	{
		return(Left.GetPointer()<=Right.GetPointer());
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType1, typename TType2>
	inline bool operator>=(const CSharedPointer<TType1>& Left, const CSharedPointer<TType2>& Right)
	{
		return(Left.GetPointer()>=Right.GetPointer());
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType>
	inline bool operator==(const CSharedPointer<TType>& Left, std::nullptr_t)
	{
		return(Left.GetPointer()==static_cast<TType*>(nullptr));
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType>
	inline bool operator==(std::nullptr_t, const CSharedPointer<TType>& Right)
	{
		return(static_cast<TType*>(nullptr)==Right.GetPointer());
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType>
	inline bool operator!=(const CSharedPointer<TType>& Left, std::nullptr_t)
	{
		return(Left.GetPointer()!=static_cast<TType*>(nullptr));
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType>
	inline bool operator!=(std::nullptr_t, const CSharedPointer<TType>& Right)
	{
		return(static_cast<TType*>(nullptr)!=Right.GetPointer());
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType>
	inline bool operator<(const CSharedPointer<TType>& Left, std::nullptr_t)
	{
		return(Left.GetPointer()<static_cast<TType*>(nullptr));
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType>
	inline bool operator<(std::nullptr_t, const CSharedPointer<TType>& Right)
	{
		return(static_cast<TType*>(nullptr)<Right.GetPointer());
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType>
	inline bool operator>(const CSharedPointer<TType>& Left, std::nullptr_t)
	{
		return(Left.GetPointer()>static_cast<TType*>(nullptr));
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType>
	inline bool operator>(std::nullptr_t, const CSharedPointer<TType>& Right)
	{
		return(static_cast<TType*>(nullptr)>Right.GetPointer());
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType>
	inline bool operator<=(const CSharedPointer<TType>& Left, std::nullptr_t)
	{
		return(Left.GetPointer()<=static_cast<TType*>(nullptr));
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType>
	inline bool operator<=(std::nullptr_t, const CSharedPointer<TType>& Right)
	{
		return(static_cast<TType*>(nullptr)<=Right.GetPointer());
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType>
	inline bool operator>=(const CSharedPointer<TType>& Left, std::nullptr_t)
	{
		return(Left.GetPointer()>=static_cast<TType*>(nullptr));
	}
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType>
	inline bool operator>=(std::nullptr_t, const CSharedPointer<TType>& Right)
	{
		return(static_cast<TType*>(nullptr)>=Right.GetPointer());
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------