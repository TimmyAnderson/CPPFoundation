//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Sockets/CSocketSendToParameters.h>
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Socket/CSocketCANAddress.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketCANSendToParameters final : public CSocketSendToParameters
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CSocketCANAddress									MAddress;
			CCSPByteBuffer										MData;
			Size												MOffset;
			Size												MNumberOfBytesToSend;

		public:
			virtual const CSocketAddress& GetAddress(void) const noexcept override;
			virtual CCSPByteBuffer GetData(void) const noexcept override;
			virtual Size GetOffset(void) const noexcept override;
			virtual Size GetNumberOfBytesToSend(void) const noexcept override;
			const CSocketCANAddress& GetCANAddress(void) const noexcept;

		public:
			CSocketCANSendToParameters(const CSocketAddress& Address, CCSPByteBuffer Data, Size Offset, Size NumberOfBytesToSend);
			virtual ~CSocketCANSendToParameters(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------