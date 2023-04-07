//----------------------------------------------------------------------------------------------------------------------
#include "CString.h"
#include <locale>
#include <Framework/Foundation/Collections/CByteBuffer.h>
#include <Framework/Foundation/Collections/CSet.h>
#include <Framework/Foundation/Collections/CVector.h>
#include <Framework/Foundation/Exceptions/CInvalidOperationException.h>
#include <Framework/Foundation/Exceptions/CValueOutOfRangeException.h>
#include <Framework/Foundation/Mathematics/CMathematics.h>
#include <Framework/Platform/Global/Macros.h>
#include "CIntegerFormatter.h"
#include "CFloatFormatter.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const Size													CString::END=string::npos;
	const CString												CString::EMPTY="";
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(void)
		: MString("")
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(const CString& Other)
		: MString(Other.MString)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(CString&& Other) noexcept
		: MString(FUNCTION_MOVE(Other.MString))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(const string& Value)
		: MString(Value)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(string&& Value)
		: MString(FUNCTION_MOVE(Value))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(const CByteBuffer& Value)
		: MString(reinterpret_cast<const Char*>(Value.GetRawData()),static_cast<string::size_type>(Value.GetLength()))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(const Char* Value)
		: MString(Value)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(const Char* Value, Size Length)
		: MString(Value,static_cast<string::size_type>(Length))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(const Char* From, const Char* To)
		: MString(From,To)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(Size Width, Char Value)
		: MString(Width,Value)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(bool Value)
		: MString()
	{
		if (Value==true)
		{
			MString="1";
		}
		else
		{
			MString="0";
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(int8 Value)
		: MString()
	{
		CIntegerFormatter<int8>									Formatter;
		
		Formatter.ConvertToString(*this,Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(int8 Value, const IValueFormatter<int8>& Formatter)
		: MString()
	{
		Formatter.ConvertToString(*this,Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(int8 Value, EIntegerFormat IntegerFormat, Size MinimalWidth, bool PadWithZeros)
		: MString()
	{
		CIntegerFormatter<int8>									Formatter(IntegerFormat,MinimalWidth,PadWithZeros);
			
		Formatter.ConvertToString(*this,Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(int16 Value)
		: MString()
	{
		CIntegerFormatter<int16>								Formatter;
		
		Formatter.ConvertToString(*this,Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(int16 Value, const IValueFormatter<int16>& Formatter)
		: MString()
	{
		Formatter.ConvertToString(*this,Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(int16 Value, EIntegerFormat IntegerFormat, Size MinimalWidth, bool PadWithZeros)
		: MString()
	{
		CIntegerFormatter<int16>								Formatter(IntegerFormat,MinimalWidth,PadWithZeros);
			
		Formatter.ConvertToString(*this,Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(int32 Value)
		: MString()
	{
		CIntegerFormatter<int32>								Formatter;
		
		Formatter.ConvertToString(*this,Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(int32 Value, const IValueFormatter<int32>& Formatter)
		: MString()
	{
		Formatter.ConvertToString(*this,Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(int32 Value, EIntegerFormat IntegerFormat, Size MinimalWidth, bool PadWithZeros)
		: MString()
	{
		CIntegerFormatter<int32>								Formatter(IntegerFormat,MinimalWidth,PadWithZeros);
			
		Formatter.ConvertToString(*this,Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(int64 Value)
		: MString()
	{
		CIntegerFormatter<int64>								Formatter;
		
		Formatter.ConvertToString(*this,Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(int64 Value, const IValueFormatter<int64>& Formatter)
		: MString()
	{
		Formatter.ConvertToString(*this,Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(int64 Value, EIntegerFormat IntegerFormat, Size MinimalWidth, bool PadWithZeros)
		: MString()
	{
		CIntegerFormatter<int64>								Formatter(IntegerFormat,MinimalWidth,PadWithZeros);
			
		Formatter.ConvertToString(*this,Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(uint8 Value)
		: MString()
	{
		CIntegerFormatter<uint8>								Formatter;
		
		Formatter.ConvertToString(*this,Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(uint8 Value, const IValueFormatter<uint8>& Formatter)
		: MString()
	{
		Formatter.ConvertToString(*this,Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(uint8 Value, EIntegerFormat IntegerFormat, Size MinimalWidth, bool PadWithZeros)
		: MString()
	{
		CIntegerFormatter<uint8>								Formatter(IntegerFormat,MinimalWidth,PadWithZeros);
			
		Formatter.ConvertToString(*this,Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(uint16 Value)
		: MString()
	{
		CIntegerFormatter<uint16>								Formatter;
		
		Formatter.ConvertToString(*this,Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(uint16 Value, const IValueFormatter<uint16>& Formatter)
		: MString()
	{
		Formatter.ConvertToString(*this,Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(uint16 Value, EIntegerFormat IntegerFormat, Size MinimalWidth, bool PadWithZeros)
		: MString()
	{
		CIntegerFormatter<uint16>								Formatter(IntegerFormat,MinimalWidth,PadWithZeros);
			
		Formatter.ConvertToString(*this,Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(uint32 Value)
		: MString()
	{
		CIntegerFormatter<uint32>								Formatter;
		
		Formatter.ConvertToString(*this,Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(uint32 Value, const IValueFormatter<uint32>& Formatter)
		: MString()
	{
		Formatter.ConvertToString(*this,Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(uint32 Value, EIntegerFormat IntegerFormat, Size MinimalWidth, bool PadWithZeros)
		: MString()
	{
		CIntegerFormatter<uint32>								Formatter(IntegerFormat,MinimalWidth,PadWithZeros);
			
		Formatter.ConvertToString(*this,Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(uint64 Value)
		: MString()
	{
		CIntegerFormatter<uint64>								Formatter;
		
		Formatter.ConvertToString(*this,Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(uint64 Value, const IValueFormatter<uint64>& Formatter)
		: MString()
	{
		Formatter.ConvertToString(*this,Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(uint64 Value, EIntegerFormat IntegerFormat, Size MinimalWidth, bool PadWithZeros)
		: MString()
	{
		CIntegerFormatter<uint64>								Formatter(IntegerFormat,MinimalWidth,PadWithZeros);
			
		Formatter.ConvertToString(*this,Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(float32 Value)
		: MString()
	{
		CFloatFormatter<float32>								Formatter;
		
		Formatter.ConvertToString(*this,Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(float32 Value, const IValueFormatter<float32>& Formatter)
		: MString()
	{
		Formatter.ConvertToString(*this,Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(float32 Value, Size Precision, Size MinimalWidth, Char PaddingCharacter, EPaddingDirection PaddingDirection)
		: MString()
	{
		CFloatFormatter<float32>								Formatter(Precision,MinimalWidth,PaddingCharacter,PaddingDirection);
		
		Formatter.ConvertToString(*this,Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(float64 Value)
		: MString()
	{
		CFloatFormatter<float64>								Formatter;
		
		Formatter.ConvertToString(*this,Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(float64 Value, const IValueFormatter<float64>& Formatter)
		: MString()
	{
		Formatter.ConvertToString(*this,Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(float64 Value, Size Precision, Size MinimalWidth, Char PaddingCharacter, EPaddingDirection PaddingDirection)
		: MString()
	{
		CFloatFormatter<float64>								Formatter(Precision,MinimalWidth,PaddingCharacter,PaddingDirection);
		
		Formatter.ConvertToString(*this,Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(float80 Value)
		: MString()
	{
		CFloatFormatter<float80>								Formatter;
		
		Formatter.ConvertToString(*this,Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(float80 Value, const IValueFormatter<float80>& Formatter)
		: MString()
	{
		Formatter.ConvertToString(*this,Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(float80 Value, Size Precision, Size MinimalWidth, Char PaddingCharacter, EPaddingDirection PaddingDirection)
		: MString()
	{
		CFloatFormatter<float80>								Formatter(Precision,MinimalWidth,PaddingCharacter,PaddingDirection);
		
		Formatter.ConvertToString(*this,Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::CString(initializer_list<Char> Characters)
		: MString(Characters)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CString::~CString(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	[[noreturn]] void CString::ThrowException(const CString Message, const exception& E)
	{
		throw(CInvalidOperationException(Message,E));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CString::FormatParameter(CString& FormattedString, const CString& Parameter)
	{
		try
		{
			FormattedString+=Parameter;
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CString::FormatParameter(CString& FormattedString, CString&& Parameter)
	{
		try
		{
			FormattedString+=FUNCTION_MOVE(Parameter);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CString::FormatParameter(CString& FormattedString, const string& Parameter)
	{
		try
		{
			FormattedString+=Parameter;
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CString::FormatParameter(CString& FormattedString, string&& Parameter)
	{
		try
		{
			FormattedString+=Parameter;
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CString::FormatParameter(CString& FormattedString, const Char* Parameter)
	{
		try
		{
			FormattedString+=Parameter;
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CString::FormatParameter(CString& FormattedString, const CObject& Parameter)
	{
		try
		{
			FormattedString+=Parameter.ToString();
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CString::FormatParameter(CString& FormattedString, CObject& Parameter)
	{
		try
		{
			FormattedString+=Parameter.ToString();
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CString::InternalFormat(CString&)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString& CString::operator=(const CString& Other)
	{
		try
		{
			MString=Other.MString;

			return(*this);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString& CString::operator=(CString&& Other) noexcept
	{
		try
		{
			MString=FUNCTION_MOVE(Other.MString);

			return(*this);
		}
		catch(const exception& /*E*/)
		{
			/*
			// CODE SHOULD NEVER GET HERE.
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
			*/

			return(*this);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString& CString::operator=(const string& Other)
	{
		try
		{
			MString=Other;

			return(*this);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString& CString::operator=(const Char* Other)
	{
		try
		{
			MString=Other;

			return(*this);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString& CString::operator+=(Char Other)
	{
		try
		{
			MString+=Other;

			return(*this);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString& CString::operator+=(const CString& Other)
	{
		try
		{
			MString+=Other.GetString();

			return(*this);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString& CString::operator+=(const string& Other)
	{
		try
		{
			MString+=Other;

			return(*this);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString& CString::operator+=(const Char* Other)
	{
		try
		{
			MString+=Other;

			return(*this);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CString::operator==(const CString& Other) const
	{
		try
		{
			if (GetLength()==Other.GetLength())
			{
				Size											Length=GetLength();

				for(Size Index=0;Index<Length;Index++)
				{
					if ((*this)[Index]!=Other[Index])
					{
						return(false);
					}
				}

				return(true);
			}
			else
			{
				return(false);
			}
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CString::operator!=(const CString& Other) const
	{
		try
		{
			if (*this==Other)
			{
				return(false);
			}
			else
			{
				return(true);
			}
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CString::operator<(const CString& Other) const
	{
		try
		{
			Size												Length=(GetLength()<=Other.GetLength()) ? GetLength() : Other.GetLength();

			for(Size Index=0;Index<Length;Index++)
			{
				if ((*this)[Index]<Other[Index])
				{
					return(true);
				}
				else if ((*this)[Index]>Other[Index])
				{
					return(false);
				}
			}

			if (GetLength()<Other.GetLength())
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CString::operator<=(const CString& Other) const
	{
		try
		{
			Size												Length=(GetLength()<=Other.GetLength()) ? GetLength() : Other.GetLength();

			for(Size Index=0;Index<Length;Index++)
			{
				if ((*this)[Index]<Other[Index])
				{
					return(true);
				}
				else if ((*this)[Index]>Other[Index])
				{
					return(false);
				}
			}

			if (GetLength()<=Other.GetLength())
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CString::operator>(const CString& Other) const
	{
		try
		{
			Size												Length=(GetLength()<=Other.GetLength()) ? GetLength() : Other.GetLength();

			for(Size Index=0;Index<Length;Index++)
			{
				if ((*this)[Index]>Other[Index])
				{
					return(true);
				}
				else if ((*this)[Index]<Other[Index])
				{
					return(false);
				}
			}

			if (GetLength()>Other.GetLength())
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CString::operator>=(const CString& Other) const
	{
		try
		{
			Size												Length=(GetLength()<=Other.GetLength()) ? GetLength() : Other.GetLength();

			for(Size Index=0;Index<Length;Index++)
			{
				if ((*this)[Index]>Other[Index])
				{
					return(true);
				}
				else if ((*this)[Index]<Other[Index])
				{
					return(false);
				}
			}

			if (GetLength()>=Other.GetLength())
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	Char& CString::operator[](Size Index)
	{
		try
		{
			CheckIndex(Index,false);

			return(MString[static_cast<string::size_type>(Index)]);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	const Char& CString::operator[](Size Index) const
	{
		try
		{
			CheckIndex(Index,false);

			return(MString[static_cast<string::size_type>(Index)]);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString operator+(const CString& Left, const CString& Right)
	{
		try
		{
			CString												Result(Left);

			Result+=Right;

			return(Result);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString operator+(const CString& Left, const string& Right)
	{
		try
		{
			CString												Result(Left);

			Result+=Right;

			return(Result);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString operator+(const CString& Left, const Char* Right)
	{
		try
		{
			CString												Result(Left);

			Result+=Right;

			return(Result);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	ostream& operator<<(ostream& Stream, const CString& Value)
	{
		try
		{
			Stream << Value.MString;

			return(Stream);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	istream& operator>>(istream& Stream, CString& Value)
	{
		try
		{
			Stream >> Value.MString;

			return(Stream);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString operator"" _S(const Char* Value, Size ValueSize)
	{
		CString													StringValue;

		StringValue.Resize(ValueSize);

		for(Size Index=0;Index<ValueSize;Index++)
		{
			StringValue[Index]=Value[Index];
		}

		return(StringValue);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CString& CString::Empty(void)
	{
		try
		{
			return(EMPTY);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CString::ToLowerString(const CString& Value)
	{
		try
		{
			locale												Locale;
			CString												LowerValue=Value;

			for(Char& Character : LowerValue)
			{
				Character=tolower(Character,Locale);
			}

			return(LowerValue);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CString::ToUpperString(const CString& Value)
	{
		try
		{
			locale												Locale;
			CString												UpperValue=Value;

			for(Char& Character : UpperValue)
			{
				Character=toupper(Character,Locale);
			}

			return(UpperValue);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CString::FromChar(Char Value)
	{
		try
		{
			return(CString({Value}));
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CString::Format(void)
	{
		try
		{
			return("");
		}
		catch(const std::exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CString::CheckIndex(Size Index, bool AllowAfterStringPosition) const
	{
		try
		{
			if (AllowAfterStringPosition==false)
			{
				if (Index>=GetLength())
				{
					throw(CValueOutOfRangeException("INDEX is OUT of RANGE !"));
				}
			}
			else
			{
				if (Index>GetLength())
				{
					throw(CValueOutOfRangeException("INDEX is OUT of RANGE !"));
				}
			}
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CString::CheckOffset(Size Offset) const
	{
		try
		{
			if (Offset>GetLength() && Offset!=END)
			{
				throw(CValueOutOfRangeException("OFFSET is OUT of RANGE !"));
			}
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	Char CString::GetCharacter(Size Index) const
	{
		try
		{
			return(MString[static_cast<string::size_type>(Index)]);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CString::ToString(void) const
	{
		try
		{
			return(*this);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	const string& CString::GetString(void) const noexcept
	{
		return(MString);
	}
//----------------------------------------------------------------------------------------------------------------------
	string& CString::GetString(void) noexcept
	{
		return(MString);
	}
//----------------------------------------------------------------------------------------------------------------------
	const Char* CString::GetCharArray(void) const
	{
		try
		{
			return(MString.c_str());
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer CString::GetByteBuffer(void) const
	{
		try
		{
			CByteBuffer											ByteBuffer(reinterpret_cast<const uint8*>(GetCharArray()),GetLength());

			return(ByteBuffer);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CString::GetLength(void) const
	{
		try
		{
			Size												Length=static_cast<Size>(MString.length());
				
			return(Length);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CString::GetCapacity(void) const
	{
		try
		{
			Size												Capacity=static_cast<Size>(MString.capacity());
				
			return(Capacity);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CString::SetCapacity(Size Capacity)
	{
		try
		{
			MString.reserve(Capacity);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CString::Resize(Size NewSize)
	{
		try
		{
			MString.resize(NewSize);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CString::ShrinkCapacityToFit(void)
	{
		try
		{
			MString.shrink_to_fit();
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CString::IsEmpty(void) const
	{
		try
		{
			if (GetLength()==0)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CString::IsEmptyOrWhitespace(void) const
	{
		try
		{
			if (IsEmpty()==true)
			{
				return(true);
			}
			else
			{
				locale											Locale;

				for(const Char& Character : *this)
				{
					if (isspace(Character,Locale)==false)
					{
						return(false);
					}
				}

				return(true);
			}
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CString::HasStringAt(Size Offset, const CString& String) const
	{
		try
		{
			CheckOffset(Offset);

			if ((String.GetLength()+Offset)<=GetLength())
			{
				for(Size Index=0;Index<String.GetLength();Index++)
				{
					if (MString[static_cast<string::size_type>(Offset+Index)]!=String[Index])
					{
						return(false);
					}
				}

				return(true);
			}
			else
			{
				return(false);
			}
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CString::GetHash(void) const
	{
		try
		{
			hash<string>										Hash;
			Size												HashCode=static_cast<Size>(Hash.operator()(MString));

			return(HashCode);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CString::Clear(void)
	{
		try
		{
			MString.clear();
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString& CString::Append(Char Other)
	{
		try
		{
			MString.append(1,Other);

			return(*this);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString& CString::Append(const CString& Other)
	{
		try
		{
			MString.append(Other.GetCharArray());

			return(*this);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CString::Append(const CString& Other) const
	{
		CString													Value=*this;

		Value.Append(Other);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString& CString::Append(const string& Other)
	{
		try
		{
			MString.append(Other);

			return(*this);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString& CString::Append(const Char* Other)
	{
		try
		{
			MString.append(Other);

			return(*this);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString& CString::Append(const Char* Other, Size Length)
	{
		try
		{
			MString.append(Other,static_cast<string::size_type>(Length));

			return(*this);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString& CString::Insert(Char Char, Size Offset)
	{
		try
		{
			CheckIndex(Offset,true);

			MString.insert(static_cast<string::size_type>(Offset),1,Char);

			return(*this);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString& CString::Insert(const CString& String, Size Offset)
	{
		try
		{
			CheckIndex(Offset,true);

			MString.insert(static_cast<string::size_type>(Offset),String.GetString());

			return(*this);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CString::Insert(const CString& String, Size Offset) const
	{
		CString													Value=*this;

		Value.Insert(String,Offset);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString& CString::Insert(const Char* Value, Size Length, Size Offset)
	{
		try
		{
			CheckIndex(Offset,true);

			MString.insert(static_cast<string::size_type>(Offset),Value,static_cast<string::size_type>(Length));

			return(*this);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString& CString::Erase(Size Offset, Size Length)
	{
		try
		{
			CheckIndex(Offset,true);

			MString.erase(static_cast<string::size_type>(Offset),static_cast<string::size_type>(Length));

			return(*this);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CString::Erase(Size Offset, Size Length) const
	{
		CString													Value=*this;

		Value.Erase(Offset,Length);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString& CString::EraseAll(Char CharToErase)
	{
		try
		{
			for(Size Index=0;Index<GetLength();Index++)
			{
				if (MString[static_cast<string::size_type>(Index)]==CharToErase)
				{
					MString.erase(static_cast<string::size_type>(Index),static_cast<string::size_type>(1));
					Index--;
				}
			}

			return(*this);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CString::EraseAll(Char CharToErase) const
	{
		CString													Value=*this;

		Value.EraseAll(CharToErase);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CString::Contains(Char Char) const
	{
		try
		{
			if (FindFirst(Char)!=END)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CString::Contains(const CString& String) const
	{
		try
		{
			if (FindFirst(String)!=END)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CString::StartsWith(const CString& String) const
	{
		try
		{
			Size												Position=FindFirst(String);

			if (Position==0)
			{
				return(true);
			}
			else
			{
				return(false);
			}
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CString::EndsWith(const CString& String) const
	{
		try
		{
			Size												Position=FindLast(String);

			if (Position!=END)
			{
				if ((Position+String.GetLength())==GetLength())
				{
					return(true);
				}
				else
				{
					return(false);
				}
			}
			else
			{
				return(false);
			}
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CString::FindFirst(Char Char, Size Offset) const
	{
		try
		{
			CheckOffset(Offset);

			Size												Position=static_cast<Size>(MString.find(Char,static_cast<string::size_type>(Offset)));

			return(Position);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CString::FindFirst(const CString& String, Size Offset) const
	{
		try
		{
			CheckOffset(Offset);

			Size												Position=static_cast<Size>(MString.find(String.GetCharArray(),static_cast<string::size_type>(Offset)));

			return(Position);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CString::FindLast(Char Char, Size Offset) const
	{
		try
		{
			CheckOffset(Offset);

			Size												Position=static_cast<Size>(MString.rfind(Char,static_cast<string::size_type>(Offset)));

			return(Position);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CString::FindLast(const CString& String, Size Offset) const
	{
		try
		{
			CheckOffset(Offset);

			Size												Position=static_cast<Size>(MString.rfind(String.GetCharArray(),static_cast<string::size_type>(Offset)));

			return(Position);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString& CString::ReplaceFirst(Char OriginalChar, Char NewChar, Size Offset)
	{
		try
		{
			CheckOffset(Offset);

			Size												Position=FindFirst(OriginalChar,Offset);

			if (Position!=END)
			{
				MString[Position]=NewChar;
			}

			return(*this);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CString::ReplaceFirst(Char OriginalChar, Char NewChar, Size Offset) const
	{
		CString													Value=*this;

		Value.ReplaceFirst(OriginalChar,NewChar,Offset);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString& CString::ReplaceFirst(const CString& OriginalString, const CString& NewString, Size Offset)
	{
		try
		{
			CheckOffset(Offset);

			Size												Position=FindFirst(OriginalString,Offset);

			if (Position!=END)
			{
				MString.replace(static_cast<string::size_type>(Position),static_cast<string::size_type>(OriginalString.GetLength()),NewString.GetString());
			}

			return(*this);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CString::ReplaceFirst(const CString& OriginalString, const CString& NewString, Size Offset) const
	{
		CString													Value=*this;

		Value.ReplaceFirst(OriginalString,NewString,Offset);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString& CString::ReplaceLast(Char OriginalChar, Char NewChar, Size Offset)
	{
		try
		{
			CheckOffset(Offset);

			Size												Position=FindLast(OriginalChar,Offset);

			if (Position!=END)
			{
				MString[Position]=NewChar;
			}

			return(*this);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CString::ReplaceLast(Char OriginalChar, Char NewChar, Size Offset) const
	{
		CString													Value=*this;

		Value.ReplaceLast(OriginalChar,NewChar,Offset);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString& CString::ReplaceLast(const CString& OriginalString, const CString& NewString, Size Offset)
	{
		try
		{
			CheckOffset(Offset);

			Size												Position=FindLast(OriginalString,Offset);

			if (Position!=END)
			{
				MString.replace(static_cast<string::size_type>(Position),static_cast<string::size_type>(OriginalString.GetLength()),NewString.GetString());
			}

			return(*this);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CString::ReplaceLast(const CString& OriginalString, const CString& NewString, Size Offset) const
	{
		CString													Value=*this;

		Value.ReplaceLast(OriginalString,NewString,Offset);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString& CString::ReplaceAll(Char OriginalChar, Char NewChar)
	{
		try
		{
			Size												Length=GetLength();

			for(Size Index=0;Index<Length;Index++)
			{
				if (MString[static_cast<string::size_type>(Index)]==OriginalChar)
				{
					MString[static_cast<string::size_type>(Index)]=NewChar;
				}
			}

			return(*this);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CString::ReplaceAll(Char OriginalChar, Char NewChar) const
	{
		CString													Value=*this;

		Value.ReplaceAll(OriginalChar,NewChar);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString& CString::ReplaceAll(const CString& OriginalString, const CString& NewString)
	{
		try
		{
			Size												OriginalStringLength=OriginalString.GetLength();
			Size												NewStringLength=NewString.GetLength();
			Size												Offset=FindFirst(OriginalString,0);

			while(Offset!=END)
			{
				MString.replace(static_cast<string::size_type>(Offset),static_cast<string::size_type>(OriginalStringLength),NewString.GetString());
			
				Offset+=NewStringLength;
				Offset=FindFirst(OriginalString,Offset);
			}

			return(*this);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CString::ReplaceAll(const CString& OriginalString, const CString& NewString) const
	{
		CString													Value=*this;

		Value.ReplaceAll(OriginalString,NewString);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CString::LexicographicallyEqual(const CString& StringToCompare, bool CaseSensitive) const
	{
		if (LexicographicalCompare(StringToCompare,CaseSensitive)==0)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CString::LexicographicalCompare(const CString& StringToCompare, bool CaseSensitive) const
	{
		try
		{
			if (CaseSensitive==true)
			{
				Size											MinLength=CMathematics::Mininum(GetLength(),StringToCompare.GetLength());

				for(Size Index=0;Index<MinLength;Index++)
				{
					Char										Char1=(*this)[Index];
					Char										Char2=StringToCompare[Index];

					if (Char1<Char2)
					{
						return(-1);
					}
					else if (Char1>Char2)
					{
						return(1);
					}
				}

				if (GetLength()<StringToCompare.GetLength())
				{
					return(-1);
				}
				else if (GetLength()>StringToCompare.GetLength())
				{
					return(1);
				}
				else
				{
					return(0);
				}
			}
			else
			{
				Size											MinLength=CMathematics::Mininum(GetLength(),StringToCompare.GetLength());

				for(Size Index=0;Index<MinLength;Index++)
				{
					locale										Locale;
					Char										Char1=toupper((*this)[Index],Locale);
					Char										Char2=toupper(StringToCompare[Index],Locale);

					if (Char1<Char2)
					{
						return(-1);
					}
					else if (Char1>Char2)
					{
						return(1);
					}
				}

				if (GetLength()<StringToCompare.GetLength())
				{
					return(-1);
				}
				else if (GetLength()>StringToCompare.GetLength())
				{
					return(1);
				}
				else
				{
					return(0);
				}
			}
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CString::SubString(Size Offset, Size Length) const
	{
		try
		{
			CheckIndex(Offset,true);

			CString												SubString=MString.substr(static_cast<string::size_type>(Offset),static_cast<string::size_type>(Length));

			return(SubString);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CString> CString::Split(Char Separator, bool RemoveEmptyEntries) const
	{
		try
		{
			CVector<CString>									Splits;
			Size												LastPosition=0;
			Size												SeparatorLength=1;

			while(true)
			{
				Size											SeparatorPosition=FindFirst(Separator,LastPosition);

				if (SeparatorPosition!=END)
				{
					Size										SplitSize=(SeparatorPosition-LastPosition);

					if (RemoveEmptyEntries==false || SplitSize>0)
					{
						CString									Split=SubString(LastPosition,SplitSize);

						Splits.Add(FUNCTION_MOVE(Split));
					}

					LastPosition=SeparatorPosition+SeparatorLength;
				}
				else
				{
					if (LastPosition!=GetLength())
					{
						CString									Split=SubString(LastPosition);

						Splits.Add(FUNCTION_MOVE(Split));
					}
					else
					{
						if (RemoveEmptyEntries==false)
						{
							Splits.Add("");
						}
					}

					break;
				}
			}

			return(Splits);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CString> CString::Split(const CString& Separator, bool RemoveEmptyEntries) const
	{
		try
		{
			CVector<CString>									Splits;
			Size												LastPosition=0;
			Size												SeparatorLength=Separator.GetLength();

			while(true)
			{
				Size											SeparatorPosition=FindFirst(Separator,LastPosition);

				if (SeparatorPosition!=END)
				{
					Size										SplitSize=(SeparatorPosition-LastPosition);

					if (RemoveEmptyEntries==false || SplitSize>0)
					{
						CString									Split=SubString(LastPosition,SplitSize);

						Splits.Add(FUNCTION_MOVE(Split));
					}

					LastPosition=SeparatorPosition+SeparatorLength;
				}
				else
				{
					if (LastPosition!=GetLength())
					{
						CString									Split=SubString(LastPosition);

						Splits.Add(FUNCTION_MOVE(Split));
					}
					else
					{
						if (RemoveEmptyEntries==false)
						{
							Splits.Add("");
						}
					}

					break;
				}
			}

			return(Splits);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CString::SSplitIndex> CString::SplitToIndexes(Char Separator, bool RemoveEmptyEntries) const
	{
		try
		{
			CVector<SSplitIndex>								Splits;
			Size												LastPosition=0;
			Size												SeparatorLength=1;

			while(true)
			{
				Size											SeparatorPosition=FindFirst(Separator,LastPosition);

				if (SeparatorPosition!=END)
				{
					Size										SplitSize=(SeparatorPosition-LastPosition);

					if (RemoveEmptyEntries==false || SplitSize>0)
					{
						Splits.Add(SSplitIndex(LastPosition,SplitSize));
					}

					LastPosition=SeparatorPosition+SeparatorLength;
				}
				else
				{
					Size										SplitSize=(GetLength()-LastPosition);

					if (RemoveEmptyEntries==false || SplitSize>0)
					{
						Splits.Add(SSplitIndex(LastPosition,SplitSize));
					}

					break;
				}
			}

			return(Splits);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CVector<CString::SSplitIndex> CString::SplitToIndexes(const CString& Separator, bool RemoveEmptyEntries) const
	{
		try
		{
			CVector<SSplitIndex>								Splits;
			Size												LastPosition=0;
			Size												SeparatorLength=Separator.GetLength();

			while(true)
			{
				Size											SeparatorPosition=FindFirst(Separator,LastPosition);

				if (SeparatorPosition!=END)
				{
					Size										SplitSize=(SeparatorPosition-LastPosition);

					if (RemoveEmptyEntries==false || SplitSize>0)
					{
						Splits.Add(SSplitIndex(LastPosition,SplitSize));
					}

					LastPosition=SeparatorPosition+SeparatorLength;
				}
				else
				{
					Size										SplitSize=(GetLength()-LastPosition);

					if (RemoveEmptyEntries==false || SplitSize>0)
					{
						Splits.Add(SSplitIndex(LastPosition,SplitSize));
					}

					break;
				}
			}

			return(Splits);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString& CString::Trim(void)
	{
		try
		{
			CVector<Char>										CharactersToTrim={' ','\r','\n','\t'};

			TrimStart(CharactersToTrim);
			TrimEnd(CharactersToTrim);

			return(*this);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CString::Trim(void) const
	{
		CString													Value=*this;

		Value.Trim();

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString& CString::Trim(const CVector<Char>& CharactersToTrim)
	{
		try
		{
			TrimStart(CharactersToTrim);
			TrimEnd(CharactersToTrim);

			return(*this);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CString::Trim(const CVector<Char>& CharactersToTrim) const
	{
		CString													Value=*this;

		Value.Trim(CharactersToTrim);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString& CString::TrimStart(const CVector<Char>& CharactersToTrim)
	{
		try
		{
			CSet<Char>											SortedCharactersToTrim(CharactersToTrim);
			Size												Length=GetLength();

			if (Length>0)
			{
				bool											HasCharactersToRemove=false;
				Size											Index=0;
				Size											LengthToRemove=0;

				while(true)
				{
					Char										Character=GetCharacter(Index);

					if (SortedCharactersToTrim.Contains(Character)==true)
					{
						HasCharactersToRemove=true;
						LengthToRemove++;
					}
					else
					{
						break;
					}

					if (++Index==0)
					{
						break;
					}
				}

				if (HasCharactersToRemove==true)
				{
					Erase(0,LengthToRemove);
				}
			}

			return(*this);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CString::TrimStart(const CVector<Char>& CharactersToTrim) const
	{
		CString													Value=*this;

		Value.TrimStart(CharactersToTrim);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString& CString::TrimEnd(const CVector<Char>& CharactersToTrim)
	{
		try
		{
			CSet<Char>											SortedCharactersToTrim(CharactersToTrim);
			Size												Length=GetLength();

			if (Length>0)
			{
				bool											HasCharactersToRemove=false;
				Size											Index=(Length-1);
				Size											RemoveIndex=0;

				while(true)
				{
					Char										Character=GetCharacter(Index);

					if (SortedCharactersToTrim.Contains(Character)==true)
					{
						HasCharactersToRemove=true;
						RemoveIndex=Index;
					}
					else
					{
						break;
					}

					if (Index--==0)
					{
						break;
					}
				}

				if (HasCharactersToRemove==true)
				{
					Size										LengthToRemove=(Length-RemoveIndex);

					Erase(RemoveIndex,LengthToRemove);
				}
			}

			return(*this);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CString::TrimEnd(const CVector<Char>& CharactersToTrim) const
	{
		CString													Value=*this;

		Value.TrimEnd(CharactersToTrim);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString& CString::PadLeft(Size Width, Char Character)
	{
		try
		{
			string												PadString(Width,Character);

			MString.insert(0,PadString);

			return(*this);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CString::PadLeft(Size Width, Char Character) const
	{
		CString													Value=*this;

		Value.PadLeft(Width,Character);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString& CString::PadRight(Size Width, Char Character)
	{
		try
		{
			string												PadString(Width,Character);

			MString+=PadString;

			return(*this);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CString::PadRight(Size Width, Char Character) const
	{
		CString													Value=*this;

		Value.PadRight(Width,Character);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString& CString::ToLower(void)
	{
		try
		{
			locale												Locale;

			for(Char& Character : *this)
			{
				Character=tolower(Character,Locale);
			}

			return(*this);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CString::ToLower(void) const
	{
		CString													Value=ToLowerString(*this);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	CString& CString::ToUpper(void)
	{
		try
		{
			locale												Locale;

			for(Char& Character : *this)
			{
				Character=toupper(Character,Locale);
			}

			return(*this);
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString CString::ToUpper(void) const
	{
		CString													Value=ToUpperString(*this);

		return(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	string::iterator CString::begin(void)
	{
		try
		{
			return(MString.begin());
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	string::iterator CString::end(void)
	{
		try
		{
			return(MString.end());
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	string::const_iterator CString::begin(void) const
	{
		try
		{
			return(MString.cbegin());
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	string::const_iterator CString::end(void) const
	{
		try
		{
			return(MString.cend());
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString ToHexaDecimalString(int8 Value, bool AddPrefix, Size MinimalWidth, bool PadWithZeros)
	{
		try
		{
			return(CString(Value,(AddPrefix==false) ? EIntegerFormat::E_HEXADECIMAL : EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX,MinimalWidth,PadWithZeros));
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString ToHexaDecimalString(int16 Value, bool AddPrefix, Size MinimalWidth, bool PadWithZeros)
	{
		try
		{
			return(CString(Value,(AddPrefix==false) ? EIntegerFormat::E_HEXADECIMAL : EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX,MinimalWidth,PadWithZeros));
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString ToHexaDecimalString(int32 Value, bool AddPrefix, Size MinimalWidth, bool PadWithZeros)
	{
		try
		{
			return(CString(Value,(AddPrefix==false) ? EIntegerFormat::E_HEXADECIMAL : EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX,MinimalWidth,PadWithZeros));
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString ToHexaDecimalString(int64 Value, bool AddPrefix, Size MinimalWidth, bool PadWithZeros)
	{
		try
		{
			return(CString(Value,(AddPrefix==false) ? EIntegerFormat::E_HEXADECIMAL : EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX,MinimalWidth,PadWithZeros));
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString ToHexaDecimalString(uint8 Value, bool AddPrefix, Size MinimalWidth, bool PadWithZeros)
	{
		try
		{
			return(CString(Value,(AddPrefix==false) ? EIntegerFormat::E_HEXADECIMAL : EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX,MinimalWidth,PadWithZeros));
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString ToHexaDecimalString(uint16 Value, bool AddPrefix, Size MinimalWidth, bool PadWithZeros)
	{
		try
		{
			return(CString(Value,(AddPrefix==false) ? EIntegerFormat::E_HEXADECIMAL : EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX,MinimalWidth,PadWithZeros));
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString ToHexaDecimalString(uint32 Value, bool AddPrefix, Size MinimalWidth, bool PadWithZeros)
	{
		try
		{
			return(CString(Value,(AddPrefix==false) ? EIntegerFormat::E_HEXADECIMAL : EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX,MinimalWidth,PadWithZeros));
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CString ToHexaDecimalString(uint64 Value, bool AddPrefix, Size MinimalWidth, bool PadWithZeros)
	{
		try
		{
			return(CString(Value,(AddPrefix==false) ? EIntegerFormat::E_HEXADECIMAL : EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX,MinimalWidth,PadWithZeros));
		}
		catch(const exception& E)
		{
			throw(CInvalidOperationException("INVALID STRING OPERATION !",E));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------