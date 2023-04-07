//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Sockets/CSocketSendParameters.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Socket/CSocketTCPAddress.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPSendParameters final : public CSocketSendParameters
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPByteBuffer										MData;
			Size												MOffset;
			Size												MNumberOfBytesToSend;

		public:
			virtual CCSPByteBuffer GetData(void) const noexcept override;
			virtual Size GetOffset(void) const noexcept override;
			virtual Size GetNumberOfBytesToSend(void) const noexcept override;

		public:
			CSocketTCPSendParameters(CCSPByteBuffer Data, Size Offset, Size NumberOfBytesToSend);
			virtual ~CSocketTCPSendParameters(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------