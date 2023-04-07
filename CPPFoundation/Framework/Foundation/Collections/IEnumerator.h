//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <type_traits>
#include <Framework/Foundation/Types/CSharedPointer.h>
#include "IEnumeratorConst.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	template<typename TItemType>
	class IEnumerator : public IEnumeratorConst<TItemType>
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			virtual TItemType& GetCurrent(void)=0;

		public:
			IEnumerator(void)
			{
			}

			virtual ~IEnumerator(void) override
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------