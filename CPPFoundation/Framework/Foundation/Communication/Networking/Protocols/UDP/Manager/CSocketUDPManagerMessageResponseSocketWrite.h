//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Socket/CSocketUDPAddress.h>
#include "CSocketUDPManagerMessageContext.h"
#include "CSocketUDPManagerMessageResponse.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketUDPManagerMessageResponseSocketWrite final : public CSocketUDPManagerMessageResponse
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPSocketUDPManagerMessageContext					MMessageContext;
			bool												MOperationSucceeded;
			CSocketUDPAddress									MDestinationAddress;
			CCSPByteBuffer										MData;
			Size												MNumberOfBytesWritten;

		public:
			CSocketUDPManagerMessageResponseSocketWrite& operator=(const CSocketUDPManagerMessageResponseSocketWrite& Other);
			CSocketUDPManagerMessageResponseSocketWrite& operator=(CSocketUDPManagerMessageResponseSocketWrite&& Other);

		public:
			virtual CString ToString(void) const override;
			CCSPSocketUDPManagerMessageContext GetMessageContext(void) const noexcept;
			bool GetOperationSucceeded(void) const noexcept;
			const CSocketUDPAddress& GetDestinationAddress(void) const noexcept;
			CCSPByteBuffer GetData(void) const noexcept;
			Size GetNumberOfBytesWritten(void) const noexcept;

		public:
			CSocketUDPManagerMessageResponseSocketWrite(const CSocketID& SocketID, CCSPSocketUDPManagerMessageContext MessageContext, bool OperationSucceeded, const CSocketUDPAddress& DestinationAddress, CCSPByteBuffer Data, Size NumberOfBytesWritten);
			CSocketUDPManagerMessageResponseSocketWrite(const CSocketUDPManagerMessageResponseSocketWrite& Other);
			CSocketUDPManagerMessageResponseSocketWrite(CSocketUDPManagerMessageResponseSocketWrite&& Other);
			virtual ~CSocketUDPManagerMessageResponseSocketWrite(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketUDPManagerMessageResponseSocketWrite=CSharedPointer<CSocketUDPManagerMessageResponseSocketWrite>;
	using														CCSPSocketUDPManagerMessageResponseSocketWrite=CSharedPointer<const CSocketUDPManagerMessageResponseSocketWrite>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------