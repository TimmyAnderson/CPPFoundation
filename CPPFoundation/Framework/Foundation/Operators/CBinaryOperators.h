//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <type_traits>
#include <Framework/Platform/Global/Macros.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	template <typename TType1, typename TType2>
	class CBinaryOperators final
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			struct SOperatorYes
			{
//----------------------------------------------------------------------------------------------------------------------
				Char											MField[1];
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
			struct SOperatorNo
			{
//----------------------------------------------------------------------------------------------------------------------
				Char											MField[2];
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private:
			template <typename TLocalType1, typename TLocalType2>
			static auto HasDefinedOperatorPlus(TLocalType1 Value1, TLocalType2 Value2) -> decltype(Value1+Value2,SOperatorYes())
			{
				return(SOperatorYes());
			}

			template <typename ...TLocalTypes>
			static SOperatorNo HasDefinedOperatorPlus(TLocalTypes...)
			{
				return(SOperatorNo());
			}

			template <typename TLocalType1, typename TLocalType2>
			static auto HasDefinedOperatorMinus(TLocalType1 Value1, TLocalType2 Value2) -> decltype(Value1-Value2,SOperatorYes())
			{
				return(SOperatorYes());
			}

			template <typename ...TLocalTypes>
			static SOperatorNo HasDefinedOperatorMinus(TLocalTypes...)
			{
				return(SOperatorNo());
			}

			template <typename TLocalType1, typename TLocalType2>
			static auto HasDefinedOperatorMultiple(TLocalType1 Value1, TLocalType2 Value2) -> decltype(Value1*Value2,SOperatorYes())
			{
				return(SOperatorYes());
			}

			template <typename ...TLocalTypes>
			static SOperatorNo HasDefinedOperatorMultiple(TLocalTypes...)
			{
				return(SOperatorNo());
			}

			template <typename TLocalType1, typename TLocalType2>
			static auto HasDefinedOperatorDivide(TLocalType1 Value1, TLocalType2 Value2) -> decltype(Value1/Value2,SOperatorYes())
			{
				return(SOperatorYes());
			}

			template <typename ...TLocalTypes>
			static SOperatorNo HasDefinedOperatorDivide(TLocalTypes...)
			{
				return(SOperatorNo());
			}

			template <typename TLocalType1, typename TLocalType2>
			static auto HasDefinedOperatorBitwiseLeftShift(TLocalType1 Value1, TLocalType2 Value2) -> decltype(Value1<<Value2,SOperatorYes())
			{
				return(SOperatorYes());
			}

			template <typename ...TLocalTypes>
			static SOperatorNo HasDefinedOperatorBitwiseLeftShift(TLocalTypes...)
			{
				return(SOperatorNo());
			}

			template <typename TLocalType1, typename TLocalType2>
			static auto HasDefinedOperatorBitwiseRightShift(TLocalType1 Value1, TLocalType2 Value2) -> decltype(Value1>>Value2,SOperatorYes())
			{
				return(SOperatorYes());
			}

			template <typename ...TLocalTypes>
			static SOperatorNo HasDefinedOperatorBitwiseRightShift(TLocalTypes...)
			{
				return(SOperatorNo());
			}

		public:
			static const bool									HasOperatorPlus=(sizeof(HasDefinedOperatorPlus<TType1,TType2>(std::declval<TType1>(),std::declval<TType2>()))==sizeof(SOperatorYes));
			static const bool									HasOperatorMinus=(sizeof(HasDefinedOperatorMinus<TType1,TType2>(std::declval<TType1>(),std::declval<TType2>()))==sizeof(SOperatorYes));
			static const bool									HasOperatorMultiple=(sizeof(HasDefinedOperatorMultiple<TType1,TType2>(std::declval<TType1>(),std::declval<TType2>()))==sizeof(SOperatorYes));
			static const bool									HasOperatorDivide=(sizeof(HasDefinedOperatorDivide<TType1,TType2>(std::declval<TType1>(),std::declval<TType2>()))==sizeof(SOperatorYes));
			static const bool									HasOperatorBitwiseLeftShift=(sizeof(HasDefinedOperatorBitwiseLeftShift<TType1,TType2>(std::declval<TType1>(),std::declval<TType2>()))==sizeof(SOperatorYes));
			static const bool									HasOperatorBitwiseRightShift=(sizeof(HasDefinedOperatorBitwiseRightShift<TType1,TType2>(std::declval<TType1>(),std::declval<TType2>()))==sizeof(SOperatorYes));

		public:
			// Just to make compiler HAPPY.
			CBinaryOperators(void)
			{
			}

			// Just to make compiler HAPPY.
			~CBinaryOperators(void)
			{
			}
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------