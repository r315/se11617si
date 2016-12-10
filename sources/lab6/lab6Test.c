#include <stdio.h>
#include <string.h>
#include <spi.h>
#include <led.h>
#include <lcd.h>
#include <timer.h>
#include <rtc.h>
#include <button.h>
#include <flash.h>
#include <time.h>

#ifdef _EMU_
const int presistentRtc[]={0,2,0,0,0,0,0,0,0,0,0};
#define SAVED_RTC presistentRtc
#else
#define SAVED_RTC (13*FLASH_SECTOR_SIZE)
#endif

#define BASE_HEX 16
#define MEM_ADDRESS_FORMAT (4<<8) | BASE_HEX
#define MEM_DATA_FORMAT (2<<8) | BASE_HEX
#define MEM_MAX_COLS 8

#define BASE_DEC 10
#define TIME_FORMAT (2<<8) | BASE_DEC

enum RtcFormat{
   RTC_DATETIME,
   RTC_TIME_HHMM,
   RTC_TIME_HHMMSS,
   RTC_DATE, 
   RTC_WDAY  
};
   
enum States{
    IDLE,
    ACERTO,
    ALARM
};

enum AlarmFields{
   HOUR,
   MINUTES,
   SECONDS,
   WEEKDAY
};

struct Alarm{
    struct tm alarm;
    int active;  //seconds
    int timer;
   int state;
};

struct Alarm alarm;
   
void restoreRtc(struct tm *rtc){
   memcpy((void*)rtc, (void*)SAVED_RTC, sizeof(struct tm));
   RTC_SetAlarmValue(rtc);
}

void setTime(struct tm *rtc, uint32_t field, signed char step){
  
   switch(field){
      case HOUR:
         rtc->tm_hour = (rtc->tm_hour + step) % 24;
         if((uint32_t)rtc->tm_hour > 23)
            rtc->tm_hour = 23;
         break;
         
      case MINUTES:
           rtc->tm_min = (rtc->tm_min + step) % 60;
         if((uint32_t)rtc->tm_min > 59)
            rtc->tm_min = 59;
         break;
      case SECONDS:
         rtc->tm_sec = (rtc->tm_sec + step) % 60;
         if((uint32_t)rtc->tm_sec > 59)
            rtc->tm_sec = 59;
         break;
         
      case WEEKDAY:
         rtc->tm_wday = (rtc->tm_wday + step) % 7;
         if((uint32_t)rtc->tm_wday > 6)
            rtc->tm_wday = 6;
         break;
      
   }
   
}

void PRINT_RtcTime(struct tm* rtc, uint8_t format){
    LCD_WriteInt(rtc->tm_hour, TIME_FORMAT);
    LCD_WriteChar(':');
    LCD_WriteInt(rtc->tm_min, TIME_FORMAT);
    if(format == RTC_TIME_HHMMSS){
        LCD_WriteChar(':');
        LCD_WriteInt(rtc->tm_sec, TIME_FORMAT);
    }
}

const char wdays[7][4]={"mon","tue","wed","thu","fri","sat","sun"};
void PRINT_Rtc(struct tm* rtc, uint8_t data){   
   switch(data){      
      case RTC_DATETIME:
         PRINT_RtcTime(rtc,RTC_TIME_HHMM);
         LCD_WriteChar(' ');
                  
      case RTC_DATE:
         LCD_WriteInt(rtc->tm_mday, TIME_FORMAT);
         LCD_WriteChar('-');
         LCD_WriteInt(rtc->tm_mon, TIME_FORMAT);
         LCD_WriteChar('-');
         LCD_WriteInt(rtc->tm_year, (4<<8) | BASE_DEC);
         break;     
         
      case RTC_TIME_HHMM:
         PRINT_RtcTime(rtc, RTC_TIME_HHMM);
         break;
      
      case RTC_TIME_HHMMSS:
         PRINT_RtcTime(rtc,RTC_TIME_HHMMSS);        
         break;      
         
      case RTC_WDAY:         
         LCD_WriteString((char*)&wdays[rtc->tm_wday][0]);         
         break;      
   }   
}

void PRINT_Mem(void *start, uint32_t len){
uint32_t i;   

    LCD_Goto(0,48);
    while(len){
        LCD_WriteInt(*((uint32_t*)&start), MEM_ADDRESS_FORMAT);
        LCD_WriteChar(':');
        for(i=0; i < MEM_MAX_COLS && len > 0;i++){
            LCD_WriteChar(' ');
            LCD_WriteInt(*((uint8_t*)(start++)), MEM_DATA_FORMAT);
            len--;            
        }       
        //LCD_NewLine();
    }
}

