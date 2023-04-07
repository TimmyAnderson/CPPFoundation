//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Sockets/CSocketReceiveFromResult.h>
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Socket/CSocketCANAddress.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketCANReceiveFromResult final : public CSocketReceiveFromResult
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CSPByteBuffer										MData;
			Size												MOffset;
			Size												MNumberOfReceivedBytes;
			CSocketCANAddress									MAddress;

		public:
			virtual CSPByteBuffer GetData(void) const noexcept override;
			virtual Size GetOffset(void) const noexcept override;
			virtual Size GetNumberOfReceivedBytes(void) const noexcept override;
			virtual const CSocketAddress& GetAddress(void) const noexcept override;
			virtual void SetResult(CSPByteBuffer Data, Size Offset, Size NumberOfReceivedBytes, const CSocketAddress& Address) override;
			const CSocketCANAddress& GetCANAddress(void) const noexcept;

		public:
			CSocketCANReceiveFromResult(void);
			virtual ~CSocketCANReceiveFromResult(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------