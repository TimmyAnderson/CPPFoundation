//----------------------------------------------------------------------------------------------------------------------
#include "CCacheEntryTest1.h"
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
	CCacheEntryTest1::CCacheEntryTest1(const CCacheEntryID& ID, const CExpirationTime& ExpirationTime, const CString& Value)
		: CCacheEntry(ID,ExpirationTime), MValue(Value)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CCacheEntryTest1::~CCacheEntryTest1(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CString& CCacheEntryTest1::GetValue(void) const noexcept
	{
		return(MValue);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------