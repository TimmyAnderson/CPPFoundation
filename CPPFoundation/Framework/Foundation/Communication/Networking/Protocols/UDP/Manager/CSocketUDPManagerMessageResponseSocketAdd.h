//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Socket/CSocketUDP.h>
#include "CSocketUDPManagerMessageContext.h"
#include "CSocketUDPManagerMessageResponse.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketUDPManagerMessageResponseSocketAdd final : public CSocketUDPManagerMessageResponse
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPSocketUDPManagerMessageContext					MMessageContext;
			bool												MOperationSucceeded;
			CSPSocketUDP										MSocket;

		public:
			CSocketUDPManagerMessageResponseSocketAdd& operator=(const CSocketUDPManagerMessageResponseSocketAdd& Other);
			CSocketUDPManagerMessageResponseSocketAdd& operator=(CSocketUDPManagerMessageResponseSocketAdd&& Other) noexcept;

		public:
			virtual CString ToString(void) const override;
			CCSPSocketUDPManagerMessageContext GetMessageContext(void) const noexcept;
			bool GetOperationSucceeded(void) const noexcept;
			CSPSocketUDP GetSocket(void) const noexcept;

		public:
			CSocketUDPManagerMessageResponseSocketAdd(CCSPSocketUDPManagerMessageContext MessageContext, bool OperationSucceeded, CSPSocketUDP Socket);
			CSocketUDPManagerMessageResponseSocketAdd(const CSocketUDPManagerMessageResponseSocketAdd& Other);
			CSocketUDPManagerMessageResponseSocketAdd(CSocketUDPManagerMessageResponseSocketAdd&& Other) noexcept;
			virtual ~CSocketUDPManagerMessageResponseSocketAdd(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketUDPManagerMessageResponseSocketAdd=CSharedPointer<CSocketUDPManagerMessageResponseSocketAdd>;
	using														CCSPSocketUDPManagerMessageResponseSocketAdd=CSharedPointer<const CSocketUDPManagerMessageResponseSocketAdd>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------