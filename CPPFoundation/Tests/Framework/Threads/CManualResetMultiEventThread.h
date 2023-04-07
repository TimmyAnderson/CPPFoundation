//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Threads/CManualResetMultiEvent.h>
#include <Framework/Foundation/Threads/CThread.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CManualResetMultiEventThread final : public CPPFoundation::Foundation::CThread
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CPPFoundation::Foundation::CManualResetMultiEvent<3>&	MEvent;
			bool												MCodeExecuted;

		protected:
			virtual void ThreadMethod(bool) override;
			virtual CPPFoundation::Foundation::CTimeout GetTimeout(void) override;

		protected:
			virtual void ThreadSafeUninitializationEvent(void) override;

		public:
			void StartThread(void);
			void StopThread(void);

		public:
			CManualResetMultiEventThread(CPPFoundation::Foundation::CLogWriter& LogWriter, CPPFoundation::Foundation::CManualResetMultiEvent<3>& Event);
			virtual ~CManualResetMultiEventThread(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------