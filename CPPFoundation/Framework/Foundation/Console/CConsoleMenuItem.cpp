//----------------------------------------------------------------------------------------------------------------------
#include "CConsoleMenuItem.h"
#include <Framework/Foundation/Collections/CVector.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	const CString												CConsoleMenuItem::HELP_PREFIX="?";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CConsoleMenuItem::CConsoleMenuItem(const CString& Command, const CString& Description, const CString& HelpText, EConsoleMenuItemType MenuItemType, const CConsoleMenuItemCallbackFunction& CallbackFunction)
		: MCommand(CString::ToUpperString(Command)), MDescription(Description), MHelpText(HelpText), MMenuItemType(MenuItemType), MMenuCallback(new CConsoleMenuItemCallbackFunction(CallbackFunction))
	{
		if (StartsWithHelpPrefix(Command)==true)
		{
			throw(CInvalidOperationException(CString::Format("COMMAND can't start with PREFIX [",HELP_PREFIX,"] !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CConsoleMenuItem::~CConsoleMenuItem(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CConsoleMenuItem::StartsWithHelpPrefix(const CString& Command)
	{
		if (Command.StartsWith(HELP_PREFIX)==true)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CConsoleMenuItem::RemoveHelpPrefix(const CString& Command)
	{
		CString													CommandString=Command;

		if (StartsWithHelpPrefix(Command)==true)
		{
			CommandString=CommandString.Erase(0,HELP_PREFIX.GetLength());

			return(CommandString);
		}
		else
		{
			return(CommandString);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CString& CConsoleMenuItem::GetCommand(void) const noexcept
	{
		return(MCommand);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CString& CConsoleMenuItem::GetDescription(void) const noexcept
	{
		return(MDescription);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CString& CConsoleMenuItem::GetHelpText(void) const noexcept
	{
		return(MHelpText);
	}
//----------------------------------------------------------------------------------------------------------------------
	EConsoleMenuItemType CConsoleMenuItem::GetMenuItemType(void) const noexcept
	{
		return(MMenuItemType);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CConsoleMenuItem::CallMenuCallback(const CConsoleMenuItemCommandParams& CommandParams) const
	{
		MMenuCallback->operator()(CommandParams);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CConsoleMenuItem::GetMenuItemDescriptiveText(void) const
	{
		CString													DescriptiveText=CString::Format("'",MCommand,"' - ",MDescription);

		return(DescriptiveText);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CConsoleMenuItem::GetMenuItemHelpText(void) const
	{
		if (MHelpText=="")
		{
			CString												DescriptiveText=CString::Format(MCommand," - ",MDescription);

			return(DescriptiveText);
		}
		else
		{
			CString												DescriptiveText=CString::Format(MCommand," ",MHelpText," - ",MDescription);

			return(DescriptiveText);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CConsoleMenuItem::GetMenuItemCompleteHelpText(void) const
	{
		if (MHelpText=="")
		{
			CString												DescriptiveText=CString::Format(MCommand," - ",MDescription);

			return(DescriptiveText);
		}
		else
		{
			CString												DescriptiveText=CString::Format(MCommand," ",MDescription," - ",MHelpText);

			return(DescriptiveText);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CConsoleMenuItem::CheckCommandText(const CString& CommandText) const
	{
		CString													FullCommandText=CString::ToUpperString(CommandText);
		CVector<CString>										Splits=FullCommandText.Split(" ");

		if (Splits.GetLength()>0)
		{
			if (Splits[0]==MCommand)
			{
				return(true);
			}
		}

		return(false);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------