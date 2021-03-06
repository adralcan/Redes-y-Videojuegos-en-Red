#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <iostream>
#include <time.h>

int main (int argc, char **argv) {
	struct addrinfo hints; // pistas para filtrar
	struct addrinfo *res; // resultado: lista enlazada con todas las direcciones 

	memset((void*) &hints, '\0', sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	//hints.ai_socktype = SOCK_DGRAM; // DGRAM siempre es UDP

	int rc = getaddrinfo(argv[1], argv[2], &hints, &res);

	if (rc != 0) {
		std::cout << "error getaddrinfo(): " << gai_strerror(rc) << std::endl;
		return -1;
	}
	char host [NI_MAXHOST], server[NI_MAXSERV];
	getnameinfo(res->ai_addr, res->ai_addrlen, host, sizeof(host), server, sizeof(server), NI_NUMERICHOST);
	while(res != NULL){
		std::cout << "Name: " << host << std::endl;
		std::cout << "Family: " << res->ai_family << std::endl;	
		std::cout << "Type: " << res->ai_socktype << std::endl;	
		res = res->ai_next; 
	}	

	return 0;
}
