//----------------------------------------------------------------------------------------------------------------------
#include "CThreadTest.h"
#include <thread>
#include <chrono>
#include <system_error>
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Foundation/Collections/CVector.h>
#include <Framework/Foundation/Console/CConsoleHelper.h>
#include <Framework/Foundation/Logger/CConsoleLogWriter.h>
#include <Framework/Foundation/Threads/CLock.h>
#include <Framework/Foundation/Types/CFunction.h>
#include <Framework/Foundation/Types/CMethod.h>
#include <Framework/Platform/Global/CFunctions.h>
#include "CMyThread1.h"
#include "CMyThread2.h"
#include "CMyThread3.h"
#include "CShortLivingThread.h"
#include "CLongLivingThread.h"
#include "CThreadWithStopRequestedEvent.h"
#include "CAutoResetMultiEventThread.h"
#include "CManualResetMultiEventThread.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace std;
	using namespace std::chrono;
	using namespace CPPFoundation::Foundation;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CThreadTest::CThreadTest(CLogWriter& LogWriter, const CLogCategory& LogCategoryTest, Size NumberOfThreads, Size NumberOfIterationsForLockings, Size NumberOfIterationsForAtomics)
		: CTest(LogWriter,LogCategoryTest,"THREAD TEST"), MNumberOfThreads(NumberOfThreads), MNumberOfIterationsForLockings(NumberOfIterationsForLockings), MNumberOfIterationsForAtomics(NumberOfIterationsForAtomics)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CThreadTest::~CThreadTest(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CThreadTest::StaticAtomicIncrement(Size& Value)
	{
		Value=Value+1;
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CThreadTest::BasicThread(atomic<bool>& SharedVariable)
	{
		this_thread::sleep_for(duration<int,ratio<1,1000>>(100));

		SharedVariable.store(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CThreadTest::MutexThread(CMutex& Mutex, Size NumberOfCycles, Size* Counter)
	{
		Mutex.Lock();

		for(Size Index=0;Index<NumberOfCycles;Index++)
		{
			*Counter=*Counter+1;
		}

		Mutex.Unlock();
	}
//----------------------------------------------------------------------------------------------------------------------
	void CThreadTest::LockThread(CMutex& Mutex, Size NumberOfCycles, Size* Counter)
	{
		CLock													Lock(Mutex);

		for(Size Index=0;Index<NumberOfCycles;Index++)
		{
			*Counter=*Counter+1;
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CThreadTest::LockWithSpinThread(CMutex& Mutex, Size NumberOfCycles, Size* Counter)
	{
		CLock													Lock(Mutex,100000000);

		for(Size Index=0;Index<NumberOfCycles;Index++)
		{
			*Counter=*Counter+1;
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CThreadTest::AutoResetEventThread(CAutoResetEvent& AutoResetEvent)
	{
		if (AutoResetEvent.Wait(500)==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST AUTO RESET EVENT for THREAD FAILED ! TIMEOUT 1 NOT EXPIRED !\n"));
		}

		if (AutoResetEvent.Wait(1000)==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST AUTO RESET EVENT for THREAD FAILED ! TIMEOUT 2 EXPIRED !\n"));
		}

		if (AutoResetEvent.Wait(1000)==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST AUTO RESET EVENT for THREAD FAILED ! TIMEOUT 3 NOT EXPIRED !\n"));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CThreadTest::ManualResetEventThread(Size Index, CManualResetEvent& ManualResetEvent, atomic<Size>& Counter)
	{
		bool													TimeoutExpired1=ManualResetEvent.Wait(1000);

		if (TimeoutExpired1==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MANUAL RESET EVENT for THREAD [",Index,"] FAILED ! TIMEOUT 1 EXPIRED !\n"));

			return;
		}

		this_thread::sleep_for(duration<int,ratio<1,1000>>(500));

		bool													TimeoutExpired2=ManualResetEvent.Wait(1000);

		if (TimeoutExpired2==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MANUAL RESET EVENT for THREAD [",Index,"] FAILED ! TIMEOUT 2 EXPIRED !\n"));

			return;
		}

		this_thread::sleep_for(duration<int,ratio<1,1000>>(500));

		bool													TimeoutExpired3=ManualResetEvent.Wait(1000);

		if (TimeoutExpired3==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MANUAL RESET EVENT for THREAD [",Index,"] FAILED ! TIMEOUT 3 NOT EXPIRED !\n"));

			return;
		}

		Counter++;
	}
//----------------------------------------------------------------------------------------------------------------------
	void CThreadTest::AtomicIncrement(Size& Value)
	{
		Value=Value+1;
	}
//----------------------------------------------------------------------------------------------------------------------
	void CThreadTest::AtomicThread(Size NumberOfCycles, CAtomic<Size>& Counter)
	{
		CMethod<CThreadTest,void(Size&)>						Callback1(this,&CThreadTest::AtomicIncrement);
		function<void(Size&)>									Callback2(&CThreadTest::StaticAtomicIncrement);

		for(Size Index=0;Index<NumberOfCycles/2;Index++)
		{
			Counter.Execute(Callback1);
			Counter.Execute(Callback2);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CThreadTest::AtomicSlimThread(Size NumberOfCycles, CAtomicSlim<Size>& Counter)
	{
		for(Size Index=0;Index<NumberOfCycles;Index++)
		{
			Counter++;
			Counter--;
			++Counter;
			--Counter;

			++Counter;
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CThreadTest::TestBasicThread(void)
	{
		std::thread												Thread;
		atomic<bool>											SharedVariable(false);

		try
		{
			Thread=thread(&CThreadTest::BasicThread,*this,ref(SharedVariable));
		}
		catch(const system_error&)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST BASIC THREAD FAILED ! Can't CREATE THREAD !\n"));

			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST BASIC THREADS FAILED ! Can't CREATE THREAD ! UNEXPECTED EXCEPTION !\n"));

			return(false);
		}

		try
		{
			if (Thread.joinable()==true)
			{
				Thread.join();
			}
		}
		catch(const system_error&)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST BASIC THREAD FAILED ! Can't JOIN THREAD !\n"));

			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST BASIC THREAD FAILED ! Can't JOIN THREAD ! UNEXPECTED EXCEPTION !\n"));

			return(false);
		}

		if (SharedVariable.load()==false)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST BASIC THREAD FAILED ! SHARED VARIABLE was NOT SET !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CThreadTest::TestMutex(void)
	{
		Size													Counter=0;
		bool													IsError=false;
		CVector<thread>											Threads;
		CMutex													Mutex;

		for(Size Index=0;Index<MNumberOfThreads;Index++)
		{
			Threads.Add(thread());
		}

		for(Size Index=0;Index<MNumberOfThreads;Index++)
		{
			try
			{
				Threads[Index]=thread(&CThreadTest::MutexThread,*this,ref(Mutex),MNumberOfIterationsForLockings,&Counter);
			}
			catch(...)
			{
				IsError=true;
				CConsoleHelper::WriteLine(CString::Format("\tTEST MUTEX FAILED ! Can't CREATE THREAD !\n"));
			}
		}

		for(Size Index=0;Index<MNumberOfThreads;Index++)
		{
			try
			{
				if (Threads[Index].joinable()==true)
				{
					Threads[Index].join();
				}
			}
			catch(...)
			{
				IsError=true;
				CConsoleHelper::WriteLine(CString::Format("\tTEST MUTEX FAILED ! Can't JOIN THREAD !\n"));
			}
		}

		if (IsError==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MUTEX FAILED ! THREAD ERROR !\n"));
			
			return(false);
		}

		Size													ExpectedValue=(MNumberOfThreads*MNumberOfIterationsForLockings);

		if (Counter!=ExpectedValue)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MUTEX FAILED ! VARIABLE was NOT SYNCHRONIZED ! VALUE [",Counter,"] EXPECTED VAULE [",ExpectedValue,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CThreadTest::TestLock(void)
	{
		Size													Counter=0;
		bool													IsError=false;
		CVector<thread>											Threads;
		CMutex													Mutex;

		for(Size Index=0;Index<MNumberOfThreads;Index++)
		{
			Threads.Add(thread());
		}

		for(Size Index=0;Index<MNumberOfThreads;Index++)
		{
			try
			{
				Threads[Index]=thread(&CThreadTest::LockThread,*this,ref(Mutex),MNumberOfIterationsForLockings,&Counter);
			}
			catch(...)
			{
				IsError=true;
				CConsoleHelper::WriteLine(CString::Format("\tTEST LOCK FAILED ! Can't CREATE THREAD !\n"));
			}
		}

		for(Size Index=0;Index<MNumberOfThreads;Index++)
		{
			try
			{
				if (Threads[Index].joinable()==true)
				{
					Threads[Index].join();
				}
			}
			catch(...)
			{
				IsError=true;
				CConsoleHelper::WriteLine(CString::Format("\tTEST LOCK FAILED ! Can't JOIN THREAD !\n"));
			}
		}

		if (IsError==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST LOCK FAILED ! THREAD ERROR !\n"));
			
			return(false);
		}

		Size													ExpectedValue=(MNumberOfThreads*MNumberOfIterationsForLockings);

		if (Counter!=ExpectedValue)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST LOCK FAILED ! VARIABLE was NOT SYNCHRONIZED ! VALUE [",Counter,"] EXPECTED VAULE [",ExpectedValue,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CThreadTest::TestLockWithSpin(void)
	{
		Size													Counter=0;
		bool													IsError=false;
		CVector<thread>											Threads;
		CMutex													Mutex;

		for(Size Index=0;Index<MNumberOfThreads;Index++)
		{
			Threads.Add(thread());
		}

		for(Size Index=0;Index<MNumberOfThreads;Index++)
		{
			try
			{
				Threads[Index]=thread(&CThreadTest::LockWithSpinThread,*this,ref(Mutex),MNumberOfIterationsForLockings,&Counter);
			}
			catch(...)
			{
				IsError=true;
				CConsoleHelper::WriteLine(CString::Format("\tTEST LOCK WITH SPIN FAILED ! Can't CREATE THREAD !\n"));
			}
		}

		for(Size Index=0;Index<MNumberOfThreads;Index++)
		{
			try
			{
				if (Threads[Index].joinable()==true)
				{
					Threads[Index].join();
				}
			}
			catch(...)
			{
				IsError=true;
				CConsoleHelper::WriteLine(CString::Format("\tTEST LOCK WITH SPIN FAILED ! Can't JOIN THREAD !\n"));
			}
		}

		if (IsError==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST LOCK WITH SPIN FAILED ! THREAD ERROR !\n"));
			
			return(false);
		}

		Size													ExpectedValue=(MNumberOfThreads*MNumberOfIterationsForLockings);

		if (Counter!=ExpectedValue)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST LOCK WITH SPIN FAILED ! VARIABLE was NOT SYNCHRONIZED ! VALUE [",Counter,"] EXPECTED VAULE [",ExpectedValue,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CThreadTest::TestAutoResetEvent(void)
	{
		CAutoResetEvent											AutoResetEvent(false);
		bool													IsError=false;
		thread													Thread;

		try
		{
			Thread=thread(&CThreadTest::AutoResetEventThread,*this,ref(AutoResetEvent));

			this_thread::sleep_for(duration<int,ratio<1,1000>>(1000));

			AutoResetEvent.Set();
		}
		catch(...)
		{
			IsError=true;
			CConsoleHelper::WriteLine(CString::Format("\tTEST AUTO RESET EVENT FAILED ! Can't CREATE THREAD !\n"));
		}

		try
		{
			if (Thread.joinable()==true)
			{
				Thread.join();
			}
		}
		catch(...)
		{
			IsError=true;
			CConsoleHelper::WriteLine(CString::Format("\tTEST MANUAL RESET EVENT FAILED ! Can't JOIN THREAD !\n"));
		}

		if (IsError==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST AUTO RESET EVENT FAILED ! THREAD ERROR !\n"));
			
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CThreadTest::TestManualResetEvent(void)
	{
		bool													IsError=false;
		CVector<thread>											Threads;
		atomic<Size>											Counter(0);
		CManualResetEvent										ManualResetEvent;

		for(Size Index=0;Index<MNumberOfThreads;Index++)
		{
			Threads.Add(thread());
		}

		for(Size Index=0;Index<MNumberOfThreads;Index++)
		{
			try
			{
				Threads[Index]=thread(&CThreadTest::ManualResetEventThread,*this,(Index+1),ref(ManualResetEvent),ref(Counter));
			}
			catch(...)
			{
				IsError=true;
				CConsoleHelper::WriteLine(CString::Format("\tTEST MANUAL RESET EVENT FAILED ! Can't CREATE THREAD !\n"));
			}
		}

		this_thread::sleep_for(duration<int,ratio<1,1000>>(200));

		ManualResetEvent.Set();

		this_thread::sleep_for(duration<int,ratio<1,1000>>(200));

		ManualResetEvent.Reset();

		this_thread::sleep_for(duration<int,ratio<1,1000>>(500));

		ManualResetEvent.Set();

		this_thread::sleep_for(duration<int,ratio<1,1000>>(200));

		ManualResetEvent.Reset();

		for(Size Index=0;Index<MNumberOfThreads;Index++)
		{
			try
			{
				if (Threads[Index].joinable()==true)
				{
					Threads[Index].join();
				}
			}
			catch(...)
			{
				IsError=true;
				CConsoleHelper::WriteLine(CString::Format("\tTEST MANUAL RESET EVENT FAILED ! Can't JOIN THREAD !\n"));
			}
		}

		if (IsError==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MANUAL RESET EVENT FAILED ! THREAD ERROR !\n"));
			
			return(false);
		}

		if (Counter!=MNumberOfThreads)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MANUAL RESET EVENT FAILED ! VARIABLE VALUE [",Counter.load(),"] is NOT EQUAL to EXPECTED VAULE [",MNumberOfThreads,"] !\n"));
			
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CThreadTest::TestAtomic(void)
	{
		CAtomic<Size>											Counter(0);
		bool													IsError=false;
		CVector<thread>											Threads;

		for(Size Index=0;Index<MNumberOfThreads;Index++)
		{
			Threads.Add(thread());
		}

		for(Size Index=0;Index<MNumberOfThreads;Index++)
		{
			try
			{
				Threads[Index]=thread(&CThreadTest::AtomicThread,*this,MNumberOfIterationsForAtomics,ref(Counter));
			}
			catch(...)
			{
				IsError=true;
				CConsoleHelper::WriteLine(CString::Format("\tTEST ATOMIC FAILED ! Can't CREATE THREAD !\n"));
			}
		}

		for(Size Index=0;Index<MNumberOfThreads;Index++)
		{
			try
			{
				if (Threads[Index].joinable()==true)
				{
					Threads[Index].join();
				}
			}
			catch(...)
			{
				IsError=true;
				CConsoleHelper::WriteLine(CString::Format("\tTEST ATOMIC FAILED ! Can't JOIN THREAD !\n"));
			}
		}

		if (IsError==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ATOMIC FAILED ! THREAD ERROR !\n"));
			
			return(false);
		}

		Size													ExpectedValue=(MNumberOfThreads*MNumberOfIterationsForAtomics);
		Size													Value=Counter.GetValue();

		if (Value!=ExpectedValue)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ATOMIC FAILED ! VARIABLE was NOT SYNCHRONIZED ! VALUE [",Value,"] EXPECTED VAULE [",ExpectedValue,"] !\n"));

			return(false);
		}

		CAtomic<Size>											AtomicValue;

		AtomicValue.SetValue(100);

		Size													CurrentAtomicValue=AtomicValue.GetValue();
		Size													ExpectedAtomicValue=100;

		if (CurrentAtomicValue!=ExpectedAtomicValue)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ATOMIC FAILED ! VALUE [",CurrentAtomicValue,"] EXPECTED VAULE [",ExpectedAtomicValue,"] !\n"));

			return(false);
		}

		AtomicValue.Increment();
		CurrentAtomicValue=AtomicValue.GetValue();
		ExpectedAtomicValue++;

		if (CurrentAtomicValue!=ExpectedAtomicValue)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ATOMIC FAILED ! VALUE [",CurrentAtomicValue,"] EXPECTED VAULE [",ExpectedAtomicValue,"] !\n"));

			return(false);
		}

		AtomicValue.Increment(5);
		CurrentAtomicValue=AtomicValue.GetValue();
		ExpectedAtomicValue+=5;

		if (CurrentAtomicValue!=ExpectedAtomicValue)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ATOMIC FAILED ! VALUE [",CurrentAtomicValue,"] EXPECTED VAULE [",ExpectedAtomicValue,"] !\n"));

			return(false);
		}

		AtomicValue.Decrement();
		CurrentAtomicValue=AtomicValue.GetValue();
		ExpectedAtomicValue--;

		if (CurrentAtomicValue!=ExpectedAtomicValue)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ATOMIC FAILED ! VALUE [",CurrentAtomicValue,"] EXPECTED VAULE [",ExpectedAtomicValue,"] !\n"));

			return(false);
		}

		AtomicValue.Decrement(5);
		CurrentAtomicValue=AtomicValue.GetValue();
		ExpectedAtomicValue-=5;

		if (CurrentAtomicValue!=ExpectedAtomicValue)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ATOMIC FAILED ! VALUE [",CurrentAtomicValue,"] EXPECTED VAULE [",ExpectedAtomicValue,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CThreadTest::TestAtomicSlim(void)
	{
		CAtomicSlim<Size>										Counter(0);
		bool													IsError=false;
		CVector<thread>											Threads;

		for(Size Index=0;Index<MNumberOfThreads;Index++)
		{
			Threads.Add(thread());
		}

		for(Size Index=0;Index<MNumberOfThreads;Index++)
		{
			try
			{
				Threads[Index]=thread(&CThreadTest::AtomicSlimThread,*this,MNumberOfIterationsForAtomics,ref(Counter));
			}
			catch(...)
			{
				IsError=true;
				CConsoleHelper::WriteLine(CString::Format("\tTEST ATOMIC SLIM FAILED ! Can't CREATE THREAD !\n"));
			}
		}

		for(Size Index=0;Index<MNumberOfThreads;Index++)
		{
			try
			{
				if (Threads[Index].joinable()==true)
				{
					Threads[Index].join();
				}
			}
			catch(...)
			{
				IsError=true;
				CConsoleHelper::WriteLine(CString::Format("\tTEST ATOMIC SLIM FAILED ! Can't JOIN THREAD !\n"));
			}
		}

		if (IsError==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ATOMIC SLIM FAILED ! THREAD ERROR !\n"));
			
			return(false);
		}

		Size													ExpectedValue=(MNumberOfThreads*MNumberOfIterationsForAtomics);
		Size													Value=Counter.GetValue();

		if (Value!=ExpectedValue)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ATOMIC SLIM FAILED ! VARIABLE was NOT SYNCHRONIZED ! VALUE [",Value,"] EXPECTED VAULE [",ExpectedValue,"] !\n"));

			return(false);
		}

		CAtomicSlim<Size>										AtomicValue;

		AtomicValue.SetValue(100);

		Size													CurrentAtomicValue=AtomicValue.GetValue();
		Size													ExpectedAtomicValue=100;

		if (CurrentAtomicValue!=ExpectedAtomicValue)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ATOMIC SLIM FAILED ! VALUE [",CurrentAtomicValue,"] EXPECTED VAULE [",ExpectedAtomicValue,"] !\n"));

			return(false);
		}

		AtomicValue=200;

		CurrentAtomicValue=AtomicValue.GetValue();
		ExpectedAtomicValue=200;

		if (CurrentAtomicValue!=ExpectedAtomicValue)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ATOMIC SLIM FAILED ! VALUE [",CurrentAtomicValue,"] EXPECTED VAULE [",ExpectedAtomicValue,"] !\n"));

			return(false);
		}

		Size													OldValue=AtomicValue.Exchange(300);

		CurrentAtomicValue=OldValue;
		ExpectedAtomicValue=200;

		if (CurrentAtomicValue!=ExpectedAtomicValue)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ATOMIC SLIM FAILED ! VALUE [",CurrentAtomicValue,"] EXPECTED VAULE [",ExpectedAtomicValue,"] !\n"));

			return(false);
		}

		CurrentAtomicValue=AtomicValue.GetValue();
		ExpectedAtomicValue=300;

		if (CurrentAtomicValue!=ExpectedAtomicValue)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST ATOMIC SLIM FAILED ! VALUE [",CurrentAtomicValue,"] EXPECTED VAULE [",ExpectedAtomicValue,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CThreadTest::TestMyThread1(void)
	{
		CLogSource												Source("DUMMY");
		CConsoleLogWriter										LogWriter(Source);
		CAtomic<Size>											Counter(0);
		CMyThread1												Thread(LogWriter,Counter);

		for(Size Index=0;Index<3;Index++)
		{
			Counter.SetValue(0);

			try
			{
				Thread.StartThread();

				CThread::Sleep(5500);

				Thread.StopThread();
			}
			catch(const CException&)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST MY THREAD 1 FAILED ! THREAD ERROR !\n"));
				return(false);
			}
			catch(...)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST MY THREAD 1 FAILED ! THREAD ERROR !\n"));
				return(false);
			}

			Size												ExpectedValue=5;

			if (Counter.GetValue()!=ExpectedValue)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST MY THREAD 1 FAILED ! COUNTER contains VALUE [",Counter.GetValue(),"] that is DIFFERENT to EXPECTED VALUE [",ExpectedValue,"] !\n"));
				return(false);
			}

			if (Thread.IsThreadRunning()==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST MY THREAD 1 FAILED ! THREAD is STILL RUNNING !\n"));
				return(false);
			}

			if (Thread.IsThreadJoinable()==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST MY THREAD 1 FAILED ! THREAD is STILL JOINABLE !\n"));
				return(false);
			}
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CThreadTest::TestMyThread2(void)
	{
		CLogSource												Source("DUMMY");
		CConsoleLogWriter										LogWriter(Source);
		CMyThread2												Thread(LogWriter);

		for(Size Index=0;Index<3;Index++)
		{
			try
			{
				Thread.StartThread();

				CThread::Sleep(3000);

				Thread.StopThread(2000);

				if (Thread.IsThreadRunning()==true)
				{
					CConsoleHelper::WriteLine(CString::Format("\tTEST MY THREAD 2 FAILED ! THREAD is STILL RUNNING !\n"));
					return(false);
				}

				if (Thread.IsThreadJoinable()==true)
				{
					CConsoleHelper::WriteLine(CString::Format("\tTEST MY THREAD 2 FAILED ! THREAD is STILL JOINABLE !\n"));
					return(false);
				}
			}
			catch(const CException&)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST MY THREAD 2 FAILED ! THREAD ERROR !\n"));
				return(false);
			}
			catch(...)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST MY THREAD 2 FAILED ! THREAD ERROR !\n"));
				return(false);
			}
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CThreadTest::TestMyThread3(void)
	{
		const Size												NumberOfIterations=100;
		CLogSource												Source("DUMMY");
		CConsoleLogWriter										LogWriter(Source);
		CAtomic<Size>											Counter(0);
		CMyThread3												Thread(LogWriter,Counter);

		try
		{
			Thread.StartThread();

			CThread::Sleep(1000);

			for(Size Index=0;Index<NumberOfIterations;Index++)
			{
				Thread.SetWorkerEvent();

				CThread::Sleep(100);
			}

			Thread.StopThread();

			if (Counter.GetValue()!=NumberOfIterations)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST MY THREAD 3 FAILED ! COUNTER contains VALUE [",Counter.GetValue(),"] that is DIFFERENT to EXPECTED VALUE [",NumberOfIterations,"] !\n"));
				return(false);
			}

			if (Thread.IsThreadRunning()==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST MY THREAD 3 FAILED ! THREAD is STILL RUNNING !\n"));
				return(false);
			}

			if (Thread.IsThreadJoinable()==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST MY THREAD 3 FAILED ! THREAD is STILL JOINABLE !\n"));
				return(false);
			}
		}
		catch(const CException&)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MY THREAD 3 FAILED ! THREAD ERROR !\n"));
			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MY THREAD 3 FAILED ! THREAD ERROR !\n"));
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CThreadTest::TestShortLivingThread(void)
	{
		CLogSource												Source("DUMMY");
		CConsoleLogWriter										LogWriter(Source);
		// SHORT LIVING THREAD.
		CShortLivingThread										Thread(LogWriter);

		try
		{
			for(Size Index=0;Index<3;Index++)
			{
				Thread.StartThread();

				// WAIT for SHORT LIVING THREAD to FINISH.
				CThread::Sleep(1000);

				// Try to STOP already FINISHED THREAD.
				Thread.StopThread();

				if (Thread.IsThreadRunning()==true)
				{
					CConsoleHelper::WriteLine(CString::Format("\tTEST SHORT LIVING THREAD FAILED ! THREAD is STILL RUNNING !\n"));
					return(false);
				}

				if (Thread.IsThreadJoinable()==true)
				{
					CConsoleHelper::WriteLine(CString::Format("\tTEST SHORT LIVING THREAD FAILED ! THREAD is STILL JOINABLE !\n"));
					return(false);
				}
			}
		}
		catch(const CException&)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST SHORT LIVING THREAD FAILED ! THREAD ERROR !\n"));
			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST SHORT LIVING THREAD FAILED ! THREAD ERROR !\n"));
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CThreadTest::TestDoubleStop(void)
	{
		CLogSource												Source("DUMMY");
		CConsoleLogWriter										LogWriter(Source);
		CLongLivingThread										Thread(LogWriter);

		try
		{
			for(Size Index=0;Index<3;Index++)
			{
				if (Thread.IsThreadRunning()==true)
				{
					CConsoleHelper::WriteLine(CString::Format("\tTEST DOUBLE STOP FAILED ! THREAD is STILL RUNNING !\n"));
					return(false);
				}

				if (Thread.IsThreadJoinable()==true)
				{
					CConsoleHelper::WriteLine(CString::Format("\tTEST DOUBLE STOP FAILED ! THREAD is STILL JOINABLE !\n"));
					return(false);
				}

				Thread.StartThread();

				// WAIT for a WHILE.
				CThread::Sleep(3000);

				Thread.StopThread();

				if (Thread.IsThreadRunning()==true)
				{
					CConsoleHelper::WriteLine(CString::Format("\tTEST DOUBLE STOP FAILED ! THREAD is STILL RUNNING !\n"));
					return(false);
				}

				if (Thread.IsThreadJoinable()==true)
				{
					CConsoleHelper::WriteLine(CString::Format("\tTEST DOUBLE STOP FAILED ! THREAD is STILL JOINABLE !\n"));
					return(false);
				}

				// Try to STOP already STOPPED THREAD.
				Thread.StopThread();

				if (Thread.IsThreadRunning()==true)
				{
					CConsoleHelper::WriteLine(CString::Format("\tTEST DOUBLE STOP FAILED ! THREAD is STILL RUNNING !\n"));
					return(false);
				}

				if (Thread.IsThreadJoinable()==true)
				{
					CConsoleHelper::WriteLine(CString::Format("\tTEST DOUBLE STOP FAILED ! THREAD is STILL JOINABLE !\n"));
					return(false);
				}
			}
		}
		catch(const CException&)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST DOUBLE STOP FAILED ! THREAD ERROR !\n"));
			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST DOUBLE STOP FAILED ! THREAD ERROR !\n"));
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CThreadTest::TestThreadWithStopRequestedEvent(void)
	{
		CLogSource												Source("DUMMY");
		CConsoleLogWriter										LogWriter(Source);
		CThreadWithStopRequestedEvent							Thread(LogWriter);

		try
		{
			for(Size Index=0;Index<3;Index++)
			{
				if (Thread.IsThreadRunning()==true)
				{
					CConsoleHelper::WriteLine(CString::Format("\tTEST THREAD WITH STOP REQUESTED EVENT FAILED ! THREAD is STILL RUNNING !\n"));
					return(false);
				}

				if (Thread.IsThreadJoinable()==true)
				{
					CConsoleHelper::WriteLine(CString::Format("\tTEST THREAD WITH STOP REQUESTED EVENT FAILED ! THREAD is STILL JOINABLE !\n"));
					return(false);
				}

				Thread.StartThread();

				// WAIT for a WHILE.
				CThread::Sleep(3000);

				Thread.StopThread();

				if (Thread.IsThreadRunning()==true)
				{
					CConsoleHelper::WriteLine(CString::Format("\tTEST THREAD WITH STOP REQUESTED EVENT FAILED ! THREAD is STILL RUNNING !\n"));
					return(false);
				}

				if (Thread.IsThreadJoinable()==true)
				{
					CConsoleHelper::WriteLine(CString::Format("\tTEST THREAD WITH STOP REQUESTED EVENT FAILED ! THREAD is STILL JOINABLE !\n"));
					return(false);
				}
			}
		}
		catch(const CException&)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST THREAD WITH STOP REQUESTED EVENT FAILED ! THREAD ERROR !\n"));
			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST THREAD WITH STOP REQUESTED EVENT FAILED ! THREAD ERROR !\n"));
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CThreadTest::TestAutoResetMultiEvent(void)
	{
		CLogSource												Source("DUMMY");
		CConsoleLogWriter										LogWriter(Source);
		CAutoResetMultiEvent<3>									Event;
		CAutoResetMultiEvent<3>									InitializedEvent(CArray<bool,3>({false,true,false}));
		CAutoResetMultiEventThread								Thread(LogWriter,Event);
		Size													SingalizedEventIndex=0;

		try
		{
			if (InitializedEvent.WaitAny(SingalizedEventIndex)==false)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST AUTO RESET MULTI EVENT FAILED ! EVENT is NOT SIGNALIZED !\n"));
				return(false);
			}
			
			if (SingalizedEventIndex!=1)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST AUTO RESET MULTI EVENT FAILED ! WRONG EVENT is SIGNALIZED !\n"));
				return(false);
			}

			if (Event.WaitAll(100)==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST AUTO RESET MULTI EVENT FAILED ! EVENT is SIGNALIZED !\n"));
				return(false);
			}

			if (Event.WaitAny(100,SingalizedEventIndex)==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST AUTO RESET MULTI EVENT FAILED ! EVENT is SIGNALIZED !\n"));
				return(false);
			}

			Thread.StartThread();

			if (Event.WaitAll(100)==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST AUTO RESET MULTI EVENT FAILED ! EVENT is SIGNALIZED !\n"));
				return(false);
			}

			if (Event.WaitAny(100,SingalizedEventIndex)==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST AUTO RESET MULTI EVENT FAILED ! EVENT is SIGNALIZED !\n"));
				return(false);
			}

			// Will be SET only AFTER ALL EVENTS are SET.
			Event.WaitAll();

			CConsoleHelper::WriteLine(CString::Format("ALL EVENTS are SIGNALIZED !\n"));

			if (Event.WaitAll(100)==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST AUTO RESET MULTI EVENT FAILED ! EVENT is SIGNALIZED !\n"));
				return(false);
			}

			Event.Set(2);

			if (Event.IsSignalized(2)==false)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST AUTO RESET MULTI EVENT FAILED ! EVENT is NOT SIGNALIZED !\n"));
				return(false);
			}

			if (Event.WaitAny(SingalizedEventIndex)==false)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST AUTO RESET MULTI EVENT FAILED ! EVENT is NOT SIGNALIZED !\n"));
				return(false);
			}
			
			if (SingalizedEventIndex!=2)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST AUTO RESET MULTI EVENT FAILED ! WRONG EVENT is SIGNALIZED !\n"));
				return(false);
			}

			if (Event.IsSignalized(2)==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST AUTO RESET MULTI EVENT FAILED ! EVENT is SIGNALIZED !\n"));
				return(false);
			}

			if (Event.WaitAny(100,SingalizedEventIndex)==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST AUTO RESET MULTI EVENT FAILED ! EVENT is SIGNALIZED !\n"));
				return(false);
			}

			Event.Set(0);
			Event.Set(1);
			Event.Set(2);

			if (Event.WaitAny(SingalizedEventIndex)==false)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST AUTO RESET MULTI EVENT FAILED ! EVENT is NOT SIGNALIZED !\n"));
				return(false);
			}
			
			if (SingalizedEventIndex!=0)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST AUTO RESET MULTI EVENT FAILED ! WRONG EVENT is SIGNALIZED !\n"));
				return(false);
			}

			Event.ResetAll();

			if (Event.WaitAll(100)==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST AUTO RESET MULTI EVENT FAILED ! EVENT is SIGNALIZED !\n"));
				return(false);
			}

			if (Event.WaitAny(100,SingalizedEventIndex)==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST AUTO RESET MULTI EVENT FAILED ! EVENT is SIGNALIZED !\n"));
				return(false);
			}

			Event.Set(1);
			Event.Set(2);

			Event.Reset(1);

			if (Event.WaitAny(SingalizedEventIndex)==false)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST AUTO RESET MULTI EVENT FAILED ! EVENT is NOT SIGNALIZED !\n"));
				return(false);
			}
			
			if (SingalizedEventIndex!=2)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST AUTO RESET MULTI EVENT FAILED ! WRONG EVENT is SIGNALIZED !\n"));
				return(false);
			}

			Thread.StopThread();

			if (Thread.IsThreadRunning()==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST AUTO RESET MULTI EVENT FAILED ! THREAD is STILL RUNNING !\n"));
				return(false);
			}

			if (Thread.IsThreadJoinable()==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST AUTO RESET MULTI EVENT FAILED ! THREAD is STILL JOINABLE !\n"));
				return(false);
			}
		}
		catch(const CException&)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST AUTO RESET MULTI EVENT FAILED ! THREAD ERROR !\n"));
			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST AUTO RESET MULTI EVENT FAILED ! THREAD ERROR !\n"));
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CThreadTest::TestManualResetMultiEvent(void)
	{
		CLogSource												Source("DUMMY");
		CConsoleLogWriter										LogWriter(Source);
		CManualResetMultiEvent<3>								Event;
		CManualResetMultiEvent<3>								InitializedEvent(CArray<bool,3>({false,true,false}));
		CManualResetMultiEventThread							Thread(LogWriter,Event);
		Size													SingalizedEventIndex=0;

		try
		{
			if (InitializedEvent.WaitAny(SingalizedEventIndex)==false)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST MANUAL RESET MULTI EVENT FAILED ! EVENT is NOT SIGNALIZED !\n"));
				return(false);
			}
			
			if (SingalizedEventIndex!=1)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST MANUAL RESET MULTI EVENT FAILED ! WRONG EVENT is SIGNALIZED !\n"));
				return(false);
			}

			if (Event.WaitAll(100)==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST MANUAL RESET MULTI EVENT FAILED ! EVENT is SIGNALIZED !\n"));
				return(false);
			}

			if (Event.WaitAny(100,SingalizedEventIndex)==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST MANUAL RESET MULTI EVENT FAILED ! EVENT is SIGNALIZED !\n"));
				return(false);
			}

			Thread.StartThread();

			if (Event.WaitAll(100)==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST MANUAL RESET MULTI EVENT FAILED ! EVENT is SIGNALIZED !\n"));
				return(false);
			}

			if (Event.WaitAny(100,SingalizedEventIndex)==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST MANUAL RESET MULTI EVENT FAILED ! EVENT is SIGNALIZED !\n"));
				return(false);
			}

			// Will be SET only AFTER ALL EVENTS are SET.
			Event.WaitAll();

			CConsoleHelper::WriteLine(CString::Format("ALL EVENTS are SIGNALIZED !\n"));

			if (Event.WaitAny(SingalizedEventIndex)==false)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST MANUAL RESET MULTI EVENT FAILED ! EVENT is NOT SIGNALIZED !\n"));
				return(false);
			}
			
			if (SingalizedEventIndex!=0)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST MANUAL RESET MULTI EVENT FAILED ! WRONG EVENT is SIGNALIZED !\n"));
				return(false);
			}

			Event.Reset(0);

			if (Event.WaitAny(SingalizedEventIndex)==false)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST MANUAL RESET MULTI EVENT FAILED ! EVENT is NOT SIGNALIZED !\n"));
				return(false);
			}
			
			if (SingalizedEventIndex!=1)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST MANUAL RESET MULTI EVENT FAILED ! WRONG EVENT is SIGNALIZED !\n"));
				return(false);
			}

			Event.ResetAll();

			if (Event.WaitAll(100)==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST MANUAL RESET MULTI EVENT FAILED ! EVENT is SIGNALIZED !\n"));
				return(false);
			}

			if (Event.WaitAny(100,SingalizedEventIndex)==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST MANUAL RESET MULTI EVENT FAILED ! EVENT is SIGNALIZED !\n"));
				return(false);
			}

			Event.Set(2);

			if (Event.WaitAny(SingalizedEventIndex)==false)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST MANUAL RESET MULTI EVENT FAILED ! EVENT is NOT SIGNALIZED !\n"));
				return(false);
			}
			
			if (SingalizedEventIndex!=2)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST MANUAL RESET MULTI EVENT FAILED ! WRONG EVENT is SIGNALIZED !\n"));
				return(false);
			}

			if (Event.IsSignalized(2)==false)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST MANUAL RESET MULTI EVENT FAILED ! EVENT is NOT SIGNALIZED !\n"));
				return(false);
			}

			Thread.StopThread();

			if (Thread.IsThreadRunning()==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST MANUAL RESET MULTI EVENT FAILED ! THREAD is STILL RUNNING !\n"));
				return(false);
			}

			if (Thread.IsThreadJoinable()==true)
			{
				CConsoleHelper::WriteLine(CString::Format("\tTEST MANUAL RESET MULTI EVENT FAILED ! THREAD is STILL JOINABLE !\n"));
				return(false);
			}
		}
		catch(const CException&)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MANUAL RESET MULTI EVENT FAILED ! THREAD ERROR !\n"));
			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST MANUAL RESET MULTI EVENT FAILED ! THREAD ERROR !\n"));
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CThreadTest::ExecuteTest(void)
	{
		CVector<CTestMethod<CThreadTest>>						Tests;

		Tests.Add(CTestMethod<CThreadTest>(this,&CThreadTest::TestBasicThread));
		Tests.Add(CTestMethod<CThreadTest>(this,&CThreadTest::TestMutex));
		Tests.Add(CTestMethod<CThreadTest>(this,&CThreadTest::TestLock));
		Tests.Add(CTestMethod<CThreadTest>(this,&CThreadTest::TestLockWithSpin));
		Tests.Add(CTestMethod<CThreadTest>(this,&CThreadTest::TestAutoResetEvent));
		Tests.Add(CTestMethod<CThreadTest>(this,&CThreadTest::TestManualResetEvent));
		Tests.Add(CTestMethod<CThreadTest>(this,&CThreadTest::TestAtomic));
		Tests.Add(CTestMethod<CThreadTest>(this,&CThreadTest::TestAtomicSlim));
		Tests.Add(CTestMethod<CThreadTest>(this,&CThreadTest::TestMyThread1));
		Tests.Add(CTestMethod<CThreadTest>(this,&CThreadTest::TestMyThread2));
		Tests.Add(CTestMethod<CThreadTest>(this,&CThreadTest::TestMyThread3));
		Tests.Add(CTestMethod<CThreadTest>(this,&CThreadTest::TestShortLivingThread));
		Tests.Add(CTestMethod<CThreadTest>(this,&CThreadTest::TestDoubleStop));
		Tests.Add(CTestMethod<CThreadTest>(this,&CThreadTest::TestThreadWithStopRequestedEvent));
		Tests.Add(CTestMethod<CThreadTest>(this,&CThreadTest::TestAutoResetMultiEvent));
		Tests.Add(CTestMethod<CThreadTest>(this,&CThreadTest::TestManualResetMultiEvent));

		bool													AllTestPassed=true;
		Size													TestNumber=0;

		for(CTestMethod<CThreadTest>& Method : Tests)
		{
			if (Method()==true)
			{
				CString											Output;

				Output+=GetSeparator(true);
				Output+="\tSUBTEST [";
				Output+=CString(++TestNumber);
				Output+="] PASSED SUCCESSFULLY !\n";
				Output+=GetSeparator(true);

				CConsoleHelper::WriteLine(Output,EConsoleColor::E_LIGHT_GREEN,EConsoleColor::E_DEFAULT,false);
			}
			else
			{
				CString											Output;

				Output+=GetSeparator(true);
				Output+="\tSUBTEST [";
				Output+=CString(++TestNumber);
				Output+="] FAILED !\n";
				Output+=GetSeparator(true);

				AllTestPassed=false;

				CConsoleHelper::WriteLine(Output,EConsoleColor::E_LIGHT_RED,EConsoleColor::E_DEFAULT,false);
			}
		}

		CConsoleHelper::WriteLine(GetSeparator(false));
		CConsoleHelper::WriteLine(GetSeparator(false));
		CConsoleHelper::WriteLine(GetSeparator(false));

		if (AllTestPassed==true)
		{
			CConsoleHelper::WriteLine("ALL TESTS PASSED SUCCESSFULLY !",EConsoleColor::E_LIGHT_GREEN,EConsoleColor::E_DEFAULT,false);
		}
		else
		{
			CConsoleHelper::WriteLine("SOME TESTS FAILED !",EConsoleColor::E_LIGHT_RED,EConsoleColor::E_DEFAULT,false);
		}

		CConsoleHelper::WriteLine(GetSeparator(false));
		CConsoleHelper::WriteLine(GetSeparator(false));
		CConsoleHelper::WriteLine(GetSeparator(false));

		return(AllTestPassed);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------