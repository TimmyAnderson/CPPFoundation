//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CList.h>
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Socket/CSocketUDP.h>
#include <Framework/Foundation/Objects/CObject.h>
#include "CSocketUDPManagerWriteOperation.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketUDPManagerSocketData final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			enum class ESocketUDPManagerSocketState : uint8
			{
//----------------------------------------------------------------------------------------------------------------------
				E_OPENED=1,
				E_CLOSED=2,
				E_FAILED=3,
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private:
			CSPSocketUDP										MSocket;
			ESocketUDPManagerSocketState						MSocketState;
			CSocketUDPManagerWriteOperationCollection			MWriteOperations;

		public:
			static CString SocketStateToString(CSocketUDPManagerSocketData::ESocketUDPManagerSocketState State);

		public:
			CSPSocketUDP GetSocket(void) const noexcept;
			ESocketUDPManagerSocketState GetSocketState(void) const noexcept;
			void SetSocketState(ESocketUDPManagerSocketState SocketState) noexcept;
			CSocketUDPManagerWriteOperationCollection& GetWriteOperations(void) noexcept;
			void AddWriteOperation(CCSPSocketUDPManagerMessageRequestSocketWrite Operation);
			void ClearWriteOperations(void);

		public:
			CSocketUDPManagerSocketData(CSPSocketUDP Socket);
			virtual ~CSocketUDPManagerSocketData(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------