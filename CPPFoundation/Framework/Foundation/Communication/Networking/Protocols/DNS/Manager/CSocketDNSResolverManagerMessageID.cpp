//----------------------------------------------------------------------------------------------------------------------
#include "CSocketDNSResolverManagerMessageID.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageID::CSocketDNSResolverManagerMessageID(void)
		: CID(CID::CreateID())
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageID::CSocketDNSResolverManagerMessageID(const CString& ID)
		: CID(ID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageID::CSocketDNSResolverManagerMessageID(CString&& ID)
		: CID(FUNCTION_MOVE(ID))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageID::CSocketDNSResolverManagerMessageID(CCSPString ID)
		: CID(ID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageID::CSocketDNSResolverManagerMessageID(const CSocketDNSResolverManagerMessageID& Other)
		: CID(Other)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageID::CSocketDNSResolverManagerMessageID(CSocketDNSResolverManagerMessageID&& Other) noexcept
		: CID(FUNCTION_MOVE(Other))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageID::~CSocketDNSResolverManagerMessageID(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageID& CSocketDNSResolverManagerMessageID::operator=(const CSocketDNSResolverManagerMessageID& Other)
	{
		CID::operator=(Other);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSResolverManagerMessageID& CSocketDNSResolverManagerMessageID::operator=(CSocketDNSResolverManagerMessageID&& Other) noexcept
	{
		CID::operator=(FUNCTION_MOVE(Other));

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------