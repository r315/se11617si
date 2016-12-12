#include "system.h"
#include <button.h>


typedef enum Mstates{
  IDLE,
  CONFIG,  
  GAME,
  SAVE    
}State;

int config(int b);
int spcinv(int b);
int saveToFlash(void);

int main(void){
State state = IDLE;
uint32_t button;    
    
    SYS_Init();
    
    
    while(loop){
        
        //Check Events      
        BUTTON_Hit();
        
        if(BUTTON_GetButtonEvents() == BUTTON_PRESSED){
            button = BUTTON_GetButton();        
        }
        else
            button = 0;      
                
        switch(state){
            case IDLE: 
                if(button == BUTTON_F){                   
                    state = GAME;
                    break;
                }
                
                if(button == BUTTON_S){
                    loadSavedGame();
                    state = GAME;
                    break;
                }
                
                if(button == (BUTTON_F| BUTTON_R)){
                    if(BUTTON_GetButtonEvents() == BUTTON_HOLD){
                        state = CONFIG;
                        break;
                    }
                }                
                break;
                
            case CONFIG: 
                if(!config(button)){
                    state = IDLE;
                }
                break;
                
            case GAME: 
                if(button == BUTTON_S){
                    state = SAVE;
                }
                spcinv(button);
                break;    
                        
            case SAVE:
                if(!saveToFlash()){
                    state = IDLE;
                }
                break;   
        }        
    }

}
