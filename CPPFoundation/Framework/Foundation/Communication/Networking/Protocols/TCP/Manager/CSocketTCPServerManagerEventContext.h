//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Events/CEventContext.h>
#include "ISocketTCPServerManagerCallback.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPServerManagerEventContext : public CEventContext
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			ISocketTCPServerManagerCallback&							MCallback;

		public:
			CSocketTCPServerManagerEventContext& operator=(const CSocketTCPServerManagerEventContext& Other);
			CSocketTCPServerManagerEventContext& operator=(CSocketTCPServerManagerEventContext&& Other);

		public:
			ISocketTCPServerManagerCallback& GetCallback(void) const noexcept;

		public:
			CSocketTCPServerManagerEventContext(const CEventID& EventID, ISocketTCPServerManagerCallback& Callback);
			CSocketTCPServerManagerEventContext(CEventID&& EventID, ISocketTCPServerManagerCallback& Callback);
			CSocketTCPServerManagerEventContext(const CSocketTCPServerManagerEventContext& Other);
			CSocketTCPServerManagerEventContext(CSocketTCPServerManagerEventContext&& Other);
			virtual ~CSocketTCPServerManagerEventContext(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPServerManagerEventContext=CSharedPointer<CSocketTCPServerManagerEventContext>;
	using														CCSPSocketTCPServerManagerEventContext=CSharedPointer<const CSocketTCPServerManagerEventContext>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------