//----------------------------------------------------------------------------------------------------------------------
#include "CConsoleLogWriterColorSettings.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CConsoleLogWriterColorSettings::CConsoleLogWriterColorSettings(bool UseLogCategory, const CLogCategory& LogCategory, bool UseLogRecordLevel, ELogRecordLevel LogRecordLevel, const CString& FunctionName, const CString& LogMessageContentFragment, EConsoleColor ForegroundColor, EConsoleColor BackgroundColor, bool Underline)
		: MUseLogCategory(UseLogCategory), MLogCategory(LogCategory), MUseLogRecordLevel(UseLogRecordLevel), MLogRecordLevel(LogRecordLevel), MFunctionName(FunctionName), MLogMessageContentFragment(LogMessageContentFragment), MForegroundColor(ForegroundColor), MBackgroundColor(BackgroundColor), MUnderline(Underline)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CConsoleLogWriterColorSettings::~CConsoleLogWriterColorSettings(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	EConsoleColor CConsoleLogWriterColorSettings::GetForegroundColor(void) const noexcept
	{
		return(MForegroundColor);
	}
//----------------------------------------------------------------------------------------------------------------------
	EConsoleColor CConsoleLogWriterColorSettings::GetBackgroundColor(void) const noexcept
	{
		return(MBackgroundColor);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CConsoleLogWriterColorSettings::GetUnderline(void) const noexcept
	{
		return(MUnderline);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CConsoleLogWriterColorSettings::UseSettings(const CLogCategory& LogCategory, ELogRecordLevel LogLevel, const Char* FunctionName, const CString& LogMessage) const
	{
		if (MUseLogCategory==true)
		{
			if (MLogCategory!=LogCategory)
			{
				return(false);
			}
		}

		if (MUseLogRecordLevel==true)
		{
			if (MLogRecordLevel!=LogLevel)
			{
				return(false);
			}
		}

		if (MFunctionName.IsEmpty()==false)
		{
			if (MFunctionName!=CString(FunctionName))
			{
				return(false);
			}
		}

		if (MLogMessageContentFragment.IsEmpty()==false)
		{
			if (LogMessage.Contains(MLogMessageContentFragment)==false)
			{
				return(false);
			}
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------