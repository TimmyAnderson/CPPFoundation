//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CVector.h>
#include <Framework/Foundation/Communication/Networking/Protocols/DNS/Resolver/CSocketDNSAddress.h>
#include <Framework/Foundation/Communication/Networking/Protocols/IP/CSocketIPAddress.h>
#include "CSocketDNSResolverManagerMessageResponse.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress final : public CSocketDNSResolverManagerMessageResponse
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CSocketDNSAddress									MDNSAddress;
			CVector<CSocketIPAddress>							MIPAddresses;

		public:
			CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress& operator=(const CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress& Other);
			CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress& operator=(CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress&& Other) noexcept;

		public:
			virtual CString ToString(void) const override;

		public:
			const CSocketDNSAddress& GetDNSAddress(void) const noexcept;
			const CVector<CSocketIPAddress>& GetIPAddresses(void) const noexcept;

		public:
			CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress(CCSPSocketDNSResolverManagerMessageContext MessageContext, bool OperationSucceeded, const CSocketDNSAddress& DNSAddress, const CVector<CSocketIPAddress>& IPAddresses);
			CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress(CCSPSocketDNSResolverManagerMessageContext MessageContext, bool OperationSucceeded, const CSocketDNSAddress& DNSAddress, CVector<CSocketIPAddress>&& IPAddresses);
			CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress(const CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress& Other);
			CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress(CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress&& Other) noexcept;
			virtual ~CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress=CSharedPointer<CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress>;
	using														CCSPSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress=CSharedPointer<const CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------