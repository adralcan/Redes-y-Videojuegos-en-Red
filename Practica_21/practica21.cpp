#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main(){
	/* Comprobar la ocurrencia de error y notificarlo con la llamada perror(3)*/
	int sU = setuid(2);
	if (sU == -1) {
		//perror("Error");
		char * descriptionError = strerror(errno); // error es una variable propia de cada thread (se crea sola)
	
	}
	std::cout << descriptionError << std::endl;
	return 1;
}
