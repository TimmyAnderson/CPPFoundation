//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <Framework/Platform/Global/Macros.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Platform
{
//----------------------------------------------------------------------------------------------------------------------
	enum class EFileOpenFlags
	{
//----------------------------------------------------------------------------------------------------------------------
		E_RDONLY=O_RDONLY,
		E_WRONLY=O_WRONLY,
		E_RDWR=O_RDWR,
		E_APPEND=O_APPEND,
		E_CREAT=O_CREAT,
		E_TRUNC=O_TRUNC,
		E_EXCL=O_EXCL,
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	inline EFileOpenFlags operator|(EFileOpenFlags Left, EFileOpenFlags Right)
	{
		int32													TypedLeft=static_cast<int32>(Left);
		int32													TypedRight=static_cast<int32>(Right);
		int32													TypedResult=(TypedLeft | TypedRight);
		EFileOpenFlags											Result=static_cast<EFileOpenFlags>(TypedResult);

		return(Result);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------