//----------------------------------------------------------------------------------------------------------------------
#include "CParserPacketData.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CParserPacketData::CParserPacketData(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CParserPacketData::~CParserPacketData(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CParserPacketData::CheckLength(Size ActualLength, Size ExpectedLength)
	{
		CParserHelper::CheckLength(ActualLength,ExpectedLength);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserPacketData::CheckLength(const CParserByteBufferReader& Reader, Size ExpectedLength)
	{
		CheckLength(Reader.GetLength(),ExpectedLength);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CParserPacketData::ToString(void) const
	{
		try
		{
			return(InternalToString());
		}
		catch(const CParserException& E)
		{
			throw(CParserException(CString::Format("PACKET DATA FAILED to CONVERT to STRING ! EXCEPTION [",E.ToString(),"] !")));
		}
		catch(const CException& E)
		{
			throw(CParserException(CString::Format("PACKET DATA FAILED to CONVERT to STRING ! UNEXPECTED EXCEPTION [",E.ToString(),"] !")));
		}
		catch(...)
		{
			throw(CParserException(CString::Format("PACKET DATA FAILED to CONVERT to STRING ! UNKNOWN EXCEPTION !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CParserPacketData::Equals(const CParserPacketData& Other) const
	{
		try
		{
			return(InternalEquals(Other));
		}
		catch(const CParserException& E)
		{
			throw(CParserException(CString::Format("PACKET DATA FAILED to COMPARE ! EXCEPTION [",E.ToString(),"] !")));
		}
		catch(const CException& E)
		{
			throw(CParserException(CString::Format("PACKET DATA FAILED to COMPARE ! UNEXPECTED EXCEPTION [",E.ToString(),"] !")));
		}
		catch(...)
		{
			throw(CParserException(CString::Format("PACKET DATA FAILED to COMPARE ! UNKNOWN EXCEPTION !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserPacketData::CreatePacketData(CParserByteBufferWriter& Writer, CParserParameterCollection& Parameters)
	{
		try
		{
			InternalCreatePacketData(Writer,Parameters);
		}
		catch(const CParserException& E)
		{
			throw(CParserException(CString::Format("PACKET DATA FAILED to CREATE ! EXCEPTION [",E.ToString(),"] !")));
		}
		catch(const CException& E)
		{
			throw(CParserException(CString::Format("PACKET DATA FAILED to CREATE ! UNEXPECTED EXCEPTION [",E.ToString(),"] !")));
		}
		catch(...)
		{
			throw(CParserException(CString::Format("PACKET DATA FAILED to CREATE ! UNKNOWN EXCEPTION !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserPacketData::ParsePacketData(CParserByteBufferReader& Reader, CParserParameterCollection& Parameters)
	{
		try
		{
			InternalParsePacketData(Reader,Parameters);
		}
		catch(const CParserException& E)
		{
			throw(CParserException(CString::Format("PACKET DATA FAILED to PARSE ! EXCEPTION [",E.ToString(),"] !")));
		}
		catch(const CException& E)
		{
			throw(CParserException(CString::Format("PACKET DATA FAILED to PARSE ! UNEXPECTED EXCEPTION [",E.ToString(),"] !")));
		}
		catch(...)
		{
			throw(CParserException(CString::Format("PACKET DATA FAILED to PARSE ! UNKNOWN EXCEPTION !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------