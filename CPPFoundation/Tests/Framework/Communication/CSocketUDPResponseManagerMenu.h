//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Manager/CSocketUDPManager.h>
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Manager/CSocketUDPManagerMessageResponseSocketRead.h>
#include <Framework/Foundation/Console/CConsoleMenu.h>
#include <Framework/Foundation/Collections/CMap.h>
#include <Framework/Foundation/Logger/CConsoleLogWriter.h>
#include "CSocketUDPResponseManager.h"
#include "CSocketUDPResponseCondition.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketUDPResponseManagerMenu final : public CPPFoundation::Foundation::CConsoleMenu, private CPPFoundation::Foundation::ISocketUDPManagerCallback
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			using												CSocketCollection=CPPFoundation::Foundation::CMap<CPPFoundation::Foundation::CString,CPPFoundation::Foundation::CSPSocketUDP>;

		private:
			bool												MIsLibraryInitialized;
			CSocketCollection									MSocketCollection;
			CPPFoundation::Foundation::CSPSocketUDPManager			MSocketManager;
			CSPSocketUDPResponseManager							MSocketUDPResponseManager;
			CSocketUDPResponseConditionCollection				MResponseConditionCollection;

		private:
			void CheckForResponse(CPPFoundation::Foundation::CCSPSocketUDPManagerMessageResponseSocketRead MessageResponse);

		private:
			virtual void ProcessMessageResponse(CPPFoundation::Foundation::CCSPSocketUDPManagerMessageResponse MessageResponse) override;

		private:
			void MenuItemExit(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemInitialize(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemUninitialize(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemStartSocketManager(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemStopSocketManager(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemStartResponseManager(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemStopResponseManager(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemCreateSocket(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemDestroySocket(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemBindSocket(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemAddSocket(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemRemoveSocket(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemSendToSocket(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemExecuteCommand(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);

		protected:
			virtual CPPFoundation::Foundation::CString GetStatus(void) const override;

		public:
			CSocketUDPResponseManagerMenu(CPPFoundation::Foundation::CConsoleLogWriter& LogWriter);
			virtual ~CSocketUDPResponseManagerMenu(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------