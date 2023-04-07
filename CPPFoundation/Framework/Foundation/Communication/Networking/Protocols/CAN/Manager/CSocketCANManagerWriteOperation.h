//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CList.h>
#include <Framework/Foundation/Objects/CObject.h>
#include "CSocketCANManagerMessageRequestSocketWrite.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketCANManagerWriteOperation final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPSocketCANManagerMessageRequestSocketWrite		MPacket;
			Size												MNumberOfBytesToWrite;
			Size												MNumberOfBytesWritten;

		public:
			CCSPSocketCANManagerMessageRequestSocketWrite GetPacket(void) const noexcept;
			Size GetNumberOfBytesToWrite(void) const noexcept;
			Size GetNumberOfBytesWritten(void) const noexcept;
			void AddNumberOfBytesWritten(Size Value) noexcept;

		public:
			CSocketCANManagerWriteOperation(CCSPSocketCANManagerMessageRequestSocketWrite Packet);
			virtual ~CSocketCANManagerWriteOperation(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSocketCANManagerWriteOperationCollection=CList<CSocketCANManagerWriteOperation>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------