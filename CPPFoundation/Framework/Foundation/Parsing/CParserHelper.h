//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Types/Types.h>
#include <Framework/Foundation/Collections/CArray.h>
#include <Framework/Foundation/Collections/CByteBuffer.h>
#include <Framework/Foundation/Exceptions/CParserException.h>
#include <Framework/Foundation/Types/TypeTraits.h>
#include <Framework/Platform/Global/CConstants.h>
#include "EParserEndianness.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CParserHelper final
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			static const Size									NIBBLE_SIZE_IN_BITS;
			static const Size									NIBBLE_MASK;
			static const Size									BCD_MIN_VALUE;
			static const Size									BCD_MAX_VALUE;
			static const Size									BCD_MIN_NUMERIC_VALUE;
			static const Size									BCD_MAX_NUMERIC_VALUE;
			static const Size									BCD_TO_DECADIC_VALUE_CONVERSION;

		public:
			static const Size									BITS_PER_BYTE;
			static const Size									BYTE_MAGNITUDE;

		private:
			static void CheckLength(Size BufferLength, Size Index, Size Length);
			static void CheckLength(const CByteBuffer& Buffer, Size Index, Size Length);
			static void GetBitsCheckArguments(Size StartPositionInBits, Size LengthInBits, Size BitLength);

		private:
			template<typename TType>
			static void InternalSerialize(uint8* Buffer, Size BufferLength, TType Value, Size Index, EParserEndianness Endianness)
			{
				const Size										LENGTH=sizeof(TType);

				CheckLength(BufferLength,Index,LENGTH);

				uint8*											Pointer=reinterpret_cast<uint8*>(&Value);
				uint8											Data[LENGTH];

				for(Size LocalIndex=0;LocalIndex<LENGTH;LocalIndex++)
				{
					Data[LocalIndex]=Pointer[LocalIndex];
				}

				if (CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS!=Endianness)
				{
					for(Size LocalIndex=0;LocalIndex<(LENGTH/2);LocalIndex++)
					{
						uint8									Temp=Data[LocalIndex];

						Data[LocalIndex]=Data[LENGTH-LocalIndex-1];
						Data[LENGTH-LocalIndex-1]=Temp;
					}
				}

				for(Size LocalIndex=0;LocalIndex<LENGTH;LocalIndex++)
				{
					Buffer[Index+LocalIndex]=Data[LocalIndex];
				}
			}

			template<typename TType>
			static void InternalSerialize(CByteBuffer& Buffer, TType Value, Size Index, EParserEndianness Endianness)
			{
				constexpr Size									LENGTH=sizeof(TType);

				CheckLength(Buffer,Index,LENGTH);

				uint8*											Pointer=reinterpret_cast<uint8*>(&Value);
				uint8											Data[LENGTH];

				for(Size LocalIndex=0;LocalIndex<LENGTH;LocalIndex++)
				{
					Data[LocalIndex]=Pointer[LocalIndex];
				}

				if (CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS!=Endianness)
				{
					for(Size LocalIndex=0;LocalIndex<(LENGTH/2);LocalIndex++)
					{
						uint8									Temp=Data[LocalIndex];

						Data[LocalIndex]=Data[LENGTH-LocalIndex-1];
						Data[LENGTH-LocalIndex-1]=Temp;
					}
				}

				for(Size LocalIndex=0;LocalIndex<LENGTH;LocalIndex++)
				{
					Buffer[Index+LocalIndex]=Data[LocalIndex];
				}
			}

			template<typename TType, Size ARRAY_SIZE>
			static void InternalSerializeArray(uint8* Buffer, Size BufferLength, const CArray<TType,ARRAY_SIZE>& Value, Size Index, EParserEndianness Endianness)
			{
				const Size										ITEM_LENGTH=sizeof(TType);
				const Size										LENGTH=ITEM_LENGTH*ARRAY_SIZE;

				CheckLength(BufferLength,Index,LENGTH);

				for(Size ItemIndex=0,StartIndex=Index;ItemIndex<ARRAY_SIZE;ItemIndex++,StartIndex+=ITEM_LENGTH)
				{
					InternalSerialize<TType>(Buffer,BufferLength,Value[ItemIndex],StartIndex,Endianness);
				}
			}

			template<typename TType, Size ARRAY_SIZE>
			static void InternalSerializeArray(CByteBuffer& Buffer, const CArray<TType,ARRAY_SIZE>& Value, Size Index, EParserEndianness Endianness)
			{
				const Size										ITEM_LENGTH=sizeof(TType);
				const Size										LENGTH=ITEM_LENGTH*ARRAY_SIZE;

				CheckLength(Buffer,Index,LENGTH);

				for(Size ItemIndex=0,StartIndex=Index;ItemIndex<ARRAY_SIZE;ItemIndex++,StartIndex+=ITEM_LENGTH)
				{
					InternalSerialize<TType>(Buffer,Value[ItemIndex],StartIndex,Endianness);
				}
			}

			template<typename TType>
			static TType InternalDeserialize(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness)
			{
				const Size										LENGTH=sizeof(TType);

				CheckLength(BufferLength,Index,LENGTH);

				uint8											Data[LENGTH];

				for(Size LocalIndex=0;LocalIndex<LENGTH;LocalIndex++)
				{
					Data[LocalIndex]=Buffer[Index+LocalIndex];
				}

				if (CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS!=Endianness)
				{
					for(Size LocalIndex=0;LocalIndex<(LENGTH/2);LocalIndex++)
					{
						uint8									Temp=Data[LocalIndex];

						Data[LocalIndex]=Data[LENGTH-LocalIndex-1];
						Data[LENGTH-LocalIndex-1]=Temp;
					}
				}

				TType*											Pointer=reinterpret_cast<TType*>(Data);
				TType											Value=*Pointer;

				return(Value);
			}

			template<typename TType>
			static TType InternalDeserialize(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness)
			{
				constexpr Size									LENGTH=sizeof(TType);

				CheckLength(Buffer,Index,LENGTH);

				uint8											Data[LENGTH];

				Buffer.Copy(&Data[0],Index,LENGTH);

				if (CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS!=Endianness)
				{
					for(Size LocalIndex=0;LocalIndex<(LENGTH/2);LocalIndex++)
					{
						uint8									Temp=Data[LocalIndex];

						Data[LocalIndex]=Data[LENGTH-LocalIndex-1];
						Data[LENGTH-LocalIndex-1]=Temp;
					}
				}

				TType*											Pointer=reinterpret_cast<TType*>(Data);
				TType											Value=*Pointer;

				return(Value);
			}

			template<typename TType, Size ARRAY_SIZE>
			static CArray<TType,ARRAY_SIZE> InternalDeserializeArray(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness)
			{
				const Size										ITEM_LENGTH=sizeof(TType);
				const Size										LENGTH=ITEM_LENGTH*ARRAY_SIZE;

				CheckLength(BufferLength,Index,LENGTH);

				CArray<TType,ARRAY_SIZE>						Value;

				for(Size ItemIndex=0,StartIndex=Index;ItemIndex<ARRAY_SIZE;ItemIndex++,StartIndex+=ITEM_LENGTH)
				{
					TType										Item=InternalDeserialize<TType>(Buffer,BufferLength,StartIndex,Endianness);

					Value[ItemIndex]=Item;
				}

				return(Value);
			}

			template<typename TType, Size ARRAY_SIZE>
			static CArray<TType,ARRAY_SIZE> InternalDeserializeArray(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness)
			{
				const Size										ITEM_LENGTH=sizeof(TType);
				const Size										LENGTH=ITEM_LENGTH*ARRAY_SIZE;

				CheckLength(Buffer,Index,LENGTH);

				CArray<TType,ARRAY_SIZE>						Value;

				for(Size ItemIndex=0,StartIndex=Index;ItemIndex<ARRAY_SIZE;ItemIndex++,StartIndex+=ITEM_LENGTH)
				{
					TType										Item=InternalDeserialize<TType>(Buffer,StartIndex,Endianness);

					Value[ItemIndex]=Item;
				}

				return(Value);
			}

		private:
			template<typename TType>
			static TType InternalGetBits(TType Value, Size StartPositionInBits, Size LengthInBits)
			{
				const Size										BIT_SIZE=sizeof(TType)*BITS_PER_BYTE;

				GetBitsCheckArguments(StartPositionInBits,LengthInBits,BIT_SIZE);

				if (LengthInBits!=BIT_SIZE)
				{
					TType										NewValue=Value;

					NewValue=static_cast<TType>(NewValue >> StartPositionInBits);

					TType										Mask=CPrimitiveType<TType>::Max();

					Mask=static_cast<TType>(Mask << LengthInBits);
					Mask=static_cast<TType>(~Mask);
					NewValue&=Mask;

					return(NewValue);
				}
				else
				{
					return(Value);
				}
			}

			template<typename TType>
			static TType InternalOrBits(TType Value, TType OrValue, Size StartPositionInBits, Size LengthInBits)
			{
				using											UnsignedType=typename std::make_unsigned<TType>::type;

				const Size										BIT_SIZE=sizeof(TType)*BITS_PER_BYTE;

				GetBitsCheckArguments(StartPositionInBits,LengthInBits,BIT_SIZE);

				if (LengthInBits!=BIT_SIZE)
				{
					TType										NewValue=Value;
					UnsignedType								MaskBase=CPrimitiveType<UnsignedType>::Max();
					TType										Mask=static_cast<TType>(MaskBase>>(BIT_SIZE-LengthInBits)<<StartPositionInBits);
					TType										NewSetValue=static_cast<TType>(OrValue<<StartPositionInBits);

					NewSetValue&=Mask;

					NewValue=static_cast<TType>((NewValue | NewSetValue));

					return(NewValue);
				}
				else
				{
					TType										NewValue=static_cast<TType>(Value | OrValue);

					return(NewValue);
				}
			}
		
			template<typename TType>
			static TType InternalSetBits(TType Value, TType SetValue, Size StartPositionInBits, Size LengthInBits)
			{
				using											UnsignedType=typename std::make_unsigned<TType>::type;

				const Size										BIT_SIZE=sizeof(TType)*BITS_PER_BYTE;

				GetBitsCheckArguments(StartPositionInBits,LengthInBits,BIT_SIZE);

				if (LengthInBits!=BIT_SIZE)
				{
					TType										NewValue=Value;
					UnsignedType								MaskBase=CPrimitiveType<UnsignedType>::Max();
					TType										Mask1=static_cast<TType>(MaskBase>>(BIT_SIZE-LengthInBits)<<StartPositionInBits);
					TType										Mask2=static_cast<TType>(~Mask1);

					NewValue&=Mask2;

					TType										NewSetValue=static_cast<TType>(SetValue<<StartPositionInBits);

					NewSetValue&=Mask1;

					NewValue=static_cast<TType>((NewValue | NewSetValue));

					return(NewValue);
				}
				else
				{
					return(SetValue);
				}
			}

			template<typename TType>
			static TType InternalGetLengthInBytes(TType LengthInBits)
			{
				TType											BitsPerByte=static_cast<TType>(BITS_PER_BYTE);
				TType											LengthInBytes=static_cast<TType>(LengthInBits/BitsPerByte);
				
				if ((LengthInBits % BitsPerByte)!=0)
				{
					LengthInBytes++;
				}

				return(LengthInBytes);
			}

		public:
			static void SerializeInt8(uint8* Buffer, Size BufferLength, int8 Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static void SerializeUInt8(uint8* Buffer, Size BufferLength, uint8 Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static void SerializeInt16(uint8* Buffer, Size BufferLength, int16 Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static void SerializeUInt16(uint8* Buffer, Size BufferLength, uint16 Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static void SerializeInt32(uint8* Buffer, Size BufferLength, int32 Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static void SerializeUInt32(uint8* Buffer, Size BufferLength, uint32 Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static void SerializeInt64(uint8* Buffer, Size BufferLength, int64 Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static void SerializeUInt64(uint8* Buffer, Size BufferLength, uint64 Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static void SerializeFloat32(uint8* Buffer, Size BufferLength, float32 Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static void SerializeFloat64(uint8* Buffer, Size BufferLength, float64 Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static void SerializeFloat80(uint8* Buffer, Size BufferLength, float80 Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static void SerializeSize(uint8* Buffer, Size BufferLength, Size Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);

			template<typename TEnumType>
			static void SerializeEnum(uint8* Buffer, Size BufferLength, TEnumType Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				static_assert(STypeTraitIsEnum<TEnumType>::Value()==true,"METHOD can NOT be used for NON ENUM TYPES !");

				InternalSerialize<TEnumType>(Buffer,BufferLength,Value,Index,Endianness);
			}

		public:
			static void SerializeInt8(CByteBuffer& Buffer, int8 Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static void SerializeUInt8(CByteBuffer& Buffer, uint8 Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static void SerializeInt16(CByteBuffer& Buffer, int16 Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static void SerializeUInt16(CByteBuffer& Buffer, uint16 Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static void SerializeInt32(CByteBuffer& Buffer, int32 Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static void SerializeUInt32(CByteBuffer& Buffer, uint32 Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static void SerializeInt64(CByteBuffer& Buffer, int64 Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static void SerializeUInt64(CByteBuffer& Buffer, uint64 Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static void SerializeFloat32(CByteBuffer& Buffer, float32 Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static void SerializeFloat64(CByteBuffer& Buffer, float64 Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static void SerializeFloat80(CByteBuffer& Buffer, float80 Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static void SerializeSize(CByteBuffer& Buffer, Size Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);

			template<typename TEnumType>
			static void SerializeEnum(CByteBuffer& Buffer, TEnumType Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				static_assert(STypeTraitIsEnum<TEnumType>::Value()==true,"METHOD can NOT be used for NON ENUM TYPES !");

				InternalSerialize<TEnumType>(Buffer,Value,Index,Endianness);
			}


		public:
			template<Size ARRAY_SIZE>
			static void SerializeArrayInt8(uint8* Buffer, Size BufferLength, const CArray<int8,ARRAY_SIZE>& Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				InternalSerializeArray<int8,ARRAY_SIZE>(Buffer,BufferLength,Value,Index,Endianness);
			}

			template<Size ARRAY_SIZE>
			static void SerializeArrayUInt8(uint8* Buffer, Size BufferLength, const CArray<uint8,ARRAY_SIZE>& Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				InternalSerializeArray<uint8,ARRAY_SIZE>(Buffer,BufferLength,Value,Index,Endianness);
			}

			template<Size ARRAY_SIZE>
			static void SerializeArrayInt16(uint8* Buffer, Size BufferLength, const CArray<int16,ARRAY_SIZE>& Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				InternalSerializeArray<int16,ARRAY_SIZE>(Buffer,BufferLength,Value,Index,Endianness);
			}

			template<Size ARRAY_SIZE>
			static void SerializeArrayUInt16(uint8* Buffer, Size BufferLength, const CArray<uint16,ARRAY_SIZE>& Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				InternalSerializeArray<uint16,ARRAY_SIZE>(Buffer,BufferLength,Value,Index,Endianness);
			}

			template<Size ARRAY_SIZE>
			static void SerializeArrayInt32(uint8* Buffer, Size BufferLength, const CArray<int32,ARRAY_SIZE>& Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				InternalSerializeArray<int32,ARRAY_SIZE>(Buffer,BufferLength,Value,Index,Endianness);
			}

			template<Size ARRAY_SIZE>
			static void SerializeArrayUInt32(uint8* Buffer, Size BufferLength, const CArray<uint32,ARRAY_SIZE>& Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				InternalSerializeArray<uint32,ARRAY_SIZE>(Buffer,BufferLength,Value,Index,Endianness);
			}

			template<Size ARRAY_SIZE>
			static void SerializeArrayInt64(uint8* Buffer, Size BufferLength, const CArray<int64,ARRAY_SIZE>& Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				InternalSerializeArray<int64,ARRAY_SIZE>(Buffer,BufferLength,Value,Index,Endianness);
			}

			template<Size ARRAY_SIZE>
			static void SerializeArrayUInt64(uint8* Buffer, Size BufferLength, const CArray<uint64,ARRAY_SIZE>& Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				InternalSerializeArray<uint64,ARRAY_SIZE>(Buffer,BufferLength,Value,Index,Endianness);
			}

			template<Size ARRAY_SIZE>
			static void SerializeArrayFloat32(uint8* Buffer, Size BufferLength, const CArray<float32,ARRAY_SIZE>& Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				InternalSerializeArray<float32,ARRAY_SIZE>(Buffer,BufferLength,Value,Index,Endianness);
			}

			template<Size ARRAY_SIZE>
			static void SerializeArrayFloat64(uint8* Buffer, Size BufferLength, const CArray<float64,ARRAY_SIZE>& Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				InternalSerializeArray<float64,ARRAY_SIZE>(Buffer,BufferLength,Value,Index,Endianness);
			}

			template<Size ARRAY_SIZE>
			static void SerializeArrayFloat80(uint8* Buffer, Size BufferLength, const CArray<float80,ARRAY_SIZE>& Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				InternalSerializeArray<float80,ARRAY_SIZE>(Buffer,BufferLength,Value,Index,Endianness);
			}

			template<Size ARRAY_SIZE>
			static void SerializeArraySize(uint8* Buffer, Size BufferLength, const CArray<Size,ARRAY_SIZE>& Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				InternalSerializeArray<Size,ARRAY_SIZE>(Buffer,BufferLength,Value,Index,Endianness);
			}

			template<typename TEnumType, Size ARRAY_SIZE>
			static void SerializeArrayEnum(uint8* Buffer, Size BufferLength, const CArray<TEnumType,ARRAY_SIZE>& Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				static_assert(STypeTraitIsEnum<TEnumType>::Value()==true,"METHOD can NOT be used for NON ENUM TYPES !");

				InternalSerializeArray<TEnumType,ARRAY_SIZE>(Buffer,BufferLength,Value,Index,Endianness);
			}

		public:
			template<Size ARRAY_SIZE>
			static void SerializeArrayInt8(CByteBuffer& Buffer, const CArray<int8,ARRAY_SIZE>& Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				InternalSerializeArray<int8,ARRAY_SIZE>(Buffer,Value,Index,Endianness);
			}

			template<Size ARRAY_SIZE>
			static void SerializeArrayUInt8(CByteBuffer& Buffer, const CArray<uint8,ARRAY_SIZE>& Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				InternalSerializeArray<uint8,ARRAY_SIZE>(Buffer,Value,Index,Endianness);
			}

			template<Size ARRAY_SIZE>
			static void SerializeArrayInt16(CByteBuffer& Buffer, const CArray<int16,ARRAY_SIZE>& Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				InternalSerializeArray<int16,ARRAY_SIZE>(Buffer,Value,Index,Endianness);
			}

			template<Size ARRAY_SIZE>
			static void SerializeArrayUInt16(CByteBuffer& Buffer, const CArray<uint16,ARRAY_SIZE>& Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				InternalSerializeArray<uint16,ARRAY_SIZE>(Buffer,Value,Index,Endianness);
			}

			template<Size ARRAY_SIZE>
			static void SerializeArrayInt32(CByteBuffer& Buffer, const CArray<int32,ARRAY_SIZE>& Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				InternalSerializeArray<int32,ARRAY_SIZE>(Buffer,Value,Index,Endianness);
			}

			template<Size ARRAY_SIZE>
			static void SerializeArrayUInt32(CByteBuffer& Buffer, const CArray<uint32,ARRAY_SIZE>& Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				InternalSerializeArray<uint32,ARRAY_SIZE>(Buffer,Value,Index,Endianness);
			}

			template<Size ARRAY_SIZE>
			static void SerializeArrayInt64(CByteBuffer& Buffer, const CArray<int64,ARRAY_SIZE>& Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				InternalSerializeArray<int64,ARRAY_SIZE>(Buffer,Value,Index,Endianness);
			}

			template<Size ARRAY_SIZE>
			static void SerializeArrayUInt64(CByteBuffer& Buffer, const CArray<uint64,ARRAY_SIZE>& Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				InternalSerializeArray<uint64,ARRAY_SIZE>(Buffer,Value,Index,Endianness);
			}

			template<Size ARRAY_SIZE>
			static void SerializeArrayFloat32(CByteBuffer& Buffer, const CArray<float32,ARRAY_SIZE>& Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				InternalSerializeArray<float32,ARRAY_SIZE>(Buffer,Value,Index,Endianness);
			}

			template<Size ARRAY_SIZE>
			static void SerializeArrayFloat64(CByteBuffer& Buffer, const CArray<float64,ARRAY_SIZE>& Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				InternalSerializeArray<float64,ARRAY_SIZE>(Buffer,Value,Index,Endianness);
			}

			template<Size ARRAY_SIZE>
			static void SerializeArrayFloat80(CByteBuffer& Buffer, const CArray<float80,ARRAY_SIZE>& Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				InternalSerializeArray<float80,ARRAY_SIZE>(Buffer,Value,Index,Endianness);
			}

			template<Size ARRAY_SIZE>
			static void SerializeArraySize(CByteBuffer& Buffer, const CArray<Size,ARRAY_SIZE>& Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				InternalSerializeArray<Size,ARRAY_SIZE>(Buffer,Value,Index,Endianness);
			}

			template<typename TEnumType, Size ARRAY_SIZE>
			static void SerializeArrayEnum(CByteBuffer& Buffer, const CArray<TEnumType,ARRAY_SIZE>& Value, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				static_assert(STypeTraitIsEnum<TEnumType>::Value()==true,"METHOD can NOT be used for NON ENUM TYPES !");

				InternalSerializeArray<TEnumType,ARRAY_SIZE>(Buffer,Value,Index,Endianness);
			}

		public:
			static int8 DeserializeInt8(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static uint8 DeserializeUInt8(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static int16 DeserializeInt16(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static uint16 DeserializeUInt16(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static int32 DeserializeInt32(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static uint32 DeserializeUInt32(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static int64 DeserializeInt64(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static uint64 DeserializeUInt64(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static float32 DeserializeFloat32(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static float64 DeserializeFloat64(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static float80 DeserializeFloat80(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static Size DeserializeSize(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);

			template<typename TEnumType>
			static TEnumType DeserializeEnum(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				static_assert(STypeTraitIsEnum<TEnumType>::Value()==true,"METHOD can NOT be used for NON ENUM TYPES !");

				return(InternalDeserialize<TEnumType>(Buffer,BufferLength,Index,Endianness));
			}

			template<typename TEnumType>
			static TEnumType DeserializeEnumAndCheck(const Char* ValueName, const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				static_assert(STypeTraitIsEnum<TEnumType>::Value()==true,"METHOD can NOT be used for NON ENUM TYPES !");

				TEnumType										EnumValue=InternalDeserialize<TEnumType>(Buffer,BufferLength,Index,Endianness);

				CheckEnumValue<TEnumType>(EnumValue,ValueName);

				return(EnumValue);
			}

		public:
			static int8 DeserializeInt8(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static uint8 DeserializeUInt8(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static int16 DeserializeInt16(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static uint16 DeserializeUInt16(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static int32 DeserializeInt32(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static uint32 DeserializeUInt32(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static int64 DeserializeInt64(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static uint64 DeserializeUInt64(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static float32 DeserializeFloat32(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static float64 DeserializeFloat64(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static float80 DeserializeFloat80(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);
			static Size DeserializeSize(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS);

			template<typename TEnumType>
			static TEnumType DeserializeEnum(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				static_assert(STypeTraitIsEnum<TEnumType>::Value()==true,"METHOD can NOT be used for NON ENUM TYPES !");

				return(InternalDeserialize<TEnumType>(Buffer,Index,Endianness));
			}

			template<typename TEnumType>
			static TEnumType DeserializeEnumAndCheck(const Char* ValueName, const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				static_assert(STypeTraitIsEnum<TEnumType>::Value()==true,"METHOD can NOT be used for NON ENUM TYPES !");

				TEnumType										EnumValue=InternalDeserialize<TEnumType>(Buffer,Index,Endianness);

				CheckEnumValue<TEnumType>(EnumValue,ValueName);

				return(EnumValue);
			}

		public:
			template<Size ARRAY_SIZE>
			static CArray<int8,ARRAY_SIZE> DeserializeArrayInt8(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				return(InternalDeserializeArray<int8,ARRAY_SIZE>(Buffer,BufferLength,Index,Endianness));
			}

			template<Size ARRAY_SIZE>
			static CArray<uint8,ARRAY_SIZE> DeserializeArrayUInt8(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				return(InternalDeserializeArray<uint8,ARRAY_SIZE>(Buffer,BufferLength,Index,Endianness));
			}

			template<Size ARRAY_SIZE>
			static CArray<int16,ARRAY_SIZE> DeserializeArrayInt16(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				return(InternalDeserializeArray<int16,ARRAY_SIZE>(Buffer,BufferLength,Index,Endianness));
			}

			template<Size ARRAY_SIZE>
			static CArray<uint16,ARRAY_SIZE> DeserializeArrayUInt16(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				return(InternalDeserializeArray<uint16,ARRAY_SIZE>(Buffer,BufferLength,Index,Endianness));
			}

			template<Size ARRAY_SIZE>
			static CArray<int32,ARRAY_SIZE> DeserializeArrayInt32(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				return(InternalDeserializeArray<int32,ARRAY_SIZE>(Buffer,BufferLength,Index,Endianness));
			}

			template<Size ARRAY_SIZE>
			static CArray<uint32,ARRAY_SIZE> DeserializeArrayUInt32(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				return(InternalDeserializeArray<uint32,ARRAY_SIZE>(Buffer,BufferLength,Index,Endianness));
			}

			template<Size ARRAY_SIZE>
			static CArray<int64,ARRAY_SIZE> DeserializeArrayInt64(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				return(InternalDeserializeArray<int64,ARRAY_SIZE>(Buffer,BufferLength,Index,Endianness));
			}

			template<Size ARRAY_SIZE>
			static CArray<uint64,ARRAY_SIZE> DeserializeArrayUInt64(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				return(InternalDeserializeArray<uint64,ARRAY_SIZE>(Buffer,BufferLength,Index,Endianness));
			}

			template<Size ARRAY_SIZE>
			static CArray<float32,ARRAY_SIZE> DeserializeArrayFloat32(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				return(InternalDeserializeArray<float32,ARRAY_SIZE>(Buffer,BufferLength,Index,Endianness));
			}

			template<Size ARRAY_SIZE>
			static CArray<float64,ARRAY_SIZE> DeserializeArrayFloat64(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				return(InternalDeserializeArray<float64,ARRAY_SIZE>(Buffer,BufferLength,Index,Endianness));
			}

			template<Size ARRAY_SIZE>
			static CArray<float80,ARRAY_SIZE> DeserializeArrayFloat80(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				return(InternalDeserializeArray<float80,ARRAY_SIZE>(Buffer,BufferLength,Index,Endianness));
			}

			template<Size ARRAY_SIZE>
			static CArray<Size,ARRAY_SIZE> DeserializeArraySize(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				return(InternalDeserializeArray<Size,ARRAY_SIZE>(Buffer,BufferLength,Index,Endianness));
			}

			template<typename TEnumType, Size ARRAY_SIZE>
			static CArray<TEnumType,ARRAY_SIZE> DeserializeArrayEnum(const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				static_assert(STypeTraitIsEnum<TEnumType>::Value()==true,"METHOD can NOT be used for NON ENUM TYPES !");

				return(InternalDeserializeArray<TEnumType,ARRAY_SIZE>(Buffer,BufferLength,Index,Endianness));
			}

			template<typename TEnumType, Size ARRAY_SIZE>
			static CArray<TEnumType,ARRAY_SIZE> DeserializeArrayEnumAndCheck(const Char* ValueName, const uint8* Buffer, Size BufferLength, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				static_assert(STypeTraitIsEnum<TEnumType>::Value()==true,"METHOD can NOT be used for NON ENUM TYPES !");

				CArray<TEnumType,ARRAY_SIZE>					EnumValue=InternalDeserializeArray<TEnumType,ARRAY_SIZE>(Buffer,BufferLength,Index,Endianness);

				for(Size LocalIndex=0;LocalIndex<ARRAY_SIZE;LocalIndex++)
				{
					CheckEnumValue<TEnumType>(EnumValue[LocalIndex],ValueName);
				}

				return(EnumValue);
			}

		public:
			template<Size ARRAY_SIZE>
			static CArray<int8,ARRAY_SIZE> DeserializeArrayInt8(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				return(InternalDeserializeArray<int8,ARRAY_SIZE>(Buffer,Index,Endianness));
			}

			template<Size ARRAY_SIZE>
			static CArray<uint8,ARRAY_SIZE> DeserializeArrayUInt8(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				return(InternalDeserializeArray<uint8,ARRAY_SIZE>(Buffer,Index,Endianness));
			}

			template<Size ARRAY_SIZE>
			static CArray<int16,ARRAY_SIZE> DeserializeArrayInt16(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				return(InternalDeserializeArray<int16,ARRAY_SIZE>(Buffer,Index,Endianness));
			}

			template<Size ARRAY_SIZE>
			static CArray<uint16,ARRAY_SIZE> DeserializeArrayUInt16(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				return(InternalDeserializeArray<uint16,ARRAY_SIZE>(Buffer,Index,Endianness));
			}

			template<Size ARRAY_SIZE>
			static CArray<int32,ARRAY_SIZE> DeserializeArrayInt32(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				return(InternalDeserializeArray<int32,ARRAY_SIZE>(Buffer,Index,Endianness));
			}

			template<Size ARRAY_SIZE>
			static CArray<uint32,ARRAY_SIZE> DeserializeArrayUInt32(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				return(InternalDeserializeArray<uint32,ARRAY_SIZE>(Buffer,Index,Endianness));
			}

			template<Size ARRAY_SIZE>
			static CArray<int64,ARRAY_SIZE> DeserializeArrayInt64(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				return(InternalDeserializeArray<int64,ARRAY_SIZE>(Buffer,Index,Endianness));
			}

			template<Size ARRAY_SIZE>
			static CArray<uint64,ARRAY_SIZE> DeserializeArrayUInt64(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				return(InternalDeserializeArray<uint64,ARRAY_SIZE>(Buffer,Index,Endianness));
			}

			template<Size ARRAY_SIZE>
			static CArray<float32,ARRAY_SIZE> DeserializeArrayFloat32(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				return(InternalDeserializeArray<float32,ARRAY_SIZE>(Buffer,Index,Endianness));
			}

			template<Size ARRAY_SIZE>
			static CArray<float64,ARRAY_SIZE> DeserializeArrayFloat64(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				return(InternalDeserializeArray<float64,ARRAY_SIZE>(Buffer,Index,Endianness));
			}

			template<Size ARRAY_SIZE>
			static CArray<float80,ARRAY_SIZE> DeserializeArrayFloat80(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				return(InternalDeserializeArray<float80,ARRAY_SIZE>(Buffer,Index,Endianness));
			}

			template<Size ARRAY_SIZE>
			static CArray<Size,ARRAY_SIZE> DeserializeArraySize(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				return(InternalDeserializeArray<Size,ARRAY_SIZE>(Buffer,Index,Endianness));
			}

			template<typename TEnumType, Size ARRAY_SIZE>
			static CArray<TEnumType,ARRAY_SIZE> DeserializeArrayEnum(const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				static_assert(STypeTraitIsEnum<TEnumType>::Value()==true,"METHOD can NOT be used for NON ENUM TYPES !");

				return(InternalDeserializeArray<TEnumType,ARRAY_SIZE>(Buffer,Index,Endianness));
			}

			template<typename TEnumType, Size ARRAY_SIZE>
			static CArray<TEnumType,ARRAY_SIZE> DeserializeArrayEnumAndCheck(const Char* ValueName, const CByteBuffer& Buffer, Size Index, EParserEndianness Endianness=CPPFoundation::Platform::CConstants::SYSTEM_ENDIANESS)
			{
				static_assert(STypeTraitIsEnum<TEnumType>::Value()==true,"METHOD can NOT be used for NON ENUM TYPES !");

				CArray<TEnumType,ARRAY_SIZE>					EnumValue=InternalDeserializeArray<TEnumType,ARRAY_SIZE>(Buffer,Index,Endianness);

				for(Size LocalIndex=0;LocalIndex<ARRAY_SIZE;LocalIndex++)
				{
					CheckEnumValue<TEnumType>(EnumValue[LocalIndex],ValueName);
				}

				return(EnumValue);
			}

		public:
			static bool HasBitInt8(int8 Value, Size PositionInBits);
			static bool HasBitUInt8(uint8 Value, Size PositionInBits);
			static bool HasBitInt16(int16 Value, Size PositionInBits);
			static bool HasBitUInt16(uint16 Value, Size PositionInBits);
			static bool HasBitInt32(int32 Value, Size PositionInBits);
			static bool HasBitUInt32(uint32 Value, Size PositionInBits);
			static bool HasBitInt64(int64 Value, Size PositionInBits);
			static bool HasBitUInt64(uint64 Value, Size PositionInBits);
			static bool HasBitSize(Size Value, Size PositionInBits);

		public:
			static int8 GetBitInt8(int8 Value, Size PositionInBits);
			static uint8 GetBitUInt8(uint8 Value, Size PositionInBits);
			static int16 GetBitInt16(int16 Value, Size PositionInBits);
			static uint16 GetBitUInt16(uint16 Value, Size PositionInBits);
			static int32 GetBitInt32(int32 Value, Size PositionInBits);
			static uint32 GetBitUInt32(uint32 Value, Size PositionInBits);
			static int64 GetBitInt64(int64 Value, Size PositionInBits);
			static uint64 GetBitUInt64(uint64 Value, Size PositionInBits);
			static Size GetBitSize(Size Value, Size PositionInBits);

		public:
			static int8 GetBitsInt8(int8 Value, Size StartPositionInBits=0, Size LengthInBits=sizeof(int8)*BITS_PER_BYTE);
			static uint8 GetBitsUInt8(uint8 Value, Size StartPositionInBits=0, Size LengthInBits=sizeof(uint8)*BITS_PER_BYTE);
			static int16 GetBitsInt16(int16 Value, Size StartPositionInBits=0, Size LengthInBits=sizeof(int16)*BITS_PER_BYTE);
			static uint16 GetBitsUInt16(uint16 Value, Size StartPositionInBits=0, Size LengthInBits=sizeof(uint16)*BITS_PER_BYTE);
			static int32 GetBitsInt32(int32 Value, Size StartPositionInBits=0, Size LengthInBits=sizeof(int32)*BITS_PER_BYTE);
			static uint32 GetBitsUInt32(uint32 Value, Size StartPositionInBits=0, Size LengthInBits=sizeof(uint32)*BITS_PER_BYTE);
			static int64 GetBitsInt64(int64 Value, Size StartPositionInBits=0, Size LengthInBits=sizeof(int64)*BITS_PER_BYTE);
			static uint64 GetBitsUInt64(uint64 Value, Size StartPositionInBits=0, Size LengthInBits=sizeof(uint64)*BITS_PER_BYTE);
			static Size GetBitsSize(Size Value, Size StartPositionInBits=0, Size LengthInBits=sizeof(Size)*BITS_PER_BYTE);

		public:
			static int8 OrBitInt8(int8 Value, bool OrValue, Size PositionInBits);
			static uint8 OrBitUInt8(uint8 Value, bool OrValue, Size PositionInBits);
			static int16 OrBitInt16(int16 Value, bool OrValue, Size PositionInBits);
			static uint16 OrBitUInt16(uint16 Value, bool OrValue, Size PositionInBits);
			static int32 OrBitInt32(int32 Value, bool OrValue, Size PositionInBits);
			static uint32 OrBitUInt32(uint32 Value, bool OrValue, Size PositionInBits);
			static int64 OrBitInt64(int64 Value, bool OrValue, Size PositionInBits);
			static uint64 OrBitUInt64(uint64 Value, bool OrValue, Size PositionInBits);
			static Size OrBitSize(Size Value, bool OrValue, Size PositionInBits);

		public:
			static int8 OrBitsInt8(int8 Value, int8 OrValue, Size StartPositionInBits=0, Size LengthInBits=sizeof(int8)*BITS_PER_BYTE);
			static uint8 OrBitsUInt8(uint8 Value, uint8 OrValue, Size StartPositionInBits=0, Size LengthInBits=sizeof(uint8)*BITS_PER_BYTE);
			static int16 OrBitsInt16(int16 Value, int16 OrValue, Size StartPositionInBits=0, Size LengthInBits=sizeof(int16)*BITS_PER_BYTE);
			static uint16 OrBitsUInt16(uint16 Value, uint16 OrValue, Size StartPositionInBits=0, Size LengthInBits=sizeof(uint16)*BITS_PER_BYTE);
			static int32 OrBitsInt32(int32 Value, int32 OrValue, Size StartPositionInBits=0, Size LengthInBits=sizeof(int32)*BITS_PER_BYTE);
			static uint32 OrBitsUInt32(uint32 Value, uint32 OrValue, Size StartPositionInBits=0, Size LengthInBits=sizeof(uint32)*BITS_PER_BYTE);
			static int64 OrBitsInt64(int64 Value, int64 OrValue, Size StartPositionInBits=0, Size LengthInBits=sizeof(int64)*BITS_PER_BYTE);
			static uint64 OrBitsUInt64(uint64 Value, uint64 OrValue, Size StartPositionInBits=0, Size LengthInBits=sizeof(uint64)*BITS_PER_BYTE);
			static Size OrBitsSize(Size Value, Size OrValue, Size StartPositionInBits=0, Size LengthInBits=sizeof(Size)*BITS_PER_BYTE);

		public:
			static int8 SetBitInt8(int8 Value, bool SetValue, Size PositionInBits);
			static uint8 SetBitUInt8(uint8 Value, bool SetValue, Size PositionInBits);
			static int16 SetBitInt16(int16 Value, bool SetValue, Size PositionInBits);
			static uint16 SetBitUInt16(uint16 Value, bool SetValue, Size PositionInBits);
			static int32 SetBitInt32(int32 Value, bool SetValue, Size PositionInBits);
			static uint32 SetBitUInt32(uint32 Value, bool SetValue, Size PositionInBits);
			static int64 SetBitInt64(int64 Value, bool SetValue, Size PositionInBits);
			static uint64 SetBitUInt64(uint64 Value, bool SetValue, Size PositionInBits);
			static Size SetBitSize(Size Value, bool SetValue, Size PositionInBits);

		public:
			static int8 SetBitsInt8(int8 Value, int8 SetValue, Size StartPositionInBits=0, Size LengthInBits=sizeof(int8)*BITS_PER_BYTE);
			static uint8 SetBitsUInt8(uint8 Value, uint8 SetValue, Size StartPositionInBits=0, Size LengthInBits=sizeof(uint8)*BITS_PER_BYTE);
			static int16 SetBitsInt16(int16 Value, int16 SetValue, Size StartPositionInBits=0, Size LengthInBits=sizeof(int16)*BITS_PER_BYTE);
			static uint16 SetBitsUInt16(uint16 Value, uint16 SetValue, Size StartPositionInBits=0, Size LengthInBits=sizeof(uint16)*BITS_PER_BYTE);
			static int32 SetBitsInt32(int32 Value, int32 SetValue, Size StartPositionInBits=0, Size LengthInBits=sizeof(int32)*BITS_PER_BYTE);
			static uint32 SetBitsUInt32(uint32 Value, uint32 SetValue, Size StartPositionInBits=0, Size LengthInBits=sizeof(uint32)*BITS_PER_BYTE);
			static int64 SetBitsInt64(int64 Value, int64 SetValue, Size StartPositionInBits=0, Size LengthInBits=sizeof(int64)*BITS_PER_BYTE);
			static uint64 SetBitsUInt64(uint64 Value, uint64 SetValue, Size StartPositionInBits=0, Size LengthInBits=sizeof(uint64)*BITS_PER_BYTE);
			static Size SetBitsSize(Size Value, Size SetValue, Size StartPositionInBits=0, Size LengthInBits=sizeof(Size)*BITS_PER_BYTE);

		public:
			static int8 GetLengthInBytesInt8(int8 LengthInBits);
			static uint8 GetLengthInBytesUInt8(uint8 LengthInBits);
			static int16 GetLengthInBytesInt16(int16 LengthInBits);
			static uint16 GetLengthInBytesUInt16(uint16 LengthInBits);
			static int32 GetLengthInBytesInt32(int32 LengthInBits);
			static uint32 GetLengthInBytesUInt32(uint32 LengthInBits);
			static int64 GetLengthInBytesInt64(int64 LengthInBits);
			static uint64 GetLengthInBytesUInt64(uint64 LengthInBits);
			static Size GetLengthInBytesSize(Size LengthInBits);

		public:
			static uint8 ConvertToBCD(uint8 Value);
			static uint8 ConvertFromBCD(uint8 Value);

		public:
			[[noreturn]] static void ThrowLengthException(Size ExpectedLength);
			[[noreturn]] static void ThrowUnexpectedLengthException(Size Length);
			[[noreturn]] static void ThrowNotNULLException(const Char* ValueName);

			template<typename TType>
			[[noreturn]] static void ThrowInvalidValueException(TType Value, const CString& Reason, const Char* ValueName)
			{
				throw(CParserException(CString::Format("VALUE [",ValueName,"] is INVALID [",Value,"] ! REASON [",Reason,"] !")));
			}

			template<typename TEnumType>
			[[noreturn]] static void ThrowEnumValueException(TEnumType Value, const Char* ValueName)
			{
				static_assert(STypeTraitIsEnum<TEnumType>::Value()==true,"METHOD can NOT be used for NON ENUM TYPES !");

				throw(CParserException(CString::Format("ENUM [",ValueName,"] has INVALID VALUE [",Value,"] !")));
			}

			template<typename TEnumType>
			[[noreturn]] static void ThrowEnumRangeException(TEnumType MinValue, TEnumType MaxValue, const Char* ValueName)
			{
				static_assert(STypeTraitIsEnum<TEnumType>::Value()==true,"METHOD can NOT be used for NON ENUM TYPES !");

				throw(CParserException(CString::Format("VALUE [",ValueName,"] is OUT of RANGE <",MinValue,",",MaxValue,"> !")));
			}

			template<typename TAritmeticType>
			[[noreturn]] static void ThrowArithmeticRangeException(TAritmeticType MinValue, TAritmeticType MaxValue, const Char* ValueName)
			{
				static_assert(STypeTraitIsNumericType<TAritmeticType>::Value()==true,"METHOD can NOT be used for NON ARITHMETIC TYPES !");

				throw(CParserException(CString::Format("VALUE [",ValueName,"] is OUT of RANGE <",MinValue,",",MaxValue,"> !")));
			}

		public:
			static void CheckLength(Size ActualLength, Size ExpectedLength);

			template<typename TPointerType>
			static void CheckNotNULL(CSharedPointer<TPointerType> Value, const Char* ValueName)
			{
				if (Value==nullptr)
				{
					ThrowNotNULLException(ValueName);
				}
			}
			
			template<typename TEnumType>
			static void CheckEnumValue(TEnumType Value, const Char* ValueName)
			{
				static_assert(STypeTraitIsEnum<TEnumType>::Value()==true,"METHOD can NOT be used for NON ENUM TYPES !");

				if (IsValidValue(Value)==false)
				{
					ThrowEnumValueException(Value,ValueName);
				}
			}

			template<typename TEnumType>
			static void CheckEnumRange(TEnumType Value, TEnumType MinValue, TEnumType MaxValue, const Char* ValueName)
			{
				static_assert(STypeTraitIsEnum<TEnumType>::Value()==true,"METHOD can NOT be used for NON ENUM TYPES !");

				if (Value<MinValue || Value>MaxValue)
				{
					ThrowEnumRangeException(MinValue,MaxValue,ValueName);
				}
			}

			template<typename TAritmeticType>
			static void CheckArithmeticRange(TAritmeticType Value, TAritmeticType MinValue, TAritmeticType MaxValue, const Char* ValueName)
			{
				static_assert(STypeTraitIsNumericType<TAritmeticType>::Value()==true,"METHOD can NOT be used for NON ARITHMETIC TYPES !");

				if (Value<MinValue || Value>MaxValue)
				{
					ThrowArithmeticRangeException(MinValue,MaxValue,ValueName);
				}
			}

			template<typename TType, typename TPredicate>
			static void CheckValue(TType Value, TPredicate Predicate, const CString& Reason, const Char* ValueName)
			{
				if (Predicate(Value)==false)
				{
					ThrowInvalidValueException(Value,Reason,ValueName);
				}
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------