//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CVector.h>
#include <Framework/Foundation/Communication/Networking/Protocols/DNS/Resolver/CSocketDNSAddress.h>
#include <Framework/Foundation/Communication/Networking/Protocols/DNS/Resolver/ESocketDNSAddressType.h>
#include <Framework/Foundation/Communication/Networking/Protocols/DNS/Resolver/ESocketDNSProtocolType.h>
#include <Framework/Foundation/Communication/Networking/Protocols/IP/CSocketIPAddress.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Platform
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketDNSHelper final
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			static CPPFoundation::Foundation::CVector<CPPFoundation::Foundation::CSocketIPAddress> ConvertDNSAddressToIPAddress(const CPPFoundation::Foundation::CSocketDNSAddress& DNSAddress, CPPFoundation::Foundation::ESocketDNSAddressType AddressType, CPPFoundation::Foundation::ESocketDNSProtocolType ProtocolType);
			static CPPFoundation::Foundation::CSocketDNSAddress ConvertIPAddressToDNSAddress(const CPPFoundation::Foundation::CSocketIPAddress& IPAddress, bool DNSAddressRequired);
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------