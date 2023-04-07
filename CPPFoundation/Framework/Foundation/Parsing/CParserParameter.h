//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Types/CSharedPointer.h>
#include "CParserParameterID.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CParserParameter : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CParserParameterID									MParameterID;

		public:
			const CParserParameterID& GetParameterID(void) const noexcept;

		public:
			CParserParameter(const CParserParameterID& ParameterID);
			virtual ~CParserParameter(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CSPParserParameter=CSharedPointer<CParserParameter>;
	using														CCSPParserParameter=CSharedPointer<const CParserParameter>;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------