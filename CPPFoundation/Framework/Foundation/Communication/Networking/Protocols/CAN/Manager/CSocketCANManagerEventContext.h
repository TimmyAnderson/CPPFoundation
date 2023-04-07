//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Events/CEventContext.h>
#include "ISocketCANManagerCallback.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketCANManagerEventContext : public CEventContext
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			ISocketCANManagerCallback&							MCallback;

		public:
			CSocketCANManagerEventContext& operator=(const CSocketCANManagerEventContext& Other);
			CSocketCANManagerEventContext& operator=(CSocketCANManagerEventContext&& Other);

		public:
			ISocketCANManagerCallback& GetCallback(void) const noexcept;

		public:
			CSocketCANManagerEventContext(const CEventID& EventID, ISocketCANManagerCallback& Callback);
			CSocketCANManagerEventContext(CEventID&& EventID, ISocketCANManagerCallback& Callback);
			CSocketCANManagerEventContext(const CSocketCANManagerEventContext& Other);
			CSocketCANManagerEventContext(CSocketCANManagerEventContext&& Other);
			virtual ~CSocketCANManagerEventContext(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketCANManagerEventContext=CSharedPointer<CSocketCANManagerEventContext>;
	using														CCSPSocketCANManagerEventContext=CSharedPointer<const CSocketCANManagerEventContext>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------