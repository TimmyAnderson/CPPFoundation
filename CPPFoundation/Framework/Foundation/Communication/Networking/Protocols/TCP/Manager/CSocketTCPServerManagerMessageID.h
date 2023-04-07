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
	class CSocketTCPServerManagerMessageID final : public CID
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CSocketTCPServerManagerMessageID& operator=(const CSocketTCPServerManagerMessageID& Other);
			CSocketTCPServerManagerMessageID& operator=(CSocketTCPServerManagerMessageID&& Other);

		public:
			CSocketTCPServerManagerMessageID(void);
			CSocketTCPServerManagerMessageID(const CString& ID);
			CSocketTCPServerManagerMessageID(CString&& ID);
			CSocketTCPServerManagerMessageID(CCSPString ID);
			CSocketTCPServerManagerMessageID(const CSocketTCPServerManagerMessageID& Other);
			CSocketTCPServerManagerMessageID(CSocketTCPServerManagerMessageID&& Other);
			virtual ~CSocketTCPServerManagerMessageID(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------