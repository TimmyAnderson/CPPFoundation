//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#if defined(PLATFORM_WINDOWS)
#include <Winsock2.h>
#include <Ws2ipdef.h>
#elif defined(PLATFORM_LINUX)
#include <sys/socket.h>
#include <netinet/ip.h>
#else
#error UNSUPPORTED PLATFORM !
#endif
#include <Framework/Foundation/Communication/Networking/Protocols/IP/CSocketIPAddress.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Platform
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketAddressHelper final
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			static sockaddr_in ConvertToPlatformAddressIPv4(const CPPFoundation::Foundation::CSocketIPAddress& Address);
			static sockaddr_in6 ConvertToPlatformAddressIPv6(const CPPFoundation::Foundation::CSocketIPAddress& Address);
			static CPPFoundation::Foundation::CSocketIPAddress ConvertFromPlatformAddressIPv4(const sockaddr_in& PlatformAddress);
			static CPPFoundation::Foundation::CSocketIPAddress ConvertFromPlatformAddressIPv6(const sockaddr_in6& PlatformAddress);
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------