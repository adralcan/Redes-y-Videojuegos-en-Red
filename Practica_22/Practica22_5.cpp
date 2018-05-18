// tcp client
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


int main (int argc, char **argv) {

	struct addrinfo hints;
	struct addrinfo *res; // se usa para el bind()

	memset((void*) &hints, '\0', sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM; // DGRAM -> UDP / STREAM -> TCP
	hints.ai_flags = 0; //AI_PASSIVE;    /* For wildcard IP address */

	// returns a list of address structures
	int rc = getaddrinfo(argv[1], argv[2], &hints, &res);

	if (rc != 0) {
		std::cout << "error getaddrinfo(): " << gai_strerror(rc) << std::endl;
		return -1;
	}

	int sd = socket(res->ai_family, res->ai_socktype,
                       res->ai_protocol);

	//bind (sd, res->ai_addr, res->ai_addrlen);

	freeaddrinfo(res);

	struct sockaddr addr;
	socklen_t addlen = sizeof(addr); 

	connect(sd, &addr, addlen);
	while(true){
		char buf[256];
		std::cin >> buf;
		if(buf[0] == 'Q'){
			shutdown(sd, 2); // 0 no quiero recibir datos, 1 no quiero enviar datos y 2 ambas
		}
		else{
			sendto(sd, buf, sizeof(buf), 0, res->ai_addr, res->ai_addrlen);
			int ss = recv(sd, buf, 255, 0);
			if(ss == -1)	
					std::cout << "error recv(): " << gai_strerror(rc) << std::endl;
			else{	
				buf[ss]='\0'; // para que sepa cual es el ultimo byte y que el msg sea legible
				std::cout << buf << std::endl;
			}
		}
	}
	return 0;
}




