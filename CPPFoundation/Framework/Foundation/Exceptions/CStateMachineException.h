//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CException.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CStateMachineException final : public CException
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CStateMachineException& operator=(const CStateMachineException& Other);
			CStateMachineException& operator=(CStateMachineException&& Other) noexcept;

		public:
			CStateMachineException(void);
			CStateMachineException(const CString& Message);
			CStateMachineException(CString&& Message);
			CStateMachineException(const std::exception& Exception);
			CStateMachineException(const CString& Message, const std::exception& Exception);
			CStateMachineException(const CString& Message, const CException& Exception);
			CStateMachineException(const CStateMachineException& Other);
			CStateMachineException(CStateMachineException&& Other) noexcept;
			virtual ~CStateMachineException(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------