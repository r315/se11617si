#include <gpio.h>

#define LED (1<<12)
#define INPUT (1<<0)

int main(void){
int state;
GPIO_Init(LED,0);

while(1){
	state = GPIO_Read() & INPUT;
	GPIO_Write(state == 0 ? LED : 0);
}

return 0;
}




 
