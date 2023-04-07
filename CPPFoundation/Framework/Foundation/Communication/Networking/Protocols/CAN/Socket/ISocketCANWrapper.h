//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Strings/CString.h>
#include <Framework/Foundation/Time/CTimeout.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
#include <Framework/Foundation/Communication/Networking/Sockets/ISocketWrapper.h>
#include "CSocketCANAddress.h"
#include "CSocketCANReceiveFromParameters.h"
#include "CSocketCANReceiveFromResult.h"
#include "CSocketCANSendToParameters.h"
#include "CSocketCANSendToResult.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class ISocketCANWrapper : public virtual ISocketWrapper
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			virtual int32 GetSocketHandler(void) const noexcept override=0;
			virtual CPPFoundation::Platform::CSocketPlaformData GetPlatformData(void) const override=0;
			virtual void BindToAddress(const CSocketCANAddress& Address)=0;
			virtual void SendTo(const CSocketCANSendToParameters& Parameters, CSocketCANSendToResult& OperationResult)=0;
			virtual void ReceiveFrom(const CSocketCANReceiveFromParameters& Parameters, CSocketCANReceiveFromResult& OperationResult)=0;
			virtual void ChangeBlockingState(bool BlockingState)=0;
			virtual CString GetNetworkInterfaceName(int32 NetworkInterfaceIndex)=0;
			virtual int32 GetNetworkInterfaceIndex(const CString& NetworkInterfaceName)=0;
			virtual int32 GetSendBufferSize(void)=0;
			virtual void SetSendBufferSize(int32 SendBufferSize)=0;
			virtual int32 GetReceiveBufferSize(void)=0;
			virtual void SetReceiveBufferSize(int32 ReceiveBufferSize)=0;

		public:
			ISocketCANWrapper(void);
			virtual ~ISocketCANWrapper(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														ISPSocketCANWrapper=CSharedPointer<ISocketCANWrapper>;
	using														ICSPSocketCANWrapper=CSharedPointer<const ISocketCANWrapper>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------