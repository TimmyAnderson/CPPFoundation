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
	class CSocketReceiveFromParameters : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			virtual CSPByteBuffer GetData(void) const noexcept=0;
			virtual Size GetOffset(void) const noexcept=0;
			virtual Size GetNumberOfBytesToReceive(void) const noexcept=0;

		public:
			CSocketReceiveFromParameters(void);
			virtual ~CSocketReceiveFromParameters(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------