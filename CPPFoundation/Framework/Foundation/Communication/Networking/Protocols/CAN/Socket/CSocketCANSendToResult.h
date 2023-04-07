//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Sockets/CSocketSendToResult.h>
#include <Framework/Foundation/Communication/Networking/Protocols/CAN/Socket/CSocketCANAddress.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketCANSendToResult final : public CSocketSendToResult
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CSocketCANAddress									MAddress;
			CCSPByteBuffer										MData;
			Size												MOffset;
			Size												MNumberOfSentBytes;

		public:
			virtual const CSocketAddress& GetAddress(void) const noexcept override;
			virtual CCSPByteBuffer GetData(void) const noexcept override;
			virtual Size GetOffset(void) const noexcept override;
			virtual Size GetNumberOfSentBytes(void) const noexcept override;
			virtual void SetResult(const CSocketAddress& Address, CCSPByteBuffer Data, Size Offset, Size NumberOfSentBytes) override;
			const CSocketCANAddress& GetCANAddress(void) const noexcept;

		public:
			CSocketCANSendToResult(void);
			virtual ~CSocketCANSendToResult(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------