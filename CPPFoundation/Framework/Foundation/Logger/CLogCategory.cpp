//----------------------------------------------------------------------------------------------------------------------
#include "CLogCategory.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CLogCategory::CLogCategory(const CString& CategoryType)
		: MCategoryType(CategoryType), MCategoryTypeHash(CategoryType.GetHash())
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CLogCategory::CLogCategory(CString&& CategoryType)
		: MCategoryType(), MCategoryTypeHash(CategoryType.GetHash())
	{
		MCategoryType=FUNCTION_MOVE(CategoryType);
	}
//----------------------------------------------------------------------------------------------------------------------
	CLogCategory::CLogCategory(const CLogCategory& Other)
		: MCategoryType(Other.MCategoryType), MCategoryTypeHash(Other.MCategoryTypeHash)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CLogCategory::CLogCategory(CLogCategory&& Other) noexcept
		: MCategoryType(FUNCTION_MOVE(Other.MCategoryType)), MCategoryTypeHash(Other.MCategoryTypeHash)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CLogCategory::~CLogCategory(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CLogCategory& CLogCategory::operator=(const CLogCategory& Other)
	{
		MCategoryType=Other.MCategoryType;
		MCategoryTypeHash=Other.MCategoryTypeHash;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CLogCategory& CLogCategory::operator=(CLogCategory&& Other) noexcept
	{
		MCategoryType=FUNCTION_MOVE(Other.MCategoryType);
		MCategoryTypeHash=Other.MCategoryTypeHash;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CLogCategory::operator==(const CLogCategory& Other) const
	{
		if (MCategoryType==Other.MCategoryType)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CLogCategory::operator!=(const CLogCategory& Other) const
	{
		if (MCategoryType!=Other.MCategoryType)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CString& CLogCategory::GetCategoryType(void) const noexcept
	{
		return(MCategoryType);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CLogCategory::GetHash(void) const
	{
		return(MCategoryTypeHash);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------