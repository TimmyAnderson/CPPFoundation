//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Miscellaneous/CID.h>
#include <Framework/Foundation/Strings/CString.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CParserParameterID final : public CID
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			CParserParameterID& operator=(const CParserParameterID& Other);
			CParserParameterID& operator=(CParserParameterID&& Other) noexcept;

		public:
			CParserParameterID(const CString& ID);
			CParserParameterID(CString&& ID);
			CParserParameterID(CCSPString ID);
			CParserParameterID(const CParserParameterID& ID);
			CParserParameterID(CParserParameterID&& ID) noexcept;
			virtual ~CParserParameterID(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------