/**
* @file		buttons.h
* @brief	Contains API header for reading buttons.
*     		
* @version	1.0
* @date		3 Nov. 2016
* @author	Hugo Reis
**********************************************************************/

#ifndef _button_h_
#define _button_h_

#include <stdint.h>
#include <lpc2106.h>

typedef struct{
	uint32_t cur;
	uint32_t last;
	uint32_t timer;
	uint32_t events;
	uint32_t mask;
}BUTTON_Controller;


#define BUTTON_HOLD_TIME 2000   //2 seconds

#define BUTTON_EMPTY    0
#define BUTTON_PRESSED  1 
#define BUTTON_RELEASED 2
#define BUTTON_HOLD     3

#define BUTTON_L (1<<11)
#define BUTTON_R (1<<13)
#define BUTTON_F (1<<12)
#define BUTTON_S (1<<15)

#define BUTTON_MASK (BUTTON_L | BUTTON_R | BUTTON_F | BUTTON_S)


/**
* @brief Faz a iniciação do sistema para permitir o acesso aos botões
* @param mask bitmap com os bits correspondentes aos pinos ligados nos botões
**/
void BUTTON_Init(uint32_t mask);

/**
* @brief Devolve o codigo (bitmap) do botão pressionado ou 0 no caso de não existir 
*        qualquer botão pressionado. Não é bloqueante.
**/
int BUTTON_Hit(void);

/**
* @brief Devolve o código (bitmap) do botão pressionado. É bloqueante.
*
**/						   
int BUTTON_Read(void);

/**
* @brief Devolve o código (bitmap) do estado do botão: pressionado (transição),
*        libertado (transição), repetição (mantém o estado anterior)
**/
int BUTTON_GetButtonsEvents(void);

#endif
