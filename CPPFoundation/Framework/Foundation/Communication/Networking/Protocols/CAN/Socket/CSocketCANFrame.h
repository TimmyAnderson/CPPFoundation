//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Collections/CByteBuffer.h>
#include "CSocketCANID.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketCANFrame final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			const static Size									CAN_ID_LENGTH;
			const static Size									CAN_DATA_LENGTH;
			const static Size									CAN_FRAME_LENGTH;

		private:
			CSocketCANID										MCANID;
			CByteBuffer											MCANData;

		public:
			CSocketCANFrame& operator=(const CSocketCANFrame& Other);
			CSocketCANFrame& operator=(CSocketCANFrame&& Other) noexcept;
			bool operator==(const CSocketCANFrame& Other) const;
			bool operator!=(const CSocketCANFrame& Other) const;

		public:
			virtual CString ToString(void) const override;
			const CSocketCANID& GetCANID(void) const noexcept;
			const CByteBuffer& GetCANData(void) const noexcept;

		public:
			CByteBuffer Serialize(void) const;
			void Deserialize(const CByteBuffer& Data);

		public:
			CSocketCANFrame(void);
			CSocketCANFrame(const CSocketCANID& CANID, const CByteBuffer& CANData);
			CSocketCANFrame(const CSocketCANID& CANID, CByteBuffer&& CANData);
			CSocketCANFrame(CSocketCANID&& CANID, CByteBuffer&& CANData);
			CSocketCANFrame(const CSocketCANFrame& Other);
			CSocketCANFrame(CSocketCANFrame&& Other) noexcept;
			virtual ~CSocketCANFrame(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------