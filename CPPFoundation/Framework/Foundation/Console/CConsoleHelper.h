//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Strings/CString.h>
#include "EConsoleColor.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	#define MACRO_COLOR_TEXT(Text,ForegroundColor) CConsoleHelper::AddEscapeSequences(Text,ForegroundColor,EConsoleColor::E_DEFAULT,false)
	#define MACRO_COLOR_TEXT_FULL(Text,ForegroundColor,BackgroundColor,Underline) CConsoleHelper::AddEscapeSequences(Text,ForegroundColor,BackgroundColor,Underline)
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	class CConsoleHelper final
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			static const CString								BEGIN_ESCAPE_SEQUENCE;
			static const CString								END_ESCAPE_SEQUENCE;
			static const CString								ESCAPE_SEQUENCE_SEPARATOR;
			static const CString								RESET_ESCAPE_SEQUENCE;

		private:
			static CString CreateEscapeSequence(const CString& Text, EConsoleColor ForegroundColor, EConsoleColor BackgroundColor, bool Underline);

		public:
			static void InitializeConsole(bool EnableAnsiSequences);
			static CString ReadLine(void);
			static void Write(const CString& Text);
			static void Write(const CString& Text, EConsoleColor ForegroundColor, EConsoleColor BackgroundColor, bool Underline);
			static void WriteLine(void);
			static void WriteLine(const CString& Text);
			static void WriteLine(const CString& Text, EConsoleColor ForegroundColor, EConsoleColor BackgroundColor, bool Underline);
			static CString AddEscapeSequences(const CString& Text, EConsoleColor ForegroundColor, EConsoleColor BackgroundColor, bool Underline);
			static void Clear(void);
			static void Flush(void);
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------