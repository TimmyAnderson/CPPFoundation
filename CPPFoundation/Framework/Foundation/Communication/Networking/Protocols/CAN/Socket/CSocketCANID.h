//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Strings/CString.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketCANID final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			const static uint32									CAN_EXTENDED_FRAME_FLAG;
			const static uint32									CAN_REMOTE_FRAME_FLAG;
			const static uint32									CAN_ERROR_FRAME_FLAG;
			const static uint32									CAN_STANDARD_FRAME_MASK;
			const static uint32									CAN_EXTENDED_FRAME_MASK;
			const static uint32									CAN_ERROR_FRAME_MASK;

		private:
			uint32												MID;

		public:
			bool operator==(const CSocketCANID& Other) const;
			bool operator!=(const CSocketCANID& Other) const;

		public:
			virtual CString ToString(void) const override;
			bool IsExtendedFrame(void) const noexcept;
			bool IsRemoteFrame(void) const noexcept;
			bool IsErrorFrame(void) const noexcept;
			uint32 GetID(void) const noexcept;
			uint32 GetMaskedID(void) const noexcept;
			uint32 GetAdjustedID(void) const noexcept;

		public:
			CSocketCANID(void);
			CSocketCANID(bool ExtendedFrame, bool RemoteFrame, bool ErrorFrame, uint32 ID);
			CSocketCANID(uint32 ID);
			virtual ~CSocketCANID(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------