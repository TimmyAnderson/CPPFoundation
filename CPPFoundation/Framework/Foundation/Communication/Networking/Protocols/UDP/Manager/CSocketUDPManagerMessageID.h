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
	class CSocketUDPManagerMessageID final : public CID
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CSocketUDPManagerMessageID& operator=(const CSocketUDPManagerMessageID& Other);
			CSocketUDPManagerMessageID& operator=(CSocketUDPManagerMessageID&& Other) noexcept;

		public:
			CSocketUDPManagerMessageID(void);
			CSocketUDPManagerMessageID(const CString& ID);
			CSocketUDPManagerMessageID(CString&& ID);
			CSocketUDPManagerMessageID(CCSPString ID);
			CSocketUDPManagerMessageID(const CSocketUDPManagerMessageID& Other);
			CSocketUDPManagerMessageID(CSocketUDPManagerMessageID&& Other) noexcept;
			virtual ~CSocketUDPManagerMessageID(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------