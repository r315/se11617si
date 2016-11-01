#include <spi.h>


int main(int argc, char *argv[]){

	SPI_Init();
	
	while(1){ 
		SPI_Send('U');
		
	}
	return 0;
}
 
