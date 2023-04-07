//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Strings/CString.h>
#include <Framework/Foundation/Time/CTimeout.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
#include <Framework/Foundation/Communication/Networking/Sockets/ISocketWrapper.h>
#include "CSocketTCPAddress.h"
#include "CSocketTCPReceiveParameters.h"
#include "CSocketTCPReceiveResult.h"
#include "CSocketTCPSendParameters.h"
#include "CSocketTCPSendResult.h"
#include "ESocketTCPShutdownFlags.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class ISocketTCPWrapper : public virtual ISocketWrapper
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			virtual int32 GetSocketHandler(void) const noexcept override=0;
			virtual CPPFoundation::Platform::CSocketPlaformData GetPlatformData(void) const override=0;
			virtual CSharedPointer<ISocketTCPWrapper> Accept(CSocketTCPAddress& Address)=0;
			virtual void BindToAddress(const CSocketTCPAddress& Address)=0;
			virtual bool ConnectToAddress(const CSocketTCPAddress& Address)=0;
			virtual void Listen(Size MaximumNumberOfPendingConnections)=0;
			virtual void Shutdown(ESocketTCPShutdownFlags ShutdownFlags)=0;
			virtual void Send(const CSocketTCPSendParameters& Parameters, CSocketTCPSendResult& OperationResult)=0;
			virtual void Receive(const CSocketTCPReceiveParameters& Parameters, CSocketTCPReceiveResult& OperationResult)=0;
			virtual void ChangeBlockingState(bool BlockingState)=0;
			virtual int32 GetSendBufferSize(void)=0;
			virtual void SetSendBufferSize(int32 SendBufferSize)=0;
			virtual int32 GetReceiveBufferSize(void)=0;
			virtual void SetReceiveBufferSize(int32 ReceiveBufferSize)=0;

		public:
			ISocketTCPWrapper(void);
			virtual ~ISocketTCPWrapper(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														ISPSocketTCPWrapper=CSharedPointer<ISocketTCPWrapper>;
	using														ICSPSocketTCPWrapper=CSharedPointer<const ISocketTCPWrapper>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------