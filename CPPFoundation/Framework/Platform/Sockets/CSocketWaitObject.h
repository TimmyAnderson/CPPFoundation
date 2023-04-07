//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#if defined(PLATFORM_WINDOWS)
#include <Winsock2.h>
#elif defined(PLATFORM_LINUX)
#else
#error UNSUPPORTED PLATFORM !
#endif
#include <Framework/Foundation/Communication/Networking/Sockets/CSocket.h>
#include <Framework/Foundation/Communication/Networking/Sockets/ESocketWaitEvent.h>
#include <Framework/Foundation/Communication/Networking/Sockets/ESocketWaitFlags.h>
#include <Framework/Foundation/Communication/Networking/Sockets/ESocketWaitResultFlags.h>
#include <Framework/Foundation/Communication/Networking/Sockets/ISocketWaitObject.h>
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Time/CTimeout.h>
#include "CSocketSynchronizationObject.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Platform
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketWaitObject final : public virtual CPPFoundation::Foundation::CObject, public virtual CPPFoundation::Foundation::ISocketWaitObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			static const Size									MAXIMUM_NUMBER_OF_SOCKETS;

		private:
			CSocketSynchronizationObject						MSynchronizationObject;

		public:
			virtual Size GetMaximumNumberOfSocket(void) const override;
			virtual CPPFoundation::Foundation::ESocketWaitEvent WaitForEvent(CPPFoundation::Foundation::CVector<CPPFoundation::Foundation::CSocketWaitState>& Sockets, const CPPFoundation::Foundation::CTimeout& Timeout) override;
			virtual void SetEvent(void) override;
			virtual void ResetEvent(void) override;

		public:
			CSocketWaitObject(void);
			virtual ~CSocketWaitObject(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------