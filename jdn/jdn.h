#ifndef INCLUDED__CX__JDN__H
#define INCLUDED__CX__JDN__H

/////////////////////////////////////////////////////////////////////////////
//
// File: jdn.h
//
// Created by MOON, Eui-kwon.
// Created on Apr-20th, 2023.
//
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
//! @file   jdn.h
//! @brief  julian day number 헤더 파일.





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
//#define jdn_time_t int64_t
#define jdn_time_t int32_t

//===========================================================================
//#include <time.h>
//#define jdn_timt_t time_t
//#define jdn_time_t __time64_t
//#define jdn_time_t __time32_t





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void jdn_to_modified_jdn        (const int32_t jdn, int32_t* const modified_jdn);
void jdn_to_truncated_jd        (const int32_t jdn, int32_t* const truncated_jd);
void jdn_to_lilian_date         (const int32_t jdn, int32_t* const lilian_date);
void jdn_to_unix_time_day_count (const int32_t jdn, int32_t* const unix_time_day_count);

//===========================================================================
void gregorian_calendar_date_to_jdn (const int32_t year, const int32_t month, const int32_t day, int32_t* const jdn);
void julian_calendar_date_to_jdn    (const int32_t year, const int32_t month, const int32_t day, int32_t* const jdn);
void jdn_to_gregorian_calendar_date (const int32_t jdn, int32_t* const year, int32_t* const month, int32_t* const day);
void jdn_to_julian_calendar_date    (const int32_t jdn, int32_t* const year, int32_t* const month, int32_t* const day);

//===========================================================================
int32_t calendar_date_from_1582_10_05_to_1582_10_14 (const int32_t year, const int32_t month, const int32_t day);

bool calendar_date_to_jdn (const int32_t year, const int32_t month, const int32_t day, int32_t* const jdn);
void jdn_to_calendar_date (const int32_t jdn, int32_t* const year, int32_t* const month, int32_t* const day);

//===========================================================================
int32_t get_day_of_week_us  (const int32_t jdn);
int32_t get_day_of_week_iso (const int32_t jdn);

//===========================================================================
bool gregorian_calendar_is_leap_year          (const int32_t year);
bool gregorian_calendar_get_last_day_of_month (const int32_t year, const int32_t month, int32_t* const day);
bool gregorian_calendar_is_valid_date         (const int32_t year, const int32_t month, const int32_t day);

//===========================================================================
void epoch_to_jdn         (const int32_t base_epoch_jdn, const int32_t day_number, int32_t* const jdn);
void epoch_to_date        (const int32_t base_epoch_jdn, const int32_t day_number, int32_t* const year, int32_t* const month, int32_t* const day);
void epoch_to_day_of_week (const int32_t base_epoch_jdn, const int32_t day_number, int32_t* const day_of_week);
void epoch_to_time        (const int32_t daysecond_number, int32_t* const hour, int32_t* const minute, int32_t* const second);

//===========================================================================
int32_t epoch_second_get_day_number       (const jdn_time_t epoch_second);
int32_t epoch_second_get_daysecond_number (const jdn_time_t epoch_second);

void epoch_second_to_jdn         (const int32_t base_epoch_jdn, const jdn_time_t epoch_second, int32_t* const jdn);
void epoch_second_to_datetime    (const int32_t base_epoch_jdn, const jdn_time_t epoch_second, int32_t* const year, int32_t* const month, int32_t* const day, int32_t* const day_of_week, int32_t* const hour, int32_t* const minute, int32_t* const second);
void epoch_second_to_date        (const int32_t base_epoch_jdn, const jdn_time_t epoch_second, int32_t* const year, int32_t* const month, int32_t* const day);
void epoch_second_to_day_of_week (const int32_t base_epoch_jdn, const jdn_time_t epoch_second, int32_t* const day_of_week);
void epoch_second_to_time        (const jdn_time_t epoch_second, int32_t* const hour, int32_t* const minute, int32_t* const second);
void datetime_to_epoch_second    (const int32_t year, const int32_t month, const int32_t day, const int32_t hour, const int32_t minute, const int32_t second, const int32_t base_epoch_jdn, jdn_time_t* const epoch_second);

//===========================================================================
int32_t unix_time_get_base_epoch_jdn (void);

void unix_time_to_jdn         (const jdn_time_t t, int32_t* const jdn);
void unix_time_to_datetime    (const jdn_time_t t, int32_t* const year, int32_t* const month, int32_t* const day, int32_t* const day_of_week, int32_t* const hour, int32_t* const minute, int32_t* const second);
void unix_time_to_date        (const jdn_time_t t, int32_t* const year, int32_t* const month, int32_t* const day);
void unix_time_to_day_of_week (const jdn_time_t t, int32_t* const day_of_week);
void unix_time_to_time        (const jdn_time_t t, int32_t* const hour, int32_t* const minute, int32_t* const second);
void datetime_to_unix_time    (const int32_t year, const int32_t month, const int32_t day, const int32_t hour, const int32_t minute, const int32_t second, jdn_time_t* const t);






#endif


