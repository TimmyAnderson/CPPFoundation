//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPAddress.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPAddress::CSocketTCPAddress(void)
		: MIPEndpoint()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPAddress::CSocketTCPAddress(const CSocketIPEndpoint& IPEndpoint)
		: MIPEndpoint(IPEndpoint)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPAddress::CSocketTCPAddress(CSocketIPEndpoint&& IPEndpoint)
		: MIPEndpoint(FUNCTION_MOVE(IPEndpoint))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPAddress::CSocketTCPAddress(const CSocketTCPAddress& Other)
		: MIPEndpoint(Other.MIPEndpoint)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPAddress::CSocketTCPAddress(CSocketTCPAddress&& Other)
		: MIPEndpoint(FUNCTION_MOVE(Other.MIPEndpoint))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPAddress::~CSocketTCPAddress(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPAddress& CSocketTCPAddress::operator=(const CSocketTCPAddress& Other)
	{
		MIPEndpoint=Other.MIPEndpoint;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPAddress& CSocketTCPAddress::operator=(CSocketTCPAddress&& Other)
	{
		MIPEndpoint=FUNCTION_MOVE(Other.MIPEndpoint);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketTCPAddress::operator==(const CSocketTCPAddress& Other) const
	{
		if (MIPEndpoint!=Other.MIPEndpoint)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketTCPAddress::operator!=(const CSocketTCPAddress& Other) const
	{
		return(!(*this==Other));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketTCPAddress::ParseIPv4TCPAddress(const CString& Value, CSocketTCPAddress& Result)
	{
		CSocketIPEndpoint										IPEndpoint;

		if (CSocketIPEndpoint::ParseIPv4Endpoint(Value,IPEndpoint)==false)
		{
			return(false);
		}

		Result=CSocketTCPAddress(IPEndpoint);

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketTCPAddress::ParseIPv6TCPAddress(const CString& Value, CSocketTCPAddress& Result)
	{
		CSocketIPEndpoint										IPEndpoint;

		if (CSocketIPEndpoint::ParseIPv6Endpoint(Value,IPEndpoint)==false)
		{
			return(false);
		}

		Result=CSocketTCPAddress(IPEndpoint);

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketTCPAddress::ToString(void) const
	{
		return(MIPEndpoint.ToString());
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketTCPAddress::Equals(const CSocketAddress& Other) const
	{
		if (Other.IsTypeOf<CSocketTCPAddress>()==false)
		{
			return(false);
		}

		const CSocketTCPAddress&								TypedOther=Other.DynamicCastReference<CSocketTCPAddress>();

		return((*this==TypedOther));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CSocketIPEndpoint& CSocketTCPAddress::GetIPEndpoint(void) const noexcept
	{
		return(MIPEndpoint);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------