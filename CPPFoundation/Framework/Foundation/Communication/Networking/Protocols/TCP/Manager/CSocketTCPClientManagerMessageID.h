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
	class CSocketTCPClientManagerMessageID final : public CID
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CSocketTCPClientManagerMessageID& operator=(const CSocketTCPClientManagerMessageID& Other);
			CSocketTCPClientManagerMessageID& operator=(CSocketTCPClientManagerMessageID&& Other);

		public:
			CSocketTCPClientManagerMessageID(void);
			CSocketTCPClientManagerMessageID(const CString& ID);
			CSocketTCPClientManagerMessageID(CString&& ID);
			CSocketTCPClientManagerMessageID(CCSPString ID);
			CSocketTCPClientManagerMessageID(const CSocketTCPClientManagerMessageID& Other);
			CSocketTCPClientManagerMessageID(CSocketTCPClientManagerMessageID&& Other);
			virtual ~CSocketTCPClientManagerMessageID(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------