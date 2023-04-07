//----------------------------------------------------------------------------------------------------------------------
#include "CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress.h"
#include "CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress::CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress(CCSPSocketDNSResolverManagerMessageContext MessageContext, const CSocketIPAddress& IPAddress, bool DNSAddressRequired)
		: CSocketDNSResolverManagerMessageRequest(MessageContext), MIPAddress(IPAddress), MDNSAddressRequired(DNSAddressRequired)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress::CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress(CCSPSocketDNSResolverManagerMessageContext MessageContext, CSocketIPAddress&& IPAddress, bool DNSAddressRequired)
		: CSocketDNSResolverManagerMessageRequest(MessageContext), MIPAddress(FUNCTION_MOVE(IPAddress)), MDNSAddressRequired(DNSAddressRequired)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress::CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress(const CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress& Other)
		: CSocketDNSResolverManagerMessageRequest(Other), MIPAddress(Other.MIPAddress), MDNSAddressRequired(Other.MDNSAddressRequired)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress::CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress(CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress&& Other)
		: CSocketDNSResolverManagerMessageRequest(FUNCTION_MOVE(Other)), MIPAddress(FUNCTION_MOVE(Other.MIPAddress)), MDNSAddressRequired(Other.MDNSAddressRequired)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress::~CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress& CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress::operator=(const CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress& Other)
	{
		CSocketDNSResolverManagerMessageRequest::operator=(Other);

		MIPAddress=Other.MIPAddress;
		MDNSAddressRequired=Other.MDNSAddressRequired;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress& CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress::operator=(CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress&& Other)
	{
		CSocketDNSResolverManagerMessageRequest::operator=(FUNCTION_MOVE(Other));

		MIPAddress=FUNCTION_MOVE(Other.MIPAddress);
		MDNSAddressRequired=Other.MDNSAddressRequired;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress::ToString(void) const
	{
		return(CString::Format("DNS RESOLVER MESSAGE REQUEST IP ADDRESS to DNS ADDRESS - MESSAGE CONTEXT [",GetMessageContext(),"] IP ADDRESS [",MIPAddress,"] DNS ADDRESS REQUIRED [",MDNSAddressRequired,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketDNSResolverManagerMessageResponse CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress::CreateErrorResponse(void) const
	{
		return(CCSPSocketDNSResolverManagerMessageResponse(new CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress(GetMessageContext(),false,CSocketDNSAddress())));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CSocketIPAddress& CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress::GetIPAddress(void) const noexcept
	{
		return(MIPAddress);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketDNSResolverManagerMessageRequestIPAddressToDNSAddress::GetDNSAddressRequired(void) const noexcept
	{
		return(MDNSAddressRequired);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------