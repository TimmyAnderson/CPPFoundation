//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Sockets/CSocketSendResult.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Socket/CSocketTCPAddress.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPSendResult final : public CSocketSendResult
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPByteBuffer										MData;
			Size												MOffset;
			Size												MNumberOfSentBytes;

		public:
			virtual CCSPByteBuffer GetData(void) const noexcept override;
			virtual Size GetOffset(void) const noexcept override;
			virtual Size GetNumberOfSentBytes(void) const noexcept override;
			virtual void SetResult(CCSPByteBuffer Data, Size Offset, Size NumberOfSentBytes) override;

		public:
			CSocketTCPSendResult(void);
			virtual ~CSocketTCPSendResult(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------