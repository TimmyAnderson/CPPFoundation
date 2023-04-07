//----------------------------------------------------------------------------------------------------------------------
#include "CParserByteBufferWriter.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CParserByteBufferWriter::CParserByteBufferWriter(void)
		: MBuffer()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CParserByteBufferWriter::CParserByteBufferWriter(const CParserByteBufferWriter& Other)
		: MBuffer(Other.MBuffer)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CParserByteBufferWriter::CParserByteBufferWriter(CParserByteBufferWriter&& Other) noexcept
		: MBuffer(FUNCTION_MOVE(Other.MBuffer))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CParserByteBufferWriter::~CParserByteBufferWriter(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CParserByteBufferWriter& CParserByteBufferWriter::operator=(const CParserByteBufferWriter& Other)
	{
		MBuffer=Other.MBuffer;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CParserByteBufferWriter& CParserByteBufferWriter::operator=(CParserByteBufferWriter&& Other) noexcept
	{
		MBuffer=FUNCTION_MOVE(Other.MBuffer);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	uint8& CParserByteBufferWriter::operator[](Size Index)
	{
		return(MBuffer[Index]);
	}
//----------------------------------------------------------------------------------------------------------------------
	uint8 CParserByteBufferWriter::operator[](Size Index) const
	{
		return(MBuffer[Index]);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CParserByteBufferWriter::ToString(void) const
	{
		return(MBuffer.ToString());
	}
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer& CParserByteBufferWriter::GetBuffer(void) noexcept
	{
		return(MBuffer);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CByteBuffer& CParserByteBufferWriter::GetBuffer(void) const noexcept
	{
		return(MBuffer);
	}
//----------------------------------------------------------------------------------------------------------------------
	Size CParserByteBufferWriter::GetLength(void) const
	{
		return(MBuffer.GetLength());
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserByteBufferWriter::Add(uint8 Value)
	{
		MBuffer.Add(Value);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserByteBufferWriter::Add(const CByteBuffer& Buffer)
	{
		MBuffer.Add(Buffer);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserByteBufferWriter::Add(CByteBuffer&& Buffer)
	{
		MBuffer.Add(FUNCTION_MOVE(Buffer));
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserByteBufferWriter::Add(const CParserByteBufferWriter& Writer)
	{
		MBuffer.Add(Writer.MBuffer);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserByteBufferWriter::Add(uint8* Buffer, Size Length)
	{
		MBuffer.Add(Buffer,Length);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserByteBufferWriter::Insert(uint8 Item, Size Index)
	{
		MBuffer.Insert(Item,Index);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserByteBufferWriter::Erase(Size Index)
	{
		MBuffer.Erase(Index);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserByteBufferWriter::Erase(Size Index, Size Length)
	{
		MBuffer.Erase(Index,Length);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CParserByteBufferWriter::SerializeInt8(int8 Value, EParserEndianness Endianness)
	{
		Size													Length=MBuffer.GetLength();

		MBuffer.Add(uint8(0),sizeof(Value));

		CParserHelper::SerializeInt8(MBuffer,Value,Length,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserByteBufferWriter::SerializeUInt8(uint8 Value, EParserEndianness Endianness)
	{
		Size													Length=MBuffer.GetLength();

		MBuffer.Add(uint8(0),sizeof(Value));

		CParserHelper::SerializeUInt8(MBuffer,Value,Length,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserByteBufferWriter::SerializeInt16(int16 Value, EParserEndianness Endianness)
	{
		Size													Length=MBuffer.GetLength();

		MBuffer.Add(uint8(0),sizeof(Value));

		CParserHelper::SerializeInt16(MBuffer,Value,Length,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserByteBufferWriter::SerializeUInt16(uint16 Value, EParserEndianness Endianness)
	{
		Size													Length=MBuffer.GetLength();

		MBuffer.Add(uint8(0),sizeof(Value));

		CParserHelper::SerializeUInt16(MBuffer,Value,Length,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserByteBufferWriter::SerializeInt32(int32 Value, EParserEndianness Endianness)
	{
		Size													Length=MBuffer.GetLength();

		MBuffer.Add(uint8(0),sizeof(Value));

		CParserHelper::SerializeInt32(MBuffer,Value,Length,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserByteBufferWriter::SerializeUInt32(uint32 Value, EParserEndianness Endianness)
	{
		Size													Length=MBuffer.GetLength();

		MBuffer.Add(uint8(0),sizeof(Value));

		CParserHelper::SerializeUInt32(MBuffer,Value,Length,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserByteBufferWriter::SerializeInt64(int64 Value, EParserEndianness Endianness)
	{
		Size													Length=MBuffer.GetLength();

		MBuffer.Add(uint8(0),sizeof(Value));

		CParserHelper::SerializeInt64(MBuffer,Value,Length,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserByteBufferWriter::SerializeUInt64(uint64 Value, EParserEndianness Endianness)
	{
		Size													Length=MBuffer.GetLength();

		MBuffer.Add(uint8(0),sizeof(Value));

		CParserHelper::SerializeUInt64(MBuffer,Value,Length,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserByteBufferWriter::SerializeFloat32(float32 Value, EParserEndianness Endianness)
	{
		Size													Length=MBuffer.GetLength();

		MBuffer.Add(uint8(0),sizeof(Value));

		CParserHelper::SerializeFloat32(MBuffer,Value,Length,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserByteBufferWriter::SerializeFloat64(float64 Value, EParserEndianness Endianness)
	{
		Size													Length=MBuffer.GetLength();

		MBuffer.Add(uint8(0),sizeof(Value));

		CParserHelper::SerializeFloat64(MBuffer,Value,Length,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserByteBufferWriter::SerializeFloat80(float80 Value, EParserEndianness Endianness)
	{
		Size													Length=MBuffer.GetLength();

		MBuffer.Add(uint8(0),sizeof(Value));

		CParserHelper::SerializeFloat80(MBuffer,Value,Length,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserByteBufferWriter::SerializeSize(Size Value, EParserEndianness Endianness)
	{
		Size													Length=MBuffer.GetLength();

		MBuffer.Add(uint8(0),sizeof(Value));

		CParserHelper::SerializeSize(MBuffer,Value,Length,Endianness);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------