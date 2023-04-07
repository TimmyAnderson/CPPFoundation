//----------------------------------------------------------------------------------------------------------------------
#include "CSchedulerManager.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	const CTimeout&												CSchedulerManager::MAXIMUM_CHECK_TIMEOUT=CTimeout(10*1000);
	const CTimeout&												CSchedulerManager::MAXIMUM_TIME_DIFFERENCE=CTimeout(5*60*1000);
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSchedulerManager::CSchedulerManager(CLogWriter& LogWriter, ISchedulerManagerCallback& Callback, const CTimeout& MaximumCheckTimeout, const CTimeout& MaximumTimeDifference)
		: CThread(LogWriter,CString::Format("SCHEDULER MANAGER THREAD")), MLogCategorySchedulerManager(CString::Format("SCHEDULER MANAGER")), MSchedulerManagerMutex(), MCallback(Callback), MSchedulerItemCollection(), MMaximumCheckTimeout(MaximumCheckTimeout), MMaximumTimeDifference(MaximumTimeDifference)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSchedulerManager::~CSchedulerManager(void)
	{
		StopScheduler();
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CLogCategory& CSchedulerManager::GetLogCategorySchedulerManager(void) const noexcept
	{
		return(MLogCategorySchedulerManager);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSchedulerManager::FireCallback(const CSchedulerItemID& SchedulerItemID)
	{
		try
		{
			MCallback.ExecuteSchedulerAction(SchedulerItemID);

			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySchedulerManager(),ELogRecordLevel::E_DEBUG,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("EXECUTION SCHEDULER ITEM [",SchedulerItemID,"] SUCCESSFULLY EXECUTED !")));
		}
		catch(const CException& E)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySchedulerManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("EXECUTION SCHEDULER ITEM [",SchedulerItemID,"] FAILED to EXECUTE !"),E));
			throw;
		}
		catch(...)
		{
			MACRO_WRITE_TO_LOG(GetLogWriter(),GetLogCategorySchedulerManager(),ELogRecordLevel::E_ERROR,MACRO_FUNCTION_NAME,MACRO_LINE_NUMBER,CLogRecord(CString::Format("EXECUTION SCHEDULER ITEM [",ToString(),"] FAILED to EXECUTE !"),CUnknownException()));
			throw;
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSchedulerManager::ThreadMethod(bool)
	{
		CSchedulerTime											Time=CSchedulerTime(CDateTime::GetCurrentLocalTime());

		for(CSPSchedulerItem SchedulerItem : MSchedulerItemCollection)
		{
			bool												ExecuteSchedulerItem=false;

			if (SchedulerItem->HasNextSchedulerTimeExpired(Time,MMaximumTimeDifference,ExecuteSchedulerItem)==true)
			{
				if (ExecuteSchedulerItem==true)
				{
					FireCallback(SchedulerItem->GetID());
				}
			}

			SchedulerItem->RecalculateNextSchedulerTime(Time);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CTimeout CSchedulerManager::GetTimeout(void)
	{
		CSchedulerTime											CurrentTime=CSchedulerTime(CDateTime::GetCurrentLocalTime());
		CTimeout												Timeout=CTimeout::GetInfinite();

		for(CSPSchedulerItem SchedulerItem : MSchedulerItemCollection)
		{
			CTimeout											SchedulerItemTimeout=SchedulerItem->GetTimeout(CSchedulerTime(CurrentTime),MMaximumCheckTimeout);

			Timeout=CTimeout::Min(Timeout,SchedulerItemTimeout);
		}

		return(Timeout);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSchedulerManager::ThreadSafeInitializationEvent(void)
	{
		CSchedulerTime											CurrentTime=CSchedulerTime(CDateTime::GetCurrentLocalTime());

		for(CSPSchedulerItem SchedulerItem : MSchedulerItemCollection)
		{
			SchedulerItem->ResetExecutionTimeout(CurrentTime);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CSchedulerManager::StartScheduler(const CSchedulerItemCollection& SchedulerItemCollection)
	{
		CLock													Lock(MSchedulerManagerMutex);
		{
			MSchedulerItemCollection=SchedulerItemCollection;

			InternalStartThread();
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSchedulerManager::StopScheduler(void) noexcept
	{
		CLock													Lock(MSchedulerManagerMutex);
		{
			InternalStopThread();
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------