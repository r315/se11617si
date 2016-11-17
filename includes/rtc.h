/**
* @file		rtc.h
* @brief	Contains the RTC API header.
*     		
* @version	1.0
* @date		10 Nov. 2016
* @author	Hugo Reis
**********************************************************************/

#ifndef _rtc_h_
#define _rtc_h_

#include <stdint.h>
#include <time.h>
#include <lpc2106.h>

#define RTC_ON     (1<<9)
#define RTC_CLKEN  (1<<0)
#define RTC_CTCRST (1<<2)
#define RTC_RTCALF (1<<1)

#define RTC_PowerUp() SC->PCONP |= RTC_ON

#define RTC_DIVIDER 32768

#define RTC_ALARMS_OFF 0xFF

/** 
* @brief Faz a iniciação do sistema para permitir o acesso ao periférico RTC.
*        O RTC é iniciado com os valores do parâmetro.
**/
void RTC_Init(struct tm *dateTime); 	 

/** 
* @brief Devolve em dateTime o valor corrente do RTC.
**/
void RTC_GetValue(struct tm *dateTime);

/** 
* @brief Realiza a atualização do RTC com os valores do parâmetro dateTime.
**/
void RTC_SetValue(struct tm *dateTime);

/** 
* @brief Devolve em dateTime o valor corrente do alarme do RTC.
**/
void RTC_GetAlarmValue(struct tm *dateTime);

/** 
* @brief Realiza a atualização do alarme do RTC com os valores do parâmetro dateTime.
**/
void RTC_SetAlarmValue(struct tm *dateTime);

/** 
* @brief Activa um alarme
**/
void RTC_ActivateAlarm(uint32_t alarm);

/** 
* @brief Desactiva um alarme
**/
void RTC_DeactivateAlarm(uint32_t alarm);

/** 
* @brief Verifica se algum alarme foi gerado.
* @return 1 = true
**/
uint32_t RTC_HasAlarms(void);

/** 
* @brief clears any activated alarm
**/
void RTC_ClearAlarms(void);

#endif

