//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Types/Types.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	enum class EWaitResult : uint8
	{
//----------------------------------------------------------------------------------------------------------------------
		E_NONE,
		E_TIMEOUT,
		E_EXIT_EVENT_SET,
		E_SIGNALIZATION_EVENT_SET,
		E_WAIT_EVENT_SET,
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------