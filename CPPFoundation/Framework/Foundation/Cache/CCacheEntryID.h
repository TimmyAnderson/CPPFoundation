//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Miscellaneous/CID.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CCacheEntryID final : public CID
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CCacheEntryID& operator=(const CCacheEntryID& Other);
			CCacheEntryID& operator=(CCacheEntryID&& Other) noexcept;

		public:
			CCacheEntryID(void);
			CCacheEntryID(const CString& ID);
			CCacheEntryID(CString&& ID);
			CCacheEntryID(CCSPString ID);
			CCacheEntryID(const CCacheEntryID& Other);
			CCacheEntryID(CCacheEntryID&& Other) noexcept;
			virtual ~CCacheEntryID(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------