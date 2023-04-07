//----------------------------------------------------------------------------------------------------------------------
#include "CParser.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CParser::CParser(CLogWriter& LogWriter, const CLogCategory& LogCategoryParser, CCSPParserConfiguration ParserConfiguration)
		: MLogWriter(LogWriter), MLogCategoryParser(LogCategoryParser), MParserConfiguration(ParserConfiguration)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CParser::~CParser(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CCSPParserConfiguration CParser::GetParserConfiguration(void) const noexcept
	{
		return(MParserConfiguration);
	}
//----------------------------------------------------------------------------------------------------------------------
	CParserByteBufferWriter CParser::CreatePacket(CSPParserPacket Packet, CParserParameterCollection& Parameters)
	{
		try
		{
			return(InternalCreatePacket(Packet,Parameters));
		}
		catch(const CParserException& E)
		{
			throw(CParserException(CString::Format("PARSER FAILED to CREATE PACKET [",Packet->ToString(),"] ! EXCEPTION [",E.ToString(),"] !")));
		}
		catch(const CException& E)
		{
			throw(CParserException(CString::Format("PARSER FAILED to CREATE PACKET [",Packet->ToString(),"] ! UNEXPECTED EXCEPTION [",E.ToString(),"] !")));
		}
		catch(...)
		{
			throw(CParserException(CString::Format("PARSER FAILED to CREATE PACKET [",Packet->ToString(),"] ! UNEXPECTED UNKNOWN EXCEPTION !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CSPParserPacket CParser::ParsePacket(CParserByteBufferReader& Reader, CParserParameterCollection& Parameters)
	{
		try
		{
			return(InternalParsePacket(Reader,Parameters));
		}
		catch(const CParserException& E)
		{
			throw(CParserException(CString::Format("PARSER FAILED to PARSE PACKET [",Reader.ToString(),"] ! EXCEPTION [",E.ToString(),"] !")));
		}
		catch(const CException& E)
		{
			throw(CParserException(CString::Format("PARSER FAILED to PARSE PACKET [",Reader.ToString(),"] ! UNEXPECTED EXCEPTION [",E.ToString(),"] !")));
		}
		catch(...)
		{
			throw(CParserException(CString::Format("PARSER FAILED to PARSE PACKET [",Reader.ToString(),"] ! UNEXPECTED UNKNOWN EXCEPTION !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CTimeout CParser::GetTimeout(CSteadyClock::Milliseconds TimeInMS)
	{
		try
		{
			return(InternalGetTimeout(TimeInMS));
		}
		catch(const CParserException& E)
		{
			throw(CParserException(CString::Format("PARSER FAILED to GET TIMEOUT ! EXCEPTION [",E.ToString(),"] !")));
		}
		catch(const CException& E)
		{
			throw(CParserException(CString::Format("PARSER FAILED to GET TIMEOUT ! UNEXPECTED EXCEPTION [",E.ToString(),"] !")));
		}
		catch(...)
		{
			throw(CParserException(CString::Format("PARSER FAILED to GET TIMEOUT ! UNEXPECTED UNKNOWN EXCEPTION !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CParser::Reset(void)
	{
		try
		{
			InternalReset();
		}
		catch(const CParserException& E)
		{
			throw(CParserException(CString::Format("PARSER FAILED to RESET ! EXCEPTION [",E.ToString(),"] !")));
		}
		catch(const CException& E)
		{
			throw(CParserException(CString::Format("PARSER FAILED to RESET ! UNEXPECTED EXCEPTION [",E.ToString(),"] !")));
		}
		catch(...)
		{
			throw(CParserException(CString::Format("PARSER FAILED to RESET ! UNEXPECTED UNKNOWN EXCEPTION !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CLogWriter& CParser::GetLogWriter(void) const noexcept
	{
		return(MLogWriter);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CLogCategory& CParser::GetLogCategoryParser(void) const noexcept
	{
		return(MLogCategoryParser);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CString& CParser::GetParserName(void) const noexcept
	{
		return(MParserConfiguration->GetParserName());
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------