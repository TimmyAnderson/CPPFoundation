//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <utility>
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Foundation/Objects/CObject.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	template<typename TFirstType, typename TSecondType>
	class CPair final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		template<typename TLocalFirstType, typename TLocalSecondType>
		friend class CPair;

		private:
			std::pair<TFirstType,TSecondType>					MPair;

		public:
			CPair<TFirstType,TSecondType>& operator=(const CPair<TFirstType,TSecondType>& Pair)
			{
				MPair=Pair.MPair;

				return(*this);
			}

			template<typename TLocalFirstType, typename TLocalSecondType,typename=typename std::enable_if<std::is_convertible<TLocalFirstType,TFirstType>::value && std::is_convertible<TLocalSecondType,TSecondType>::value==true,void>::type>
			CPair<TFirstType,TSecondType>& operator=(const CPair<TLocalFirstType,TLocalSecondType>& Pair)
			{
				MPair=Pair.MPair;

				return(*this);
			}

			CPair<TFirstType,TSecondType>& operator=(CPair<TFirstType,TSecondType>&& Pair)
			{
				MPair=FUNCTION_MOVE(Pair.MPair);

				return(*this);
			}

			template<typename TLocalFirstType, typename TLocalSecondType,typename=typename std::enable_if<std::is_convertible<TLocalFirstType,TFirstType>::value && std::is_convertible<TLocalSecondType,TSecondType>::value==true,void>::type>
			CPair<TFirstType,TSecondType>& operator=(CPair<TLocalFirstType,TLocalSecondType>&& Pair)
			{
				MPair.first=FUNCTION_FORWARD<TLocalFirstType>(Pair.GetFirst());
				MPair.second=FUNCTION_FORWARD<TLocalSecondType>(Pair.GetSecond());

				return(*this);
			}

			CPair<TFirstType,TSecondType>& operator=(const std::pair<TFirstType,TSecondType>& Pair)
			{
				MPair=Pair;

				return(*this);
			}

			template<typename TLocalFirstType, typename TLocalSecondType,typename=typename std::enable_if<std::is_convertible<TLocalFirstType,TFirstType>::value && std::is_convertible<TLocalSecondType,TSecondType>::value==true,void>::type>
			CPair<TFirstType,TSecondType>& operator=(const std::pair<TLocalFirstType,TLocalSecondType>& Pair)
			{
				MPair=Pair;

				return(*this);
			}

			CPair<TFirstType,TSecondType>& operator=(std::pair<TFirstType,TSecondType>&& Pair)
			{
				MPair=FUNCTION_MOVE(Pair);

				return(*this);
			}

			template<typename TLocalFirstType, typename TLocalSecondType,typename=typename std::enable_if<std::is_convertible<TLocalFirstType,TFirstType>::value && std::is_convertible<TLocalSecondType,TSecondType>::value==true,void>::type>
			CPair<TFirstType,TSecondType>& operator=(std::pair<TLocalFirstType,TLocalSecondType>&& Pair)
			{
				MPair.first=FUNCTION_FORWARD<TLocalFirstType>(Pair.first);
				MPair.second=FUNCTION_FORWARD<TLocalSecondType>(Pair.second);

				return(*this);
			}

		public:
			TFirstType& GetFirst(void) noexcept
			{
				return(MPair.first);
			}

			TSecondType& GetSecond(void) noexcept
			{
				return(MPair.second);
			}

			const TFirstType& GetFirst(void) const noexcept
			{
				return(MPair.first);
			}

			const TSecondType& GetSecond(void) const noexcept
			{
				return(MPair.second);
			}

			void SetFirst(const TFirstType& Value) noexcept
			{
				MPair.first=Value;
			}

			void SetSecond(const TSecondType& Value) noexcept
			{
				MPair.second=Value;
			}

			void SetFirst(TFirstType&& Value) noexcept
			{
				MPair.first=FUNCTION_MOVE(Value);
			}

			void SetSecond(TSecondType&& Value) noexcept
			{
				MPair.second=FUNCTION_MOVE(Value);
			}

		public:
			CPair(void)
				: MPair()
			{
			}

			CPair(const TFirstType& FirstValue, const TSecondType& SecondValue)
				: MPair(FirstValue,SecondValue)
			{
			}

			template<typename TLocalFirstType, typename TLocalSecondType,typename=typename std::enable_if<std::is_convertible<TLocalFirstType,TFirstType>::value && std::is_convertible<TLocalSecondType,TSecondType>::value==true,void>::type>
			CPair(const TLocalFirstType& FirstValue, const TLocalSecondType& SecondValue)
				: MPair(FirstValue,SecondValue)
			{
			}

			CPair(TFirstType&& FirstValue, TSecondType&& SecondValue)
				: MPair(FUNCTION_MOVE(FirstValue),FUNCTION_MOVE(SecondValue))
			{
			}

			template<typename TLocalFirstType, typename TLocalSecondType,typename=typename std::enable_if<std::is_convertible<TLocalFirstType,TFirstType>::value && std::is_convertible<TLocalSecondType,TSecondType>::value==true,void>::type>
			CPair(TLocalFirstType&& FirstValue, TLocalSecondType&& SecondValue)
				: MPair(FUNCTION_FORWARD<TLocalFirstType>(FirstValue),FUNCTION_FORWARD<TLocalSecondType>(SecondValue))
			{
			}

			CPair(const CPair<TFirstType,TSecondType>& Pair)
				: MPair(Pair.MPair)
			{
			}

			template<typename TLocalFirstType, typename TLocalSecondType,typename=typename std::enable_if<std::is_convertible<TLocalFirstType,TFirstType>::value && std::is_convertible<TLocalSecondType,TSecondType>::value==true,void>::type>
			CPair(const CPair<TLocalFirstType,TLocalSecondType>& Pair)
				: MPair(Pair.MPair)
			{
			}

			CPair(CPair<TFirstType,TSecondType>&& Pair) noexcept
				: MPair(FUNCTION_MOVE(Pair.MPair))
			{
			}

			template<typename TLocalFirstType, typename TLocalSecondType,typename=typename std::enable_if<std::is_convertible<TLocalFirstType,TFirstType>::value && std::is_convertible<TLocalSecondType,TSecondType>::value==true,void>::type>
			CPair(CPair<TLocalFirstType,TLocalSecondType>&& Pair)
				: MPair()
			{
				MPair.first=FUNCTION_FORWARD<TLocalFirstType>(Pair.GetFirst());
				MPair.second=FUNCTION_FORWARD<TLocalSecondType>(Pair.GetSecond());
			}

			CPair(const std::pair<TFirstType,TSecondType>& Pair)
				: MPair(Pair)
			{
			}

			template<typename TLocalFirstType, typename TLocalSecondType,typename=typename std::enable_if<std::is_convertible<TLocalFirstType,TFirstType>::value && std::is_convertible<TLocalSecondType,TSecondType>::value==true,void>::type>
			CPair(const std::pair<TLocalFirstType,TLocalSecondType>& Pair)
				: MPair(Pair)
			{
			}

			CPair(std::pair<TFirstType,TSecondType>&& Pair)
				: MPair(FUNCTION_MOVE(Pair))
			{
			}

			template<typename TLocalFirstType, typename TLocalSecondType,typename=typename std::enable_if<std::is_convertible<TLocalFirstType,TFirstType>::value && std::is_convertible<TLocalSecondType,TSecondType>::value==true,void>::type>
			CPair(std::pair<TLocalFirstType,TLocalSecondType>&& Pair)
				: MPair()
			{
				MPair.first=FUNCTION_FORWARD<TLocalFirstType>(Pair.first);
				MPair.second=FUNCTION_FORWARD<TLocalSecondType>(Pair.second);
			}

			virtual ~CPair(void) override
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------