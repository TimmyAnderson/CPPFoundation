//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CList.h>
#include <Framework/Foundation/Objects/CObject.h>
#include "CSocketUDPManagerMessageRequestSocketWrite.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketUDPManagerWriteOperation final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPSocketUDPManagerMessageRequestSocketWrite		MPacket;
			Size												MNumberOfBytesToWrite;
			Size												MNumberOfBytesWritten;

		public:
			CCSPSocketUDPManagerMessageRequestSocketWrite GetPacket(void) const noexcept;
			Size GetNumberOfBytesToWrite(void) const noexcept;
			Size GetNumberOfBytesWritten(void) const noexcept;
			void AddNumberOfBytesWritten(Size Value) noexcept;

		public:
			CSocketUDPManagerWriteOperation(CCSPSocketUDPManagerMessageRequestSocketWrite Packet);
			virtual ~CSocketUDPManagerWriteOperation(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSocketUDPManagerWriteOperationCollection=CList<CSocketUDPManagerWriteOperation>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------