//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Events/CEventContext.h>
#include "ISocketTCPClientManagerCallback.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPClientManagerEventContext : public CEventContext
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			ISocketTCPClientManagerCallback&							MCallback;

		public:
			CSocketTCPClientManagerEventContext& operator=(const CSocketTCPClientManagerEventContext& Other);
			CSocketTCPClientManagerEventContext& operator=(CSocketTCPClientManagerEventContext&& Other) noexcept;

		public:
			ISocketTCPClientManagerCallback& GetCallback(void) const noexcept;

		public:
			CSocketTCPClientManagerEventContext(const CEventID& EventID, ISocketTCPClientManagerCallback& Callback);
			CSocketTCPClientManagerEventContext(CEventID&& EventID, ISocketTCPClientManagerCallback& Callback);
			CSocketTCPClientManagerEventContext(const CSocketTCPClientManagerEventContext& Other);
			CSocketTCPClientManagerEventContext(CSocketTCPClientManagerEventContext&& Other) noexcept;
			virtual ~CSocketTCPClientManagerEventContext(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPClientManagerEventContext=CSharedPointer<CSocketTCPClientManagerEventContext>;
	using														CCSPSocketTCPClientManagerEventContext=CSharedPointer<const CSocketTCPClientManagerEventContext>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------