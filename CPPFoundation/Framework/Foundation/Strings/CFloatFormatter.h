//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <type_traits>
#include <sstream>
#include <iomanip> 
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Foundation/Exceptions/CArgumentException.h>
#include <Framework/Foundation/Exceptions/CInvalidOperationException.h>
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Types/CPrimitiveType.h>
#include <Framework/Foundation/Exceptions/CInvalidValueException.h>
#include "EPaddingDirection.h"
#include "IValueFormatter.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	template<typename TFloatType>
	class CFloatFormatter final : public CObject, public IValueFormatter<TFloatType>
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			enum class EFloatingPointNumberParsingState
			{
//----------------------------------------------------------------------------------------------------------------------
				E_BEGIN,
				E_INTEGER_PART,
				E_DECIMAL_POINT_LETTER,
				E_FRACTION_PART,
				E_EXPONENT_LETTER,
				E_EXPONENT_PART,
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		static_assert(std::is_same<TFloatType,float32>::value==true || std::is_same<TFloatType,float64>::value==true || std::is_same<TFloatType,float80>::value==true,"TYPE is NOT SUPPORTED for TEMPLATE [CFloatFormatter<TFloatType>] !");

		private:
			Size												MPrecision;
			Size												MMinimalWidth;
			Char												MPaddingCharacter;
			EPaddingDirection									MPaddingDirection;

		private:
			bool CheckStringFormat(const CString& Value, Size From, Size To) const
			{
				if (From>=To || To>Value.GetLength())
				{
					return(false);
				}

				EFloatingPointNumberParsingState				State=EFloatingPointNumberParsingState::E_BEGIN;
				bool											HasNumber=false;
				bool											HasExponent=false;

				for(Size Index=From;Index<To;Index++)
				{
					Char										Character=Value[Index];

					if (State==EFloatingPointNumberParsingState::E_BEGIN)
					{
						if (Character=='+')
						{
							State=EFloatingPointNumberParsingState::E_INTEGER_PART;
						}
						else if (Character=='-')
						{
							State=EFloatingPointNumberParsingState::E_INTEGER_PART;
						}
						else if (Character=='.')
						{
							State=EFloatingPointNumberParsingState::E_DECIMAL_POINT_LETTER;
						}
						else if (Character=='e' || Character=='E')
						{
							return(false);
						}
						else if (Character>='0' && Character<='9')
						{
							State=EFloatingPointNumberParsingState::E_INTEGER_PART;
							HasNumber=true;
						}
						else
						{
							return(false);
						}
					}
					else if (State==EFloatingPointNumberParsingState::E_INTEGER_PART)
					{
						if (Character=='+')
						{
							return(false);
						}
						else if (Character=='-')
						{
							return(false);
						}
						else if (Character=='.')
						{
							State=EFloatingPointNumberParsingState::E_DECIMAL_POINT_LETTER;
						}
						else if (Character=='e' || Character=='E')
						{
							State=EFloatingPointNumberParsingState::E_EXPONENT_LETTER;
						}
						else if (Character>='0' && Character<='9')
						{
							State=EFloatingPointNumberParsingState::E_INTEGER_PART;
							HasNumber=true;
						}
						else
						{
							return(false);
						}
					}
					else if (State==EFloatingPointNumberParsingState::E_DECIMAL_POINT_LETTER)
					{
						if (Character=='+')
						{
							return(false);
						}
						else if (Character=='-')
						{
							return(false);
						}
						else if (Character=='.')
						{
							return(false);
						}
						else if (Character=='e' || Character=='E')
						{
							State=EFloatingPointNumberParsingState::E_EXPONENT_LETTER;
						}
						else if (Character>='0' && Character<='9')
						{
							State=EFloatingPointNumberParsingState::E_FRACTION_PART;
							HasNumber=true;
						}
						else
						{
							return(false);
						}
					}
					else if (State==EFloatingPointNumberParsingState::E_FRACTION_PART)
					{
						if (Character=='+')
						{
							return(false);
						}
						else if (Character=='-')
						{
							return(false);
						}
						else if (Character=='.')
						{
							return(false);
						}
						else if (Character=='e' || Character=='E')
						{
							State=EFloatingPointNumberParsingState::E_EXPONENT_LETTER;
						}
						else if (Character>='0' && Character<='9')
						{
							State=EFloatingPointNumberParsingState::E_FRACTION_PART;
						}
						else
						{
							return(false);
						}
					}
					else if (State==EFloatingPointNumberParsingState::E_EXPONENT_LETTER)
					{
						if (Character=='+')
						{
							State=EFloatingPointNumberParsingState::E_EXPONENT_PART;
						}
						else if (Character=='-')
						{
							State=EFloatingPointNumberParsingState::E_EXPONENT_PART;
						}
						else if (Character=='.')
						{
							return(false);
						}
						else if (Character=='e' || Character=='E')
						{
							return(false);
						}
						else if (Character>='0' && Character<='9')
						{
							State=EFloatingPointNumberParsingState::E_EXPONENT_PART;
							HasExponent=true;
						}
						else
						{
							return(false);
						}
					}
					else if (State==EFloatingPointNumberParsingState::E_EXPONENT_PART)
					{
						if (Character=='+')
						{
							return(false);
						}
						else if (Character=='-')
						{
							return(false);
						}
						else if (Character=='.')
						{
							return(false);
						}
						else if (Character=='e' || Character=='E')
						{
							return(false);
						}
						else if (Character>='0' && Character<='9')
						{
							State=EFloatingPointNumberParsingState::E_EXPONENT_PART;
							HasExponent=true;
						}
						else
						{
							return(false);
						}
					}
					else
					{
						throw(CInvalidOperationException("INVALID PARSING STATE !"));
					}
				}

				if (State==EFloatingPointNumberParsingState::E_BEGIN)
				{
					return(false);
				}
				else if (State==EFloatingPointNumberParsingState::E_INTEGER_PART)
				{
					return(HasNumber);
				}
				else if (State==EFloatingPointNumberParsingState::E_DECIMAL_POINT_LETTER)
				{
					return(HasNumber);
				}
				else if (State==EFloatingPointNumberParsingState::E_FRACTION_PART)
				{
					return(HasNumber);
				}
				else if (State==EFloatingPointNumberParsingState::E_EXPONENT_LETTER)
				{
					return(false);
				}
				else if (State==EFloatingPointNumberParsingState::E_EXPONENT_PART)
				{
					if (HasNumber==true && HasExponent==true)
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
					throw(CInvalidOperationException("INVALID PARSING STATE !"));
				}
			}

		public:
			virtual bool Parse(const CString& Value, TFloatType& Result) const override
			{
				return(Parse(Value,0,Value.GetLength(),Result));
			}

			virtual bool Parse(const CString& Value, Size From, Size To, TFloatType& Result) const override
			{
				try
				{
					if (CheckStringFormat(Value,From,To)==false)
					{
						return(false);
					}

					std::stringstream							Stream;

					Stream.write(&Value[From],static_cast<std::streamsize>(To-From));

					Stream << std::setprecision(static_cast<int>(MPrecision));

					if (MMinimalWidth>0)
					{
						if (MPaddingDirection==EPaddingDirection::E_LEFT)
						{
							Stream << std::left;
						}
						else if (MPaddingDirection==EPaddingDirection::E_INTERNAL)
						{
							Stream << std::internal;
						}
						else if (MPaddingDirection==EPaddingDirection::E_RIGHT)
						{
							Stream << std::right;
						}
						else
						{
							throw(CInvalidOperationException("INVALID PADDING DIRECTION !"));
						}

						Stream << std::setw(static_cast<int>(MMinimalWidth));
					}

					Stream >> Result;

					bool										ParsingSucceeded=static_cast<bool>(Stream);

					if (ParsingSucceeded==true)
					{
						return(true);
					}
					else
					{
						return(false);
					}
				}
				catch(...)
				{
					return(false);
				}
			}

			virtual void ConvertToString(CString& String, TFloatType Value) const override
			{
				std::stringstream								Stream;

				Stream << std::setprecision(static_cast<int>(MPrecision));

				if (MMinimalWidth>0)
				{
					if (MPaddingDirection==EPaddingDirection::E_LEFT)
					{
						Stream << std::left;
					}
					else if (MPaddingDirection==EPaddingDirection::E_INTERNAL)
					{
						Stream << std::internal;
					}
					else if (MPaddingDirection==EPaddingDirection::E_RIGHT)
					{
						Stream << std::right;
					}
					else
					{
						throw(CInvalidOperationException("INVALID PADDING DIRECTION !"));
					}

					Stream << std::setw(static_cast<int>(MMinimalWidth));
					Stream << std::setfill(MPaddingCharacter);
				}

				Stream << Value;
		
				String+=Stream.str();
			}

			virtual CString ConvertToString(TFloatType Value) const override
			{
				CString											String;

				ConvertToString(String,Value);

				return(String);
			}

		public:
			CFloatFormatter(Size Precision=CPrimitiveType<TFloatType>::GetMaxDigits10(), Size MinimalWidth=0, Char PaddingCharacter=' ', EPaddingDirection PaddingDirection=EPaddingDirection::E_INTERNAL)
				: MPrecision(Precision), MMinimalWidth(MinimalWidth), MPaddingCharacter(PaddingCharacter), MPaddingDirection(PaddingDirection)
			{
				if (CheckValue(PaddingDirection)==false)
				{
					throw(CArgumentException("INVALID PADDING DIRECTION !"));
				}
			}

			virtual ~CFloatFormatter(void) override
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using CFloat32Formatter=CFloatFormatter<float32>;
	using CFloat64Formatter=CFloatFormatter<float64>;
	using CFloat80Formatter=CFloatFormatter<float80>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------