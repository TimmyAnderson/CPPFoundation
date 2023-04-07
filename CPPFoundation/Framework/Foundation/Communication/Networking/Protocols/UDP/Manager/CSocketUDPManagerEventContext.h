//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Events/CEventContext.h>
#include "ISocketUDPManagerCallback.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketUDPManagerEventContext : public CEventContext
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			ISocketUDPManagerCallback&							MCallback;

		public:
			CSocketUDPManagerEventContext& operator=(const CSocketUDPManagerEventContext& Other);
			CSocketUDPManagerEventContext& operator=(CSocketUDPManagerEventContext&& Other) noexcept;

		public:
			ISocketUDPManagerCallback& GetCallback(void) const noexcept;

		public:
			CSocketUDPManagerEventContext(const CEventID& EventID, ISocketUDPManagerCallback& Callback);
			CSocketUDPManagerEventContext(CEventID&& EventID, ISocketUDPManagerCallback& Callback);
			CSocketUDPManagerEventContext(const CSocketUDPManagerEventContext& Other);
			CSocketUDPManagerEventContext(CSocketUDPManagerEventContext&& Other) noexcept;
			virtual ~CSocketUDPManagerEventContext(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketUDPManagerEventContext=CSharedPointer<CSocketUDPManagerEventContext>;
	using														CCSPSocketUDPManagerEventContext=CSharedPointer<const CSocketUDPManagerEventContext>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------