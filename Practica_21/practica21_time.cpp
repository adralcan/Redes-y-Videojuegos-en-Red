#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>


int main(){
	
	time_t tloc = 2;
	time_t segundos = time(&tloc);
	if (segundos == -1) {
		perror("Error");	
	}	
	
	const time_t timer = 3;
	char * resultado = ctime(&timer);
	if (resultado == NULL){
		perror("Error");	
	}
	time_t hor=(int)(segundos / 3600);
    	time_t minu=(int)((segundos - hor * 3600) / 60);
    	time_t seg= segundos - (hor * 3600 + minu * 60);
    	std::cout << hor << "h " << minu << "m " << seg << "s" << std::endl;
	std::cout << resultado << std::endl;
	return 1;
}
