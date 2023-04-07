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
	class CSocketSendToResult : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			virtual const CSocketAddress& GetAddress(void) const noexcept=0;
			virtual CCSPByteBuffer GetData(void) const noexcept=0;
			virtual Size GetOffset(void) const noexcept=0;
			virtual Size GetNumberOfSentBytes(void) const noexcept=0;
			virtual void SetResult(const CSocketAddress& Address, CCSPByteBuffer Data, Size Offset, Size NumberOfSentBytes)=0;

		public:
			CSocketSendToResult(void);
			virtual ~CSocketSendToResult(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------