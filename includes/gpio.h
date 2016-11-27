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
#define GPIO_Set(n) FIO0->SET = (1 << n)  // change the state of only
#define GPIO_Clr(n) FIO0->CLR = (1 << n)  // one pin

#define GPIO_SetN(x) FIO0->SET = x			//change selected pins
#define GPIO_ClrN(x) FIO0->CLR = x

#define GPIO_Write(x) FIO0->PIN = x		//change all pins
#define GPIO_Read() FIO0->PIN

#define GPIO_SetOutput(n) FIO0->DIR |= (1 << n) //affect single pin
#define GPIO_SetInput(n)  FIO0->DIR &= ~(1 << n)

#define GPIO_SetOutputN(n) FIO0->DIR |= n //affect multiple pin

#define GPIO_SetDir(n)  FIO0->DIR = x //affect all pins
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



#endif

