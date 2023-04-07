//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CByteBuffer.h>
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Time/CSteadyClock.h>
#include <Framework/Foundation/Time/CTimeout.h>
#include "CParserByteBufferReader.h"
#include "CParserByteBufferWriter.h"
#include "CParserConfiguration.h"
#include "CParserPacket.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class IParser : public virtual CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			IParser& operator=(const IParser& Other)=delete;

		public:
			virtual CCSPParserConfiguration GetParserConfiguration(void) const noexcept=0;
			virtual CParserByteBufferWriter CreatePacket(CSPParserPacket Packet, CParserParameterCollection& Parameters)=0;
			virtual CSPParserPacket ParsePacket(CParserByteBufferReader& Reader, CParserParameterCollection& Parameters)=0;
			virtual CTimeout GetTimeout(CSteadyClock::Milliseconds TimeInMS)=0;
			virtual void Reset(void)=0;
			
		public:
			IParser(void);
			IParser(const IParser&)=delete;
			virtual ~IParser(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														ISPParser=CSharedPointer<IParser>;
	using														ICSPParser=CSharedPointer<const IParser>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------