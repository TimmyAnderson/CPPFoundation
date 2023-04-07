//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CVector.h>
#include <Framework/Foundation/Communication/Networking/Protocols/IP/CSocketIPAddress.h>
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
#include "CSocketDNSAddress.h"
#include "ESocketDNSAddressType.h"
#include "ESocketDNSProtocolType.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketDNSResolver final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CVector<CSocketIPAddress> ConvertDNSAddressToIPAddress(const CSocketDNSAddress& DNSAddress, ESocketDNSAddressType AddressType, ESocketDNSProtocolType ProtocolType);
			CSocketDNSAddress ConvertIPAddressToDNSAddress(const CSocketIPAddress& IPAddress, bool DNSAddressRequired);

		public:
			CSocketDNSResolver(void);
			virtual ~CSocketDNSResolver(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketDNSResolver=CSharedPointer<CSocketDNSResolver>;
	using														CCSPSocketDNSResolver=CSharedPointer<const CSocketDNSResolver>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------