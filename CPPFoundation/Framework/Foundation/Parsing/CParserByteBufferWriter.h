//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Collections/CArray.h>
#include <Framework/Foundation/Collections/CByteBuffer.h>
#include <Framework/Foundation/Types/TypeTraits.h>
#include <Framework/Platform/Global/CConstants.h>
#include "CParserHelper.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CParserByteBufferWriter final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CByteBuffer											MBuffer;

		public:
			CParserByteBufferWriter& operator=(const CParserByteBufferWriter& Other);
			CParserByteBufferWriter& operator=(CParserByteBufferWriter&& Other) noexcept;
			uint8& operator[](Size Index);
			uint8 operator[](Size Index) const;

		public:
			virtual CString ToString(void) const override;
			CByteBuffer& GetBuffer(void) noexcept;
			const CByteBuffer& GetBuffer(void) const noexcept;
			Size GetLength(void) const;
			void Add(uint8 Value);
			void Add(const CByteBuffer& Buffer);
			void Add(CByteBuffer&& Buffer);
			void Add(const CParserByteBufferWriter& Writer);
			void Add(uint8* Buffer, Size Length);
			void Insert(uint8 Item, Size Index);
			void Erase(Size Index);
			void Erase(Size Index, Size Length);

		public:
			void SerializeInt8(int8 Value, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			void SerializeUInt8(uint8 Value, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			void SerializeInt16(int16 Value, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			void SerializeUInt16(uint16 Value, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			void SerializeInt32(int32 Value, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			void SerializeUInt32(uint32 Value, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			void SerializeInt64(int64 Value, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			void SerializeUInt64(uint64 Value, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			void SerializeFloat32(float32 Value, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			void SerializeFloat64(float64 Value, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			void SerializeFloat80(float80 Value, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			void SerializeSize(Size Value, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);

			template<typename TEnumType>
			void SerializeEnum(TEnumType Value, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				static_assert(STypeTraitIsEnum<TEnumType>::Value()==true,"METHOD can NOT be used for NON ENUM TYPES !");

				Size											Length=MBuffer.GetLength();

				MBuffer.Add(uint8(0),sizeof(Value));

				CParserHelper::SerializeEnum<TEnumType>(MBuffer,Value,Length,Endianness);
			}

		public:
			CParserByteBufferWriter(void);
			CParserByteBufferWriter(const CParserByteBufferWriter& Other);
			CParserByteBufferWriter(CParserByteBufferWriter&& Other) noexcept;
			virtual ~CParserByteBufferWriter(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------