//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Communication/Networking/Sockets/CSocketReceiveFromParameters.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketUDPReceiveFromParameters final : public CSocketReceiveFromParameters
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
			CSocketUDPReceiveFromParameters(CSPByteBuffer Data, Size Offset, Size NumberOfBytesToReceive);
			virtual ~CSocketUDPReceiveFromParameters(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------