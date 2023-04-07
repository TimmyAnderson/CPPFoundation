//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <Framework/Platform/Global/CConstants.h>
#include <Framework/Platform/Global/CFunctions.h>
#include <Framework/Platform/Global/Macros.h>
#include "CConsoleHelper.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace std;
	using namespace CPPFoundation::Platform;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CString												CConsoleHelper::BEGIN_ESCAPE_SEQUENCE=CString::Format(static_cast<Char>(0x1B),"[");
	const CString												CConsoleHelper::END_ESCAPE_SEQUENCE="m"_S;
	const CString												CConsoleHelper::ESCAPE_SEQUENCE_SEPARATOR=";"_S;
	const CString												CConsoleHelper::RESET_ESCAPE_SEQUENCE=CString::Format(CConsoleHelper::BEGIN_ESCAPE_SEQUENCE,"0",CConsoleHelper::END_ESCAPE_SEQUENCE);
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CConsoleHelper::CreateEscapeSequence(const CString& Text, EConsoleColor ForegroundColor, EConsoleColor BackgroundColor, bool Underline)
	{
		static const CString									UNDERLINE="4";	
		static const CString									NO_UNDERLINE="24";

		if (ForegroundColor==EConsoleColor::E_DEFAULT && BackgroundColor==EConsoleColor::E_DEFAULT && Underline==false)
		{
			return(Text);
		}
		else
		{
			CString												UnderlineEscapeSequence=(Underline==true) ? UNDERLINE : NO_UNDERLINE;
			CString												EscapeSequence=CString::Format(BEGIN_ESCAPE_SEQUENCE,CString(ToForegroundColorCode(ForegroundColor)),ESCAPE_SEQUENCE_SEPARATOR,CString(ToBackgroundColorCode(BackgroundColor)),ESCAPE_SEQUENCE_SEPARATOR,UnderlineEscapeSequence,END_ESCAPE_SEQUENCE,Text,RESET_ESCAPE_SEQUENCE);

			return(EscapeSequence);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CConsoleHelper::InitializeConsole(bool EnableAnsiSequences)
	{
		CFunctions::InitializeConsole(EnableAnsiSequences);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CConsoleHelper::ReadLine(void)
	{
		string													String;

		getline(cin,String);

		return(CString(String));
	}
//----------------------------------------------------------------------------------------------------------------------
	void CConsoleHelper::Write(const CString& Text)
	{
		cout << Text << flush;
	}
//----------------------------------------------------------------------------------------------------------------------
	void CConsoleHelper::Write(const CString& Text, EConsoleColor ForegroundColor, EConsoleColor BackgroundColor, bool Underline)
	{
		CString													TextToWrite=CreateEscapeSequence(Text,ForegroundColor,BackgroundColor,Underline);

		cout << TextToWrite << flush;
	}
//----------------------------------------------------------------------------------------------------------------------
	void CConsoleHelper::WriteLine(void)
	{
		cout << endl;
	}
//----------------------------------------------------------------------------------------------------------------------
	void CConsoleHelper::WriteLine(const CString& Text)
	{
		CString													TextToWrite(Text);

		TextToWrite+=CConstants::END_LINE;

		cout << TextToWrite << flush;
	}
//----------------------------------------------------------------------------------------------------------------------
	void CConsoleHelper::WriteLine(const CString& Text, EConsoleColor ForegroundColor, EConsoleColor BackgroundColor, bool Underline)
	{
		CString													TextToWrite=CreateEscapeSequence(Text,ForegroundColor,BackgroundColor,Underline);

		TextToWrite+=CConstants::END_LINE;

		cout << TextToWrite << flush;
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CConsoleHelper::AddEscapeSequences(const CString& Text, EConsoleColor ForegroundColor, EConsoleColor BackgroundColor, bool Underline)
	{
		CString													TextWithEscapeSequences=CreateEscapeSequence(Text,ForegroundColor,BackgroundColor,Underline);

		return(TextWithEscapeSequences);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CConsoleHelper::Clear(void)
	{
		CFunctions::ClearScreen();
	}
//----------------------------------------------------------------------------------------------------------------------
	void CConsoleHelper::Flush(void)
	{
		cout.flush();
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------