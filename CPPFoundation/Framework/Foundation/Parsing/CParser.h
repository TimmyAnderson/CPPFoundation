//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Logger/CLogWriter.h>
#include "IParser.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CParser : public virtual IParser
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CLogWriter&											MLogWriter;
			const CLogCategory									MLogCategoryParser;
			CCSPParserConfiguration								MParserConfiguration;

		public:
			CParser& operator=(const CParser& Other)=delete;

		protected:
			virtual CParserByteBufferWriter InternalCreatePacket(CSPParserPacket Packet, CParserParameterCollection& Parameters)=0;
			virtual CSPParserPacket InternalParsePacket(CParserByteBufferReader& Reader, CParserParameterCollection& Parameters)=0;
			virtual CTimeout InternalGetTimeout(CSteadyClock::Milliseconds TimeInMS)=0;
			virtual void InternalReset(void)=0;

		public:
			virtual CCSPParserConfiguration GetParserConfiguration(void) const noexcept override final;
			virtual CParserByteBufferWriter CreatePacket(CSPParserPacket Packet, CParserParameterCollection& Parameters) override final;
			virtual CSPParserPacket ParsePacket(CParserByteBufferReader& Reader, CParserParameterCollection& Parameters) override final;
			virtual CTimeout GetTimeout(CSteadyClock::Milliseconds TimeInMS) override final;
			virtual void Reset(void) override final;

		public:
			CLogWriter& GetLogWriter(void) const noexcept;
			const CLogCategory& GetLogCategoryParser(void) const noexcept;
			const CString& GetParserName(void) const noexcept;

		public:
			CParser(CLogWriter& LogWriter, const CLogCategory& LogCategoryParser, CCSPParserConfiguration ParserConfiguration);
			virtual ~CParser(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPParser=CSharedPointer<CParser>;
	using														CCSPParser=CSharedPointer<const CParser>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------