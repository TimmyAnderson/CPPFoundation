//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Console/CConsoleMenu.h>
#include <Framework/Foundation/Collections/CMap.h>
#include <Framework/Foundation/Logger/CConsoleLogWriter.h>
#include <Framework/Foundation/Communication/Networking/Sockets/CSocket.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketUDPMenu final : public CPPFoundation::Foundation::CConsoleMenu
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			using												CSocketCollection=CPPFoundation::Foundation::CMap<CPPFoundation::Foundation::CString,CPPFoundation::Foundation::CSPSocket>;

		private:
			bool												MIsLibraryInitialized;
			CSocketCollection									MSocketCollection;

		private:
			void MenuItemExit(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemInitialize(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemUninitialize(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemCreateSocket(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemDestroySocket(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemBindSocket(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemSendToSocket(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemReceiveFromSocket(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemSendToSocketCustomBuffer(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemReceiveFromSocketCustomBuffer(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemWaitForEvent(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemGetSendBufferSize(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemSetSendBufferSize(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemGetReceiveBufferSize(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemSetReceiveBufferSize(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);

		protected:
			virtual CPPFoundation::Foundation::CString GetStatus(void) const override;

		public:
			CSocketUDPMenu(CPPFoundation::Foundation::CConsoleLogWriter& LogWriter);
			virtual ~CSocketUDPMenu(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------