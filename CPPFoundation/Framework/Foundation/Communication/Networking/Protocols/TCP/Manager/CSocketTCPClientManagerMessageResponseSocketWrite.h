//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CSocketTCPClientManagerMessageResponse.h"
#include "CSocketTCPClientManagerMessageContext.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPClientManagerMessageResponseSocketWrite final : public CSocketTCPClientManagerMessageResponse
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPSocketTCPClientManagerMessageContext			MMessageContext;
			bool												MOperationSucceeded;
			CCSPByteBuffer										MData;
			Size												MNumberOfBytesWritten;

		public:
			CSocketTCPClientManagerMessageResponseSocketWrite& operator=(const CSocketTCPClientManagerMessageResponseSocketWrite& Other);
			CSocketTCPClientManagerMessageResponseSocketWrite& operator=(CSocketTCPClientManagerMessageResponseSocketWrite&& Other);

		public:
			virtual CString ToString(void) const override;
			CCSPSocketTCPClientManagerMessageContext GetMessageContext(void) const noexcept;
			bool GetOperationSucceeded(void) const noexcept;
			CCSPByteBuffer GetData(void) const noexcept;
			Size GetNumberOfBytesWritten(void) const noexcept;

		public:
			CSocketTCPClientManagerMessageResponseSocketWrite(const CSocketID& SocketID, CCSPSocketTCPClientManagerMessageContext MessageContext, bool OperationSucceeded, CCSPByteBuffer Data, Size NumberOfBytesWritten);
			CSocketTCPClientManagerMessageResponseSocketWrite(const CSocketTCPClientManagerMessageResponseSocketWrite& Other);
			CSocketTCPClientManagerMessageResponseSocketWrite(CSocketTCPClientManagerMessageResponseSocketWrite&& Other);
			virtual ~CSocketTCPClientManagerMessageResponseSocketWrite(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPSocketTCPClientManagerMessageResponseSocketWrite=CSharedPointer<CSocketTCPClientManagerMessageResponseSocketWrite>;
	using														CCSPSocketTCPClientManagerMessageResponseSocketWrite=CSharedPointer<const CSocketTCPClientManagerMessageResponseSocketWrite>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------