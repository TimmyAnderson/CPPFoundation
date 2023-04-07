//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Sockets/CSocketReceiveParameters.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPReceiveParameters final : public CSocketReceiveParameters
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CSPByteBuffer										MData;
			Size												MOffset;
			Size												MNumberOfBytesToReceive;

		public:
			virtual CSPByteBuffer GetData(void) const noexcept override;
			virtual Size GetOffset(void) const noexcept override;
			virtual Size GetNumberOfBytesToReceive(void) const noexcept override;

		public:
			CSocketTCPReceiveParameters(CSPByteBuffer Data, Size Offset, Size NumberOfBytesToReceive);
			virtual ~CSocketTCPReceiveParameters(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------