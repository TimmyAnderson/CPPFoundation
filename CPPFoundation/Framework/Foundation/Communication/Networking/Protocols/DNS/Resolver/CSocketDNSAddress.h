//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Sockets/CSocketAddress.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketDNSAddress final : public CSocketAddress
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			static const CString								LOCAL_HOST_ADDRESS;

		private:
			CString												MDNSAddress;

		public:
			CSocketDNSAddress& operator=(const CSocketDNSAddress& Other);
			CSocketDNSAddress& operator=(CSocketDNSAddress&& Other) noexcept;
			bool operator==(const CSocketDNSAddress& Other) const;
			bool operator!=(const CSocketDNSAddress& Other) const;
			bool operator<(const CSocketDNSAddress& Other) const;

		public:
			static CSocketDNSAddress CreateLocalHostAddress(void);
			static bool ParseDNSAddress(const CString& Value, CSocketDNSAddress& Result);

		public:
			virtual CString ToString(void) const override;
			virtual bool Equals(const CSocketAddress& Other) const override;
			const CString& GetDNSAddress(void) const noexcept;

		public:
			CSocketDNSAddress(void);
			CSocketDNSAddress(const CString& DNSAddress);
			CSocketDNSAddress(CString&& DNSAddress);
			CSocketDNSAddress(const CSocketDNSAddress& Other);
			CSocketDNSAddress(CSocketDNSAddress&& Other) noexcept;
			virtual ~CSocketDNSAddress(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketDNSAddress=CSharedPointer<CSocketDNSAddress>;
	using														CCSPSocketDNSAddress=CSharedPointer<const CSocketDNSAddress>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------