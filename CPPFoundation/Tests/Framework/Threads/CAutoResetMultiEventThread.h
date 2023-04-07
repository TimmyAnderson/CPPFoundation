//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Threads/CAutoResetMultiEvent.h>
#include <Framework/Foundation/Threads/CThread.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CAutoResetMultiEventThread final : public CPPFoundation::Foundation::CThread
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CPPFoundation::Foundation::CAutoResetMultiEvent<3>&	MEvent;
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
			CAutoResetMultiEventThread(CPPFoundation::Foundation::CLogWriter& LogWriter, CPPFoundation::Foundation::CAutoResetMultiEvent<3>& Event);
			virtual ~CAutoResetMultiEventThread(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------