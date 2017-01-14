/**
* @file		timer.h
* @brief	Contains API header for controlling timer 0.
*     		
* @version	1.0
* @date		3 Nov. 2016
* @author	Hugo Reis
**********************************************************************/

#ifndef _timer_h_
#define _timer_h_

#include <stdint.h>
#include <lpc2106.h>

#define TIMER0_ON 	(1<<1)
#define TIMER1_ON	(1<<2)

#define TIMER_CR	(1<<1)
#define TIMER_CE	(1<<0)

#define MS_IN_1S 1000

/**
* @brief Faz a iniciação do sistema para permitir o acesso ao periférico Timer 0. O
*	     timer deve ser iniciado em modo continuo e à frequência (Hz) indicada no parâmetro.
*/
void TIMER0_Init(unsigned int frequency);

/**
* @brief Devolve o valor corrente do Timer 0 em unidades de contagem (ticks).
**/
unsigned int TIMER0_GetValue(void);

/**
* @brief Devolve o valor, em unidades de contagem (ticks), desde o lastRead até o
*        tempo corrente.
**/
unsigned int TIMER0_Elapse(unsigned int lastRead);

/**
* @brief Converte contagem de ticks em milisegundos
**/
unsigned int TIMER0_TicksToMs(unsigned int ticks);

/**
* @brief efectua uma pausa de ms passado como parametro
**/

void TIMER0_DelayMs(unsigned int ms);

#endif
