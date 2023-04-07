//----------------------------------------------------------------------------------------------------------------------
#include "CParserPacket.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CParserPacket::CParserPacket(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CParserPacket::~CParserPacket(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CParserPacket::CheckLength(Size ActualLength, Size ExpectedLength)
	{
		CParserHelper::CheckLength(ActualLength,ExpectedLength);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserPacket::CheckLength(const CParserByteBufferReader& Reader, Size ExpectedLength)
	{
		CheckLength(Reader.GetLength(),ExpectedLength);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CParserPacket::ToString(void) const
	{
		try
		{
			return(InternalToString());
		}
		catch(const CParserException& E)
		{
			throw(CParserException(CString::Format("PACKET FAILED to CONVERT to STRING ! EXCEPTION [",E.ToString(),"] !")));
		}
		catch(const CException& E)
		{
			throw(CParserException(CString::Format("PACKET FAILED to CONVERT to STRING ! UNEXPECTED EXCEPTION [",E.ToString(),"] !")));
		}
		catch(...)
		{
			throw(CParserException(CString::Format("PACKET FAILED to CONVERT to STRING ! UNKNOWN EXCEPTION !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CParserPacket::Equals(const CParserPacket& Other) const
	{
		try
		{
			return(InternalEquals(Other));
		}
		catch(const CParserException& E)
		{
			throw(CParserException(CString::Format("PACKET FAILED to COMPARE ! EXCEPTION [",E.ToString(),"] !")));
		}
		catch(const CException& E)
		{
			throw(CParserException(CString::Format("PACKET FAILED to COMPARE ! UNEXPECTED EXCEPTION [",E.ToString(),"] !")));
		}
		catch(...)
		{
			throw(CParserException(CString::Format("PACKET FAILED to COMPARE ! UNKNOWN EXCEPTION !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserPacket::CreatePacket(CParserByteBufferWriter& Writer, CParserParameterCollection& Parameters)
	{
		try
		{
			InternalCreatePacket(Writer,Parameters);
		}
		catch(const CParserException& E)
		{
			throw(CParserException(CString::Format("PACKET FAILED to CREATE ! EXCEPTION [",E.ToString(),"] !")));
		}
		catch(const CException& E)
		{
			throw(CParserException(CString::Format("PACKET FAILED to CREATE ! UNEXPECTED EXCEPTION [",E.ToString(),"] !")));
		}
		catch(...)
		{
			throw(CParserException(CString::Format("PACKET FAILED to CREATE ! UNKNOWN EXCEPTION !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParserPacket::ParsePacket(CParserByteBufferReader& Reader, CParserParameterCollection& Parameters)
	{
		try
		{
			InternalParsePacket(Reader,Parameters);
		}
		catch(const CParserException& E)
		{
			throw(CParserException(CString::Format("PACKET FAILED to PARSE ! EXCEPTION [",E.ToString(),"] !")));
		}
		catch(const CException& E)
		{
			throw(CParserException(CString::Format("PACKET FAILED to PARSE ! UNEXPECTED EXCEPTION [",E.ToString(),"] !")));
		}
		catch(...)
		{
			throw(CParserException(CString::Format("PACKET FAILED to PARSE ! UNKNOWN EXCEPTION !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------