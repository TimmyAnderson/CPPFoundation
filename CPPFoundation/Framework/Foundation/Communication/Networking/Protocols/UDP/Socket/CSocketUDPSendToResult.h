//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Sockets/CSocketSendToResult.h>
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Socket/CSocketUDPAddress.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketUDPSendToResult final : public CSocketSendToResult
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CSocketUDPAddress									MAddress;
			CCSPByteBuffer										MData;
			Size												MOffset;
			Size												MNumberOfSentBytes;

		public:
			virtual const CSocketAddress& GetAddress(void) const noexcept override;
			virtual CCSPByteBuffer GetData(void) const noexcept override;
			virtual Size GetOffset(void) const noexcept override;
			virtual Size GetNumberOfSentBytes(void) const noexcept override;
			virtual void SetResult(const CSocketAddress& Address, CCSPByteBuffer Data, Size Offset, Size NumberOfSentBytes) override;
			const CSocketUDPAddress& GetUDPAddress(void) const noexcept;

		public:
			CSocketUDPSendToResult(void);
			virtual ~CSocketUDPSendToResult(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------