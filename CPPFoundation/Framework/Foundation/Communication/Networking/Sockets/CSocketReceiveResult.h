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
	class CSocketReceiveResult : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			virtual bool GetOperationSucceeded(void) const noexcept=0;
			virtual CSPByteBuffer GetData(void) const noexcept=0;
			virtual Size GetOffset(void) const noexcept=0;
			virtual Size GetNumberOfReceivedBytes(void) const noexcept=0;
			virtual void SetResult(bool OperationSucceeded, CSPByteBuffer Data, Size Offset, Size NumberOfReceivedBytes)=0;

		public:
			CSocketReceiveResult(void);
			virtual ~CSocketReceiveResult(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------