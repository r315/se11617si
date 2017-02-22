/**
* @file		gpio.h
* @brief	common functions for io port access
* @version	1.0
* @date		30 Out. 2016
* @author	Hugo Reis
**********************************************************************/

#ifndef _GPIO_H_
#define _GPIO_H_

#include <stdint.h>
#include <lpc2106.h>
/*
#define GPIO_Set(n) GPIO0->SET = (1 << n)  // change the state of only one pin
#define GPIO_Clr(n) GPIO0->CLR = (1 << n)  // by giving his number

#define GPIO_SetN(x) GPIO0->SET = x        // change selected pins
#define GPIO_ClrN(x) GPIO0->CLR = x        // by giving the pretended bts

#define GPIO_Write(x) GPIO0->PIN = x		//change all pins
#define GPIO_Read()   GPIO0->PIN

#define GPIO_SetOutput(n) GPIO0->DIR |= (1 << n) //affect single pin
#define GPIO_SetInput(n)  GPIO0->DIR &= ~(1 << n)

#define GPIO_SetOutputN(n) GPIO0->DIR |= n //affect multiple pin

#define GPIO_SetDir(n)  GPIO0->DIR = x //affect all pins
*/

#define GPIO_Set(n) FIO0->SET = (1 << n)        // change the state of only
#define GPIO_Clr(n) FIO0->CLR = (1 << n)        // one pin
#define GPIO_SetOutput(n) FIO0->DIR |= (1 << n) //affect single pin
#define GPIO_SetInput(n)  FIO0->DIR &= ~(1 << n)

#define GPIO_SetN(x) FIO0->SET = x              //change selected pins
#define GPIO_ClrN(x) FIO0->CLR = x
#define GPIO_Write(x) FIO0->PIN = x             //change all pins
#define GPIO_Read() FIO0->PIN
#define GPIO_SetDir(n)  FIO0->DIR = x           //affect all pins
#define GPIO_SetOutputN(n) FIO0->DIR |= n       //affect multiple pin
#define GPIO_SetInputN(n)  FIO0->DIR &= ~n      //affect multiple pin

/**
 * @brief inicializa um pino com direcao e estado
 * */
void GPIO_Init(uint8_t bit, uint8_t dir, uint8_t state);

/**
 * @brief muda o estado do pino
 * */
void GPIO_SetPin(uint8_t bit, uint8_t state);

/**
 * @brief obtem o estado do pino
 * */
uint8_t GPIO_GetPin(uint8_t bit);
#endif

