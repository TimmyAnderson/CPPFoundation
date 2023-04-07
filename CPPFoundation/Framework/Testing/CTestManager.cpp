//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Console/CConsoleHelper.h>
#include "CTestManager.h"
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
	CTestManager::CTestManager(CLogWriter& LogWriter, const CLogCategory& LogCategoryTest, const CTestCollection& TestCollection)
		: MLogWriter(LogWriter), MLogCategoryTest(LogCategoryTest), MTestCollection(TestCollection)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CTestManager::~CTestManager(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CLogWriter& CTestManager::GetLogWriter(void) noexcept
	{
		return(MLogWriter);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CLogCategory& CTestManager::GetLogCategoryTest(void) const noexcept
	{
		return(MLogCategoryTest);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CTestManager::ExecuteTests(void)
	{
		const Size												SEPARATOR_LENGTH=79;

		CString													Separator=CString::Format(CString().PadRight(SEPARATOR_LENGTH,'-'),"\n");
		bool													AllTestsPassed=true;

		for(CSPTest& Test : MTestCollection)
		{
			try
			{
				CString											Message;

				Message+=Separator;
				Message+=CString::Format("TEST [",Test->GetName(),"] STARTED !\n");

				CConsoleHelper::Write(Message);

				if (Test->ExecuteTest()==true)
				{
					CString										Result;

					Result+=CString::Format("TEST [",Test->GetName(),"] SUCCESSFULLY FINISHED !\n");
					Result+=Separator;

					CConsoleHelper::Write(Result);
				}
				else
				{
					AllTestsPassed=false;

					CString										Result;

					Result+=CString::Format("TEST [",Test->GetName(),"] FINISHED with FAILURE !\n");
					Result+=Separator;

					CConsoleHelper::Write(Result);
				}
			}
			catch(...)
			{
				AllTestsPassed=false;

				CString											Result;

				Result+=CString::Format("TEST [",Test->GetName(),"] FINISHED with EXCEPTION FAILURE !\n");
				Result+=Separator;

				CConsoleHelper::Write(Result);
			}
		}

		return(AllTestsPassed);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------