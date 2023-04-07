//----------------------------------------------------------------------------------------------------------------------
#if defined(PLATFORM_WINDOWS)
#define _CRTDBG_MAP_ALLOC
#include <WinSock2.h>
#include <stdlib.h>
#include <crtdbg.h>
#undef INFINITE
#undef min
#undef max
#elif defined(PLATFORM_LINUX)
#include <sys/socket.h>
#endif
//----------------------------------------------------------------------------------------------------------------------
#include <type_traits>
#include <vector>
#include <memory>
#include <cstdlib>
#include <cstdio>
#include <array>
#include <iostream>
#include <numeric>
#include <string>
#include <functional>
#include <sstream>
#include <iomanip> 
#include <chrono>
#include <thread>
#include <Framework/Foundation/Mathematics/CMathematics.h>
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Strings/CString.h>
#include <Framework/Foundation/Types/TypeTraits.h>
#include <Framework/Foundation/Exceptions/CException.h>
#include <Framework/Foundation/Exceptions/CValueOutOfRangeException.h>
#include <Framework/Foundation/Collections/CArray.h>
#include <Framework/Foundation/Collections/CByteBuffer.h>
#include <Framework/Foundation/Collections/CList.h>
#include <Framework/Foundation/Collections/CMap.h>
#include <Framework/Foundation/Collections/CMultiMap.h>
#include <Framework/Foundation/Collections/CSet.h>
#include <Framework/Foundation/Collections/CVector.h>
#include <Framework/Foundation/Collections/CDequeue.h>
#include <Framework/Foundation/Collections/CTSDequeue.h>
#include <Framework/Foundation/Collections/CTuple.h>
#include <Framework/Foundation/Collections/CPair.h>
#include <Framework/Foundation/Console/CConsoleHelper.h>
#include <Framework/Foundation/Console/CConsoleMenu.h>
#include <Framework/Foundation/Events/CEvent.h>
#include <Framework/Foundation/Events/CEventThread.h>
#include <Framework/Foundation/Events/CEventData.h>
#include <Framework/Foundation/FileSystem/CFilePath.h>
#include <Framework/Foundation/Logger/CLogFilter.h>
#include <Framework/Foundation/Logger/CLogRecord.h>
#include <Framework/Foundation/Logger/CConsoleLogWriter.h>
#include <Framework/Foundation/Miscellaneous/CID.h>
#include <Framework/Foundation/Operators/CBinaryOperators.h>
#include <Framework/Foundation/Operators/COperatorEqualTo.h>
#include <Framework/Foundation/Operators/COperatorNotEqualTo.h>
#include <Framework/Foundation/Operators/COperatorLessThan.h>
#include <Framework/Foundation/Operators/COperatorLessThanOrEqualTo.h>
#include <Framework/Foundation/Operators/COperatorGreaterThan.h>
#include <Framework/Foundation/Operators/COperatorGreaterThanOrEqualTo.h>
#include <Framework/Foundation/Parsing/CParserByteBufferReader.h>
#include <Framework/Foundation/Parsing/CParserByteBufferWriter.h>
#include <Framework/Foundation/Parsing/CParserHelper.h>
#include <Framework/Foundation/StateMachines/StateMachines/CStateMachineID.h>
#include <Framework/Foundation/StateMachines/StateMachines/CStateMachine.h>
#include <Framework/Foundation/StateMachines/StateMachines/CStateMachineCollection.h>
#include <Framework/Foundation/StateMachines/StateMachinesProcessor/CStateMachinesProcessor.h>
#include <Framework/Foundation/StateMachines/States/CState.h>
#include <Framework/Foundation/Threads/CAutoResetEvent.h>
#include <Framework/Foundation/Threads/CAutoResetMultiEvent.h>
#include <Framework/Foundation/Threads/CManualResetEvent.h>
#include <Framework/Foundation/Threads/CManualResetMultiEvent.h>
#include <Framework/Foundation/Threads/CAtomic.h>
#include <Framework/Foundation/Threads/CThread.h>
#include <Framework/Foundation/Time/CTimePoint.h>
#include <Framework/Foundation/Time/CDateTime.h>
#include <Framework/Foundation/Time/CStopWatch.h>
#include <Framework/Foundation/Types/CFunction.h>
#include <Framework/Foundation/Types/CMethod.h>
#include <Framework/Foundation/Types/CNullable.h>
#include <Framework/Foundation/Types/CPrimitiveType.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
#include <Framework/Foundation/Types/SBool.h>
#include <Framework/Platform/Global/CFunctions.h>
#include <Framework/Testing/CTestManager.h>
#include <Tests/Framework/Cache/CCacheTest.h>
#include <Tests/Framework/Collections/CCollectionTest.h>
#include <Tests/Framework/FileSystem/CFileSystemTest.h>
#include <Tests/Framework/Mathematics/CMathematicsTest.h>
#include <Tests/Framework/Communication/CCommunicationTest.h>
#include <Tests/Framework/Communication/CSocketCANMenu.h>
#include <Tests/Framework/Communication/CSocketCANManagerMenu.h>
#include <Tests/Framework/Communication/CSocketDNSMenu.h>
#include <Tests/Framework/Communication/CSocketUDPMenu.h>
#include <Tests/Framework/Communication/CSocketUDPManagerMenu.h>
#include <Tests/Framework/Communication/CSocketUDPResponseManagerMenu.h>
#include <Tests/Framework/Communication/CSocketTCPMenu.h>
#include <Tests/Framework/Communication/CSocketTCPManagerMenu.h>
#include <Tests/Framework/Scheduler/CSchedulerTest.h>
#include <Tests/Framework/Security/CEncryptionTest.h>
#include <Tests/Framework/StateMachines/Tests/CStateMachineTest.h>
#include <Tests/Framework/Strings/CNumericConversionsTest.h>
#include <Tests/Framework/Threads/CThreadTest.h>
#include <Tests/Framework/Types/CFunctionTest.h>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
using namespace std::chrono;
using namespace CPPFoundation::Foundation;
using namespace CPPFoundation::Platform;
using namespace CPPFoundation::Testing;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void ExecuteTests(void)
{
	CConsoleLogWriter											LogWriter(CLogSource("TEST"));
	CLogCategory												LogCategory("TEST");
	CTestCollection												TestCollection;

	TestCollection.Add(CSPTest(new CCollectionTest(LogWriter,LogCategory)));
	//TestCollection.Add(CSPTest(new CFileSystemTest(LogWriter,LogCategory)));
	//TestCollection.Add(CSPTest(new CFunctionTest(LogWriter,LogCategory)));
	//TestCollection.Add(CSPTest(new CMathematicsTest(LogWriter,LogCategory)));
	//TestCollection.Add(CSPTest(new CNumericConversionsTest(LogWriter,LogCategory)));
	//TestCollection.Add(CSPTest(new CEncryptionTest(LogWriter,LogCategory,true)));
	//TestCollection.Add(CSPTest(new CSchedulerTest(LogWriter,LogCategory)));
	//TestCollection.Add(CSPTest(new CThreadTest(LogWriter,LogCategory,10,1000*1000*100,1000*100)));
	//TestCollection.Add(CSPTest(new CCommunicationTest(LogWriter,LogCategory)));
	//TestCollection.Add(CSPTest(new CStateMachineTest(LogWriter,LogCategory,false)));
	//TestCollection.Add(CSPTest(new CCacheTest(LogWriter,LogCategory)));
	//TestCollection.Add(CSPTest(new CEncryptionTest(LogWriter,LogCategory,false)));
	
	CTestManager												TestManager(LogWriter,LogCategory,TestCollection);

	TestManager.ExecuteTests();
}
//----------------------------------------------------------------------------------------------------------------------
void ExecuteSocketCANMenu(void)
{
	CConsoleLogWriter											LogWriter(CLogSource("SOCKET"));
	CSocketCANMenu												Menu(LogWriter);

	Menu.ExecuteMainMenuLoop();
}
//----------------------------------------------------------------------------------------------------------------------
void ExecuteSocketCANManagerMenu(void)
{
	CConsoleLogWriter											LogWriter(CLogSource("SOCKET"));
	CSocketCANManagerMenu										Menu(LogWriter);

	Menu.ExecuteMainMenuLoop();
}
//----------------------------------------------------------------------------------------------------------------------
void ExecuteSocketUDPMenu(void)
{
	CConsoleLogWriter											LogWriter(CLogSource("SOCKET"));
	CSocketUDPMenu												Menu(LogWriter);

	Menu.ExecuteMainMenuLoop();
}
//----------------------------------------------------------------------------------------------------------------------
void ExecuteSocketUDPManagerMenu(void)
{
	ISPLogFilter												LogFilter(new CLogFilter(CLogFilterConfiguration(true,true,true,true,true,CLogFilterConfiguration::CLogFilterConfigurationItemCollection())));
	CConsoleLogWriter											LogWriter(CLogSource("SOCKET"),LogFilter);
	CSocketUDPManagerMenu										Menu(LogWriter);

	Menu.ExecuteMainMenuLoop();
}
//----------------------------------------------------------------------------------------------------------------------
void ExecuteSocketUDPResponseManagerMenu(void)
{
	ISPLogFilter												LogFilter(new CLogFilter(CLogFilterConfiguration(true,true,true,true,true,CLogFilterConfiguration::CLogFilterConfigurationItemCollection())));
	CConsoleLogWriter											LogWriter(CLogSource("SOCKET"),LogFilter);
	CSocketUDPResponseManagerMenu								Menu(LogWriter);

	Menu.ExecuteMainMenuLoop();
}
//----------------------------------------------------------------------------------------------------------------------
void ExecuteSocketTCPMenu(void)
{
	CConsoleLogWriter											LogWriter(CLogSource("SOCKET"));
	CSocketTCPMenu												Menu(LogWriter);

	Menu.ExecuteMainMenuLoop();
}
//----------------------------------------------------------------------------------------------------------------------
void ExecuteSocketTCPManagerMenu(void)
{
	ISPLogFilter												LogFilter(new CLogFilter(CLogFilterConfiguration(true,true,true,true,true,CLogFilterConfiguration::CLogFilterConfigurationItemCollection())));
	CConsoleLogWriter											LogWriter(CLogSource("SOCKET"),LogFilter);
	CSocketTCPManagerMenu										Menu(LogWriter);

	Menu.ExecuteMainMenuLoop();
}
//----------------------------------------------------------------------------------------------------------------------
void ExecuteSocketDNSMenu(void)
{
	CConsoleLogWriter											LogWriter(CLogSource("SOCKET"));
	CSocketDNSMenu												Menu(LogWriter);

	Menu.ExecuteMainMenuLoop();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
	try
	{
		CConsoleHelper::InitializeConsole(true);

		//ExecuteTests();
		//ExecuteSocketCANMenu();
		//ExecuteSocketCANManagerMenu();
		//ExecuteSocketUDPMenu();
		//ExecuteSocketUDPManagerMenu();
		//ExecuteSocketUDPResponseManagerMenu();
		//ExecuteSocketTCPMenu();
		//ExecuteSocketTCPManagerMenu();
		//ExecuteSocketDNSMenu();
	}
	catch(const CException& E)
	{
		CConsoleHelper::WriteLine(MACRO_COLOR_TEXT_FULL(CString::Format("FATAL EXCEPTION [",E,"] !"),EConsoleColor::E_DARK_BLACK,EConsoleColor::E_LIGHT_RED,false));
	}

	CConsoleHelper::WriteLine("Press ENTER to EXIT !");
	CConsoleHelper::ReadLine();

	return(EXIT_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------