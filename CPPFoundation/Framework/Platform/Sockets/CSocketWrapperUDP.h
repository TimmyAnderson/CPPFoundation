//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#if defined(PLATFORM_WINDOWS)
#include <Winsock2.h>
#elif defined(PLATFORM_LINUX)
#else
#error UNSUPPORTED PLATFORM !
#endif
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Socket/ISocketUDPWrapper.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Platform
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketWrapperUDP final : public virtual CPPFoundation::Foundation::CObject, public CPPFoundation::Foundation::ISocketUDPWrapper
	{
//----------------------------------------------------------------------------------------------------------------------
#if defined(PLATFORM_WINDOWS)
		private:
			SOCKET												MSocket;
			WSAEVENT											MSocketEvent;
#elif defined(PLATFORM_LINUX)
		private:
			int													MSocket;
#else
#error UNSUPPORTED PLATFORM !
#endif

		private:
			void Uninitialize(void) noexcept;

		public:
			virtual CPPFoundation::Foundation::CString ToString(void) const override;
			virtual int32 GetSocketHandler(void) const noexcept override;
			virtual CSocketPlaformData GetPlatformData(void) const override;
			virtual void BindToAddress(const CPPFoundation::Foundation::CSocketUDPAddress& Address) override;
			virtual void SendTo(const CPPFoundation::Foundation::CSocketUDPSendToParameters& Parameters, CPPFoundation::Foundation::CSocketUDPSendToResult& OperationResult) override;
			virtual void ReceiveFrom(const CPPFoundation::Foundation::CSocketUDPReceiveFromParameters& Parameters, CPPFoundation::Foundation::CSocketUDPReceiveFromResult& OperationResult) override;
			virtual void ChangeBlockingState(bool BlockingState) override;
			virtual int32 GetSendBufferSize(void) override;
			virtual void SetSendBufferSize(int32 SendBufferSize) override;
			virtual int32 GetReceiveBufferSize(void) override;
			virtual void SetReceiveBufferSize(int32 ReceiveBufferSize) override;

		public:
			CSocketWrapperUDP(void);
			virtual ~CSocketWrapperUDP(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------