//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <future>
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Foundation/Collections/CDequeue.h>
#include <Framework/Foundation/Logger/CConsoleLogWriter.h>
#include <Framework/Foundation/Time/CSteadyClock.h>
#include "CConsoleMenuBatchItemCollection.h"
#include "CConsoleMenuItem.h"
#include "CConsoleMenuItemCollection.h"
#include "CConsoleMenuItemCommandParams.h"
#include "EConsoleMenuLayout.h"
#include "EConsoleMenuOnPressEnterBehavior.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CConsoleMenu : public virtual CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		protected:
			using												CCommandHistoryCollection=CDequeue<CString>;

		private:
			static const Size									CONSOLE_WIDTH;
			static const CString								SEPARATOR;

		private:
			CLogWriter&											MLogWriter;
			const CLogCategory									MLogCategoryMenu;
			const CString										MMenuName;
			const EConsoleMenuLayout							MMenuLayout;
			const EConsoleMenuOnPressEnterBehavior				MOnPressEnterBehavior;
			const Size											MCommandHistoryLength;
			CConsoleMenuItemCollection							MMenuItems;
			CConsoleMenuBatchItemCollection						MBatchCollection;
			CString												MLastCommand;
			CCommandHistoryCollection							MCommandHistoryCollection;

		private:
			void ShowMainMenuSingleLine(void);
			void ShowMainMenuMultiLine(void);
			bool ReadInput(void);

		protected:
			virtual CString GetStatus(void) const=0;

		protected:
			CLogWriter& GetLogWriter(void) const noexcept;
			const CLogCategory& GetLogCategoryMenu(void) const noexcept;
			void AddMenuItem(const CConsoleMenuItem& MenuItem);
			void StartBatch(const CString& BatchName, std::future<void> Batch);
			void StopBatch(const CString& BatchName);
			bool IsBatchRunning(const CString& BatchName);
			bool WaitForBatchFinished(const CString& BatchName, uint64 Milliseconds);
			Size GetNumberOfRunningBatches(void) const;
			const CString& GetLastCommand(void) const noexcept;
			const CCommandHistoryCollection& GetCommandHistoryCollection(void) const noexcept;

		public:
			void ExecuteMainMenuLoop(void);
			void ExecuteCommand(const CString& Command);

		public:
			CConsoleMenu(CLogWriter& LogWriter, const CString& MenuName, EConsoleMenuLayout MenuLayout=EConsoleMenuLayout::E_SINGLE_LINE, EConsoleMenuOnPressEnterBehavior OnPressEnterBehavior=EConsoleMenuOnPressEnterBehavior::E_CLEAR_SCREEN, Size CommandHistoryLength=0);
			virtual ~CConsoleMenu(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------