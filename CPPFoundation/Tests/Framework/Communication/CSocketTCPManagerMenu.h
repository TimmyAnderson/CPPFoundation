//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Manager/CSocketTCPClientManager.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Manager/CSocketTCPServerManager.h>
#include <Framework/Foundation/Console/CConsoleMenu.h>
#include <Framework/Foundation/Collections/CMap.h>
#include <Framework/Foundation/Logger/CConsoleLogWriter.h>
#include <Framework/Foundation/Miscellaneous/CRandom.h>
#include <Framework/Foundation/Threads/CAtomic.h>
#include "CSocketStatistics.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPManagerMenu final : public CPPFoundation::Foundation::CConsoleMenu, private CPPFoundation::Foundation::ISocketTCPServerManagerCallback, private CPPFoundation::Foundation::ISocketTCPClientManagerCallback
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			using												CServerSocketCollection=CPPFoundation::Foundation::CMap<CPPFoundation::Foundation::CString,CPPFoundation::Foundation::CSPSocketTCPServer>;
			using												CClientSocketCollection=CPPFoundation::Foundation::CMap<CPPFoundation::Foundation::CString,CPPFoundation::Foundation::CSPSocketTCPClient>;

		private:
			bool												MIsServerManagerInitialized;
			bool												MIsClientManagerInitialized;
			CServerSocketCollection								MServerSocketCollection;
			CClientSocketCollection								MClientSocketCollection;
			CPPFoundation::Foundation::CSPSocketTCPServerManager	MServerSocketManager;
			CPPFoundation::Foundation::CSPSocketTCPClientManager	MClientSocketManager;
			CPPFoundation::Foundation::CRandom<int32>				MRandom;
			CPPFoundation::Foundation::CAtomic<Size>				MAcceptSocketCounter;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfPacketsSends;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfPacketsSendSuccesses;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfPacketsSendFailures;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfPacketsReceives;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfSocketsAccepts;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfSocketsConnects;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfSocketsConnectSuccesses;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfSocketsConnectFailures;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfSocketsShutdowns;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfSocketsShutdownSuccesses;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfSocketsShutdownFailures;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfSocketsServerAdds;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfSocketsServerAddSuccesses;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfSocketsServerAddFailures;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfSocketsServerRemoves;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfSocketsServerRemoveSuccesses;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfSocketsServerRemoveFailures;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfSocketsClientAdds;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfSocketsClientAddSuccesses;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfSocketsClientAddFailures;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfSocketsClientRemoves;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfSocketsClientRemoveSuccesses;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfSocketsClientRemoveFailures;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfSocketsServerCloses;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfSocketsServerErrors;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfSocketsClientClosings;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfSocketsClientCloses;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfSocketsClientErrors;
			CSocketStatistics									MSocketStatistics;

		private:
			virtual void ProcessMessageResponse(CPPFoundation::Foundation::CCSPSocketTCPServerManagerMessageResponse MessageResponse) override;
			virtual void ProcessMessageResponse(CPPFoundation::Foundation::CCSPSocketTCPClientManagerMessageResponse MessageResponse) override;

		private:
			void MenuItemExit(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemInitializeServer(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemUninitializeServer(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemInitializeClient(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemUninitializeClient(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemStartSocketManagerServer(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemStopSocketManagerServer(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemStartSocketManagerClient(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemStopSocketManagerClient(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemCreateSocket(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemDestroySocket(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemBindSocket(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemListenSocket(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemAddSocket(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemRemoveSocket(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemConnectSocketManually(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemCloseSocketManually(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemConnectSocket(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemShutdownSocket(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemSendToSocket(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemMultiSendToSocket(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemSendLongPacketToSocket(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemMultiSendLongPacketToSocket(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemGetSendBufferSize(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemSetSendBufferSize(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemGetReceiveBufferSize(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemSetReceiveBufferSize(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemExecuteCommand(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemStatistics(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemDataStatistics(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);

		protected:
			virtual CPPFoundation::Foundation::CString GetStatus(void) const override;

		public:
			CSocketTCPManagerMenu(CPPFoundation::Foundation::CConsoleLogWriter& LogWriter);
			virtual ~CSocketTCPManagerMenu(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------