int acerto(struct Alarm *alarm, int b){
static uint8_t state = 0;
signed char step = 0;
uint8_t update = 0;



   if(b == BUTTON_S){
      state++;
      LCD_Goto(0,16);
      LCD_WriteString("             ");
   }
   
   if(b == BUTTON_F){      
      state = 0;
      return 0;
   }
   
   if(b == BUTTON_L)
      step = -1;
   else if(b == BUTTON_R)
      step =  1;      

   switch(state){
      case 0:     //horas
         setTime(&alarm->alarm, HOUR, step);         
         LCD_Goto(8,16);
         LCD_WriteChar('^');
         update = 1;
         break;   
         
      case 1:     //minutos         
         setTime(&alarm->alarm, MINUTES, step);         
         LCD_Goto(32,16);
         LCD_WriteChar('^');
         update = 1;
         break;
         
      case 2:     //dia semana         
         setTime(&alarm->alarm, WEEKDAY, step);         
         LCD_Goto(58,16);
         LCD_WriteChar('^');
         update = 1;
         break;
      
      case 3:
         RTC_SetAlarmValue(&alarm->alarm);         
         state = FLASH_WriteData((void*)SAVED_RTC,(void*)&alarm->alarm,32);
         if(state){
            LCD_WriteString(" Fail: ");
            LCD_WriteInt(state,10);
         }
         state = 0;
         return 0;
         
      default:
         break;
      
   }
   
   if(update){
       LCD_Goto(0,0);
       PRINT_Rtc(&alarm->alarm, RTC_TIME_HHMM);                
       LCD_WriteChar(' ');
       PRINT_Rtc(&alarm->alarm, RTC_WDAY);      
       LCD_WriteString("    ");
   }      
   return 1;
}


int play_alarm(struct Alarm *almr){
    if(almr->active){
        if(TIMER0_Elapse(almr->timer) > 500){
            LCD_Goto(0,48);
            if(!almr->state){
                LCD_WriteString("Alarme!");
                almr->state = 1;
            }else{
                LCD_WriteString("       ");
                almr->state = 0;
                almr->active--;            
            }
            almr->timer = TIMER0_GetValue();
        }
      return 1;
    }
    return 0;
}

void PRINT_RtcInfoTime(struct tm *time){
    LCD_Goto(0,0);
    LCD_WriteString("Rtc: ");
    RTC_GetValue(time);
    PRINT_Rtc(time,RTC_TIME_HHMMSS);
}

void PRINT_RtcInfoAlarm(struct tm *alarm){    
    LCD_Goto(0,16);
    LCD_WriteString("Alm: ");
    RTC_GetAlarmValue(alarm);
    PRINT_Rtc(alarm,RTC_TIME_HHMMSS);
}


int main(int argc, char *argv[]){
struct tm rtc;
int main_state  = IDLE; 
int button;    
    
    //PLL_Init();   //if used must be the first peripheral to initialize
    
    TIMER0_Init(MS_IN_1S);

    LED_Init(LED, LED_ON);

    BUTTON_Init();

    SPI_Init(1000, SPI_8BIT); // lcd must be initialyze with low speed and 8bit transfers

    LCD_Init();

    SPI_Init(SPI_MAX_FREQ, SPI_16BIT); //after init use full speed

    LCD_Clear(RGB(6,2,4));

    LCD_SetColors(GREEN,BLACK);
    
    memset((void*)&rtc, 0 , sizeof(struct tm));	// initialize rtc structures
   
    restoreRtc(&alarm.alarm);    //get stored alarm from flash
    
    RTC_Init(&rtc);
    
    RTC_DeactivateAlarm(RTC_AMR_OFF);
    
    RTC_SetAlarmValue(&alarm.alarm);
     
    RTC_ActivateAlarm(RTC_AMR_MIN);
   
    PRINT_RtcInfoTime(&rtc);
   
    PRINT_RtcInfoAlarm(&alarm.alarm);

    while(loop()){ 
  
    //Check Events      
    if(BUTTON_GetButtonEvents() == BUTTON_PRESSED){
        button = BUTTON_GetButton();        
    }
    else
        button = 0;
      
      
    //process main state machine        
    switch(main_state){         
        case ACERTO:
            if(!acerto(&alarm, button)){
                PRINT_RtcInfoTime(&rtc);   
                PRINT_RtcInfoAlarm(&alarm.alarm);
                RTC_ActivateAlarm(RTC_AMR_MIN);
                main_state = IDLE;                  
            }
            break;
         
         case ALARM:   
            PRINT_RtcInfoTime(&rtc);
            if(!play_alarm(&alarm)){                  
                RTC_ClearAlarm();
                main_state = IDLE;
            }               
            break;
            
         case IDLE: 
            PRINT_RtcInfoTime(&rtc);
            if(RTC_CheckAlarm()){
                alarm.active = 10;
                main_state = ALARM;
                break;
            }
               
            if(button == BUTTON_S){
                LCD_Goto(0,16);
                LCD_WriteString("             ");
                main_state = ACERTO;                  
                break;
            }              
               
            if(button == BUTTON_L){
                LCD_Goto(0,32);
                LCD_WriteInt(RTC->AMR,2);
                break;
            }
                
            if(button == BUTTON_R){    
                PRINT_Mem((void*)SAVED_RTC,32);
                break;
            }
                  
               
         default:   
               break;      
      }
    }
    return 0;
}
 
