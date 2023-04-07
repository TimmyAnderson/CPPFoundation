//----------------------------------------------------------------------------------------------------------------------
#include "CSocketDNSAddress.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	const CString												CSocketDNSAddress::LOCAL_HOST_ADDRESS("locahost");
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSAddress::CSocketDNSAddress(void)
		: MDNSAddress()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSAddress::CSocketDNSAddress(const CString& DNSAddress)
		: MDNSAddress(DNSAddress)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSAddress::CSocketDNSAddress(CString&& DNSAddress)
		: MDNSAddress(FUNCTION_MOVE(DNSAddress))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSAddress::CSocketDNSAddress(const CSocketDNSAddress& Other)
		: MDNSAddress(Other.MDNSAddress)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSAddress::CSocketDNSAddress(CSocketDNSAddress&& Other) noexcept
		: MDNSAddress(FUNCTION_MOVE(Other.MDNSAddress))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSAddress::~CSocketDNSAddress(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSAddress& CSocketDNSAddress::operator=(const CSocketDNSAddress& Other)
	{
		MDNSAddress=Other.MDNSAddress;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSAddress& CSocketDNSAddress::operator=(CSocketDNSAddress&& Other) noexcept
	{
		MDNSAddress=FUNCTION_MOVE(Other.MDNSAddress);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketDNSAddress::operator==(const CSocketDNSAddress& Other) const
	{
		if (MDNSAddress!=Other.MDNSAddress)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketDNSAddress::operator!=(const CSocketDNSAddress& Other) const
	{
		return(!(*this==Other));
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketDNSAddress::operator<(const CSocketDNSAddress& Other) const
	{
		return(MDNSAddress<Other.MDNSAddress);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSAddress CSocketDNSAddress::CreateLocalHostAddress(void)
	{
		return(CSocketDNSAddress(LOCAL_HOST_ADDRESS));
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketDNSAddress::ParseDNSAddress(const CString& Value, CSocketDNSAddress& Result)
	{
		Result=CSocketDNSAddress(Value);

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketDNSAddress::ToString(void) const
	{
		return(MDNSAddress.ToString());
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketDNSAddress::Equals(const CSocketAddress& Other) const
	{
		if (Other.IsTypeOf<CSocketDNSAddress>()==false)
		{
			return(false);
		}

		const CSocketDNSAddress&							TypedOther=Other.DynamicCastReference<CSocketDNSAddress>();

		return((*this==TypedOther));
	}
//----------------------------------------------------------------------------------------------------------------------
	const CString& CSocketDNSAddress::GetDNSAddress(void) const noexcept
	{
		return(MDNSAddress);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------