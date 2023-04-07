//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <type_traits>
#include <limits>
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Strings/CString.h>
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
	template<typename TPrimitiveType>
	class CPrimitiveType final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		static_assert(std::numeric_limits<TPrimitiveType>::is_specialized==true && (std::is_integral<TPrimitiveType>::value==true || std::is_floating_point<TPrimitiveType>::value==true),"TYPE is NOT SUPPORTED for TEMPLATE [CPrimitiveType<TPrimitiveType>] !");

		private:
			TPrimitiveType										MValue;

		public:
			static constexpr TPrimitiveType Min(void)
			{
				return(std::numeric_limits<TPrimitiveType>::lowest());
			}

			static constexpr TPrimitiveType Max(void)
			{
				return(std::numeric_limits<TPrimitiveType>::max());
			}

			static constexpr TPrimitiveType Infinity(void)
			{
				static_assert(std::numeric_limits<TPrimitiveType>::has_infinity==true,"METHOD doesn't SUPPORT INFINITY VALUE for TEMPLATE [CPrimitiveType<TPrimitiveType>] !");

				return(std::numeric_limits<TPrimitiveType>::infinity());
			}

			static constexpr TPrimitiveType QuietNaN(void)
			{
				static_assert(std::numeric_limits<TPrimitiveType>::has_quiet_NaN==true,"METHOD doesn't SUPPORT QUIET NAN VALUE for TEMPLATE [CPrimitiveType<TPrimitiveType>] !");

				return(std::numeric_limits<TPrimitiveType>::quiet_NaN());
			}

			static constexpr TPrimitiveType SignalingNaN(void)
			{
				static_assert(std::numeric_limits<TPrimitiveType>::has_signaling_NaN==true,"METHOD doesn't SUPPORT SIGNALING NAN VALUE for TEMPLATE [CPrimitiveType<TPrimitiveType>] !");

				return(std::numeric_limits<TPrimitiveType>::signaling_NaN());
			}

			static constexpr TPrimitiveType Epsilon(void)
			{
				return(std::numeric_limits<TPrimitiveType>::epsilon());
			}

			static constexpr TPrimitiveType RoundError(void)
			{
				return(std::numeric_limits<TPrimitiveType>::round_error());
			}

			static constexpr bool HasInfinity(void)
			{
				return(std::numeric_limits<TPrimitiveType>::has_infinity);
			}

			static constexpr bool HasQuietNaN(void)
			{
				return(std::numeric_limits<TPrimitiveType>::has_quiet_NaN);
			}

			static constexpr bool HasSignalingNaN(void)
			{
				return(std::numeric_limits<TPrimitiveType>::has_signaling_NaN);
			}

			static constexpr int32 GetMaxDigits10(void)
			{
				return(static_cast<int32>(std::numeric_limits<TPrimitiveType>::max_digits10));
			}

		public:
			TPrimitiveType GetValue(void) const
			{
				return(MValue);
			}

		public:
			virtual CString ToString(void) const override
			{
				CString											String(MValue);

				return(String);
			}

		public:
			CPrimitiveType(TPrimitiveType Value)
				: MValue(Value)
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CInt8=CPrimitiveType<int8>;
	using														CInt16=CPrimitiveType<int16>;
	using														CInt32=CPrimitiveType<int32>;
	using														CInt64=CPrimitiveType<int64>;
	using														CUInt8=CPrimitiveType<uint8>;
	using														CUInt16=CPrimitiveType<uint16>;
	using														CUInt32=CPrimitiveType<uint32>;
	using														CUInt64=CPrimitiveType<uint64>;
	using														CFloat32=CPrimitiveType<float32>;
	using														CFloat64=CPrimitiveType<float64>;
	using														CFloat80=CPrimitiveType<float80>;
	using														CSize=CPrimitiveType<Size>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------