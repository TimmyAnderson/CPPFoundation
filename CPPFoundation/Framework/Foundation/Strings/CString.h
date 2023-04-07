//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
#include <sstream>
#include <functional>
#include <exception>
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Operators/CBinaryOperators.h>
#include <Framework/Foundation/Types/TypeTraits.h>
#include "EIntegerFormat.h"
#include "EPaddingDirection.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	template<typename TValue>
	class IValueFormatter;
	template<typename TIntegerType>
	class CIntegerFormatter;
	template<typename TFloatType>
	class CFloatFormatter;
	template<typename TItemType>
	class CVector;
	class CByteBuffer;
	class CInvalidOperationException;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	class CString final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			struct SSplitIndex final
			{
//----------------------------------------------------------------------------------------------------------------------
				private:
					Size										MPosition;
					Size										MLength;

				public:
					Size GetPosition(void) const noexcept
					{
						return(MPosition);
					}

					Size GetLength(void) const noexcept
					{
						return(MLength);
					}

				public:
					SSplitIndex(Size Position, Size Length)
						: MPosition(Position), MLength(Length)
					{
					}

					~SSplitIndex(void)
					{
					}
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		public:
			static const Size									END;
			static const CString								EMPTY;

		private:
			std::string											MString;

			friend std::ostream& operator<<(std::ostream& Stream, const CString& Value);
			friend std::istream& operator>> (std::istream& Stream, CString& Value);
			friend CString operator+(const CString& Left, const CString& Right);
			friend CString operator+(const CString& Left, const std::string& Right);
			friend CString operator+(const CString& Left, const Char* Right);

		public:
			CString& operator=(const CString& Other);
			CString& operator=(const std::string& Other);
			CString& operator=(const Char* Other);
			CString& operator=(CString&& Other) noexcept;

			template<typename TValue>
			typename std::enable_if<std::is_enum<TValue>::value==true && CBinaryOperators<std::ostream&,TValue&>::HasOperatorBitwiseLeftShift==true,CString&>::type operator=(const TValue& Value)
			{
				try
				{
					std::stringstream							Stream;

					Stream << Value;

					MString=Stream.str();

					return(*this);
				}
				catch(const std::exception& E)
				{
					ThrowException("INVALID STRING OPERATION !",E);
					throw;
				}
			}

			template<typename TValue>
			typename std::enable_if<std::is_enum<TValue>::value==true && CBinaryOperators<std::ostream&,TValue&>::HasOperatorBitwiseLeftShift==false,CString&>::type operator=(const TValue& Value)
			{
				try
				{
					using										TUnderlyingType=typename std::underlying_type<TValue>::type;

					TUnderlyingType								TypedValue=static_cast<TUnderlyingType>(Value);

					std::stringstream							Stream;

					Stream << CString(TypedValue);

					MString=Stream.str();

					return(*this);
				}
				catch(const std::exception& E)
				{
					ThrowException("INVALID STRING OPERATION !",E);
					throw;
				}
			}

			CString& operator+=(Char Other);
			CString& operator+=(const CString& Other);
			CString& operator+=(const std::string& Other);
			CString& operator+=(const Char* Other);
			bool operator==(const CString& Other) const;
			bool operator!=(const CString& Other) const;
			bool operator<(const CString& Other) const;
			bool operator<=(const CString& Other) const;
			bool operator>(const CString& Other) const;
			bool operator>=(const CString& Other) const;
			Char& operator[](Size Index);
			const Char& operator[](Size Index) const;

		private:
			[[noreturn]] static void ThrowException(const CString Message, const std::exception& E);

		private:
			static void FormatParameter(CString& FormattedString, const CString& Parameter);
			static void FormatParameter(CString& FormattedString, CString&& Parameter);
			static void FormatParameter(CString& FormattedString, const std::string& Parameter);
			static void FormatParameter(CString& FormattedString, std::string&& Parameter);
			static void FormatParameter(CString& FormattedString, const Char* Parameter);
			static void FormatParameter(CString& FormattedString, const CObject& Parameter);
			static void FormatParameter(CString& FormattedString, CObject& Parameter);

			template<typename TParameter>
			static typename std::enable_if<STypeTraitIsEnum<TParameter>::RawValue==true && CBinaryOperators<std::ostream&,TParameter&>::HasOperatorBitwiseLeftShift==true && CBinaryOperators<CString&,TParameter&>::HasOperatorBitwiseLeftShift==true,void>::type FormatParameter(CString& FormattedString, TParameter Parameter)
			{
				try
				{
					CString										Value;

					Value << Parameter;

					FormattedString+=Value;
				}
				catch(const std::exception& E)
				{
					ThrowException("INVALID STRING OPERATION !",E);
					throw;
				}
			}

			template<typename TParameter>
			static typename std::enable_if<STypeTraitIsEnum<TParameter>::RawValue==true && CBinaryOperators<std::ostream&,TParameter&>::HasOperatorBitwiseLeftShift==true && CBinaryOperators<CString&,TParameter&>::HasOperatorBitwiseLeftShift==false,void>::type FormatParameter(CString& FormattedString, TParameter Parameter)
			{
				try
				{
					std::stringstream							Stream;

					Stream << Parameter;

					FormattedString+=Stream.str();
				}
				catch(const std::exception& E)
				{
					ThrowException("INVALID STRING OPERATION !",E);
					throw;
				}
			}

			template<typename TParameter>
			static typename std::enable_if<STypeTraitIsEnum<TParameter>::RawValue==true && CBinaryOperators<std::ostream&,TParameter&>::HasOperatorBitwiseLeftShift==false && CBinaryOperators<CString&,TParameter&>::HasOperatorBitwiseLeftShift==true,void>::type FormatParameter(CString& FormattedString, TParameter Parameter)
			{
				try
				{
					CString										Value;

					Value << Parameter;

					FormattedString+=Value;
				}
				catch(const std::exception& E)
				{
					ThrowException("INVALID STRING OPERATION !",E);
					throw;
				}
			}

			template<typename TParameter>
			static typename std::enable_if<STypeTraitIsEnum<TParameter>::RawValue==true && CBinaryOperators<std::ostream&,TParameter&>::HasOperatorBitwiseLeftShift==false && CBinaryOperators<CString&,TParameter&>::HasOperatorBitwiseLeftShift==false,void>::type FormatParameter(CString& FormattedString, TParameter Parameter)
			{
				try
				{
					using										TUnderlyingType=typename std::underlying_type<TParameter>::type;

					TUnderlyingType								TypedParameter=static_cast<TUnderlyingType>(Parameter);

					std::stringstream							Stream;

					Stream << CString(TypedParameter);

					FormattedString+=Stream.str();
				}
				catch(const std::exception& E)
				{
					ThrowException("INVALID STRING OPERATION !",E);
					throw;
				}
			}

			template<typename TParameter>
			static typename std::enable_if<STypeTraitIsEnum<TParameter>::RawValue==false && std::is_same<TParameter,int8>::value==true,void>::type FormatParameter(CString& FormattedString, TParameter Parameter)
			{
				try
				{
					int16										IntegerParameter=static_cast<int16>(Parameter);
					std::stringstream							Stream;

					Stream << IntegerParameter;

					FormattedString+=Stream.str();
				}
				catch(const std::exception& E)
				{
					ThrowException("INVALID STRING OPERATION !",E);
					throw;
				}
			}

			template<typename TParameter>
			static typename std::enable_if<STypeTraitIsEnum<TParameter>::RawValue==false && std::is_same<TParameter,uint8>::value==true,void>::type FormatParameter(CString& FormattedString, TParameter Parameter)
			{
				try
				{
					uint16										IntegerParameter=static_cast<uint16>(Parameter);
					std::stringstream							Stream;

					Stream << IntegerParameter;

					FormattedString+=Stream.str();
				}
				catch(const std::exception& E)
				{
					ThrowException("INVALID STRING OPERATION !",E);
					throw;
				}
			}

			template<typename TParameter>
			static typename std::enable_if<STypeTraitIsEnum<TParameter>::RawValue==false && std::is_same<TParameter,int8>::value==false && std::is_same<TParameter,uint8>::value==false && CBinaryOperators<std::ostream&,TParameter&>::HasOperatorBitwiseLeftShift==true,void>::type FormatParameter(CString& FormattedString, TParameter Parameter)
			{
				try
				{
					std::stringstream							Stream;

					Stream << Parameter;

					FormattedString+=Stream.str();
				}
				catch(const std::exception& E)
				{
					ThrowException("INVALID STRING OPERATION !",E);
					throw;
				}
			}

			template<typename TParameter>
			static typename std::enable_if<STypeTraitIsEnum<TParameter>::RawValue==false && std::is_same<TParameter,int8>::value==false && std::is_same<TParameter,uint8>::value==false && CBinaryOperators<std::ostream&,TParameter&>::HasOperatorBitwiseLeftShift==false,void>::type FormatParameter(CString& FormattedString, TParameter)
			{
				try
				{
					std::stringstream							Stream;

					Stream << CString(typeid(TParameter).name());

					FormattedString+=Stream.str();
				}
				catch(const std::exception& E)
				{
					ThrowException("INVALID STRING OPERATION !",E);
					throw;
				}
			}

			static void InternalFormat(CString&);

			template<typename TFirstParameter, typename... TOtherParameters>
			static void InternalFormat(CString& FormattedString, TFirstParameter&& FirstParameter, TOtherParameters&&... OtherParameters)
			{
				try
				{
					FormatParameter(FormattedString,FUNCTION_FORWARD<TFirstParameter>(FirstParameter));

					InternalFormat(FormattedString,FUNCTION_FORWARD<TOtherParameters>(OtherParameters)...);
				}
				catch(const std::exception& E)
				{
					ThrowException("INVALID STRING OPERATION !",E);
					throw;
				}
			}

		public:
			static const CString& Empty(void);
			static CString ToLowerString(const CString& Value);
			static CString ToUpperString(const CString& Value);
			static CString FromChar(Char Value);
			static CString Format(void);

		public:
			template<typename... TParameters>
			static CString Format(TParameters&&... Parameters)
			{
				try
				{
					CString										String;
					
					InternalFormat(String,FUNCTION_FORWARD<TParameters>(Parameters)...);

					return(String);
				}
				catch(const std::exception& E)
				{
					ThrowException("INVALID STRING OPERATION !",E);
					throw;
				}
			}

			template<typename... TParameters>
			static void FormatString(CString& String, TParameters&&... Parameters)
			{
				try
				{
					InternalFormat(String,FUNCTION_FORWARD<TParameters>(Parameters)...);
				}
				catch(const std::exception& E)
				{
					ThrowException("INVALID STRING OPERATION !",E);
					throw;
				}
			}

			template<typename TValue>
			static typename std::enable_if<std::is_enum<TValue>::value==true && CBinaryOperators<std::ostream&,TValue&>::HasOperatorBitwiseLeftShift==true,CString>::type ConvertFromEnum(const TValue& Value)
			{
				try
				{
					std::stringstream							Stream;

					Stream << Value;

					CString										String=Stream.str();

					return(String);
				}
				catch(const std::exception& E)
				{
					ThrowException("INVALID STRING OPERATION !",E);
					throw;
				}
			}

			template<typename TValue>
			static typename std::enable_if<std::is_enum<TValue>::value==true && CBinaryOperators<std::ostream&,TValue&>::HasOperatorBitwiseLeftShift==false,CString>::type ConvertFromEnum(const TValue& Value)
			{
				try
				{
					using										TUnderlyingType=typename std::underlying_type<TValue>::type;

					TUnderlyingType								TypedValue=static_cast<TUnderlyingType>(Value);

					std::stringstream							Stream;

					Stream << CString(TypedValue);

					CString										String=Stream.str();

					return(String);
				}
				catch(const std::exception& E)
				{
					ThrowException("INVALID STRING OPERATION !",E);
					throw;
				}
			}

		private:
			void CheckIndex(Size Index, bool AllowAfterStringPosition) const;
			void CheckOffset(Size Offset) const;
			Char GetCharacter(Size Index) const;

		public:
			virtual CString ToString(void) const override;
			const std::string& GetString(void) const noexcept;
			std::string& GetString(void) noexcept;
			const Char* GetCharArray(void) const;
			CByteBuffer GetByteBuffer(void) const;
			Size GetLength(void) const;
			Size GetCapacity(void) const;
			void SetCapacity(Size Capacity);
			void Resize(Size NewSize);
			void ShrinkCapacityToFit(void);
			bool IsEmpty(void) const;
			bool IsEmptyOrWhitespace(void) const;
			bool HasStringAt(Size Offset, const CString& String) const;
			Size GetHash(void) const;
			void Clear(void);
			CString& Append(Char Other);
			CString& Append(const CString& Other);
			CString Append(const CString& Other) const;
			CString& Append(const std::string& Other);
			CString& Append(const Char* Other);
			// INSERTS also the NULL CHARACTERS if PRESENT in the C-STRING.
			CString& Append(const Char* Other, Size Length);
			CString& Insert(Char Char, Size Offset);
			CString& Insert(const CString& String, Size Offset);
			CString Insert(const CString& String, Size Offset) const;
			// INSERTS also the NULL CHARACTERS if PRESENT in the C-STRING.
			CString& Insert(const Char* Value, Size Length, Size Offset);
			CString& Erase(Size Offset=0, Size Length=END);
			CString Erase(Size Offset=0, Size Length=END) const;
			CString& EraseAll(Char CharToErase);
			CString EraseAll(Char CharToErase) const;
			bool Contains(Char Char) const;
			bool Contains(const CString& String) const;
			bool StartsWith(const CString& String) const;
			bool EndsWith(const CString& String) const;
			Size FindFirst(Char Char, Size Offset=0) const;
			Size FindFirst(const CString& String, Size Offset=0) const;
			Size FindLast(Char Char, Size Offset=END) const;
			Size FindLast(const CString& String, Size Offset=END) const;
			CString& ReplaceFirst(Char OriginalChar, Char NewChar, Size Offset=0);
			CString ReplaceFirst(Char OriginalChar, Char NewChar, Size Offset=0) const;
			CString& ReplaceFirst(const CString& OriginalString, const CString& NewString, Size Offset=0);
			CString ReplaceFirst(const CString& OriginalString, const CString& NewString, Size Offset=0) const;
			CString& ReplaceLast(Char OriginalChar, Char NewChar, Size Offset=END);
			CString ReplaceLast(Char OriginalChar, Char NewChar, Size Offset=END) const;
			CString& ReplaceLast(const CString& OriginalString, const CString& NewString, Size Offset=END);
			CString ReplaceLast(const CString& OriginalString, const CString& NewString, Size Offset=END) const;
			CString& ReplaceAll(Char OriginalChar, Char NewChar);
			CString ReplaceAll(Char OriginalChar, Char NewChar) const;
			CString& ReplaceAll(const CString& OriginalString, const CString& NewChar);
			CString ReplaceAll(const CString& OriginalString, const CString& NewChar) const;
			bool LexicographicallyEqual(const CString& StringToCompare, bool CaseSensitive=true) const;
			int32 LexicographicalCompare(const CString& StringToCompare, bool CaseSensitive=true) const;
			CString SubString(Size Offset=0, Size Length=END) const;
			CVector<CString> Split(Char Separator, bool RemoveEmptyEntries=true) const;
			CVector<CString> Split(const CString& Separator, bool RemoveEmptyEntries=true) const;
			CVector<SSplitIndex> SplitToIndexes(Char Separator, bool RemoveEmptyEntries=true) const;
			CVector<SSplitIndex> SplitToIndexes(const CString& Separator, bool RemoveEmptyEntries=true) const;
			CString& Trim(void);
			CString Trim(void) const;
			CString& Trim(const CVector<Char>& CharactersToTrim);
			CString Trim(const CVector<Char>& CharactersToTrim) const;
			CString& TrimStart(const CVector<Char>& CharactersToTrim);
			CString TrimStart(const CVector<Char>& CharactersToTrim) const;
			CString& TrimEnd(const CVector<Char>& CharactersToTrim);
			CString TrimEnd(const CVector<Char>& CharactersToTrim) const;
			CString& PadLeft(Size Width, Char Character);
			CString PadLeft(Size Width, Char Character) const;
			CString& PadRight(Size Width, Char Character);
			CString PadRight(Size Width, Char Character) const;
			CString& ToLower(void);
			CString ToLower(void) const;
			CString& ToUpper(void);
			CString ToUpper(void) const;
			std::string::iterator begin(void);
			std::string::iterator end(void);
			std::string::const_iterator begin(void) const;
			std::string::const_iterator end(void) const;

		public:
			CString(void);
			CString(const CString& Other);
			CString(CString&& Other) noexcept;
			CString(const std::string& Value);
			CString(std::string&& Value);
			CString(const CByteBuffer& Value);
			CString(const Char* Value);
			// INSERTS also the NULL CHARACTERS if PRESENT in the C-STRING.
			CString(const Char* Value, Size Length);
			CString(const Char* From, const Char* To);

			template<class TIterator>
			CString(TIterator First, TIterator Last)
				: MString(First,Last)
			{
			}

			CString(Size Width, Char Value);
			explicit CString(bool Value);
			explicit CString(int8 Value);
			explicit CString(int8 Value, const IValueFormatter<int8>& Formatter);
			explicit CString(int8 Value, EIntegerFormat IntegerFormat, Size MinimalWidth=0, bool PadWithZeros=false);
			explicit CString(int16 Value);
			explicit CString(int16 Value, const IValueFormatter<int16>& Formatter);
			explicit CString(int16 Value, EIntegerFormat IntegerFormat, Size MinimalWidth=0, bool PadWithZeros=false);
			explicit CString(int32 Value);
			explicit CString(int32 Value, const IValueFormatter<int32>& Formatter);
			explicit CString(int32 Value, EIntegerFormat IntegerFormat, Size MinimalWidth=0, bool PadWithZeros=false);
			explicit CString(int64 Value);
			explicit CString(int64 Value, const IValueFormatter<int64>& Formatter);
			explicit CString(int64 Value, EIntegerFormat IntegerFormat, Size MinimalWidth=0, bool PadWithZeros=false);
			explicit CString(uint8 Value);
			explicit CString(uint8 Value, const IValueFormatter<uint8>& Formatter);
			explicit CString(uint8 Value, EIntegerFormat IntegerFormat, Size MinimalWidth=0, bool PadWithZeros=false);
			explicit CString(uint16 Value);
			explicit CString(uint16 Value, const IValueFormatter<uint16>& Formatter);
			explicit CString(uint16 Value, EIntegerFormat IntegerFormat, Size MinimalWidth=0, bool PadWithZeros=false);
			explicit CString(uint32 Value);
			explicit CString(uint32 Value, const IValueFormatter<uint32>& Formatter);
			explicit CString(uint32 Value, EIntegerFormat IntegerFormat, Size MinimalWidth=0, bool PadWithZeros=false);
			explicit CString(uint64 Value);
			explicit CString(uint64 Value, const IValueFormatter<uint64>& Formatter);
			explicit CString(uint64 Value, EIntegerFormat IntegerFormat, Size MinimalWidth=0, bool PadWithZeros=false);
			explicit CString(float32 Value);
			explicit CString(float32 Value, const IValueFormatter<float32>& Formatter);
			explicit CString(float32 Value, Size Precision, Size MinimalWidth=0, Char PaddingCharacter=' ', EPaddingDirection PaddingDirection=EPaddingDirection::E_INTERNAL);
			explicit CString(float64 Value);
			explicit CString(float64 Value, const IValueFormatter<float64>& Formatter);
			explicit CString(float64 Value, Size Precision, Size MinimalWidth=0, Char PaddingCharacter=' ', EPaddingDirection PaddingDirection=EPaddingDirection::E_INTERNAL);
			explicit CString(float80 Value);
			explicit CString(float80 Value, const IValueFormatter<float80>& Formatter);
			explicit CString(float80 Value, Size Precision, Size MinimalWidth=0, Char PaddingCharacter=' ', EPaddingDirection PaddingDirection=EPaddingDirection::E_INTERNAL);

			template<typename TValue>
			CString(const TValue& Value, const IValueFormatter<TValue>& Formatter)
				: MString(Formatter.ConvertToString(Value).GetString())
			{
			}

			CString(std::initializer_list<Char> Characters);

			virtual ~CString(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString operator+(const CString& Left, const CString& Right);
	CString operator+(const CString& Left, const std::string& Right);
	CString operator+(const CString& Left, const Char* Right);
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	std::ostream& operator<<(std::ostream& Stream, const CString& Value);
	std::istream& operator>>(std::istream& Stream, CString& Value);
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString operator"" _S(const Char* Value, Size ValueSize);
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString ToHexaDecimalString(int8 Value, bool AddPrefix=false, Size MinimalWidth=sizeof(int8)*2, bool PadWithZeros=true);
	CString ToHexaDecimalString(int16 Value, bool AddPrefix=false, Size MinimalWidth=sizeof(int16)*2, bool PadWithZeros=true);
	CString ToHexaDecimalString(int32 Value, bool AddPrefix=false, Size MinimalWidth=sizeof(int32)*2, bool PadWithZeros=true);
	CString ToHexaDecimalString(int64 Value, bool AddPrefix=false, Size MinimalWidth=sizeof(int64)*2, bool PadWithZeros=true);
	CString ToHexaDecimalString(uint8 Value, bool AddPrefix=false, Size MinimalWidth=sizeof(uint8)*2, bool PadWithZeros=true);
	CString ToHexaDecimalString(uint16 Value, bool AddPrefix=false, Size MinimalWidth=sizeof(uint16)*2, bool PadWithZeros=true);
	CString ToHexaDecimalString(uint32 Value, bool AddPrefix=false, Size MinimalWidth=sizeof(uint32)*2, bool PadWithZeros=true);
	CString ToHexaDecimalString(uint64 Value, bool AddPrefix=false, Size MinimalWidth=sizeof(uint64)*2, bool PadWithZeros=true);
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------