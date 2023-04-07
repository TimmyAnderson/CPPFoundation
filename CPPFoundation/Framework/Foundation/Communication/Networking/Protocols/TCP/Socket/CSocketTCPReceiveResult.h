//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Sockets/CSocketReceiveResult.h>
#include <Framework/Foundation/Communication/Networking/Protocols/TCP/Socket/CSocketTCPAddress.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPReceiveResult final : public CSocketReceiveResult
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			bool												MOperationSucceeded;
			CSPByteBuffer										MData;
			Size												MOffset;
			Size												MNumberOfReceivedBytes;

		public:
			virtual bool GetOperationSucceeded(void) const noexcept override;
			virtual CSPByteBuffer GetData(void) const noexcept override;
			virtual Size GetOffset(void) const noexcept override;
			virtual Size GetNumberOfReceivedBytes(void) const noexcept override;
			virtual void SetResult(bool OperationSucceeded, CSPByteBuffer Data, Size Offset, Size NumberOfReceivedBytes) override;

		public:
			CSocketTCPReceiveResult(void);
			virtual ~CSocketTCPReceiveResult(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------