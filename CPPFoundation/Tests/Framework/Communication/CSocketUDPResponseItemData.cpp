//----------------------------------------------------------------------------------------------------------------------
#include "CSocketUDPResponseItemData.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace CPPFoundation::Foundation;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPResponseItemData::CSocketUDPResponseItemData(const CValueCollection& ValueCollection)
		: MResponseItemDataMode(ESocketUDPResponseItemDataMode::E_DATA), MValueCollection(ValueCollection), MIndexCollection(), MValueGenerator()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPResponseItemData::CSocketUDPResponseItemData(const CIndexCollection& IndexCollection)
		: MResponseItemDataMode(ESocketUDPResponseItemDataMode::E_USE_REQUEST_DATA), MValueCollection(), MIndexCollection(IndexCollection), MValueGenerator()
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPResponseItemData::CSocketUDPResponseItemData(const CValueGeneratorCallback& ValueGenerator)
		: MResponseItemDataMode(ESocketUDPResponseItemDataMode::E_USE_VALUE_GENERATOR), MValueCollection(), MIndexCollection(), MValueGenerator(ValueGenerator)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CSocketUDPResponseItemData::~CSocketUDPResponseItemData(void)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	ESocketUDPResponseItemDataMode CSocketUDPResponseItemData::GetResponseItemDataMode(void) const noexcept
	{
		return(MResponseItemDataMode);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CSocketUDPResponseItemData::CValueCollection& CSocketUDPResponseItemData::GetValueCollection(void) const noexcept
	{
		return(MValueCollection);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CSocketUDPResponseItemData::CIndexCollection& CSocketUDPResponseItemData::GetIndexCollection(void) const noexcept
	{
		return(MIndexCollection);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CSocketUDPResponseItemData::CValueGeneratorCallback& CSocketUDPResponseItemData::GetValueGenerator(void) const noexcept
	{
		return(MValueGenerator);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------