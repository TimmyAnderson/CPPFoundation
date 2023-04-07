//----------------------------------------------------------------------------------------------------------------------
#include "CSocketUDPAddress.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPAddress::CSocketUDPAddress(void)
		: MIPEndpoint()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPAddress::CSocketUDPAddress(const CSocketIPEndpoint& IPEndpoint)
		: MIPEndpoint(IPEndpoint)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPAddress::CSocketUDPAddress(CSocketIPEndpoint&& IPEndpoint)
		: MIPEndpoint(FUNCTION_MOVE(IPEndpoint))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPAddress::CSocketUDPAddress(const CSocketUDPAddress& Other)
		: MIPEndpoint(Other.MIPEndpoint)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPAddress::CSocketUDPAddress(CSocketUDPAddress&& Other)
		: MIPEndpoint(FUNCTION_MOVE(Other.MIPEndpoint))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPAddress::~CSocketUDPAddress(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPAddress& CSocketUDPAddress::operator=(const CSocketUDPAddress& Other)
	{
		MIPEndpoint=Other.MIPEndpoint;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPAddress& CSocketUDPAddress::operator=(CSocketUDPAddress&& Other)
	{
		MIPEndpoint=FUNCTION_MOVE(Other.MIPEndpoint);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketUDPAddress::operator==(const CSocketUDPAddress& Other) const
	{
		if (MIPEndpoint!=Other.MIPEndpoint)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketUDPAddress::operator!=(const CSocketUDPAddress& Other) const
	{
		return(!(*this==Other));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketUDPAddress::ParseIPv4UDPAddress(const CString& Value, CSocketUDPAddress& Result)
	{
		CSocketIPEndpoint										IPEndpoint;

		if (CSocketIPEndpoint::ParseIPv4Endpoint(Value,IPEndpoint)==false)
		{
			return(false);
		}

		Result=CSocketUDPAddress(IPEndpoint);

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketUDPAddress::ParseIPv6UDPAddress(const CString& Value, CSocketUDPAddress& Result)
	{
		CSocketIPEndpoint										IPEndpoint;

		if (CSocketIPEndpoint::ParseIPv6Endpoint(Value,IPEndpoint)==false)
		{
			return(false);
		}

		Result=CSocketUDPAddress(IPEndpoint);

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketUDPAddress::ToString(void) const
	{
		return(MIPEndpoint.ToString());
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketUDPAddress::Equals(const CSocketAddress& Other) const
	{
		if (Other.IsTypeOf<CSocketUDPAddress>()==false)
		{
			return(false);
		}

		const CSocketUDPAddress&								TypedOther=Other.DynamicCastReference<CSocketUDPAddress>();

		return((*this==TypedOther));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CSocketIPEndpoint& CSocketUDPAddress::GetIPEndpoint(void) const noexcept
	{
		return(MIPEndpoint);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------