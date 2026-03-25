# Julian Day Number

## 개요

이 라이브러리는 Julian Day Number(JDN) 및 다양한 달력 변환, 날짜 계산, Unix Time 변환 등을 위한 C 함수들을 제공합니다.

그레고리력, 율리우스력, 릴리안 데이트, Modified/Truncated JD, Unix Time 등 다양한 날짜 시스템 간 변환을 지원합니다.

---


## 개발 동기

{`년`, `월`, `일`}을 int32_t값으로 편하게 처리하기 위해서는

JDN이라는 단위로 변환하여 처리하면 사용하기 쉽습니다.

일 단위 2^32-1범위 => -2,147,483,648일 ~ +2,147,483,647일 = 약-5,883,516.8년 ~ 약5,883,516.8년

rtc나 log관련 시간처리 할 때 용이합니다.

---

## 주요 타입

- `jdn_time_t`: 날짜/시간 계산에 사용되는 정수형(기본: int64_t)

- 가급적 64비트용으로 사용하세요.

---

## 주요 함수 목록 및 설명

### JDN 변환 함수

- `void jdn_to_modified_jdn(const int32_t jdn, int32_t* const modified_jdn);`
  - JDN → Modified JD 변환
- `void jdn_to_truncated_jd(const int32_t jdn, int32_t* const truncated_jd);`
  - JDN → Truncated JD 변환
- `void jdn_to_lilian_date(const int32_t jdn, int32_t* const lilian_date);`
  - JDN → Lilian Date 변환
- `void jdn_to_unix_time_day_count(const int32_t jdn, int32_t* const unix_time_day_count);`
  - JDN → Unix Epoch 일수 변환

### 달력 변환 함수

- `void gregorian_calendar_date_to_jdn(const int32_t year, const int32_t month, const int32_t day, int32_t* const jdn);`
  - 그레고리력 → JDN
- `void julian_calendar_date_to_jdn(const int32_t year, const int32_t month, const int32_t day, int32_t* const jdn);`
  - 율리우스력 → JDN
- `void jdn_to_gregorian_calendar_date(const int32_t jdn, int32_t* const year, int32_t* const month, int32_t* const day);`
  - JDN → 그레고리력
- `void jdn_to_julian_calendar_date(const int32_t jdn, int32_t* const year, int32_t* const month, int32_t* const day);`
  - JDN → 율리우스력

### 날짜 유효성/윤년/요일

- `bool gregorian_calendar_is_leap_year(const int32_t year);`
  - 윤년 판별(그레고리력)
- `bool gregorian_calendar_is_valid_date(const int32_t year, const int32_t month, const int32_t day);`
  - 날짜 유효성 검사(그레고리력)
- `int32_t get_day_of_week_us(const int32_t jdn);`
  - 미국식 요일(0=일~6=토)
- `int32_t get_day_of_week_iso(const int32_t jdn);`
  - ISO 요일(1=월~7=일)

### Epoch/Unix Time 변환

- `void epoch_to_jdn(const int32_t base_epoch_jdn, const int32_t day_number, int32_t* const jdn);`
- `void epoch_to_date(const int32_t base_epoch_jdn, const int32_t day_number, int32_t* const year, int32_t* const month, int32_t* const day);`
- `void unix_time_to_jdn(const jdn_time_t t, int32_t* const jdn);`
- `void unix_time_to_datetime(const jdn_time_t t, int32_t* const year, ...);`
- `void datetime_to_unix_time(const int32_t year, ... , jdn_time_t* const t);`

### 기타

- `int32_t calendar_date_from_1582_10_05_to_1582_10_14(const int32_t year, const int32_t month, const int32_t day);`
  - 1582년 10월 5~14일(달력 개정 결번 구간) 판별
- `int32_t epoch_second_get_day_number(const jdn_time_t epoch_second);`
  - Epoch 초 → 경과 일수
- `int32_t epoch_second_get_daysecond_number(const jdn_time_t epoch_second);`
  - Epoch 초 → 하루 내 경과 초

---

## 사용 예시

```c
int32_t jdn, year, month, day;
gregorian_calendar_date_to_jdn(2024, 3, 25, &jdn); // 2024-03-25 → JDN
jdn_to_gregorian_calendar_date(jdn, &year, &month, &day); // JDN → 2024-03-25
```

---

## 참고

- JDN: -4712/01/01(BC 4713년 1월 1일) = 0
- Modified JD: JD − 2400000.5 (1858-11-17)
- Truncated JD: JD − 2440000.5 (1968-05-24)
- Lilian Date: JD − 2299159.5 (1582-10-15)
- Unix Epoch: JD − 2440587.5 (1970-01-01)

---

## 구현/코딩 스타일

- 모든 입력 파라미터에 const 적용(값/포인터)
- C99 표준, int32_t 등 고정폭 타입 사용
- 함수별 doxygen 스타일 주석
- 윤년, 요일, 유효성 등 달력 계산 보조 함수 제공
