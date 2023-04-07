//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Types/Types.h>
#include <Framework/Foundation/Parsing/EParserEndianness.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Platform
{
//----------------------------------------------------------------------------------------------------------------------
	class CConstants final
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			static const char*									END_LINE;
			static const uint64									THREAD_BLOCKING_LIMIT;
			static const uint64									THREAD_BLOCKING_TIMEOUT_IN_MS;
			static const CPPFoundation::Foundation::EParserEndianness	SYSTEM_ENDIANESS;
			static const Size									CAN_FRAME_LENGTH;
			static const Size									CAN_MAX_DATA_LENGTH;
			static const uint32									CAN_EXTENDED_FRAME_FLAG;
			static const uint32									CAN_REMOTE_FRAME_FLAG;
			static const uint32									CAN_ERROR_FRAME_FLAG;
			static const uint32									CAN_STANDARD_FRAME_MASK;
			static const uint32									CAN_EXTENDED_FRAME_MASK;
			static const uint32									CAN_ERROR_FRAME_MASK;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------