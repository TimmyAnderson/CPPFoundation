//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Strings/CString.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CLogCategory final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		private:
			CString												MCategoryType;
			Size												MCategoryTypeHash;

		public:
			CLogCategory& operator=(const CLogCategory& Other);
			CLogCategory& operator=(CLogCategory&& Other) noexcept;
			bool operator==(const CLogCategory& Other) const;
			bool operator!=(const CLogCategory& Other) const;

		public:
			const CString& GetCategoryType(void) const noexcept;
			Size GetHash(void) const;

		public:
			CLogCategory(const CString& CategoryType);
			CLogCategory(CString&& CategoryType);
			CLogCategory(const CLogCategory& Other);
			CLogCategory(CLogCategory&& Other) noexcept;
			virtual ~CLogCategory(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------