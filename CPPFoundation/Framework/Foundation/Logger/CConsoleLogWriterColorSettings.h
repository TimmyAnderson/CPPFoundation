//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Console/EConsoleColor.h>
#include <Framework/Foundation/Strings/CString.h>
#include "CLogCategory.h"
#include "ELogRecordLevel.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CConsoleLogWriterColorSettings final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			bool												MUseLogCategory;
			CLogCategory										MLogCategory;
			bool												MUseLogRecordLevel;
			ELogRecordLevel										MLogRecordLevel;
			CString												MFunctionName;
			CString												MLogMessageContentFragment;
			EConsoleColor										MForegroundColor;
			EConsoleColor										MBackgroundColor;
			bool												MUnderline;

		public:
			EConsoleColor GetForegroundColor(void) const noexcept;
			EConsoleColor GetBackgroundColor(void) const noexcept;
			bool GetUnderline(void) const noexcept;

		public:
			bool UseSettings(const CLogCategory& LogCategory, ELogRecordLevel LogLevel, const Char* FunctionName, const CString& LogMessage) const;

		public:
			CConsoleLogWriterColorSettings(bool UseLogCategory, const CLogCategory& LogCategory, bool UseLogRecordLevel, ELogRecordLevel LogRecordLevel, const CString& FunctionName, const CString& LogMessageContentFragment, EConsoleColor ForegroundColor, EConsoleColor BackgroundColor, bool Underline);
			virtual ~CConsoleLogWriterColorSettings(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------