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
	hints.ai_socktype = SOCK_DGRAM; // DGRAM siempre es UDP
	hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */

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
		socklen_t addrlen = sizeof(src_addr); // Tamaño direccionIP

		char host [NI_MAXHOST];
		char serv [NI_MAXSERV];

		size_t s = recvfrom(sd, buf, 255, 0, &src_addr, &addrlen);

		// Utiliza lo devuelto por el recvfrom();
		getnameinfo(&src_addr, addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST);
		//std::cout << buf << endl;

		std::cout << "Conexion: " << host << ":" <<	serv << std::endl;

		char outstr[200];
		time_t t;
		tm * tmp;

		t = time(NULL);
		tmp = localtime(&t);
		if (tmp == NULL) {
		perror("localtime");
		}
		
		switch (buf[0]) {
			case 't':
				strftime(outstr, sizeof(outstr), "%H:%M", tmp);
				std::cout << outstr << std::endl;
			break;	
			case 'd':
				strftime(outstr, sizeof(outstr), "Hoy es %d/%m/%y", tmp);
				std::cout << outstr << std::endl;
			break;

			case 'q':
			std::cout << "CLOSE" << std::endl;
			shutdown(sd, 2); // 0 no quiero recibir datos, 1 no quiero enviar datos y 2 ambas
			close(sd);
			break;
		}

		if(buf[0] == 'q') // para que salga del bucle y deje de imprimir pero no estoy seguro de esto
			break;
		// No hsce falta devolverlo
		//sendto(/*En este caso solo hay un canal*/ sd, buf, s, 0, &src_addr, addrlen);

	}
	return 0;
}




