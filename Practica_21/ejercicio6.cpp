#include <time.h>
#include <stdio.h>
#include <locale.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <errno.h>

       int main(int argc, char *argv[])
       {
           char outstr[4];
           time_t t;
           tm * tmp;

           t = time(NULL);
           tmp = localtime(&t);
           if (tmp == NULL) {
               perror("localtime");
           }

           strftime(outstr, sizeof(outstr), argv[1], tmp);

        std::cout << outstr << std::endl;
	return 1;
       }

