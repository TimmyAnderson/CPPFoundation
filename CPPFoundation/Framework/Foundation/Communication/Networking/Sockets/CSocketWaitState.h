//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Sockets/CSocket.h>
#include <Framework/Foundation/Communication/Networking/Sockets/ESocketWaitFlags.h>
#include <Framework/Foundation/Communication/Networking/Sockets/ESocketWaitResultFlags.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketWaitState final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CSPSocket											MSocket;
			ESocketWaitFlags									MWaitFlags;
			ESocketWaitResultFlags								MWaitResultFlags;

		public:
			CSPSocket GetSocket(void) const noexcept;
			ESocketWaitFlags GetWaitFlags(void) const noexcept;
			void SetWaitFlags(ESocketWaitFlags Flags) noexcept;
			ESocketWaitResultFlags GetWaitResultFlags(void) const noexcept;
			void SetWaitResultFlags(ESocketWaitResultFlags Flags) noexcept;

		public:
			CSocketWaitState(CSPSocket Socket, ESocketWaitFlags WaitFlags);
			virtual ~CSocketWaitState(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------