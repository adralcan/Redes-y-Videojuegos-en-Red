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
	hints.ai_socktype = SOCK_STREAM; // DGRAM siempre es TCP
	//hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */

	int rc = getaddrinfo(argv[1], argv[2], &hints, &res);

	if (rc != 0) {
		std::cout << "error getaddrinfo(): " << gai_strerror(rc) << std::endl;
		return -1;
	}

	int sd = socket(res->ai_family, res->ai_socktype,
                       res->ai_protocol);

	bind (sd, res->ai_addr, res->ai_addrlen); // binds the socket with the addres

	listen(sd, 1); // el socket sd se usara para aceptar peticiones de conexion
	freeaddrinfo(res);

	while(true) {

		struct sockaddr client;
		socklen_t client_len = sizeof(client); 

		// aceptamos el siguiente cliente que este en espera
		int client_s = accept(sd, &client, &client_len);
		if(client_s == -1)
			std::cout << "error accept(): " << gai_strerror(rc) << std::endl;	
			
		char host [NI_MAXHOST];
		char serv [NI_MAXSERV];

		getnameinfo(&client, client_len, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

		std::cout << "Conexion: " << host << ":" <<	serv << std::endl;

		while(true){
			char buf[256];
			//size_t s = recv(sd, buf, 255, 0);
			size_t s = recvfrom(sd, buf, 255, 0, &client, &client_len);
			if(s == -1){
				std::cout << "error recv(): " << gai_strerror(rc) << std::endl;	
				break;		
			}
			if(s == 0){ // ordenary shutdown
				close(sd);
				break;
			}
			std::cout << buf;
			send(sd, buf, s, 0);
		}
	}
	return 0;
}




