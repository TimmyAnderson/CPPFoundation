//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CList.h>
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Socket/CSocketCAN.h>
#include <Framework/Foundation/Objects/CObject.h>
#include "CSocketCANManagerWriteOperation.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketCANManagerSocketData final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			enum class ESocketCANManagerSocketState : uint8
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
			CSPSocketCAN										MSocket;
			ESocketCANManagerSocketState						MSocketState;
			CSocketCANManagerWriteOperationCollection			MWriteOperations;

		public:
			static CString SocketStateToString(CSocketCANManagerSocketData::ESocketCANManagerSocketState State);

		public:
			CSPSocketCAN GetSocket(void) const noexcept;
			ESocketCANManagerSocketState GetSocketState(void) const noexcept;
			void SetSocketState(ESocketCANManagerSocketState SocketState) noexcept;
			CSocketCANManagerWriteOperationCollection& GetWriteOperations(void) noexcept;
			void AddWriteOperation(CCSPSocketCANManagerMessageRequestSocketWrite Operation);
			void ClearWriteOperations(void);

		public:
			CSocketCANManagerSocketData(CSPSocketCAN Socket);
			virtual ~CSocketCANManagerSocketData(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------