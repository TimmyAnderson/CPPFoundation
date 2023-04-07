//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#if defined(PLATFORM_WINDOWS)
#include <Winsock2.h>
#elif defined(PLATFORM_LINUX)
#else
#error UNSUPPORTED PLATFORM !
#endif
#include <Framework/Foundation/Communication/Networking/Sockets/ISocketSynchronizationObject.h>
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Threads/CMutex.h>
#include <Framework/Foundation/Threads/CLock.h>
#include <Framework/Foundation/Time/CTimeout.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Platform
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketWaitObject;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	class CSocketSynchronizationObject final : public virtual CPPFoundation::Foundation::CObject, public virtual CPPFoundation::Foundation::ISocketSynchronizationObject
	{
//----------------------------------------------------------------------------------------------------------------------
		friend CSocketWaitObject;

		private:
#if defined(PLATFORM_WINDOWS)
			SOCKET												MSocket;
			WSAEVENT											MEvent;
#elif defined(PLATFORM_LINUX)
		private:
			CPPFoundation::Foundation::CMutex						MPipeMutex;
			int													MPipeDescriptors[2];
#else
#error UNSUPPORTED PLATFORM !
#endif

		private:
			void Uninitialize(void) noexcept;

#if defined(PLATFORM_WINDOWS)
		private:
			WSAEVENT GetEvent(void) const noexcept;
#elif defined(PLATFORM_LINUX)
		private:
			int GetDescriptor(void) const noexcept;
#else
#error UNSUPPORTED PLATFORM !
#endif

		public:
			virtual void SetEvent(void) override;
			virtual void ResetEvent(void) override;

		public:
			CSocketSynchronizationObject(void);
			virtual ~CSocketSynchronizationObject(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------