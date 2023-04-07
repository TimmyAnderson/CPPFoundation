//----------------------------------------------------------------------------------------------------------------------
#include "CSocketPlaformData.h"
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
	CSocketPlaformData::CSocketPlaformData(SOCKET Socket, WSAEVENT SocketEvent)
		: MSocket(Socket), MSocketEvent(SocketEvent)
	{
	}
#elif defined(PLATFORM_LINUX)
	CSocketPlaformData::CSocketPlaformData(int Socket)
		: MSocket(Socket)
	{
	}
#else
#error UNSUPPORTED PLATFORM !
#endif
//----------------------------------------------------------------------------------------------------------------------
#if defined(PLATFORM_WINDOWS)
	CSocketPlaformData::~CSocketPlaformData(void)
	{
	}
#elif defined(PLATFORM_LINUX)
	CSocketPlaformData::~CSocketPlaformData(void)
	{
	}
#else
#error UNSUPPORTED PLATFORM !
#endif
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#if defined(PLATFORM_WINDOWS)
	SOCKET CSocketPlaformData::GetSocket(void) const noexcept
	{
		return(MSocket);
	}
#elif defined(PLATFORM_LINUX)
	int CSocketPlaformData::GetSocket(void) const noexcept
	{
		return(MSocket);
	}
#else
#error UNSUPPORTED PLATFORM !
#endif
//----------------------------------------------------------------------------------------------------------------------
#if defined(PLATFORM_WINDOWS)
	WSAEVENT CSocketPlaformData::GetEvent(void) const noexcept
	{
		return(MSocketEvent);
	}
#elif defined(PLATFORM_LINUX)
#else
#error UNSUPPORTED PLATFORM !
#endif
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------