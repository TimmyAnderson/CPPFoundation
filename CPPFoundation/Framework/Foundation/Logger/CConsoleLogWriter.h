//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CVector.h>
#include <Framework/Foundation/Console/EConsoleColor.h>
#include "CConsoleLogWriterColorSettings.h"
#include "CLogWriter.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CConsoleLogWriter final : public CLogWriter
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			using												CColorSettingsCollection=CVector<CConsoleLogWriterColorSettings>;

		private:
			const bool											MWriteSource;
			const bool											MWriteCategory;
			const bool											MWriteFunctionName;
			const bool											MWriteLineNumber;
			const bool											MWritePID;
			const bool											MUseColors;
			const CColorSettingsCollection						MColorSettingsCollection;

		private:
			static CColorSettingsCollection CreateColorSettingsCollection(const CColorSettingsCollection& ColorSettingsCollection, EConsoleColor ForegroundColorCriticalLogs, EConsoleColor BackgroundColorCriticalLogs, EConsoleColor ForegroundColorErrorLogs, EConsoleColor BackgroundColorErrorLogs, EConsoleColor ForegroundColorWarningLogs, EConsoleColor BackgroundColorWarningLogs, EConsoleColor ForegroundColorInformationLogs, EConsoleColor BackgroundColorInformationLogs, EConsoleColor ForegroundColorDebugLogs, EConsoleColor BackgroundColorDebugLogs);

		protected:
			virtual void InternalWriteToLog(const CLogCategory& LogCategory, ELogRecordLevel LogLevel, const Char* FunctionName, Size LineNumber, const CLogRecord& LogRecord) override;

		public:
			CConsoleLogWriter(const CLogSource& LogSource, ISPLogFilter LogFilter=ISPLogFilter(), bool WriteSource=false, bool WriteCategory=false, bool WriteFunctionName=false, bool WriteLineNumber=false, bool WritePID=false, bool UseColors=true, EConsoleColor ForegroundColorCriticalLogs=EConsoleColor::E_DARK_BLACK, EConsoleColor BackgroundColorCriticalLogs=EConsoleColor::E_LIGHT_RED, EConsoleColor ForegroundColorErrorLogs=EConsoleColor::E_DARK_BLACK, EConsoleColor BackgroundColorErrorLogs=EConsoleColor::E_LIGHT_RED, EConsoleColor ForegroundColorWarningLogs=EConsoleColor::E_LIGHT_RED, EConsoleColor BackgroundColorWarningLogs=EConsoleColor::E_DEFAULT, EConsoleColor ForegroundColorInformationLogs=EConsoleColor::E_DEFAULT, EConsoleColor BackgroundColorInformationLogs=EConsoleColor::E_DEFAULT, EConsoleColor ForegroundColorDebugLogs=EConsoleColor::E_DEFAULT, EConsoleColor BackgroundColorDebugLogs=EConsoleColor::E_DEFAULT);
			CConsoleLogWriter(const CLogSource& LogSource, const CColorSettingsCollection& ColorSettingsCollection, ISPLogFilter LogFilter=ISPLogFilter(), bool WriteSource=false, bool WriteCategory=false, bool WriteFunctionName=false, bool WriteLineNumber=false, bool WritePID=false, bool UseColors=true, EConsoleColor ForegroundColorCriticalLogs=EConsoleColor::E_DARK_BLACK, EConsoleColor BackgroundColorCriticalLogs=EConsoleColor::E_LIGHT_RED, EConsoleColor ForegroundColorErrorLogs=EConsoleColor::E_DARK_BLACK, EConsoleColor BackgroundColorErrorLogs=EConsoleColor::E_LIGHT_RED, EConsoleColor ForegroundColorWarningLogs=EConsoleColor::E_LIGHT_RED, EConsoleColor BackgroundColorWarningLogs=EConsoleColor::E_DEFAULT, EConsoleColor ForegroundColorInformationLogs=EConsoleColor::E_DEFAULT, EConsoleColor BackgroundColorInformationLogs=EConsoleColor::E_DEFAULT, EConsoleColor ForegroundColorDebugLogs=EConsoleColor::E_DEFAULT, EConsoleColor BackgroundColorDebugLogs=EConsoleColor::E_DEFAULT);
			virtual ~CConsoleLogWriter(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------