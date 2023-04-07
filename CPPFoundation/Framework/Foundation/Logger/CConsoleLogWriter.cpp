//----------------------------------------------------------------------------------------------------------------------
#include "CConsoleLogWriter.h"
#include <Framework/Foundation/Console/CConsoleHelper.h>
#include <Framework/Platform/Global/CFunctions.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace CPPFoundation::Platform;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CConsoleLogWriter::CConsoleLogWriter(const CLogSource& LogSource, ISPLogFilter LogFilter, bool WriteSource, bool WriteCategory, bool WriteFunctionName, bool WriteLineNumber, bool WritePID, bool UseColors, EConsoleColor ForegroundColorCriticalLogs, EConsoleColor BackgroundColorCriticalLogs, EConsoleColor ForegroundColorErrorLogs, EConsoleColor BackgroundColorErrorLogs, EConsoleColor ForegroundColorWarningLogs, EConsoleColor BackgroundColorWarningLogs, EConsoleColor ForegroundColorInformationLogs, EConsoleColor BackgroundColorInformationLogs, EConsoleColor ForegroundColorDebugLogs, EConsoleColor BackgroundColorDebugLogs)
		: CLogWriter(LogSource,LogFilter), MWriteSource(WriteSource), MWriteCategory(WriteCategory), MWriteFunctionName(WriteFunctionName), MWriteLineNumber(WriteLineNumber), MWritePID(WritePID), MUseColors(UseColors), MColorSettingsCollection(CreateColorSettingsCollection(CColorSettingsCollection(),ForegroundColorCriticalLogs,BackgroundColorCriticalLogs,ForegroundColorErrorLogs,BackgroundColorErrorLogs,ForegroundColorWarningLogs,BackgroundColorWarningLogs,ForegroundColorInformationLogs,BackgroundColorInformationLogs,ForegroundColorDebugLogs,BackgroundColorDebugLogs))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CConsoleLogWriter::CConsoleLogWriter(const CLogSource& LogSource, const CColorSettingsCollection& ColorSettingsCollection, ISPLogFilter LogFilter, bool WriteSource, bool WriteCategory, bool WriteFunctionName, bool WriteLineNumber, bool WritePID, bool UseColors, EConsoleColor ForegroundColorCriticalLogs, EConsoleColor BackgroundColorCriticalLogs, EConsoleColor ForegroundColorErrorLogs, EConsoleColor BackgroundColorErrorLogs, EConsoleColor ForegroundColorWarningLogs, EConsoleColor BackgroundColorWarningLogs, EConsoleColor ForegroundColorInformationLogs, EConsoleColor BackgroundColorInformationLogs, EConsoleColor ForegroundColorDebugLogs, EConsoleColor BackgroundColorDebugLogs)
		: CLogWriter(LogSource,LogFilter), MWriteSource(WriteSource), MWriteCategory(WriteCategory), MWriteFunctionName(WriteFunctionName), MWriteLineNumber(WriteLineNumber), MWritePID(WritePID), MUseColors(UseColors), MColorSettingsCollection(CreateColorSettingsCollection(ColorSettingsCollection,ForegroundColorCriticalLogs,BackgroundColorCriticalLogs,ForegroundColorErrorLogs,BackgroundColorErrorLogs,ForegroundColorWarningLogs,BackgroundColorWarningLogs,ForegroundColorInformationLogs,BackgroundColorInformationLogs,ForegroundColorDebugLogs,BackgroundColorDebugLogs))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CConsoleLogWriter::~CConsoleLogWriter(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CConsoleLogWriter::CColorSettingsCollection CConsoleLogWriter::CreateColorSettingsCollection(const CColorSettingsCollection& ColorSettingsCollection, EConsoleColor ForegroundColorCriticalLogs, EConsoleColor BackgroundColorCriticalLogs, EConsoleColor ForegroundColorErrorLogs, EConsoleColor BackgroundColorErrorLogs, EConsoleColor ForegroundColorWarningLogs, EConsoleColor BackgroundColorWarningLogs, EConsoleColor ForegroundColorInformationLogs, EConsoleColor BackgroundColorInformationLogs, EConsoleColor ForegroundColorDebugLogs, EConsoleColor BackgroundColorDebugLogs)
	{
		CColorSettingsCollection								ExtendedColorSettingsCollection(ColorSettingsCollection);

		ExtendedColorSettingsCollection.Add(CConsoleLogWriterColorSettings(false,CLogCategory(""),true,ELogRecordLevel::E_DEBUG,"","",ForegroundColorDebugLogs,BackgroundColorDebugLogs,false));
		ExtendedColorSettingsCollection.Add(CConsoleLogWriterColorSettings(false,CLogCategory(""),true,ELogRecordLevel::E_INFORMATION,"","",ForegroundColorInformationLogs,BackgroundColorInformationLogs,false));
		ExtendedColorSettingsCollection.Add(CConsoleLogWriterColorSettings(false,CLogCategory(""),true,ELogRecordLevel::E_WARNING,"","",ForegroundColorWarningLogs,BackgroundColorWarningLogs,false));
		ExtendedColorSettingsCollection.Add(CConsoleLogWriterColorSettings(false,CLogCategory(""),true,ELogRecordLevel::E_ERROR,"","",ForegroundColorErrorLogs,BackgroundColorErrorLogs,false));
		ExtendedColorSettingsCollection.Add(CConsoleLogWriterColorSettings(false,CLogCategory(""),true,ELogRecordLevel::E_CRITICAL,"","",ForegroundColorCriticalLogs,BackgroundColorCriticalLogs,false));

		return(ExtendedColorSettingsCollection);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CConsoleLogWriter::InternalWriteToLog(const CLogCategory& LogCategory, ELogRecordLevel LogLevel, const Char* FunctionName, Size LineNumber, const CLogRecord& LogRecord)
	{
		CString													Message;

		CString::FormatString(Message,"DT [",CString(LogRecord.GetLogTime().GetHour(),EIntegerFormat::E_NONE,2,true),":",CString(LogRecord.GetLogTime().GetMinute(),EIntegerFormat::E_NONE,2,true),":",CString(LogRecord.GetLogTime().GetSecond(),EIntegerFormat::E_NONE,2,true),".",CString(LogRecord.GetLogTime().GetMillisecond(),EIntegerFormat::E_NONE,3,true),"]");

		if (MWritePID==true)
		{
			CString::FormatString(Message,", PID [",CFunctions::GetCurrentPID(),"]");
		}

		if (MWriteSource==true)
		{
			CString::FormatString(Message,", S [",GetLogSource().GetSourceType(),"]");
		}

		if (MWriteCategory==true)
		{
			CString::FormatString(Message,", C [",LogCategory.GetCategoryType(),"]");
		}

		CString::FormatString(Message,", LT [",LogLevel,"]");

		if (MWriteFunctionName==true)
		{
			CString::FormatString(Message,", FN [",FunctionName,"]");
		}

		if (MWriteLineNumber==true)
		{
			CString::FormatString(Message,", LN [",LineNumber,"]");
		}

		CString::FormatString(Message,", MSG [",LogRecord.GetLogMessage(),"]");

		if (MUseColors==false)
		{
			Message+="\n";

			CConsoleHelper::Write(Message);
		}
		else
		{
			EConsoleColor										ForegroundColor=EConsoleColor::E_DEFAULT;
			EConsoleColor										BackgroundColor=EConsoleColor::E_DEFAULT;
			bool												Underline=false;

			for(const CConsoleLogWriterColorSettings& ColorSettings : MColorSettingsCollection)
			{
				if (ColorSettings.UseSettings(LogCategory,LogLevel,FunctionName,LogRecord.GetLogMessage())==true)
				{
					ForegroundColor=ColorSettings.GetForegroundColor();
					BackgroundColor=ColorSettings.GetBackgroundColor();
					Underline=ColorSettings.GetUnderline();

					break;
				}
			}

			Message+="\n";

			CConsoleHelper::Write(Message,ForegroundColor,BackgroundColor,Underline);
		}

		CConsoleHelper::Flush();
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------