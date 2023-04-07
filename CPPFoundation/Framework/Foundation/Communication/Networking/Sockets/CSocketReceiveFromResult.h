//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CByteBuffer.h>
#include <Framework/Foundation/Objects/CObject.h>
#include "CSocketAddress.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketReceiveFromResult : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			virtual CSPByteBuffer GetData(void) const noexcept=0;
			virtual Size GetOffset(void) const noexcept=0;
			virtual Size GetNumberOfReceivedBytes(void) const noexcept=0;
			virtual const CSocketAddress& GetAddress(void) const noexcept=0;
			virtual void SetResult(CSPByteBuffer Data, Size Offset, Size NumberOfReceivedBytes, const CSocketAddress& Address)=0;

		public:
			CSocketReceiveFromResult(void);
			virtual ~CSocketReceiveFromResult(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------