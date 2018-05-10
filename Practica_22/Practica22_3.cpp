#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include <locale>


int main (int argc, char **argv, char **comando) {

	struct addrinfo hints;
	struct addrinfo *res; // se usa para el bind()

	memset((void*) &hints, '\0', sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM; // DGRAM siempre es UDP
	hints.ai_flags = 0; //AI_PASSIVE;    /* For wildcard IP address */

	// returns a list of address structures
	int rc = getaddrinfo(argv[1], argv[2], &hints, &res);

	if (rc != 0) {
		std::cout << "error getaddrinfo(): " << gai_strerror(rc) << std::endl;
		return -1;
	}

	int sd = socket(res->ai_family, res->ai_socktype,
                       res->ai_protocol);

	bind (sd, res->ai_addr, res->ai_addrlen);

	freeaddrinfo(res);

	while(true) {

		char buf[256];
		buf[0] = 't';
		//sendto(/*En este caso solo hay un canal*/ sd, buf, sizeof(buf[0]), 0, &src_addr, addrlen);
		if(write(sd, buf[0], strlen(buf[0]) + 1) == -1) //+1 for terminating null byte
				std::cout << "error write(): " << gai_strerror(rc) << std::endl;

		if(read(sd, buf, sizeof(buf)) == -1)	
				std::cout << "error read(): " << gai_strerror(rc) << std::endl;

		/*char c;
		std::cin >> c;
		//std::cout << c << std::endl;
		//std::cout << **comando << std::endl;
		// no estiendo porque pasa el comando como mayuscula
		if(c == **comando){
			std::cout << "recive la t";
			buf[0] = 't';
		} */

	}
	return 0;
}




