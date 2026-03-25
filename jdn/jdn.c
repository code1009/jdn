/////////////////////////////////////////////////////////////////////////////
//
// File: jdn.c
//
// Created by MOON, Eui-kwon.
// Created on Apr-20th, 2023.
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
//! @file   jdn.c
//! @brief  julian day number 소스 파일.





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
/*

//===========================================================================
# Julian Period
15 (indiction cycle) × 19 (Metonic cycle) × 28 (Solar cycle) = 7980 years
첫 주기 : 4713 BC ~ AD 3268

# Julian Day
Julian Period의 일 
천문학에서 사용
Julian Calendar 와는 다른 별도의 개념

# Julian Day Number(JDN)
정수 형태의 Julian 일
-4712/01/01 = 0(BC 4713년)
-4712/01/02 = 1
-4712/01/03 = 2
JDN은 날짜 의미로만 사용

# Julian Date(JD)
실수 형태의 Julian 일
-4712/01/01 12:00:00 = 0.0
-4712/01/02 00:00:00 = 0.5
-4712/01/02 12:00:00 = 1.0
-4712/01/03 00:00:00 = 1.5
-4712/01/03 12:00:00 = 2.0
JD는 날짜+시간 의미 사용

//===========================================================================
# Julian Calendar 
1582년 10월 04일 목요일 까지 사용
365.25 주기

# Gregorian Calendar 
1582년 10월 15일 금요일 부터 사용
365.2425 주기

# Calendar Date
1582년 10월 05일 ~ 1582년 10월 14일은 존재 안함

//===========================================================================
# 지구 태양공전 주기
항성년(恒星年/Siderial year   ) 365.2564일 = 365일  6시간  9분 : 별자리 기준
회귀년(回歸年/Tropical year   ) 365.2422일 = 365일  5시간 49분 : 태양년, 춘분점 기준
근점년(近點年/Anomalistic year) 365.2596일 = 365일  6시간 14분
교점년(交點年/Draconic year   ) 346.6201일 = 346일 14시간 53분

# 달의 지구공전 주기
항성월(恒星月/Sidereal month  )  27.3217일 = 27일  7시간 43분
삭망월(朔望月/Synodic month   )  29.5306일 = 29일 12시간 44분(평균값)
회귀월(回歸月/Tropical month  )  27.3216일 = 27일  7시간 43분
근점월(近點月/Anomaistic month)  27.5546일 = 27일 13시간 19분
교점월(交點月/Draconic month  )  27.2122일 = 27일  5시간  6분

//===========================================================================
# 지구 자전
북극과 남극을 잇는 선기준으로 23시간 56분 04.091초 주기
지구의 북극에서 보았을 때 시계 반대방향으로 회전

# 보통 1년이라 하면 대개 회귀년을 지칭

//===========================================================================
# Unix Epoch Time
1970년 01월 01일
윤초 없음

# 윤초
GMT 12월 31일 23:59:60 - 한국시간 01월 01일 오전 08시 59분 60초
GMT 06월 30일 23:59:60 - 한국시간 07월 01일 오전 08시 59분 60초
필요시 삽입됨

# Epoch Time
윤초 표시하지 않음

# 참고 URL
https://en.wikipedia.org/wiki/Julian_day

http://aa.usno.navy.mil/data/docs/JulianDate.php
https://www.tondering.dk/claus/cal/gregorian.php#country
http://jidolstar.tistory.com/482

*/





/////////////////////////////////////////////////////////////////////////////
//
// Headers
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include <stdint.h>
#include <stdbool.h>
#include "jdn.h"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
//!
//! @brief jdn을 modified jdn으로 변환.
//!
//! @param jdn          jdn.
//! @param modified_jdn modified jdn.
//! 
void jdn_to_modified_jdn (const int32_t jdn, int32_t* const modified_jdn)
{
	/*
	# Modified JD
	
	Epoch:       0h Nov 17, 1858
	Calculation: JD - 2400000.5
	*/

	*modified_jdn = jdn-2400001;
}

//!
//! @brief jdn을 truncated jd으로 변환.
//!
//! @param jdn          jdn.
//! @param truncated_jd truncated jd.
//! 
void jdn_to_truncated_jd (const int32_t jdn, int32_t* const truncated_jd)
{
	/*
	# Truncated JD
	
	Introduced by NASA in 1979
	
	Epoch:       0h May 24, 1968
	Calculation: floor (JD - 2440000.5)

	cf: 
	ceil () 소수점 이하 올림
	floor() 소수점 이하 버림
	round() 소수점 반올림
	*/

	*truncated_jd = jdn-2440001;
}

//!
//! @brief jdn을 lilian date으로 변환.
//!
//! @param jdn         jdn.
//! @param lilian_date lilian date.
//! 
void jdn_to_lilian_date (const int32_t jdn, int32_t* const lilian_date)
{
	/*
	# Lilian date 

	Count of days of the Gregorian calendar
	
	Epoch:       Oct 15, 1582
	Calculation: floor (JD - 2299159.5)
	*/

	*lilian_date = jdn-2299160;
}

