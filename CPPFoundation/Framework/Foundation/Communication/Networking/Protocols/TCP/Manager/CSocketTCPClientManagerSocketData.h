//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CList.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Socket/CSocketTCPClient.h>
#include <Framework/Foundation/Objects/CObject.h>
#include "CSocketTCPClientManagerMessageRequestSocketConnect.h"
#include "CSocketTCPClientManagerWriteOperation.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPClientManagerSocketData final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			enum class ESocketTCPClientManagerSocketState : uint8
			{
//----------------------------------------------------------------------------------------------------------------------
				E_WAITING_FOR_CONNECTION=1,
				E_CONNECTED=2,
				E_HALF_CLOSED_READ=3,
				E_HALF_CLOSED_WRITE=4,
				E_CLOSED=5,
				E_FAILED=6,
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		private:
			CSPSocketTCPClient									MSocket;
			ESocketTCPClientManagerSocketState					MSocketState;
			CCSPSocketTCPClientManagerMessageRequestSocketConnect	MConnectOperation;
			CSocketTCPClientManagerWriteOperationCollection		MWriteOperations;

		public:
			static CString SocketStateToString(CSocketTCPClientManagerSocketData::ESocketTCPClientManagerSocketState State);

		public:
			CSPSocketTCPClient GetSocket(void) const noexcept;
			ESocketTCPClientManagerSocketState GetSocketState(void) const noexcept;
			void SetSocketState(ESocketTCPClientManagerSocketState SocketState) noexcept;
			CCSPSocketTCPClientManagerMessageRequestSocketConnect GetConnectOperation(void) const noexcept;
			CSocketTCPClientManagerWriteOperationCollection& GetWriteOperations(void) noexcept;
			const CSocketTCPClientManagerWriteOperationCollection& GetWriteOperations(void) const noexcept;
			void AddWriteOperation(CCSPSocketTCPClientManagerMessageRequestSocketWrite Operation);
			void ClearWriteOperations(void);

		public:
			CSocketTCPClientManagerSocketData(CSPSocketTCPClient Socket, ESocketTCPClientManagerSocketState SocketState, CCSPSocketTCPClientManagerMessageRequestSocketConnect ConnectOperation);
			virtual ~CSocketTCPClientManagerSocketData(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------