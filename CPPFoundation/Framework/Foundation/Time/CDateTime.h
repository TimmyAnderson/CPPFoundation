//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <Framework/Foundation/Objects/CObject.h>
#include <Framework/Foundation/Exceptions/CInvalidOperationException.h>
#include <Framework/Foundation/Strings/CString.h>
#include <Framework/Foundation/Types/CNullable.h>
#include <Framework/Foundation/Types/TypeTraits.h>
#include "CTimeout.h"
#include "CTimePoint.h"
#include "EDayOfWeek.h"
#include "EDateTimeFragmentFormat.h"
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	class CDateTime final : public CObject
	{
//----------------------------------------------------------------------------------------------------------------------
		public:
			using												DateTimeTicks=int64;

		private:
			static const DateTimeTicks							MIN_TIME;
			static const DateTimeTicks							MAX_TIME;
			static const int32									MIN_YEAR;
			static const int32									MAX_YEAR;
			static const int32									MIN_MONTH;
			static const int32									MAX_MONTH;
			static const int32									MIN_DAY;
			static const int32									MAX_DAY;
			static const int32									MIN_HOUR;
			static const int32									MAX_HOUR;
			static const int32									MIN_MINUTE;
			static const int32									MAX_MINUTE;
			static const int32									MIN_SECOND;
			static const int32									MAX_SECOND;
			static const int32									MIN_MILLISECOND;
			static const int32									MAX_MILLISECOND;
			static const int64									FOUR_HUNDRED_YEARS;
			static const int64									ONE_HUNDRED_YEARS;
			static const int64									FOUR_YEARS;
			static const int64									NUMBER_OF_MONTHS_PER_YEAR;
			static const int64									NUMBER_OF_DAYS_PER_YEAR;
			static const int64									NUMBER_OF_DAYS_PER_LEAP_YEAR;
			static const int64									NUMBER_OF_DAYS_PER_WEEK;
			static const int64									NUMBER_OF_MILLISECONDS_PER_SECOND;
			static const int64									NUMBER_OF_SECONDS_PER_MINUTE;
			static const int64									NUMBER_OF_SECONDS_PER_HOUR;
			static const int64									NUMBER_OF_SECONDS_PER_DAY;
			static const int64									NUMBER_OF_SECONDS_PER_NON_LEAP_YEAR;

		private:
			static const CDateTime								MIN_DATE_TIME;
			static const CDateTime								MAX_DATE_TIME;

		private:
			// TICK is a MILLISECOND.
			DateTimeTicks										MTicks;

		public:
			CDateTime& operator=(const CDateTime& Other) noexcept;
			CDateTime& operator=(CDateTime&& Other) noexcept;

		private:
			static int32 GetNumberOfLeapYears(int32 Year);
			static DateTimeTicks InternalConvertTimeToTicks(const CTimePoint& TimePoint);
			static void InternalConvertTicksToTime(DateTimeTicks Ticks, CTimePoint& TimePoint);

		public:
			static bool IsValidTicks(DateTimeTicks Time);
			static bool IsValidYear(int32 Year);
			static bool IsValidMonth(int32 Month);
			static bool IsValidDayOfWeek(EDayOfWeek DayOfWeek);
			static bool IsValidDay(int32 Day);
			static bool IsValidDay(int32 Day, int32 Month, int32 Year);
			static bool IsValidHour(int32 Hour);
			static bool IsValidMinute(int32 Minute);
			static bool IsValidSecond(int32 Second);
			static bool IsValidMillisecond(int32 Millisecond);
			static void CheckTicks(DateTimeTicks Time);
			static void CheckYear(int32 Year);
			static void CheckMonth(int32 Month);
			static void CheckDayOfWeek(EDayOfWeek DayOfWeek);
			static void CheckDay(int32 Day);
			static void CheckDay(int32 Day, int32 Month, int32 Year);
			static void CheckHour(int32 Hour);
			static void CheckMinute(int32 Minute);
			static void CheckSecond(int32 Second);
			static void CheckMillisecond(int32 Millisecond);

		public:
			static const CDateTime& GetMin(void);
			static const CDateTime& GetMax(void);
			static CDateTime GetCurrentLocalTime(void);
			static CDateTime GetCurrentUTCTime(void);
			static bool IsLeapYear(int32 Year);
			static bool IsDaylightSavingTime(void);
			static int32 GetLocalTimeOffsetInSeconds(void);
			static int32 GetDaysInMonth(int32 Month, int32 Year);
			static int32 GetDaysInYear(int32 Year);

		public:
			static int64 GetNumberOfDaysPerWeek(void);
			static int64 GetNumberOfSecondsPerDay(void);
			static int64 GetNumberOfSecondsPerHour(void);
			static int64 GetNumberOfSecondsPerMinute(void);
			static int64 GetNumberOfMillisecondsPerSecond(void);
			
		public:
			static DateTimeTicks ConvertTimeToTicks(const CTimePoint& TimePoint);
			static void ConvertTicksToTime(DateTimeTicks Ticks, CTimePoint& TimePoint);
			static CTimeout ConvertTicksToTimeout(DateTimeTicks Ticks);
			static int64 ConvertTicksToMilliseconds(DateTimeTicks Ticks);
			static int64 ConvertTicksToSeconds(DateTimeTicks Ticks);

		private:
			void FormatDateTimeFragment(CString& FormattedString, const CString& Parameter) const;
			void FormatDateTimeFragment(CString& FormattedString, const std::string& Parameter) const;
			void FormatDateTimeFragment(CString& FormattedString, const Char* Parameter) const;
			void FormatDateTimeFragment(CString& FormattedString, const CObject& Parameter) const;
			void FormatDateTimeFragment(CString& FormattedString, CObject& Parameter) const;
			void FormatDateTimeFragment(CString& FormattedString, EDateTimeFragmentFormat Parameter) const;
			void InternalFormatDateTime(CString&) const;

		private:
			template<typename TParameter>
			typename std::enable_if<STypeTraitIsEnum<TParameter>::RawValue==true && CBinaryOperators<std::ostream&,TParameter&>::HasOperatorBitwiseLeftShift==true,void>::type FormatDateTimeFragment(CString& FormattedString, TParameter Parameter) const
			{
				std::stringstream								Stream;

				Stream << Parameter;

				FormattedString+=Stream.str();
			}

			template<typename TParameter>
			typename std::enable_if<STypeTraitIsEnum<TParameter>::RawValue==true && CBinaryOperators<std::ostream&,TParameter&>::HasOperatorBitwiseLeftShift==false,void>::type FormatDateTimeFragment(CString& FormattedString, TParameter Parameter) const
			{
				using											TUnderlyingType=typename std::underlying_type<TParameter>::type;

				TUnderlyingType									TypedParameter=static_cast<TUnderlyingType>(Parameter);

				std::stringstream								Stream;

				Stream << CString(TypedParameter);

				FormattedString+=Stream.str();
			}

			template<typename TParameter>
			typename std::enable_if<STypeTraitIsEnum<TParameter>::RawValue==false && std::is_same<TParameter,int8>::value==true,void>::type FormatDateTimeFragment(CString& FormattedString, TParameter Parameter) const
			{
				int16											IntegerParameter=static_cast<int16>(Parameter);
				std::stringstream								Stream;

				Stream << IntegerParameter;

				FormattedString+=Stream.str();
			}

			template<typename TParameter>
			typename std::enable_if<STypeTraitIsEnum<TParameter>::RawValue==false && std::is_same<TParameter,uint8>::value==true,void>::type FormatDateTimeFragment(CString& FormattedString, TParameter Parameter) const
			{
				uint16											IntegerParameter=static_cast<uint16>(Parameter);
				std::stringstream								Stream;

				Stream << IntegerParameter;

				FormattedString+=Stream.str();
			}

			template<typename TParameter>
			typename std::enable_if<STypeTraitIsEnum<TParameter>::RawValue==false && std::is_same<TParameter,int8>::value==false && std::is_same<TParameter,uint8>::value==false && CBinaryOperators<std::ostream&,TParameter&>::HasOperatorBitwiseLeftShift==true,void>::type FormatDateTimeFragment(CString& FormattedString, TParameter Parameter) const
			{
				std::stringstream								Stream;

				Stream << Parameter;

				FormattedString+=Stream.str();
			}

			template<typename TParameter>
			typename std::enable_if<STypeTraitIsEnum<TParameter>::RawValue==false && std::is_same<TParameter,int8>::value==false && std::is_same<TParameter,uint8>::value==false && CBinaryOperators<std::ostream&,TParameter&>::HasOperatorBitwiseLeftShift==false,void>::type FormatDateTimeFragment(CString& FormattedString, TParameter) const
			{
				std::stringstream								Stream;

				Stream << CString(typeid(TParameter).name());

				FormattedString+=Stream.str();
			}

			template<typename TFirstParameter, typename... TOtherParameters>
			void InternalFormatDateTime(CString& FormattedString, TFirstParameter&& FirstParameter, TOtherParameters&&... OtherParameters) const
			{
				FormatDateTimeFragment(FormattedString,FUNCTION_FORWARD<TFirstParameter>(FirstParameter));

				InternalFormatDateTime(FormattedString,FUNCTION_FORWARD<TOtherParameters>(OtherParameters)...);
			}

		public:
			virtual CString ToString(void) const override;
			DateTimeTicks GetTicks(void) const noexcept;
			int32 GetYear(void) const noexcept;
			int32 GetMonth(void) const noexcept;
			EDayOfWeek GetDayOfWeek(void) const noexcept;
			int32 GetDay(void) const noexcept;
			int32 GetHour(void) const noexcept;
			int32 GetMinute(void) const noexcept;
			int32 GetSecond(void) const noexcept;
			int32 GetMillisecond(void) const noexcept;
			CTimePoint GetTimePoint(void) const noexcept;
			int32 GetDayOfYear(void) const noexcept;

		public:
			CString FormatDateTime(void) const;

		public:
			template<typename... TParameters>
			CString FormatDateTime(TParameters&&... Parameters) const
			{
				CString											String;
					
				InternalFormatDateTime(String,FUNCTION_FORWARD<TParameters>(Parameters)...);

				return(String);
			}

		public:
			CDateTime& AddYears(int32 Years);
			CDateTime& AddMonths(int32 Months);
			CDateTime& AddDays(int32 Days);
			CDateTime& AddHours(int64 Hours);
			CDateTime& AddMinutes(int64 Minutes);
			CDateTime& AddSeconds(int64 Seconds);
			CDateTime& AddMilliseconds(int64 Milliseconds);

		public:
			CDateTime(DateTimeTicks Ticks=MIN_TIME);
			CDateTime(const CTimePoint& TimePoint);
			CDateTime(int32 Year, int32 Month, int32 Day, int32 Hour, int32 Minute, int32 Second, int32 Millisecond);
			CDateTime(const CDateTime& Other);
			CDateTime(CDateTime&& Other) noexcept;
//----------------------------------------------------------------------------------------------------------------------
	};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	using														CNullableDateTime=CNullable<CDateTime>;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool operator==(const CDateTime& Left, const CDateTime& Right);
	bool operator!=(const CDateTime& Left, const CDateTime& Right);
	bool operator<(const CDateTime& Left, const CDateTime& Right);
	bool operator<=(const CDateTime& Left, const CDateTime& Right);
	bool operator>(const CDateTime& Left, const CDateTime& Right);
	bool operator>=(const CDateTime& Left, const CDateTime& Right);
	// RETURNS DIFFERENCE in TICKS.
	CDateTime::DateTimeTicks operator-(const CDateTime& Left, const CDateTime& Right);
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------