//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CStateMachinesProcessorSettings : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CStateMachinesProcessorSettings(void);
			virtual ~CStateMachinesProcessorSettings(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPStateMachinesProcessorSettings=CSharedPointer<CStateMachinesProcessorSettings>;
	using														CCSPStateMachinesProcessorSettings=CSharedPointer<const CStateMachinesProcessorSettings>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------