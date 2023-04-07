//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Sockets/CSocketSendToParameters.h>
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Socket/CSocketUDPAddress.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketUDPSendToParameters final : public CSocketSendToParameters
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CSocketUDPAddress									MAddress;
			CCSPByteBuffer										MData;
			Size												MOffset;
			Size												MNumberOfBytesToSend;

		public:
			virtual const CSocketAddress& GetAddress(void) const noexcept override;
			virtual CCSPByteBuffer GetData(void) const noexcept override;
			virtual Size GetOffset(void) const noexcept override;
			virtual Size GetNumberOfBytesToSend(void) const noexcept override;
			const CSocketUDPAddress& GetUDPAddress(void) const noexcept;

		public:
			CSocketUDPSendToParameters(const CSocketAddress& Address, CCSPByteBuffer Data, Size Offset, Size NumberOfBytesToSend);
			virtual ~CSocketUDPSendToParameters(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------