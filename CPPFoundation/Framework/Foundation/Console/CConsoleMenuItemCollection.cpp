//----------------------------------------------------------------------------------------------------------------------
#include "CConsoleMenuItemCollection.h"
#include <Framework/Foundation/Exceptions/CInvalidOperationException.h>
#include "CConsoleHelper.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CConsoleMenuItemCollection::CConsoleMenuItemCollection(void)
		: MMenuItems()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CConsoleMenuItemCollection::~CConsoleMenuItemCollection(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CConsoleMenuItemCollection::ValidateCollection(void)
	{
		bool													ExitFound=false;
		Size													Length=MMenuItems.GetLength();

		for (Size Index=0;Index<Length;Index++)
		{
			if (MMenuItems[Index].GetMenuItemType()==EConsoleMenuItemType::E_ITEM_EXIT)
			{
				ExitFound=true;
				break;
			}
		}

		if (ExitFound==false)
		{
			return(false);
		}

		for (Size Index1=0;Index1<Length-1;Index1++)
		{
			for (Size Index2=Index1+1;Index2<Length;Index2++)
			{
				if (MMenuItems[Index1].GetCommand()==MMenuItems[Index2].GetCommand())
				{
					return(false);
				}
			}
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CConsoleMenuItemCollection::AddMenuItem(const CConsoleMenuItem& MenuItem)
	{
		Size													Position=MMenuItems.GetLength();

		MMenuItems.Add(MenuItem);

		if (ValidateCollection()==false)
		{
			MMenuItems.Erase(Position);

			throw(CInvalidOperationException("MENU ITEM COLLECTION MUST have an ITEM with [E_ITEM_EXIT] and ALL COMMANDS MUST be DIFFERENT !"));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CConsoleMenuItemCollection::GetSingleLineMenuString(void) const
	{
		CString													MenuString="Menu: ";

		for (Size Index=0,Length=MMenuItems.GetLength();Index<Length;Index++)
		{
			if (Index!=0)
			{
				MenuString+=", ";
			}

			MenuString+=MMenuItems[Index].GetMenuItemDescriptiveText();
		}

		return(MenuString);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CConsoleMenuItemCollection::GetMultiLineMenuString(void) const
	{
		CString													MenuString="Menu:";

		for (Size Index=0,Length=MMenuItems.GetLength();Index<Length;Index++)
		{
			if (Index==0)
			{
				MenuString+="\t";
			}
			else
			{
				MenuString+="\n\t";
			}


			MenuString+=MMenuItems[Index].GetMenuItemDescriptiveText();
		}

		return(MenuString);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CConsoleMenuItemCollection::ExecuteInput(CString Input) const
	{
		bool													ShowHelpText=false;

		if (CConsoleMenuItem::StartsWithHelpPrefix(Input)==true)
		{
			Input=CConsoleMenuItem::RemoveHelpPrefix(Input);

			if (Input.GetLength()==0)
			{
				for(const CConsoleMenuItem& MenuItem : MMenuItems)
				{
					CConsoleHelper::WriteLine(MenuItem.GetMenuItemCompleteHelpText());
				}

				return(false);
			}

			ShowHelpText=true;
		}

		const CConsoleMenuItem*									MenuItem=nullptr;

		for (Size Index=0,Length=MMenuItems.GetLength();Index<Length;Index++)
		{
			if (MMenuItems[Index].CheckCommandText(Input)==true)
			{
				MenuItem=&MMenuItems[Index];
				break;
			}
		}

		if (MenuItem!=nullptr)
		{
			if (ShowHelpText==false)
			{
				CConsoleMenuItemCommandParams					CommandParams(Input);

				MenuItem->CallMenuCallback(CommandParams);

				if (MenuItem->GetMenuItemType()==EConsoleMenuItemType::E_ITEM_EXIT)
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}
			else
			{
				CConsoleHelper::WriteLine(MenuItem->GetMenuItemHelpText());

				return(false);
			}
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------