//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Exceptions/CParserException.h>
#include <Framework/Foundation/Parsing/CParserByteBufferReader.h>
#include <Framework/Foundation/Parsing/CParserByteBufferWriter.h>
#include <Framework/Foundation/Parsing/CParserHelper.h>
#include <Framework/Foundation/Types/TypeTraits.h>
#include "CParserPacketParseConstructor.h"
#include "CParserParameterCollection.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CParserPacket : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		protected:
			template<typename TPointerType>
			static void CheckNotNULL(CSharedPointer<TPointerType> Value, const Char* ValueName)
			{
				CParserHelper::CheckNotNULL<TPointerType>(Value,ValueName);
			}

			static void CheckLength(Size ActualLength, Size ExpectedLength);
			static void CheckLength(const CParserByteBufferReader& Reader, Size ExpectedLength);

			template<typename TEnumType>
			static void CheckEnumValue(TEnumType Value, const Char* ValueName)
			{
				static_assert(STypeTraitIsEnum<TEnumType>::Value()==true,"METHOD can NOT be used for NON ENUM TYPES !");

				CParserHelper::CheckEnumValue<TEnumType>(Value,ValueName);
			}

			template<typename TEnumType>
			static void CheckEnumRange(TEnumType Value, TEnumType MinValue, TEnumType MaxValue, const Char* ValueName)
			{
				static_assert(STypeTraitIsEnum<TEnumType>::Value()==true,"METHOD can NOT be used for NON ENUM TYPES !");

				CParserHelper::CheckEnumRange<TEnumType>(Value,MinValue,MaxValue,ValueName);
			}

			template<typename TAritmeticType>
			static void CheckArithmeticRange(TAritmeticType Value, TAritmeticType MinValue, TAritmeticType MaxValue, const Char* ValueName)
			{
				static_assert(STypeTraitIsNumericType<TAritmeticType>::Value()==true,"METHOD can NOT be used for NON ARITHMETIC TYPES !");

				CParserHelper::CheckArithmeticRange<TAritmeticType>(Value,MinValue,MaxValue,ValueName);
			}

		protected:
			virtual CString InternalToString(void) const=0;
			virtual bool InternalEquals(const CParserPacket& Other) const=0;
			virtual void InternalCreatePacket(CParserByteBufferWriter& Writer, CParserParameterCollection& Parameters)=0;
			virtual void InternalParsePacket(CParserByteBufferReader& Reader, CParserParameterCollection& Parameters)=0;

		public:
			virtual CString ToString(void) const override;
			bool Equals(const CParserPacket& Other) const;
			void CreatePacket(CParserByteBufferWriter& Writer, CParserParameterCollection& Parameters);
			void ParsePacket(CParserByteBufferReader& Reader, CParserParameterCollection& Parameters);

		public:
			CParserPacket(void);
			virtual ~CParserPacket(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPParserPacket=CSharedPointer<CParserPacket>;
	using														CCSPParserPacket=CSharedPointer<const CParserPacket>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------