//!
//! @brief jdn을 unix 일 수로 변환.
//!
//! @param jdn                 jdn.
//! @param unix_time_day_count 1970년 1월 1일 부터 현재까지의 일 수.
//! 
void jdn_to_unix_time_day_count (const int32_t jdn, int32_t* const unix_time_day_count)
{
	/*
	# Unix Time

	Count of seconds

	Epoch:       0h Jan 1, 1970
	Calculation: (JD - 2440587.5) × 86400
	*/

	*unix_time_day_count = jdn-2440588;
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
//!
//! @brief 그레고리력을 jdn으로 변환.
//!
//! Converting Gregorian calendar date to Julian Day Number(noon).
//!
//! @param year  년.
//! @param month 월.
//! @param day   일.
//! @param jdn   jdn.
//! 
void gregorian_calendar_date_to_jdn (const int32_t year, const int32_t month, const int32_t day, int32_t* const jdn)
{
	// The algorithm is valid for all (possibly proleptic) Gregorian calendar dates after November 23, -4713.

	int32_t J;
	int32_t Y;
	int32_t M;
	int32_t D;


	Y = year;
	M = month;
	D = day;

	
	int32_t M1;
	int32_t Y1;


	M1 = (M - 14) / 12;
	Y1 = Y + 4800;
	J  = 1461 * (Y1 + M1) / 4 + 367 * (M - 2 - 12 * M1) / 12 - (3 * ((Y1 + M1 +100) / 100)) / 4 + D - 32075;


	*jdn = J;
}

//!
//! @brief 율리우스력을 jdn으로 변환.
//!
//! Converting Julian calendar date to Julian Day Number(noon).
//!
//! @param year  년.
//! @param month 월.
//! @param day   일.
//! @param jdn   jdn.
//! 
void julian_calendar_date_to_jdn (const int32_t year, const int32_t month, const int32_t day, int32_t* const jdn)
{
	// The algorithm is valid for all (possibly proleptic) Julian calendar years >= -4712, that is, for all JDN >= 0.

	int32_t J;
	int32_t Y;
	int32_t M;
	int32_t D;


	Y = year;
	M = month;
	D = day;

	J = 367 * Y - (7 * (Y + 5001 + (M - 9) / 7)) / 4 + (275 * M) / 9 + D + 1729777;


	*jdn = J;
}

#if 0
void jdn_to_gregorian_calendar_date (const int32_t jdn, int32_t* const year, int32_t* const month, int32_t* const day)
{
	int32_t J;
	int32_t Y;
	int32_t M;
	int32_t D;

	
	J = jdn;


	int32_t p;
	int32_t q;
	int32_t r;
	int32_t s;
	int32_t t;
	int32_t u;
	int32_t v;


	p = J + 68569;
	q = 4*p/146097;
	r = p - (146097*q + 3)/4;
	s = 4000*(r+1)/1461001;
	t = r - 1461*s/4 + 31;
	u = 80*t/2447;
	v = u/11;

	Y = 100*(q-49)+s+v;
	M = u + 2 - 12*v;
	D = t - 2447*u/80;

	*year  = Y;
	*month = M;
	*day   = D;
}
#endif

//!
//! @brief jdn을 그레고리력으로 변환.
//!
//! @param jdn   jdn.
//! @param year  년.
//! @param month 월.
//! @param day   일.
//! 
void jdn_to_gregorian_calendar_date(const int32_t jdn, int32_t* const year, int32_t* const month, int32_t* const day)
{
	const int32_t y = 4716;
	const int32_t j = 1401;
	const int32_t m = 2;
	const int32_t n = 12;
	const int32_t r = 4;
	const int32_t p = 1461;
	const int32_t v = 3;
	const int32_t u = 5;
	const int32_t s = 153;
	const int32_t w = 2;
	const int32_t B = 274277;
	const int32_t C = -38;

	int32_t J;
	int32_t Y;
	int32_t M;
	int32_t D;


	J = jdn;


	int32_t f;
	int32_t e;
	int32_t g;
	int32_t h;

	f = J + j + (((4 * J + B) / 146097) * 3) / 4 + C;
	e = r * f + v;
	g = (e % p) / r;
	h = u * g + w;
	
	D = (h % s) / u  + 1;
	M = (h / s + m) % n + 1;
	Y = (e / p) - y + (n + m - M) / n;


	*year  = Y;
	*month = M;
	*day   = D;
}

//!
//! @brief jdn을 율리우스력으로 변환.
//!
//! @param jdn   jdn.
//! @param year  년.
//! @param month 월.
//! @param day   일.
//! 
void jdn_to_julian_calendar_date (const int32_t jdn, int32_t* const year, int32_t* const month, int32_t* const day)
{
	const int32_t y = 4716;
	const int32_t j = 1401;
	const int32_t m = 2;
	const int32_t n = 12;
	const int32_t r = 4;
	const int32_t p = 1461;
	const int32_t v = 3;
	const int32_t u = 5;
	const int32_t s = 153;
	const int32_t w = 2;
//	const int32_t B = 274277;
//	const int32_t C = -38;


	int32_t J;
	int32_t Y;
	int32_t M;
	int32_t D;


	J = jdn;


	int32_t f;
	int32_t e;
	int32_t g;
	int32_t h;

	f = J + j;
	e = r * f + v;
	g = (e % p) / r;
	h = u * g + w;
	
	D = (h % s) / u  + 1;
	M = (h / s + m) % n + 1;
	Y = (e / p) - y + (n + m - M) / n;


	*year  = Y;
	*month = M;
	*day   = D;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
//!
//! @brief 날짜가 1582년 10월 05일 부터 1582년 10월 14일 사이 확인.
//! 
//! 율리우스력에서 그레고리력으로 변경될때 제거된 날짜 확인.
//!
//! @param year  년.
//! @param month 월.
//! @param day   일.
//! 
//! @retval 0  1582년 10월 05일 부터 1582년 10월 14일 사이.
//! @retval <0 1582년 10월 05일 부터 1582년 10월 14일 이전(음수).
//! @retval >0 1582년 10월 05일 부터 1582년 10월 14일 이후(양수).
//! 
int32_t calendar_date_from_1582_10_05_to_1582_10_14 (const int32_t year, const int32_t month, const int32_t day)
{
	int32_t from_1582_10_05_to_1582_10_14;



	from_1582_10_05_to_1582_10_14 = 0;
	if     (year< 1582)
	{
		from_1582_10_05_to_1582_10_14 = -1;
	}
	else if (year==1582)
	{
		if      (month <  10)
		{
			from_1582_10_05_to_1582_10_14 = -1;
		}
		else if (month == 10)
		{
			if      (day <= 4)
			{
				from_1582_10_05_to_1582_10_14 = -1;
			}
			else if (day >= 15)
			{
				from_1582_10_05_to_1582_10_14 = 1;
			}
			else
			{
				from_1582_10_05_to_1582_10_14 = 0;
			}
		}
		else /* if (month >  10) */
		{
			from_1582_10_05_to_1582_10_14 = 1;
		}
	}
	else /* if (year> 1582) */
	{
		from_1582_10_05_to_1582_10_14 = 1;
	}


	return from_1582_10_05_to_1582_10_14;
}

//!
//! @brief 날짜에 대한 jdn 계산.
//! 
//! @param year  년.
//! @param month 월.
//! @param day   일.
//! @param jdn   jdn.
//! 
//! @return 성공 여부.
//! 
bool calendar_date_to_jdn (const int32_t year, const int32_t month, const int32_t day, int32_t* const jdn)
{
	int32_t from_1582_10_05_to_1582_10_14;



	from_1582_10_05_to_1582_10_14 = calendar_date_from_1582_10_05_to_1582_10_14(year,month,day);

	if      (0> from_1582_10_05_to_1582_10_14)
	{
		julian_calendar_date_to_jdn (year,month,day, jdn);
	}
	else if (0==from_1582_10_05_to_1582_10_14)
	{
		return false;
	}
	else /* if (0< from_1582_10_05_to_1582_10_14) */
	{
		gregorian_calendar_date_to_jdn (year,month,day, jdn);
	}

	return true;
}

//!
//! @brief jdn에 대한 날짜 계산.
//! 
//! @param year  년.
//! @param month 월.
//! @param day   일.
//! @param jdn   jdn.
//! 
void jdn_to_calendar_date (const int32_t jdn, int32_t* const year, int32_t* const month, int32_t* const day)
{
	// jdn: 2299160 = 1582-10-04 Julian Calendar Date
	// jdn: 2299161 = 1582-10-15 Gregorian Calendar Date

	if (jdn<=2299160)
	{
		jdn_to_julian_calendar_date    (jdn, year,month,day);
	}
	else
	{
		jdn_to_gregorian_calendar_date (jdn, year,month,day);
	}
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
//!
//! @brief jdn을 이용하여 미국 표준 요일 반환.
//! 
//! @param jdn jdn.
//! 
//! @retval 0 Sun.  
//! @retval 1 Mon.  
//! @retval 2 Tue.  
//! @retval 3 Wed.  
//! @retval 4 Thu.  
//! @retval 5 Fri.  
//! @retval 6 Sat.  
//! 
int32_t get_day_of_week_us (const int32_t jdn)
{
	/*
	W1 = mod(J + 1, 7)

	0=Sun
	1=Mon
	2=Tue
	3=Wed
	4=Thu
	5=Fri
	6=Sat
	*/

	return (jdn + 1) % 7;
}

//!
//! @brief jdn을 이용하여 국제 표준 요일 반환.
//! 
//! @param jdn jdn.
//! 
//! @retval 1 Mon.  
//! @retval 2 Tue.  
//! @retval 3 Wed.  
//! @retval 4 Thu.  
//! @retval 5 Fri.  
//! @retval 6 Sat.  
//! @retval 7 Sun.  
//! 
int32_t get_day_of_week_iso (const int32_t jdn)
{
	/*
	W0 = mod (J, 7) + 1

	1=Mon
	2=Tue
	3=Wed
	4=Thu
	5=Fri
	6=Sat
	7=Sun
	*/

	return (jdn % 7) + 1;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
//!
//! @brief 그레고리력 기준의 윤년 여부 반환.
//! 
//! @param year 년도.
//! 
//! @retval true  윤년.
//! @retval false 평년.
//! 
bool gregorian_calendar_is_leap_year (const int32_t year)
{
	if ( (0==(year%400)) 
	     || 
	     ((0!=(year%100)) && (0==(year%4))) )
	{
		return true;
	}

	return false;
}

//!
//! @brief 그레고리력 기준의 월의 마지막 일자를 계산.
//! 
//! @param year  년.
//! @param month 월.
//! @param day   월의 마지막 일자.
//! 
//! @return 성공 여부.
//! 
bool gregorian_calendar_get_last_day_of_month (const int32_t year, const int32_t month, int32_t* const day)
{
	int32_t month_days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };


	if (gregorian_calendar_is_leap_year(year))
	{
		month_days[1] = 29;
	}

	
	if ( !( (0<month) && (month<13)) )
	{
		return false;
	}


	*day = month_days[month-1];

	return true;
}

//!
//! @brief 그레고리력 기준의 유효한 유효한 날짜 여부 반환.
//! 
//! @param year  년.
//! @param month 월.
//! @param day   일.
//! 
//! @return 유효한 날짜 여부.
//! 
bool gregorian_calendar_is_valid_date (const int32_t year, const int32_t month, const int32_t day)
{
	int32_t last_day_of_month;



	if (false==gregorian_calendar_get_last_day_of_month(year, month, &last_day_of_month))
	{
		return false;
	}

	if ( (day < 0) || (day > last_day_of_month) ) 
	{
		return false;
	}

	return true;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
//!
//! @brief 기준 epoch jdn의 값에서 일 수를 더해 jdn 계산.
//! 
//! @param base_epoch_jdn 기준 epoch jdn.
//! @param day_number     더 할 일 수.
//! @param jdn            jdn.
//! 
void epoch_to_jdn (const int32_t base_epoch_jdn, const int32_t day_number, int32_t* const jdn)
{	
	*jdn = base_epoch_jdn + day_number;
}

//!
//! @brief 기준 epoch jdn의 값에서 일 수를 더해 년/월/일 계산.
//! 
//! @param base_epoch_jdn 기준 epoch jdn.
//! @param day_number     더 할 일 수.
//! @param year           년.
//! @param month          월.
//! @param day            일.
//! 
void epoch_to_date (const int32_t base_epoch_jdn, const int32_t day_number, int32_t* const year, int32_t* const month, int32_t* const day)
{
	int32_t jdn;

	
	epoch_to_jdn(base_epoch_jdn, day_number, &jdn);
	

	jdn_to_gregorian_calendar_date(jdn, year, month, day);
}

//!
//! @brief 기준 epoch jdn의 값에서 일 수를 더해 요일(미국 표준) 계산.
//! 
//! get_day_of_week_us() 함수 참조.
//! 
//! @param base_epoch_jdn 기준 epoch jdn.
//! @param day_number     더 할 일 수.
//! @param day_of_week    요일.
//! 
void epoch_to_day_of_week (const int32_t base_epoch_jdn, const int32_t day_number, int32_t* const day_of_week)
{
	int32_t jdn;

	
	epoch_to_jdn(base_epoch_jdn, day_number, &jdn);
	

	*day_of_week = get_day_of_week_us(jdn);
}

//!
//! @brief 한 날의 초를 시/분/초 단위 계산.
//! 
//! @param daysecond_number  한 날의 초.
//! @param hour              시.
//! @param minute            분.
//! @param second            초.
//! 
//! @par pseudocode
//! @code
//! function()
//! {
//!		*hour   =  daysecond_number / 3600;
//!		*minute = (daysecond_number % 3600) / 60;
//!		*second = (daysecond_number % 3600) % 60;
//! }
//! @endcode
//! 
void epoch_to_time (const int32_t daysecond_number, int32_t* const hour, int32_t* const minute, int32_t* const second)
{
	*hour   =  daysecond_number / 3600;
	*minute = (daysecond_number % 3600) / 60;
	*second = (daysecond_number % 3600) % 60;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
//!
//! @brief 경과된 시간의 epoch 초를 경과 된 날 수 반환.
//! 
//! @param epoch_second 경과된 시간의 epoch 초.
//! 
//! @return 경과 된 날 수.
//! 
//! @par pseudocode
//! @code
//! function()
//! {
//!		return epoch_second/(86400=24시*60분*60초);
//! }
//! @endcode
//! 
int32_t epoch_second_get_day_number (const jdn_time_t epoch_second)
{
	const int32_t second_per_day = 86400; // 24*60*60;
	
	int32_t day_number;


	day_number = (int32_t)(epoch_second / second_per_day);


	return day_number;
}

//!
//! @brief 경과된 시간의 epoch 초를 경과 된 한 날의 초 반환.
//! 
//! @param epoch_second 경과된 시간의 epoch 초.
//! 
//! @return 경과 된 한 날의 초 계산.
//! 
//! @par pseudocode
//! @code
//! function()
//! {
//!		return epoch_second%(86400=24시*60분*60초);
//! }
//! @endcode
//! 
int32_t epoch_second_get_daysecond_number (const jdn_time_t epoch_second)
{
	const int32_t second_per_day = 86400; // 24*60*60;
	
	int32_t daysecond_number;


	daysecond_number = (int32_t)(epoch_second % second_per_day);


	return daysecond_number;
}

//===========================================================================
//!
//! @brief 기준 epoch jdn에서 경과된 시간의 epoch 초에 대해 jdn 계산.
//! 
//! @param base_epoch_jdn 기준 epoch jdn.
//! @param epoch_second   경과된 시간의 epoch 초.
//! @param jdn            jdn.
//! 
void epoch_second_to_jdn (const int32_t base_epoch_jdn, const jdn_time_t epoch_second, int32_t* const jdn)
{
	int32_t day_number;

	
	day_number = epoch_second_get_day_number(epoch_second);
	

	epoch_to_jdn(base_epoch_jdn, day_number, jdn);
}

//!
//! @brief 기준 epoch jdn에서 경과된 시간의 epoch 초에 대해 년/월/일/요일/시/분/초 계산.
//! 
//! @param base_epoch_jdn 기준 epoch jdn.
//! @param epoch_second   경과된 시간의 epoch 초.
//! @param year           년.
//! @param month          월.
//! @param day            일.
//! @param day_of_week    요일(미국 표준).
//! @param hour           시.
//! @param minute         분.
//! @param second         초.
//! 
void epoch_second_to_datetime (
	const int32_t base_epoch_jdn, const jdn_time_t epoch_second, 
	int32_t* const year, int32_t* const month, int32_t* const day, int32_t* const day_of_week, 
	int32_t* const hour, int32_t* const minute, int32_t* const second
)
{
	int32_t day_number;
	int32_t daysecond_number;
	
	int32_t jdn;


	day_number       = epoch_second_get_day_number      (epoch_second);
	daysecond_number = epoch_second_get_daysecond_number(epoch_second);
	

	epoch_to_jdn(base_epoch_jdn, day_number, &jdn);

	
	jdn_to_gregorian_calendar_date(jdn, year, month, day);
	*day_of_week = get_day_of_week_us(jdn);

	
	epoch_to_time(daysecond_number, hour, minute, second);
}

//!
//! @brief 기준 epoch jdn에서 경과된 시간의 epoch 초에 대해 년/월/일 계산.
//! 
//! @param base_epoch_jdn epoch jdn.
//! @param epoch_second   경과된 시간의 epoch 초.
//! @param year           년.
//! @param month          월.
//! @param day            일.
//! 
void epoch_second_to_date (
	const int32_t base_epoch_jdn, const jdn_time_t epoch_second, 
	int32_t* const year, int32_t* const month, int32_t* const day
)
{
	int32_t day_number;
	
	int32_t jdn;


	day_number = epoch_second_get_day_number(epoch_second);
	

	epoch_to_jdn(base_epoch_jdn, day_number, &jdn);

	
	jdn_to_gregorian_calendar_date(jdn, year, month, day);
}

//!
//! @brief 기준 epoch jdn에서 경과된 시간의 epoch 초에 대해 요일 계산.
//! 
//! @param base_epoch_jdn epoch jdn.
//! @param epoch_second   경과된 시간의 epoch 초.
//! @param day_of_week    요일(미국 표준).
//! 
void epoch_second_to_day_of_week (const int32_t base_epoch_jdn, const jdn_time_t epoch_second, int32_t* const day_of_week)
{
	int32_t day_number;
	
	int32_t jdn;


	day_number = epoch_second_get_day_number(epoch_second);

	
	epoch_to_jdn(base_epoch_jdn, day_number, &jdn);

	
	*day_of_week = get_day_of_week_us(jdn);
}

//!
//! @brief 경과된 시간의 epoch 초에 대해 시/분/초 계산.
//! 
//! @param epoch_second   경과된 시간의 epoch 초.
//! @param hour           시.
//! @param minute         분.
//! @param second         초.
//! 
void epoch_second_to_time (const jdn_time_t epoch_second, int32_t* const hour, int32_t* const minute, int32_t* const second)
{
	int32_t daysecond_number;


	daysecond_number = epoch_second_get_daysecond_number(epoch_second);
	

	epoch_to_time(daysecond_number, hour, minute, second);
}

//!
//! @brief 년/월/일/요일/시/분/초에 대해 기준 epoch jdn에서 경과된 시간의 epoch 초 계산.
//! 
//! @param year           년.
//! @param month          월.
//! @param day            일.
//! @param hour           시.
//! @param minute         분.
//! @param second         초.
//! @param base_epoch_jdn 기준 epoch jdn.
//! @param epoch_second   경과된 시간의 epoch 초.
//! 
void datetime_to_epoch_second (
	const int32_t year, const int32_t month, const int32_t day, 
	const int32_t hour, const int32_t minute, const int32_t second, 
	const int32_t base_epoch_jdn, jdn_time_t* const epoch_second
)
{
	const int32_t second_per_day = 86400; // 24*60*60;

	int32_t jdn;

	jdn_time_t day_number;
	jdn_time_t daysecond_number;


	gregorian_calendar_date_to_jdn (year, month, day, &jdn);

	
	day_number       = jdn - base_epoch_jdn;
	daysecond_number = hour*3600 + minute*60 + second;
	

	*epoch_second = day_number*second_per_day + daysecond_number;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
//!
//! @brief unix 기준 시간에 대한 기준 epoch jdn 반환.
//! 
//! @retval 2440588 jdn 1970년 01월 01일 12:00:00.
//! 
int32_t unix_time_get_base_epoch_jdn (void)
{
	const int32_t base_jdn = 2440588; // 1970년 01월 01일 12:00:00


	return base_jdn;
}

//!
//! @brief unix 초 시간에 대한 jdn 계산.
//! 
//! @param t   unix 초 시간.
//! @param jdn jdn.
//! 
void unix_time_to_jdn (const jdn_time_t t, int32_t* const jdn)
{
	epoch_second_to_jdn (unix_time_get_base_epoch_jdn(), t, jdn);
}

//!
//! @brief unix 초 시간에 대한 년/월/일/요일/시/분/초 계산.
//! 
//! @param t              unix 초 시간.
//! @param year           년.
//! @param month          월.
//! @param day            일.
//! @param day_of_week    요일(미국 표준).
//! @param hour           시.
//! @param minute         분.
//! @param second         초.
//! 
void unix_time_to_datetime (
	const jdn_time_t t, 
	int32_t* const year, int32_t* const month, int32_t* const day, int32_t* const day_of_week, 
	int32_t* const hour, int32_t* const minute, int32_t* const second
)
{
	epoch_second_to_datetime (unix_time_get_base_epoch_jdn(), t, year, month, day, day_of_week, hour, minute, second);
}

//!
//! @brief unix 초 시간에 대한 년/월/일 계산.
//! 
//! @param t     unix 초 시간.
//! @param year  년.
//! @param month 월.
//! @param day   일.
//! 
void unix_time_to_date (const jdn_time_t t, int32_t* const year, int32_t* const month, int32_t* const day)
{
	epoch_second_to_date (unix_time_get_base_epoch_jdn(), t, year, month, day);
}

//!
//! @brief unix 초 시간에 대한 요일 계산.
//! 
//! @param t           unix 초 시간.
//! @param day_of_week 요일(미국 표준).
//! 
void unix_time_to_day_of_week (const jdn_time_t t, int32_t* const day_of_week)
{
	epoch_second_to_day_of_week (unix_time_get_base_epoch_jdn(), t, day_of_week);
}

//!
//! @brief unix 초 시간에 대한 시/분/초 계산.
//! 
//! @param t      unix 초 시간.
//! @param hour   시.
//! @param minute 분.
//! @param second 초.
void unix_time_to_time (const jdn_time_t t, int32_t* const hour, int32_t* const minute, int32_t* const second)
{
	epoch_second_to_time (t, hour, minute, second);
}

//!
//! @brief unix 초 시간에 대한 시/분/초 계산.
//! 
//! @param year   년.
//! @param month  월.
//! @param day    일.
//! @param hour   시.
//! @param minute 분.
//! @param second 초.
//! @param t      unix 초 시간.
//! 
void datetime_to_unix_time (
	const int32_t year, const int32_t month, const int32_t day, 
	const int32_t hour, const int32_t minute, const int32_t second, 
	jdn_time_t* const t
)
{
	datetime_to_epoch_second (year, month, day, hour, minute, second, unix_time_get_base_epoch_jdn(), t);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#if 1





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include <stdio.h>
#include <time.h>





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void show (
	int32_t jdn           ,
	int32_t year          ,
	int32_t month         ,
	int32_t day           ,
	int32_t day_of_week_us,
	int32_t hour          ,
	int32_t minute        , 
	int32_t second
	)
{
	const char* day_of_week_string_list[] = { "일", "월", "화", "수", "목", "금", "토" };
	const char* day_of_week;


	day_of_week = day_of_week_string_list[day_of_week_us];


	int32_t modified_jdn;
	int32_t truncated_jd;
	int32_t lilian_date;
	int32_t unix_time_day_count;


	jdn_to_modified_jdn       (jdn, &modified_jdn       );
	jdn_to_truncated_jd       (jdn, &truncated_jd       );
	jdn_to_lilian_date        (jdn, &lilian_date        );
	jdn_to_unix_time_day_count(jdn, &unix_time_day_count);

	printf ("%+05d-%02d-%02d(%s) %02d:%02d:%02d = JDN(%8d), MJDN(%8d), TJD(%8d), LILIAN(%8d), UNIX(%8d) \n", 
		year,month,day, day_of_week, 
		hour, minute, second,
		jdn,
		modified_jdn       ,
		truncated_jd       ,
		lilian_date        ,
		unix_time_day_count
		);
}

int main (int argc, char* argv[])
//int jdn_test ()
{
	int32_t jdn         = 0;
	int32_t year        = 0;
	int32_t month       = 0;
	int32_t day         = 0;
	int32_t day_of_week = 0;
	int32_t hour        = 0;
	int32_t minute      = 0;
	int32_t second      = 0;

	int32_t day_count = 0;

	jdn_time_t t;
	const jdn_time_t gmt_plus_9 = 9 * 60 * 60; // GMT+9:00 기준의 현재 시간. (한국 표준시 기준의 현재 시간.)


	//-----------------------------------------------------------------------
	// 1st-Jan 1, 4713 BC
	printf("# 1st-Jan 1, 4713 BC\n");
	jdn = 0;
	jdn_to_calendar_date(jdn, &year,&month,&day); day_of_week = get_day_of_week_us(jdn); show(jdn, year, month, day, day_of_week, hour, minute, second);

	year  =-4712; 
	month =1;
	day   =1;
	calendar_date_to_jdn(year,month,day,   &jdn); day_of_week = get_day_of_week_us(jdn); show(jdn, year, month, day, day_of_week, hour, minute, second);

	printf("\n");


	//-----------------------------------------------------------------------
	printf("# 1st-Jan 1, 4712 BC\n");
	year  =-4711;
	month =1;
	day   =1;
	calendar_date_to_jdn(year,month,day,   &jdn); day_of_week = get_day_of_week_us(jdn); show(jdn, year, month, day, day_of_week, hour, minute, second);
	
	printf ("\n");


	//-----------------------------------------------------------------------
	// 1st-Jan, 1 BC
	printf("# 1st-Jan, 1 BC\n");
	year  =0;
	month =1;
	day   =1;
	calendar_date_to_jdn(year,month,day,   &jdn); day_of_week = get_day_of_week_us(jdn); show(jdn, year, month, day, day_of_week, hour, minute, second);
	jdn_to_calendar_date(jdn, &year,&month,&day); day_of_week = get_day_of_week_us(jdn); show(jdn, year, month, day, day_of_week, hour, minute, second);
	
	printf ("\n");


	//-----------------------------------------------------------------------
	// 1st-Jan, 1 AD
	printf("# 1st-Jan, 1 AD\n");
	year  =1;
	month =1;
	day   =1;
	calendar_date_to_jdn(year,month,day,   &jdn); day_of_week = get_day_of_week_us(jdn); show(jdn, year, month, day, day_of_week, hour, minute, second);
	jdn_to_calendar_date(jdn, &year,&month,&day); day_of_week = get_day_of_week_us(jdn); show(jdn, year, month, day, day_of_week, hour, minute, second);
	
	printf ("\n");


	//-----------------------------------------------------------------------
	// 1st-Jan, 2 AD
	printf("# 1st-Jan, 2 AD\n");
	year  =2;
	month =1;
	day   =1;
	calendar_date_to_jdn(year,month,day,   &jdn); day_of_week = get_day_of_week_us(jdn); show(jdn, year, month, day, day_of_week, hour, minute, second);
	jdn_to_calendar_date(jdn, &year,&month,&day); day_of_week = get_day_of_week_us(jdn); show(jdn, year, month, day, day_of_week, hour, minute, second);
	
	printf ("\n");


	//-----------------------------------------------------------------------
	// jdn: 2299161 = 1582-10-15 Gregorian Calendar Date
	printf("# jdn: 2299161 = 1582-10-15 Gregorian Calendar Date\n");
	jdn = 2299161-2;
	jdn_to_calendar_date(jdn, &year,&month,&day); day_of_week = get_day_of_week_us(jdn); show(jdn, year, month, day, day_of_week, hour, minute, second);

	jdn = 2299161-1;
	jdn_to_calendar_date(jdn, &year,&month,&day); day_of_week = get_day_of_week_us(jdn); show(jdn, year, month, day, day_of_week, hour, minute, second);

	jdn = 2299161;
	jdn_to_calendar_date(jdn, &year,&month,&day); day_of_week = get_day_of_week_us(jdn); show(jdn, year, month, day, day_of_week, hour, minute, second);

	jdn = 2299161+1;
	jdn_to_calendar_date(jdn, &year,&month,&day); day_of_week = get_day_of_week_us(jdn); show(jdn, year, month, day, day_of_week, hour, minute, second);

	printf("\n");


	//-----------------------------------------------------------------------
	year  =1582;
	month =10;
	day   = 3;
	calendar_date_to_jdn(year,month,day,   &jdn); day_of_week = get_day_of_week_us(jdn); show(jdn, year, month, day, day_of_week, hour, minute, second);

	year  =1582;
	month =10;
	day   = 4;
	calendar_date_to_jdn(year,month,day,   &jdn); day_of_week = get_day_of_week_us(jdn); show(jdn, year, month, day, day_of_week, hour, minute, second);

	printf("\n");


	//-----------------------------------------------------------------------
	// Lilian date : Oct 15, 1582 = floor (JD - 2299159.5) ; Count of days of the Gregorian calendar
	printf("# Lilian date : Oct 15, 1582 = floor (JD - 2299159.5)\n");
	year  =1582;
	month =10;
	day   =15;
	calendar_date_to_jdn(year,month,day,   &jdn); day_of_week = get_day_of_week_us(jdn); show(jdn, year, month, day, day_of_week, hour, minute, second);

	year  =1582;
	month =10;
	day   =16;
	calendar_date_to_jdn(year,month,day,   &jdn); day_of_week = get_day_of_week_us(jdn); show(jdn, year, month, day, day_of_week, hour, minute, second);
	
	printf ("\n");


	//-----------------------------------------------------------------------
	// Reduced JD (JD - 2400000)
	printf("# Reduced JD (JD - 2400000)\n");
	year  =1858;
	month =11;
	day   =16;
	calendar_date_to_jdn(year,month,day,   &jdn); day_of_week = get_day_of_week_us(jdn); show(jdn, year, month, day, day_of_week, hour, minute, second);
	jdn_to_calendar_date(jdn, &year,&month,&day); day_of_week = get_day_of_week_us(jdn); show(jdn, year, month, day, day_of_week, hour, minute, second);
	
	printf ("\n");


	//-----------------------------------------------------------------------
	// Modified JD: 0h Nov 17, 1858 = (JD - 2400000.5)
	printf("# Modified JD: 0h Nov 17, 1858 = (JD - 2400000.5)\n");
	year  =1858;
	month =11;
	day   =17;
	calendar_date_to_jdn(year,month,day,   &jdn); day_of_week = get_day_of_week_us(jdn); show(jdn, year, month, day, day_of_week, hour, minute, second);
	jdn_to_calendar_date(jdn, &year,&month,&day); day_of_week = get_day_of_week_us(jdn); show(jdn, year, month, day, day_of_week, hour, minute, second);
	
	printf ("\n");
	

	//-----------------------------------------------------------------------
	// Truncated JD: 0h May 24, 1968 = floor (JD - 2440000.5) ; Introduced by NASA in 1979
	printf("# Truncated JD: 0h May 24, 1968 = floor (JD - 2440000.5)\n");
	year  =1968;
	month =5;
	day   =24;
	calendar_date_to_jdn(year,month,day,   &jdn); day_of_week = get_day_of_week_us(jdn); show(jdn, year, month, day, day_of_week, hour, minute, second);
	jdn_to_calendar_date(jdn, &year,&month,&day); day_of_week = get_day_of_week_us(jdn); show(jdn, year, month, day, day_of_week, hour, minute, second);
	
	printf ("\n");


	//-----------------------------------------------------------------------
	// Unix Time: 0h Jan 1, 1970 = (JD - 2440587.5) × 86400
	printf("# Unix Time: 0h Jan 1, 1970 = (JD - 2440587.5) × 86400\n");
	year  =1970;
	month =1;
	day   =1;
	calendar_date_to_jdn(year,month,day,   &jdn); day_of_week = get_day_of_week_us(jdn); show(jdn, year, month, day, day_of_week, hour, minute, second);
	jdn_to_calendar_date(jdn, &year,&month,&day); day_of_week = get_day_of_week_us(jdn); show(jdn, year, month, day, day_of_week, hour, minute, second);
	
	printf ("\n");


	//-----------------------------------------------------------------------
	printf("# 1st-Jan, 2000 AD\n");
	year  =2000;
	month =1;
	day   =1;
	calendar_date_to_jdn(year,month,day,   &jdn); day_of_week = get_day_of_week_us(jdn); show(jdn, year, month, day, day_of_week, hour, minute, second);
	jdn_to_calendar_date(jdn, &year,&month,&day); day_of_week = get_day_of_week_us(jdn); show(jdn, year, month, day, day_of_week, hour, minute, second);
	
	printf ("\n");


	//-----------------------------------------------------------------------
	t = (jdn_time_t)(time(NULL) + gmt_plus_9);
	day_count = (int32_t)(t / 86400);

#if 1
	// 64-bit time_t인 경우, 2038년 1월 19일 이후의 시간도 표현 가능.
	printf ("# now unix seconds: time() = %lld, day_count = %lld / 86400 = %d\n", t, t, day_count);
#else
	// 32-bit time_t인 경우, 2038년 1월 19일 이후의 시간은 표현 불가능.
	printf("# now unix seconds: time() = %ld, day_count = %ld / 86400 = %d\n", t, t, day_count);
#endif

	unix_time_to_jdn     (t, &jdn);
	unix_time_to_datetime(t, &year,&month,&day, &day_of_week, &hour, &minute, &second);

	show (jdn, year, month, day, day_of_week, hour, minute, second);

	calendar_date_to_jdn(year,month,day,   &jdn); day_of_week = get_day_of_week_us(jdn); show(jdn, year, month, day, day_of_week, hour, minute, second);
	jdn_to_calendar_date(jdn, &year,&month,&day); day_of_week = get_day_of_week_us(jdn); show(jdn, year, month, day, day_of_week, hour, minute, second);

	printf ("\n");

	return 0;
}
#endif

/*

# 1st-Jan 1, 4713 BC
-4712-01-01(월) 00:00:00 = JDN(       0), MJDN(-2400001), TJD(-2440001), LILIAN(-2299160), UNIX(-2440588)
-4712-01-01(월) 00:00:00 = JDN(       0), MJDN(-2400001), TJD(-2440001), LILIAN(-2299160), UNIX(-2440588)

# 1st-Jan 1, 4712 BC
-4711-01-01(수) 00:00:00 = JDN(     366), MJDN(-2399635), TJD(-2439635), LILIAN(-2298794), UNIX(-2440222)

# 1st-Jan, 1 BC
+0000-01-01(목) 00:00:00 = JDN( 1721058), MJDN( -678943), TJD( -718943), LILIAN( -578102), UNIX( -719530)
+0000-01-01(목) 00:00:00 = JDN( 1721058), MJDN( -678943), TJD( -718943), LILIAN( -578102), UNIX( -719530)

# 1st-Jan, 1 AD
+0001-01-01(토) 00:00:00 = JDN( 1721424), MJDN( -678577), TJD( -718577), LILIAN( -577736), UNIX( -719164)
+0001-01-01(토) 00:00:00 = JDN( 1721424), MJDN( -678577), TJD( -718577), LILIAN( -577736), UNIX( -719164)

# 1st-Jan, 2 AD
+0002-01-01(일) 00:00:00 = JDN( 1721789), MJDN( -678212), TJD( -718212), LILIAN( -577371), UNIX( -718799)
+0002-01-01(일) 00:00:00 = JDN( 1721789), MJDN( -678212), TJD( -718212), LILIAN( -577371), UNIX( -718799)

# jdn: 2299161 = 1582-10-15 Gregorian Calendar Date
+1582-10-03(수) 00:00:00 = JDN( 2299159), MJDN( -100842), TJD( -140842), LILIAN(      -1), UNIX( -141429)
+1582-10-04(목) 00:00:00 = JDN( 2299160), MJDN( -100841), TJD( -140841), LILIAN(       0), UNIX( -141428)
+1582-10-15(금) 00:00:00 = JDN( 2299161), MJDN( -100840), TJD( -140840), LILIAN(       1), UNIX( -141427)
+1582-10-16(토) 00:00:00 = JDN( 2299162), MJDN( -100839), TJD( -140839), LILIAN(       2), UNIX( -141426)

+1582-10-03(수) 00:00:00 = JDN( 2299159), MJDN( -100842), TJD( -140842), LILIAN(      -1), UNIX( -141429)
+1582-10-04(목) 00:00:00 = JDN( 2299160), MJDN( -100841), TJD( -140841), LILIAN(       0), UNIX( -141428)

# Lilian date : Oct 15, 1582 = floor (JD - 2299159.5)
+1582-10-15(금) 00:00:00 = JDN( 2299161), MJDN( -100840), TJD( -140840), LILIAN(       1), UNIX( -141427)
+1582-10-16(토) 00:00:00 = JDN( 2299162), MJDN( -100839), TJD( -140839), LILIAN(       2), UNIX( -141426)

# Reduced JD (JD - 2400000)
+1858-11-16(화) 00:00:00 = JDN( 2400000), MJDN(      -1), TJD(  -40001), LILIAN(  100840), UNIX(  -40588)
+1858-11-16(화) 00:00:00 = JDN( 2400000), MJDN(      -1), TJD(  -40001), LILIAN(  100840), UNIX(  -40588)

# Modified JD: 0h Nov 17, 1858 = (JD - 2400000.5)
+1858-11-17(수) 00:00:00 = JDN( 2400001), MJDN(       0), TJD(  -40000), LILIAN(  100841), UNIX(  -40587)
+1858-11-17(수) 00:00:00 = JDN( 2400001), MJDN(       0), TJD(  -40000), LILIAN(  100841), UNIX(  -40587)

# Truncated JD: 0h May 24, 1968 = floor (JD - 2440000.5)
+1968-05-24(금) 00:00:00 = JDN( 2440001), MJDN(   40000), TJD(       0), LILIAN(  140841), UNIX(    -587)
+1968-05-24(금) 00:00:00 = JDN( 2440001), MJDN(   40000), TJD(       0), LILIAN(  140841), UNIX(    -587)

# Unix Time: 0h Jan 1, 1970 = (JD - 2440587.5) × 86400
+1970-01-01(목) 00:00:00 = JDN( 2440588), MJDN(   40587), TJD(     587), LILIAN(  141428), UNIX(       0)
+1970-01-01(목) 00:00:00 = JDN( 2440588), MJDN(   40587), TJD(     587), LILIAN(  141428), UNIX(       0)

# 1st-Jan, 2000 AD
+2000-01-01(토) 00:00:00 = JDN( 2451545), MJDN(   51544), TJD(   11544), LILIAN(  152385), UNIX(   10957)
+2000-01-01(토) 00:00:00 = JDN( 2451545), MJDN(   51544), TJD(   11544), LILIAN(  152385), UNIX(   10957)

# now unix seconds: time() = 1774447603, day_count = 1774447603 / 86400 = 20537
+2026-03-25(수) 14:06:43 = JDN( 2461125), MJDN(   61124), TJD(   21124), LILIAN(  161965), UNIX(   20537)
+2026-03-25(수) 14:06:43 = JDN( 2461125), MJDN(   61124), TJD(   21124), LILIAN(  161965), UNIX(   20537)
+2026-03-25(수) 14:06:43 = JDN( 2461125), MJDN(   61124), TJD(   21124), LILIAN(  161965), UNIX(   20537)

*/

