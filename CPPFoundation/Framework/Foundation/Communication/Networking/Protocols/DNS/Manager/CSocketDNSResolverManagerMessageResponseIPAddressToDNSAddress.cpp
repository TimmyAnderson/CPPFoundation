//----------------------------------------------------------------------------------------------------------------------
#include "CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress::CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress(CCSPSocketDNSResolverManagerMessageContext MessageContext, bool OperationSucceeded, const CSocketDNSAddress& DNSAddress)
		: CSocketDNSResolverManagerMessageResponse(MessageContext,OperationSucceeded), MDNSAddress(DNSAddress)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress::CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress(CCSPSocketDNSResolverManagerMessageContext MessageContext, bool OperationSucceeded, CSocketDNSAddress&& DNSAddress)
		: CSocketDNSResolverManagerMessageResponse(MessageContext,OperationSucceeded), MDNSAddress(FUNCTION_MOVE(DNSAddress))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress::CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress(const CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress& Other)
		: CSocketDNSResolverManagerMessageResponse(Other), MDNSAddress(Other.MDNSAddress)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress::CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress(CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress&& Other) noexcept
		: CSocketDNSResolverManagerMessageResponse(FUNCTION_MOVE(Other)), MDNSAddress(FUNCTION_MOVE(Other.MDNSAddress))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress::~CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress& CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress::operator=(const CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress& Other)
	{
		CSocketDNSResolverManagerMessageResponse::operator=(Other);

		MDNSAddress=Other.MDNSAddress;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress& CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress::operator=(CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress&& Other) noexcept
	{
		CSocketDNSResolverManagerMessageResponse::operator=(FUNCTION_MOVE(Other));

		MDNSAddress=FUNCTION_MOVE(Other.MDNSAddress);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress::ToString(void) const
	{
		return(CString::Format("DNS RESOLVER MESSAGE RESPONSE IP ADDRESS to DNS ADDRESS - MESSAGE CONTEXT [",GetMessageContext(),"] OPERATION SUCCEEDED [",GetOperationSucceeded(),"] DNS ADDRESS [",MDNSAddress,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CSocketDNSAddress& CSocketDNSResolverManagerMessageResponseIPAddressToDNSAddress::GetDNSAddress(void) const noexcept
	{
		return(MDNSAddress);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------