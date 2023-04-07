//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Console/CConsoleMenu.h>
#include <Framework/Foundation/Logger/CConsoleLogWriter.h>
#include <Framework/Foundation/Communication/Networking/Protocols/DNS/Resolver/CSocketDNSResolver.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketDNSMenu final : public CPPFoundation::Foundation::CConsoleMenu
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			bool												MIsLibraryInitialized;
			CPPFoundation::Foundation::CSocketDNSResolver			MSocketDNSResolver;

		private:
			void MenuItemExit(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemInitialize(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemUninitialize(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemHostNameToIPAddress(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemIPv4AddressToHostName(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);
			void MenuItemIPv6AddressToHostName(const CPPFoundation::Foundation::CConsoleMenuItemCommandParams& CommandParams);

		protected:
			virtual CPPFoundation::Foundation::CString GetStatus(void) const override;

		public:
			CSocketDNSMenu(CPPFoundation::Foundation::CConsoleLogWriter& LogWriter);
			virtual ~CSocketDNSMenu(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------