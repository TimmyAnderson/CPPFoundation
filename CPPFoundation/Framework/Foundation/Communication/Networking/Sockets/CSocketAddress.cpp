//----------------------------------------------------------------------------------------------------------------------
#include "CSocketAddress.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	CSocketAddress::CSocketAddress(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketAddress::~CSocketAddress(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketAddress::operator==(const CSocketAddress& Other) const
	{
		return(Equals(Other));
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CSocketAddress::operator!=(const CSocketAddress& Other) const
	{
		return(!(*this==Other));
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------