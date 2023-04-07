//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <type_traits>
#include <sstream>
#include <iomanip> 
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Types/CPrimitiveType.h>
#include <Framework/Foundation/Exceptions/CInvalidValueException.h>
#include "IValueFormatter.h"
#include "EIntegerFormat.h"
#if defined(PLATFORM_WINDOWS)
#pragma warning( disable : 4127)
#endif
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	template<typename TIntegerType>
	class CIntegerFormatter final : public CObject, public IValueFormatter<TIntegerType>
	{
//----------------------------------------------------------------------------------------------------------------------
		static_assert(std::is_same<TIntegerType,int8>::value==true || std::is_same<TIntegerType,uint8>::value==true || std::is_same<TIntegerType,int16>::value==true || std::is_same<TIntegerType,uint16>::value==true || std::is_same<TIntegerType,int32>::value==true || std::is_same<TIntegerType,uint32>::value==true || std::is_same<TIntegerType,int64>::value==true || std::is_same<TIntegerType,uint64>::value==true || std::is_same<TIntegerType,Size>::value==true,"TYPE is NOT SUPPORTED for TEMPLATE [CIntegerFormatter<TIntegerType>] !");

		private:
			static const int32									BASE_NONE=10;
			static const int32									BASE_HEXADECIMAL=16;

		private:
			EIntegerFormat										MFormat;
			Size												MMinimalWidth;
			bool												MPadWithZeros;

		private:
			static bool CheckStringFormat(const CString& Value, EIntegerFormat Format, Size From, Size To, Size& NumberIndex, bool& IsNegative)
			{
				NumberIndex=From;
				IsNegative=false;

				if (From>=To || To>Value.GetLength())
				{
					return(false);
				}

				bool											HasNumber=false;

				if (std::is_signed<TIntegerType>::value==true)
				{
					if ((NumberIndex+1)<=To)
					{
						Char									Sign=Value[NumberIndex];

						if (Sign=='+')
						{
							NumberIndex++;
						}
						else if (Sign=='-')
						{
							NumberIndex++;
							IsNegative=true;
						}
					}
					else
					{
						return(false);
					}
				}
				else
				{
					if ((NumberIndex+1)<=To)
					{
						Char									Sign=Value[NumberIndex];

						if (Sign=='+')
						{
							NumberIndex++;
						}
					}
				}

				if (Format==EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX)
				{
					if ((NumberIndex+2)<=To)
					{
						Char									Zero=Value[NumberIndex];
						Char									X=Value[NumberIndex+1];

						if (Zero!='0')
						{
							return(false);
						}

						if (X!='x' && X!='X')
						{
							return(false);
						}

						NumberIndex+=2;
					}
					else
					{
						return(false);
					}
				}

				if (Format==EIntegerFormat::E_NONE)
				{
					for(Size Index=NumberIndex;Index<To;Index++)
					{
						Char									Char=Value[Index];
						
						if (Char>='0' && Char<='9')
						{
							HasNumber=true;
						}
						else
						{
							return(false);
						}
					}
				}
				else if (Format==EIntegerFormat::E_HEXADECIMAL || Format==EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX)
				{
					for(Size Index=NumberIndex;Index<To;Index++)
					{
						Char									Char=Value[Index];
						
						if (((Char>='0' && Char<='9') || (Char>='A' && Char<='H') || (Char>='a' && Char<='h')))
						{
							HasNumber=true;
						}
						else
						{
							return(false);
						}
					}
				}
				else
				{
					throw(CInvalidValueException("INVALID INTEGER FORMAT !"));
				}

				return(HasNumber);
			}

		public:
			virtual bool Parse(const CString& Value, TIntegerType& Result) const override
			{
				return(Parse(Value,0,Value.GetLength(),Result));
			}

			virtual bool Parse(const CString& Value, Size From, Size To, TIntegerType& Result) const override
			{
				Size											NumberIndex;
				bool											IsNegative;

				if (CheckStringFormat(Value,MFormat,From,To,NumberIndex,IsNegative)==false)
				{
					return(false);
				}

				From=NumberIndex;

				try
				{
					std::stringstream							Stream;

					if (IsNegative==true)
					{
						Stream.put('-');
					}

					Stream.write(&Value[From],static_cast<std::streamsize>(To-From));

					if (MFormat==EIntegerFormat::E_NONE)
					{
						Stream << std::dec;
					}
					else if (MFormat==EIntegerFormat::E_HEXADECIMAL)
					{
						Stream << std::hex << std::uppercase;
					}
					else if (MFormat==EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX)
					{
						Stream << std::hex << std::uppercase << std::showbase;
					}
					else
					{
						throw(CInvalidValueException("INVALID INTEGER FORMAT !"));
					}

					Stream >> Result;

					bool										ParsingSucceeded=static_cast<bool>(Stream);

					if (ParsingSucceeded==true)
					{
						return(true);
					}
					else
					{
						if (std::is_signed<TIntegerType>::value==true)
						{
							typename std::make_unsigned<TIntegerType>::type	UnsignedResult=0;

							Stream.clear();
							Stream.seekg(0);

							if (MFormat==EIntegerFormat::E_NONE)
							{
								Stream << std::dec;
							}
							else if (MFormat==EIntegerFormat::E_HEXADECIMAL)
							{
								Stream << std::hex << std::uppercase;
							}
							else if (MFormat==EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX)
							{
								Stream << std::hex << std::uppercase << std::showbase;
							}
							else
							{
								throw(CInvalidValueException("INVALID INTEGER FORMAT !"));
							}

							Stream >> UnsignedResult;

							ParsingSucceeded=static_cast<bool>(Stream);

							if (ParsingSucceeded==true)
							{
								Result=static_cast<TIntegerType>(UnsignedResult);

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
				}
				catch(...)
				{
					return(false);
				}
			}

			virtual void ConvertToString(CString& String, TIntegerType Value) const override
			{
				std::stringstream								Stream;

				if (MFormat==EIntegerFormat::E_NONE)
				{
					Stream << std::dec;
				}
				else if (MFormat==EIntegerFormat::E_HEXADECIMAL)
				{
					Stream << std::hex << std::uppercase;
				}
				else if (MFormat==EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX)
				{
					Stream << std::hex << std::uppercase;
					String+="0x";
				}
				else
				{
					throw(CInvalidValueException("INVALID INTEGER FORMAT !"));
				}

				if (MMinimalWidth!=0)
				{
					Stream << std::setw(static_cast<int>(MMinimalWidth));
				}

				if (MPadWithZeros==true)
				{
					Stream << std::setfill('0');
				}

				Stream << Value;
		
				String+=Stream.str();

				if (MPadWithZeros==true && Value<0)
				{
					Size										Length=String.GetLength();

					for(Size Index=0;Index<Length;Index++)
					{
						if (String[Index]=='-')
						{
							if (Index!=0)
							{
								String[0]='-';
								String[Index]='0';
							}

							break;
						}
					}
				}
			}

			virtual CString ConvertToString(TIntegerType Value) const override
			{
				CString											String;

				ConvertToString(String,Value);

				return(String);
			}

		public:
			CIntegerFormatter(EIntegerFormat Format=EIntegerFormat::E_NONE, Size MinimalWidth=0, bool PadWithZeros=false)
				: MFormat(Format), MMinimalWidth(MinimalWidth), MPadWithZeros(PadWithZeros)
			{
			}

			virtual ~CIntegerFormatter(void) override
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<>
	class CIntegerFormatter<int8> final : public CObject, public IValueFormatter<int8>
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			static const int32									BASE_NONE=10;
			static const int32									BASE_HEXADECIMAL=16;
			static const int16									MIN_VALUE=-128;
			static const int16									MAX_VALUE=127;

		private:
			EIntegerFormat										MFormat;
			Size												MMinimalWidth;
			bool												MPadWithZeros;
			CIntegerFormatter<int16>							MFormatter;

		public:
			virtual bool Parse(const CString& Value, int8& Result) const override
			{
				return(Parse(Value,0,Value.GetLength(),Result));
			}

			virtual bool Parse(const CString& Value, Size From, Size To, int8& Result) const override
			{
				int16											Value16Bits;

				if (MFormatter.Parse(Value,From,To,Value16Bits)==false)
				{
					return(false);
				}

				if (Value16Bits<MIN_VALUE || Value16Bits>MAX_VALUE)
				{
					return(false);
				}

				Result=static_cast<int8>(Value16Bits);

				return(true);
			}

			virtual void ConvertToString(CString& String, int8 Value) const override
			{
				std::stringstream								Stream;

				if (MFormat==EIntegerFormat::E_NONE)
				{
					Stream << std::dec;
				}
				else if (MFormat==EIntegerFormat::E_HEXADECIMAL)
				{
					Stream << std::hex << std::uppercase;
				}
				else if (MFormat==EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX)
				{
					Stream << std::hex << std::uppercase;
					String+="0x";
				}
				else
				{
					throw(CInvalidValueException("INVALID INTEGER FORMAT !"));
				}

				if (MMinimalWidth!=0)
				{
					Stream << std::setw(static_cast<int>(MMinimalWidth));
				}

				if (MPadWithZeros==true)
				{
					Stream << std::setfill('0');
				}

				int16											IntegerValue=static_cast<int16>(Value);

				Stream << IntegerValue;
		
				String+=Stream.str();

				if (MPadWithZeros==true && Value<0)
				{
					Size										Length=String.GetLength();

					for(Size Index=0;Index<Length;Index++)
					{
						if (String[Index]=='-')
						{
							if (Index!=0)
							{
								String[0]='-';
								String[Index]='0';
							}

							break;
						}
					}
				}
			}

			virtual CString ConvertToString(int8 Value) const override
			{
				CString											String;

				ConvertToString(String,Value);

				return(String);
			}

		public:
			CIntegerFormatter(EIntegerFormat Format=EIntegerFormat::E_NONE, Size MinimalWidth=0, bool PadWithZeros=false)
				: MFormat(Format), MMinimalWidth(MinimalWidth), MPadWithZeros(PadWithZeros), MFormatter(MFormat,MMinimalWidth,PadWithZeros)
			{
			}

			~CIntegerFormatter(void)
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	template<>
	class CIntegerFormatter<uint8> final : public CObject, public IValueFormatter<uint8>
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			static const int32									BASE_NONE=10;
			static const int32									BASE_HEXADECIMAL=16;
			static const int16									MAX_VALUE=255;

		private:
			EIntegerFormat										MFormat;
			Size												MMinimalWidth;
			bool												MPadWithZeros;
			CIntegerFormatter<uint16>							MFormatter;

		public:
			virtual bool Parse(const CString& Value, uint8& Result) const override
			{
				return(Parse(Value,0,Value.GetLength(),Result));
			}

			virtual bool Parse(const CString& Value, Size From, Size To, uint8& Result) const override
			{
				uint16											Value16Bits;

				if (MFormatter.Parse(Value,From,To,Value16Bits)==false)
				{
					return(false);
				}

				if (Value16Bits>MAX_VALUE)
				{
					return(false);
				}

				Result=static_cast<uint8>(Value16Bits);

				return(true);
			}

			virtual void ConvertToString(CString& String, uint8 Value) const override
			{
				std::stringstream								Stream;

				if (MFormat==EIntegerFormat::E_NONE)
				{
					Stream << std::dec;
				}
				else if (MFormat==EIntegerFormat::E_HEXADECIMAL)
				{
					Stream << std::hex << std::uppercase;
				}
				else if (MFormat==EIntegerFormat::E_HEXADECIMAL_WITH_PREFIX)
				{
					Stream << std::hex << std::uppercase;
					String+="0x";
				}
				else
				{
					throw(CInvalidValueException("INVALID INTEGER FORMAT !"));
				}

				if (MMinimalWidth!=0)
				{
					Stream << std::setw(static_cast<int>(MMinimalWidth));
				}

				if (MPadWithZeros==true)
				{
					Stream << std::setfill('0');
				}

				int16											IntegerValue=static_cast<int16>(Value);

				Stream << IntegerValue;
		
				String+=Stream.str();

				if (MPadWithZeros==true)
				{
					Size										Length=String.GetLength();

					for(Size Index=0;Index<Length;Index++)
					{
						if (String[Index]=='-')
						{
							if (Index!=0)
							{
								String[0]='-';
								String[Index]='0';
							}

							break;
						}
					}
				}
			}

			virtual CString ConvertToString(uint8 Value) const override
			{
				CString											String;

				ConvertToString(String,Value);

				return(String);
			}

		public:
			CIntegerFormatter(EIntegerFormat Format=EIntegerFormat::E_NONE, Size MinimalWidth=0, bool PadWithZeros=false)
				: MFormat(Format), MMinimalWidth(MinimalWidth), MPadWithZeros(PadWithZeros), MFormatter(MFormat,MMinimalWidth,PadWithZeros)
			{
			}

			virtual ~CIntegerFormatter(void) override
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using CInt8Formatter=CIntegerFormatter<int8>;
	using CUInt8Formatter=CIntegerFormatter<uint8>;
	using CInt16Formatter=CIntegerFormatter<int16>;
	using CUInt16Formatter=CIntegerFormatter<uint16>;
	using CInt32Formatter=CIntegerFormatter<int32>;
	using CUInt32Formatter=CIntegerFormatter<uint32>;
	using CInt64Formatter=CIntegerFormatter<int64>;
	using CUInt64Formatter=CIntegerFormatter<uint64>;
	using CSizeFormatter=CIntegerFormatter<Size>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------