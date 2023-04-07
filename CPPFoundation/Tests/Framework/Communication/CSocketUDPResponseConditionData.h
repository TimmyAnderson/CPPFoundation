//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CByteBuffer.h>
#include "ESocketUDPResponseConditionDataComparisonMode.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketUDPResponseConditionData final : public CPPFoundation::Foundation::CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			ESocketUDPResponseConditionDataComparisonMode		MComparisonMode;
			CPPFoundation::Foundation::CByteBuffer					MBytesToCompare;

		public:
			ESocketUDPResponseConditionDataComparisonMode GetComparisonMode(void) const noexcept;
			const CPPFoundation::Foundation::CByteBuffer& GetBytesToCompare(void) const noexcept;

		public:
			CSocketUDPResponseConditionData(ESocketUDPResponseConditionDataComparisonMode ComparisonMode, const CPPFoundation::Foundation::CByteBuffer& BytesToCompare);
			virtual ~CSocketUDPResponseConditionData(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------