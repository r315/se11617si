#include <gpio.h>

#define LED (1<<12)
#define INPUT (1<<0)

int main(void){
int state;
GPIO_SetOutputN(LED);

while(1){
	state = GPIO_Read() & INPUT;
	if(state)
        GPIO_ClrN(LED);
    else
        GPIO_SetN(LED);
}

return 0;
}




 
