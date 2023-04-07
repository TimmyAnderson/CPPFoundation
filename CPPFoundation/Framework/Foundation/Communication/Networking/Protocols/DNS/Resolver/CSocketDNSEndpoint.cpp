//----------------------------------------------------------------------------------------------------------------------
#include "CSocketDNSEndpoint.h"
#include <Framework/Foundation/Strings/CIntegerFormatter.h>
#include <Framework/Foundation/Collections/CVector.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	const Size													CSocketDNSEndpoint::NUMBER_OF_DNS_ENDPOINT_SEGMENTS=2;
	const Char													CSocketDNSEndpoint::DNS_ADDRESS_PORT_SERPARATOR=':';
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSEndpoint::CSocketDNSEndpoint(void)
		: MDNSAddress(), MPort()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSEndpoint::CSocketDNSEndpoint(const CSocketDNSAddress& DNSAddress, uint16 Port)
		: MDNSAddress(DNSAddress), MPort(Port)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSEndpoint::CSocketDNSEndpoint(CSocketDNSAddress&& DNSAddress, uint16 Port)
		: MDNSAddress(FUNCTION_MOVE(DNSAddress)), MPort(Port)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSEndpoint::CSocketDNSEndpoint(const CSocketDNSEndpoint& Other)
		: MDNSAddress(Other.MDNSAddress), MPort(Other.MPort)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSEndpoint::CSocketDNSEndpoint(CSocketDNSEndpoint&& Other) noexcept
		: MDNSAddress(FUNCTION_MOVE(Other.MDNSAddress)), MPort(FUNCTION_MOVE(Other.MPort))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSEndpoint::~CSocketDNSEndpoint(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSEndpoint& CSocketDNSEndpoint::operator=(const CSocketDNSEndpoint& Other)
	{
		MDNSAddress=Other.MDNSAddress;
		MPort=Other.MPort;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSEndpoint& CSocketDNSEndpoint::operator=(CSocketDNSEndpoint&& Other) noexcept
	{
		MDNSAddress=FUNCTION_MOVE(Other.MDNSAddress);
		MPort=FUNCTION_MOVE(Other.MPort);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketDNSEndpoint::operator==(const CSocketDNSEndpoint& Other) const
	{
		if (MDNSAddress!=Other.MDNSAddress)
		{
			return(false);
		}

		if (MPort!=Other.MPort)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketDNSEndpoint::operator!=(const CSocketDNSEndpoint& Other) const
	{
		return(!(*this==Other));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSEndpoint CSocketDNSEndpoint::CreateLocalHostEndpoint(uint16 Port)
	{
		return(CSocketDNSEndpoint(CSocketDNSAddress::CreateLocalHostAddress(),Port));
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketDNSEndpoint::ParseDNSEndpoint(const CString& Value, CSocketDNSEndpoint& Result)
	{
		if (Value.GetLength()==0)
		{
			return(false);
		}

		CVector<CString>										Splits=Value.Split(DNS_ADDRESS_PORT_SERPARATOR,false);
		CUInt16Formatter										Formatter;
		CSocketDNSAddress										DNSAddress=Splits[0];
		uint16													Port;

		if (Splits.GetLength()!=NUMBER_OF_DNS_ENDPOINT_SEGMENTS)
		{
			return(false);
		}

		if (Formatter.Parse(Splits[1],Port)==false)
		{
			return(false);
		}

		Result=CSocketDNSEndpoint(DNSAddress,Port);

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketDNSEndpoint::ToString(void) const
	{
		static const CString									DNS_ADDRESS_PORT_SERPARATOR_STRING=CString::FromChar(DNS_ADDRESS_PORT_SERPARATOR);

		CString													Address=CString::Format(MDNSAddress.ToString(),DNS_ADDRESS_PORT_SERPARATOR_STRING,MPort);

		return(Address);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketDNSEndpoint::Equals(const CSocketEndpoint& Other) const
	{
		if (Other.IsTypeOf<CSocketDNSEndpoint>()==false)
		{
			return(false);
		}

		const CSocketDNSEndpoint&								TypedOther=Other.DynamicCastReference<CSocketDNSEndpoint>();

		if (MDNSAddress!=TypedOther.MDNSAddress)
		{
			return(false);
		}

		if (MPort!=TypedOther.MPort)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CSocketDNSAddress& CSocketDNSEndpoint::GetDNSAddress(void) const noexcept
	{
		return(MDNSAddress);
	}
//----------------------------------------------------------------------------------------------------------------------
	uint16 CSocketDNSEndpoint::GetPort(void) const noexcept
	{
		return(MPort);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------