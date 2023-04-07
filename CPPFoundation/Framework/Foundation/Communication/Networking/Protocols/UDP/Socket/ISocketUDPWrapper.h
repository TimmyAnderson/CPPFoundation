//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Strings/CString.h>
#include <Framework/Foundation/Time/CTimeout.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
#include <Framework/Foundation/Communication/Networking/Sockets/ISocketWrapper.h>
#include "CSocketUDPAddress.h"
#include "CSocketUDPReceiveFromParameters.h"
#include "CSocketUDPReceiveFromResult.h"
#include "CSocketUDPSendToParameters.h"
#include "CSocketUDPSendToResult.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class ISocketUDPWrapper : public virtual ISocketWrapper
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			virtual int32 GetSocketHandler(void) const noexcept override=0;
			virtual CPPFoundation::Platform::CSocketPlaformData GetPlatformData(void) const override=0;
			virtual void BindToAddress(const CSocketUDPAddress& Address)=0;
			virtual void SendTo(const CSocketUDPSendToParameters& Parameters, CSocketUDPSendToResult& OperationResult)=0;
			virtual void ReceiveFrom(const CSocketUDPReceiveFromParameters& Parameters, CSocketUDPReceiveFromResult& OperationResult)=0;
			virtual void ChangeBlockingState(bool BlockingState)=0;
			virtual int32 GetSendBufferSize(void)=0;
			virtual void SetSendBufferSize(int32 SendBufferSize)=0;
			virtual int32 GetReceiveBufferSize(void)=0;
			virtual void SetReceiveBufferSize(int32 ReceiveBufferSize)=0;

		public:
			ISocketUDPWrapper(void);
			virtual ~ISocketUDPWrapper(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														ISPSocketUDPWrapper=CSharedPointer<ISocketUDPWrapper>;
	using														ICSPSocketUDPWrapper=CSharedPointer<const ISocketUDPWrapper>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------