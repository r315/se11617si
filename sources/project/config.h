#ifndef _config_h_
#define _config_h_

enum TimeFields{
   HOUR,
   MINUTES,   
   WEEKDAY,   
   MDAY,
   MONTH,
   YEAR   
};

enum RtcFormat{
   RTC_DATETIME,
   RTC_TIME_HHMM,
   RTC_TIME_HHMMSS,
   RTC_DATE, 
   RTC_WDAY  
};

void popConfig(void *ptr);
int config(int b);
#endif
