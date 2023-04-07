//----------------------------------------------------------------------------------------------------------------------
#include "CConsoleMenuItemCommandParams.h"
#include <Framework/Foundation/Exceptions/CValueOutOfRangeException.h>
#include <Framework/Foundation/Strings/CIntegerFormatter.h>
#include <Framework/Foundation/Strings/CFloatFormatter.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	const CString												CConsoleMenuItemCommandParams::HEXADECIMAL_PREFIX="0X";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CConsoleMenuItemCommandParams::CConsoleMenuItemCommandParams(const CString& CommandText)
		: MCommand(), MCommandParams()
	{
		CVector<CString>										Splits=CommandText.Split(" ");
		Size													NumberOfSplits=Splits.GetLength();

		if (NumberOfSplits>0)
		{
			MCommand=CString::ToUpperString(Splits[0]);
			Splits.Erase(0);

			MCommandParams=Splits;
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CConsoleMenuItemCommandParams::CConsoleMenuItemCommandParams(const CConsoleMenuItemCommandParams& Other)
		: MCommand(Other.MCommand), MCommandParams(Other.MCommandParams)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CConsoleMenuItemCommandParams::CConsoleMenuItemCommandParams(CConsoleMenuItemCommandParams&& Other) noexcept
		: MCommand(FUNCTION_MOVE(Other.MCommand)), MCommandParams(FUNCTION_MOVE(Other.MCommandParams))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CConsoleMenuItemCommandParams::~CConsoleMenuItemCommandParams(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CConsoleMenuItemCommandParams::CheckParamIndex(Size Index) const
	{
		Size													CommandParamsLength=MCommandParams.GetLength();

		if (Index>=CommandParamsLength)
		{
			throw(CValueOutOfRangeException(CString::Format("INDEX is OUTSIDE of BOUNDS <0,",(CommandParamsLength-1),"> !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	int8 CConsoleMenuItemCommandParams::GetValueAsInt8(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, int8 DefaultValue, bool AllowHexValues, int8 LowerBound, int8 UpperBound)
	{
		if (RawValue==DefaultValuePlaceholder)
		{
			return(DefaultValue);
		}
		else
		{
			EIntegerFormat										Format;

			if (AllowHexValues==true)
			{
				if (RawValue.StartsWith(HEXADECIMAL_PREFIX)==true)
				{
					Format=EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX;
				}
				else
				{
					Format=EIntegerFormat::E_HEXADECIMAL;
				}
			}
			else
			{
				Format=EIntegerFormat::E_NONE;
			}

			CInt8Formatter										Formatter(Format);
			int8												Value;

			if (Formatter.Parse(RawValue,Value)==false)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE !")));
			}

			if (Value<LowerBound || Value>UpperBound)
			{
				throw(CValueOutOfRangeException(CString::Format("PARAMETER [",ParameterName,"] is OUT OF BOUNDS <",LowerBound,",",UpperBound,"> !")));
			}

			return(Value);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	uint8 CConsoleMenuItemCommandParams::GetValueAsUInt8(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, uint8 DefaultValue, bool AllowHexValues, uint8 LowerBound, uint8 UpperBound)
	{
		if (RawValue==DefaultValuePlaceholder)
		{
			return(DefaultValue);
		}
		else
		{
			EIntegerFormat										Format;

			if (AllowHexValues==true)
			{
				if (RawValue.StartsWith(HEXADECIMAL_PREFIX)==true)
				{
					Format=EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX;
				}
				else
				{
					Format=EIntegerFormat::E_HEXADECIMAL;
				}
			}
			else
			{
				Format=EIntegerFormat::E_NONE;
			}

			CUInt8Formatter										Formatter(Format);
			uint8												Value;

			if (Formatter.Parse(RawValue,Value)==false)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE !")));
			}

			if (Value<LowerBound || Value>UpperBound)
			{
				throw(CValueOutOfRangeException(CString::Format("PARAMETER [",ParameterName,"] is OUT OF BOUNDS <",LowerBound,",",UpperBound,"> !")));
			}

			return(Value);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	int16 CConsoleMenuItemCommandParams::GetValueAsInt16(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, int16 DefaultValue, bool AllowHexValues, int16 LowerBound, int16 UpperBound)
	{
		if (RawValue==DefaultValuePlaceholder)
		{
			return(DefaultValue);
		}
		else
		{
			EIntegerFormat										Format;

			if (AllowHexValues==true)
			{
				if (RawValue.StartsWith(HEXADECIMAL_PREFIX)==true)
				{
					Format=EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX;
				}
				else
				{
					Format=EIntegerFormat::E_HEXADECIMAL;
				}
			}
			else
			{
				Format=EIntegerFormat::E_NONE;
			}

			CInt16Formatter										Formatter(Format);
			int16												Value;

			if (Formatter.Parse(RawValue,Value)==false)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE !")));
			}

			if (Value<LowerBound || Value>UpperBound)
			{
				throw(CValueOutOfRangeException(CString::Format("PARAMETER [",ParameterName,"] is OUT OF BOUNDS <",LowerBound,",",UpperBound,"> !")));
			}

			return(Value);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	uint16 CConsoleMenuItemCommandParams::GetValueAsUInt16(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, uint16 DefaultValue, bool AllowHexValues, uint16 LowerBound, uint16 UpperBound)
	{
		if (RawValue==DefaultValuePlaceholder)
		{
			return(DefaultValue);
		}
		else
		{
			EIntegerFormat										Format;

			if (AllowHexValues==true)
			{
				if (RawValue.StartsWith(HEXADECIMAL_PREFIX)==true)
				{
					Format=EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX;
				}
				else
				{
					Format=EIntegerFormat::E_HEXADECIMAL;
				}
			}
			else
			{
				Format=EIntegerFormat::E_NONE;
			}

			CUInt16Formatter									Formatter(Format);
			uint16												Value;

			if (Formatter.Parse(RawValue,Value)==false)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE !")));
			}

			if (Value<LowerBound || Value>UpperBound)
			{
				throw(CValueOutOfRangeException(CString::Format("PARAMETER [",ParameterName,"] is OUT OF BOUNDS <",LowerBound,",",UpperBound,"> !")));
			}

			return(Value);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CConsoleMenuItemCommandParams::GetValueAsInt32(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, int32 DefaultValue, bool AllowHexValues, int32 LowerBound, int32 UpperBound)
	{
		if (RawValue==DefaultValuePlaceholder)
		{
			return(DefaultValue);
		}
		else
		{
			EIntegerFormat										Format;

			if (AllowHexValues==true)
			{
				if (RawValue.StartsWith(HEXADECIMAL_PREFIX)==true)
				{
					Format=EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX;
				}
				else
				{
					Format=EIntegerFormat::E_HEXADECIMAL;
				}
			}
			else
			{
				Format=EIntegerFormat::E_NONE;
			}

			CInt32Formatter										Formatter(Format);
			int32												Value;

			if (Formatter.Parse(RawValue,Value)==false)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE !")));
			}

			if (Value<LowerBound || Value>UpperBound)
			{
				throw(CValueOutOfRangeException(CString::Format("PARAMETER [",ParameterName,"] is OUT OF BOUNDS <",LowerBound,",",UpperBound,"> !")));
			}

			return(Value);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	uint32 CConsoleMenuItemCommandParams::GetValueAsUInt32(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, uint32 DefaultValue, bool AllowHexValues, uint32 LowerBound, uint32 UpperBound)
	{
		if (RawValue==DefaultValuePlaceholder)
		{
			return(DefaultValue);
		}
		else
		{
			EIntegerFormat										Format;

			if (AllowHexValues==true)
			{
				if (RawValue.StartsWith(HEXADECIMAL_PREFIX)==true)
				{
					Format=EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX;
				}
				else
				{
					Format=EIntegerFormat::E_HEXADECIMAL;
				}
			}
			else
			{
				Format=EIntegerFormat::E_NONE;
			}

			CUInt32Formatter									Formatter(Format);
			uint32												Value;

			if (Formatter.Parse(RawValue,Value)==false)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE !")));
			}

			if (Value<LowerBound || Value>UpperBound)
			{
				throw(CValueOutOfRangeException(CString::Format("PARAMETER [",ParameterName,"] is OUT OF BOUNDS <",LowerBound,",",UpperBound,"> !")));
			}

			return(Value);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	int64 CConsoleMenuItemCommandParams::GetValueAsInt64(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, int64 DefaultValue, bool AllowHexValues, int64 LowerBound, int64 UpperBound)
	{
		if (RawValue==DefaultValuePlaceholder)
		{
			return(DefaultValue);
		}
		else
		{
			EIntegerFormat										Format;

			if (AllowHexValues==true)
			{
				if (RawValue.StartsWith(HEXADECIMAL_PREFIX)==true)
				{
					Format=EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX;
				}
				else
				{
					Format=EIntegerFormat::E_HEXADECIMAL;
				}
			}
			else
			{
				Format=EIntegerFormat::E_NONE;
			}

			CInt64Formatter										Formatter(Format);
			int64												Value;

			if (Formatter.Parse(RawValue,Value)==false)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE !")));
			}

			if (Value<LowerBound || Value>UpperBound)
			{
				throw(CValueOutOfRangeException(CString::Format("PARAMETER [",ParameterName,"] is OUT OF BOUNDS <",LowerBound,",",UpperBound,"> !")));
			}

			return(Value);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	uint64 CConsoleMenuItemCommandParams::GetValueAsUInt64(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, uint64 DefaultValue, bool AllowHexValues, uint64 LowerBound, uint64 UpperBound)
	{
		if (RawValue==DefaultValuePlaceholder)
		{
			return(DefaultValue);
		}
		else
		{
			EIntegerFormat										Format;

			if (AllowHexValues==true)
			{
				if (RawValue.StartsWith(HEXADECIMAL_PREFIX)==true)
				{
					Format=EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX;
				}
				else
				{
					Format=EIntegerFormat::E_HEXADECIMAL;
				}
			}
			else
			{
				Format=EIntegerFormat::E_NONE;
			}

			CUInt64Formatter									Formatter(Format);
			uint64												Value;

			if (Formatter.Parse(RawValue,Value)==false)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE !")));
			}

			if (Value<LowerBound || Value>UpperBound)
			{
				throw(CValueOutOfRangeException(CString::Format("PARAMETER [",ParameterName,"] is OUT OF BOUNDS <",LowerBound,",",UpperBound,"> !")));
			}

			return(Value);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	float32 CConsoleMenuItemCommandParams::GetValueAsFloat32(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, float32 DefaultValue, float32 LowerBound, float32 UpperBound)
	{
		if (RawValue==DefaultValuePlaceholder)
		{
			return(DefaultValue);
		}
		else
		{
			CFloat32Formatter									Formatter;
			float32												Value;

			if (Formatter.Parse(RawValue,Value)==false)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE !")));
			}

			if (Value<LowerBound || Value>UpperBound)
			{
				throw(CValueOutOfRangeException(CString::Format("PARAMETER [",ParameterName,"] is OUT OF BOUNDS <",LowerBound,",",UpperBound,"> !")));
			}

			return(Value);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	float64 CConsoleMenuItemCommandParams::GetValueAsFloat64(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, float64 DefaultValue, float64 LowerBound, float64 UpperBound)
	{
		if (RawValue==DefaultValuePlaceholder)
		{
			return(DefaultValue);
		}
		else
		{
			CFloat64Formatter									Formatter;
			float64												Value;

			if (Formatter.Parse(RawValue,Value)==false)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE !")));
			}

			if (Value<LowerBound || Value>UpperBound)
			{
				throw(CValueOutOfRangeException(CString::Format("PARAMETER [",ParameterName,"] is OUT OF BOUNDS <",LowerBound,",",UpperBound,"> !")));
			}

			return(Value);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	float80 CConsoleMenuItemCommandParams::GetValueAsFloat80(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, float80 DefaultValue, float80 LowerBound, float80 UpperBound)
	{
		if (RawValue==DefaultValuePlaceholder)
		{
			return(DefaultValue);
		}
		else
		{
			CFloat80Formatter									Formatter;
			float80												Value;

			if (Formatter.Parse(RawValue,Value)==false)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE !")));
			}

			if (Value<LowerBound || Value>UpperBound)
			{
				throw(CValueOutOfRangeException(CString::Format("PARAMETER [",ParameterName,"] is OUT OF BOUNDS <",LowerBound,",",UpperBound,"> !")));
			}

			return(Value);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CConsoleMenuItemCommandParams::GetValueAsSize(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, Size DefaultValue, bool AllowHexValues, Size LowerBound, Size UpperBound)
	{
		if (RawValue==DefaultValuePlaceholder)
		{
			return(DefaultValue);
		}
		else
		{
			EIntegerFormat										Format;

			if (AllowHexValues==true)
			{
				if (RawValue.StartsWith(HEXADECIMAL_PREFIX)==true)
				{
					Format=EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX;
				}
				else
				{
					Format=EIntegerFormat::E_HEXADECIMAL;
				}
			}
			else
			{
				Format=EIntegerFormat::E_NONE;
			}

			CSizeFormatter										Formatter(Format);
			Size												Value;

			if (Formatter.Parse(RawValue,Value)==false)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE !")));
			}

			if (Value<LowerBound || Value>UpperBound)
			{
				throw(CValueOutOfRangeException(CString::Format("PARAMETER [",ParameterName,"] is OUT OF BOUNDS <",LowerBound,",",UpperBound,"> !")));
			}

			return(Value);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CConsoleMenuItemCommandParams::GetValueAsString(const CString& RawValue, const CString& DefaultValuePlaceholder, const CString& DefaultValue)
	{
		if (RawValue==DefaultValuePlaceholder)
		{
			return(DefaultValue);
		}
		else
		{
			CString												ParamValue=RawValue;

			return(ParamValue);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	// SUPPORTED FORMAT: [DAY-MONTH-YEAR_HOUR:MINUTE:SECOND.MILLISECOND].
	CDateTime CConsoleMenuItemCommandParams::GetValueAsDateTime(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CDateTime& DefaultValue, const CDateTime& LowerBound, const CDateTime& UpperBound)
	{
		static const CString									SEPARATOR_DAY_MONTH="-";
		static const CString									SEPARATOR_MONTH_YEAR="-";
		static const CString									SEPARATOR_YEAR_HOUR="_";
		static const CString									SEPARATOR_HOUR_MINUTE=":";
		static const CString									SEPARATOR_MINUTE_SECOND=":";
		static const CString									SEPARATOR_SECOND_MILLISECOND=".";
		static const Size										SEPARATOR_SIZE_DAY_MONTH=SEPARATOR_DAY_MONTH.GetLength();
		static const Size										SEPARATOR_SIZE_MONTH_YEAR=SEPARATOR_MONTH_YEAR.GetLength();
		static const Size										SEPARATOR_SIZE_YEAR_HOUR=SEPARATOR_YEAR_HOUR.GetLength();
		static const Size										SEPARATOR_SIZE_HOUR_MINUTE=SEPARATOR_HOUR_MINUTE.GetLength();
		static const Size										SEPARATOR_SIZE_MINUTE_SECOND=SEPARATOR_MINUTE_SECOND.GetLength();
		static const Size										SEPARATOR_SIZE_SECOND_MILLISECOND=SEPARATOR_SECOND_MILLISECOND.GetLength();

		if (RawValue==DefaultValuePlaceholder)
		{
			return(DefaultValue);
		}
		else
		{
			CInt32Formatter										Formatter(EIntegerFormat::E_NONE);
			int32												Year=CDateTime::GetMin().GetYear();
			int32												Month=CDateTime::GetMin().GetMonth();
			int32												Day=CDateTime::GetMin().GetDay();
			int32												Hour=CDateTime::GetMin().GetHour();
			int32												Minute=CDateTime::GetMin().GetMinute();
			int32												Second=CDateTime::GetMin().GetSecond();
			int32												Millisecond=CDateTime::GetMin().GetMillisecond();
			Size												BeginOffset=0;
			Size												EndOffset=0;

			if ((EndOffset=RawValue.FindFirst(SEPARATOR_DAY_MONTH,BeginOffset))==CString::END)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE ! EXPECTED FORMAT is [DAY-MONTH-YEAR_HOUR:MINUTE:SECOND.MILLISECOND] !")));
			}

			if (Formatter.Parse(RawValue,BeginOffset,EndOffset,Day)==false)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE ! EXPECTED FORMAT is [DAY-MONTH-YEAR_HOUR:MINUTE:SECOND.MILLISECOND] !")));
			}

			BeginOffset=EndOffset+SEPARATOR_SIZE_DAY_MONTH;

			if ((EndOffset=RawValue.FindFirst(SEPARATOR_MONTH_YEAR,BeginOffset))==CString::END)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE ! EXPECTED FORMAT is [DAY-MONTH-YEAR_HOUR:MINUTE:SECOND.MILLISECOND] !")));
			}

			if (Formatter.Parse(RawValue,BeginOffset,EndOffset,Month)==false)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE ! EXPECTED FORMAT is [DAY-MONTH-YEAR_HOUR:MINUTE:SECOND.MILLISECOND] !")));
			}

			BeginOffset=EndOffset+SEPARATOR_SIZE_MONTH_YEAR;

			if ((EndOffset=RawValue.FindFirst(SEPARATOR_YEAR_HOUR,BeginOffset))==CString::END)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE ! EXPECTED FORMAT is [DAY-MONTH-YEAR_HOUR:MINUTE:SECOND.MILLISECOND] !")));
			}

			if (Formatter.Parse(RawValue,BeginOffset,EndOffset,Year)==false)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE ! EXPECTED FORMAT is [DAY-MONTH-YEAR_HOUR:MINUTE:SECOND.MILLISECOND] !")));
			}

			BeginOffset=EndOffset+SEPARATOR_SIZE_YEAR_HOUR;

			if ((EndOffset=RawValue.FindFirst(SEPARATOR_HOUR_MINUTE,BeginOffset))==CString::END)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE ! EXPECTED FORMAT is [DAY-MONTH-YEAR_HOUR:MINUTE:SECOND.MILLISECOND] !")));
			}

			if (Formatter.Parse(RawValue,BeginOffset,EndOffset,Hour)==false)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE ! EXPECTED FORMAT is [DAY-MONTH-YEAR_HOUR:MINUTE:SECOND.MILLISECOND] !")));
			}

			BeginOffset=EndOffset+SEPARATOR_SIZE_HOUR_MINUTE;

			if ((EndOffset=RawValue.FindFirst(SEPARATOR_MINUTE_SECOND,BeginOffset))==CString::END)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE ! EXPECTED FORMAT is [DAY-MONTH-YEAR_HOUR:MINUTE:SECOND.MILLISECOND] !")));
			}

			if (Formatter.Parse(RawValue,BeginOffset,EndOffset,Minute)==false)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE ! EXPECTED FORMAT is [DAY-MONTH-YEAR_HOUR:MINUTE:SECOND.MILLISECOND] !")));
			}

			BeginOffset=EndOffset+SEPARATOR_SIZE_MINUTE_SECOND;

			if ((EndOffset=RawValue.FindFirst(SEPARATOR_SECOND_MILLISECOND,BeginOffset))==CString::END)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE ! EXPECTED FORMAT is [DAY-MONTH-YEAR_HOUR:MINUTE:SECOND.MILLISECOND] !")));
			}

			if (Formatter.Parse(RawValue,BeginOffset,EndOffset,Second)==false)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE ! EXPECTED FORMAT is [DAY-MONTH-YEAR_HOUR:MINUTE:SECOND.MILLISECOND] !")));
			}

			BeginOffset=EndOffset+SEPARATOR_SIZE_SECOND_MILLISECOND;
			EndOffset=RawValue.GetLength();

			if (Formatter.Parse(RawValue,BeginOffset,EndOffset,Millisecond)==false)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE ! EXPECTED FORMAT is [DAY-MONTH-YEAR_HOUR:MINUTE:SECOND.MILLISECOND] !")));
			}

			if (CDateTime::IsValidDay(Day,Month,Year)==false)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE ! EXPECTED FORMAT is [DAY-MONTH-YEAR_HOUR:MINUTE:SECOND.MILLISECOND] !")));
			}

			if (CDateTime::IsValidMonth(Month)==false)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE ! EXPECTED FORMAT is [DAY-MONTH-YEAR_HOUR:MINUTE:SECOND.MILLISECOND] !")));
			}

			if (CDateTime::IsValidYear(Year)==false)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE ! EXPECTED FORMAT is [DAY-MONTH-YEAR_HOUR:MINUTE:SECOND.MILLISECOND] !")));
			}

			if (CDateTime::IsValidHour(Hour)==false)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE ! EXPECTED FORMAT is [DAY-MONTH-YEAR_HOUR:MINUTE:SECOND.MILLISECOND] !")));
			}

			if (CDateTime::IsValidMinute(Minute)==false)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE ! EXPECTED FORMAT is [DAY-MONTH-YEAR_HOUR:MINUTE:SECOND.MILLISECOND] !")));
			}

			if (CDateTime::IsValidSecond(Second)==false)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE ! EXPECTED FORMAT is [DAY-MONTH-YEAR_HOUR:MINUTE:SECOND.MILLISECOND] !")));
			}

			if (CDateTime::IsValidMillisecond(Millisecond)==false)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE ! EXPECTED FORMAT is [DAY-MONTH-YEAR_HOUR:MINUTE:SECOND.MILLISECOND] !")));
			}

			CDateTime											Value(Year,Month,Day,Hour,Minute,Second,Millisecond);

			if (Value<LowerBound || Value>UpperBound)
			{
				throw(CValueOutOfRangeException(CString::Format("PARAMETER [",ParameterName,"] is OUT OF BOUNDS <",LowerBound,",",UpperBound,"> !")));
			}

			return(Value);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPAddress CConsoleMenuItemCommandParams::GetValueAsIPv4Address(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketIPAddress& DefaultValue)
	{
		if (RawValue==DefaultValuePlaceholder)
		{
			return(DefaultValue);
		}
		else
		{
			CSocketIPAddress									Value;

			if (CSocketIPAddress::ParseIPv4Address(RawValue,Value)==false)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE !")));
			}

			return(Value);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPEndpoint CConsoleMenuItemCommandParams::GetValueAsIPv4Endpoint(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketIPEndpoint& DefaultValue)
	{
		if (RawValue==DefaultValuePlaceholder)
		{
			return(DefaultValue);
		}
		else
		{
			CSocketIPEndpoint									Value;

			if (CSocketIPEndpoint::ParseIPv4Endpoint(RawValue,Value)==false)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE !")));
			}

			return(Value);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPAddress CConsoleMenuItemCommandParams::GetValueAsIPv6Address(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketIPAddress& DefaultValue)
	{
		if (RawValue==DefaultValuePlaceholder)
		{
			return(DefaultValue);
		}
		else
		{
			CSocketIPAddress									Value;

			if (CSocketIPAddress::ParseIPv6Address(RawValue,Value)==false)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE !")));
			}

			return(Value);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPEndpoint CConsoleMenuItemCommandParams::GetValueAsIPv6Endpoint(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketIPEndpoint& DefaultValue)
	{
		if (RawValue==DefaultValuePlaceholder)
		{
			return(DefaultValue);
		}
		else
		{
			CSocketIPEndpoint									Value;

			if (CSocketIPEndpoint::ParseIPv6Endpoint(RawValue,Value)==false)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE !")));
			}

			return(Value);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSAddress CConsoleMenuItemCommandParams::GetValueAsDNSAddress(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketDNSAddress& DefaultValue)
	{
		if (RawValue==DefaultValuePlaceholder)
		{
			return(DefaultValue);
		}
		else
		{
			CSocketDNSAddress									Value;

			if (CSocketDNSAddress::ParseDNSAddress(RawValue,Value)==false)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE !")));
			}

			return(Value);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSEndpoint CConsoleMenuItemCommandParams::GetValueAsDNSEndpoint(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketDNSEndpoint& DefaultValue)
	{
		if (RawValue==DefaultValuePlaceholder)
		{
			return(DefaultValue);
		}
		else
		{
			CSocketDNSEndpoint									Value;

			if (CSocketDNSEndpoint::ParseDNSEndpoint(RawValue,Value)==false)
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE !")));
			}

			return(Value);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CConsoleMenuItemCommandParams::GetValueAsBool(const CString& RawValue, const CString& ParameterName, const CString& DefaultValuePlaceholder, bool DefaultValue)
	{
		if (RawValue==DefaultValuePlaceholder)
		{
			return(DefaultValue);
		}
		else
		{
			int32												Value=GetValueAsUInt32(RawValue,ParameterName,"",0,false,CUInt32::Min(),CUInt32::Max());

			if (Value!=0)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CString& CConsoleMenuItemCommandParams::GetCommand(void) const noexcept
	{
		return(MCommand);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CVector<CString>& CConsoleMenuItemCommandParams::GetCommandParams(void) const noexcept
	{
		return(MCommandParams);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CConsoleMenuItemCommandParams::GetNumberOfParams(void) const noexcept
	{
		return(MCommandParams.GetLength());
	}
//----------------------------------------------------------------------------------------------------------------------
	void CConsoleMenuItemCommandParams::CheckNumberOfParams(Size NumberOfParams) const
	{
		Size													CommandParamsLength=MCommandParams.GetLength();

		if (NumberOfParams>CommandParamsLength)
		{
			throw(CValueOutOfRangeException(CString::Format("NOT ENOUGH COMMAND PARAMETERS ! COMMAND has just [",CommandParamsLength,"] PARAMETERS but [",NumberOfParams,"] COMMANDS EXPECTED !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	int8 CConsoleMenuItemCommandParams::GetParamAsInt8(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, int8 DefaultValue, bool AllowHexValues, int8 LowerBound, int8 UpperBound) const
	{
		CheckParamIndex(Index);
		
		int8													Value=GetValueAsInt8(CString::ToUpperString(MCommandParams[Index]),ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	uint8 CConsoleMenuItemCommandParams::GetParamAsUInt8(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, uint8 DefaultValue, bool AllowHexValues, uint8 LowerBound, uint8 UpperBound) const
	{
		CheckParamIndex(Index);
		
		uint8													Value=GetValueAsUInt8(CString::ToUpperString(MCommandParams[Index]),ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	int16 CConsoleMenuItemCommandParams::GetParamAsInt16(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, int16 DefaultValue, bool AllowHexValues, int16 LowerBound, int16 UpperBound) const
	{
		CheckParamIndex(Index);
		
		int16													Value=GetValueAsInt16(CString::ToUpperString(MCommandParams[Index]),ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	uint16 CConsoleMenuItemCommandParams::GetParamAsUInt16(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, uint16 DefaultValue, bool AllowHexValues, uint16 LowerBound, uint16 UpperBound) const
	{
		CheckParamIndex(Index);
		
		uint16													Value=GetValueAsUInt16(CString::ToUpperString(MCommandParams[Index]),ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CConsoleMenuItemCommandParams::GetParamAsInt32(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, int32 DefaultValue, bool AllowHexValues, int32 LowerBound, int32 UpperBound) const
	{
		CheckParamIndex(Index);
		
		int32													Value=GetValueAsInt32(CString::ToUpperString(MCommandParams[Index]),ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	uint32 CConsoleMenuItemCommandParams::GetParamAsUInt32(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, uint32 DefaultValue, bool AllowHexValues, uint32 LowerBound, uint32 UpperBound) const
	{
		CheckParamIndex(Index);
		
		uint32													Value=GetValueAsUInt32(CString::ToUpperString(MCommandParams[Index]),ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	int64 CConsoleMenuItemCommandParams::GetParamAsInt64(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, int64 DefaultValue, bool AllowHexValues, int64 LowerBound, int64 UpperBound) const
	{
		CheckParamIndex(Index);
		
		int64													Value=GetValueAsInt64(CString::ToUpperString(MCommandParams[Index]),ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	uint64 CConsoleMenuItemCommandParams::GetParamAsUInt64(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, uint64 DefaultValue, bool AllowHexValues, uint64 LowerBound, uint64 UpperBound) const
	{
		CheckParamIndex(Index);
		
		uint64													Value=GetValueAsUInt64(CString::ToUpperString(MCommandParams[Index]),ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	float32 CConsoleMenuItemCommandParams::GetParamAsFloat32(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, float32 DefaultValue, float32 LowerBound, float32 UpperBound) const
	{
		CheckParamIndex(Index);

		float32													Value=GetValueAsFloat32(CString::ToUpperString(MCommandParams[Index]),ParameterName,DefaultValuePlaceholder,DefaultValue,LowerBound,UpperBound);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	float64 CConsoleMenuItemCommandParams::GetParamAsFloat64(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, float64 DefaultValue, float64 LowerBound, float64 UpperBound) const
	{
		CheckParamIndex(Index);

		float64													Value=GetValueAsFloat64(CString::ToUpperString(MCommandParams[Index]),ParameterName,DefaultValuePlaceholder,DefaultValue,LowerBound,UpperBound);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	float80 CConsoleMenuItemCommandParams::GetParamAsFloat80(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, float80 DefaultValue, float80 LowerBound, float80 UpperBound) const
	{
		CheckParamIndex(Index);

		float80													Value=GetValueAsFloat80(CString::ToUpperString(MCommandParams[Index]),ParameterName,DefaultValuePlaceholder,DefaultValue,LowerBound,UpperBound);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CConsoleMenuItemCommandParams::GetParamAsSize(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, Size DefaultValue, bool AllowHexValues, Size LowerBound, Size UpperBound) const
	{
		CheckParamIndex(Index);
		
		Size													Value=GetValueAsSize(CString::ToUpperString(MCommandParams[Index]),ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CConsoleMenuItemCommandParams::GetParamAsString(Size Index, const CString& DefaultValuePlaceholder, const CString& DefaultValue) const
	{
		CheckParamIndex(Index);

		CString													ParamValue=GetValueAsString(MCommandParams[Index],DefaultValuePlaceholder,DefaultValue);

		return(ParamValue);
	}
//----------------------------------------------------------------------------------------------------------------------
	CDateTime CConsoleMenuItemCommandParams::GetParamAsDateTime(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CDateTime& DefaultValue, const CDateTime& LowerBound, const CDateTime& UpperBound) const
	{
		CheckParamIndex(Index);

		CDateTime												Value=GetValueAsDateTime(CString::ToUpperString(MCommandParams[Index]),ParameterName,DefaultValuePlaceholder,DefaultValue,LowerBound,UpperBound);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPAddress CConsoleMenuItemCommandParams::GetParamAsIPv4Address(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketIPAddress& DefaultValue) const
	{
		CheckParamIndex(Index);

		CSocketIPAddress										Value=GetValueAsIPv4Address(MCommandParams[Index],ParameterName,DefaultValuePlaceholder,DefaultValue);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPEndpoint CConsoleMenuItemCommandParams::GetParamAsIPv4Endpoint(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketIPEndpoint& DefaultValue) const
	{
		CheckParamIndex(Index);

		CSocketIPEndpoint										Value=GetValueAsIPv4Endpoint(MCommandParams[Index],ParameterName,DefaultValuePlaceholder,DefaultValue);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPAddress CConsoleMenuItemCommandParams::GetParamAsIPv6Address(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketIPAddress& DefaultValue) const
	{
		CheckParamIndex(Index);

		CSocketIPAddress										Value=GetValueAsIPv6Address(MCommandParams[Index],ParameterName,DefaultValuePlaceholder,DefaultValue);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketIPEndpoint CConsoleMenuItemCommandParams::GetParamAsIPv6Endpoint(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketIPEndpoint& DefaultValue) const
	{
		CheckParamIndex(Index);

		CSocketIPEndpoint										Value=GetValueAsIPv6Endpoint(MCommandParams[Index],ParameterName,DefaultValuePlaceholder,DefaultValue);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSAddress CConsoleMenuItemCommandParams::GetParamAsDNSAddress(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketDNSAddress& DefaultValue) const
	{
		CheckParamIndex(Index);

		CSocketDNSAddress										Value=GetValueAsDNSAddress(MCommandParams[Index],ParameterName,DefaultValuePlaceholder,DefaultValue);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketDNSEndpoint CConsoleMenuItemCommandParams::GetParamAsDNSEndpoint(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketDNSEndpoint& DefaultValue) const
	{
		CheckParamIndex(Index);

		CSocketDNSEndpoint										Value=GetValueAsDNSEndpoint(MCommandParams[Index],ParameterName,DefaultValuePlaceholder,DefaultValue);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CConsoleMenuItemCommandParams::GetParamAsBool(Size Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, bool DefaultValue) const
	{
		CheckParamIndex(Index);

		bool													Value=GetValueAsBool(MCommandParams[Index],ParameterName,DefaultValuePlaceholder,DefaultValue);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CVector<int8> CConsoleMenuItemCommandParams::GetSeparatedParamsAsInt8(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, int8 DefaultValue, bool AllowHexValues, int8 LowerBound, int8 UpperBound) const
	{
		CheckParamIndex(Index);
		
		CString													RawParamValue=CString::ToUpperString(MCommandParams[Index]);
		CVector<CString>										ParamValues=RawParamValue.Split(Separator);
		CVector<int8>											Values;

		Values.ReserveCapacity(ParamValues.GetLength());

		for(const CString& ParamValue : ParamValues)
		{
			int8												Value=GetValueAsInt8(ParamValue,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound);

			Values.Add(Value);
		}

		return(Values);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<uint8> CConsoleMenuItemCommandParams::GetSeparatedParamsAsUInt8(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, uint8 DefaultValue, bool AllowHexValues, uint8 LowerBound, uint8 UpperBound) const
	{
		CheckParamIndex(Index);
		
		CString													RawParamValue=CString::ToUpperString(MCommandParams[Index]);
		CVector<CString>										ParamValues=RawParamValue.Split(Separator);
		CVector<uint8>											Values;

		Values.ReserveCapacity(ParamValues.GetLength());

		for(const CString& ParamValue : ParamValues)
		{
			uint8												Value=GetValueAsUInt8(ParamValue,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound);

			Values.Add(Value);
		}

		return(Values);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<int16> CConsoleMenuItemCommandParams::GetSeparatedParamsAsInt16(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, int16 DefaultValue, bool AllowHexValues, int16 LowerBound, int16 UpperBound) const
	{
		CheckParamIndex(Index);
		
		CString													RawParamValue=CString::ToUpperString(MCommandParams[Index]);
		CVector<CString>										ParamValues=RawParamValue.Split(Separator);
		CVector<int16>											Values;

		Values.ReserveCapacity(ParamValues.GetLength());

		for(const CString& ParamValue : ParamValues)
		{
			int16												Value=GetValueAsInt16(ParamValue,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound);

			Values.Add(Value);
		}

		return(Values);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<uint16> CConsoleMenuItemCommandParams::GetSeparatedParamsAsUInt16(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, uint16 DefaultValue, bool AllowHexValues, uint16 LowerBound, uint16 UpperBound) const
	{
		CheckParamIndex(Index);
		
		CString													RawParamValue=CString::ToUpperString(MCommandParams[Index]);
		CVector<CString>										ParamValues=RawParamValue.Split(Separator);
		CVector<uint16>											Values;

		Values.ReserveCapacity(ParamValues.GetLength());

		for(const CString& ParamValue : ParamValues)
		{
			uint16												Value=GetValueAsUInt16(ParamValue,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound);

			Values.Add(Value);
		}

		return(Values);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<int32> CConsoleMenuItemCommandParams::GetSeparatedParamsAsInt32(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, int32 DefaultValue, bool AllowHexValues, int32 LowerBound, int32 UpperBound) const
	{
		CheckParamIndex(Index);
		
		CString													RawParamValue=CString::ToUpperString(MCommandParams[Index]);
		CVector<CString>										ParamValues=RawParamValue.Split(Separator);
		CVector<int32>											Values;

		Values.ReserveCapacity(ParamValues.GetLength());

		for(const CString& ParamValue : ParamValues)
		{
			int32												Value=GetValueAsInt32(ParamValue,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound);

			Values.Add(Value);
		}

		return(Values);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<uint32> CConsoleMenuItemCommandParams::GetSeparatedParamsAsUInt32(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, uint32 DefaultValue, bool AllowHexValues, uint32 LowerBound, uint32 UpperBound) const
	{
		CheckParamIndex(Index);
		
		CString													RawParamValue=CString::ToUpperString(MCommandParams[Index]);
		CVector<CString>										ParamValues=RawParamValue.Split(Separator);
		CVector<uint32>											Values;

		Values.ReserveCapacity(ParamValues.GetLength());

		for(const CString& ParamValue : ParamValues)
		{
			uint32												Value=GetValueAsUInt32(ParamValue,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound);

			Values.Add(Value);
		}

		return(Values);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<int64> CConsoleMenuItemCommandParams::GetSeparatedParamsAsInt64(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, int64 DefaultValue, bool AllowHexValues, int64 LowerBound, int64 UpperBound) const
	{
		CheckParamIndex(Index);
		
		CString													RawParamValue=CString::ToUpperString(MCommandParams[Index]);
		CVector<CString>										ParamValues=RawParamValue.Split(Separator);
		CVector<int64>											Values;

		Values.ReserveCapacity(ParamValues.GetLength());

		for(const CString& ParamValue : ParamValues)
		{
			int64												Value=GetValueAsInt64(ParamValue,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound);

			Values.Add(Value);
		}

		return(Values);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<uint64> CConsoleMenuItemCommandParams::GetSeparatedParamsAsUInt64(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, uint64 DefaultValue, bool AllowHexValues, uint64 LowerBound, uint64 UpperBound) const
	{
		CheckParamIndex(Index);
		
		CString													RawParamValue=CString::ToUpperString(MCommandParams[Index]);
		CVector<CString>										ParamValues=RawParamValue.Split(Separator);
		CVector<uint64>											Values;

		Values.ReserveCapacity(ParamValues.GetLength());

		for(const CString& ParamValue : ParamValues)
		{
			uint64												Value=GetValueAsUInt64(ParamValue,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound);

			Values.Add(Value);
		}

		return(Values);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<float32> CConsoleMenuItemCommandParams::GetSeparatedParamsAsFloat32(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, float32 DefaultValue, float32 LowerBound, float32 UpperBound) const
	{
		CheckParamIndex(Index);

		CString													RawParamValue=CString::ToUpperString(MCommandParams[Index]);
		CVector<CString>										ParamValues=RawParamValue.Split(Separator);
		CVector<float32>										Values;

		Values.ReserveCapacity(ParamValues.GetLength());

		for(const CString& ParamValue : ParamValues)
		{
			float32												Value=GetValueAsFloat32(ParamValue,ParameterName,DefaultValuePlaceholder,DefaultValue,LowerBound,UpperBound);

			Values.Add(Value);
		}

		return(Values);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<float64> CConsoleMenuItemCommandParams::GetSeparatedParamsAsFloat64(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, float64 DefaultValue, float64 LowerBound, float64 UpperBound) const
	{
		CheckParamIndex(Index);

		CString													RawParamValue=CString::ToUpperString(MCommandParams[Index]);
		CVector<CString>										ParamValues=RawParamValue.Split(Separator);
		CVector<float64>										Values;

		Values.ReserveCapacity(ParamValues.GetLength());

		for(const CString& ParamValue : ParamValues)
		{
			float64												Value=GetValueAsFloat64(ParamValue,ParameterName,DefaultValuePlaceholder,DefaultValue,LowerBound,UpperBound);

			Values.Add(Value);
		}

		return(Values);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<float80> CConsoleMenuItemCommandParams::GetSeparatedParamsAsFloat80(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, float80 DefaultValue, float80 LowerBound, float80 UpperBound) const
	{
		CheckParamIndex(Index);

		CString													RawParamValue=CString::ToUpperString(MCommandParams[Index]);
		CVector<CString>										ParamValues=RawParamValue.Split(Separator);
		CVector<float80>										Values;

		Values.ReserveCapacity(ParamValues.GetLength());

		for(const CString& ParamValue : ParamValues)
		{
			float80												Value=GetValueAsFloat80(ParamValue,ParameterName,DefaultValuePlaceholder,DefaultValue,LowerBound,UpperBound);

			Values.Add(Value);
		}

		return(Values);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<Size> CConsoleMenuItemCommandParams::GetSeparatedParamsAsSize(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, Size DefaultValue, bool AllowHexValues, Size LowerBound, Size UpperBound) const
	{
		CheckParamIndex(Index);
		
		CString													RawParamValue=CString::ToUpperString(MCommandParams[Index]);
		CVector<CString>										ParamValues=RawParamValue.Split(Separator);
		CVector<Size>											Values;

		Values.ReserveCapacity(ParamValues.GetLength());

		for(const CString& ParamValue : ParamValues)
		{
			Size												Value=GetValueAsSize(ParamValue,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound);

			Values.Add(Value);
		}

		return(Values);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CString> CConsoleMenuItemCommandParams::GetSeparatedParamsAsString(Size Index, const CString& Separator, const CString& DefaultValuePlaceholder, const CString& DefaultValue) const
	{
		CheckParamIndex(Index);

		CString													RawParamValue=CString::ToUpperString(MCommandParams[Index]);
		CVector<CString>										ParamValues=RawParamValue.Split(Separator);
		CVector<CString>										Values;

		Values.ReserveCapacity(ParamValues.GetLength());

		for(const CString& ParamValue : ParamValues)
		{
			CString												Value=GetValueAsString(ParamValue,DefaultValuePlaceholder,DefaultValue);

			Values.Add(Value);
		}

		return(Values);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CDateTime> CConsoleMenuItemCommandParams::GetSeparatedParamsAsDateTime(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, const CDateTime& DefaultValue, const CDateTime& LowerBound, const CDateTime& UpperBound) const
	{
		CheckParamIndex(Index);

		CString													RawParamValue=CString::ToUpperString(MCommandParams[Index]);
		CVector<CString>										ParamValues=RawParamValue.Split(Separator);
		CVector<CDateTime>										Values;

		Values.ReserveCapacity(ParamValues.GetLength());

		for(const CString& ParamValue : ParamValues)
		{
			CDateTime											Value=GetValueAsDateTime(ParamValue,ParameterName,DefaultValuePlaceholder,DefaultValue,LowerBound,UpperBound);

			Values.Add(Value);
		}

		return(Values);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketIPAddress> CConsoleMenuItemCommandParams::GetSeparatedParamsAsIPv4Address(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, const CSocketIPAddress& DefaultValue) const
	{
		CheckParamIndex(Index);

		CString													RawParamValue=CString::ToUpperString(MCommandParams[Index]);
		CVector<CString>										ParamValues=RawParamValue.Split(Separator);
		CVector<CSocketIPAddress>								Values;

		Values.ReserveCapacity(ParamValues.GetLength());

		for(const CString& ParamValue : ParamValues)
		{
			CSocketIPAddress									Value=GetValueAsIPv4Address(ParamValue,ParameterName,DefaultValuePlaceholder,DefaultValue);

			Values.Add(Value);
		}

		return(Values);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketIPEndpoint> CConsoleMenuItemCommandParams::GetSeparatedParamsAsIPv4Endpoint(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, const CSocketIPEndpoint& DefaultValue) const
	{
		CheckParamIndex(Index);

		CString													RawParamValue=CString::ToUpperString(MCommandParams[Index]);
		CVector<CString>										ParamValues=RawParamValue.Split(Separator);
		CVector<CSocketIPEndpoint>								Values;

		Values.ReserveCapacity(ParamValues.GetLength());

		for(const CString& ParamValue : ParamValues)
		{
			CSocketIPEndpoint									Value=GetValueAsIPv4Endpoint(ParamValue,ParameterName,DefaultValuePlaceholder,DefaultValue);

			Values.Add(Value);
		}

		return(Values);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketIPAddress> CConsoleMenuItemCommandParams::GetSeparatedParamsAsIPv6Address(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, const CSocketIPAddress& DefaultValue) const
	{
		CheckParamIndex(Index);

		CString													RawParamValue=CString::ToUpperString(MCommandParams[Index]);
		CVector<CString>										ParamValues=RawParamValue.Split(Separator);
		CVector<CSocketIPAddress>								Values;

		Values.ReserveCapacity(ParamValues.GetLength());

		for(const CString& ParamValue : ParamValues)
		{
			CSocketIPAddress									Value=GetValueAsIPv6Address(ParamValue,ParameterName,DefaultValuePlaceholder,DefaultValue);

			Values.Add(Value);
		}

		return(Values);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketIPEndpoint> CConsoleMenuItemCommandParams::GetSeparatedParamsAsIPv6Endpoint(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, const CSocketIPEndpoint& DefaultValue) const
	{
		CheckParamIndex(Index);

		CString													RawParamValue=CString::ToUpperString(MCommandParams[Index]);
		CVector<CString>										ParamValues=RawParamValue.Split(Separator);
		CVector<CSocketIPEndpoint>								Values;

		Values.ReserveCapacity(ParamValues.GetLength());

		for(const CString& ParamValue : ParamValues)
		{
			CSocketIPEndpoint									Value=GetValueAsIPv6Endpoint(ParamValue,ParameterName,DefaultValuePlaceholder,DefaultValue);

			if (CSocketIPEndpoint::ParseIPv6Endpoint(ParamValue,Value)==true)
			{
				Values.Add(Value);
			}
			else
			{
				throw(CInvalidOperationException(CString::Format("PARAMETER [",ParameterName,"] contains INVALID VALUE !")));
			}
		}

		return(Values);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketDNSAddress> CConsoleMenuItemCommandParams::GetSeparatedParamsAsDNSAddress(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, const CSocketDNSAddress& DefaultValue) const
	{
		CheckParamIndex(Index);

		CString													RawParamValue=CString::ToUpperString(MCommandParams[Index]);
		CVector<CString>										ParamValues=RawParamValue.Split(Separator);
		CVector<CSocketDNSAddress>								Values;

		Values.ReserveCapacity(ParamValues.GetLength());

		for(const CString& ParamValue : ParamValues)
		{
			CSocketDNSAddress									Value=GetValueAsDNSAddress(ParamValue,ParameterName,DefaultValuePlaceholder,DefaultValue);

			Values.Add(Value);
		}

		return(Values);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketDNSEndpoint> CConsoleMenuItemCommandParams::GetSeparatedParamsAsDNSEndpoint(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, const CSocketDNSEndpoint& DefaultValue) const
	{
		CheckParamIndex(Index);

		CString													RawParamValue=CString::ToUpperString(MCommandParams[Index]);
		CVector<CString>										ParamValues=RawParamValue.Split(Separator);
		CVector<CSocketDNSEndpoint>								Values;

		Values.ReserveCapacity(ParamValues.GetLength());

		for(const CString& ParamValue : ParamValues)
		{
			CSocketDNSEndpoint									Value=GetValueAsDNSEndpoint(ParamValue,ParameterName,DefaultValuePlaceholder,DefaultValue);

			Values.Add(Value);
		}

		return(Values);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<SBool> CConsoleMenuItemCommandParams::GetSeparatedParamsAsBool(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, SBool DefaultValue) const
	{
		CheckParamIndex(Index);

		CString													RawParamValue=CString::ToUpperString(MCommandParams[Index]);
		CVector<CString>										ParamValues=RawParamValue.Split(Separator);
		CVector<SBool>											Values;

		Values.ReserveCapacity(ParamValues.GetLength());

		CInt32Formatter											Formatter(EIntegerFormat::E_NONE);

		for(const CString& ParamValue : ParamValues)
		{
			SBool												Value=GetValueAsBool(ParamValue,ParameterName,DefaultValuePlaceholder,DefaultValue);

			Values.Add(Value);
		}

		return(Values);
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer CConsoleMenuItemCommandParams::GetSeparatedParamsAsByteBuffer(Size Index, const CString& ParameterName, const CString& Separator, const CString& DefaultValuePlaceholder, uint8 DefaultValue, bool AllowHexValues, uint8 LowerBound, uint8 UpperBound) const
	{
		CheckParamIndex(Index);
		
		CString													RawParamValue=CString::ToUpperString(MCommandParams[Index]);
		CVector<CString>										ParamValues=RawParamValue.Split(Separator);
		CByteBuffer												Values;

		Values.ReserveCapacity(ParamValues.GetLength());

		for(const CString& ParamValue : ParamValues)
		{
			uint8												Value=GetValueAsUInt8(ParamValue,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound);

			Values.Add(Value);
		}

		return(Values);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CVector<int8> CConsoleMenuItemCommandParams::GetParamsAsInt8Array(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, int8 DefaultValue, bool AllowHexValues, int8 LowerBound, int8 UpperBound) const
	{
		CVector<int8>											Parameters;

		CheckParamIndex(Index);

		Size													NumberOfParameters=GetParamAsSize(Index,ParameterName);

		CheckParamIndex(Index+NumberOfParameters);

		Index++;

		for(Size Counter=0;Counter<NumberOfParameters;Counter++,Index++)
		{
			Parameters.Add(GetParamAsInt8(Index,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<uint8> CConsoleMenuItemCommandParams::GetParamsAsUInt8Array(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, uint8 DefaultValue, bool AllowHexValues, uint8 LowerBound, uint8 UpperBound) const
	{
		CVector<uint8>											Parameters;

		CheckParamIndex(Index);

		Size													NumberOfParameters=GetParamAsSize(Index,ParameterName);

		CheckParamIndex(Index+NumberOfParameters);

		Index++;

		for(Size Counter=0;Counter<NumberOfParameters;Counter++,Index++)
		{
			Parameters.Add(GetParamAsUInt8(Index,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<int16> CConsoleMenuItemCommandParams::GetParamsAsInt16Array(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, int16 DefaultValue, bool AllowHexValues, int16 LowerBound, int16 UpperBound) const
	{
		CVector<int16>											Parameters;

		CheckParamIndex(Index);

		Size													NumberOfParameters=GetParamAsSize(Index,ParameterName);

		CheckParamIndex(Index+NumberOfParameters);

		Index++;

		for(Size Counter=0;Counter<NumberOfParameters;Counter++,Index++)
		{
			Parameters.Add(GetParamAsInt16(Index,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<uint16> CConsoleMenuItemCommandParams::GetParamsAsUInt16Array(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, uint16 DefaultValue, bool AllowHexValues, uint16 LowerBound, uint16 UpperBound) const
	{
		CVector<uint16>											Parameters;

		CheckParamIndex(Index);

		Size													NumberOfParameters=GetParamAsSize(Index,ParameterName);

		CheckParamIndex(Index+NumberOfParameters);

		Index++;

		for(Size Counter=0;Counter<NumberOfParameters;Counter++,Index++)
		{
			Parameters.Add(GetParamAsUInt16(Index,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<int32> CConsoleMenuItemCommandParams::GetParamsAsInt32Array(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, int32 DefaultValue, bool AllowHexValues, int32 LowerBound, int32 UpperBound) const
	{
		CVector<int32>											Parameters;

		CheckParamIndex(Index);

		Size													NumberOfParameters=GetParamAsSize(Index,ParameterName);

		CheckParamIndex(Index+NumberOfParameters);

		Index++;

		for(Size Counter=0;Counter<NumberOfParameters;Counter++,Index++)
		{
			Parameters.Add(GetParamAsInt32(Index,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<uint32> CConsoleMenuItemCommandParams::GetParamsAsUInt32Array(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, uint32 DefaultValue, bool AllowHexValues, uint32 LowerBound, uint32 UpperBound) const
	{
		CVector<uint32>											Parameters;

		CheckParamIndex(Index);

		Size													NumberOfParameters=GetParamAsSize(Index,ParameterName);

		CheckParamIndex(Index+NumberOfParameters);

		Index++;

		for(Size Counter=0;Counter<NumberOfParameters;Counter++,Index++)
		{
			Parameters.Add(GetParamAsUInt32(Index,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<int64> CConsoleMenuItemCommandParams::GetParamsAsInt64Array(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, int64 DefaultValue, bool AllowHexValues, int64 LowerBound, int64 UpperBound) const
	{
		CVector<int64>											Parameters;

		CheckParamIndex(Index);

		Size													NumberOfParameters=GetParamAsSize(Index,ParameterName);

		CheckParamIndex(Index+NumberOfParameters);

		Index++;

		for(Size Counter=0;Counter<NumberOfParameters;Counter++,Index++)
		{
			Parameters.Add(GetParamAsInt64(Index,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<uint64> CConsoleMenuItemCommandParams::GetParamsAsUInt64Array(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, uint64 DefaultValue, bool AllowHexValues, uint64 LowerBound, uint64 UpperBound) const
	{
		CVector<uint64>											Parameters;

		CheckParamIndex(Index);

		Size													NumberOfParameters=GetParamAsSize(Index,ParameterName);

		CheckParamIndex(Index+NumberOfParameters);

		Index++;

		for(Size Counter=0;Counter<NumberOfParameters;Counter++,Index++)
		{
			Parameters.Add(GetParamAsUInt64(Index,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<float32> CConsoleMenuItemCommandParams::GetParamsAsFloat32Array(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, float32 DefaultValue, float32 LowerBound, float32 UpperBound) const
	{
		CVector<float32>										Parameters;

		CheckParamIndex(Index);

		Size													NumberOfParameters=GetParamAsSize(Index,ParameterName);

		CheckParamIndex(Index+NumberOfParameters);

		Index++;

		for(Size Counter=0;Counter<NumberOfParameters;Counter++,Index++)
		{
			Parameters.Add(GetParamAsFloat32(Index,ParameterName,DefaultValuePlaceholder,DefaultValue,LowerBound,UpperBound));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<float64> CConsoleMenuItemCommandParams::GetParamsAsFloat64Array(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, float64 DefaultValue, float64 LowerBound, float64 UpperBound) const
	{
		CVector<float64>										Parameters;

		CheckParamIndex(Index);

		Size													NumberOfParameters=GetParamAsSize(Index,ParameterName);

		CheckParamIndex(Index+NumberOfParameters);

		Index++;

		for(Size Counter=0;Counter<NumberOfParameters;Counter++,Index++)
		{
			Parameters.Add(GetParamAsFloat64(Index,ParameterName,DefaultValuePlaceholder,DefaultValue,LowerBound,UpperBound));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<float80> CConsoleMenuItemCommandParams::GetParamsAsFloat80Array(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, float80 DefaultValue, float80 LowerBound, float80 UpperBound) const
	{
		CVector<float80>										Parameters;

		CheckParamIndex(Index);

		Size													NumberOfParameters=GetParamAsSize(Index,ParameterName);

		CheckParamIndex(Index+NumberOfParameters);

		Index++;

		for(Size Counter=0;Counter<NumberOfParameters;Counter++,Index++)
		{
			Parameters.Add(GetParamAsFloat80(Index,ParameterName,DefaultValuePlaceholder,DefaultValue,LowerBound,UpperBound));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<Size> CConsoleMenuItemCommandParams::GetParamsAsSizeArray(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, Size DefaultValue, bool AllowHexValues, Size LowerBound, Size UpperBound) const
	{
		CVector<Size>											Parameters;

		CheckParamIndex(Index);

		Size													NumberOfParameters=GetParamAsSize(Index,ParameterName);

		CheckParamIndex(Index+NumberOfParameters);

		Index++;

		for(Size Counter=0;Counter<NumberOfParameters;Counter++,Index++)
		{
			Parameters.Add(GetParamAsSize(Index,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CString> CConsoleMenuItemCommandParams::GetParamsAsStringsArray(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CString& DefaultValue) const
	{
		CVector<CString>										Parameters;

		CheckParamIndex(Index);

		Size													NumberOfParameters=GetParamAsSize(Index,ParameterName);

		CheckParamIndex(Index+NumberOfParameters);

		Index++;

		for(Size Counter=0;Counter<NumberOfParameters;Counter++,Index++)
		{
			Parameters.Add(GetParamAsString(Index,DefaultValuePlaceholder,DefaultValue));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CDateTime> CConsoleMenuItemCommandParams::GetParamsAsDateTimeArray(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CDateTime& DefaultValue, const CDateTime& LowerBound, const CDateTime& UpperBound) const
	{
		CVector<CDateTime>										Parameters;

		CheckParamIndex(Index);

		Size													NumberOfParameters=GetParamAsSize(Index,ParameterName);

		CheckParamIndex(Index+NumberOfParameters);

		Index++;

		for(Size Counter=0;Counter<NumberOfParameters;Counter++,Index++)
		{
			Parameters.Add(GetParamAsDateTime(Index,ParameterName,DefaultValuePlaceholder,DefaultValue,LowerBound,UpperBound));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketIPAddress> CConsoleMenuItemCommandParams::GetParamsAsIPv4AddressesArray(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketIPAddress& DefaultValue) const
	{
		CVector<CSocketIPAddress>								Parameters;

		CheckParamIndex(Index);

		Size													NumberOfParameters=GetParamAsSize(Index,ParameterName);

		CheckParamIndex(Index+NumberOfParameters);

		Index++;

		for(Size Counter=0;Counter<NumberOfParameters;Counter++,Index++)
		{
			Parameters.Add(GetParamAsIPv4Address(Index,ParameterName,DefaultValuePlaceholder,DefaultValue));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketIPEndpoint> CConsoleMenuItemCommandParams::GetParamsAsIPv4EndpointsArray(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketIPEndpoint& DefaultValue) const
	{
		CVector<CSocketIPEndpoint>								Parameters;

		CheckParamIndex(Index);

		Size													NumberOfParameters=GetParamAsSize(Index,ParameterName);

		CheckParamIndex(Index+NumberOfParameters);

		Index++;

		for(Size Counter=0;Counter<NumberOfParameters;Counter++,Index++)
		{
			Parameters.Add(GetParamAsIPv4Endpoint(Index,ParameterName,DefaultValuePlaceholder,DefaultValue));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketIPAddress> CConsoleMenuItemCommandParams::GetParamsAsIPv6AddressesArray(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketIPAddress& DefaultValue) const
	{
		CVector<CSocketIPAddress>								Parameters;

		CheckParamIndex(Index);

		Size													NumberOfParameters=GetParamAsSize(Index,ParameterName);

		CheckParamIndex(Index+NumberOfParameters);

		Index++;

		for(Size Counter=0;Counter<NumberOfParameters;Counter++,Index++)
		{
			Parameters.Add(GetParamAsIPv6Address(Index,ParameterName,DefaultValuePlaceholder,DefaultValue));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketIPEndpoint> CConsoleMenuItemCommandParams::GetParamsAsIPv6EndpointsArray(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketIPEndpoint& DefaultValue) const
	{
		CVector<CSocketIPEndpoint>								Parameters;

		CheckParamIndex(Index);

		Size													NumberOfParameters=GetParamAsSize(Index,ParameterName);

		CheckParamIndex(Index+NumberOfParameters);

		Index++;

		for(Size Counter=0;Counter<NumberOfParameters;Counter++,Index++)
		{
			Parameters.Add(GetParamAsIPv6Endpoint(Index,ParameterName,DefaultValuePlaceholder,DefaultValue));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketDNSAddress> CConsoleMenuItemCommandParams::GetParamsAsDNSAddressesArray(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketDNSAddress& DefaultValue) const
	{
		CVector<CSocketDNSAddress>								Parameters;

		CheckParamIndex(Index);

		Size													NumberOfParameters=GetParamAsSize(Index,ParameterName);

		CheckParamIndex(Index+NumberOfParameters);

		Index++;

		for(Size Counter=0;Counter<NumberOfParameters;Counter++,Index++)
		{
			Parameters.Add(GetParamAsDNSAddress(Index,ParameterName,DefaultValuePlaceholder,DefaultValue));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketDNSEndpoint> CConsoleMenuItemCommandParams::GetParamsAsDNSEndpointsArray(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketDNSEndpoint& DefaultValue) const
	{
		CVector<CSocketDNSEndpoint>								Parameters;

		CheckParamIndex(Index);

		Size													NumberOfParameters=GetParamAsSize(Index,ParameterName);

		CheckParamIndex(Index+NumberOfParameters);

		Index++;

		for(Size Counter=0;Counter<NumberOfParameters;Counter++,Index++)
		{
			Parameters.Add(GetParamAsDNSEndpoint(Index,ParameterName,DefaultValuePlaceholder,DefaultValue));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<SBool> CConsoleMenuItemCommandParams::GetParamsAsBoolsArray(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, SBool DefaultValue) const
	{
		CVector<SBool>											Parameters;

		CheckParamIndex(Index);

		Size													NumberOfParameters=GetParamAsSize(Index,ParameterName);

		CheckParamIndex(Index+NumberOfParameters);

		Index++;

		for(Size Counter=0;Counter<NumberOfParameters;Counter++,Index++)
		{
			Parameters.Add(GetParamAsBool(Index,ParameterName,DefaultValuePlaceholder,DefaultValue));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer CConsoleMenuItemCommandParams::GetParamsAsByteBufferArray(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, uint8 DefaultValue, bool AllowHexValues, uint8 LowerBound, uint8 UpperBound) const
	{
		CByteBuffer												Parameters(GetParamsAsUInt8Array(Index,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CVector<int8> CConsoleMenuItemCommandParams::GetRemainingParamsAsInt8(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, int8 DefaultValue, bool AllowHexValues, int8 LowerBound, int8 UpperBound) const
	{
		CVector<int8>											Parameters;
		Size													NumberOfParameters=GetNumberOfParams();

		for(Size CurrentIndex=Index;CurrentIndex<NumberOfParameters;CurrentIndex++,Index++)
		{
			Parameters.Add(GetParamAsInt8(CurrentIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<uint8> CConsoleMenuItemCommandParams::GetRemainingParamsAsUInt8(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, uint8 DefaultValue, bool AllowHexValues, uint8 LowerBound, uint8 UpperBound) const
	{
		CVector<uint8>											Parameters;
		Size													NumberOfParameters=GetNumberOfParams();

		for(Size CurrentIndex=Index;CurrentIndex<NumberOfParameters;CurrentIndex++,Index++)
		{
			Parameters.Add(GetParamAsUInt8(CurrentIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<int16> CConsoleMenuItemCommandParams::GetRemainingParamsAsInt16(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, int16 DefaultValue, bool AllowHexValues, int16 LowerBound, int16 UpperBound) const
	{
		CVector<int16>											Parameters;
		Size													NumberOfParameters=GetNumberOfParams();

		for(Size CurrentIndex=Index;CurrentIndex<NumberOfParameters;CurrentIndex++,Index++)
		{
			Parameters.Add(GetParamAsInt16(CurrentIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<uint16> CConsoleMenuItemCommandParams::GetRemainingParamsAsUInt16(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, uint16 DefaultValue, bool AllowHexValues, uint16 LowerBound, uint16 UpperBound) const
	{
		CVector<uint16>											Parameters;
		Size													NumberOfParameters=GetNumberOfParams();

		for(Size CurrentIndex=Index;CurrentIndex<NumberOfParameters;CurrentIndex++,Index++)
		{
			Parameters.Add(GetParamAsUInt16(CurrentIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<int32> CConsoleMenuItemCommandParams::GetRemainingParamsAsInt32(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, int32 DefaultValue, bool AllowHexValues, int32 LowerBound, int32 UpperBound) const
	{
		CVector<int32>											Parameters;
		Size													NumberOfParameters=GetNumberOfParams();

		for(Size CurrentIndex=Index;CurrentIndex<NumberOfParameters;CurrentIndex++,Index++)
		{
			Parameters.Add(GetParamAsInt32(CurrentIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<uint32> CConsoleMenuItemCommandParams::GetRemainingParamsAsUInt32(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, uint32 DefaultValue, bool AllowHexValues, uint32 LowerBound, uint32 UpperBound) const
	{
		CVector<uint32>											Parameters;
		Size													NumberOfParameters=GetNumberOfParams();

		for(Size CurrentIndex=Index;CurrentIndex<NumberOfParameters;CurrentIndex++,Index++)
		{
			Parameters.Add(GetParamAsUInt32(CurrentIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<int64> CConsoleMenuItemCommandParams::GetRemainingParamsAsInt64(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, int64 DefaultValue, bool AllowHexValues, int64 LowerBound, int64 UpperBound) const
	{
		CVector<int64>											Parameters;
		Size													NumberOfParameters=GetNumberOfParams();

		for(Size CurrentIndex=Index;CurrentIndex<NumberOfParameters;CurrentIndex++,Index++)
		{
			Parameters.Add(GetParamAsInt64(CurrentIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<uint64> CConsoleMenuItemCommandParams::GetRemainingParamsAsUInt64(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, uint64 DefaultValue, bool AllowHexValues, uint64 LowerBound, uint64 UpperBound) const
	{
		CVector<uint64>											Parameters;
		Size													NumberOfParameters=GetNumberOfParams();

		for(Size CurrentIndex=Index;CurrentIndex<NumberOfParameters;CurrentIndex++,Index++)
		{
			Parameters.Add(GetParamAsUInt64(CurrentIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<float32> CConsoleMenuItemCommandParams::GetRemainingParamsAsFloat32(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, float32 DefaultValue, float32 LowerBound, float32 UpperBound) const
	{
		CVector<float32>										Parameters;
		Size													NumberOfParameters=GetNumberOfParams();

		for(Size CurrentIndex=Index;CurrentIndex<NumberOfParameters;CurrentIndex++,Index++)
		{
			Parameters.Add(GetParamAsFloat32(CurrentIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,LowerBound,UpperBound));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<float64> CConsoleMenuItemCommandParams::GetRemainingParamsAsFloat64(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, float64 DefaultValue, float64 LowerBound, float64 UpperBound) const
	{
		CVector<float64>										Parameters;
		Size													NumberOfParameters=GetNumberOfParams();

		for(Size CurrentIndex=Index;CurrentIndex<NumberOfParameters;CurrentIndex++,Index++)
		{
			Parameters.Add(GetParamAsFloat64(CurrentIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,LowerBound,UpperBound));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<float80> CConsoleMenuItemCommandParams::GetRemainingParamsAsFloat80(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, float80 DefaultValue, float80 LowerBound, float80 UpperBound) const
	{
		CVector<float80>										Parameters;
		Size													NumberOfParameters=GetNumberOfParams();

		for(Size CurrentIndex=Index;CurrentIndex<NumberOfParameters;CurrentIndex++,Index++)
		{
			Parameters.Add(GetParamAsFloat80(CurrentIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,LowerBound,UpperBound));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<Size> CConsoleMenuItemCommandParams::GetRemainingParamsAsSize(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, Size DefaultValue, bool AllowHexValues, Size LowerBound, Size UpperBound) const
	{
		CVector<Size>											Parameters;
		Size													NumberOfParameters=GetNumberOfParams();

		for(Size CurrentIndex=Index;CurrentIndex<NumberOfParameters;CurrentIndex++,Index++)
		{
			Parameters.Add(GetParamAsSize(CurrentIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CString> CConsoleMenuItemCommandParams::GetRemainingParamsAsStrings(Size& Index, const CString& DefaultValuePlaceholder, const CString& DefaultValue) const
	{
		CVector<CString>										Parameters;
		Size													NumberOfParameters=GetNumberOfParams();

		for(Size CurrentIndex=Index;CurrentIndex<NumberOfParameters;CurrentIndex++,Index++)
		{
			Parameters.Add(GetParamAsString(CurrentIndex,DefaultValuePlaceholder,DefaultValue));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CDateTime> CConsoleMenuItemCommandParams::GetRemainingParamsAsDateTime(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CDateTime& DefaultValue, const CDateTime& LowerBound, const CDateTime& UpperBound) const
	{
		CVector<CDateTime>										Parameters;
		Size													NumberOfParameters=GetNumberOfParams();

		for(Size CurrentIndex=Index;CurrentIndex<NumberOfParameters;CurrentIndex++,Index++)
		{
			Parameters.Add(GetParamAsDateTime(CurrentIndex,ParameterName,DefaultValuePlaceholder,DefaultValue,LowerBound,UpperBound));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketIPAddress> CConsoleMenuItemCommandParams::GetRemainingParamsAsIPv4Addresses(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketIPAddress& DefaultValue) const
	{
		CVector<CSocketIPAddress>								Parameters;
		Size													NumberOfParameters=GetNumberOfParams();

		for(Size CurrentIndex=Index;CurrentIndex<NumberOfParameters;CurrentIndex++,Index++)
		{
			Parameters.Add(GetParamAsIPv4Address(CurrentIndex,ParameterName,DefaultValuePlaceholder,DefaultValue));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketIPEndpoint> CConsoleMenuItemCommandParams::GetRemainingParamsAsIPv4Endpoints(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketIPEndpoint& DefaultValue) const
	{
		CVector<CSocketIPEndpoint>								Parameters;
		Size													NumberOfParameters=GetNumberOfParams();

		for(Size CurrentIndex=Index;CurrentIndex<NumberOfParameters;CurrentIndex++,Index++)
		{
			Parameters.Add(GetParamAsIPv4Endpoint(CurrentIndex,ParameterName,DefaultValuePlaceholder,DefaultValue));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketIPAddress> CConsoleMenuItemCommandParams::GetRemainingParamsAsIPv6Addresses(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketIPAddress& DefaultValue) const
	{
		CVector<CSocketIPAddress>								Parameters;
		Size													NumberOfParameters=GetNumberOfParams();

		for(Size CurrentIndex=Index;CurrentIndex<NumberOfParameters;CurrentIndex++,Index++)
		{
			Parameters.Add(GetParamAsIPv6Address(CurrentIndex,ParameterName,DefaultValuePlaceholder,DefaultValue));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketIPEndpoint> CConsoleMenuItemCommandParams::GetRemainingParamsAsIPv6Endpoints(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketIPEndpoint& DefaultValue) const
	{
		CVector<CSocketIPEndpoint>								Parameters;
		Size													NumberOfParameters=GetNumberOfParams();

		for(Size CurrentIndex=Index;CurrentIndex<NumberOfParameters;CurrentIndex++,Index++)
		{
			Parameters.Add(GetParamAsIPv6Endpoint(CurrentIndex,ParameterName,DefaultValuePlaceholder,DefaultValue));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketDNSAddress> CConsoleMenuItemCommandParams::GetRemainingParamsAsDNSAddresses(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketDNSAddress& DefaultValue) const
	{
		CVector<CSocketDNSAddress>								Parameters;
		Size													NumberOfParameters=GetNumberOfParams();

		for(Size CurrentIndex=Index;CurrentIndex<NumberOfParameters;CurrentIndex++,Index++)
		{
			Parameters.Add(GetParamAsDNSAddress(CurrentIndex,ParameterName,DefaultValuePlaceholder,DefaultValue));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CSocketDNSEndpoint> CConsoleMenuItemCommandParams::GetRemainingParamsAsDNSEndpoints(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, const CSocketDNSEndpoint& DefaultValue) const
	{
		CVector<CSocketDNSEndpoint>								Parameters;
		Size													NumberOfParameters=GetNumberOfParams();

		for(Size CurrentIndex=Index;CurrentIndex<NumberOfParameters;CurrentIndex++,Index++)
		{
			Parameters.Add(GetParamAsDNSEndpoint(CurrentIndex,ParameterName,DefaultValuePlaceholder,DefaultValue));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<SBool> CConsoleMenuItemCommandParams::GetRemainingParamsAsBools(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, SBool DefaultValue) const
	{
		CVector<SBool>											Parameters;
		Size													NumberOfParameters=GetNumberOfParams();

		for(Size CurrentIndex=Index;CurrentIndex<NumberOfParameters;CurrentIndex++,Index++)
		{
			Parameters.Add(GetParamAsBool(CurrentIndex,ParameterName,DefaultValuePlaceholder,DefaultValue));
		}

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer CConsoleMenuItemCommandParams::GetRemainingParamsAsByteBuffer(Size& Index, const CString& ParameterName, const CString& DefaultValuePlaceholder, uint8 DefaultValue, bool AllowHexValues, uint8 LowerBound, uint8 UpperBound) const
	{
		CByteBuffer												Parameters(GetRemainingParamsAsUInt8(Index,ParameterName,DefaultValuePlaceholder,DefaultValue,AllowHexValues,LowerBound,UpperBound));

		return(Parameters);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------