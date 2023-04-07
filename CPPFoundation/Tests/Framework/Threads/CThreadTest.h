//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <atomic>
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Testing/CTest.h>
#include <Framework/Foundation/Threads/CAutoResetEvent.h>
#include <Framework/Foundation/Threads/CManualResetEvent.h>
#include <Framework/Foundation/Threads/CMutex.h>
#include <Framework/Foundation/Threads/CAtomic.h>
#include <Framework/Foundation/Threads/CAtomicSlim.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CThreadTest final : public CTest
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			Size												MNumberOfThreads;
			Size												MNumberOfIterationsForLockings;
			Size												MNumberOfIterationsForAtomics;

		private:
			static void StaticAtomicIncrement(Size& Value);

		private:
			void BasicThread(std::atomic<bool>& SharedVariable);
			void MutexThread(CPPFoundation::Foundation::CMutex& Mutex, Size NumberOfCycles, Size* Counter);
			void LockThread(CPPFoundation::Foundation::CMutex& Mutex, Size NumberOfCycles, Size* Counter);
			void LockWithSpinThread(CPPFoundation::Foundation::CMutex& Mutex, Size NumberOfCycles, Size* Counter);
			void AutoResetEventThread(CPPFoundation::Foundation::CAutoResetEvent& AutoResetEvent);
			void ManualResetEventThread(Size Index, CPPFoundation::Foundation::CManualResetEvent& ManualResetEvent, std::atomic<Size>& Counter);
			void AtomicIncrement(Size& Value);
			void AtomicThread(Size NumberOfCycles, CPPFoundation::Foundation::CAtomic<Size>& Counter);
			void AtomicSlimThread(Size NumberOfCycles, CPPFoundation::Foundation::CAtomicSlim<Size>& Counter);

		private:
			bool TestBasicThread(void);
			bool TestMutex(void);
			bool TestLock(void);
			bool TestLockWithSpin(void);
			bool TestAutoResetEvent(void);
			bool TestManualResetEvent(void);
			bool TestAtomic(void);
			bool TestAtomicSlim(void);
			bool TestMyThread1(void);
			bool TestMyThread2(void);
			bool TestMyThread3(void);
			bool TestShortLivingThread(void);
			bool TestDoubleStop(void);
			bool TestThreadWithStopRequestedEvent(void);
			bool TestAutoResetMultiEvent(void);
			bool TestManualResetMultiEvent(void);

		public:
			virtual bool ExecuteTest(void) override;

		public:
			CThreadTest(CPPFoundation::Foundation::CLogWriter& LogWriter, const CPPFoundation::Foundation::CLogCategory& LogCategoryTest, Size NumberOfThreads, Size NumberOfIterationsForLockings, Size NumberOfIterationsForAtomics);
			virtual ~CThreadTest(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------