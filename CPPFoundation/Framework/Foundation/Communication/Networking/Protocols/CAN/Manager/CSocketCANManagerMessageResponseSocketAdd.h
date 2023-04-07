//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Sockets/CSocket.h>
#include "CSocketCANManagerMessageContext.h"
#include "CSocketCANManagerMessageResponse.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketCANManagerMessageResponseSocketAdd final : public CSocketCANManagerMessageResponse
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPSocketCANManagerMessageContext					MMessageContext;
			bool												MOperationSucceeded;
			CSPSocket											MSocket;

		public:
			CSocketCANManagerMessageResponseSocketAdd& operator=(const CSocketCANManagerMessageResponseSocketAdd& Other);
			CSocketCANManagerMessageResponseSocketAdd& operator=(CSocketCANManagerMessageResponseSocketAdd&& Other) noexcept;

		public:
			virtual CString ToString(void) const override;
			CCSPSocketCANManagerMessageContext GetMessageContext(void) const noexcept;
			bool GetOperationSucceeded(void) const noexcept;
			CSPSocket GetSocket(void) const noexcept;

		public:
			CSocketCANManagerMessageResponseSocketAdd(CCSPSocketCANManagerMessageContext MessageContext, bool OperationSucceeded, CSPSocket Socket);
			CSocketCANManagerMessageResponseSocketAdd(const CSocketCANManagerMessageResponseSocketAdd& Other);
			CSocketCANManagerMessageResponseSocketAdd(CSocketCANManagerMessageResponseSocketAdd&& Other) noexcept;
			virtual ~CSocketCANManagerMessageResponseSocketAdd(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketCANManagerMessageResponseSocketAdd=CSharedPointer<CSocketCANManagerMessageResponseSocketAdd>;
	using														CCSPSocketCANManagerMessageResponseSocketAdd=CSharedPointer<const CSocketCANManagerMessageResponseSocketAdd>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------