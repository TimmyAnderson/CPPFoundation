//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Threads/CThread.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CThreadWithStopRequestedEvent final : public CPPFoundation::Foundation::CThread
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			Size												MCounter;
			Size												MStopActionCounter;

		protected:
			virtual void ThreadMethod(bool) override;
			virtual CPPFoundation::Foundation::CTimeout GetTimeout(void) override;

		protected:
			virtual void ThreadStopRequestedEvent(void) override;
			virtual void ThreadSafeUninitializationEvent(void) override;

		public:
			void StartThread(void);
			void StopThread(void);

		public:
			CThreadWithStopRequestedEvent(CPPFoundation::Foundation::CLogWriter& LogWriter);
			virtual ~CThreadWithStopRequestedEvent(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------