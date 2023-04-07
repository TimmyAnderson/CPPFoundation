//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CList.h>
#include <Framework/Foundation/Objects/CObject.h>
#include "CSocketTCPClientManagerMessageRequestSocketWrite.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketTCPClientManagerWriteOperation final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CCSPSocketTCPClientManagerMessageRequestSocketWrite	MPacket;
			Size												MNumberOfBytesToWrite;
			Size												MNumberOfBytesWritten;

		public:
			CCSPSocketTCPClientManagerMessageRequestSocketWrite GetPacket(void) const noexcept;
			bool WriteOperationCompleted(void) const noexcept;
			Size GetNumberOfBytesToWrite(void) const noexcept;
			Size GetNumberOfBytesWritten(void) const noexcept;
			void AddNumberOfBytesWritten(Size Value) noexcept;

		public:
			CSocketTCPClientManagerWriteOperation(CCSPSocketTCPClientManagerMessageRequestSocketWrite Packet);
			virtual ~CSocketTCPClientManagerWriteOperation(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSocketTCPClientManagerWriteOperationCollection=CList<CSocketTCPClientManagerWriteOperation>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------