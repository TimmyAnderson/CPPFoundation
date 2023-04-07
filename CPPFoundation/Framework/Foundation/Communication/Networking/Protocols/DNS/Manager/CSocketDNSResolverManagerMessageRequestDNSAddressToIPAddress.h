//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Protocols/DNS/Resolver/CSocketDNSAddress.h>
#include <Framework/Foundation/Communication/Networking/Protocols/DNS/Resolver/ESocketDNSAddressType.h>
#include <Framework/Foundation/Communication/Networking/Protocols/DNS/Resolver/ESocketDNSProtocolType.h>
#include "CSocketDNSResolverManagerMessageRequest.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress final : public CSocketDNSResolverManagerMessageRequest
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CSocketDNSAddress									MDNSAddress;
			ESocketDNSAddressType								MAddressType;
			ESocketDNSProtocolType								MProtocolType;

		public:
			CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress& operator=(const CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress& Other);
			CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress& operator=(CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress&& Other);

		public:
			virtual CString ToString(void) const override;
			virtual CCSPSocketDNSResolverManagerMessageResponse CreateErrorResponse(void) const override;

		public:
			const CSocketDNSAddress& GetDNSAddress(void) const noexcept;
			ESocketDNSAddressType GetAddressType(void) const noexcept;
			ESocketDNSProtocolType GetProtocolType(void) const noexcept;

		public:
			CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress(CCSPSocketDNSResolverManagerMessageContext MessageContext, const CSocketDNSAddress& DNSAddress, ESocketDNSAddressType AddressType, ESocketDNSProtocolType ProtocolType);
			CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress(CCSPSocketDNSResolverManagerMessageContext MessageContext, CSocketDNSAddress&& DNSAddress, ESocketDNSAddressType AddressType, ESocketDNSProtocolType ProtocolType);
			CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress(const CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress& Other);
			CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress(CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress&& Other);
			virtual ~CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress=CSharedPointer<CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress>;
	using														CCSPSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress=CSharedPointer<const CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------