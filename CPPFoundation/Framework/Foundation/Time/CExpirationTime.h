//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Objects/CObject.h>
#include "CTimeout.h"
#include "CSteadyClock.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CExpirationTime final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		friend bool operator==(const CExpirationTime& Left, const CExpirationTime& Right);
		friend bool operator!=(const CExpirationTime& Left, const CExpirationTime& Right);
		friend bool operator<(const CExpirationTime& Left, const CExpirationTime& Right);
		friend bool operator<=(const CExpirationTime& Left, const CExpirationTime& Right);
		friend bool operator>(const CExpirationTime& Left, const CExpirationTime& Right);
		friend bool operator>=(const CExpirationTime& Left, const CExpirationTime& Right);

		private:
			bool												MIsInfinite;
			CSteadyClock::Milliseconds							MExpirationTimeInMS;

		private:
			static CExpirationTime								ZERO_EXPIRATION_TIME;
			static CExpirationTime								INFINITE_EXPIRATION_TIME;

		public:
			CExpirationTime& operator=(const CExpirationTime& Other);

		public:
			static const CExpirationTime& GetZero(void);
			static const CExpirationTime& GetInfinite(void);

		public:
			static CExpirationTime Min(const CExpirationTime& Left, const CExpirationTime& Right);
			static CExpirationTime Max(const CExpirationTime& Left, const CExpirationTime& Right);
			static CExpirationTime Min(std::initializer_list<CExpirationTime> ExpirationTimes);
			static CExpirationTime Max(std::initializer_list<CExpirationTime> ExpirationTimes);

		public:
			virtual CString ToString(void) const override;
			bool IsInfinite(void) const noexcept;
			CSteadyClock::Milliseconds GetExpirationTime(void) const noexcept;
			void Reset(void);
			void Reset(const CExpirationTime& Other);
			void Reset(CSteadyClock::Milliseconds TimeoutInMS);
			void Reset(const CTimeout& Timeout);
			void AddTimeout(CTimeout Timeout);
			CTimeout CalculateTimeout(CSteadyClock::Milliseconds CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds()) const;
			bool HasExpired(CSteadyClock::Milliseconds CurrentTimeInMS=CSteadyClock::GetCurrentTimeInMilliseconds()) const;

		public:
			CExpirationTime(void);
			CExpirationTime(const CExpirationTime& Other);
			CExpirationTime(CSteadyClock::Milliseconds TimeoutInMS, CSteadyClock::Milliseconds CurrentTime=CSteadyClock::GetCurrentTimeInMilliseconds());
			CExpirationTime(const CTimeout& Timeout);
			virtual ~CExpirationTime(void) override;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool operator==(const CExpirationTime& Left, const CExpirationTime& Right);
	bool operator!=(const CExpirationTime& Left, const CExpirationTime& Right);
	bool operator<(const CExpirationTime& Left, const CExpirationTime& Right);
	bool operator<=(const CExpirationTime& Left, const CExpirationTime& Right);
	bool operator>(const CExpirationTime& Left, const CExpirationTime& Right);
	bool operator>=(const CExpirationTime& Left, const CExpirationTime& Right);
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------