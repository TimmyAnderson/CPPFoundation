//----------------------------------------------------------------------------------------------------------------------
#include "CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress.h"
#include "CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress::CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress(CCSPSocketDNSResolverManagerMessageContext MessageContext, const CSocketDNSAddress& DNSAddress, ESocketDNSAddressType AddressType, ESocketDNSProtocolType ProtocolType)
		: CSocketDNSResolverManagerMessageRequest(MessageContext), MDNSAddress(DNSAddress), MAddressType(AddressType), MProtocolType(ProtocolType)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress::CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress(CCSPSocketDNSResolverManagerMessageContext MessageContext, CSocketDNSAddress&& DNSAddress, ESocketDNSAddressType AddressType, ESocketDNSProtocolType ProtocolType)
		: CSocketDNSResolverManagerMessageRequest(MessageContext), MDNSAddress(FUNCTION_MOVE(DNSAddress)), MAddressType(AddressType), MProtocolType(ProtocolType)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress::CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress(const CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress& Other)
		: CSocketDNSResolverManagerMessageRequest(Other), MDNSAddress(Other.MDNSAddress), MAddressType(Other.MAddressType), MProtocolType(Other.MProtocolType)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress::CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress(CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress&& Other)
		: CSocketDNSResolverManagerMessageRequest(FUNCTION_MOVE(Other)), MDNSAddress(FUNCTION_MOVE(Other.MDNSAddress)), MAddressType(Other.MAddressType), MProtocolType(Other.MProtocolType)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress::~CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress& CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress::operator=(const CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress& Other)
	{
		CSocketDNSResolverManagerMessageRequest::operator=(Other);

		MDNSAddress=Other.MDNSAddress;
		MAddressType=Other.MAddressType;
		MProtocolType=Other.MProtocolType;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress& CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress::operator=(CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress&& Other)
	{
		CSocketDNSResolverManagerMessageRequest::operator=(FUNCTION_MOVE(Other));

		MDNSAddress=FUNCTION_MOVE(Other.MDNSAddress);
		MAddressType=Other.MAddressType;
		MProtocolType=Other.MProtocolType;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress::ToString(void) const
	{
		return(CString::Format("DNS RESOLVER MESSAGE REQUEST DNS ADDRESS to IP ADDRESS - MESSAGE CONTEXT [",GetMessageContext(),"] DNS ADDRESS [",MDNSAddress,"] ADDRESS TYPE [",MAddressType,"] PROTOCOL TYPE [",MProtocolType,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	CCSPSocketDNSResolverManagerMessageResponse CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress::CreateErrorResponse(void) const
	{
		return(CCSPSocketDNSResolverManagerMessageResponse(new CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress(GetMessageContext(),false,MDNSAddress,CVector<CSocketIPAddress>())));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CSocketDNSAddress& CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress::GetDNSAddress(void) const noexcept
	{
		return(MDNSAddress);
	}
//----------------------------------------------------------------------------------------------------------------------
	ESocketDNSAddressType CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress::GetAddressType(void) const noexcept
	{
		return(MAddressType);
	}
//----------------------------------------------------------------------------------------------------------------------
	ESocketDNSProtocolType CSocketDNSResolverManagerMessageRequestDNSAddressToIPAddress::GetProtocolType(void) const noexcept
	{
		return(MProtocolType);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------