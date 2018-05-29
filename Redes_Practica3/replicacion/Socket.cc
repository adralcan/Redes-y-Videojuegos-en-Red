#include "Socket.h"
#include "Serializable.h"

#include <string.h>

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// Implementación Socket
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

bool operator== (const Socket &s1, const Socket &s2)
{
	sockaddr_in* si1 = (sockaddr_in*) s1.sa;
	sockaddr_in* si2 = (sockaddr_in*) s2.sa;
	
	return (si1.sin_family == si2.sin_family && si1.sin_port == si2.sin_port
		&& si1.sin_addr == si2.sin_addr);
}

std::ostream& operator<<(std::ostream& os, const Socket& s)
{
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];

    getnameinfo((struct sockaddr *) &(s.sa), s.sa_len, host, NI_MAXHOST, serv,
                NI_MAXSERV, NI_NUMERICHOST);

    os << host << ":" << serv;
}

// ----------------------------------------------------------------------------

Socket::Socket(const char * address, const char * port):sd(-1)
{
	struct addrinfo hints;
	struct addrinfo *res; // se usa para el bind()

	memset((void*) &hints, '\0', sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM; // DGRAM siempre es UDP
	hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */

	int rc = getaddrinfo(address, port, &hints, &res);

	if (rc != 0) {
		std::cout << "error getaddrinfo(): " << gai_strerror(rc) << std::endl;
		return -1;
	}

	int sd = socket(res->ai_family, res->ai_socktype,
        res->ai_protocol);
	sa = res->ai_addr;
	sa_len = res->ai_addrlen;
}

// ----------------------------------------------------------------------------

int Socket::bind()
{
    return ::bind(sd, (const struct sockaddr *) &sa, sa_len);
}

// ----------------------------------------------------------------------------

int Socket::send(Serializable * obj, Socket * sock)
{
	return sendto(d, obj->data(), obj->size(), 0, &sock->sa, sock->sa_len);
}

// ----------------------------------------------------------------------------

int Socket::recv(char * buffer, Socket ** sock)
{
	return recvfrom(sd, buffer, sizeof(buffer), 0, &sock->sa, sock->sa_len);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

