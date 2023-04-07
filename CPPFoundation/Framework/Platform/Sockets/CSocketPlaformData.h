//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#if defined(PLATFORM_WINDOWS)
#include <Winsock2.h>
#elif defined(PLATFORM_LINUX)
#else
#error UNSUPPORTED PLATFORM !
#endif
#include <Framework/Foundation/Objects/CObject.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Platform
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketPlaformData final : public virtual CPPFoundation::Foundation::CObject
	{
//----------------------------------------------------------------------------------------------------------------------
#if defined(PLATFORM_WINDOWS)
		private:
			SOCKET												MSocket;
			WSAEVENT											MSocketEvent;
#elif defined(PLATFORM_LINUX)
			int													MSocket;
#else
#error UNSUPPORTED PLATFORM !
#endif

#if defined(PLATFORM_WINDOWS)
		public:
			SOCKET GetSocket(void) const noexcept;
			WSAEVENT GetEvent(void) const noexcept;
#elif defined(PLATFORM_LINUX)
		public:
			int GetSocket(void) const noexcept;
#else
#error UNSUPPORTED PLATFORM !
#endif

#if defined(PLATFORM_WINDOWS)
		public:
			CSocketPlaformData(SOCKET Socket, WSAEVENT SocketEvent);
			virtual ~CSocketPlaformData(void) override;
#elif defined(PLATFORM_LINUX)
		public:
			CSocketPlaformData(int Socket);
			virtual ~CSocketPlaformData(void) override;
#else
#error UNSUPPORTED PLATFORM !
#endif
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------