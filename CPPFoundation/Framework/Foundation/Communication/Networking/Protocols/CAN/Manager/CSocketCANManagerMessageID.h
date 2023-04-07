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
	class CSocketCANManagerMessageID final : public CID
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CSocketCANManagerMessageID& operator=(const CSocketCANManagerMessageID& Other);
			CSocketCANManagerMessageID& operator=(CSocketCANManagerMessageID&& Other);

		public:
			CSocketCANManagerMessageID(void);
			CSocketCANManagerMessageID(const CString& ID);
			CSocketCANManagerMessageID(CString&& ID);
			CSocketCANManagerMessageID(CCSPString ID);
			CSocketCANManagerMessageID(const CSocketCANManagerMessageID& Other);
			CSocketCANManagerMessageID(CSocketCANManagerMessageID&& Other);
			virtual ~CSocketCANManagerMessageID(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------