//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Sockets/CSocketReceiveFromResult.h>
#include <Framework/Foundation/Communication/Networking/Protocols/UDP/Socket/CSocketUDPAddress.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketUDPReceiveFromResult final : public CSocketReceiveFromResult
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CSPByteBuffer										MData;
			Size												MOffset;
			Size												MNumberOfReceivedBytes;
			CSocketUDPAddress									MAddress;

		public:
			virtual CSPByteBuffer GetData(void) const noexcept override;
			virtual Size GetOffset(void) const noexcept override;
			virtual Size GetNumberOfReceivedBytes(void) const noexcept override;
			virtual const CSocketAddress& GetAddress(void) const noexcept override;
			virtual void SetResult(CSPByteBuffer Data, Size Offset, Size NumberOfReceivedBytes, const CSocketAddress& Address) override;
			const CSocketUDPAddress& GetUDPAddress(void) const noexcept;

		public:
			CSocketUDPReceiveFromResult(void);
			virtual ~CSocketUDPReceiveFromResult(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------