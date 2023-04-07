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
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Socket/ISocketTCPWrapper.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Platform
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketWrapperTCP final : public virtual CPPFoundation::Foundation::CObject, public CPPFoundation::Foundation::ISocketTCPWrapper
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
			virtual CPPFoundation::Foundation::CSharedPointer<CPPFoundation::Foundation::ISocketTCPWrapper> Accept(CPPFoundation::Foundation::CSocketTCPAddress& Address) override;
			virtual void BindToAddress(const CPPFoundation::Foundation::CSocketTCPAddress& Address) override;
			virtual bool ConnectToAddress(const CPPFoundation::Foundation::CSocketTCPAddress& Address) override;
			virtual void Listen(Size MaximumNumberOfPendingConnections) override;
			virtual void Shutdown(CPPFoundation::Foundation::ESocketTCPShutdownFlags ShutdownFlags) override;
			virtual void Send(const CPPFoundation::Foundation::CSocketTCPSendParameters& Parameters, CPPFoundation::Foundation::CSocketTCPSendResult& OperationResult) override;
			virtual void Receive(const CPPFoundation::Foundation::CSocketTCPReceiveParameters& Parameters, CPPFoundation::Foundation::CSocketTCPReceiveResult& OperationResult) override;
			virtual void ChangeBlockingState(bool BlockingState) override;
			virtual int32 GetSendBufferSize(void) override;
			virtual void SetSendBufferSize(int32 SendBufferSize) override;
			virtual int32 GetReceiveBufferSize(void) override;
			virtual void SetReceiveBufferSize(int32 ReceiveBufferSize) override;

		private:
#if defined(PLATFORM_WINDOWS)
			CSocketWrapperTCP(SOCKET Socket);
#elif defined(PLATFORM_LINUX)
			CSocketWrapperTCP(int Socket);
#else
#error UNSUPPORTED PLATFORM !
#endif

		public:
			CSocketWrapperTCP(void);
			virtual ~CSocketWrapperTCP(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------