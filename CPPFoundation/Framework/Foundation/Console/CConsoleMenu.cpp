//----------------------------------------------------------------------------------------------------------------------
#include "CConsoleMenu.h"
#include <Framework/Foundation/Exceptions/CException.h>
#include "CConsoleHelper.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const Size													CConsoleMenu::CONSOLE_WIDTH=79;
	const CString												CConsoleMenu::SEPARATOR=CString("").PadRight(CONSOLE_WIDTH,'-');
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CConsoleMenu::CConsoleMenu(CLogWriter& LogWriter, const CString& MenuName, EConsoleMenuLayout MenuLayout, EConsoleMenuOnPressEnterBehavior OnPressEnterBehavior, Size CommandHistoryLength)
		: MLogWriter(LogWriter), MLogCategoryMenu(CString::Format("MENU [",MenuName,"]")), MMenuName(MenuName), MMenuLayout(MenuLayout), MOnPressEnterBehavior(OnPressEnterBehavior), MCommandHistoryLength(CommandHistoryLength), MMenuItems(), MBatchCollection(), MLastCommand(), MCommandHistoryCollection()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CConsoleMenu::~CConsoleMenu(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CConsoleMenu::ShowMainMenuSingleLine(void)
	{
		CString													Text;

		Text+=SEPARATOR;
		Text+="\n";
		Text+=MMenuItems.GetSingleLineMenuString();

		CString													Status=GetStatus();

		if (Status!="")
		{
			Text+="\n";
			Text+=Status;
			Text+="\n";
		}

		Text+=SEPARATOR;
		Text+="\n";

		CConsoleHelper::Write(Text);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CConsoleMenu::ShowMainMenuMultiLine(void)
	{
		CString													Text;

		Text+=SEPARATOR;
		Text+="\n";
		Text+=MMenuItems.GetMultiLineMenuString();

		CString													Status=GetStatus();

		if (Status!="")
		{
			Text+="\n";
			Text+=Status;
			Text+="\n";
		}

		Text+=SEPARATOR;
		Text+="\n";

		CConsoleHelper::Write(Text);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CConsoleMenu::ReadInput(void)
	{
		CString													Command=CConsoleHelper::ReadLine();

		if (Command.IsEmpty()==false)
		{
			MLastCommand=Command;

			if (MCommandHistoryLength>0)
			{
				MCommandHistoryCollection.PushFront(Command);

				if (MCommandHistoryCollection.GetLength()>MCommandHistoryLength)
				{
					MCommandHistoryCollection.PopBack();
				}
			}

			return(MMenuItems.ExecuteInput(Command));
		}
		else
		{
			if (MOnPressEnterBehavior==EConsoleMenuOnPressEnterBehavior::E_CLEAR_SCREEN)
			{
				CConsoleHelper::Clear();

				return(false);
			}
			else
			{
				return(MMenuItems.ExecuteInput(MLastCommand));
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CLogWriter& CConsoleMenu::GetLogWriter(void) const noexcept
	{
		return(MLogWriter);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CLogCategory& CConsoleMenu::GetLogCategoryMenu(void) const noexcept
	{
		return(MLogCategoryMenu);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CConsoleMenu::AddMenuItem(const CConsoleMenuItem& MenuItem)
	{
		MMenuItems.AddMenuItem(MenuItem);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CConsoleMenu::StartBatch(const CString& BatchName, future<void> Batch)
	{
		MBatchCollection.StartBatch(BatchName,FUNCTION_MOVE(Batch));
	}
//----------------------------------------------------------------------------------------------------------------------
	void CConsoleMenu::StopBatch(const CString& BatchName)
	{
		MBatchCollection.StopBatch(BatchName);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CConsoleMenu::IsBatchRunning(const CString& BatchName)
	{
		return(MBatchCollection.IsBatchRunning(BatchName));
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CConsoleMenu::WaitForBatchFinished(const CString& BatchName, uint64 Milliseconds)
	{
		return(MBatchCollection.WaitForBatchFinished(BatchName,Milliseconds));
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CConsoleMenu::GetNumberOfRunningBatches(void) const
	{
		return(MBatchCollection.GetNumberOfRunningBatches());
	}
//----------------------------------------------------------------------------------------------------------------------
	const CString& CConsoleMenu::GetLastCommand(void) const noexcept
	{
		return(MLastCommand);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CConsoleMenu::CCommandHistoryCollection& CConsoleMenu::GetCommandHistoryCollection(void) const noexcept
	{
		return(MCommandHistoryCollection);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CConsoleMenu::ExecuteMainMenuLoop(void)
	{
		while(true)
		{
			try
			{
				if (MMenuLayout==EConsoleMenuLayout::E_SINGLE_LINE)
				{
					ShowMainMenuSingleLine();
				}
				else
				{
					ShowMainMenuMultiLine();
				}

				if (ReadInput()==true)
				{
					break;
				}
			}
			catch(const CException& E)
			{
				CConsoleHelper::WriteLine(CString::Format("!!!!! FATAL EXCEPTION [",E.GetMessage(),"] in MAIN MENU ! !!!!!"));
			}
			catch(...)
			{
				CConsoleHelper::WriteLine("!!!!! FATAL EXCEPTION in MAIN MENU ! !!!!!");
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CConsoleMenu::ExecuteCommand(const CString& Command)
	{
		MMenuItems.ExecuteInput(Command);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------