//----------------------------------------------------------------------------------------------------------------------
#include "CStateMachineID.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CStateMachineID::CStateMachineID(void)
		: CID(CID::CreateID())
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateMachineID::CStateMachineID(const CString& ID)
		: CID(ID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateMachineID::CStateMachineID(CString&& ID)
		: CID(FUNCTION_MOVE(ID))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateMachineID::CStateMachineID(CCSPString ID)
		: CID(ID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateMachineID::CStateMachineID(const CStateMachineID& Other)
		: CID(Other)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateMachineID::CStateMachineID(CStateMachineID&& Other) noexcept
		: CID(FUNCTION_MOVE(Other))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateMachineID::~CStateMachineID(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CStateMachineID& CStateMachineID::operator=(const CStateMachineID& Other)
	{
		CID::operator=(Other);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CStateMachineID& CStateMachineID::operator=(CStateMachineID&& Other) noexcept
	{
		CID::operator=(FUNCTION_MOVE(Other));

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CStateMachineID CStateMachineID::CreateEmptyStateMachineID(void)
	{
		return(CStateMachineID(""));
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------