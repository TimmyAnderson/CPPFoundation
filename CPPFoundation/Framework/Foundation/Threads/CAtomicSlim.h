//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <atomic>
#include <type_traits>
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Foundation/Objects/CObject.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	template<typename TType>
	class CAtomicSlim final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		static_assert(std::is_trivially_copyable<TType>::value==true,"TYPE MUST be TRIVIALLY COPYABLE !");

		private:
			std::atomic<TType>									MValue;

		public:
			CAtomicSlim<TType>& operator=(TType Value) noexcept
			{
				MValue=Value;

				return(*this);
			}

			CAtomicSlim<TType>& operator=(const CAtomicSlim<TType>& Other) noexcept
			{
				MValue=Other.GetValue();

				return(*this);
			}

		public:
			CAtomicSlim<TType>& operator++(void) noexcept
			{
				static_assert(std::is_integral<TType>::value==true,"TYPE MUST be INTERGRAL TYPE !");

				++MValue;

				return(*this);
			}

			CAtomicSlim<TType> operator++(int) noexcept
			{
				static_assert(std::is_integral<TType>::value==true,"TYPE MUST be INTERGRAL TYPE !");

				MValue++;

				return(*this);
			}

			CAtomicSlim<TType>& operator--(void) noexcept
			{
				static_assert(std::is_integral<TType>::value==true,"TYPE MUST be INTERGRAL TYPE !");

				--MValue;

				return(*this);
			}

			CAtomicSlim<TType> operator--(int) noexcept
			{
				static_assert(std::is_integral<TType>::value==true,"TYPE MUST be INTERGRAL TYPE !");

				MValue--;

				return(*this);
			}

		public:
			TType GetValue(void) const noexcept
			{
				return(MValue.load());
			}

			void SetValue(TType Value) noexcept
			{
				MValue.store(Value);
			}

			TType Exchange(TType Value) noexcept
			{
				TType											OldValue=MValue.exchange(Value);

				return(OldValue);
			}

		public:
			CAtomicSlim(void) noexcept
				: MValue()
			{
			}

			CAtomicSlim(TType Value) noexcept
				: MValue(Value)
			{
			}

			CAtomicSlim(const CAtomicSlim<TType>& Other) noexcept
				: MValue(Other.GetValue())
			{
			}

			virtual ~CAtomicSlim(void) override
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------