// Programacion concurrente tcp
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
#include <pthread.h>



class ServerThread{
public:
	ServerThread(int s) : sd(s){};
	void do_msg(){
		while(true){
			char buf[256];

			std::cout << pthread_self();
			size_t s = recv(sd, buf, 255, 0);
			sleep(3);
			send(sd, buf, sizeof(buf), 0);

		}
	}
private:
	int sd;
};

extern "C" void * start_routine(void * _st){
	ServerThread * st = static_cast<ServerThread*>(_st);
	st->do_msg();
	return 0;
}

int main (int argc, char **argv) {

// 1. INICIAMOS EL SOCKET
	struct addrinfo hints;
	struct addrinfo *res; // se usa para el bind()

	memset((void*) &hints, '\0', sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM; // DGRAM siempre es UDP
	//hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */

	int rc = getaddrinfo(argv[1], argv[2], &hints, &res);

	if (rc != 0) {
		std::cout << "error getaddrinfo(): " << gai_strerror(rc) << std::endl;
		return -1;
	}

	int sd = socket(res->ai_family, res->ai_socktype,
                       res->ai_protocol);

	bind (sd, res->ai_addr, res->ai_addrlen);

	listen(sd, 1); // el socket sd se usara para aceptar peticiones de conexion

	freeaddrinfo(res);

	// Permanecemos en el bucle esperando conexiones
	while(true){ 
		struct sockaddr  src_addr;
		socklen_t addrlen = sizeof(src_addr); // Tamaño direccionIP		
		int socket_descriptor = accept(sd, &src_addr, &addrlen);
		if(socket_descriptor > -1){
			std::cout << "Llega hasta aqui" << std::endl;
			pthread_t thread_id;
			pthread_attr_t atributes;
			ServerThread * st = new ServerThread(socket_descriptor);
			pthread_attr_init(&atributes);
			pthread_attr_setdetachstate(&atributes, PTHREAD_CREATE_DETACHED);
			pthread_create(&thread_id, &atributes, start_routine,
				static_cast<void*>(st));
		}
	}
	while(true) {
		// Para que espere el thread principal
		char c;
		std::cin >> c;
		if(c == 'q')
			break;
		
	}
	return 0;
}




