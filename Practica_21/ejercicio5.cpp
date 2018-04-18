#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <math.h>

int main() {
	
	timespec tp_antes;
	int antes = clock_gettime(2, &tp_antes);
	for (int i = 0; i < 10000; i++);
	timespec tp_despues;
	int despues = clock_gettime(2, &tp_despues);
	if (antes != 0 || despues != 0){
		perror("Error:");
	}
	std::cout << "Antes: " << (long)pow(tp_antes.tv_sec, 3) + tp_antes.tv_nsec << " Despues: " << (long)pow(tp_antes.tv_sec, 3) + tp_despues.tv_nsec << std::endl;
	return 1;
}
