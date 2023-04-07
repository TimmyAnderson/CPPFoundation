//----------------------------------------------------------------------------------------------------------------------
#include "CConstants.h"
#if defined(PLATFORM_WINDOWS)
#elif defined(PLATFORM_LINUX)
#include <linux/can.h>
#else
#error UNSUPPORTED PLATFORM !
#endif
#include <Framework/Platform/Global/Macros.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Platform
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace CPPFoundation::Foundation;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#if defined(PLATFORM_WINDOWS)
	const char*													CConstants::END_LINE="\r\n";
	const uint64												CConstants::THREAD_BLOCKING_LIMIT=1000;
	const uint64												CConstants::THREAD_BLOCKING_TIMEOUT_IN_MS=1000;
	const EParserEndianness										CConstants::SYSTEM_ENDIANESS=EParserEndianness::E_LITTLE_ENDIAN;
	const Size													CConstants::CAN_FRAME_LENGTH=16;
	const Size													CConstants::CAN_MAX_DATA_LENGTH=8;
	const uint32												CConstants::CAN_EXTENDED_FRAME_FLAG=0x80000000U;
	const uint32												CConstants::CAN_REMOTE_FRAME_FLAG=0x40000000U;
	const uint32												CConstants::CAN_ERROR_FRAME_FLAG=0x20000000U;
	const uint32												CConstants::CAN_STANDARD_FRAME_MASK=0x000007FFU;
	const uint32												CConstants::CAN_EXTENDED_FRAME_MASK=0x1FFFFFFFU;
	const uint32												CConstants::CAN_ERROR_FRAME_MASK=0x1FFFFFFFU;
#elif defined(PLATFORM_LINUX)
	const char*													CConstants::END_LINE="\n";
	const uint64												CConstants::THREAD_BLOCKING_LIMIT=1000;
	const uint64												CConstants::THREAD_BLOCKING_TIMEOUT_IN_MS=3000;
	const EParserEndianness										CConstants::SYSTEM_ENDIANESS=EParserEndianness::E_LITTLE_ENDIAN;
	const Size													CConstants::CAN_FRAME_LENGTH=sizeof(can_frame);
	const Size													CConstants::CAN_MAX_DATA_LENGTH=static_cast<Size>(CAN_MAX_DLEN);
	const uint32												CConstants::CAN_EXTENDED_FRAME_FLAG=static_cast<uint32>(CAN_EFF_FLAG);
	const uint32												CConstants::CAN_REMOTE_FRAME_FLAG=static_cast<uint32>(CAN_RTR_FLAG);
	const uint32												CConstants::CAN_ERROR_FRAME_FLAG=static_cast<uint32>(CAN_ERR_FLAG);
	const uint32												CConstants::CAN_STANDARD_FRAME_MASK=static_cast<uint32>(CAN_SFF_MASK);
	const uint32												CConstants::CAN_EXTENDED_FRAME_MASK=static_cast<uint32>(CAN_EFF_MASK);
	const uint32												CConstants::CAN_ERROR_FRAME_MASK=static_cast<uint32>(CAN_ERR_MASK);
#else
#error UNSUPPORTED PLATFORM !
#endif
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------