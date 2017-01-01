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

typedef struct{
	uint32_t cur;
	uint32_t last;
	uint32_t counter;
	uint32_t events;
    uint32_t htime;
}BUTTON_Controller;

#define BUTTON_DEFAULT_HOLD_TIME 2000   //2 seconds

enum Benvent{
    BUTTON_EMPTY = 0,
    BUTTON_PRESSED,
    BUTTON_TIMING,
    BUTTON_HOLD,
    BUTTON_RELEASED	
}Bstate;


/**
* @brief Button connections
*		P0.11  Left
*		P0.12  Fire
*		P0.13  Right
*       P0.15  Save
**/
#define BUTTON_L (1<<11)
#define BUTTON_R (1<<13)
#define BUTTON_F (1<<12)
#define BUTTON_S (1<<15)

#define BUTTON_MASK (BUTTON_L | BUTTON_R | BUTTON_F | BUTTON_S)

#if defined(_EMU_)
#define loop BUTTON_GetEvents() != 256 //SDL_QUIT
#else
#define loop 1
#endif


/**
* @brief Faz a iniciação do sistema para permitir o acesso aos botões
* @param mask bitmap com os bits correspondentes aos pinos ligados nos botões
**/
void BUTTON_Init(int ht);

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
* @brief Devolve o código (bitmap) do estado do botão: 
* 		 pressionado (transição),
*        libertado (transição),
*        repetição (mantido pressionado)
**/
int BUTTON_GetEvents(void);

/**
 * @brief Devolve o codigo (bitmap) da tecla corrente
 *        EMPTY se nenhuma tecla pressionada
 **/
int BUTTON_GetButton(void); 

/*
* @brief configura o tempo minimo para que uma tecla 
*        seja considerada como mantida oressionada 
**/
void BUTTON_SetHoldTime(int t);
#endif

