//----------------------------------------------------------------------------------------------------------------------
#include "CFunctionTest.h"
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Foundation/Collections/CVector.h>
#include <Framework/Foundation/Console/CConsoleHelper.h>
#include "CFunctionTestDerived1.h"
#include "CFunctionTestDerived2.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace CPPFoundation::Foundation;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CFunctionTest::CFunctionTest(CLogWriter& LogWriter, const CLogCategory& LogCategoryTest)
		: CTest(LogWriter,LogCategoryTest,"FUNCTION TEST")
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CFunctionTest::~CFunctionTest(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	int32 CFunctionTest::FunctionTest1(int32 Value)
	{
		return(Value+10);
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CFunctionTest::FunctionTest2(int32 Value)
	{
		return(Value+20);
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CFunctionTest::FunctionTest3(int32 Value, const CFunctionTestBase& Class)
	{
		return(Value+100+Class.GetSum());
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CFunctionTest::TestFunctionTransfer1(const CFunction<int32(int32,CFunctionTestBase&)>& Function)
	{
		CFunctionTestDerived1									Derived1(1,2);
		int32													ReturnValue=Function(333,Derived1);

		return(ReturnValue);
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CFunctionTest::TestFunctionTransfer2(CFunction<int32(int32,CFunctionTestBase&)> Function)
	{
		CFunctionTestDerived2									Derived2(3,4);
		int32													ReturnValue=Function(444,Derived2);

		return(ReturnValue);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CFunctionTest::TestFunction(void)
	{
		CFunctionTestDerived1									Derived1(30,100);
		CFunctionTestDerived2									Derived2(60,200);

		const int32												ExpectedValue1=60;
		const int32												ExpectedValue2=70;
		const int32												ExpectedValue31=280;
		const int32												ExpectedValue32=420;
		const int32												ExpectedValue33=425;
		const int32												ExpectedValue34=430;
		const int32												ExpectedValue41=436;
		const int32												ExpectedValue42=551;

		CFunction<int32(int32)>									Function1(&CFunctionTest::FunctionTest1);
		CFunction<int32(int32)>									Function2(&CFunctionTest::FunctionTest2);
		CFunction<int32(int32,CFunctionTestBase&)>				Function31(&CFunctionTest::FunctionTest3);
		CFunction<int32(int32,CFunctionTestBase&)>				Function32(&CFunctionTest::FunctionTest3);
		CFunction<int32(int32,CFunctionTestBase&)>				Function33(Function32);
		CFunction<int32(int32,CFunctionTestBase&)>				Function41(&CFunctionTest::FunctionTest3);
		CFunction<int32(int32,CFunctionTestBase&)>				Function42(&CFunctionTest::FunctionTest3);

		int32													Result1=Function1(50);
		int32													Result2=Function2(50);
		int32													Result31=Function31(50,Derived1);
		int32													Result32=Function32(60,Derived2);
		int32													Result33=Function33(65,Derived2);

		Function31=Function32;

		int32													Result34=Function31(70,Derived2);

		int32													Result41=TestFunctionTransfer1(Function41);
		int32													Result42=TestFunctionTransfer2(Function42);

		if (Result1!=ExpectedValue1)
		{
			CConsoleHelper::WriteLine(CString::Format("TEST 1 FAILED [",Result1,",",ExpectedValue1,"] !\n"));
		}

		if (Result2!=ExpectedValue2)
		{
			CConsoleHelper::WriteLine(CString::Format("TEST 2 FAILED [",Result2,",",ExpectedValue2,"] !\n"));
		}

		if (Result31!=ExpectedValue31)
		{
			CConsoleHelper::WriteLine(CString::Format("TEST 3 FAILED [",Result31,",",ExpectedValue31,"] !\n"));
		}

		if (Result32!=ExpectedValue32)
		{
			CConsoleHelper::WriteLine(CString::Format("TEST 4 FAILED [",Result32,",",ExpectedValue32,"] !\n"));
		}

		if (Result33!=ExpectedValue33)
		{
			CConsoleHelper::WriteLine(CString::Format("TEST 5 FAILED [",Result33,",",ExpectedValue33,"] !\n"));
		}

		if (Result34!=ExpectedValue34)
		{
			CConsoleHelper::WriteLine(CString::Format("TEST 6 FAILED [",Result34,",",ExpectedValue34,"] !\n"));
		}

		if (Result41!=ExpectedValue41)
		{
			CConsoleHelper::WriteLine(CString::Format("TEST 7 FAILED [",Result41,",",ExpectedValue41,"] !\n"));
		}

		if (Result42!=ExpectedValue42)
		{
			CConsoleHelper::WriteLine(CString::Format("TEST 8 FAILED [",Result42,",",ExpectedValue42,"] !\n"));
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	int32 CFunctionTest::TestMethodTransfer1(const CMethod<CFunctionTestClass,int32(int32,CFunctionTestBase&)>& Method)
	{
		CFunctionTestDerived1									Derived1(1,2);
		int32													ReturnValue=Method(333,Derived1);

		return(ReturnValue);
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CFunctionTest::TestMethodTransfer2(CMethod<CFunctionTestClass,int32(int32,CFunctionTestBase&)> Method)
	{
		CFunctionTestDerived2									Derived2(3,4);
		int32													ReturnValue=Method(444,Derived2);

		return(ReturnValue);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CFunctionTest::TestMethod(void)
	{
		CFunctionTestClass										Class1(1000);
		CFunctionTestClass										Class2(2000);

		CFunctionTestDerived1									Derived1(30,100);
		CFunctionTestDerived2									Derived2(60,200);

		const int32												ExpectedValue11=1060;
		const int32												ExpectedValue12=2060;
		const int32												ExpectedValue21=1070;
		const int32												ExpectedValue22=2070;
		const int32												ExpectedValue31=1280;
		const int32												ExpectedValue32=2410;
		const int32												ExpectedValue33=2415;
		const int32												ExpectedValue34=2420;
		const int32												ExpectedValue41=1436;
		const int32												ExpectedValue42=2551;

		CMethod<CFunctionTestClass,int32(int32)>				Method11(&Class1,&CFunctionTestClass::MethodTest1);
		CMethod<CFunctionTestClass,int32(int32)>				Method12(&Class2,&CFunctionTestClass::MethodTest1);
		CMethod<CFunctionTestClass,int32(int32)>				Method21(&Class1,&CFunctionTestClass::MethodTest2);
		CMethod<CFunctionTestClass,int32(int32)>				Method22(&Class2,&CFunctionTestClass::MethodTest2);
		CMethod<CFunctionTestClass,int32(int32,CFunctionTestBase&)>	Method31(&Class1,&CFunctionTestClass::MethodTest3);
		CMethod<CFunctionTestClass,int32(int32,CFunctionTestBase&)>	Method32(&Class2,&CFunctionTestClass::MethodTest3);
		CMethod<CFunctionTestClass,int32(int32,CFunctionTestBase&)>	Method33(Method32);
		CMethod<CFunctionTestClass,int32(int32,CFunctionTestBase&)>	Method41(&Class1,&CFunctionTestClass::MethodTest3);
		CMethod<CFunctionTestClass,int32(int32,CFunctionTestBase&)>	Method42(&Class2,&CFunctionTestClass::MethodTest3);

		int32													Result11=Method11(50);
		int32													Result12=Method12(50);
		int32													Result21=Method21(50);
		int32													Result22=Method22(50);
		int32													Result31=Method31(50,Derived1);
		int32													Result32=Method32(50,Derived2);
		int32													Result33=Method33(55,Derived2);

		Method31=Method32;

		int32													Result34=Method31(60,Derived2);

		int32													Result41=TestMethodTransfer1(Method41);
		int32													Result42=TestMethodTransfer2(Method42);

		if (Result11!=ExpectedValue11)
		{
			CConsoleHelper::WriteLine(CString::Format("TEST 1 FAILED [",Result11,",",ExpectedValue11,"] !\n"));
		}

		if (Result12!=ExpectedValue12)
		{
			CConsoleHelper::WriteLine(CString::Format("TEST 2 FAILED [",Result12,",",ExpectedValue12,"] !\n"));
		}

		if (Result21!=ExpectedValue21)
		{
			CConsoleHelper::WriteLine(CString::Format("TEST 3 FAILED [",Result21,",",ExpectedValue21,"] !\n"));
		}

		if (Result22!=ExpectedValue22)
		{
			CConsoleHelper::WriteLine(CString::Format("TEST 4 FAILED [",Result22,",",ExpectedValue22,"] !\n"));
		}

		if (Result31!=ExpectedValue31)
		{
			CConsoleHelper::WriteLine(CString::Format("TEST 5 FAILED [",Result31,",",ExpectedValue31,"] !\n"));
		}

		if (Result32!=ExpectedValue32)
		{
			CConsoleHelper::WriteLine(CString::Format("TEST 6 FAILED [",Result32,",",ExpectedValue32,"] !\n"));
		}

		if (Result33!=ExpectedValue33)
		{
			CConsoleHelper::WriteLine(CString::Format("TEST 7 FAILED [",Result33,",",ExpectedValue33,"] !\n"));
		}

		if (Result34!=ExpectedValue34)
		{
			CConsoleHelper::WriteLine(CString::Format("TEST 8 FAILED [",Result34,",",ExpectedValue34,"] !\n"));
		}

		if (Result41!=ExpectedValue41)
		{
			CConsoleHelper::WriteLine(CString::Format("TEST 9 FAILED [",Result41,",",ExpectedValue41,"] !\n"));
		}

		if (Result42!=ExpectedValue42)
		{
			CConsoleHelper::WriteLine(CString::Format("TEST 10 FAILED [",Result42,",",ExpectedValue42,"] !\n"));
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CFunctionTest::ExecuteTest(void)
	{
		CVector<CTestMethod<CFunctionTest>>						Tests;

		Tests.Add(CTestMethod<CFunctionTest>(this,&CFunctionTest::TestFunction));
		Tests.Add(CTestMethod<CFunctionTest>(this,&CFunctionTest::TestMethod));

		bool													AllTestPassed=true;
		Size													TestNumber=0;

		for(CTestMethod<CFunctionTest>& Method : Tests)
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