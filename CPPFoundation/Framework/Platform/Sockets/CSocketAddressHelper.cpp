//----------------------------------------------------------------------------------------------------------------------
#include "CSocketAddressHelper.h"
#if defined(PLATFORM_WINDOWS)
#elif defined(PLATFORM_LINUX)
#else
#error UNSUPPORTED PLATFORM !
#endif
#include <cstring>
#include <Framework/Foundation/Exceptions/CArgumentException.h>
#include <Framework/Foundation/Parsing/CParserHelper.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Platform
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace std;
	using namespace CPPFoundation::Foundation;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	sockaddr_in CSocketAddressHelper::ConvertToPlatformAddressIPv4(const CSocketIPAddress& Address)
	{
		if (Address.GetAddressType()!=ESocketIPAddressType::E_IP_V4)
		{
			throw(CArgumentException("Can't CONVERT IPv4 ADDRESS ! INVALID ADDRESS TYPE !"));
		}
		
#if defined(PLATFORM_WINDOWS)
		uint32													DeserializedAddress=CParserHelper::DeserializeUInt32(Address.GetAddress(),0,EParserEndianness::E_BIG_ENDIAN);
		sockaddr_in												PlatformAddress;

		memset(&PlatformAddress,0,sizeof(PlatformAddress));

		PlatformAddress.sin_family=AF_INET;
		PlatformAddress.sin_port=0;
		PlatformAddress.sin_addr.s_addr=htonl(static_cast<uint32_t>(DeserializedAddress));

		return(PlatformAddress);
#elif defined(PLATFORM_LINUX)
		uint32													DeserializedAddress=CParserHelper::DeserializeUInt32(Address.GetAddress(),0,EParserEndianness::E_BIG_ENDIAN);
		sockaddr_in												PlatformAddress;

		memset(&PlatformAddress,0,sizeof(PlatformAddress));

		PlatformAddress.sin_family=AF_INET;
		PlatformAddress.sin_port=0;
		PlatformAddress.sin_addr.s_addr=htonl(static_cast<uint32_t>(DeserializedAddress));

		return(PlatformAddress);
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	sockaddr_in6 CSocketAddressHelper::ConvertToPlatformAddressIPv6(const CSocketIPAddress& Address)
	{
		if (Address.GetAddressType()!=ESocketIPAddressType::E_IP_V6)
		{
			throw(CArgumentException("Can't CONVERT IPv6 ADDRESS ! INVALID ADDRESS TYPE !"));
		}

		if (sizeof(in6_addr)!=Address.GetAddress().GetLength())
		{
			throw(CArgumentException("Can't CONVERT IPv6 ADDRESS ! INVALID ADDRESS SIZE !"));
		}

#if defined(PLATFORM_WINDOWS)
		sockaddr_in6											PlatformAddress;
		
		memset(&PlatformAddress,0,sizeof(PlatformAddress));

		PlatformAddress.sin6_family=AF_INET6;
		PlatformAddress.sin6_port=0;
		PlatformAddress.sin6_flowinfo=0;

		for(Size Index=0;Index<Address.GetAddress().GetLength();Index++)
		{
			PlatformAddress.sin6_addr.s6_addr[Index]=static_cast<UCHAR>(Address.GetAddress()[Index]);
		}
		
		return(PlatformAddress);
#elif defined(PLATFORM_LINUX)
		sockaddr_in6											PlatformAddress;

		memset(&PlatformAddress,0,sizeof(PlatformAddress));

		PlatformAddress.sin6_family=AF_INET6;
		PlatformAddress.sin6_port=0;
		PlatformAddress.sin6_flowinfo=0;

		for(Size Index=0;Index<Address.GetAddress().GetLength();Index++)
		{
			PlatformAddress.sin6_addr.s6_addr[Index]=static_cast<UCharacter>(Address.GetAddress()[Index]);
		}

		PlatformAddress.sin6_scope_id=0;

		return(PlatformAddress);
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPAddress CSocketAddressHelper::ConvertFromPlatformAddressIPv4(const sockaddr_in& PlatformAddress)
	{
#if defined(PLATFORM_WINDOWS)
		if (PlatformAddress.sin_family!=AF_INET)
		{
			throw(CArgumentException("Can't CONVERT IPv4 ADDRESS ! INVALID ADDRESS TYPE !"));
		}

		CByteBuffer												Buffer({0,0,0,0});

		CParserHelper::SerializeUInt32(Buffer,ntohl(PlatformAddress.sin_addr.S_un.S_addr),0,EParserEndianness::E_BIG_ENDIAN);

		CSocketIPAddress										Address(Buffer);

		return(Address);
#elif defined(PLATFORM_LINUX)
		if (PlatformAddress.sin_family!=AF_INET)
		{
			throw(CArgumentException("Can't CONVERT IPv4 ADDRESS ! INVALID ADDRESS TYPE !"));
		}

		CByteBuffer												Buffer({0,0,0,0});

		CParserHelper::SerializeUInt32(Buffer,ntohl(PlatformAddress.sin_addr.s_addr),0,EParserEndianness::E_BIG_ENDIAN);

		CSocketIPAddress										Address(Buffer);

		return(Address);
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPAddress CSocketAddressHelper::ConvertFromPlatformAddressIPv6(const sockaddr_in6& PlatformAddress)
	{
#if defined(PLATFORM_WINDOWS)
		if (PlatformAddress.sin6_family!=AF_INET6)
		{
			throw(CArgumentException("Can't CONVERT IPv6 ADDRESS ! INVALID ADDRESS TYPE !"));
		}

		CByteBuffer												Buffer;
		
		for(Size Index=0;Index<sizeof(PlatformAddress.sin6_addr.s6_addr);Index++)
		{
			Buffer.Add(static_cast<uint8>(PlatformAddress.sin6_addr.s6_addr[Index]));
		}

		CSocketIPAddress										Address(Buffer);

		return(Address);
#elif defined(PLATFORM_LINUX)
		if (PlatformAddress.sin6_family!=AF_INET6)
		{
			throw(CArgumentException("Can't CONVERT IPv6 ADDRESS ! INVALID ADDRESS TYPE !"));
		}

		CByteBuffer												Buffer;

		for(Size Index=0;Index<sizeof(PlatformAddress.sin6_addr.s6_addr);Index++)
		{
			Buffer.Add(static_cast<uint8>(PlatformAddress.sin6_addr.s6_addr[Index]));
		}

		CSocketIPAddress										Address(Buffer);

		return(Address);
#else
#error UNSUPPORTED PLATFORM !
#endif
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------