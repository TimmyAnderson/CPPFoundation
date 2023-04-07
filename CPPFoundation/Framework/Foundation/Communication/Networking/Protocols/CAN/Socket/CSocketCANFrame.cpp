//----------------------------------------------------------------------------------------------------------------------
#include "CSocketCANFrame.h"
#include <Framework/Foundation/Exceptions/CSocketException.h>
#include <Framework/Foundation/Parsing/CParserByteBufferReader.h>
#include <Framework/Foundation/Parsing/CParserByteBufferWriter.h>
#include <Framework/Platform/Global/CConstants.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace std;
	using namespace CPPFoundation::Platform;
//----------------------------------------------------------------------------------------------------------------------
	const Size													CSocketCANFrame::CAN_ID_LENGTH=4;
	const Size													CSocketCANFrame::CAN_DATA_LENGTH=CConstants::CAN_MAX_DATA_LENGTH;
	const Size													CSocketCANFrame::CAN_FRAME_LENGTH=CAN_ID_LENGTH+CAN_DATA_LENGTH;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANFrame::CSocketCANFrame(void)
		: MCANID(), MCANData()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANFrame::CSocketCANFrame(const CSocketCANID& CANID, const CByteBuffer& CANData)
		: MCANID(CANID), MCANData(CANData)
	{
		if (CANData.GetLength()>CAN_DATA_LENGTH)
		{
			throw(CSocketException("CAN DATA are TOO LARGE !"));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANFrame::CSocketCANFrame(const CSocketCANID& CANID, CByteBuffer&& CANData)
		: MCANID(CANID), MCANData(FUNCTION_MOVE(CANData))
	{
		if (CANData.GetLength()>CAN_DATA_LENGTH)
		{
			throw(CSocketException("CAN DATA are TOO LARGE !"));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANFrame::CSocketCANFrame(CSocketCANID&& CANID, CByteBuffer&& CANData)
		: MCANID(FUNCTION_MOVE(CANID)), MCANData(FUNCTION_MOVE(CANData))
	{
		if (CANData.GetLength()>CAN_DATA_LENGTH)
		{
			throw(CSocketException("CAN DATA are TOO LARGE !"));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANFrame::CSocketCANFrame(const CSocketCANFrame& Other)
		: MCANID(Other.MCANID), MCANData(Other.MCANData)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANFrame::CSocketCANFrame(CSocketCANFrame&& Other) noexcept
		: MCANID(FUNCTION_MOVE(Other.MCANID)), MCANData(FUNCTION_MOVE(Other.MCANData))
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANFrame::~CSocketCANFrame(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANFrame& CSocketCANFrame::operator=(const CSocketCANFrame& Other)
	{
		MCANID=Other.MCANID;
		MCANData=Other.MCANData;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANFrame& CSocketCANFrame::operator=(CSocketCANFrame&& Other) noexcept
	{
		MCANID=FUNCTION_MOVE(Other.MCANID);
		MCANData=FUNCTION_MOVE(Other.MCANData);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketCANFrame::operator==(const CSocketCANFrame& Other) const
	{
		if (MCANID!=Other.MCANID)
		{
			return(false);
		}

		if (MCANData!=Other.MCANData)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketCANFrame::operator!=(const CSocketCANFrame& Other) const
	{
		return(!(*this==Other));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketCANFrame::ToString(void) const
	{
		return(CString::Format("CAN ID [",MCANID.ToString(),"] CAN DATA [",MCANData.ToString(),"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	const CSocketCANID& CSocketCANFrame::GetCANID(void) const noexcept
	{
		return(MCANID);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CByteBuffer& CSocketCANFrame::GetCANData(void) const noexcept
	{
		return(MCANData);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CByteBuffer CSocketCANFrame::Serialize(void) const
	{
		CParserByteBufferWriter									Writer;

		Writer.SerializeUInt32(MCANID.GetID(),EParserEndianness::E_BIG_ENDIAN);
		Writer.Add(MCANData);

		return(Writer.GetBuffer());
	}
//----------------------------------------------------------------------------------------------------------------------
	void CSocketCANFrame::Deserialize(const CByteBuffer& Data)
	{
		CParserByteBufferReader									Reader(Data);

		if (Reader.GetLength()<CAN_ID_LENGTH)
		{
			throw(CSocketException("CAN ID is TOO SHORT !"));
		}

		uint32													CANID=Reader.DeserializeUInt32(EParserEndianness::E_BIG_ENDIAN);

		if (Reader.GetLength()>CAN_DATA_LENGTH)
		{
			throw(CSocketException("CAN DATA are TOO LARGE !"));
		}

		CByteBuffer												CANData=Reader.GetRemainingArrayAndInc();

		MCANID=CANID;
		MCANData=FUNCTION_MOVE(CANData);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------