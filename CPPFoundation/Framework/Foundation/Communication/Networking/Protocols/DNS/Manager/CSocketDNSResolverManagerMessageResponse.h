//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Types/CSharedPointer.h>
#include "CSocketDNSResolverManagerMessageContext.h"
#include "CSocketDNSResolverManagerMessage.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketDNSResolverManagerMessageResponse : public CSocketDNSResolverManagerMessage
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPSocketDNSResolverManagerMessageContext			MMessageContext;
			bool												MOperationSucceeded;

		public:
			CSocketDNSResolverManagerMessageResponse& operator=(const CSocketDNSResolverManagerMessageResponse& Other);
			CSocketDNSResolverManagerMessageResponse& operator=(CSocketDNSResolverManagerMessageResponse&& Other);

		public:
			CCSPSocketDNSResolverManagerMessageContext GetMessageContext(void) const noexcept;
			bool GetOperationSucceeded(void) const noexcept;

		protected:
			CSocketDNSResolverManagerMessageResponse(CCSPSocketDNSResolverManagerMessageContext MessageContext, bool OperationSucceeded);
			CSocketDNSResolverManagerMessageResponse(const CSocketDNSResolverManagerMessageResponse& Other);
			CSocketDNSResolverManagerMessageResponse(CSocketDNSResolverManagerMessageResponse&& Other);
			virtual ~CSocketDNSResolverManagerMessageResponse(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketDNSResolverManagerMessageResponse=CSharedPointer<CSocketDNSResolverManagerMessageResponse>;
	using														CCSPSocketDNSResolverManagerMessageResponse=CSharedPointer<const CSocketDNSResolverManagerMessageResponse>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------