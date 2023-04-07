//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CSocketDNSResolverManagerMessage.h"
#include "CSocketDNSResolverManagerMessageContext.h"
#include "CSocketDNSResolverManagerMessageResponse.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketDNSResolverManagerMessageRequest : public CSocketDNSResolverManagerMessage
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPSocketDNSResolverManagerMessageContext			MMessageContext;

		public:
			CSocketDNSResolverManagerMessageRequest& operator=(const CSocketDNSResolverManagerMessageRequest& Other);
			CSocketDNSResolverManagerMessageRequest& operator=(CSocketDNSResolverManagerMessageRequest&& Other) noexcept;

		public:
			virtual CCSPSocketDNSResolverManagerMessageResponse CreateErrorResponse(void) const=0;

		public:
			CCSPSocketDNSResolverManagerMessageContext GetMessageContext(void) const noexcept;

		protected:
			CSocketDNSResolverManagerMessageRequest(CCSPSocketDNSResolverManagerMessageContext MessageContext);
			CSocketDNSResolverManagerMessageRequest(const CSocketDNSResolverManagerMessageRequest& Other);
			CSocketDNSResolverManagerMessageRequest(CSocketDNSResolverManagerMessageRequest&& Other) noexcept;
			virtual ~CSocketDNSResolverManagerMessageRequest(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketDNSResolverManagerMessageRequest=CSharedPointer<CSocketDNSResolverManagerMessageRequest>;
	using														CCSPSocketDNSResolverManagerMessageRequest=CSharedPointer<const CSocketDNSResolverManagerMessageRequest>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------