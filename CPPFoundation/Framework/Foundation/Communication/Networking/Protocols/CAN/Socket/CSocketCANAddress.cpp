//----------------------------------------------------------------------------------------------------------------------
#include "CSocketCANAddress.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANAddress::CSocketCANAddress(void)
		: MNetworkInterfaceIndex(), MProtocolClassAddressReceiveID(), MProtocolClassAddressSendID()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANAddress::CSocketCANAddress(int32 NetworkInterfaceIndex, uint32 ProtocolClassAddressReceiveID, uint32 ProtocolClassAddressSendID)
		: MNetworkInterfaceIndex(NetworkInterfaceIndex), MProtocolClassAddressReceiveID(ProtocolClassAddressReceiveID), MProtocolClassAddressSendID(ProtocolClassAddressSendID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANAddress::CSocketCANAddress(const CSocketCANAddress& Other)
		: MNetworkInterfaceIndex(Other.MNetworkInterfaceIndex), MProtocolClassAddressReceiveID(Other.MProtocolClassAddressReceiveID), MProtocolClassAddressSendID(Other.MProtocolClassAddressSendID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANAddress::CSocketCANAddress(CSocketCANAddress&& Other) noexcept
		: MNetworkInterfaceIndex(FUNCTION_MOVE(Other.MNetworkInterfaceIndex)), MProtocolClassAddressReceiveID(FUNCTION_MOVE(Other.MProtocolClassAddressReceiveID)), MProtocolClassAddressSendID(FUNCTION_MOVE(Other.MProtocolClassAddressSendID))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANAddress::~CSocketCANAddress(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANAddress& CSocketCANAddress::operator=(const CSocketCANAddress& Other)
	{
		MNetworkInterfaceIndex=Other.MNetworkInterfaceIndex;
		MProtocolClassAddressReceiveID=Other.MProtocolClassAddressReceiveID;
		MProtocolClassAddressSendID=Other.MProtocolClassAddressSendID;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANAddress& CSocketCANAddress::operator=(CSocketCANAddress&& Other) noexcept
	{
		MNetworkInterfaceIndex=Other.MNetworkInterfaceIndex;
		MProtocolClassAddressReceiveID=Other.MProtocolClassAddressReceiveID;
		MProtocolClassAddressSendID=Other.MProtocolClassAddressSendID;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketCANAddress::operator==(const CSocketCANAddress& Other) const
	{
		if (MNetworkInterfaceIndex!=Other.MNetworkInterfaceIndex)
		{
			return(false);
		}

		if (MProtocolClassAddressReceiveID!=Other.MProtocolClassAddressReceiveID)
		{
			return(false);
		}

		if (MProtocolClassAddressSendID!=Other.MProtocolClassAddressSendID)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketCANAddress::operator!=(const CSocketCANAddress& Other) const
	{
		return(!(*this==Other));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketCANAddress::ToString(void) const
	{
		return(CString::Format(MNetworkInterfaceIndex,"-",MProtocolClassAddressReceiveID,"-",MProtocolClassAddressSendID));
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketCANAddress::Equals(const CSocketAddress& Other) const
	{
		if (Other.IsTypeOf<CSocketCANAddress>()==false)
		{
			return(false);
		}

		const CSocketCANAddress&								TypedOther=Other.DynamicCastReference<CSocketCANAddress>();

		return((*this==TypedOther));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	int32 CSocketCANAddress::GetNetworkInterfaceIndex(void) const noexcept
	{
		return(MNetworkInterfaceIndex);
	}
//----------------------------------------------------------------------------------------------------------------------
	uint32 CSocketCANAddress::GetProtocolClassAddressReceiveID(void) const noexcept
	{
		return(MProtocolClassAddressReceiveID);
	}
//----------------------------------------------------------------------------------------------------------------------
	uint32 CSocketCANAddress::GetProtocolClassAddressSendID(void) const noexcept
	{
		return(MProtocolClassAddressSendID);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------