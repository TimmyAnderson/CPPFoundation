//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Strings/CString.h>
#include <Framework/Foundation/Exceptions/CInvalidOperationException.h>
#include "CConsoleMenuItemCommandParams.h"
#include "EConsoleMenuItemType.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CConsoleMenuItem final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			static const CString								HELP_PREFIX;

		private:
			CString												MCommand;
			CString												MDescription;
			CString												MHelpText;
			EConsoleMenuItemType								MMenuItemType;
			CSPConsoleMenuItemCallback							MMenuCallback;

		public:
			static bool StartsWithHelpPrefix(const CString& Command);
			static CString RemoveHelpPrefix(const CString& Command);

		public:
			const CString& GetCommand(void) const noexcept;
			const CString& GetDescription(void) const noexcept;
			const CString& GetHelpText(void) const noexcept;
			EConsoleMenuItemType GetMenuItemType(void) const noexcept;
			void CallMenuCallback(const CConsoleMenuItemCommandParams& CommandParams) const;

		public:
			CString GetMenuItemDescriptiveText(void) const;
			CString GetMenuItemHelpText(void) const;
			CString GetMenuItemCompleteHelpText(void) const;
			bool CheckCommandText(const CString& CommandText) const;

		public:
			CConsoleMenuItem(const CString& Command, const CString& Description, const CString& HelpText, EConsoleMenuItemType MenuItemType, const CConsoleMenuItemCallbackFunction& CallbackFunction);

			template<typename TClassType>
			CConsoleMenuItem(const CString& Command, const CString& Description, const CString& HelpText, EConsoleMenuItemType MenuItemType, const CConsoleMenuItemCallbackMethod<TClassType>& CallbackMethod)
				: MCommand(CString::ToUpperString(Command)), MDescription(Description), MHelpText(HelpText), MMenuItemType(MenuItemType), MMenuCallback(new CConsoleMenuItemCallbackMethod<TClassType>(CallbackMethod))
			{
				if (StartsWithHelpPrefix(Command)==true)
				{
					throw(CInvalidOperationException(CString::Format("COMMAND can't start with PREFIX [",HELP_PREFIX,"] !")));
				}
			}

			virtual ~CConsoleMenuItem(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------