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
	class CSocketDNSResolverManagerMessageID final : public CID
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CSocketDNSResolverManagerMessageID& operator=(const CSocketDNSResolverManagerMessageID& Other);
			CSocketDNSResolverManagerMessageID& operator=(CSocketDNSResolverManagerMessageID&& Other) noexcept;

		public:
			CSocketDNSResolverManagerMessageID(void);
			CSocketDNSResolverManagerMessageID(const CString& ID);
			CSocketDNSResolverManagerMessageID(CString&& ID);
			CSocketDNSResolverManagerMessageID(CCSPString ID);
			CSocketDNSResolverManagerMessageID(const CSocketDNSResolverManagerMessageID& Other);
			CSocketDNSResolverManagerMessageID(CSocketDNSResolverManagerMessageID&& Other) noexcept;
			virtual ~CSocketDNSResolverManagerMessageID(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------