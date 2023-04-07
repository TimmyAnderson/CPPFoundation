//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Socket/CSocketCANAddress.h>
#include "CSocketCANManagerMessageContext.h"
#include "CSocketCANManagerMessageResponse.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketCANManagerMessageResponseSocketWrite final : public CSocketCANManagerMessageResponse
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPSocketCANManagerMessageContext					MMessageContext;
			bool												MOperationSucceeded;
			CSocketCANAddress									MDestinationAddress;
			CCSPByteBuffer										MData;
			Size												MNumberOfBytesWritten;

		public:
			CSocketCANManagerMessageResponseSocketWrite& operator=(const CSocketCANManagerMessageResponseSocketWrite& Other);
			CSocketCANManagerMessageResponseSocketWrite& operator=(CSocketCANManagerMessageResponseSocketWrite&& Other) noexcept;

		public:
			virtual CString ToString(void) const override;
			CCSPSocketCANManagerMessageContext GetMessageContext(void) const noexcept;
			bool GetOperationSucceeded(void) const noexcept;
			const CSocketCANAddress& GetDestinationAddress(void) const noexcept;
			CCSPByteBuffer GetData(void) const noexcept;
			Size GetNumberOfBytesWritten(void) const noexcept;

		public:
			CSocketCANManagerMessageResponseSocketWrite(const CSocketID& SocketID, CCSPSocketCANManagerMessageContext MessageContext, bool OperationSucceeded, const CSocketCANAddress& DestinationAddress, CCSPByteBuffer Data, Size NumberOfBytesWritten);
			CSocketCANManagerMessageResponseSocketWrite(const CSocketCANManagerMessageResponseSocketWrite& Other);
			CSocketCANManagerMessageResponseSocketWrite(CSocketCANManagerMessageResponseSocketWrite&& Other) noexcept;
			virtual ~CSocketCANManagerMessageResponseSocketWrite(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketCANManagerMessageResponseSocketWrite=CSharedPointer<CSocketCANManagerMessageResponseSocketWrite>;
	using														CCSPSocketCANManagerMessageResponseSocketWrite=CSharedPointer<const CSocketCANManagerMessageResponseSocketWrite>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------