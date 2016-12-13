#include <button.h>

#include "system.h"
#include "save.h"
#include "config.h"
#include "space.h"
#include "idle.h"


typedef enum Mstates{
  IDLE,
  CONFIG,  
  GAME,
  SAVE    
}State;

int dummy;

State switchTo(State newState){
    switch(newState){
        case IDLE: popIdle(); break;
        case CONFIG: break;
        case GAME: popSpace();break;
        case SAVE: break;
    }
    return newState;
}


int main(void){
State state;
uint32_t button;    
    
    SYS_Init();    
    
    state = switchTo(IDLE);
    
    while(loop){
        
        //Check Events      
        BUTTON_Hit();
        
        if(BUTTON_GetButtonEvents() == BUTTON_PRESSED){
           button = BUTTON_GetButton();            
        }
        else
           button = BUTTON_EMPTY;      
           
        if(BUTTON_GetButtonEvents() != BUTTON_EMPTY){
            printf("State %u\n",BUTTON_GetButtonEvents());
        }
         
        //main state machine        
        switch(state){
            case IDLE: 
                if(button == BUTTON_F){                   
                    state = switchTo(GAME);
                    break;
                }
                
                if(button == BUTTON_S){
                    loadGame(&dummy,1);
                    state = switchTo(GAME);
                    break;
                }
                
                if(button == (BUTTON_F| BUTTON_R)){
                    if(BUTTON_GetButtonEvents() == BUTTON_HOLD){
                        state = switchTo(CONFIG);
                        break;
                    }
                }
                                                
                idle();                
                break;
                
            case CONFIG: 
                if(!config(button)){
                    state = switchTo(IDLE);
                }
                break;
                
            case GAME: 
                if(button == BUTTON_S){
                    state = switchTo(SAVE);
                    break;
                }
                space(button);
                break;    
                        
            case SAVE:
                if(!saveGame(&dummy,1)){
                    state = switchTo(IDLE);
                }
                break;   
        }        
    }
return 0;
}
