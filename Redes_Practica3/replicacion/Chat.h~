#include <string>
#include <unistd.h>
#include <string.h>
#include "Serializable.h"
#include "Socket.h"
#include "UDPServer.h"

class ChatMessage: public Serializable
{
public:
    ChatMessage(){};

    ChatMessage(const char * n, const std::string m)
    {
	  strncpy(nick, n, 8);
	  strncpy(message, m, 80);
    };

    void to_bin()
    {
	int32_t total = 80 * sizeof(char) + 8 * sizeof(char);
	alloc_data(total);
	char * tmp = _data + sizeof(int32_t);
	memcpy(tmp, nick, 8); // nick
	tmp += 8;
	memcpy(tmp, &message, 80); //msg
    }

    virtual int from_bin(char * bobj)
    {
	char * tmp = bobj + sizeof(int32_t);
	memcpy (name, tmp, 8);
	tmp += 8;
	memcpy(&nick, tmp, sizeof(char) * 8);
	tmp += sizeof(int16_t);
	memcpy(&message, tmp, sizeof(char) * 80);
    }

    char message[80];

    char nick[8];
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

class ChatServer : public UDPServer
{
public:
    ChatServer(const char * s, const char * p): UDPServer(s, p){};

    void do_message(char * buffer)
    {
	
    }
};

class ChatClient
{
public:
    ChatClient(const char * s, const char * p, const char * n):socket(s, p),
        nick(n){};

    void input_thread()
    {
    }

    void net_thread()
    {
    }

private:
    char nick[8];

    Socket socket;
};

