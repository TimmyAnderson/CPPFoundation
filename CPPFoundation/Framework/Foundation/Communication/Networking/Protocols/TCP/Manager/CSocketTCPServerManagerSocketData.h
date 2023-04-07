//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CList.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Socket/CSocketTCPServer.h>
#include <Framework/Foundation/Objects/CObject.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPServerManagerSocketData final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			enum class ESocketTCPServerManagerSocketState : uint8
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
			CSPSocketTCPServer									MSocket;
			ESocketTCPServerManagerSocketState					MSocketState;

		public:
			static CString SocketStateToString(CSocketTCPServerManagerSocketData::ESocketTCPServerManagerSocketState State);

		public:
			CSPSocketTCPServer GetSocket(void) const noexcept;
			ESocketTCPServerManagerSocketState GetSocketState(void) const noexcept;
			void SetSocketState(ESocketTCPServerManagerSocketState SocketState) noexcept;

		public:
			CSocketTCPServerManagerSocketData(CSPSocketTCPServer Socket);
			virtual ~CSocketTCPServerManagerSocketData(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------