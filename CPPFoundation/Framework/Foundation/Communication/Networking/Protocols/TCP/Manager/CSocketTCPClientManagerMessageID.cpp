//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPClientManagerMessageID.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageID::CSocketTCPClientManagerMessageID(void)
		: CID(CID::CreateID())
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageID::CSocketTCPClientManagerMessageID(const CString& ID)
		: CID(ID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageID::CSocketTCPClientManagerMessageID(CString&& ID)
		: CID(FUNCTION_MOVE(ID))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageID::CSocketTCPClientManagerMessageID(CCSPString ID)
		: CID(ID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageID::CSocketTCPClientManagerMessageID(const CSocketTCPClientManagerMessageID& Other)
		: CID(Other)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageID::CSocketTCPClientManagerMessageID(CSocketTCPClientManagerMessageID&& Other)
		: CID(FUNCTION_MOVE(Other))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageID::~CSocketTCPClientManagerMessageID(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageID& CSocketTCPClientManagerMessageID::operator=(const CSocketTCPClientManagerMessageID& Other)
	{
		CID::operator=(Other);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPClientManagerMessageID& CSocketTCPClientManagerMessageID::operator=(CSocketTCPClientManagerMessageID&& Other)
	{
		CID::operator=(FUNCTION_MOVE(Other));

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------