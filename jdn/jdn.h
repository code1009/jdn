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
#define jdn_time_t int64_t
//#define jdn_time_t int32_t
//#define jdn_timt_t time_t
//#define jdn_time_t __time64_t
//#define jdn_time_t __time32_t





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void jdn_to_modified_jdn        (int32_t jdn, int32_t* modified_jdn);
void jdn_to_truncated_jd        (int32_t jdn, int32_t* truncated_jd);
void jdn_to_lilian_date         (int32_t jdn, int32_t* lilian_date);
void jdn_to_unix_time_day_count (int32_t jdn, int32_t* unix_time_day_count);

//===========================================================================
void gregorian_calendar_date_to_jdn (int32_t year, int32_t month, int32_t day, int32_t* jdn);
void julian_calendar_date_to_jdn    (int32_t year, int32_t month, int32_t day, int32_t* jdn);
void jdn_to_gregorian_calendar_date (int32_t jdn, int32_t* year, int32_t* month, int32_t* day);
void jdn_to_julian_calendar_date    (int32_t jdn, int32_t* year, int32_t* month, int32_t* day);

//===========================================================================
int32_t  calendar_date_from_1582_10_05_to_1582_10_14 (int32_t year, int32_t month, int32_t day);

bool calendar_date_to_jdn (int32_t year, int32_t month, int32_t day, int32_t* jdn);
void jdn_to_calendar_date (int32_t jdn, int32_t* year, int32_t* month, int32_t* day);

//===========================================================================
int32_t us_get_day_of_week  (int32_t jdn);
int32_t iso_get_day_of_week (int32_t jdn);

//===========================================================================
bool gregorian_calendar_is_leap_year          (int32_t year);
bool gregorian_calendar_get_last_day_of_month (int32_t year, int32_t month, int32_t* day);
bool gregorian_calendar_is_valid_date         (int32_t year, int32_t month, int32_t day);

//===========================================================================
void epoch_to_jdn         (int32_t base_epoch_jdn, int32_t day_number, int32_t* jdn);
void epoch_to_date        (int32_t base_epoch_jdn, int32_t day_number, int32_t* year, int32_t* month, int32_t* day);
void epoch_to_day_of_week (int32_t base_epoch_jdn, int32_t day_number, int32_t* day_of_week);
void epoch_to_time        (                        int32_t daysecond_number, int32_t* hour, int32_t* minute, int32_t* second);

//===========================================================================
int32_t epoch_second_get_day_number       (jdn_time_t epoch_second);
int32_t epoch_second_get_daysecond_number (jdn_time_t epoch_second);

void epoch_second_to_jdn         (int32_t base_epoch_jdn, jdn_time_t epoch_second, int32_t* jdn);
void epoch_second_to_datetime    (int32_t base_epoch_jdn, jdn_time_t epoch_second, int32_t* year, int32_t* month, int32_t* day, int32_t* day_of_week, int32_t* hour, int32_t* minute, int32_t* second);
void epoch_second_to_date        (int32_t base_epoch_jdn, jdn_time_t epoch_second, int32_t* year, int32_t* month, int32_t* day);
void epoch_second_to_day_of_week (int32_t base_epoch_jdn, jdn_time_t epoch_second, int32_t* day_of_week);
void epoch_second_to_time        (                        jdn_time_t epoch_second, int32_t* hour, int32_t* minute, int32_t* second);
void datetime_to_epoch_second    (int32_t year, int32_t month, int32_t day, int32_t hour, int32_t minute, int32_t second, int32_t base_epoch_jdn, jdn_time_t* epoch_second);

//===========================================================================
int32_t unix_time_get_base_epoch_jdn (void);

void unix_time_to_jdn         (jdn_time_t t, int32_t* jdn);
void unix_time_to_datetime    (jdn_time_t t, int32_t* year, int32_t* month, int32_t* day, int32_t* day_of_week, int32_t* hour, int32_t* minute, int32_t* second);
void unix_time_to_date        (jdn_time_t t, int32_t* year, int32_t* month, int32_t* day);
void unix_time_to_day_of_week (jdn_time_t t, int32_t* day_of_week);
void unix_time_to_time        (jdn_time_t t, int32_t* hour, int32_t* minute, int32_t* second);
void datetime_to_unix_time    (int32_t year, int32_t month, int32_t day, int32_t hour, int32_t minute, int32_t second, jdn_time_t* t);






#endif


