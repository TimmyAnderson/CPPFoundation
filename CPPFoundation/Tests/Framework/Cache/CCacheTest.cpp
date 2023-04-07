//----------------------------------------------------------------------------------------------------------------------
#include "CCacheTest.h"
#include <Framework/Foundation/Cache/CCacheManager.h>
#include <Framework/Foundation/Console/CConsoleHelper.h>
#include <Framework/Foundation/Types/CMethod.h>
#include "CCacheEntryTest1.h"
#include "CCacheEntryTest2.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace std;
	using namespace CPPFoundation::Foundation;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CCacheTest::CCacheTest(CLogWriter& LogWriter, const CLogCategory& LogCategoryTest)
		: CTest(LogWriter,LogCategoryTest,"SCHEDULER TEST")
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CCacheTest::~CCacheTest(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CCacheTest::TestCacheManager(void)
	{
		try
		{
			CCacheManager										Manager;
			CSteadyClock::Milliseconds							TimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds();

			Manager.AddCacheEntry(CSPCacheEntry(new CCacheEntry(CCacheEntryID("111"),CExpirationTime(2000,TimeInMS))));

			try
			{
				Manager.AddCacheEntry(CSPCacheEntry(new CCacheEntry(CCacheEntryID("111"),CExpirationTime(1000,TimeInMS))));

				CConsoleHelper::WriteLine(CString::Format("\tTEST FAILED !\n"));

				return(false);
			}
			catch(const CException&)
			{
			}

			Manager.AddCacheEntry(CSPCacheEntry(new CCacheEntry(CCacheEntryID("222"),CExpirationTime(3000,TimeInMS))));
			Manager.AddCacheEntry(CSPCacheEntry(new CCacheEntry(CCacheEntryID("333"),CExpirationTime(5000,TimeInMS))));
			Manager.AddCacheEntry(CSPCacheEntry(new CCacheEntry(CCacheEntryID("444"),CExpirationTime(4000,TimeInMS))));

			CTimeout											Timeout1=Manager.GetExpirationTime(TimeInMS);

			if (Timeout1!=CTimeout(2000))
			{
				throw(CInvalidOperationException("TEST FAILED !"));
			}

			Manager.AddCacheEntry(CSPCacheEntry(new CCacheEntry(CCacheEntryID("555"),CExpirationTime(1000,TimeInMS))));

			if (Manager.GetLength()!=5)
			{
				throw(CInvalidOperationException("TEST FAILED !"));
			}

			Manager.RemoveCacheEntriesByTime(TimeInMS);

			if (Manager.GetLength()!=5)
			{
				throw(CInvalidOperationException("TEST FAILED !"));
			}

			TimeInMS+=2500;

			CTimeout											Timeout2=Manager.GetExpirationTime(TimeInMS);

			if (Timeout2!=CTimeout(0))
			{
				throw(CInvalidOperationException("TEST FAILED !"));
			}

			Manager.RemoveCacheEntriesByTime(TimeInMS);

			if (Manager.GetLength()!=3)
			{
				throw(CInvalidOperationException("TEST FAILED !"));
			}

			CTimeout											Timeout3=Manager.GetExpirationTime(TimeInMS);

			if (Timeout3!=CTimeout(500))
			{
				throw(CInvalidOperationException("TEST FAILED !"));
			}

			Manager.RemoveCacheEntryByID(CCacheEntryID("222"));

			CTimeout											Timeout4=Manager.GetExpirationTime(TimeInMS);

			if (Timeout4!=CTimeout(1500))
			{
				throw(CInvalidOperationException("TEST FAILED !"));
			}

			CTimeout											Timeout5;

			for(CSPCacheEntry Value : Manager)
			{
				Timeout5=CTimeout::Min(Timeout5,Value->GetExpirationTime().CalculateTimeout(TimeInMS));
			}

			if (Timeout5!=CTimeout(1500))
			{
				throw(CInvalidOperationException("TEST FAILED !"));
			}

			CTimeout											Timeout6;

			for(CSPCacheEntry Value : CreateIterator(Manager))
			{
				Timeout6=CTimeout::Min(Timeout6,Value->GetExpirationTime().CalculateTimeout(TimeInMS));
			}

			if (Timeout6!=CTimeout(1500))
			{
				throw(CInvalidOperationException("TEST FAILED !"));
			}

			Manager.AddCacheEntry(CSPCacheEntry(new CCacheEntryTest1(CCacheEntryID("CE1"),CExpirationTime(3000,TimeInMS),"AAA")));
			Manager.AddCacheEntry(CSPCacheEntry(new CCacheEntryTest2(CCacheEntryID("CE2"),CExpirationTime(4000,TimeInMS),"BBB")));

			if (Manager.HasCacheEntry<CCacheEntryTest1>(CCacheEntryID("CE1"))==false)
			{
				throw(CInvalidOperationException("TEST FAILED !"));
			}

			if (Manager.HasCacheEntry<CCacheEntryTest2>(CCacheEntryID("CE1"))==true)
			{
				throw(CInvalidOperationException("TEST FAILED !"));
			}

			if (Manager.HasCacheEntry<CCacheEntryTest1>(CCacheEntryID("CE2"))==true)
			{
				throw(CInvalidOperationException("TEST FAILED !"));
			}

			if (Manager.HasCacheEntry<CCacheEntryTest2>(CCacheEntryID("CE2"))==false)
			{
				throw(CInvalidOperationException("TEST FAILED !"));
			}

			CSPCacheEntryTest1									Entry1=Manager.GetCacheEntry<CCacheEntryTest1>(CCacheEntryID("CE1"));
			CSPCacheEntryTest2									Entry2=Manager.GetCacheEntry<CCacheEntryTest2>(CCacheEntryID("CE2"));

			if (Entry1->GetValue()!="AAA")
			{
				throw(CInvalidOperationException("TEST FAILED !"));
			}

			if (Entry2->GetValue()!="BBB")
			{
				throw(CInvalidOperationException("TEST FAILED !"));
			}

			if (Entry1->GetExpirationTime()!=CExpirationTime(3000,TimeInMS))
			{
				throw(CInvalidOperationException("TEST FAILED !"));
			}

			if (Entry2->GetExpirationTime()!=CExpirationTime(4000,TimeInMS))
			{
				throw(CInvalidOperationException("TEST FAILED !"));
			}

			Manager.AddOrUpdateCacheEntry(CSPCacheEntry(new CCacheEntryTest1(CCacheEntryID("CE1"),CExpirationTime(5000,TimeInMS),"CCC")));
			Manager.AddOrUpdateCacheEntry(CSPCacheEntry(new CCacheEntryTest2(CCacheEntryID("CE2"),CExpirationTime(6000,TimeInMS),"DDD")));

			CSPCacheEntryTest1									Entry3=Manager.GetCacheEntry<CCacheEntryTest1>(CCacheEntryID("CE1"));
			CSPCacheEntryTest2									Entry4=Manager.GetCacheEntry<CCacheEntryTest2>(CCacheEntryID("CE2"));

			if (Entry3->GetValue()!="CCC")
			{
				throw(CInvalidOperationException("TEST FAILED !"));
			}

			if (Entry4->GetValue()!="DDD")
			{
				throw(CInvalidOperationException("TEST FAILED !"));
			}

			if (Entry3->GetExpirationTime()!=CExpirationTime(5000,TimeInMS))
			{
				throw(CInvalidOperationException("TEST FAILED !"));
			}

			if (Entry4->GetExpirationTime()!=CExpirationTime(6000,TimeInMS))
			{
				throw(CInvalidOperationException("TEST FAILED !"));
			}

			return(true);
		}
		catch(const CException& E)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST FAILED with EXCEPTION [",E.GetMessage(),"] !\n"));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CCacheTest::ExecuteTest(void)
	{
		CVector<CTestMethod<CCacheTest>>						Tests;

		Tests.Add(CTestMethod<CCacheTest>(this,&CCacheTest::TestCacheManager));

		bool													AllTestPassed=true;
		Size													TestNumber=0;

		for(CTestMethod<CCacheTest>& Method : Tests)
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