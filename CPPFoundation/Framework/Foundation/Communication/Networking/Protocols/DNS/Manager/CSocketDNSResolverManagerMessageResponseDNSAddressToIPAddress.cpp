//----------------------------------------------------------------------------------------------------------------------
#include "CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress::CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress(CCSPSocketDNSResolverManagerMessageContext MessageContext, bool OperationSucceeded, const CSocketDNSAddress& DNSAddress, const CVector<CSocketIPAddress>& IPAddresses)
		: CSocketDNSResolverManagerMessageResponse(MessageContext,OperationSucceeded), MDNSAddress(DNSAddress), MIPAddresses(IPAddresses)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress::CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress(CCSPSocketDNSResolverManagerMessageContext MessageContext, bool OperationSucceeded, const CSocketDNSAddress& DNSAddress, CVector<CSocketIPAddress>&& IPAddresses)
		: CSocketDNSResolverManagerMessageResponse(MessageContext,OperationSucceeded), MDNSAddress(DNSAddress), MIPAddresses(FUNCTION_MOVE(IPAddresses))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress::CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress(const CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress& Other)
		: CSocketDNSResolverManagerMessageResponse(FUNCTION_MOVE(Other)), MDNSAddress(Other.MDNSAddress), MIPAddresses(Other.MIPAddresses)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress::CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress(CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress&& Other) noexcept
		: CSocketDNSResolverManagerMessageResponse(FUNCTION_MOVE(Other)), MDNSAddress(FUNCTION_MOVE(Other.MDNSAddress)), MIPAddresses(FUNCTION_MOVE(Other.MIPAddresses))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress::~CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress& CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress::operator=(const CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress& Other)
	{
		CSocketDNSResolverManagerMessageResponse::operator=(Other);

		MDNSAddress=Other.MDNSAddress;
		MIPAddresses=Other.MIPAddresses;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress& CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress::operator=(CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress&& Other) noexcept
	{
		CSocketDNSResolverManagerMessageResponse::operator=(FUNCTION_MOVE(Other));

		MDNSAddress=FUNCTION_MOVE(Other.MDNSAddress);
		MIPAddresses=FUNCTION_MOVE(Other.MIPAddresses);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress::ToString(void) const
	{
		CString												IPAddresses;

		for(Size Index=0;Index<MIPAddresses.GetLength();Index++)
		{
			if (Index>0)
			{
				IPAddresses.Append(" ");
			}

			IPAddresses.Append(MIPAddresses[Index].ToString());
		}

		return(CString::Format("DNS RESOLVER MESSAGE RESPONSE DNS ADDRESS to IP ADDRESS - MESSAGE CONTEXT [",GetMessageContext(),"] OPERATION SUCCEEDED [",GetOperationSucceeded(),"] IP ADDRESSES [",IPAddresses,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CSocketDNSAddress& CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress::GetDNSAddress(void) const noexcept
	{
		return(MDNSAddress);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CVector<CSocketIPAddress>& CSocketDNSResolverManagerMessageResponseDNSAddressToIPAddress::GetIPAddresses(void) const noexcept
	{
		return(MIPAddresses);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------