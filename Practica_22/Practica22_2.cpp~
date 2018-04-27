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
	struct addrinfo hints;
	struct addrinfo *res; // se usa para el bind()

	memset((void*) &hints, '\0', sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM; // DGRAM siempre es UDP

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
		struct sockaddr  src_addr;
		socklen_t  addrlen;

		char host [NI_MAXHOST];
		char serv [NI_MAXSERV];
		
		ssize_t s = recvfrom(sd, buf, 255, 0, /*IP y puerto del otro extremo (variable de salida)*/ &src_addr, /*argumento de entrada/salida*/&addrlen);
		
		// Utiliza lo devuelto por el recvfrom();
		getnameinfo(&src_addr, &addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST);

		std::cout << "Conexion: " << host << ":" <<	serv << "\n";
		std::cout << "Mensaje: " << buf << std::endl;

		sendto(/*En este caso solo hay un canal*/ sd, buf, s, 0, &src_addr, addrlen);

	}
	return 0;
}




