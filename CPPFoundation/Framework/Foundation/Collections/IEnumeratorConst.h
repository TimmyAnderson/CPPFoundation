//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Types/CSharedPointer.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	template<typename TItemType>
	class IEnumeratorConst
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			virtual void Reset(void)=0;
			virtual bool MoveNext(void)=0;
			virtual const TItemType& GetCurrentConst(void) const=0;

		public:
			IEnumeratorConst(void)
			{
			}

			virtual ~IEnumeratorConst(void)
			{
			}
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------