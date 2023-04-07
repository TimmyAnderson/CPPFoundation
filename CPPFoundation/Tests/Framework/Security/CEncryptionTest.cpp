//----------------------------------------------------------------------------------------------------------------------
#include "CEncryptionTest.h"
#include <Framework/Foundation/Console/CConsoleHelper.h>
#include <Framework/Foundation/Security/Encryption/Algorithms/RC4/CEncryptionAlgorithmRC4.h>
#include <Framework/Foundation/Types/CMethod.h>
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
	CEncryptionTest::CEncryptionTest(CLogWriter& LogWriter, const CLogCategory& LogCategoryTest, bool WriteEncryptedData)
		: CTest(LogWriter,LogCategoryTest,"ENCRYPTION TEST"), MWriteEncryptedData(WriteEncryptedData)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CEncryptionTest::~CEncryptionTest(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CEncryptionTest::TestRC4(void)
	{
		CByteBuffer												Password{0x12,0x34,0x56,0x78,0x90,0xAB,0xCD,0xEF};
		CEncryptionAlgorithmRC4									RC4(CCSPEncryptionAlgorithmConfigurationRC4(new CEncryptionAlgorithmConfigurationRC4(Password,false,60*1000,6,2)));

		CByteBuffer												Input1({10,20,30,40,50,45,35,25,15,5,100,200});
		CByteBuffer												Input2({10,20,30,40});
		CByteBuffer												Input3({10,20,30,40,50,45,35,25,15,5,100,200,201,202,203,204});

		CByteBuffer												ExpectedResult1({0xB4,0xED,0xA2,0x3E,0xA3,0xE7,0xDA,0x6A,0x8F,0x3D,0xC0,0x7B});
		CByteBuffer												ExpectedResult2({0xB4,0xED,0xA2,0x3E});
		CByteBuffer												ExpectedResult3({0xB4,0xED,0xA2,0x3E,0xA3,0xE7,0xDA,0x6A,0x8F,0x3D,0xC0,0x7B,0x0F,0x01,0x77,0xA7});

		CEncryptionAlgorithmParameterCollection					ParameterCollection;

		CByteBuffer												EncryptedOutput1=RC4.Encrypt(Input1,ParameterCollection);
		CByteBuffer												EncryptedOutput2=RC4.Encrypt(Input2,ParameterCollection);
		CByteBuffer												EncryptedOutput3=RC4.Encrypt(Input3,ParameterCollection);

		if (MWriteEncryptedData==true)
		{
			CConsoleHelper::WriteLine(CString::Format("\tENCRYPTED OUTPUT 1 [",EncryptedOutput1,"] !\n"));
			CConsoleHelper::WriteLine(CString::Format("\tENCRYPTED OUTPUT 2 [",EncryptedOutput2,"] !\n"));
			CConsoleHelper::WriteLine(CString::Format("\tENCRYPTED OUTPUT 3 [",EncryptedOutput3,"] !\n"));
		}

		if (EncryptedOutput1!=ExpectedResult1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tENCRYPTED OUTPUT 1 [",EncryptedOutput1,"] is NOT EQUAL to EXPECTED RESULT 1 [",ExpectedResult1,"] !\n"));

			return(false);
		}

		if (EncryptedOutput2!=ExpectedResult2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tENCRYPTED OUTPUT 2 [",EncryptedOutput2,"] is NOT EQUAL to EXPECTED RESULT 2 [",ExpectedResult2,"] !\n"));

			return(false);
		}

		if (EncryptedOutput3!=ExpectedResult3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tENCRYPTED OUTPUT 3 [",EncryptedOutput3,"] is NOT EQUAL to EXPECTED RESULT 3 [",ExpectedResult3,"] !\n"));

			return(false);
		}

		CByteBuffer												DecryptedOutput1=RC4.Encrypt(Input1,ParameterCollection);
		CByteBuffer												DecryptedOutput2=RC4.Encrypt(Input2,ParameterCollection);
		CByteBuffer												DecryptedOutput3=RC4.Encrypt(Input3,ParameterCollection);

		if (DecryptedOutput1!=ExpectedResult1)
		{
			CConsoleHelper::WriteLine(CString::Format("\tDECRYPTED OUTPUT 1 [",DecryptedOutput1,"] is NOT EQUAL to EXPECTED RESULT 1 [",ExpectedResult1,"] !\n"));

			return(false);
		}

		if (DecryptedOutput2!=ExpectedResult2)
		{
			CConsoleHelper::WriteLine(CString::Format("\tDECRYPTED OUTPUT 2 [",DecryptedOutput2,"] is NOT EQUAL to EXPECTED RESULT 2 [",ExpectedResult2,"] !\n"));

			return(false);
		}

		if (DecryptedOutput3!=ExpectedResult3)
		{
			CConsoleHelper::WriteLine(CString::Format("\tDECRYPTED OUTPUT 3 [",DecryptedOutput3,"] is NOT EQUAL to EXPECTED RESULT 3 [",ExpectedResult3,"] !\n"));

			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CEncryptionTest::ExecuteTest(void)
	{
		CVector<CTestMethod<CEncryptionTest>>					Tests;

		Tests.Add(CTestMethod<CEncryptionTest>(this,&CEncryptionTest::TestRC4));

		bool													AllTestPassed=true;
		Size													TestNumber=0;
		
		for(CTestMethod<CEncryptionTest>& Method : Tests)
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