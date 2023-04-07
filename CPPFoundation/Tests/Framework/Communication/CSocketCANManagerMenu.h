//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Manager/CSocketCANManager.h>
#include <Framework/Foundation/Console/CConsoleMenu.h>
#include <Framework/Foundation/Collections/CMap.h>
#include <Framework/Foundation/Logger/CConsoleLogWriter.h>
#include <Framework/Foundation/Miscellaneous/CRandom.h>
#include <Framework/Foundation/Threads/CAtomic.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketCANManagerMenu final : public CPPFoundation::Foundation::CConsoleMenu, private CPPFoundation::Foundation::ISocketCANManagerCallback
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			using												CSocketCollection=CPPFoundation::Foundation::CMap<CPPFoundation::Foundation::CString,CPPFoundation::Foundation::CSPSocketCAN>;

		private:
			bool												MIsLibraryInitialized;
			CSocketCollection									MSocketCollection;
			CPPFoundation::Foundation::CSPSocketCANManager			MSocketManager;
			CPPFoundation::Foundation::CRandom<int32>				MRandom;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfPacketsSends;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfPacketsSendSuccesses;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfPacketsSendFailures;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfPacketsReceives;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfSocketsAdds;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfSocketsAddSuccesses;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfSocketsAddFailures;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfSocketsRemoves;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfSocketsRemoveSuccesses;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfSocketsRemoveFailures;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfSocketsCloses;
			CPPFoundation::Foundation::CAtomic<uint32>				MNumberOfSocketsErrors;
			CPPFoundation::Foundation::CAtomic<Size>				MNumberOfBytesSent;
			CPPFoundation::Foundation::CAtomic<Size>				MNumberOfBytesReceived;
			CPPFoundation::Foundation::CAtomic<Size>				MSumOfBytesSent;
			CPPFoundation::Foundation::CAtomic<Size>				MSumOfBytesReceived;

		private:
			virtual void ProcessMessageResponse(CPPFoundation::Foundation::CCSPSocketCANManagerMessageResponse MessageResponse) override;

		private:
			void MenuItemExit(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemInitialize(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemUninitialize(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemStartSocketManager(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemStopSocketManager(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemCreateSocket(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemDestroySocket(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemBindSocket(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemAddSocket(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemRemoveSocket(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemSendToSocket(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemMultiSendToSocket(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemGetNetworkInterfaceNameForDevice(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemGetNetworkInterfaceIndexForDevice(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemExecuteCommand(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemStatistics(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemDataStatistics(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);

		protected:
			virtual CPPFoundation::Foundation::CString GetStatus(void) const override;

		public:
			CSocketCANManagerMenu(CPPFoundation::Foundation::CConsoleLogWriter& LogWriter);
			virtual ~CSocketCANManagerMenu(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------