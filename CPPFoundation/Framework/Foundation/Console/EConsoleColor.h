//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Strings/CString.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	enum class EConsoleColor : uint8
	{
//----------------------------------------------------------------------------------------------------------------------
		E_DEFAULT=0,
		E_DARK_BLACK=1,
		E_DARK_RED=2,
		E_DARK_GREEN=3,
		E_DARK_YELLOW=4,
		E_DARK_BLUE=5,
		E_DARK_MAGENTA=6,
		E_DARK_CYAN=7,
		E_DARK_WHITE=8,
		E_LIGHT_BLACK=9,
		E_LIGHT_RED=10,
		E_LIGHT_GREEN=11,
		E_LIGHT_YELLOW=12,
		E_LIGHT_BLUE=13,
		E_LIGHT_MAGENTA=14,
		E_LIGHT_CYAN=15,
		E_LIGHT_WHITE=16,
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	inline CString& operator<<(CString& Text, EConsoleColor Value)
	{
		switch(Value)
		{
			case EConsoleColor::E_DEFAULT:
			{
				Text+="DEFAULT"_S;
			}

			case EConsoleColor::E_DARK_BLACK:
			{
				Text+="DARK BLACK"_S;
			}

			case EConsoleColor::E_DARK_RED:
			{
				Text+="DARK RED"_S;
			}

			case EConsoleColor::E_DARK_GREEN:
			{
				Text+="DARK GREEN"_S;
			}

			case EConsoleColor::E_DARK_YELLOW:
			{
				Text+="DARK YELLOW"_S;
			}

			case EConsoleColor::E_DARK_BLUE:
			{
				Text+="DARK BLUE"_S;
			}

			case EConsoleColor::E_DARK_MAGENTA:
			{
				Text+="DARK MAGENTA"_S;
			}

			case EConsoleColor::E_DARK_CYAN:
			{
				Text+="DARK CYAN"_S;
			}

			case EConsoleColor::E_DARK_WHITE:
			{
				Text+="DARK WHITE"_S;
			}


			case EConsoleColor::E_LIGHT_BLACK:
			{
				Text+="LIGHT BLACK"_S;
			}

			case EConsoleColor::E_LIGHT_RED:
			{
				Text+="LIGHT RED"_S;
			}

			case EConsoleColor::E_LIGHT_GREEN:
			{
				Text+="LIGHT GREEN"_S;
			}

			case EConsoleColor::E_LIGHT_YELLOW:
			{
				Text+="LIGHT YELLOW"_S;
			}

			case EConsoleColor::E_LIGHT_BLUE:
			{
				Text+="LIGHT BLUE"_S;
			}

			case EConsoleColor::E_LIGHT_MAGENTA:
			{
				Text+="LIGHT MAGENTA"_S;
			}

			case EConsoleColor::E_LIGHT_CYAN:
			{
				Text+="LIGHT CYAN"_S;
			}

			case EConsoleColor::E_LIGHT_WHITE:
			{
				Text+="LIGHT WHITE"_S;
			}

			default:
			{
				Text+="UNKNOWN"_S;
			}
		}

		return(Text);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	inline bool IsValidValue(EConsoleColor Value)
	{
		switch(Value)
		{
			case EConsoleColor::E_DEFAULT:
			case EConsoleColor::E_DARK_BLACK:
			case EConsoleColor::E_DARK_RED:
			case EConsoleColor::E_DARK_GREEN:
			case EConsoleColor::E_DARK_YELLOW:
			case EConsoleColor::E_DARK_BLUE:
			case EConsoleColor::E_DARK_MAGENTA:
			case EConsoleColor::E_DARK_CYAN:
			case EConsoleColor::E_DARK_WHITE:
			case EConsoleColor::E_LIGHT_BLACK:
			case EConsoleColor::E_LIGHT_RED:
			case EConsoleColor::E_LIGHT_GREEN:
			case EConsoleColor::E_LIGHT_YELLOW:
			case EConsoleColor::E_LIGHT_BLUE:
			case EConsoleColor::E_LIGHT_MAGENTA:
			case EConsoleColor::E_LIGHT_CYAN:
			case EConsoleColor::E_LIGHT_WHITE:
			{
				return(true);
			}

			default:
			{
				return(false);
			}
		}

		return(false);
	}
//----------------------------------------------------------------------------------------------------------------------
	inline uint8 ToForegroundColorCode(EConsoleColor Value)
	{
		switch(Value)
		{
			case EConsoleColor::E_DEFAULT:
			{
				return(39);
			}

			case EConsoleColor::E_DARK_BLACK:
			{
				return(30);
			}

			case EConsoleColor::E_DARK_RED:
			{
				return(31);
			}

			case EConsoleColor::E_DARK_GREEN:
			{
				return(32);
			}

			case EConsoleColor::E_DARK_YELLOW:
			{
				return(33);
			}

			case EConsoleColor::E_DARK_BLUE:
			{
				return(34);
			}

			case EConsoleColor::E_DARK_MAGENTA:
			{
				return(35);
			}

			case EConsoleColor::E_DARK_CYAN:
			{
				return(36);
			}

			case EConsoleColor::E_DARK_WHITE:
			{
				return(37);
			}

			case EConsoleColor::E_LIGHT_BLACK:
			{
				return(90);
			}

			case EConsoleColor::E_LIGHT_RED:
			{
				return(91);
			}

			case EConsoleColor::E_LIGHT_GREEN:
			{
				return(92);
			}

			case EConsoleColor::E_LIGHT_YELLOW:
			{
				return(93);
			}

			case EConsoleColor::E_LIGHT_BLUE:
			{
				return(94);
			}

			case EConsoleColor::E_LIGHT_MAGENTA:
			{
				return(95);
			}

			case EConsoleColor::E_LIGHT_CYAN:
			{
				return(96);
			}

			case EConsoleColor::E_LIGHT_WHITE:
			{
				return(97);
			}

			default:
			{
				return(39);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	inline uint8 ToBackgroundColorCode(EConsoleColor Value)
	{
		switch(Value)
		{
			case EConsoleColor::E_DEFAULT:
			{
				return(49);
			}

			case EConsoleColor::E_DARK_BLACK:
			{
				return(40);
			}

			case EConsoleColor::E_DARK_RED:
			{
				return(41);
			}

			case EConsoleColor::E_DARK_GREEN:
			{
				return(42);
			}

			case EConsoleColor::E_DARK_YELLOW:
			{
				return(43);
			}

			case EConsoleColor::E_DARK_BLUE:
			{
				return(44);
			}

			case EConsoleColor::E_DARK_MAGENTA:
			{
				return(45);
			}

			case EConsoleColor::E_DARK_CYAN:
			{
				return(46);
			}

			case EConsoleColor::E_DARK_WHITE:
			{
				return(47);
			}

			case EConsoleColor::E_LIGHT_BLACK:
			{
				return(100);
			}

			case EConsoleColor::E_LIGHT_RED:
			{
				return(101);
			}

			case EConsoleColor::E_LIGHT_GREEN:
			{
				return(102);
			}

			case EConsoleColor::E_LIGHT_YELLOW:
			{
				return(103);
			}

			case EConsoleColor::E_LIGHT_BLUE:
			{
				return(104);
			}

			case EConsoleColor::E_LIGHT_MAGENTA:
			{
				return(105);
			}

			case EConsoleColor::E_LIGHT_CYAN:
			{
				return(106);
			}

			case EConsoleColor::E_LIGHT_WHITE:
			{
				return(107);
			}

			default:
			{
				return(49);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------