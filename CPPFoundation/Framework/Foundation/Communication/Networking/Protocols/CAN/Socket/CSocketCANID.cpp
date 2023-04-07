//----------------------------------------------------------------------------------------------------------------------
#include "CSocketCANID.h"
#include <Framework/Platform/Global/CConstants.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace CPPFoundation::Platform;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const uint32												CSocketCANID::CAN_EXTENDED_FRAME_FLAG=CConstants::CAN_EXTENDED_FRAME_FLAG;
	const uint32												CSocketCANID::CAN_REMOTE_FRAME_FLAG=CConstants::CAN_REMOTE_FRAME_FLAG;
	const uint32												CSocketCANID::CAN_ERROR_FRAME_FLAG=CConstants::CAN_ERROR_FRAME_FLAG;
	const uint32												CSocketCANID::CAN_STANDARD_FRAME_MASK=CConstants::CAN_STANDARD_FRAME_MASK;
	const uint32												CSocketCANID::CAN_EXTENDED_FRAME_MASK=CConstants::CAN_EXTENDED_FRAME_MASK;
	const uint32												CSocketCANID::CAN_ERROR_FRAME_MASK=CConstants::CAN_ERROR_FRAME_MASK;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANID::CSocketCANID(void)
		: MID(0)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANID::CSocketCANID(bool ExtendedFrame, bool RemoteFrame, bool ErrorFrame, uint32 ID)
		: MID(0)
	{
		uint32													Flags=0;

		if (ExtendedFrame==false)
		{
			ID&=CAN_STANDARD_FRAME_MASK;
		}
		else
		{
			ID&=CAN_EXTENDED_FRAME_MASK;
			Flags|=CAN_EXTENDED_FRAME_FLAG;
		}

		if (RemoteFrame==true)
		{
			Flags|=CAN_REMOTE_FRAME_FLAG;
		}

		if (ErrorFrame==true)
		{
			ID&=CAN_ERROR_FRAME_MASK;
			Flags|=CAN_ERROR_FRAME_FLAG;
		}

		MID=(Flags | ID);
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANID::CSocketCANID(uint32 ID)
		: MID(ID)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketCANID::~CSocketCANID(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketCANID::operator==(const CSocketCANID& Other) const
	{
		if (MID!=Other.MID)
		{
			return(false);
		}

		return(true);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketCANID::operator!=(const CSocketCANID& Other) const
	{
		return(!(*this==Other));
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CSocketCANID::ToString(void) const
	{
		CString													Flags;

		if (IsExtendedFrame()==true)
		{
			Flags+="EXTENDED";
		}

		if (IsRemoteFrame()==true)
		{
			if (Flags.IsEmpty()==false)
			{
				Flags+=" ";
			}

			Flags+="REMOTE";
		}

		if (IsErrorFrame()==true)
		{
			if (Flags.IsEmpty()==false)
			{
				Flags+=" ";
			}

			Flags+="ERROR";
		}

		return(CString::Format("ID [",ToHexaDecimalString(GetMaskedID(),true),"] FLAGS [",Flags,"]"));
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketCANID::IsExtendedFrame(void) const noexcept
	{
		if ((MID & CAN_EXTENDED_FRAME_FLAG)!=0)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketCANID::IsRemoteFrame(void) const noexcept
	{
		if ((MID & CAN_REMOTE_FRAME_FLAG)!=0)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketCANID::IsErrorFrame(void) const noexcept
	{
		if ((MID & CAN_ERROR_FRAME_FLAG)!=0)
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	uint32 CSocketCANID::GetID(void) const noexcept
	{
		return(MID);
	}
//----------------------------------------------------------------------------------------------------------------------
	uint32 CSocketCANID::GetMaskedID(void) const noexcept
	{
		if (IsErrorFrame()==true)
		{
			uint32												MaskedID=(MID & CAN_ERROR_FRAME_MASK);

			return(MaskedID);
		}

		if (IsExtendedFrame()==false)
		{
			uint32												MaskedID=(MID & CAN_STANDARD_FRAME_MASK);

			return(MaskedID);
		}
		else
		{
			uint32												MaskedID=(MID & CAN_EXTENDED_FRAME_MASK);

			return(MaskedID);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	uint32 CSocketCANID::GetAdjustedID(void) const noexcept
	{
		static const Size										BIT_SHIFT=3;

		return(GetMaskedID() << BIT_SHIFT);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------