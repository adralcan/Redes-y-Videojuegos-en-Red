#include <locale>
#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <errno.h>

       int main(int argc, char *argv[])
       {
           char outstr[200];
           time_t t;
           tm * tmp;

           t = time(NULL);
           tmp = localtime(&t);
           if (tmp == NULL) {
               perror("localtime");
           }

        strftime(outstr, sizeof(outstr), "Esamos en el año %Y", tmp);

        std::cout << outstr << std::endl; 
	setlocale(LC_ALL, "es_ES.UTF-8");
	strftime(outstr, sizeof(outstr), "Hoy es %A, %H:%M", tmp);
	std::cout << outstr << std::endl;	
	return 1;
       }

