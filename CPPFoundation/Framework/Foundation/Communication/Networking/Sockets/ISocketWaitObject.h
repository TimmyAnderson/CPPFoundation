//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CVector.h>
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Strings/CString.h>
#include <Framework/Foundation/Time/CTimeout.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
#include "CSocket.h"
#include "CSocketWaitState.h"
#include "ESocketWaitEvent.h"
#include "ESocketWaitFlags.h"
#include "ESocketWaitResultFlags.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class ISocketWaitObject : public virtual CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			virtual Size GetMaximumNumberOfSocket(void) const=0;
			virtual ESocketWaitEvent WaitForEvent(CVector<CSocketWaitState>& Sockets, const CTimeout& Timeout)=0;
			virtual void SetEvent(void)=0;
			virtual void ResetEvent(void)=0;

		public:
			ISocketWaitObject(void);
			virtual ~ISocketWaitObject(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														ISPSocketWaitObject=CSharedPointer<ISocketWaitObject>;
	using														ICSPSocketWaitObject=CSharedPointer<const ISocketWaitObject>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------