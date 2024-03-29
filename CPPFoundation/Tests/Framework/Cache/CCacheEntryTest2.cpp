//----------------------------------------------------------------------------------------------------------------------
#include "CCacheEntryTest2.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace CPPFoundation::Foundation;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CCacheEntryTest2::CCacheEntryTest2(const CCacheEntryID& ID, const CExpirationTime& ExpirationTime, const CString& Value)
		: CCacheEntry(ID,ExpirationTime), MValue(Value)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CCacheEntryTest2::~CCacheEntryTest2(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CString& CCacheEntryTest2::GetValue(void) const noexcept
	{
		return(MValue);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------