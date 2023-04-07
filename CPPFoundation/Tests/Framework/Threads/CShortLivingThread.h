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
	class CShortLivingThread final : public CPPFoundation::Foundation::CThread
	{
//----------------------------------------------------------------------------------------------------------------------
		protected:
			virtual void ThreadMethod(bool) override;
			virtual CPPFoundation::Foundation::CTimeout GetTimeout(void) override;

		public:
			void StartThread(void);
			void StopThread(void);

		public:
			CShortLivingThread(CPPFoundation::Foundation::CLogWriter& LogWriter);
			virtual ~CShortLivingThread(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------