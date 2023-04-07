//----------------------------------------------------------------------------------------------------------------------
#include "CFileSystemTest.h"
#include <Framework/Foundation/Collections/CVector.h>
#include <Framework/Foundation/FileSystem/CDirectory.h>
#include <Framework/Foundation/FileSystem/CFile.h>
#include <Framework/Foundation/FileSystem/CFilePathTraitsLinux.h>
#include <Framework/Foundation/FileSystem/CFilePathTraitsWindows.h>
#include <Framework/Foundation/Threads/CThread.h>
#include <Framework/Foundation/Types/CMethod.h>
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
	CFileSystemTest::CFileSystemTest(CLogWriter& LogWriter, const CLogCategory& LogCategoryTest)
		: CTest(LogWriter,LogCategoryTest,"FILE SYSTEM TEST")
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CFileSystemTest::~CFileSystemTest(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CFileSystemTest::TestFilePathWindows(void) const
	{
		try
		{
			using												CTestPath=CFilePath<CFilePathTraitsWindows>;

			Size												TestNumber=0;
			CFileSystemTestPathData								TestPathData;

			CTestPath											Path1("C:\\Directory1\\Directory2\\Text.txt");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(true,"C:");
			TestPathData.SetRootDirectory(true,"\\");
			TestPathData.SetRootPath(true,"C:\\");
			TestPathData.SetParentPath(true,"C:\\Directory1\\Directory2");
			TestPathData.SetRelativePath(true,"Directory1\\Directory2\\Text.txt");
			TestPathData.SetFilename(true,"Text.txt");
			TestPathData.SetStem(true,"Text");
			TestPathData.SetExtension(true,"txt");

			CheckPath(TestNumber,Path1,TestPathData);

			CTestPath											Path2("\\Directory1\\Directory2\\Text.txt");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(false);
			TestPathData.SetRootDirectory(true,"\\");
			TestPathData.SetRootPath(true,"\\");
			TestPathData.SetParentPath(true,"\\Directory1\\Directory2");
			TestPathData.SetRelativePath(true,"Directory1\\Directory2\\Text.txt");
			TestPathData.SetFilename(true,"Text.txt");
			TestPathData.SetStem(true,"Text");
			TestPathData.SetExtension(true,"txt");

			CheckPath(TestNumber,Path2,TestPathData);

			CTestPath											Path3("Directory1\\Directory2\\Text.txt");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(false);
			TestPathData.SetRootDirectory(false);
			TestPathData.SetRootPath(false);
			TestPathData.SetParentPath(true,"Directory1\\Directory2");
			TestPathData.SetRelativePath(true,"Directory1\\Directory2\\Text.txt");
			TestPathData.SetFilename(true,"Text.txt");
			TestPathData.SetStem(true,"Text");
			TestPathData.SetExtension(true,"txt");

			CheckPath(TestNumber,Path3,TestPathData);

			CTestPath											Path4("Text.txt");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(false);
			TestPathData.SetRootDirectory(false);
			TestPathData.SetRootPath(false);
			TestPathData.SetParentPath(false);
			TestPathData.SetRelativePath(true,"Text.txt");
			TestPathData.SetFilename(true,"Text.txt");
			TestPathData.SetStem(true,"Text");
			TestPathData.SetExtension(true,"txt");

			CheckPath(TestNumber,Path4,TestPathData);

			CTestPath											Path5(".txt");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(false);
			TestPathData.SetRootDirectory(false);
			TestPathData.SetRootPath(false);
			TestPathData.SetParentPath(false);
			TestPathData.SetRelativePath(true,".txt");
			TestPathData.SetFilename(true,".txt");
			TestPathData.SetStem(false);
			TestPathData.SetExtension(true,"txt");

			CheckPath(TestNumber,Path5,TestPathData);

			CTestPath											Path6("XXX.");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(false);
			TestPathData.SetRootDirectory(false);
			TestPathData.SetRootPath(false);
			TestPathData.SetParentPath(false);
			TestPathData.SetRelativePath(true,"XXX.");
			TestPathData.SetFilename(true,"XXX.");
			TestPathData.SetStem(true,"XXX");
			TestPathData.SetExtension(false);

			CheckPath(TestNumber,Path6,TestPathData);

			CTestPath											Path7("XXX");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(false);
			TestPathData.SetRootDirectory(false);
			TestPathData.SetRootPath(false);
			TestPathData.SetParentPath(false);
			TestPathData.SetRelativePath(true,"XXX");
			TestPathData.SetFilename(true,"XXX");
			TestPathData.SetStem(true,"XXX");
			TestPathData.SetExtension(false);

			CheckPath(TestNumber,Path7,TestPathData);

			CTestPath											Path8(".");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(false);
			TestPathData.SetRootDirectory(false);
			TestPathData.SetRootPath(false);
			TestPathData.SetParentPath(false);
			TestPathData.SetRelativePath(true,".");
			TestPathData.SetFilename(true,".");
			TestPathData.SetStem(true,".");
			TestPathData.SetExtension(false);

			CheckPath(TestNumber,Path8,TestPathData);

			CTestPath											Path9("..");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(false);
			TestPathData.SetRootDirectory(false);
			TestPathData.SetRootPath(false);
			TestPathData.SetParentPath(false);
			TestPathData.SetRelativePath(true,"..");
			TestPathData.SetFilename(true,"..");
			TestPathData.SetStem(true,"..");
			TestPathData.SetExtension(false);

			CheckPath(TestNumber,Path9,TestPathData);

			CTestPath											Path10("C:\\Directory1\\Directory2\\");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(true,"C:");
			TestPathData.SetRootDirectory(true,"\\");
			TestPathData.SetRootPath(true,"C:\\");
			TestPathData.SetParentPath(true,"C:\\Directory1\\Directory2");
			TestPathData.SetRelativePath(true,"Directory1\\Directory2\\");
			TestPathData.SetFilename(false);
			TestPathData.SetStem(false);
			TestPathData.SetExtension(false);

			CheckPath(TestNumber,Path10,TestPathData);

			CTestPath											Path11("Directory1\\Directory2\\");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(false);
			TestPathData.SetRootDirectory(false);
			TestPathData.SetRootPath(false);
			TestPathData.SetParentPath(true,"Directory1\\Directory2");
			TestPathData.SetRelativePath(true,"Directory1\\Directory2\\");
			TestPathData.SetFilename(false);
			TestPathData.SetStem(false);
			TestPathData.SetExtension(false);

			CheckPath(TestNumber,Path11,TestPathData);

			CTestPath											Path12("\\XXX");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(false);
			TestPathData.SetRootDirectory(true,"\\");
			TestPathData.SetRootPath(true,"\\");
			TestPathData.SetParentPath(true,"\\");
			TestPathData.SetRelativePath(true,"XXX");
			TestPathData.SetFilename(true,"XXX");
			TestPathData.SetStem(true,"XXX");
			TestPathData.SetExtension(false);

			CheckPath(TestNumber,Path12,TestPathData);

			CTestPath											Path13("C:");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(true,"C:");
			TestPathData.SetRootDirectory(false);
			TestPathData.SetRootPath(true,"C:");
			TestPathData.SetParentPath(false);
			TestPathData.SetRelativePath(false);
			TestPathData.SetFilename(true,"C:");
			TestPathData.SetStem(true,"C:");
			TestPathData.SetExtension(false);

			CheckPath(TestNumber,Path13,TestPathData);

			CTestPath											Path14("C:\\");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(true,"C:");
			TestPathData.SetRootDirectory(true,"\\");
			TestPathData.SetRootPath(true,"C:\\");
			TestPathData.SetParentPath(true,"C:");
			TestPathData.SetRelativePath(false);
			TestPathData.SetFilename(false);
			TestPathData.SetStem(false);
			TestPathData.SetExtension(false);

			CheckPath(TestNumber,Path14,TestPathData);

			CTestPath											Path15("\\Directory\\Text");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(false);
			TestPathData.SetRootDirectory(true,"\\");
			TestPathData.SetRootPath(true,"\\");
			TestPathData.SetParentPath(true,"\\Directory");
			TestPathData.SetRelativePath(true,"Directory\\Text");
			TestPathData.SetFilename(true,"Text");
			TestPathData.SetStem(true,"Text");
			TestPathData.SetExtension(false);

			CheckPath(TestNumber,Path15,TestPathData);

			CTestPath											Path16("\\Directory1\\Directory2\\");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(false);
			TestPathData.SetRootDirectory(true,"\\");
			TestPathData.SetRootPath(true,"\\");
			TestPathData.SetParentPath(true,"\\Directory1\\Directory2");
			TestPathData.SetRelativePath(true,"Directory1\\Directory2\\");
			TestPathData.SetFilename(false);
			TestPathData.SetStem(false);
			TestPathData.SetExtension(false);

			CheckPath(TestNumber,Path16,TestPathData);

			CTestPath											Path17("C:\\File");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(true,"C:");
			TestPathData.SetRootDirectory(true,"\\");
			TestPathData.SetRootPath(true,"C:\\");
			TestPathData.SetParentPath(true,"C:\\");
			TestPathData.SetRelativePath(true,"File");
			TestPathData.SetFilename(true,"File");
			TestPathData.SetStem(true,"File");
			TestPathData.SetExtension(false);

			CheckPath(TestNumber,Path17,TestPathData);

			CTestPath											Path18("..txt");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(false);
			TestPathData.SetRootDirectory(false);
			TestPathData.SetRootPath(false);
			TestPathData.SetParentPath(false);
			TestPathData.SetRelativePath(true,"..txt");
			TestPathData.SetFilename(true,"..txt");
			TestPathData.SetStem(true,".");
			TestPathData.SetExtension(true,"txt");

			CheckPath(TestNumber,Path18,TestPathData);

			CTestPath											Path19("ABC:\\Directory1\\Directory2\\Text.txt");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(true,"ABC:");
			TestPathData.SetRootDirectory(true,"\\");
			TestPathData.SetRootPath(true,"ABC:\\");
			TestPathData.SetParentPath(true,"ABC:\\Directory1\\Directory2");
			TestPathData.SetRelativePath(true,"Directory1\\Directory2\\Text.txt");
			TestPathData.SetFilename(true,"Text.txt");
			TestPathData.SetStem(true,"Text");
			TestPathData.SetExtension(true,"txt");

			CheckPath(TestNumber,Path19,TestPathData);

			CTestPath											Path20("ABC:Directory1\\Directory2\\Text.txt");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(true,"ABC:");
			TestPathData.SetRootDirectory(false);
			TestPathData.SetRootPath(true,"ABC:");
			TestPathData.SetParentPath(true,"ABC:Directory1\\Directory2");
			TestPathData.SetRelativePath(true,"Directory1\\Directory2\\Text.txt");
			TestPathData.SetFilename(true,"Text.txt");
			TestPathData.SetStem(true,"Text");
			TestPathData.SetExtension(true,"txt");

			CheckPath(TestNumber,Path20,TestPathData);

			CTestPath											Path21("C:\\\\\\\\\\Directory1\\\\\\\\\\Directory2\\\\\\\\\\Text.txt");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(true,"C:");
			TestPathData.SetRootDirectory(true,"\\");
			TestPathData.SetRootPath(true,"C:\\");
			TestPathData.SetParentPath(true,"C:\\\\\\\\\\Directory1\\\\\\\\\\Directory2");
			TestPathData.SetRelativePath(true,"Directory1\\\\\\\\\\Directory2\\\\\\\\\\Text.txt");
			TestPathData.SetFilename(true,"Text.txt");
			TestPathData.SetStem(true,"Text");
			TestPathData.SetExtension(true,"txt");

			CheckPath(TestNumber,Path21,TestPathData);

			CTestPath											Path22("C:\\\\\\\\\\Directory1\\\\\\\\\\Directory2\\\\\\\\\\");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(true,"C:");
			TestPathData.SetRootDirectory(true,"\\");
			TestPathData.SetRootPath(true,"C:\\");
			TestPathData.SetParentPath(true,"C:\\\\\\\\\\Directory1\\\\\\\\\\Directory2");
			TestPathData.SetRelativePath(true,"Directory1\\\\\\\\\\Directory2\\\\\\\\\\");
			TestPathData.SetFilename(false);
			TestPathData.SetStem(false);
			TestPathData.SetExtension(false);

			CheckPath(TestNumber,Path22,TestPathData);

			CTestPath											Path23("\\\\\\\\\\Directory1\\\\\\\\\\Directory2\\\\\\\\\\");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(false);
			TestPathData.SetRootDirectory(true,"\\");
			TestPathData.SetRootPath(true,"\\");
			TestPathData.SetParentPath(true,"\\\\\\\\\\Directory1\\\\\\\\\\Directory2");
			TestPathData.SetRelativePath(true,"Directory1\\\\\\\\\\Directory2\\\\\\\\\\");
			TestPathData.SetFilename(false);
			TestPathData.SetStem(false);
			TestPathData.SetExtension(false);

			CheckPath(TestNumber,Path23,TestPathData);

			CTestPath											Path24("C:\\\\\\\\\\");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(true,"C:");
			TestPathData.SetRootDirectory(true,"\\");
			TestPathData.SetRootPath(true,"C:\\");
			TestPathData.SetParentPath(true,"C:");
			TestPathData.SetRelativePath(false);
			TestPathData.SetFilename(false);
			TestPathData.SetStem(false);
			TestPathData.SetExtension(false);

			CheckPath(TestNumber,Path24,TestPathData);

			CTestPath											Path25("\\\\");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(false);
			TestPathData.SetRootDirectory(true,"\\");
			TestPathData.SetRootPath(true,"\\");
			TestPathData.SetParentPath(false);
			TestPathData.SetRelativePath(false);
			TestPathData.SetFilename(false);
			TestPathData.SetStem(false);
			TestPathData.SetExtension(false);

			CheckPath(TestNumber,Path25,TestPathData);

			CTestPath											Path26("\\");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(false);
			TestPathData.SetRootDirectory(true,"\\");
			TestPathData.SetRootPath(true,"\\");
			TestPathData.SetParentPath(false);
			TestPathData.SetRelativePath(false);
			TestPathData.SetFilename(false);
			TestPathData.SetStem(false);
			TestPathData.SetExtension(false);

			CheckPath(TestNumber,Path26,TestPathData);

			CTestPath											Path27("////");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(false);
			TestPathData.SetRootDirectory(true,"/");
			TestPathData.SetRootPath(true,"/");
			TestPathData.SetParentPath(false);
			TestPathData.SetRelativePath(false);
			TestPathData.SetFilename(false);
			TestPathData.SetStem(false);
			TestPathData.SetExtension(false);

			CheckPath(TestNumber,Path27,TestPathData);

			CTestPath											Path28("/");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(false);
			TestPathData.SetRootDirectory(true,"/");
			TestPathData.SetRootPath(true,"/");
			TestPathData.SetParentPath(false);
			TestPathData.SetRelativePath(false);
			TestPathData.SetFilename(false);
			TestPathData.SetStem(false);
			TestPathData.SetExtension(false);

			CheckPath(TestNumber,Path28,TestPathData);

			CTestPath											Path29("\\\\ABC\\Directory1\\Directory2\\Text.txt");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(true,"\\\\ABC");
			TestPathData.SetRootDirectory(true,"\\");
			TestPathData.SetRootPath(true,"\\\\ABC\\");
			TestPathData.SetParentPath(true,"\\\\ABC\\Directory1\\Directory2");
			TestPathData.SetRelativePath(true,"Directory1\\Directory2\\Text.txt");
			TestPathData.SetFilename(true,"Text.txt");
			TestPathData.SetStem(true,"Text");
			TestPathData.SetExtension(true,"txt");

			CheckPath(TestNumber,Path29,TestPathData);

			CTestPath											Path30("C:C:\\Directory1\\Directory2\\Text.txt");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(true,"C:");
			TestPathData.SetRootDirectory(false);
			TestPathData.SetRootPath(true,"C:");
			TestPathData.SetParentPath(true,"C:C:\\Directory1\\Directory2");
			TestPathData.SetRelativePath(true,"C:\\Directory1\\Directory2\\Text.txt");
			TestPathData.SetFilename(true,"Text.txt");
			TestPathData.SetStem(true,"Text");
			TestPathData.SetExtension(true,"txt");

			CheckPath(TestNumber,Path30,TestPathData);

			CTestPath											SegmentPath1("C:\\Directory1\\Directory2\\Text.txt");
			CFilePathSegmentCollection							SegmentCollection1;

			SegmentCollection1.Add(CFilePathSegment(EFilePathSegmentType::E_ROOT,"C:"));
			SegmentCollection1.Add(CFilePathSegment(EFilePathSegmentType::E_ROOT_DIRECTORY,"\\"));
			SegmentCollection1.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Directory1"));
			SegmentCollection1.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Directory2"));
			SegmentCollection1.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Text.txt"));

			CheckFilePathSegments(++TestNumber,SegmentPath1,SegmentCollection1);

			CTestPath											SegmentPath2("C:/Directory1/Directory2/Text.txt");
			CFilePathSegmentCollection							SegmentCollection2;

			SegmentCollection2.Add(CFilePathSegment(EFilePathSegmentType::E_ROOT,"C:"));
			SegmentCollection2.Add(CFilePathSegment(EFilePathSegmentType::E_ROOT_DIRECTORY,"/"));
			SegmentCollection2.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Directory1"));
			SegmentCollection2.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Directory2"));
			SegmentCollection2.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Text.txt"));

			CheckFilePathSegments(++TestNumber,SegmentPath2,SegmentCollection2);

			CTestPath											SegmentPath3("\\Directory1\\Directory2\\Text.txt");
			CFilePathSegmentCollection							SegmentCollection3;

			SegmentCollection3.Add(CFilePathSegment(EFilePathSegmentType::E_ROOT_DIRECTORY,"\\"));
			SegmentCollection3.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Directory1"));
			SegmentCollection3.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Directory2"));
			SegmentCollection3.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Text.txt"));

			CheckFilePathSegments(++TestNumber,SegmentPath3,SegmentCollection3);

			CTestPath											SegmentPath4("\\Directory1\\Directory2\\");
			CFilePathSegmentCollection							SegmentCollection4;

			SegmentCollection4.Add(CFilePathSegment(EFilePathSegmentType::E_ROOT_DIRECTORY,"\\"));
			SegmentCollection4.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Directory1"));
			SegmentCollection4.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Directory2"));

			CheckFilePathSegments(++TestNumber,SegmentPath4,SegmentCollection4);

			CTestPath											SegmentPath5("Text.txt");
			CFilePathSegmentCollection							SegmentCollection5;

			SegmentCollection5.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Text.txt"));

			CheckFilePathSegments(++TestNumber,SegmentPath5,SegmentCollection5);

			CTestPath											SegmentPath6("C:Directory1\\Directory2\\Text.txt");
			CFilePathSegmentCollection							SegmentCollection6;

			SegmentCollection6.Add(CFilePathSegment(EFilePathSegmentType::E_ROOT,"C:"));
			SegmentCollection6.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Directory1"));
			SegmentCollection6.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Directory2"));
			SegmentCollection6.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Text.txt"));

			CheckFilePathSegments(++TestNumber,SegmentPath6,SegmentCollection6);

			CTestPath											SegmentPath7("Directory1\\Directory2\\Text.txt");
			CFilePathSegmentCollection							SegmentCollection7;

			SegmentCollection7.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Directory1"));
			SegmentCollection7.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Directory2"));
			SegmentCollection7.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Text.txt"));

			CheckFilePathSegments(++TestNumber,SegmentPath7,SegmentCollection7);

			CTestPath											SegmentPath8("C:C:/Directory1/Directory2/Text.txt");
			CFilePathSegmentCollection							SegmentCollection8;

			SegmentCollection8.Add(CFilePathSegment(EFilePathSegmentType::E_ROOT,"C:"));
			SegmentCollection8.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"C:"));
			SegmentCollection8.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Directory1"));
			SegmentCollection8.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Directory2"));
			SegmentCollection8.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Text.txt"));

			CheckFilePathSegments(++TestNumber,SegmentPath8,SegmentCollection8);

			CTestPath											SegmentPath9("C:\\\\\\Directory1\\\\\\Directory2\\\\\\Text.txt");
			CFilePathSegmentCollection							SegmentCollection9;

			SegmentCollection9.Add(CFilePathSegment(EFilePathSegmentType::E_ROOT,"C:"));
			SegmentCollection9.Add(CFilePathSegment(EFilePathSegmentType::E_ROOT_DIRECTORY,"\\"));
			SegmentCollection9.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Directory1"));
			SegmentCollection9.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Directory2"));
			SegmentCollection9.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Text.txt"));

			CheckFilePathSegments(++TestNumber,SegmentPath9,SegmentCollection9);

			CTestPath											SegmentPath10("\\\\ABC\\Directory1\\Directory2\\Text.txt");
			CFilePathSegmentCollection							SegmentCollection10;

			SegmentCollection10.Add(CFilePathSegment(EFilePathSegmentType::E_ROOT,"\\\\ABC"));
			SegmentCollection10.Add(CFilePathSegment(EFilePathSegmentType::E_ROOT_DIRECTORY,"\\"));
			SegmentCollection10.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Directory1"));
			SegmentCollection10.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Directory2"));
			SegmentCollection10.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Text.txt"));

			CheckFilePathSegments(++TestNumber,SegmentPath10,SegmentCollection10);

			CheckRemoveDuplicateDirectorySeparators(++TestNumber,CTestPath("C:\\Directory1\\Directory2\\Text.txt"),CTestPath("C:\\Directory1\\Directory2\\Text.txt"));
			CheckRemoveDuplicateDirectorySeparators(++TestNumber,CTestPath("C:\\\\Directory1\\\\Directory2\\\\Text.txt"),CTestPath("C:\\Directory1\\Directory2\\Text.txt"));
			CheckRemoveDuplicateDirectorySeparators(++TestNumber,CTestPath("C:\\\\\\Directory1\\\\\\Directory2\\\\\\Text.txt"),CTestPath("C:\\Directory1\\Directory2\\Text.txt"));
			CheckRemoveDuplicateDirectorySeparators(++TestNumber,CTestPath("\\\\\\Directory1\\\\\\Directory2\\\\\\"),CTestPath("\\Directory1\\Directory2\\"));

			CheckOperatorDivide(++TestNumber,CTestPath("C:\\AAA\\"),CTestPath("BBB"),CTestPath("C:\\AAA\\BBB"));
			CheckOperatorDivide(++TestNumber,CTestPath("C:\\AAA"),CTestPath("\\BBB"),CTestPath("C:\\AAA\\BBB"));
			CheckOperatorDivide(++TestNumber,CTestPath("C:\\AAA"),CTestPath("BBB"),CTestPath("C:\\AAA\\BBB"));
			CheckOperatorDivide(++TestNumber,CTestPath("C:\\AAA\\"),CTestPath(""),CTestPath("C:\\AAA\\"));
			CheckOperatorDivide(++TestNumber,CTestPath(""),CTestPath("BBB"),CTestPath("BBB"));

			CheckAppend(++TestNumber,CTestPath("C:\\AAA\\"),CTestPath("BBB"),"/",CTestPath("C:\\AAA\\BBB"));
			CheckAppend(++TestNumber,CTestPath("C:\\AAA"),CTestPath("\\BBB"),"/",CTestPath("C:\\AAA\\BBB"));
			CheckAppend(++TestNumber,CTestPath("C:\\AAA"),CTestPath("BBB"),"/",CTestPath("C:\\AAA/BBB"));

			CheckRemoveFilename(++TestNumber,CTestPath("C:\\Directory1\\Directory2\\Text.txt"),CTestPath("C:\\Directory1\\Directory2\\"));
			CheckRemoveFilename(++TestNumber,CTestPath("C:\\Directory1\\Directory2\\Text"),CTestPath("C:\\Directory1\\Directory2\\"));
			CheckRemoveFilename(++TestNumber,CTestPath("C:\\Directory1\\Directory2\\A"),CTestPath("C:\\Directory1\\Directory2\\"));
			CheckRemoveFilename(++TestNumber,CTestPath("C:\\Directory1\\Directory2\\"),CTestPath("C:\\Directory1\\Directory2\\"));
			CheckRemoveFilename(++TestNumber,CTestPath("C:\\"),CTestPath("C:\\"));
			CheckRemoveFilename(++TestNumber,CTestPath("C:"),CTestPath(""));
			CheckRemoveFilename(++TestNumber,CTestPath("C:\\Directory1\\Directory2\\\\Text.txt"),CTestPath("C:\\Directory1\\Directory2\\\\"));
			CheckRemoveFilename(++TestNumber,CTestPath("C:/Directory1/Directory2/Text.txt"),CTestPath("C:/Directory1/Directory2/"));
			CheckRemoveFilename(++TestNumber,CTestPath("C:/Directory1/Directory2/"),CTestPath("C:/Directory1/Directory2/"));
			CheckRemoveFilename(++TestNumber,CTestPath("C:/"),CTestPath("C:/"));

			CheckReplaceFilename(++TestNumber,CTestPath("C:\\Directory1\\Directory2\\Text.txt"),CTestPath("XXX.txt"),CTestPath("C:\\Directory1\\Directory2\\XXX.txt"));
			CheckReplaceFilename(++TestNumber,CTestPath("C:\\Directory1\\Directory2\\Text.txt"),CTestPath("Directory3\\XXX.txt"),CTestPath("C:\\Directory1\\Directory2\\Directory3\\XXX.txt"));
			CheckReplaceFilename(++TestNumber,CTestPath("C:\\Directory1\\Directory2\\Text.txt"),CTestPath("\\Directory3\\XXX.txt"),CTestPath("C:\\Directory1\\Directory2\\\\Directory3\\XXX.txt"));
			CheckReplaceFilename(++TestNumber,CTestPath("C:\\Directory1\\Directory2\\"),CTestPath("\\Directory3\\XXX.txt"),CTestPath("C:\\Directory1\\Directory2\\\\Directory3\\XXX.txt"));
			CheckReplaceFilename(++TestNumber,CTestPath("C:\\Directory1\\Directory2"),CTestPath("\\Directory3\\XXX.txt"),CTestPath("C:\\Directory1\\\\Directory3\\XXX.txt"));
			CheckReplaceFilename(++TestNumber,CTestPath("D:\\"),CTestPath("\\Directory\\"),CTestPath("D:\\\\Directory\\"));
			CheckReplaceFilename(++TestNumber,CTestPath("D:"),CTestPath("E:\\Directory\\ABC.txt"),CTestPath("E:\\Directory\\ABC.txt"));
			CheckReplaceFilename(++TestNumber,CTestPath("C:\\Directory1\\Directory2\\\\Text.txt"),CTestPath("\\\\XXX.txt"),CTestPath("C:\\Directory1\\Directory2\\\\\\\\XXX.txt"));
			CheckReplaceFilename(++TestNumber,CTestPath("C:/Directory1/Directory2/Text.txt"),CTestPath("Directory3/Text.txt"),CTestPath("C:/Directory1/Directory2/Directory3/Text.txt"));
			CheckReplaceFilename(++TestNumber,CTestPath("C:/Directory1/Directory2/"),CTestPath("/Directory3/Text.txt"),CTestPath("C:/Directory1/Directory2//Directory3/Text.txt"));
			CheckReplaceFilename(++TestNumber,CTestPath("C:/"),CTestPath("/Directory/Text.txt"),CTestPath("C://Directory/Text.txt"));

			CheckReplaceExtension(++TestNumber,CTestPath("C:\\Directory1\\Directory2\\Text.txt"),CTestPath("pdf"),CTestPath("C:\\Directory1\\Directory2\\Text.pdf"));
			CheckReplaceExtension(++TestNumber,CTestPath("C:\\Directory1\\Directory2\\Text."),CTestPath("pdf"),CTestPath("C:\\Directory1\\Directory2\\Text.pdf"));
			CheckReplaceExtension(++TestNumber,CTestPath("C:\\Directory1\\Directory2\\Text.txt"),CTestPath(".pdf"),CTestPath("C:\\Directory1\\Directory2\\Text..pdf"));
			CheckReplaceExtension(++TestNumber,CTestPath("C:\\Directory1\\Directory2\\Text"),CTestPath(".pdf"),CTestPath("C:\\Directory1\\Directory2\\Text.pdf"));

			return(true);
		}
		catch(const CException& E)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST PATH FAILED with EXCEPTION [",E.GetMessage(),"] !"));

			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST PATH FAILED with UNKNOWN EXCEPTION !"));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CFileSystemTest::TestFilePathLinux(void) const
	{
		try
		{
			using												CTestPath=CFilePath<CFilePathTraitsLinux>;

			Size												TestNumber=0;
			CFileSystemTestPathData								TestPathData;

			CTestPath											Path1("/Directory1/Directory2/Text.txt");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(false);
			TestPathData.SetRootDirectory(true,"/");
			TestPathData.SetRootPath(true,"/");
			TestPathData.SetParentPath(true,"/Directory1/Directory2");
			TestPathData.SetRelativePath(true,"Directory1/Directory2/Text.txt");
			TestPathData.SetFilename(true,"Text.txt");
			TestPathData.SetStem(true,"Text");
			TestPathData.SetExtension(true,"txt");

			CheckPath(TestNumber,Path1,TestPathData);

			CTestPath											Path2("Directory1/Directory2/Text.txt");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(false);
			TestPathData.SetRootDirectory(false);
			TestPathData.SetRootPath(false);
			TestPathData.SetParentPath(true,"Directory1/Directory2");
			TestPathData.SetRelativePath(true,"Directory1/Directory2/Text.txt");
			TestPathData.SetFilename(true,"Text.txt");
			TestPathData.SetStem(true,"Text");
			TestPathData.SetExtension(true,"txt");

			CheckPath(TestNumber,Path2,TestPathData);

			CTestPath											Path3("Directory1/Directory2/");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(false);
			TestPathData.SetRootDirectory(false);
			TestPathData.SetRootPath(false);
			TestPathData.SetParentPath(true,"Directory1/Directory2");
			TestPathData.SetRelativePath(true,"Directory1/Directory2/");
			TestPathData.SetFilename(false);
			TestPathData.SetStem(false);
			TestPathData.SetExtension(false);

			CheckPath(TestNumber,Path3,TestPathData);

			CTestPath											Path4("Directory1/Directory2/..");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(false);
			TestPathData.SetRootDirectory(false);
			TestPathData.SetRootPath(false);
			TestPathData.SetParentPath(true,"Directory1/Directory2");
			TestPathData.SetRelativePath(true,"Directory1/Directory2/..");
			TestPathData.SetFilename(true,"..");
			TestPathData.SetStem(true,"..");
			TestPathData.SetExtension(false);

			CheckPath(TestNumber,Path4,TestPathData);

			CTestPath											Path5("/XXX");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(false);
			TestPathData.SetRootDirectory(true,"/");
			TestPathData.SetRootPath(true,"/");
			TestPathData.SetParentPath(true,"/");
			TestPathData.SetRelativePath(true,"XXX");
			TestPathData.SetFilename(true,"XXX");
			TestPathData.SetStem(true,"XXX");
			TestPathData.SetExtension(false);

			CheckPath(TestNumber,Path5,TestPathData);

			CTestPath											Path6("/");

			TestNumber++;
			TestPathData.Reset();
			TestPathData.SetRootName(false);
			TestPathData.SetRootDirectory(true,"/");
			TestPathData.SetRootPath(true,"/");
			TestPathData.SetParentPath(false);
			TestPathData.SetRelativePath(false);
			TestPathData.SetFilename(false);
			TestPathData.SetStem(false);
			TestPathData.SetExtension(false);

			CheckPath(TestNumber,Path6,TestPathData);

			CTestPath											SegmentPath1("/Directory1/Directory2/Text.txt");
			CFilePathSegmentCollection							SegmentCollection1;

			SegmentCollection1.Add(CFilePathSegment(EFilePathSegmentType::E_ROOT_DIRECTORY,"/"));
			SegmentCollection1.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Directory1"));
			SegmentCollection1.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Directory2"));
			SegmentCollection1.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Text.txt"));

			CheckFilePathSegments(++TestNumber,SegmentPath1,SegmentCollection1);

			CTestPath											SegmentPath2("Directory1/Directory2/Text.txt");
			CFilePathSegmentCollection							SegmentCollection2;

			SegmentCollection2.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Directory1"));
			SegmentCollection2.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Directory2"));
			SegmentCollection2.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Text.txt"));

			CheckFilePathSegments(++TestNumber,SegmentPath2,SegmentCollection2);

			CTestPath											SegmentPath3("Text.txt");
			CFilePathSegmentCollection							SegmentCollection3;

			SegmentCollection3.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Text.txt"));

			CheckFilePathSegments(++TestNumber,SegmentPath3,SegmentCollection3);

			CTestPath											SegmentPath4("/////Directory1////Directory2///Text.txt");
			CFilePathSegmentCollection							SegmentCollection4;

			SegmentCollection4.Add(CFilePathSegment(EFilePathSegmentType::E_ROOT_DIRECTORY,"/"));
			SegmentCollection4.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Directory1"));
			SegmentCollection4.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Directory2"));
			SegmentCollection4.Add(CFilePathSegment(EFilePathSegmentType::E_DIRECTORY_OR_FILENAME,"Text.txt"));

			CheckFilePathSegments(++TestNumber,SegmentPath4,SegmentCollection4);

			CheckRemoveDuplicateDirectorySeparators(++TestNumber,CTestPath("/Directory1/Directory2/Text.txt"),CTestPath("/Directory1/Directory2/Text.txt"));
			CheckRemoveDuplicateDirectorySeparators(++TestNumber,CTestPath("//Directory1//Directory2//Text.txt"),CTestPath("/Directory1/Directory2/Text.txt"));
			CheckRemoveDuplicateDirectorySeparators(++TestNumber,CTestPath("///Directory1///Directory2///Text.txt"),CTestPath("/Directory1/Directory2/Text.txt"));
			CheckRemoveDuplicateDirectorySeparators(++TestNumber,CTestPath("///Directory1///Directory2///"),CTestPath("/Directory1/Directory2/"));

			CheckOperatorDivide(++TestNumber,CTestPath("/AAA/"),CTestPath("BBB"),CTestPath("/AAA/BBB"));
			CheckOperatorDivide(++TestNumber,CTestPath("/AAA"),CTestPath("/BBB"),CTestPath("/AAA/BBB"));
			CheckOperatorDivide(++TestNumber,CTestPath("/AAA"),CTestPath("BBB"),CTestPath("/AAA/BBB"));

			CheckAppend(++TestNumber,CTestPath("/AAA/"),CTestPath("BBB"),"\\",CTestPath("/AAA/BBB"));
			CheckAppend(++TestNumber,CTestPath("/AAA"),CTestPath("/BBB"),"\\",CTestPath("/AAA/BBB"));
			CheckAppend(++TestNumber,CTestPath("/AAA"),CTestPath("BBB"),"\\",CTestPath("/AAA\\BBB"));

			CheckRemoveFilename(++TestNumber,CTestPath("/Directory1/Directory2/Text.txt"),CTestPath("/Directory1/Directory2/"));
			CheckRemoveFilename(++TestNumber,CTestPath("/Directory1/Directory2/"),CTestPath("/Directory1/Directory2/"));
			CheckRemoveFilename(++TestNumber,CTestPath("/"),CTestPath("/"));

			CheckReplaceFilename(++TestNumber,CTestPath("C:/Directory1/Directory2/Text.txt"),CTestPath("Directory3/Text.txt"),CTestPath("C:/Directory1/Directory2/Directory3/Text.txt"));
			CheckReplaceFilename(++TestNumber,CTestPath("C:/Directory1/Directory2/"),CTestPath("/Directory3/Text.txt"),CTestPath("C:/Directory1/Directory2//Directory3/Text.txt"));
			CheckReplaceFilename(++TestNumber,CTestPath("C:/"),CTestPath("/Directory/Text.txt"),CTestPath("C://Directory/Text.txt"));

			CheckReplaceExtension(++TestNumber,CTestPath("/Directory1/Directory2/Text.txt"),CTestPath("pdf"),CTestPath("/Directory1/Directory2/Text.pdf"));
			CheckReplaceExtension(++TestNumber,CTestPath("/Directory1/Directory2/Text."),CTestPath("pdf"),CTestPath("/Directory1/Directory2/Text.pdf"));
			CheckReplaceExtension(++TestNumber,CTestPath("/Directory1/Directory2/Text.txt"),CTestPath(".pdf"),CTestPath("/Directory1/Directory2/Text..pdf"));

			return(true);
		}
		catch(const CException& E)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST PATH FAILED with EXCEPTION [",E.GetMessage(),"] !"));

			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST PATH FAILED with UNKNOWN EXCEPTION !"));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CFileSystemTest::TestFileOperationsOpenCloseReadWrite(void) const
	{
		try
		{
#if defined(PLATFORM_WINDOWS)
			CPath												Path(".\\Text.txt");
#elif defined(PLATFORM_LINUX)
			CPath												Path("Text.txt");
#else
#error UNSUPPORTED PLATFORM !
#endif
			{
				CFile											File(Path.GetPath(),EFileOpenMode::E_CREATE,EFileAccessMode::E_WRITE);
				CByteBuffer										Buffer({0x41,0x42,0x43,0x44,0x45});

				if (File.Write(Buffer,0,Buffer.GetLength())!=Buffer.GetLength())
				{
					throw(CInvalidOperationException("FILE WRITE FAILED !"));
				}

				if (File.Write(Buffer,1,2)!=2)
				{
					throw(CInvalidOperationException("FILE WRITE FAILED !"));
				}

				if (File.Write(Buffer,4,1)!=1)
				{
					throw(CInvalidOperationException("FILE WRITE FAILED !"));
				}

				try
				{
					File.Write(Buffer,4,2);

					CConsoleHelper::WriteLine(CString::Format("\tFILE WRITE FAILED !"));

					return(false);
				}
				catch(const CException&)
				{
				}

				try
				{
					File.Write(Buffer,5,1);

					CConsoleHelper::WriteLine(CString::Format("\tFILE WRITE FAILED !"));

					return(false);
				}
				catch(const CException&)
				{
				}
			}

			{
				// FILE is OPENED for READING.
				CFile											File(Path.GetPath(),EFileOpenMode::E_OPEN,EFileAccessMode::E_READ);
				CByteBuffer										Buffer(100);

				try
				{
					// Must THROW an EXCEPTION.
					File.Write(Buffer,0,Buffer.GetLength());

					CConsoleHelper::WriteLine(CString::Format("\tFILE WRITE FAILED !"));

					return(false);
				}
				catch(const CException&)
				{
				}
			}

			{
				// FILE is OPENED for READING.
				CFile											File(Path.GetPath(),EFileOpenMode::E_OPEN_OR_CREATE,EFileAccessMode::E_READ);
				CByteBuffer										Buffer(100);

				if (File.Read(Buffer,0,Buffer.GetLength())!=8)
				{
					throw(CInvalidOperationException("FILE READ FAILED !"));
				}

				Buffer.Resize(8);

				CByteBuffer										BufferToCompare({0x41,0x42,0x43,0x44,0x45,0x42,0x43,0x45});

				if (Buffer!=BufferToCompare)
				{
					throw(CInvalidOperationException("FILE READ FAILED !"));
				}

				try
				{
					File.Write(Buffer,99,2);

					CConsoleHelper::WriteLine(CString::Format("\tFILE WRITE FAILED !"));

					return(false);
				}
				catch(const CException&)
				{
				}

				try
				{
					File.Write(Buffer,100,1);

					CConsoleHelper::WriteLine(CString::Format("\tFILE WRITE FAILED !"));

					return(false);
				}
				catch(const CException&)
				{
				}
			}

			{
				// FILE is OPENED for READING.
				CFile											File(Path.GetPath(),EFileOpenMode::E_OPEN_OR_CREATE,EFileAccessMode::E_READ);
				CByteBuffer										Buffer=File.ReadAll();
				CByteBuffer										BufferToCompare({0x41,0x42,0x43,0x44,0x45,0x42,0x43,0x45});

				if (Buffer!=BufferToCompare)
				{
					throw(CInvalidOperationException("FILE READ ALL FAILED !"));
				}
			}

			{
				try
				{
					// FILE ALREADY EXISTS. EXCEPTION must be THROWN.
					CFile										File(Path.GetPath(),EFileOpenMode::E_CREATE_NEW,EFileAccessMode::E_READ_WRITE);

					CConsoleHelper::WriteLine(CString::Format("\tFILE OPEN FAILED !"));

					return(false);
				}
				catch(const CException&)
				{
				}
			}

			{
				CFile											File(Path.GetPath(),EFileOpenMode::E_OPEN_AND_TRUNCATE,EFileAccessMode::E_READ_WRITE);
				CByteBuffer										Buffer(100);

				if (File.Read(Buffer,0,Buffer.GetLength())!=0)
				{
					throw(CInvalidOperationException("FILE READ FAILED !"));
				}
			}

			bool												FileDeleteSucceeded=false;

			try
			{
				CFile::Delete(Path.GetPath());

				FileDeleteSucceeded=true;
			}
			catch(const CException&)
			{
			}

			if (FileDeleteSucceeded==false)
			{
				throw(CInvalidOperationException("FILE DELETE FAILED !"));
			}
		
			return(true);
		}
		catch(const CException& E)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST FILE OPERATIONS (OPEN CLOSE READ WRITE) FAILED with EXCEPTION [",E.GetMessage(),"] !"));

			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST FILE OPERATIONS (OPEN CLOSE READ WRITE) FAILED with UNKNOWN EXCEPTION !"));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CFileSystemTest::TestFileOperationsSeek(void) const
	{
		try
		{
#if defined(PLATFORM_WINDOWS)
			CPath												Path(".\\Text.txt");
#elif defined(PLATFORM_LINUX)
			CPath												Path("Text.txt");
#else
#error UNSUPPORTED PLATFORM !
#endif
			{
				CFile											File(Path.GetPath(),EFileOpenMode::E_CREATE,EFileAccessMode::E_WRITE);
				CByteBuffer										Buffer({0x41,0x42,0x43,0x44,0x45});

				if (File.Write(Buffer,0,Buffer.GetLength())!=Buffer.GetLength())
				{
					throw(CInvalidOperationException("FILE WRITE FAILED !"));
				}
			}

			{
				// FILE is OPENED for READING.
				CFile											File(Path.GetPath(),EFileOpenMode::E_OPEN,EFileAccessMode::E_READ);
				CByteBuffer										Buffer(100);

				if (File.Read(Buffer,0,Buffer.GetLength())!=5)
				{
					throw(CInvalidOperationException("FILE READ FAILED !"));
				}

				Buffer.Resize(5);

				CByteBuffer										BufferToCompare({0x41,0x42,0x43,0x44,0x45});

				if (Buffer!=BufferToCompare)
				{
					throw(CInvalidOperationException("FILE READ FAILED !"));
				}
			}

			{
				// FILE is OPENED for READING.
				CFile											File(Path.GetPath(),EFileOpenMode::E_OPEN,EFileAccessMode::E_READ);

				if (File.Seek(2,EFileSeekMode::E_BEGIN)!=2)
				{
					throw(CInvalidOperationException("FILE SEEK FAILED !"));
				}

				CByteBuffer										Buffer1(100);

				if (File.Read(Buffer1,0,Buffer1.GetLength())!=3)
				{
					throw(CInvalidOperationException("FILE READ FAILED !"));
				}

				Buffer1.Resize(3);

				CByteBuffer										BufferToCompare1({0x43,0x44,0x45});

				if (Buffer1!=BufferToCompare1)
				{
					throw(CInvalidOperationException("FILE READ FAILED !"));
				}

				if (File.Seek(-2,EFileSeekMode::E_END)!=3)
				{
					throw(CInvalidOperationException("FILE SEEK FAILED !"));
				}

				CByteBuffer										Buffer2(100);

				if (File.Read(Buffer2,0,Buffer2.GetLength())!=2)
				{
					throw(CInvalidOperationException("FILE READ FAILED !"));
				}

				Buffer2.Resize(2);

				CByteBuffer										BufferToCompare2({0x44,0x45});

				if (Buffer2!=BufferToCompare2)
				{
					throw(CInvalidOperationException("FILE READ FAILED !"));
				}

				if (File.Seek(-2,EFileSeekMode::E_CURRENT)!=3)
				{
					throw(CInvalidOperationException("FILE SEEK FAILED !"));
				}

				CByteBuffer										Buffer3(100);

				if (File.Read(Buffer3,0,Buffer3.GetLength())!=2)
				{
					throw(CInvalidOperationException("FILE READ FAILED !"));
				}

				Buffer3.Resize(2);

				CByteBuffer										BufferToCompare3({0x44,0x45});

				if (Buffer3!=BufferToCompare3)
				{
					throw(CInvalidOperationException("FILE READ FAILED !"));
				}
			}

			bool												FileDeleteSucceeded=false;

			try
			{
				CFile::Delete(Path.GetPath());

				FileDeleteSucceeded=true;
			}
			catch(const CException&)
			{
			}

			if (FileDeleteSucceeded==false)
			{
				throw(CInvalidOperationException("FILE DELETE FAILED !"));
			}

			return(true);
		}
		catch(const CException& E)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST FILE OPERATIONS (SEEK) FAILED with EXCEPTION [",E.GetMessage(),"] !"));

			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST FILE OPERATIONS (SEEK) FAILED with UNKNOWN EXCEPTION !"));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CFileSystemTest::TestFileOperationsGetFileSize(void) const
	{
		try
		{
#if defined(PLATFORM_WINDOWS)
			CPath												Path(".\\Text.txt");
#elif defined(PLATFORM_LINUX)
			CPath												Path("Text.txt");
#else
#error UNSUPPORTED PLATFORM !
#endif
			{
				CFile											File(Path.GetPath(),EFileOpenMode::E_CREATE,EFileAccessMode::E_WRITE);
				CByteBuffer										Buffer({0x41,0x42,0x43,0x44,0x45});

				if (File.Write(Buffer,0,Buffer.GetLength())!=Buffer.GetLength())
				{
					throw(CInvalidOperationException("FILE WRITE FAILED !"));
				}
			}

			{
				CFile											File(Path.GetPath(),EFileOpenMode::E_OPEN,EFileAccessMode::E_READ);

				if (File.GetSize()!=5)
				{
					throw(CInvalidOperationException("FILE GET SIZE FAILED !"));
				}
			}

			bool												FileDeleteSucceeded=false;

			try
			{
				CFile::Delete(Path.GetPath());

				FileDeleteSucceeded=true;
			}
			catch(const CException&)
			{
			}

			if (FileDeleteSucceeded==false)
			{
				throw(CInvalidOperationException("FILE DELETE FAILED !"));
			}

			return(true);
		}
		catch(const CException& E)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST FILE OPERATIONS (GET FILE SIZE) FAILED with EXCEPTION [",E.GetMessage(),"] !"));

			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST FILE OPERATIONS (GET FILE SIZE) FAILED with UNKNOWN EXCEPTION !"));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CFileSystemTest::TestFileOperationsCopyMoveExistsDelete(void) const
	{
		try
		{
#if defined(PLATFORM_WINDOWS)
			CPath												Path1(".\\Text1.txt");
			CPath												Path2(".\\Text2.txt");
			CPath												Path3(".\\Text3.txt");
#elif defined(PLATFORM_LINUX)
			CPath												Path1("Text1.txt");
			CPath												Path2("Text2.txt");
			CPath												Path3("Text3.txt");
#else
#error UNSUPPORTED PLATFORM !
#endif
			{
				CFile											File(Path1.GetPath(),EFileOpenMode::E_CREATE,EFileAccessMode::E_WRITE);
				CByteBuffer										Buffer({0x41,0x42,0x43,0x44,0x45});

				if (File.Write(Buffer,0,Buffer.GetLength())!=Buffer.GetLength())
				{
					throw(CInvalidOperationException("FILE WRITE FAILED !"));
				}
			}

			{
				// FILE is OPENED for READING.
				CFile											File(Path1.GetPath(),EFileOpenMode::E_OPEN,EFileAccessMode::E_READ);
				CByteBuffer										Buffer(100);

				if (File.Read(Buffer,0,Buffer.GetLength())!=5)
				{
					throw(CInvalidOperationException("FILE READ FAILED !"));
				}

				Buffer.Resize(5);

				CByteBuffer										BufferToCompare({0x41,0x42,0x43,0x44,0x45});

				if (Buffer!=BufferToCompare)
				{
					throw(CInvalidOperationException("FILE READ FAILED !"));
				}
			}

			CFile::Copy(Path1.GetPath(),Path2.GetPath());

			{
				// FILE is OPENED for READING.
				CFile											File(Path2.GetPath(),EFileOpenMode::E_OPEN,EFileAccessMode::E_READ);
				CByteBuffer										Buffer(100);

				if (File.Read(Buffer,0,Buffer.GetLength())!=5)
				{
					throw(CInvalidOperationException("FILE READ FAILED !"));
				}

				Buffer.Resize(5);

				CByteBuffer										BufferToCompare({0x41,0x42,0x43,0x44,0x45});

				if (Buffer!=BufferToCompare)
				{
					throw(CInvalidOperationException("FILE READ FAILED !"));
				}
			}

			CFile::Move(Path1.GetPath(),Path3.GetPath());

			{
				// FILE is OPENED for READING.
				CFile											File(Path3.GetPath(),EFileOpenMode::E_OPEN,EFileAccessMode::E_READ);
				CByteBuffer										Buffer(100);

				if (File.Read(Buffer,0,Buffer.GetLength())!=5)
				{
					throw(CInvalidOperationException("FILE READ FAILED !"));
				}

				Buffer.Resize(5);

				CByteBuffer										BufferToCompare({0x41,0x42,0x43,0x44,0x45});

				if (Buffer!=BufferToCompare)
				{
					throw(CInvalidOperationException("FILE READ FAILED !"));
				}
			}

			// FILE MUST EXIST.
			if (CFile::Exists(Path1.GetPath())==true)
			{
				throw(CInvalidOperationException("FILE EXISTS FAILED !"));
			}

			// FILE MUST EXIST.
			if (CFile::Exists(Path2.GetPath())==false)
			{
				throw(CInvalidOperationException("FILE EXISTS FAILED !"));
			}

			// FILE MUST EXIST.
			if (CFile::Exists(Path3.GetPath())==false)
			{
				throw(CInvalidOperationException("FILE EXISTS FAILED !"));
			}

			bool												FileDeleteSucceeded1=false;

			try
			{
				CFile::Delete(Path1.GetPath());

				FileDeleteSucceeded1=true;
			}
			catch(const CException&)
			{
			}

			if (FileDeleteSucceeded1==true)
			{
				throw(CInvalidOperationException("FILE DELETE FAILED !"));
			}

			bool												FileDeleteSucceeded2=false;

			try
			{
				CFile::Delete(Path2.GetPath());

				FileDeleteSucceeded2=true;
			}
			catch(const CException&)
			{
			}

			if (FileDeleteSucceeded2==false)
			{
				throw(CInvalidOperationException("FILE DELETE FAILED !"));
			}

			bool												FileDeleteSucceeded3=false;

			try
			{
				CFile::Delete(Path3.GetPath());

				FileDeleteSucceeded3=true;
			}
			catch(const CException&)
			{
			}

			if (FileDeleteSucceeded3==false)
			{
				throw(CInvalidOperationException("FILE DELETE FAILED !"));
			}

			return(true);
		}
		catch(const CException& E)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST FILE OPERATIONS (COPY MODE EXISTS DELETE) FAILED with EXCEPTION [",E.GetMessage(),"] !"));

			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST FILE OPERATIONS (COPY MODE EXISTS DELETE) FAILED with UNKNOWN EXCEPTION !"));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CFileSystemTest::TestFileOperationsReadUntil(void) const
	{
		try
		{
#if defined(PLATFORM_WINDOWS)
			CPath												Path(".\\Text.txt");
#elif defined(PLATFORM_LINUX)
			CPath												Path("Text.txt");
#else
#error UNSUPPORTED PLATFORM !
#endif
			{
				CFile											File(Path.GetPath(),EFileOpenMode::E_CREATE,EFileAccessMode::E_WRITE);
				CByteBuffer										Buffer({0x41,0x42,0x43,0x44,0x45});

				if (File.Write(Buffer,0,Buffer.GetLength())!=Buffer.GetLength())
				{
					throw(CInvalidOperationException("FILE WRITE FAILED !"));
				}

				if (File.Write(Buffer)!=Buffer.GetLength())
				{
					throw(CInvalidOperationException("FILE WRITE FAILED !"));
				}
			}

			{
				CFile											File(Path.GetPath(),EFileOpenMode::E_OPEN,EFileAccessMode::E_READ);
				CByteBuffer										EndSequence({0x43,0x44});
				CByteBuffer										Part1({0x41,0x42,0x43,0x44});
				CByteBuffer										Part2({0x45,0x41,0x42,0x43,0x44});
				CByteBuffer										Part3({0x45});
				CByteBuffer										Part4({});

				if (File.ReadUntil(EndSequence,true)!=Part1)
				{
					throw(CInvalidOperationException("FILE READ UNTIL FAILED !"));
				}

				if (File.ReadUntil(EndSequence,true)!=Part2)
				{
					throw(CInvalidOperationException("FILE READ UNTIL FAILED !"));
				}

				if (File.ReadUntil(EndSequence,true)!=Part3)
				{
					throw(CInvalidOperationException("FILE READ UNTIL FAILED !"));
				}

				if (File.ReadUntil(EndSequence,true)!=Part4)
				{
					throw(CInvalidOperationException("FILE READ UNTIL FAILED !"));
				}
			}

			{
				CFile											File(Path.GetPath(),EFileOpenMode::E_OPEN,EFileAccessMode::E_READ);
				CByteBuffer										EndSequence({0x44,0x45});
				CByteBuffer										Part1({0x41,0x42,0x43,0x44,0x45});
				CByteBuffer										Part2({0x41,0x42,0x43,0x44,0x45});
				CByteBuffer										Part3({});

				if (File.ReadUntil(EndSequence,true)!=Part1)
				{
					throw(CInvalidOperationException("FILE READ UNTIL FAILED !"));
				}

				if (File.ReadUntil(EndSequence,true)!=Part2)
				{
					throw(CInvalidOperationException("FILE READ UNTIL FAILED !"));
				}

				if (File.ReadUntil(EndSequence,true)!=Part3)
				{
					throw(CInvalidOperationException("FILE READ UNTIL FAILED !"));
				}
			}

			{
				CFile											File(Path.GetPath(),EFileOpenMode::E_OPEN,EFileAccessMode::E_READ);
				CByteBuffer										EndSequence({0x42,0x43,0x44});
				CByteBuffer										Part1({0x41,0x42,0x43,0x44});
				CByteBuffer										Part2({0x45,0x41,0x42,0x43,0x44});
				CByteBuffer										Part3({0x45});
				CByteBuffer										Part4({});

				if (File.ReadUntil(EndSequence,true,2)!=Part1)
				{
					throw(CInvalidOperationException("FILE READ UNTIL FAILED !"));
				}

				if (File.ReadUntil(EndSequence,true,2)!=Part2)
				{
					throw(CInvalidOperationException("FILE READ UNTIL FAILED !"));
				}

				if (File.ReadUntil(EndSequence,true,2)!=Part3)
				{
					throw(CInvalidOperationException("FILE READ UNTIL FAILED !"));
				}

				if (File.ReadUntil(EndSequence,true,2)!=Part4)
				{
					throw(CInvalidOperationException("FILE READ UNTIL FAILED !"));
				}
			}

			{
				CFile											File(Path.GetPath(),EFileOpenMode::E_OPEN,EFileAccessMode::E_READ);
				CByteBuffer										EndSequence({0x42,0x44});
				CByteBuffer										Part1({0x41,0x42,0x43,0x44,0x45,0x41,0x42,0x43,0x44,0x45});
				CByteBuffer										Part2({});

				if (File.ReadUntil(EndSequence,true)!=Part1)
				{
					throw(CInvalidOperationException("FILE READ UNTIL FAILED !"));
				}

				if (File.ReadUntil(EndSequence,true)!=Part2)
				{
					throw(CInvalidOperationException("FILE READ UNTIL FAILED !"));
				}
			}

			{
				CFile											File(Path.GetPath(),EFileOpenMode::E_OPEN,EFileAccessMode::E_READ);
				CByteBuffer										EndSequence({0x42,0x44});
				CByteBuffer										Part1({0x41,0x42,0x43,0x44,0x45,0x41,0x42,0x43,0x44,0x45});
				CByteBuffer										Part2({});

				if (File.ReadUntil(EndSequence,true,2)!=Part1)
				{
					throw(CInvalidOperationException("FILE READ UNTIL FAILED !"));
				}

				if (File.ReadUntil(EndSequence,true,2)!=Part2)
				{
					throw(CInvalidOperationException("FILE READ UNTIL FAILED !"));
				}
			}

			{
				CFile											File(Path.GetPath(),EFileOpenMode::E_OPEN,EFileAccessMode::E_READ);
				CByteBuffer										EndSequence({0x43,0x44});
				CByteBuffer										Part1({0x41,0x42});
				CByteBuffer										Part2({0x45,0x41,0x42});
				CByteBuffer										Part3({0x45});
				CByteBuffer										Part4({});

				if (File.ReadUntil(EndSequence,false)!=Part1)
				{
					throw(CInvalidOperationException("FILE READ UNTIL FAILED !"));
				}

				if (File.ReadUntil(EndSequence,false)!=Part2)
				{
					throw(CInvalidOperationException("FILE READ UNTIL FAILED !"));
				}

				if (File.ReadUntil(EndSequence,false)!=Part3)
				{
					throw(CInvalidOperationException("FILE READ UNTIL FAILED !"));
				}

				if (File.ReadUntil(EndSequence,false)!=Part4)
				{
					throw(CInvalidOperationException("FILE READ UNTIL FAILED !"));
				}
			}

			bool												FileDeleteSucceeded=false;

			try
			{
				CFile::Delete(Path.GetPath());

				FileDeleteSucceeded=true;
			}
			catch(const CException&)
			{
			}

			if (FileDeleteSucceeded==false)
			{
				throw(CInvalidOperationException("FILE DELETE FAILED !"));
			}

			if (CFile::Exists(Path.GetPath())==true)
			{
				throw(CInvalidOperationException("FILE EXISTS FAILED !"));
			}

			return(true);
		}
		catch(const CException& E)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST FILE OPERATIONS (READ UNTIL) FAILED with EXCEPTION [",E.GetMessage(),"] !"));

			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST FILE OPERATIONS (READ UNTIL) FAILED with UNKNOWN EXCEPTION !"));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CFileSystemTest::TestFileOperationsStringInterface(void) const
	{
		try
		{
#if defined(PLATFORM_WINDOWS)
			CPath												Path(".\\Text.txt");
#elif defined(PLATFORM_LINUX)
			CPath												Path("Text.txt");
#else
#error UNSUPPORTED PLATFORM !
#endif
			{
				CFile											File(Path.GetPath(),EFileOpenMode::E_CREATE,EFileAccessMode::E_WRITE);
				CString											Buffer("ABCDE+-FGH+-IJKL");

				if (File.WriteString(Buffer)!=Buffer.GetLength())
				{
					throw(CInvalidOperationException("FILE WRITE STRING FAILED !"));
				}
			}

			{
				// FILE is OPENED for READING.
				CFile											File(Path.GetPath(),EFileOpenMode::E_OPEN,EFileAccessMode::E_READ);
	
				if (File.ReadString(4)!=CString("ABCD"))
				{
					throw(CInvalidOperationException("FILE READ STRING FAILED !"));
				}

				if (File.ReadString(5)!=CString("E+-FG"))
				{
					throw(CInvalidOperationException("FILE READ STRING FAILED !"));
				}
			}

			{
				// FILE is OPENED for READING.
				CFile											File(Path.GetPath(),EFileOpenMode::E_OPEN,EFileAccessMode::E_READ);
	
				if (File.ReadStringLine("+-")!=CString("ABCDE"))
				{
					throw(CInvalidOperationException("FILE READ STRING LINE FAILED !"));
				}

				if (File.ReadStringLine("+-")!=CString("FGH"))
				{
					throw(CInvalidOperationException("FILE READ STRING LINE FAILED !"));
				}

				if (File.ReadStringLine("+-")!=CString("IJKL"))
				{
					throw(CInvalidOperationException("FILE READ STRING LINE FAILED !"));
				}

				if (File.ReadStringLine("+-")!=CString())
				{
					throw(CInvalidOperationException("FILE READ STRING LINE FAILED !"));
				}
			}

			{
				// FILE is OPENED for READING.
				CFile											File(Path.GetPath(),EFileOpenMode::E_OPEN,EFileAccessMode::E_READ);
	
				if (File.ReadStringAll()!=CString("ABCDE+-FGH+-IJKL"))
				{
					throw(CInvalidOperationException("FILE READ STRING ALL FAILED !"));
				}
			}

			bool												FileDeleteSucceeded=false;

			try
			{
				CFile::Delete(Path.GetPath());

				FileDeleteSucceeded=true;
			}
			catch(const CException&)
			{
			}

			if (FileDeleteSucceeded==false)
			{
				throw(CInvalidOperationException("FILE DELETE FAILED !"));
			}

			if (CFile::Exists(Path.GetPath())==true)
			{
				throw(CInvalidOperationException("FILE EXISTS FAILED !"));
			}

			return(true);
		}
		catch(const CException& E)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST FILE OPERATIONS (STRING INTERFACE) FAILED with EXCEPTION [",E.GetMessage(),"] !"));

			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST FILE OPERATIONS (STRING INTERFACE) FAILED with UNKNOWN EXCEPTION !"));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CFileSystemTest::TestFileOperationsGetTime(void) const
	{
		try
		{
#if defined(PLATFORM_WINDOWS)
			CPath												Path(".\\Text.txt");
#elif defined(PLATFORM_LINUX)
			CPath												Path("Text.txt");
#else
#error UNSUPPORTED PLATFORM !
#endif
			CDateTime											Time1=CDateTime::GetCurrentLocalTime();

			{
				CFile											File(Path.GetPath(),EFileOpenMode::E_CREATE,EFileAccessMode::E_WRITE);
				CByteBuffer										Buffer({0x41,0x42,0x43,0x44,0x45});

				if (File.Write(Buffer,0,Buffer.GetLength())!=Buffer.GetLength())
				{
					throw(CInvalidOperationException("FILE WRITE FAILED !"));
				}

				CDateTime										LastModificationTime=File.GetFileLastModificationTime();
				CDateTime::DateTimeTicks						Difference=(LastModificationTime-Time1);

				if (Difference>1000)
				{
					throw(CInvalidOperationException("FILE GET LAST MODIFICATION TIME FAILED !"));
				}
			}

			CThread::Sleep(3000);

			CDateTime											Time2=CDateTime::GetCurrentLocalTime();

			{
				CFile											File(Path.GetPath(),EFileOpenMode::E_OPEN,EFileAccessMode::E_READ);
				CByteBuffer										Buffer(100);

				if (File.Read(Buffer,0,Buffer.GetLength())!=5)
				{
					throw(CInvalidOperationException("FILE READ FAILED !"));
				}

				Buffer.Resize(5);

				CByteBuffer										BufferToCompare({0x41,0x42,0x43,0x44,0x45});

				if (Buffer!=BufferToCompare)
				{
					throw(CInvalidOperationException("FILE READ FAILED !"));
				}

				CDateTime										LastAccessTime=File.GetFileLastAccessTime();
				CDateTime::DateTimeTicks						Difference=(LastAccessTime-Time2);

				if (Difference>1000)
				{
					throw(CInvalidOperationException("FILE GET LAST ACCESS TIME FAILED !"));
				}
			}

			bool												FileDeleteSucceeded=false;

			try
			{
				CFile::Delete(Path.GetPath());

				FileDeleteSucceeded=true;
			}
			catch(const CException&)
			{
			}

			if (FileDeleteSucceeded==false)
			{
				throw(CInvalidOperationException("FILE DELETE FAILED !"));
			}
		
			return(true);
		}
		catch(const CException& E)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST FILE OPERATIONS (GET TIME) FAILED with EXCEPTION [",E.GetMessage(),"] !"));

			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST FILE OPERATIONS (GET TIME) FAILED with UNKNOWN EXCEPTION !"));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CFileSystemTest::TestDirectoryOperations(void) const
	{
		try
		{
			CPath												BaseDirectoryPath(".");

			BaseDirectoryPath/="DirectoryTest";

			CDirectory::CreateDirectory(BaseDirectoryPath.GetPath());

			try
			{
				// DIRECTORY ALREADY EXISTS. EXCEPTION must be THROWN.
				CDirectory::CreateDirectory(BaseDirectoryPath.GetPath());

				CConsoleHelper::WriteLine(CString::Format("\tDIRECTORY CREATE FAILED !"));

				return(false);
			}
			catch(const CException&)
			{
			}

			CPath												File1=BaseDirectoryPath/"File1.txt";
			CPath												File2=BaseDirectoryPath/"File2.txt";
			CPath												SubDirectory1=BaseDirectoryPath/"Directory1";
			CPath												SubDirectory2=BaseDirectoryPath/"Directory2";

			{
				CFile											File(File1.GetPath(),EFileOpenMode::E_CREATE,EFileAccessMode::E_WRITE);
				CByteBuffer										Buffer({0x41,0x42,0x43,0x44,0x45});

				if (File.Write(Buffer,0,Buffer.GetLength())!=Buffer.GetLength())
				{
					throw(CInvalidOperationException("FILE WRITE FAILED !"));
				}
			}

			{
				CFile											File(File2.GetPath(),EFileOpenMode::E_CREATE,EFileAccessMode::E_WRITE);
				CByteBuffer										Buffer({0x41,0x42,0x43,0x44,0x45});

				if (File.Write(Buffer,0,Buffer.GetLength())!=Buffer.GetLength())
				{
					throw(CInvalidOperationException("FILE WRITE FAILED !"));
				}
			}

			CDirectory::CreateDirectory(SubDirectory1.GetPath());

			CDirectory::CreateDirectory(SubDirectory2.GetPath());

			CVector<CCSPDirectoryEntry>							DirectoryEntries=CDirectory::GetDirectoryEntries(BaseDirectoryPath.GetPath());

			if (DirectoryEntries.GetLength()!=6)
			{
				throw(CInvalidOperationException("DIRECTORY GET ENTRIES FAILED !"));
			}

			for(CCSPDirectoryEntry DirectoryEntry : DirectoryEntries)
			{
				if (DirectoryEntry->GetEntryName()==".")
				{
					if (DirectoryEntry->GetEntryType()!=EDirectoryEntryType::E_DIRECTORY)
					{
						throw(CInvalidOperationException("DIRECTORY GET ENTRIES FAILED !"));
					}
				}
				else if (DirectoryEntry->GetEntryName()=="..")
				{
					if (DirectoryEntry->GetEntryType()!=EDirectoryEntryType::E_DIRECTORY)
					{
						throw(CInvalidOperationException("DIRECTORY GET ENTRIES FAILED !"));
					}
				}
				else if (DirectoryEntry->GetEntryName()=="Directory1")
				{
					if (DirectoryEntry->GetEntryType()!=EDirectoryEntryType::E_DIRECTORY)
					{
						throw(CInvalidOperationException("DIRECTORY GET ENTRIES FAILED !"));
					}
				}
				else if (DirectoryEntry->GetEntryName()=="Directory2")
				{
					if (DirectoryEntry->GetEntryType()!=EDirectoryEntryType::E_DIRECTORY)
					{
						throw(CInvalidOperationException("DIRECTORY GET ENTRIES FAILED !"));
					}
				}
				else if (DirectoryEntry->GetEntryName()=="File1.txt")
				{
					if (DirectoryEntry->GetEntryType()!=EDirectoryEntryType::E_FILE)
					{
						throw(CInvalidOperationException("DIRECTORY GET ENTRIES FAILED !"));
					}
				}
				else if (DirectoryEntry->GetEntryName()=="File2.txt")
				{
					if (DirectoryEntry->GetEntryType()!=EDirectoryEntryType::E_FILE)
					{
						throw(CInvalidOperationException("DIRECTORY GET ENTRIES FAILED !"));
					}
				}
				else
				{
					throw(CInvalidOperationException("DIRECTORY GET ENTRIES FAILED !"));
				}
			}

			CFile::Delete(File1.GetPath());

			CFile::Delete(File2.GetPath());

			CDirectory::RemoveDirectory(SubDirectory1.GetPath());

			CDirectory::RemoveDirectory(SubDirectory2.GetPath());

			CDirectory::RemoveDirectory(BaseDirectoryPath.GetPath());

			try
			{
				// DIRECTORY doesn't EXIST. EXCEPTION must be THROWN.
				CDirectory::RemoveDirectory(BaseDirectoryPath.GetPath());

				CConsoleHelper::WriteLine(CString::Format("\tDIRECTORY REMOVE FAILED !"));

				return(false);
			}
			catch(const CException&)
			{
			}

			return(true);
		}
		catch(const CException& E)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST DIRECTORY OPERATIONS FAILED with EXCEPTION [",E.GetMessage(),"] !"));

			return(false);
		}
		catch(...)
		{
			CConsoleHelper::WriteLine(CString::Format("\tTEST DIRECTORY OPERATIONS FAILED with UNKNOWN EXCEPTION !"));

			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CFileSystemTest::ExecuteTest(void)
	{
		CVector<CTestMethod<CFileSystemTest>>					Tests;

		Tests.Add(CTestMethod<CFileSystemTest>(this,&CFileSystemTest::TestFilePathWindows));
		Tests.Add(CTestMethod<CFileSystemTest>(this,&CFileSystemTest::TestFilePathLinux));
		Tests.Add(CTestMethod<CFileSystemTest>(this,&CFileSystemTest::TestFileOperationsOpenCloseReadWrite));
		Tests.Add(CTestMethod<CFileSystemTest>(this,&CFileSystemTest::TestFileOperationsSeek));
		Tests.Add(CTestMethod<CFileSystemTest>(this,&CFileSystemTest::TestFileOperationsGetFileSize));
		Tests.Add(CTestMethod<CFileSystemTest>(this,&CFileSystemTest::TestFileOperationsCopyMoveExistsDelete));
		Tests.Add(CTestMethod<CFileSystemTest>(this,&CFileSystemTest::TestFileOperationsReadUntil));
		Tests.Add(CTestMethod<CFileSystemTest>(this,&CFileSystemTest::TestFileOperationsStringInterface));
		Tests.Add(CTestMethod<CFileSystemTest>(this,&CFileSystemTest::TestFileOperationsGetTime));
		Tests.Add(CTestMethod<CFileSystemTest>(this,&CFileSystemTest::TestDirectoryOperations));

		bool													AllTestPassed=true;
		Size													TestNumber=0;
		
		for(CTestMethod<CFileSystemTest>& Method : Tests)
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