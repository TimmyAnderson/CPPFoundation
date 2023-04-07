//----------------------------------------------------------------------------------------------------------------------
#include "CSocketPlatformLibrary.h"
#if defined(PLATFORM_WINDOWS)
#define _CRTDBG_MAP_ALLOC
#include <Winsock2.h>
#pragma warning( disable : 4996)
#elif defined(PLATFORM_LINUX)
#else
#error UNSUPPORTED PLATFORM !
#endif
#include <Framework/Foundation/Exceptions/CSocketException.h>
#include "CSocketError.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Platform
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace CPPFoundation::Foundation;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSocketPlatformLibrary::InitializeSocketLibrary(void)
	{
#if defined(PLATFORM_WINDOWS)
		WSADATA													Data;
		int														Result=WSAStartup(MAKEWORD(2,2),&Data);

		if (Result!=0)
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			throw(CSocketException("Can't INITIALIZE SOCKET LIBRARY !",ErrorCode,SocketExceptionCode));
		}
#elif defined(PLATFORM_LINUX)
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketPlatformLibrary::UninitializeSocketLibrary(void)
	{
#if defined(PLATFORM_WINDOWS)
		int														Result=WSACleanup();

		if (Result!=0)
		{
			int32												ErrorCode=CSocketError::SocketGetLastErrorCode();
			ESocketExceptionCode								SocketExceptionCode=CSocketError::GetSocketExceptionCode(ErrorCode);

			throw(CSocketException("Can't UNINITIALIZE SOCKET LIBRARY !",ErrorCode,SocketExceptionCode));
		}
#elif defined(PLATFORM_LINUX)
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------