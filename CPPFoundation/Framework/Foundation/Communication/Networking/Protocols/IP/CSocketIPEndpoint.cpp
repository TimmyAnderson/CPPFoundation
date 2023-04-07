//----------------------------------------------------------------------------------------------------------------------
#include "CSocketIPEndpoint.h"
#include <Framework/Foundation/Strings/CIntegerFormatter.h>
#include <Framework/Foundation/Collections/CVector.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	const Size													CSocketIPEndpoint::NUMBER_OF_IPV4_ENDPOINT_SEGMENTS=2;
	const Char													CSocketIPEndpoint::IPV4_PORT_SERPARATOR=':';
	const Char													CSocketIPEndpoint::IPV6_PORT_SERPARATOR=':';
	const Char													CSocketIPEndpoint::IPV6_ADDRESS_OPEN_BRACKET='[';
	const Char													CSocketIPEndpoint::IPV6_ADDRESS_CLOSE_BRACKET=']';
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPEndpoint::CSocketIPEndpoint(void)
		: MIPAddress(), MPort()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPEndpoint::CSocketIPEndpoint(const CSocketIPAddress& IPAddress, uint16 Port)
		: MIPAddress(IPAddress), MPort(Port)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPEndpoint::CSocketIPEndpoint(CSocketIPAddress&& IPAddress, uint16 Port)
		: MIPAddress(FUNCTION_MOVE(IPAddress)), MPort(Port)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPEndpoint::CSocketIPEndpoint(const CSocketIPEndpoint& Other)
		: MIPAddress(Other.MIPAddress), MPort(Other.MPort)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPEndpoint::CSocketIPEndpoint(CSocketIPEndpoint&& Other) noexcept
		: MIPAddress(FUNCTION_MOVE(Other.MIPAddress)), MPort(FUNCTION_MOVE(Other.MPort))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPEndpoint::~CSocketIPEndpoint(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPEndpoint& CSocketIPEndpoint::operator=(const CSocketIPEndpoint& Other)
	{
		MIPAddress=Other.MIPAddress;
		MPort=Other.MPort;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPEndpoint& CSocketIPEndpoint::operator=(CSocketIPEndpoint&& Other) noexcept
	{
		MIPAddress=FUNCTION_MOVE(Other.MIPAddress);
		MPort=FUNCTION_MOVE(Other.MPort);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketIPEndpoint::operator==(const CSocketIPEndpoint& Other) const
	{
		if (MIPAddress!=Other.MIPAddress)
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
	bool CSocketIPEndpoint::operator!=(const CSocketIPEndpoint& Other) const
	{
		return(!(*this==Other));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPEndpoint CSocketIPEndpoint::CreateLocalHostIPv4Endpoint(uint16 Port)
	{
		return(CSocketIPEndpoint(CSocketIPAddress::CreateLocalHostIPv4Address(),Port));
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPEndpoint CSocketIPEndpoint::CreateLocalHostIPv6Endpoint(uint16 Port)
	{
		return(CSocketIPEndpoint(CSocketIPAddress::CreateLocalHostIPv6Address(),Port));
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketIPEndpoint::ParseIPv4Endpoint(const CString& Value, CSocketIPEndpoint& Result)
	{
		if (Value.GetLength()==0)
		{
			return(false);
		}

		CVector<CString>										Splits=Value.Split(IPV4_PORT_SERPARATOR,false);
		CUInt16Formatter										Formatter;
		CSocketIPAddress										IPAddress;
		uint16													Port;

		if (Splits.GetLength()!=NUMBER_OF_IPV4_ENDPOINT_SEGMENTS)
		{
			return(false);
		}

		if (CSocketIPAddress::ParseIPv4Address(Splits[0],IPAddress)==false)
		{
			return(false);
		}

		if (Formatter.Parse(Splits[1],Port)==false)
		{
			return(false);
		}

		Result=CSocketIPEndpoint(IPAddress,Port);

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketIPEndpoint::ParseIPv6Endpoint(const CString& Value, CSocketIPEndpoint& Result)
	{
		if (Value.GetLength()==0)
		{
			return(false);
		}

		CUInt16Formatter										Formatter;
		CSocketIPAddress										IPAddress;
		uint16													Port;
		Size													OpenBracketPosition=Value.FindFirst(IPV6_ADDRESS_OPEN_BRACKET);

		if (OpenBracketPosition==CString::END || OpenBracketPosition!=0)
		{
			return(false);
		}

		Size													CloseBracketPosition=Value.FindFirst(IPV6_ADDRESS_CLOSE_BRACKET,OpenBracketPosition+1);

		if (CloseBracketPosition==CString::END)
		{
			return(false);
		}

		Size													PortSeparatorPosition=CloseBracketPosition+1;

		if (PortSeparatorPosition>=Value.GetLength() || Value[PortSeparatorPosition]!=IPV6_PORT_SERPARATOR)
		{
			return(false);
		}

		Size													PortPosition=PortSeparatorPosition+1;

		if (PortPosition>=Value.GetLength())
		{
			return(false);
		}

		CString													AddressPart=Value.SubString(OpenBracketPosition+1,CloseBracketPosition-OpenBracketPosition-1);

		if (CSocketIPAddress::ParseIPv6Address(AddressPart,IPAddress)==false)
		{
			return(false);
		}

		if (Formatter.Parse(Value,PortPosition,Value.GetLength(),Port)==false)
		{
			return(false);
		}

		Result=CSocketIPEndpoint(IPAddress,Port);

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketIPEndpoint::ToString(void) const
	{
		static const CString									IPV4_PORT_SERPARATOR_STRING=CString::FromChar(IPV4_PORT_SERPARATOR);
		static const CString									IPV6_ADDRESS_OPEN_BRACKET_STRING=CString::FromChar(IPV6_ADDRESS_OPEN_BRACKET);
		static const CString									IPV6_ADDRESS_CLOSE_BRACKET_STRING=CString::FromChar(IPV6_ADDRESS_CLOSE_BRACKET);
		static const CString									IPV6_PORT_SERPARATOR_STRING=CString::FromChar(IPV6_PORT_SERPARATOR);

		if (MIPAddress.GetAddressType()==ESocketIPAddressType::E_IP_V4)
		{
			CString												Address=CString::Format(MIPAddress.ToString(),IPV4_PORT_SERPARATOR_STRING,MPort);

			return(Address);
		}
		else if (MIPAddress.GetAddressType()==ESocketIPAddressType::E_IP_V6)
		{
			CString												Address=CString::Format(IPV6_ADDRESS_OPEN_BRACKET_STRING,MIPAddress.ToString(),IPV6_ADDRESS_CLOSE_BRACKET_STRING,IPV6_PORT_SERPARATOR_STRING,MPort);

			return(Address);
		}
		else
		{
			return("");
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketIPEndpoint::Equals(const CSocketEndpoint& Other) const
	{
		if (Other.IsTypeOf<CSocketIPEndpoint>()==false)
		{
			return(false);
		}

		const CSocketIPEndpoint&								TypedOther=Other.DynamicCastReference<CSocketIPEndpoint>();

		if (MIPAddress!=TypedOther.MIPAddress)
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
	const CSocketIPAddress& CSocketIPEndpoint::GetIPAddress(void) const noexcept
	{
		return(MIPAddress);
	}
//----------------------------------------------------------------------------------------------------------------------
	uint16 CSocketIPEndpoint::GetPort(void) const noexcept
	{
		return(MPort);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------