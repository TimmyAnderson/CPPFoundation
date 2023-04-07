//----------------------------------------------------------------------------------------------------------------------
#include "CParserParameterID.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CParserParameterID::CParserParameterID(const CString& ID)
		: CID(ID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CParserParameterID::CParserParameterID(CString&& ID)
		: CID(FUNCTION_MOVE(ID))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CParserParameterID::CParserParameterID(CCSPString ID)
		: CID(ID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CParserParameterID::CParserParameterID(const CParserParameterID& ID)
		: CID(ID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CParserParameterID::CParserParameterID(CParserParameterID&& ID) noexcept
		: CID(FUNCTION_MOVE(ID))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CParserParameterID::~CParserParameterID(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CParserParameterID& CParserParameterID::operator=(const CParserParameterID& Other)
	{
		CID::operator=(Other);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CParserParameterID& CParserParameterID::operator=(CParserParameterID&& Other) noexcept
	{
		CID::operator=(FUNCTION_MOVE(Other));

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------