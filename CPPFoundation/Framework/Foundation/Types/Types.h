//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#if defined(PLATFORM_WINDOWS)
#define _CRTDBG_MAP_ALLOC
#pragma warning(default:4061)
#pragma warning(disable:4250)
//#pragma warning(default:4365)
#pragma warning(disable:26444)
#include <stdlib.h>
#include <crtdbg.h>
#endif
//----------------------------------------------------------------------------------------------------------------------
#include <cstdint>
#include <cstddef>
#include <type_traits>
//----------------------------------------------------------------------------------------------------------------------
#if !defined(MACRO_VARIABLE_TO_STRING)
#define MACRO_VARIABLE_TO_STRING(Variable) (void(Variable),#Variable)
#endif
//----------------------------------------------------------------------------------------------------------------------
#if !defined(MACRO_FUNCTION_TO_STRING)
#define MACRO_FUNCTION_TO_STRING(Function) (void(&Function),#Function)
#endif
//----------------------------------------------------------------------------------------------------------------------
#if !defined(MACRO_METHOD_TO_STRING)
#define MACRO_METHOD_TO_STRING(ClassName,Method) (void(&ClassName::Method),#Method)
#endif
//----------------------------------------------------------------------------------------------------------------------
#if !defined(MACRO_TYPE_TO_STRING)
#define MACRO_TYPE_TO_STRING(Type) (void(sizeof(Type)),#Type)
#endif
//----------------------------------------------------------------------------------------------------------------------
using															int8=int8_t;
using															int16=int16_t;
using															int32=int32_t;
using															int64=int64_t;
using															intmax=intmax_t;
//----------------------------------------------------------------------------------------------------------------------
using															uint8=uint8_t;
using															uint16=uint16_t;
using															uint32=uint32_t;
using															uint64=uint64_t;
using															uintmax=uintmax_t;
//----------------------------------------------------------------------------------------------------------------------
using															float32=float;
using															float64=double;
using															float80=long double;
//----------------------------------------------------------------------------------------------------------------------
using															Size=std::size_t;
//----------------------------------------------------------------------------------------------------------------------
using															IntPointer=std::intptr_t;
using															UIntPointer=std::uintptr_t;
//----------------------------------------------------------------------------------------------------------------------
using															Char=char;
using															SCharacter=signed char;
using															UCharacter=unsigned char;
using															WideChar=wchar_t;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
inline constexpr typename std::remove_reference<TType>::type&& FUNCTION_MOVE(TType&& Parameter) noexcept
{
	return(static_cast<typename std::remove_reference<TType>::type&&>(Parameter));
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
inline constexpr TType&& FUNCTION_FORWARD(typename std::remove_reference<TType>::type& Parameter) noexcept
{
	return(static_cast<TType&&>(Parameter));
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
inline constexpr TType&& FUNCTION_FORWARD(typename std::remove_reference<TType>::type&& Parameter) noexcept
{
	static_assert(std::is_lvalue_reference<TType>::value==false,"BAD FORWARD CALL !");

	return(static_cast<TType&&>(Parameter));
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, Size SIZE>
inline constexpr Size FUNCTION_GET_NUMBER_OF_ARRAY_ITEMS(TType (&)[SIZE])
{
	return(SIZE);
}
//----------------------------------------------------------------------------------------------------------------------