//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <typeinfo>
#include <iostream>
#include <Framework/Foundation/Types/Types.h>
#include <Framework/Platform/Global/Macros.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CString;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	class CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			[[noreturn]] void ThrowInvalidCastException(const Char* TypeName) const;

		public:
			template<typename TType>
			bool IsTypeOf(void) const
			{
				if (dynamic_cast<const TType*>(this)!=nullptr)
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}

			// Because OPERATOR [typeid] IGNORES [const] and [volatile] modifiers, METHODS RETURNS TRUE even if comparing TYPES [T] and [const T].
			template<typename TType>
			bool IsSameTypeAs(void) const
			{
				if (typeid(*this)==typeid(TType))
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}

			template<typename TType>
			const TType* DynamicCastPointer(void) const
			{
				const TType*									Pointer=dynamic_cast<const TType*>(this);

				return(Pointer);
			}

			template<typename TType>
			TType* DynamicCastPointer(void)
			{
				TType*											Pointer=dynamic_cast<TType*>(this);

				return(Pointer);
			}

			template<typename TType>
			const TType& DynamicCastReference(void) const
			{
				try
				{
					const TType&								Reference=dynamic_cast<const TType&>(*this);

					return(Reference);
				}
				catch(const std::bad_cast&)
				{
					ThrowInvalidCastException(typeid(TType).name());

					// PROGRAM NEVER gets here, because the METHOD ThrowException() ALWAYS throws an EXCEPTION. The following statements is placed here just to make COMPILER HAPPY, not COMPLAINING that the METHOD doesn't return value.
					throw;
				}
			}

			template<typename TType>
			TType& DynamicCastReference(void)
			{
				try
				{
					TType&										Reference=dynamic_cast<TType&>(*this);

					return(Reference);
				}
				catch(const std::bad_cast&)
				{
					ThrowInvalidCastException(typeid(TType).name());

					// PROGRAM NEVER gets here, because the METHOD ThrowException() ALWAYS throws an EXCEPTION. The following statements is placed here just to make COMPILER HAPPY, not COMPLAINING that the METHOD doesn't return value.
					throw;
				}
			}

		public:
			virtual CString ToString(void) const;

		public:
			CObject(void);
			virtual ~CObject(void)=0;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	std::ostream& operator<<(std::ostream& Stream, const CObject& Value);
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------