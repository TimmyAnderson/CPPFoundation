//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Threads/CThread.h>
#include <Framework/Foundation/Threads/CAtomic.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CMyThread3 final : public CPPFoundation::Foundation::CThread
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CPPFoundation::Foundation::CAtomic<Size>&				MCounter;

		protected:
			virtual void ThreadMethod(bool) override;
			virtual CPPFoundation::Foundation::CTimeout GetTimeout(void) override;

		public:
			void StartThread(void);
			void StopThread(void);
			void SetWorkerEvent(void);

		public:
			CMyThread3(CPPFoundation::Foundation::CLogWriter& LogWriter, CPPFoundation::Foundation::CAtomic<Size>& Counter);
			virtual ~CMyThread3(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------