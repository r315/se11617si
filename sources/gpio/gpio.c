#include <lpc2106.h>

#define ON 1
#define OFF 0

#define LED (1<<12)
#define IN  (1<<0)


int main(int argc, char *argv[]){	
	
	GPIO0->DIR = LED;
	GPIO0->CLR = LED;

	while(1){ 
		if(GPIO0->PIN & IN)
			GPIO0->SET = LED;
		else
			GPIO0->CLR = LED;
	
	}
	return 0;
}
 
