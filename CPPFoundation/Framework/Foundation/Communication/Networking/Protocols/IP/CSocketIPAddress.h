//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CByteBuffer.h>
#include <Framework/Foundation/Communication/Networking/Sockets/CSocketAddress.h>
#include "ESocketIPAddressType.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketIPAddress final : public CSocketAddress
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			static const Size									MAXIMUM_NUMBER_OF_IPV6_ADDRESS_DOUBLE_SEPARATOR_SEGMENTS;
			static const Size									IPV6_ADDRESS_MAXIMUM_SEGMENT_SIZE;
			static const Char									IPV4_ADDRESS_SERPARATOR;
			static const Char									IPV6_ADDRESS_SERPARATOR;
			static const CString								IPV6_ADDRESS_DOUBLE_SERPARATOR;

		private:
			static const CSocketIPAddress						LOCAL_HOST_IPV4_ADDRESS;
			static const CSocketIPAddress						LOCAL_HOST_IPV6_ADDRESS;

		public:
			static const Size									IPV4_ADDRESS_LENGTH_IN_BYTES;
			static const Size									IPV6_ADDRESS_LENGTH_IN_BYTES;

		private:
			ESocketIPAddressType								MAddressType;
			CByteBuffer											MAddress;

		public:
			CSocketIPAddress& operator=(const CSocketIPAddress& Other);
			CSocketIPAddress& operator=(CSocketIPAddress&& Other) noexcept;
			bool operator==(const CSocketIPAddress& Other) const;
			bool operator!=(const CSocketIPAddress& Other) const;

		public:
			static CSocketIPAddress CreateLocalHostIPv4Address(void);
			static CSocketIPAddress CreateLocalHostIPv6Address(void);
			static bool ParseIPv4Address(const CString& Value, CSocketIPAddress& Result);
			static bool ParseIPv6Address(const CString& Value, CSocketIPAddress& Result);

		public:
			virtual CString ToString(void) const override;
			virtual bool Equals(const CSocketAddress& Other) const override;
			ESocketIPAddressType GetAddressType(void) const noexcept;
			const CByteBuffer& GetAddress(void) const noexcept;

		public:
			CSocketIPAddress(void);
			CSocketIPAddress(uint8 AddressSegment1, uint8 AddressSegment2, uint8 AddressSegment3, uint8 AddressSegment4);
			CSocketIPAddress(const CByteBuffer& Address);
			CSocketIPAddress(CByteBuffer&& Address);
			CSocketIPAddress(const CSocketIPAddress& Other);
			CSocketIPAddress(CSocketIPAddress&& Other) noexcept;
			virtual ~CSocketIPAddress(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketIPAddress=CSharedPointer<CSocketIPAddress>;
	using														CCSPSocketIPAddress=CSharedPointer<const CSocketIPAddress>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------