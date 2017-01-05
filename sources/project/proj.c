#include <string.h>
#include <time.h>
#include <button.h>
#include <lcd.h>
#include <led.h>
#include <spi.h>
#include <flash.h>
#include <timer.h>
#include <rtc.h>
#include "proj.h"
#include "system.h"
#include "save.h"
#include "config.h"
#include "space.h"
#include "idle.h"


//---------------------------------------------------------------
// Constants and macros
//---------------------------------------------------------------


//---------------------------------------------------------------
// Structures and global variables
//---------------------------------------------------------------
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

//---------------------------------------------------------------
// Functions
//---------------------------------------------------------------

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

uint8_t generateChecksum(void *data, uint32_t size){
uint8_t sum = 0;
    while(size--){
        //printf("data %u\n",*((uint8_t*)data));
        sum += *((uint8_t*)data++);
    } 
    sum = 0xFF - sum;
    //printf("Checksum %u\n", sum);
    return sum;
}

uint8_t checksumData(void *data, uint32_t size, uint8_t checksum){
uint8_t sum = 0;
    while(size--){     
        sum += *((uint8_t*)data++);        
    }    
    //printf("Sum %u\n", sum);
    return (uint8_t)(sum + (checksum + 1));
}

uint32_t strlenInPixels(char *str){
uint8_t count = 0;
    while(*str++)
        count++;
    return count * 8;    
}

void displaySaveResult(uint32_t res){
char *msg;    

    switch(res){
        case CMD_SUCESS: 
            msg = "Save ok"; break;
            
        case SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION : 
            LCD_WriteString("Sector Not Ready");break;
            
        case INVALID_SECTOR: 
            msg = "Invalid Sector";break;
            
        case SRC_ADDR_ERROR: 
            msg = "Invalid Start Address";break;
        
        case DST_ADDR_ERROR: 
            msg = "Invalid Destination Address";break;
        
        case COUNT_ERROR: 
            msg = "Count error";break;    
            
        case BUSY: 
            msg = "Busy";break; 
            
        case COMPARE_ERROR: 
            msg = "Compare Error";break; 
            
        default:         
                LCD_Goto(0,0);
                LCD_WriteString("ERROR: 0x"); 
                LCD_WriteInt(res,(2<<8) | 16);
                LCD_WriteChar(' ');
                TIMER0_DelayMs(1500);
                return;                 
    }
    
    LCD_Goto( (LCD_W/2) - (strlenInPixels(msg)/2), LCD_H /2);
    LCD_WriteString(msg);
    TIMER0_DelayMs(1500);
}

int main(void){
State state;
uint32_t button,res;
    
    SYS_Init();       
    
    restoreData(&saveddata,sizeof(SaveData));   
    
    state = switchTo(IDLE);
    
    //printf("SaveData Size: %u Bytes\n",sizeof(SaveData));
    
    while(loop){
        
        //Check Events      
        button = BUTTON_Hit();        
        
        #if 0   
        if(BUTTON_GetEvents() != BUTTON_EMPTY){
           printf("Button %u State %u\n",button, BUTTON_GetEvents());
        }
        #endif
        
        #if 0
        if(button){
            LCD_Goto(0,0);
            LCD_WriteInt(button,(4<<8)|16);
            LCD_WriteChar(':');
            LCD_WriteInt(BUTTON_GetEvents(),16);
        }        
        #endif    
         
        //main state machine        
        switch(state){
            case IDLE:
                idle();
                
                if(BUTTON_GetEvents() == BUTTON_PRESSED){
                    switch(button){
                        case BUTTON_F:
                            newGame(&saveddata.spaceInvaders);                                      
                            state = switchTo(GAME);
                            break;
                        case BUTTON_S:
                            restoreData(&saveddata,sizeof(SaveData));
                            //if(!checksumData(&saveddata.spaceInvaders, sizeof(GameData), saveddata.checksum))
                            if(!memcmp(&saveddata,0x1a000,sizeof(SaveData)))
                                
                                state = switchTo(GAME);
                            break;
                        default: break;
                    }
                    break;
                }
                
                if(BUTTON_GetEvents() == BUTTON_HOLD){
                    //if(button == BUTTON_L){
                    switch(button){
                        //case BUTTON_L:
                        case (BUTTON_L| BUTTON_R):
                            state = switchTo(CONFIG);
                            break;
                            
                        case BUTTON_R:
                            //memset(&saveddata.topscores, 0, MAX_TOP_SCORES * sizeof(uint32_t));
                            //memset(&saveddata.spaceInvaders, 0 ,sizeof(GameData));
                            memset(&saveddata, 0, sizeof(SaveData));
                            switchTo(IDLE);
                        default: break;
                    }                
                }                
                break;
                
            case CONFIG:
                if(!config(button)){
                    state = switchTo(IDLE);
                    RTC_SetValue(&saveddata.rtc);
                }
                break;
                
            case GAME: 
                if(button == BUTTON_S){
                    if(BUTTON_GetEvents() == BUTTON_PRESSED){
                        state = switchTo(SAVE);
                        break;
                    }
                }
                space(button);
                break;    
                        
            case SAVE:
                LED_SetState(LED_ON);
                //printf("Score: %u\n",saveddata.spaceInvaders.score);                                
                saveTopScore(saveddata.spaceInvaders.score, saveddata.topscores);                
                
                saveddata.checksum = generateChecksum(&saveddata.spaceInvaders, sizeof(GameData));                    
                
                res = saveData(&saveddata, sizeof(SaveData));
                
                LED_SetState(LED_OFF);
                
                displaySaveResult(res);                
                
                state = switchTo(IDLE);                
                break;   
        }        
    }
return 0;
}
