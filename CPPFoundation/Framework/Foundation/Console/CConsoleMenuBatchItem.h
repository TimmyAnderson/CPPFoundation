//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <future>
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Strings/CString.h>
#include <Framework/Foundation/Threads/CAutoResetEvent.h>
#include <Framework/Foundation/Exceptions/CInvalidOperationException.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CConsoleMenuBatchItem final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CString												MBatchName;
			std::future<void>									MBatch;
			CAutoResetEvent										MBatchEvent;
			bool												MBatchIsRunning;

		public:
			void RunBatch(void)
			{
				if (MBatchIsRunning==true)
				{
					throw(CInvalidOperationException(CString::Format("BATCH [",MBatchName,"] is already STARTED !")));
				}

				MBatchEvent.Reset();
				MBatchIsRunning=true;
			}

			void StopBatch(void)
			{
				if (MBatchIsRunning==true)
				{
					MBatchEvent.Set();
					MBatchIsRunning=false;
				}

				MBatch.get();
			}

			bool WaitForBatchFinish(uint64 Milliseconds)
			{
				return(MBatchEvent.Wait(Milliseconds));
			}

		public:
			CConsoleMenuBatchItem(CString BatchName, std::future<void>&& Batch)
				: MBatchName(BatchName), MBatch(FUNCTION_MOVE(Batch)), MBatchEvent(false), MBatchIsRunning(false)
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPConsoleMenuBatchItem=CSharedPointer<CConsoleMenuBatchItem>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------