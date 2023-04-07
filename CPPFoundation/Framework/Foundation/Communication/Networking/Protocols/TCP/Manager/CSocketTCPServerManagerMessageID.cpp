//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPServerManagerMessageID.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageID::CSocketTCPServerManagerMessageID(void)
		: CID(CID::CreateID())
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageID::CSocketTCPServerManagerMessageID(const CString& ID)
		: CID(ID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageID::CSocketTCPServerManagerMessageID(CString&& ID)
		: CID(FUNCTION_MOVE(ID))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageID::CSocketTCPServerManagerMessageID(CCSPString ID)
		: CID(ID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageID::CSocketTCPServerManagerMessageID(const CSocketTCPServerManagerMessageID& Other)
		: CID(Other)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageID::CSocketTCPServerManagerMessageID(CSocketTCPServerManagerMessageID&& Other)
		: CID(FUNCTION_MOVE(Other))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageID::~CSocketTCPServerManagerMessageID(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageID& CSocketTCPServerManagerMessageID::operator=(const CSocketTCPServerManagerMessageID& Other)
	{
		CID::operator=(Other);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketTCPServerManagerMessageID& CSocketTCPServerManagerMessageID::operator=(CSocketTCPServerManagerMessageID&& Other)
	{
		CID::operator=(FUNCTION_MOVE(Other));

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------