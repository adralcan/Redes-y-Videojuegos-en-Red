#include "Serializable.h"

#include <iostream>
#include <string>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

class Jugador: public Serializable
{
public:
    Jugador(const char * _n, int16_t _x, int16_t _y):x(_x),y(_y)
    {
        strncpy(name, _n, MAX_NAME);
    };

    virtual ~Jugador(){};

    void to_bin()
    {
	int32_t total = MAX_NAME * sizeof(char) + 2 * sizeof(int16_t);
	alloc_data(total);
	char * tmp = _data + sizeof(int32_t);
	memcpy(tmp, name, 80); // name
	tmp += 80;
	memcpy(tmp, &x, sizeof(int16_t)); //x
	tmp += sizeof(int16_t);
	memcpy(tmp, &y, sizeof(int16_t)); //y
	tmp += sizeof(int16_t);
    }

    int from_bin(char * data)
    {
	char * tmp = data + sizeof(int32_t);
	memcpy (name, tmp, 80);
	tmp += 80;
	memcpy(&x, tmp, sizeof(int16_t));
	tmp += sizeof(int16_t);
	memcpy(&y, tmp, sizeof(int16_t));
	
    }

private:
    static const size_t MAX_NAME = 80;
    char name[MAX_NAME];

    int16_t x;
    int16_t y;


};

int main(int argc, char **argv)
{
	const char * path = "./ejercicio1.txt";
	int fileDescriptor = open(path, O_RDWR | O_CREAT, 0660);
	
	Jugador one("Player one", 12, 345);
	
	one.to_bin();
	write(fileDescriptor, one.data(), one.size());
	
	close(fileDescriptor);

	// 80: nombre, 4: cabecera, 4: x e y

}
