#include <time.h>
#include <button.h>
#include <lcd.h>
#include "system.h"
#include "save.h"
#include "config.h"
#include "space.h"
#include "idle.h"

#include <spi.h>


typedef enum Mstates{
  IDLE,
  CONFIG,  
  GAME,
  SAVE    
}State;

typedef struct _SaveData{
    uint32_t topscores[MAX_TOP_SCORES];    
    uint8_t checksum;
    GameData spaceInvaders;    
    struct tm rtc;
}SaveData;

SaveData saveddata;


State switchTo(State newState){
    switch(newState){
        case IDLE:   popIdle(saveddata.topscores); break;
        case CONFIG: popConfig(&saveddata.rtc); break;
        case GAME:   popSpace(&saveddata.spaceInvaders);break;
        case SAVE:   break;
    }
    return newState;
}

void saveTopScore(uint32_t score, uint32_t *scorestab){
uint8_t n;
uint32_t *p1,*p2;
    for(n = 0; n < MAX_TOP_SCORES; n++){
        if(score > scorestab[n]){
            p1 = &scorestab[MAX_TOP_SCORES-2];
            p2 = &scorestab[MAX_TOP_SCORES-1];
            while( (p2) != &scorestab[n]){
                *p2 = *p1;
                p1 -= 1;
                p2 -= 1;
            }
            scorestab[n] = score;
            return;
        }            
    }
}

int main(void){
State state;
uint32_t button,res;
    
    state = switchTo(IDLE);
    
    while(loop){
        
        //Check Events      
        BUTTON_Hit();
        
        if(BUTTON_GetEvents() == BUTTON_PRESSED ||
           BUTTON_GetEvents() == BUTTON_HOLD){
           button = BUTTON_GetButton();            
        }
        else
           button = BUTTON_EMPTY;      
           
        //if(BUTTON_GetEvents() != BUTTON_EMPTY){
        //   printf("Button %u State %u\n",button, BUTTON_GetEvents());
        //}
         
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
                
                if(button == (BUTTON_L | BUTTON_R)){
                    if(BUTTON_GetEvents() == BUTTON_HOLD){
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
