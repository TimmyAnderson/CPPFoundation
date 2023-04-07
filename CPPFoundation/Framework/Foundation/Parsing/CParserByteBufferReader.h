//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Objects/CObject.h>
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
	class CParserByteBufferReader final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CByteBuffer											MBuffer;
			Size												MPosition;

		public:
			CParserByteBufferReader& operator=(const CParserByteBufferReader& Other);
			CParserByteBufferReader& operator=(CParserByteBufferReader&& Other) noexcept;
			uint8& operator[](Size Index);
			uint8 operator[](Size Index) const;
			CParserByteBufferReader& operator++(void);
			CParserByteBufferReader& operator+=(Size Length);

		public:
			virtual CString ToString(void) const override;
			const CByteBuffer& GetBuffer(void) const noexcept;
			Size GetPosition(void) const;
			Size GetLength(void) const;
			Size GetTotalLength(void) const;
			bool HasLength(Size Length) const;
			void CheckLength(Size Length) const;
			void CheckLength(Size Length, const CString& ExceptionMessage) const;
			void CheckLength(Size Length, const CException& Exception) const;
			uint8 GetActual(void) const;
			uint8 GetActual(Size Index) const;
			uint8 GetActualAndInc(void);
			CByteBuffer GetActualArray(Size Length) const;
			CByteBuffer GetActualArrayAndInc(Size Length);
			CByteBuffer GetRemainingArray(void) const;
			CByteBuffer GetRemainingArrayAndInc(void);
			void Insert(uint8 Item, Size Index);
			void Erase(Size Index);
			void Erase(Size Index, Size Length);

		public:
			int8 DeserializeInt8(EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS, bool IncrementPosition=true);
			uint8 DeserializeUInt8(EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS, bool IncrementPosition=true);
			int16 DeserializeInt16(EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS, bool IncrementPosition=true);
			uint16 DeserializeUInt16(EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS, bool IncrementPosition=true);
			int32 DeserializeInt32(EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS, bool IncrementPosition=true);
			uint32 DeserializeUInt32(EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS, bool IncrementPosition=true);
			int64 DeserializeInt64(EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS, bool IncrementPosition=true);
			uint64 DeserializeUInt64(EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS, bool IncrementPosition=true);
			float32 DeserializeFloat32(EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS, bool IncrementPosition=true);
			float64 DeserializeFloat64(EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS, bool IncrementPosition=true);
			float80 DeserializeFloat80(EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS, bool IncrementPosition=true);
			Size DeserializeSize(EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS, bool IncrementPosition=true);

			template<typename TEnumType>
			TEnumType DeserializeEnum(EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS, bool IncrementPosition=true)
			{
				static_assert(STypeTraitIsEnum<TEnumType>::Value()==true,"METHOD can NOT be used for NON ENUM TYPES !");

				TEnumType										Value=CParserHelper::DeserializeEnum<TEnumType>(MBuffer,MPosition,Endianness);

				if (IncrementPosition==true)
				{
					MPosition+=sizeof(TEnumType);
				}

				return(Value);
			}

			template<typename TEnumType>
			TEnumType DeserializeEnumAndCheck(const Char* ValueName, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS, bool IncrementPosition=true)
			{
				static_assert(STypeTraitIsEnum<TEnumType>::Value()==true,"METHOD can NOT be used for NON ENUM TYPES !");

				TEnumType										Value=CParserHelper::DeserializeEnum<TEnumType>(MBuffer,MPosition,Endianness);

				if (IncrementPosition==true)
				{
					MPosition+=sizeof(TEnumType);
				}

				CParserHelper::CheckEnumValue<TEnumType>(Value,ValueName);

				return(Value);
			}

		public:
			CParserByteBufferReader(void);
			CParserByteBufferReader(const CByteBuffer& Buffer);
			CParserByteBufferReader(CByteBuffer&& Buffer);
			CParserByteBufferReader(const CParserByteBufferReader& Other);
			CParserByteBufferReader(CParserByteBufferReader&& Other) noexcept;
			virtual ~CParserByteBufferReader(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------