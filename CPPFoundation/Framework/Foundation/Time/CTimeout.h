//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Strings/CString.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CTimeout final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		friend bool operator==(const CTimeout& Left, const CTimeout& Right);
		friend bool operator!=(const CTimeout& Left, const CTimeout& Right);
		friend bool operator<(const CTimeout& Left, const CTimeout& Right);
		friend bool operator<=(const CTimeout& Left, const CTimeout& Right);
		friend bool operator>(const CTimeout& Left, const CTimeout& Right);
		friend bool operator>=(const CTimeout& Left, const CTimeout& Right);

		private:
			static CTimeout										ZERO_TIMEOUT;
			static CTimeout										INFINITE_TIMEOUT;

		private:
			bool												MIsInfinite;
			int64												MTimeoutInMS;

		public:
			CTimeout& operator=(const CTimeout& Other);
			CTimeout operator+(int64 Value);

		public:
			static const CTimeout& GetZero(void);
			static const CTimeout& GetInfinite(void);

		public:
			static CTimeout Min(const CTimeout& Left, const CTimeout& Right);
			static CTimeout Max(const CTimeout& Left, const CTimeout& Right);
			static CTimeout Min(std::initializer_list<CTimeout> Timeouts);
			static CTimeout Max(std::initializer_list<CTimeout> Timeouts);

		public:
			virtual CString ToString(void) const override;
			int64 GetTimeoutInMS(void) const noexcept;
			bool IsInfinite(void) const noexcept;
			bool IsZero(void) const noexcept;

		public:
			CTimeout(void);
			CTimeout(const CTimeout& Other);
			CTimeout(int64 TimeoutInMS);
			virtual ~CTimeout(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool operator==(const CTimeout& Left, const CTimeout& Right);
	bool operator!=(const CTimeout& Left, const CTimeout& Right);
	bool operator<(const CTimeout& Left, const CTimeout& Right);
	bool operator<=(const CTimeout& Left, const CTimeout& Right);
	bool operator>(const CTimeout& Left, const CTimeout& Right);
	bool operator>=(const CTimeout& Left, const CTimeout& Right);
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------