//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Socket/ISocketCANWrapper.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Platform
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketWrapperCAN final : public virtual CPPFoundation::Foundation::CObject, public CPPFoundation::Foundation::ISocketCANWrapper
	{
//----------------------------------------------------------------------------------------------------------------------
#if defined(PLATFORM_WINDOWS)
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
			virtual void BindToAddress(const CPPFoundation::Foundation::CSocketCANAddress& Address) override;
			virtual void SendTo(const CPPFoundation::Foundation::CSocketCANSendToParameters& Parameters, CPPFoundation::Foundation::CSocketCANSendToResult& OperationResult) override;
			virtual void ReceiveFrom(const CPPFoundation::Foundation::CSocketCANReceiveFromParameters& Parameters, CPPFoundation::Foundation::CSocketCANReceiveFromResult& OperationResult) override;
			virtual void ChangeBlockingState(bool BlockingState) override;
			virtual CPPFoundation::Foundation::CString GetNetworkInterfaceName(int32 NetworkInterfaceIndex) override;
			virtual int32 GetNetworkInterfaceIndex(const CPPFoundation::Foundation::CString& NetworkInterfaceName) override;
			virtual int32 GetSendBufferSize(void) override;
			virtual void SetSendBufferSize(int32 SendBufferSize) override;
			virtual int32 GetReceiveBufferSize(void) override;
			virtual void SetReceiveBufferSize(int32 ReceiveBufferSize) override;

		public:
			CSocketWrapperCAN(void);
			virtual ~CSocketWrapperCAN(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------