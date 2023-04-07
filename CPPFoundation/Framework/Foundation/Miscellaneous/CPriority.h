//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Collections/IIsBeforeComparator.h>
#include <Framework/Foundation/Objects/CObject.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CPriority final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			class CPriorityComparer final : public CObject, IIsBeforeComparator<CPriority>
			{
//----------------------------------------------------------------------------------------------------------------------
				public:
					virtual bool IsBefore(const CPriority& Left, const CPriority& Right) const override;

				public:
					bool operator()(const CPriority& Priority1, const CPriority& Priority2) const noexcept;
//----------------------------------------------------------------------------------------------------------------------
			};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
		friend bool operator==(const CPriority& Left, const CPriority& Right) noexcept;
		friend bool operator!=(const CPriority& Left, const CPriority& Right) noexcept;
		friend bool operator<(const CPriority& Left, const CPriority& Right) noexcept;
		friend bool operator<=(const CPriority& Left, const CPriority& Right) noexcept;
		friend bool operator>(const CPriority& Left, const CPriority& Right) noexcept;
		friend bool operator>=(const CPriority& Left, const CPriority& Right) noexcept;

		public:
			using												PriorityType=int32;

		public:
			static const CPriority								PRIORITY_DEFAULT;
			static const CPriority								PRIORITY_MIN;
			static const CPriority								PRIORITY_MAX;

		private:
			PriorityType										MPriority;

		public:
			CPriority& operator=(const CPriority& Other);

		public:
			static const CPriority& Default(void) noexcept;
			static const CPriority& Min(void) noexcept;
			static const CPriority& Max(void) noexcept;

		public:
			virtual CString ToString(void) const override;

		public:
			PriorityType GetPriority(void) const noexcept;

		public:
			CPriority(void) noexcept;
			CPriority(PriorityType Priority) noexcept;
			CPriority(const CPriority& Other) noexcept;
			virtual ~CPriority(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool operator==(const CPriority& Left, const CPriority& Right) noexcept;
	bool operator!=(const CPriority& Left, const CPriority& Right) noexcept;
	bool operator<(const CPriority& Left, const CPriority& Right) noexcept;
	bool operator<=(const CPriority& Left, const CPriority& Right) noexcept;
	bool operator>(const CPriority& Left, const CPriority& Right) noexcept;
	bool operator>=(const CPriority& Left, const CPriority& Right) noexcept;
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------