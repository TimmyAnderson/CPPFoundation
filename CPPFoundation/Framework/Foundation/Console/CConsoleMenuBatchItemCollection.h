//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <future>
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Strings/CString.h>
#include <Framework/Foundation/Collections/CMap.h>
#include <Framework/Foundation/Exceptions/CInvalidOperationException.h>
#include <Framework/Foundation/Threads/CMutex.h>
#include <Framework/Foundation/Threads/CLock.h>
#include <Framework/Foundation/Time/CTimeout.h>
#include "CConsoleMenuBatchItem.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CConsoleMenuBatchItemCollection final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			using												CBatchItemCollection=CMap<CString,CSPConsoleMenuBatchItem>;

		private:
			CBatchItemCollection								MBatchItems;

		public:
			void StartBatch(const CString& BatchName, std::future<void> Batch)
			{
				if (MBatchItems.Contains(BatchName)==true)
				{
					throw(CInvalidOperationException(CString::Format("BATCH [",BatchName,"] is already STARTED !")));
				}

				CSPConsoleMenuBatchItem							BatchItem(new CConsoleMenuBatchItem(BatchName,FUNCTION_MOVE(Batch)));

				BatchItem->RunBatch();

				MBatchItems.Add(BatchName,BatchItem);
			}

			void StopBatch(const CString& BatchName)
			{
				if (MBatchItems.Contains(BatchName)==true)
				{
					CSPConsoleMenuBatchItem						BatchItem=MBatchItems[BatchName];

					MBatchItems.Erase(BatchName);

					BatchItem->StopBatch();
				}
			}

			bool IsBatchRunning(const CString& BatchName)
			{
				if (MBatchItems.Contains(BatchName)==true)
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}

			bool WaitForBatchFinished(const CString& BatchName, uint64 Milliseconds)
			{
				if (MBatchItems.Contains(BatchName)==false)
				{
					return(true);
				}

				CSPConsoleMenuBatchItem							BatchItem=MBatchItems[BatchName];

				return(BatchItem->WaitForBatchFinish(Milliseconds));
			}

			Size GetNumberOfRunningBatches(void) const
			{
				return(MBatchItems.GetLength());
			}

		public:
			CConsoleMenuBatchItemCollection(void)
				: MBatchItems()
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------