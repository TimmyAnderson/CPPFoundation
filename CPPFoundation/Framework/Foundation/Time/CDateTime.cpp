//----------------------------------------------------------------------------------------------------------------------
#include "CDateTime.h"
#include <chrono>
#include <Framework/Platform/Global/CFunctions.h>
#include <Framework/Platform/Global/Macros.h>
#include <Framework/Foundation/Exceptions/CValueOutOfRangeException.h>
#include <Framework/Foundation/Exceptions/CInvalidValueException.h>
//----------------------------------------------------------------------------------------------------------------------
namespace CPPFoundation
{
//----------------------------------------------------------------------------------------------------------------------
namespace Foundation
{
//----------------------------------------------------------------------------------------------------------------------
	using namespace std;
	using namespace std::chrono;
	using namespace CPPFoundation::Platform;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CDateTime::DateTimeTicks								CDateTime::MIN_TIME=0;
	const CDateTime::DateTimeTicks								CDateTime::MAX_TIME=315537897599999;
	const int32													CDateTime::MIN_YEAR=1;
	const int32													CDateTime::MAX_YEAR=9999;
	const int32													CDateTime::MIN_MONTH=1;
	const int32													CDateTime::MAX_MONTH=12;
	const int32													CDateTime::MIN_DAY=1;
	const int32													CDateTime::MAX_DAY=31;
	const int32													CDateTime::MIN_HOUR=0;
	const int32													CDateTime::MAX_HOUR=23;
	const int32													CDateTime::MIN_MINUTE=0;
	const int32													CDateTime::MAX_MINUTE=59;
	const int32													CDateTime::MIN_SECOND=0;
	const int32													CDateTime::MAX_SECOND=59;
	const int32													CDateTime::MIN_MILLISECOND=0;
	const int32													CDateTime::MAX_MILLISECOND=999;
	const int64													CDateTime::FOUR_HUNDRED_YEARS=400;
	const int64													CDateTime::ONE_HUNDRED_YEARS=100;
	const int64													CDateTime::FOUR_YEARS=4;
	const int64													CDateTime::NUMBER_OF_MONTHS_PER_YEAR=12;
	const int64													CDateTime::NUMBER_OF_DAYS_PER_YEAR=365;
	const int64													CDateTime::NUMBER_OF_DAYS_PER_LEAP_YEAR=366;
	const int64													CDateTime::NUMBER_OF_DAYS_PER_WEEK=7;
	const int64													CDateTime::NUMBER_OF_MILLISECONDS_PER_SECOND=1000;
	const int64													CDateTime::NUMBER_OF_SECONDS_PER_MINUTE=60;
	const int64													CDateTime::NUMBER_OF_SECONDS_PER_HOUR=60*NUMBER_OF_SECONDS_PER_MINUTE;
	const int64													CDateTime::NUMBER_OF_SECONDS_PER_DAY=24*NUMBER_OF_SECONDS_PER_HOUR;
	const int64													CDateTime::NUMBER_OF_SECONDS_PER_NON_LEAP_YEAR=NUMBER_OF_DAYS_PER_YEAR*NUMBER_OF_SECONDS_PER_DAY;
//----------------------------------------------------------------------------------------------------------------------
	const CDateTime												CDateTime::MIN_DATE_TIME=CDateTime(MIN_TIME);
	const CDateTime												CDateTime::MAX_DATE_TIME=CDateTime(MAX_TIME);
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CDateTime::CDateTime(DateTimeTicks Ticks)
		: MTicks(0)
	{
		CheckTicks(Ticks);

		MTicks=Ticks;
	}
//----------------------------------------------------------------------------------------------------------------------
	CDateTime::CDateTime(const CTimePoint& TimePoint)
		: MTicks(0)
	{
		CheckYear(TimePoint.MYear);
		CheckMonth(TimePoint.MMonth);
		CheckDay(TimePoint.MDay,TimePoint.MMonth,TimePoint.MYear);
		CheckHour(TimePoint.MHour);
		CheckMinute(TimePoint.MMinute);
		CheckSecond(TimePoint.MSecond);
		CheckMillisecond(TimePoint.MMillisecond);

		MTicks=InternalConvertTimeToTicks(TimePoint);
	}
//----------------------------------------------------------------------------------------------------------------------
	CDateTime::CDateTime(int32 Year, int32 Month, int32 Day, int32 Hour, int32 Minute, int32 Second, int32 Millisecond)
		: MTicks(0)
	{
		CheckYear(Year);
		CheckMonth(Month);
		CheckDay(Day,Month,Year);
		CheckHour(Hour);
		CheckMinute(Minute);
		CheckSecond(Second);
		CheckMillisecond(Millisecond);

		CTimePoint												TimePoint(Year,Month,Day,Hour,Minute,Second,Millisecond);

		MTicks=InternalConvertTimeToTicks(TimePoint);
	}
//----------------------------------------------------------------------------------------------------------------------
	CDateTime::CDateTime(const CDateTime& Other)
		: MTicks(Other.MTicks)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
	CDateTime::CDateTime(CDateTime&& Other) noexcept
		: MTicks(Other.MTicks)
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CDateTime& CDateTime::operator=(const CDateTime& Other) noexcept
	{
		MTicks=Other.MTicks;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CDateTime& CDateTime::operator=(CDateTime&& Other) noexcept
	{
		MTicks=Other.MTicks;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool operator==(const CDateTime& Left, const CDateTime& Right)
	{
		if (Left.GetTicks()==Right.GetTicks())
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool operator!=(const CDateTime& Left, const CDateTime& Right)
	{
		if (Left.GetTicks()!=Right.GetTicks())
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool operator<(const CDateTime& Left, const CDateTime& Right)
	{
		if (Left.GetTicks()<Right.GetTicks())
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool operator<=(const CDateTime& Left, const CDateTime& Right)
	{
		if (Left.GetTicks()<=Right.GetTicks())
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool operator>(const CDateTime& Left, const CDateTime& Right)
	{
		if (Left.GetTicks()>Right.GetTicks())
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool operator>=(const CDateTime& Left, const CDateTime& Right)
	{
		if (Left.GetTicks()>=Right.GetTicks())
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	CDateTime::DateTimeTicks operator-(const CDateTime& Left, const CDateTime& Right)
	{
		CDateTime::DateTimeTicks								DifferenceInMS=Left.GetTicks()-Right.GetTicks();

		return(DifferenceInMS);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	bool CDateTime::IsValidTicks(DateTimeTicks Time)
	{
		if (Time<MIN_TIME || Time>MAX_TIME)
		{
			return(false);
		}
		else
		{
			return(true);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CDateTime::IsValidYear(int32 Year)
	{
		if (Year<MIN_YEAR || Year>MAX_YEAR)
		{
			return(false);
		}
		else
		{
			return(true);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CDateTime::IsValidMonth(int32 Month)
	{
		if (Month<MIN_MONTH || Month>MAX_MONTH)
		{
			return(false);
		}
		else
		{
			return(true);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CDateTime::IsValidDayOfWeek(EDayOfWeek DayOfWeek)
	{
		return(IsValidValue(DayOfWeek));
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CDateTime::IsValidDay(int32 Day)
	{
		if (Day<MIN_DAY || Day>MAX_DAY)
		{
			return(false);
		}
		else
		{
			return(true);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CDateTime::IsValidDay(int32 Day, int32 Month, int32 Year)
	{
		if (IsValidMonth(Month)==false)
		{
			return(false);
		}

		if (IsValidYear(Year)==false)
		{
			return(false);
		}

		int32													DaysInMonth=GetDaysInMonth(Month,Year);

		if (Day<MIN_DAY || Day>DaysInMonth)
		{
			return(false);
		}
		else
		{
			return(true);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CDateTime::IsValidHour(int32 Hour)
	{
		if (Hour<MIN_HOUR || Hour>MAX_HOUR)
		{
			return(false);
		}
		else
		{
			return(true);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CDateTime::IsValidMinute(int32 Minute)
	{
		if (Minute<MIN_MINUTE || Minute>MAX_MINUTE)
		{
			return(false);
		}
		else
		{
			return(true);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CDateTime::IsValidSecond(int32 Second)
	{
		if (Second<MIN_SECOND || Second>MAX_SECOND)
		{
			return(false);
		}
		else
		{
			return(true);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CDateTime::IsValidMillisecond(int32 Millisecond)
	{
		if (Millisecond<MIN_MILLISECOND || Millisecond>MAX_MILLISECOND)
		{
			return(false);
		}
		else
		{
			return(true);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CDateTime::CheckTicks(DateTimeTicks Time)
	{
		if (IsValidTicks(Time)==false)
		{
			throw(CValueOutOfRangeException(CString::Format("TIME [",Time,"] is OUT ot RANGE <",MIN_TIME,",",MAX_TIME,"> !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CDateTime::CheckYear(int32 Year)
	{
		if (IsValidYear(Year)==false)
		{
			throw(CValueOutOfRangeException(CString::Format("YEAR [",Year,"] is OUT ot RANGE <",MIN_YEAR,",",MAX_YEAR,"> !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CDateTime::CheckMonth(int32 Month)
	{
		if (IsValidMonth(Month)==false)
		{
			throw(CValueOutOfRangeException(CString::Format("MONTH [",Month,"] is OUT ot RANGE <",MIN_MONTH,",",MAX_MONTH,"> !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CDateTime::CheckDayOfWeek(EDayOfWeek DayOfWeek)
	{
		if (IsValidDayOfWeek(DayOfWeek)==false)
		{
			throw(CValueOutOfRangeException(CString::Format("DAY of WEEK [",DayOfWeek,"] is OUT ot RANGE <",EDayOfWeek::E_MONDAY,",",EDayOfWeek::E_SUNDAY,"> !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CDateTime::CheckDay(int32 Day)
	{
		if (IsValidDay(Day)==false)
		{
			throw(CValueOutOfRangeException(CString::Format("DAY [",Day,"] is OUT ot RANGE <",MIN_DAY,",",MAX_DAY,"> !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CDateTime::CheckDay(int32 Day, int32 Month, int32 Year)
	{
		if (IsValidDay(Day,Month,Year)==false)
		{
			int32												DaysInMonth=GetDaysInMonth(Month,Year);

			throw(CValueOutOfRangeException(CString::Format("DAY [",Day,"] is OUT ot RANGE <",MIN_DAY,",",DaysInMonth,"> !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CDateTime::CheckHour(int32 Hour)
	{
		if (IsValidHour(Hour)==false)
		{
			throw(CValueOutOfRangeException(CString::Format("HOUR [",Hour,"] is OUT ot RANGE <",MIN_HOUR,",",MAX_HOUR,"> !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CDateTime::CheckMinute(int32 Minute)
	{
		if (IsValidMinute(Minute)==false)
		{
			throw(CValueOutOfRangeException(CString::Format("MINUTE [",Minute,"] is OUT ot RANGE <",MIN_MINUTE,",",MAX_MINUTE,"> !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CDateTime::CheckSecond(int32 Second)
	{
		if (IsValidSecond(Second)==false)
		{
			throw(CValueOutOfRangeException(CString::Format("SECOND [",Second,"] is OUT ot RANGE <",MIN_SECOND,",",MAX_SECOND,"> !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CDateTime::CheckMillisecond(int32 Millisecond)
	{
		if (IsValidMillisecond(Millisecond)==false)
		{
			throw(CValueOutOfRangeException(CString::Format("MILLISECOND [",Millisecond,"] is OUT ot RANGE <",MIN_MILLISECOND,",",MAX_MILLISECOND,"> !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CDateTime::GetNumberOfLeapYears(int32 Year)
	{
		int32													NumberOfFourYears=Year/FOUR_YEARS;
		int32													NumberOfHundredYears=Year/ONE_HUNDRED_YEARS;
		int32													NumberOfFourHundredYears=Year/FOUR_HUNDRED_YEARS;
		int32													NumberOfLeapYears=NumberOfFourYears-(NumberOfHundredYears-NumberOfFourHundredYears);

		return(NumberOfLeapYears);
	}
//----------------------------------------------------------------------------------------------------------------------
	CDateTime::DateTimeTicks CDateTime::InternalConvertTimeToTicks(const CTimePoint& TimePoint)
	{
		int32													NumberOfFullYears=TimePoint.MYear-1;
		int32													NumberOfLeapYears=(NumberOfFullYears>0) ? GetNumberOfLeapYears(NumberOfFullYears) : 0;
		DateTimeTicks											Ticks=0;
		
		Ticks+=(NumberOfFullYears*NUMBER_OF_SECONDS_PER_NON_LEAP_YEAR);
		Ticks+=(NumberOfLeapYears*NUMBER_OF_SECONDS_PER_DAY);

		for(int32 CurrentMonth=1;CurrentMonth<TimePoint.MMonth;CurrentMonth++)
		{
			int32												DaysInMonth=GetDaysInMonth(CurrentMonth,TimePoint.MYear);
			
			Ticks+=DaysInMonth*NUMBER_OF_SECONDS_PER_DAY;
		}

		int32													NumberOfFullDays=TimePoint.MDay-1;

		Ticks+=NumberOfFullDays*NUMBER_OF_SECONDS_PER_DAY;

		Ticks+=TimePoint.MHour*NUMBER_OF_SECONDS_PER_HOUR;
		Ticks+=TimePoint.MMinute*NUMBER_OF_SECONDS_PER_MINUTE;
		Ticks+=TimePoint.MSecond;

		Ticks*=NUMBER_OF_MILLISECONDS_PER_SECOND;

		Ticks+=TimePoint.MMillisecond;

		return(Ticks);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CDateTime::InternalConvertTicksToTime(DateTimeTicks Ticks, CTimePoint& TimePoint)
	{
		static const int64										NUMBER_OF_DAYS_PER_FOUR_HUNDRED_YEARS=(NUMBER_OF_DAYS_PER_YEAR*FOUR_HUNDRED_YEARS)+GetNumberOfLeapYears(FOUR_HUNDRED_YEARS);
		static const int64										NUMBER_OF_DAYS_PER_ONE_HUNDRED_YEARS=(NUMBER_OF_DAYS_PER_YEAR*ONE_HUNDRED_YEARS)+GetNumberOfLeapYears(ONE_HUNDRED_YEARS);
		static const int64										NUMBER_OF_DAYS_PER_FOUR_YEARS=(NUMBER_OF_DAYS_PER_YEAR*FOUR_YEARS)+GetNumberOfLeapYears(FOUR_YEARS);

		int64													Year=0;
		int64													NumberOfDays=Ticks/NUMBER_OF_SECONDS_PER_DAY/NUMBER_OF_MILLISECONDS_PER_SECOND;
		int64													NumberOfFourHundredYears=NumberOfDays/NUMBER_OF_DAYS_PER_FOUR_HUNDRED_YEARS;

		NumberOfDays-=NumberOfFourHundredYears*NUMBER_OF_DAYS_PER_FOUR_HUNDRED_YEARS;
		Year+=(NumberOfFourHundredYears*FOUR_HUNDRED_YEARS);

		int64													NumberOfOneHundredYears=NumberOfDays/NUMBER_OF_DAYS_PER_ONE_HUNDRED_YEARS;

		NumberOfDays-=NumberOfOneHundredYears*NUMBER_OF_DAYS_PER_ONE_HUNDRED_YEARS;
		Year+=(NumberOfOneHundredYears*ONE_HUNDRED_YEARS);

		int64													NumberOfFourYears=NumberOfDays/NUMBER_OF_DAYS_PER_FOUR_YEARS;

		NumberOfDays-=NumberOfFourYears*NUMBER_OF_DAYS_PER_FOUR_YEARS;
		Year+=(NumberOfFourYears*FOUR_YEARS);

		Year++;

		while(NumberOfDays>0)
		{
			int64												NumberOfDaysInYear=GetDaysInYear(static_cast<int32>(Year));

			if (NumberOfDays>=NumberOfDaysInYear)
			{
				NumberOfDays-=NumberOfDaysInYear;
				Year++;
			}
			else
			{
				break;
			}
		}

		TimePoint.MYear=static_cast<int32>(Year);
		TimePoint.MMonth=1;

		for(int32 CurrentMonth=1;CurrentMonth<NUMBER_OF_MONTHS_PER_YEAR;CurrentMonth++)
		{
			int64												DaysInMonth=GetDaysInMonth(CurrentMonth,TimePoint.MYear);

			if (NumberOfDays>=DaysInMonth)
			{
				TimePoint.MMonth++;
				NumberOfDays-=DaysInMonth;
			}
			else
			{
				break;
			}
		}

		TimePoint.MDay=1+static_cast<int32>(NumberOfDays);

		int64													NumberOfMilliseconds=static_cast<int32>(Ticks%(NUMBER_OF_SECONDS_PER_DAY*NUMBER_OF_MILLISECONDS_PER_SECOND));

		TimePoint.MHour=static_cast<int32>(NumberOfMilliseconds/NUMBER_OF_SECONDS_PER_HOUR/NUMBER_OF_MILLISECONDS_PER_SECOND);
		NumberOfMilliseconds%=NUMBER_OF_SECONDS_PER_HOUR*NUMBER_OF_MILLISECONDS_PER_SECOND;

		TimePoint.MMinute=static_cast<int32>(NumberOfMilliseconds/NUMBER_OF_SECONDS_PER_MINUTE/NUMBER_OF_MILLISECONDS_PER_SECOND);
		NumberOfMilliseconds%=NUMBER_OF_SECONDS_PER_MINUTE*NUMBER_OF_MILLISECONDS_PER_SECOND;

		TimePoint.MSecond=static_cast<int32>(NumberOfMilliseconds/NUMBER_OF_MILLISECONDS_PER_SECOND);
		NumberOfMilliseconds%=NUMBER_OF_MILLISECONDS_PER_SECOND;

		TimePoint.MMillisecond=static_cast<int32>(NumberOfMilliseconds);
	}
//----------------------------------------------------------------------------------------------------------------------
	CTimeout CDateTime::ConvertTicksToTimeout(DateTimeTicks Ticks)
	{
		return(CTimeout(Ticks));
	}
//----------------------------------------------------------------------------------------------------------------------
	int64 CDateTime::ConvertTicksToMilliseconds(DateTimeTicks Ticks)
	{
		return(Ticks);
	}
//----------------------------------------------------------------------------------------------------------------------
	int64 CDateTime::ConvertTicksToSeconds(DateTimeTicks Ticks)
	{
		return(Ticks/NUMBER_OF_MILLISECONDS_PER_SECOND);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	void CDateTime::FormatDateTimeFragment(CString& FormattedString, const CString& Parameter) const
	{
		FormattedString+=Parameter;
	}
//----------------------------------------------------------------------------------------------------------------------
	void CDateTime::FormatDateTimeFragment(CString& FormattedString, const std::string& Parameter) const
	{
		FormattedString+=Parameter;
	}
//----------------------------------------------------------------------------------------------------------------------
	void CDateTime::FormatDateTimeFragment(CString& FormattedString, const Char* Parameter) const
	{
		FormattedString+=Parameter;
	}
//----------------------------------------------------------------------------------------------------------------------
	void CDateTime::FormatDateTimeFragment(CString& FormattedString, const CObject& Parameter) const
	{
		FormattedString+=Parameter.ToString();
	}
//----------------------------------------------------------------------------------------------------------------------
	void CDateTime::FormatDateTimeFragment(CString& FormattedString, CObject& Parameter) const
	{
		FormattedString+=Parameter.ToString();
	}
//----------------------------------------------------------------------------------------------------------------------
	void CDateTime::FormatDateTimeFragment(CString& FormattedString, EDateTimeFragmentFormat Parameter) const
	{
		if (Parameter==EDateTimeFragmentFormat::E_FORMAT_YEAR)
		{
			FormattedString+=CString(GetYear(),EIntegerFormat::E_NONE,4,true);
		}
		else if (Parameter==EDateTimeFragmentFormat::E_FORMAT_MONTH)
		{
			FormattedString+=CString(GetMonth(),EIntegerFormat::E_NONE,2,true);
		}
		else if (Parameter==EDateTimeFragmentFormat::E_FORMAT_DAY)
		{
			FormattedString+=CString(GetDay(),EIntegerFormat::E_NONE,2,true);
		}
		else if (Parameter==EDateTimeFragmentFormat::E_FORMAT_HOUR)
		{
			FormattedString+=CString(GetHour(),EIntegerFormat::E_NONE,2,true);
		}
		else if (Parameter==EDateTimeFragmentFormat::E_FORMAT_MINUTE)
		{
			FormattedString+=CString(GetMinute(),EIntegerFormat::E_NONE,2,true);
		}
		else if (Parameter==EDateTimeFragmentFormat::E_FORMAT_SECOND)
		{
			FormattedString+=CString(GetSecond(),EIntegerFormat::E_NONE,2,true);
		}
		else if (Parameter==EDateTimeFragmentFormat::E_FORMAT_MILLISECOND)
		{
			FormattedString+=CString(GetMillisecond(),EIntegerFormat::E_NONE,3,true);
		}
		else if (Parameter==EDateTimeFragmentFormat::E_FORMAT_UNPADDED_YEAR)
		{
			FormattedString+=CString(GetYear());
		}
		else if (Parameter==EDateTimeFragmentFormat::E_FORMAT_UNPADDED_MONTH)
		{
			FormattedString+=CString(GetMonth());
		}
		else if (Parameter==EDateTimeFragmentFormat::E_FORMAT_UNPADDED_DAY)
		{
			FormattedString+=CString(GetDay());
		}
		else if (Parameter==EDateTimeFragmentFormat::E_FORMAT_UNPADDED_HOUR)
		{
			FormattedString+=CString(GetHour());
		}
		else if (Parameter==EDateTimeFragmentFormat::E_FORMAT_UNPADDED_MINUTE)
		{
			FormattedString+=CString(GetMinute());
		}
		else if (Parameter==EDateTimeFragmentFormat::E_FORMAT_UNPADDED_SECOND)
		{
			FormattedString+=CString(GetSecond());
		}
		else if (Parameter==EDateTimeFragmentFormat::E_FORMAT_UNPADDED_MILLISECOND)
		{
			FormattedString+=CString(GetMillisecond());
		}
		else
		{
			throw(CInvalidOperationException(CString::Format("UNSUPPORTED VALUE [",Parameter,"] !")));
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	void CDateTime::InternalFormatDateTime(CString&) const
	{
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	const CDateTime& CDateTime::GetMin(void)
	{
		return(MIN_DATE_TIME);
	}
//----------------------------------------------------------------------------------------------------------------------
	const CDateTime& CDateTime::GetMax(void)
	{
		return(MAX_DATE_TIME);
	}
//----------------------------------------------------------------------------------------------------------------------
	CDateTime CDateTime::GetCurrentLocalTime(void)
	{
		// EPOCH TIME is NOT DEFINED by the C++ STANDARD but ALL IMPLEMENTATIONS use LINUX TIME.
		CDateTime												Time(1970,1,1,0,0,0,0);
		system_clock::time_point								TimePoint=system_clock::now();
		system_clock::time_point::duration						TimeSinceEpoch=TimePoint.time_since_epoch();
		milliseconds											MillisecondsSinceEpoch=duration_cast<milliseconds>(TimeSinceEpoch);
		
		Time.AddMilliseconds(static_cast<int64>(MillisecondsSinceEpoch.count()));

		time_t													CTime=system_clock::to_time_t(TimePoint);
		int32													LocalTimeOffsetInSeconds=CFunctions::GetLocalTimeOffsetInSeconds(CTime);

		Time.AddSeconds(LocalTimeOffsetInSeconds);

		return(Time);
	}
//----------------------------------------------------------------------------------------------------------------------
	CDateTime CDateTime::GetCurrentUTCTime(void)
	{
		// EPOCH TIME is NOT DEFINED by the C++ STANDARD but ALL IMPLEMENTATIONS use LINUX TIME.
		CDateTime												Time(1970,1,1,0,0,0,0);
		system_clock::time_point								TimePoint=system_clock::now();
		system_clock::time_point::duration						TimeSinceEpoch=TimePoint.time_since_epoch();
		milliseconds											MillisecondsSinceEpoch=duration_cast<milliseconds>(TimeSinceEpoch);

		Time.AddMilliseconds(static_cast<int64>(MillisecondsSinceEpoch.count()));

		return(Time);
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CDateTime::IsLeapYear(int32 Year)
	{
		CheckYear(Year);

		if ((Year%FOUR_YEARS)==0 && ((Year%ONE_HUNDRED_YEARS)!=0 || (Year%FOUR_HUNDRED_YEARS)==0))
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
	bool CDateTime::IsDaylightSavingTime(void)
	{
		bool													DaylightSavingTime=CFunctions::IsDaylightSavingTime(system_clock::to_time_t(system_clock::now()));

		return(DaylightSavingTime);
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CDateTime::GetLocalTimeOffsetInSeconds(void)
	{
		int32													LocalTimeOffsetInSeconds=CFunctions::GetLocalTimeOffsetInSeconds(system_clock::to_time_t(system_clock::now()));

		return(LocalTimeOffsetInSeconds);
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CDateTime::GetDaysInMonth(int32 Month, int32 Year)
	{
		static const int32										MONTH_ARRAY[2][NUMBER_OF_MONTHS_PER_YEAR]={{31,28,31,30,31,30,31,31,30,31,30,31},{31,29,31,30,31,30,31,31,30,31,30,31}};

		CheckMonth(Month);
		CheckYear(Year);

		int32													LeapYearIndex;

		if (IsLeapYear(Year)==false)
		{
			LeapYearIndex=0;
		}
		else
		{
			LeapYearIndex=1;
		}

		int32													DaysInMonth=MONTH_ARRAY[LeapYearIndex][Month-1];

		return(DaysInMonth);
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CDateTime::GetDaysInYear(int32 Year)
	{
		if (IsLeapYear(Year)==false)
		{
			return(NUMBER_OF_DAYS_PER_YEAR);
		}
		else
		{
			return(NUMBER_OF_DAYS_PER_LEAP_YEAR);
		}
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	int64 CDateTime::GetNumberOfDaysPerWeek(void)
	{
		return(NUMBER_OF_DAYS_PER_WEEK);
	}
//----------------------------------------------------------------------------------------------------------------------
	int64 CDateTime::GetNumberOfSecondsPerDay(void)
	{
		return(NUMBER_OF_SECONDS_PER_DAY);
	}
//----------------------------------------------------------------------------------------------------------------------
	int64 CDateTime::GetNumberOfSecondsPerHour(void)
	{
		return(NUMBER_OF_SECONDS_PER_HOUR);
	}
//----------------------------------------------------------------------------------------------------------------------
	int64 CDateTime::GetNumberOfSecondsPerMinute(void)
	{
		return(NUMBER_OF_SECONDS_PER_MINUTE);
	}
//----------------------------------------------------------------------------------------------------------------------
	int64 CDateTime::GetNumberOfMillisecondsPerSecond(void)
	{
		return(NUMBER_OF_MILLISECONDS_PER_SECOND);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CDateTime::DateTimeTicks CDateTime::ConvertTimeToTicks(const CTimePoint& TimePoint)
	{
		CheckYear(TimePoint.MYear);
		CheckMonth(TimePoint.MMonth);
		CheckDay(TimePoint.MDay,TimePoint.MMonth,TimePoint.MYear);
		CheckHour(TimePoint.MHour);
		CheckMinute(TimePoint.MMinute);
		CheckSecond(TimePoint.MSecond);
		CheckMillisecond(TimePoint.MMillisecond);

		DateTimeTicks											Ticks=InternalConvertTimeToTicks(TimePoint);

		return(Ticks);
	}
//----------------------------------------------------------------------------------------------------------------------
	void CDateTime::ConvertTicksToTime(DateTimeTicks Ticks, CTimePoint& TimePoint)
	{
		CheckTicks(Ticks);

		InternalConvertTicksToTime(Ticks,TimePoint);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CDateTime::ToString(void) const
	{
		return(CString(FormatDateTime(EDateTimeFragmentFormat::E_FORMAT_DAY,"-",EDateTimeFragmentFormat::E_FORMAT_MONTH,"-",EDateTimeFragmentFormat::E_FORMAT_YEAR," ",EDateTimeFragmentFormat::E_FORMAT_HOUR,":",EDateTimeFragmentFormat::E_FORMAT_MINUTE,":",EDateTimeFragmentFormat::E_FORMAT_SECOND,".",EDateTimeFragmentFormat::E_FORMAT_MILLISECOND)));
	}
//----------------------------------------------------------------------------------------------------------------------
	CDateTime::DateTimeTicks CDateTime::GetTicks(void) const noexcept
	{
		return(MTicks);
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CDateTime::GetYear(void) const noexcept
	{
		CTimePoint												TimePoint;

		InternalConvertTicksToTime(MTicks,TimePoint);

		return(TimePoint.MYear);
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CDateTime::GetMonth(void) const noexcept
	{
		CTimePoint												TimePoint;

		InternalConvertTicksToTime(MTicks,TimePoint);

		return(TimePoint.MMonth);
	}
//----------------------------------------------------------------------------------------------------------------------
	EDayOfWeek CDateTime::GetDayOfWeek(void) const noexcept
	{
		CTimePoint												TimePoint;

		InternalConvertTicksToTime(MTicks,TimePoint);

		int32													NumberOfLeapYears=GetNumberOfLeapYears(TimePoint.MYear-1);
		int64													NumberOfDays=((static_cast<int64>(TimePoint.MYear)-1)*NUMBER_OF_DAYS_PER_YEAR+NumberOfLeapYears+GetDayOfYear()+1);

		// 01.01.0001 is SATURDAY.
		NumberOfDays+=5;

		int32													RawDayOfWeek=static_cast<int32>(NumberOfDays % NUMBER_OF_DAYS_PER_WEEK);
		EDayOfWeek												DayOfWeek=static_cast<EDayOfWeek>(RawDayOfWeek+1);

		return(DayOfWeek);
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CDateTime::GetDay(void) const noexcept
	{
		CTimePoint												TimePoint;

		InternalConvertTicksToTime(MTicks,TimePoint);

		return(TimePoint.MDay);
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CDateTime::GetHour(void) const noexcept
	{
		int32													NumberOfMillisecondsPerDay=static_cast<int32>(MTicks%(NUMBER_OF_SECONDS_PER_DAY*NUMBER_OF_MILLISECONDS_PER_SECOND));
		int32													Hour=NumberOfMillisecondsPerDay/NUMBER_OF_SECONDS_PER_HOUR/NUMBER_OF_MILLISECONDS_PER_SECOND;

		return(Hour);
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CDateTime::GetMinute(void) const noexcept
	{
		int32													NumberOfMillisecondsPerHour=static_cast<int32>(MTicks%(NUMBER_OF_SECONDS_PER_HOUR*NUMBER_OF_MILLISECONDS_PER_SECOND));
		int32													Minute=NumberOfMillisecondsPerHour/NUMBER_OF_SECONDS_PER_MINUTE/NUMBER_OF_MILLISECONDS_PER_SECOND;

		return(Minute);
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CDateTime::GetSecond(void) const noexcept
	{
		int32													NumberOfMillisecondsPerMinute=static_cast<int32>(MTicks%(NUMBER_OF_SECONDS_PER_MINUTE*NUMBER_OF_MILLISECONDS_PER_SECOND));
		int32													Second=NumberOfMillisecondsPerMinute/NUMBER_OF_MILLISECONDS_PER_SECOND;

		return(Second);
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CDateTime::GetMillisecond(void) const noexcept
	{
		int32													Millisecond=static_cast<int32>(MTicks%NUMBER_OF_MILLISECONDS_PER_SECOND);

		return(Millisecond);
	}
//----------------------------------------------------------------------------------------------------------------------
	CTimePoint CDateTime::GetTimePoint(void) const noexcept
	{
		CTimePoint												TimePoint;
		
		ConvertTicksToTime(MTicks,TimePoint);

		return(TimePoint);
	}
//----------------------------------------------------------------------------------------------------------------------
	int32 CDateTime::GetDayOfYear(void) const noexcept
	{
		int32													DayOfYear=0;

		for(int32 Month=1,MaxMonth=GetMonth(),Year=GetYear();Month<MaxMonth;Month++)
		{
			DayOfYear+=GetDaysInMonth(Month,Year);
		}

		DayOfYear+=GetDay();

		return(DayOfYear);
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CString CDateTime::FormatDateTime(void) const
	{
		return("");
	}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
	CDateTime& CDateTime::AddYears(int32 Years)
	{
		int32													NumberOfMonths=static_cast<int32>(Years*NUMBER_OF_MONTHS_PER_YEAR);

		AddMonths(NumberOfMonths);

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CDateTime& CDateTime::AddMonths(int32 Months)
	{
		CTimePoint												TimePoint;

		InternalConvertTicksToTime(MTicks,TimePoint);

		int32													AbsoluteMonths=(Months>=0) ? Months : -Months;
		int32													NumberOfYears=AbsoluteMonths/NUMBER_OF_MONTHS_PER_YEAR;
		int32													NumberOfMonths=AbsoluteMonths%NUMBER_OF_MONTHS_PER_YEAR;

		if (Months>=0)
		{
			TimePoint.MMonth+=NumberOfMonths;

			if (TimePoint.MMonth>NUMBER_OF_MONTHS_PER_YEAR)
			{
				TimePoint.MMonth-=static_cast<int32>(NUMBER_OF_MONTHS_PER_YEAR);
				NumberOfYears++;
			}

			TimePoint.MYear+=NumberOfYears;

			int32												DaysInMonth=GetDaysInMonth(TimePoint.MMonth,TimePoint.MYear);

			if (TimePoint.MDay>DaysInMonth)
			{
				TimePoint.MDay=DaysInMonth;
			}

			MTicks=ConvertTimeToTicks(TimePoint);
		}
		else
		{
			TimePoint.MMonth-=NumberOfMonths;

			if (TimePoint.MMonth<0)
			{
				TimePoint.MMonth+=static_cast<int32>(NUMBER_OF_MONTHS_PER_YEAR);
				NumberOfYears++;
			}

			TimePoint.MYear-=NumberOfYears;

			int32												DaysInMonth=GetDaysInMonth(TimePoint.MMonth,TimePoint.MYear);

			if (TimePoint.MDay>DaysInMonth)
			{
				TimePoint.MDay=DaysInMonth;
			}

			MTicks=ConvertTimeToTicks(TimePoint);
		}

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CDateTime& CDateTime::AddDays(int32 Days)
	{
		int64													NumberOfMilliseconds=Days*NUMBER_OF_SECONDS_PER_DAY*NUMBER_OF_MILLISECONDS_PER_SECOND;
		DateTimeTicks											Ticks=MTicks+NumberOfMilliseconds;

		CheckTicks(Ticks);

		MTicks=Ticks;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CDateTime& CDateTime::AddHours(int64 Hours)
	{
		int64													NumberOfMilliseconds=Hours*NUMBER_OF_SECONDS_PER_HOUR*NUMBER_OF_MILLISECONDS_PER_SECOND;
		DateTimeTicks											Ticks=MTicks+NumberOfMilliseconds;

		CheckTicks(Ticks);

		MTicks=Ticks;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CDateTime& CDateTime::AddMinutes(int64 Minutes)
	{
		int64													NumberOfMilliseconds=Minutes*NUMBER_OF_SECONDS_PER_MINUTE*NUMBER_OF_MILLISECONDS_PER_SECOND;
		DateTimeTicks											Ticks=MTicks+NumberOfMilliseconds;

		CheckTicks(Ticks);

		MTicks=Ticks;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CDateTime& CDateTime::AddSeconds(int64 Seconds)
	{
		int64													NumberOfMilliseconds=Seconds*NUMBER_OF_MILLISECONDS_PER_SECOND;
		DateTimeTicks											Ticks=MTicks+NumberOfMilliseconds;

		CheckTicks(Ticks);

		MTicks=Ticks;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
	CDateTime& CDateTime::AddMilliseconds(int64 Milliseconds)
	{
		DateTimeTicks											Ticks=MTicks+Milliseconds;

		CheckTicks(Ticks);

		MTicks=Ticks;

		return(*this);
	}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------