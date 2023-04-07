//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Threads/CThread.h>
#include "ISchedulerManagerCallback.h"
#include "CSchedulerItem.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSchedulerManager final : public CThread
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			static const CTimeout&								MAXIMUM_CHECK_TIMEOUT;
			static const CTimeout&								MAXIMUM_TIME_DIFFERENCE;

		private:
			const CLogCategory									MLogCategorySchedulerManager;
			CMutex												MSchedulerManagerMutex;
			ISchedulerManagerCallback&							MCallback;
			CSchedulerItemCollection							MSchedulerItemCollection;
			CTimeout											MMaximumCheckTimeout;
			CTimeout											MMaximumTimeDifference;

		public:
			CSchedulerManager& operator=(const CSchedulerManager& Other)=delete;

		private:
			const CLogCategory& GetLogCategorySchedulerManager(void) const noexcept;
			void FireCallback(const CSchedulerItemID& SchedulerItemID);

		protected:
			virtual void ThreadMethod(bool EventSet) override;
			virtual CTimeout GetTimeout(void) override;
			virtual void ThreadSafeInitializationEvent(void) override;

		public:
			void StartScheduler(const CSchedulerItemCollection& SchedulerItemCollection);
			void StopScheduler(void) noexcept;

		public:
			CSchedulerManager(CLogWriter& LogWriter, ISchedulerManagerCallback& Callback, const CTimeout& MaximumCheckTimeout=MAXIMUM_CHECK_TIMEOUT, const CTimeout& MaximumTimeDifference=MAXIMUM_TIME_DIFFERENCE);
			CSchedulerManager(const CSchedulerManager& Other)=delete;
			virtual ~CSchedulerManager(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------