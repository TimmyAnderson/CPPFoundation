//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/CByteBuffer.h>
#include <Framework/Foundation/Collections/CVector.h>
#include <Framework/Foundation/Types/CFunction.h>
#include "ESocketUDPResponseItemDataMode.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Testing
{
//----------------------------------------------------------------------------------------------------------------------
	class CSocketUDPResponseItemData final : public CPPFoundation::Foundation::CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			using												CValueCollection=CPPFoundation::Foundation::CByteBuffer;
			using												CIndexCollection=CPPFoundation::Foundation::CVector<Size>;
			using												CValueGeneratorCallback=CPPFoundation::Foundation::CFunction<CPPFoundation::Foundation::CByteBuffer(const CPPFoundation::Foundation::CByteBuffer&)>;

		private:
			ESocketUDPResponseItemDataMode						MResponseItemDataMode;
			CValueCollection									MValueCollection;
			CIndexCollection									MIndexCollection;
			CValueGeneratorCallback								MValueGenerator;

		public:
			ESocketUDPResponseItemDataMode GetResponseItemDataMode(void) const noexcept;
			const CValueCollection& GetValueCollection(void) const noexcept;
			const CIndexCollection& GetIndexCollection(void) const noexcept;
			const CValueGeneratorCallback& GetValueGenerator(void) const noexcept;

		public:
			CSocketUDPResponseItemData(const CValueCollection& ValueCollection);
			CSocketUDPResponseItemData(const CIndexCollection& IndexCollection);
			CSocketUDPResponseItemData(const CValueGeneratorCallback& ValueGenerator);
			virtual ~CSocketUDPResponseItemData(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------