//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <type_traits>
#include <cmath>
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Foundation/Exceptions/CInvalidOperationException.h>
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Types/TypeTraits.h>
//----------------------------------------------------------------------------------------------------------------------
#if defined(PLATFORM_WINDOWS)
#undef min
#undef max
#endif
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CMathematics final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			template<typename TNumericType>
			static TNumericType Mininum(TNumericType Value1, TNumericType Value2)
			{
				static_assert(STypeTraitIsIntegral<TNumericType>::Value()==true || STypeTraitIsFloatingPoint<TNumericType>::Value()==true,"METHOD is NOT SUPPORTED for NON-NUMERIC TYPES !");

				if (Value1<Value2)
				{
					return(Value1);
				}
				else
				{
					return(Value2);
				}
			}

			template<typename TNumericType>
			static TNumericType Maximum(TNumericType Value1, TNumericType Value2)
			{
				static_assert(STypeTraitIsIntegral<TNumericType>::Value()==true || STypeTraitIsFloatingPoint<TNumericType>::Value()==true,"METHOD is NOT SUPPORTED for NON-NUMERIC TYPES !");

				if (Value1>Value2)
				{
					return(Value1);
				}
				else
				{
					return(Value2);
				}
			}

		public:
			template<typename TNumericType>
			static TNumericType CalculatePercentage(TNumericType Value, TNumericType Percentage)
			{
				static_assert(STypeTraitIsIntegral<TNumericType>::Value()==true || STypeTraitIsFloatingPoint<TNumericType>::Value()==true,"METHOD is NOT SUPPORTED for NON-NUMERIC TYPES !");

				constexpr TNumericType							PERCENTAGE_DIVISOR=100;

				TNumericType									Result=(Value*Percentage)/PERCENTAGE_DIVISOR;

				return(Result);
			}

		public:
			template<typename TNumericType>
			static bool EpsilonComparisonEqual(TNumericType Value1, TNumericType Value2, TNumericType Epsilon)
			{
				static_assert(STypeTraitIsFloatingPoint<TNumericType>::Value()==true,"METHOD is NOT SUPPORTED for NON FLOATING POINT TYPES !");

				if (Epsilon<TNumericType(0))
				{
					Epsilon=-Epsilon;
				}

				TNumericType									Difference=(Value2-Value1);

				if (Difference<TNumericType(0))
				{
					Difference=-Difference;
				}

				if (Difference<=Epsilon)
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}

			template<typename TNumericType>
			static bool EpsilonComparisonNotEqual(TNumericType Value1, TNumericType Value2, TNumericType Epsilon)
			{
				static_assert(STypeTraitIsFloatingPoint<TNumericType>::Value()==true,"METHOD is NOT SUPPORTED for NON FLOATING POINT TYPES !");

				return(!EpsilonComparisonEqual(Value1,Value2,Epsilon));
			}

			template<typename TNumericType>
			static bool EpsilonComparisonLowerThanOrEqual(TNumericType Value1, TNumericType Value2, TNumericType Epsilon)
			{
				static_assert(STypeTraitIsFloatingPoint<TNumericType>::Value()==true,"METHOD is NOT SUPPORTED for NON FLOATING POINT TYPES !");

				if (Value1<Value2)
				{
					return(true);
				}
				else
				{
					return(EpsilonComparisonEqual(Value1,Value2,Epsilon));
				}
			}

			template<typename TNumericType>
			static bool EpsilonComparisonGreaterToOrEqual(TNumericType Value1, TNumericType Value2, TNumericType Epsilon)
			{
				static_assert(STypeTraitIsFloatingPoint<TNumericType>::Value()==true,"METHOD is NOT SUPPORTED for NON FLOATING POINT TYPES !");

				if (Value1>Value2)
				{
					return(true);
				}
				else
				{
					return(EpsilonComparisonEqual(Value1,Value2,Epsilon));
				}
			}

		public:
			template<typename TNumericType>
			static TNumericType AbsoluteValueInteger(TNumericType Value)
			{
				static_assert(STypeTraitIsIntegral<TNumericType>::Value()==true,"METHOD is NOT SUPPORTED for NON INTEGER TYPES !");

				return(std::abs(Value));
			}

			template<typename TNumericType>
			static TNumericType AbsoluteValueFloatingPoint(TNumericType Value)
			{
				static_assert(STypeTraitIsFloatingPoint<TNumericType>::Value()==true,"METHOD is NOT SUPPORTED for NON FLOATING POINT TYPES !");

				return(std::fabs(Value));
			}

			template<typename TNumericType>
			static TNumericType SquareRoot(TNumericType Value)
			{
				static_assert(STypeTraitIsIntegral<TNumericType>::Value()==true || STypeTraitIsFloatingPoint<TNumericType>::Value()==true,"METHOD is NOT SUPPORTED for NON-NUMERIC TYPES !");

				if (Value<TNumericType(0))
				{
					throw(CInvalidOperationException("SQUARE ROOT can't be calculated from NEGATIVE VALUES !"));
				}

				return(std::sqrt(Value));
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------