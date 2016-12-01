#include <string.h>
#include <SDL2/SDL.h> 
#include <time.h>
#include <button.h>

#if defined(DBG)
#define DBG(x) printf(x)
#else
#define DBG  printf
#endif

//---------------------------------------------------------------------------
void SPI_Init(int frequency, int bitData){ }
void SPI_BeginTransfer(int csBitId){}
void SPI_EndTransfer(int csBitId){}
void SPI_Transfer(unsigned short *txBuffer, unsigned short *rxBuffer, int lenght){}
uint16_t SPI_Send(uint16_t data){ return 0xFFFF;}

//---------------------------------------------------------------------------
static int __led_state;
void LED_Init(int pinId, int state){__led_state = state;}
int LED_GetState(void){return __led_state;}
void LED_SetState(int state){ __led_state = state;}

//---------------------------------------------------------------------------
static struct tm __rtc;
void RTC_SetValue(struct tm *dateTime){	
	__rtc.tm_sec = dateTime->tm_sec % 60;
	__rtc.tm_min = dateTime->tm_min % 60;
	__rtc.tm_hour = dateTime->tm_hour % 24;
	__rtc.tm_mday = (dateTime->tm_mday > 1 && dateTime->tm_mday < 32)? dateTime->tm_mday : 1;
	__rtc.tm_mon = (dateTime->tm_mon > 1 && dateTime->tm_mon < 13)? dateTime->tm_mon : 1;
	__rtc.tm_wday = (dateTime->tm_wday > 1 && dateTime->tm_wday < 7)? dateTime->tm_wday : 0;
	__rtc.tm_year = (dateTime->tm_year > 0 && dateTime->tm_year < 4096)? dateTime->tm_year : 1900;
	__rtc.tm_yday = (dateTime->tm_yday > 1 && dateTime->tm_yday < 366)? dateTime->tm_yday : 1;	
}
void RTC_Init(struct tm *dateTime){ RTC_SetValue(dateTime);}

void RTC_GetValue(struct tm *dateTime){
time_t rawtime;
   time ( &rawtime );
   memcpy((uint8_t *)dateTime, (uint8_t *)localtime(&rawtime), sizeof(struct tm));
}

void RTC_GetAlarmValue(struct tm *dateTime){
	
}

void RTC_SetAlarmValue(struct tm *dateTime){	
}

uint32_t RTC_HasAlarms(void){ return 0;}

void RTC_ClearAlarms(void){}

void RTC_ActivateAlarm(uint32_t alarm){}

void RTC_DeactivateAlarm(uint32_t alarm){}

//---------------------------------------------------------------------------
int __button;

int BUTTON_Filter(const Uint8 *ink){
        __button= 0;
        if(ink[SDL_SCANCODE_1])  __button |= BUTTON_L;
        if(ink[SDL_SCANCODE_2])  __button |= BUTTON_F;
        if(ink[SDL_SCANCODE_3])  __button |= BUTTON_R;
        if(ink[SDL_SCANCODE_4])  __button |= BUTTON_S;
        if(ink[SDL_SCANCODE_Q])  __button = SDLK_q;
        DBG("key pressed %u\n",__button);
return __button;
}

void BUTTON_Init(void){}

int BUTTON_Hit(void){
static SDL_Event event;
    if(SDL_PollEvent(&event)){
        if(event.type == SDL_KEYDOWN){
            return BUTTON_Filter(SDL_GetKeyboardState(NULL));
        }
    }   
    return 0;
}
				   
int BUTTON_Read(void){
    while(!BUTTON_Hit());
    return __button;
}

int BUTTON_GetButtonsEvents(void){
    return __button;
}

//---------------------------------------------------------------------------
unsigned int FLASH_EraseSectors(unsigned int startSector, unsigned int endSector){
    return 0;
}

unsigned int FLASH_WriteBlock( void *dstAddr, void *srcAddr, unsigned int size){
    return 0;
}
unsigned int FLASH_WriteData(void *dstAddr, void *srcAddr, unsigned int size){
    return 0;
}
unsigned int FLASH_VerifyData(void *dstAddr, void *srcAddr, unsigned int size){
    return 0;
}
//---------------------------------------------------------------------------
void TIMER0_Init(unsigned int frequency){}

unsigned int TIMER0_GetValue(void){
	return SDL_GetTicks();
}

unsigned int TIMER0_Elapse(unsigned int lastRead){
	return SDL_GetTicks()-lastRead;
}

unsigned int TicksToMs(unsigned int ticks){
return  ticks;
}

void TIMER0_DelayMs(unsigned int ms){
    SDL_Delay(ms);
}







