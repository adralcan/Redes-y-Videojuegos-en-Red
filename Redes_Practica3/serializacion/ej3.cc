#include "Serializable.h"

#include <iostream>
#include <string>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

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
	int32_t total = MAX_NAME * sizeof(char) + 2 * sizeof(int16_t);
	alloc_data(total);
	char * tmp = data + sizeof(int32_t);
	memcpy (name, tmp, 80);
	tmp += 80;
	memcpy(&x, tmp, sizeof(int16_t));
	tmp += sizeof(int16_t);
	memcpy(&y, tmp, sizeof(int16_t));

	return 1;
	
    }

	void MostrarInfo() {
	
		std::cout << "Nombre: " << name << " X: " << x << " Y: " << y << std::endl;
	};
 
private:
    static const size_t MAX_NAME = 80;
    char name[MAX_NAME];

    int16_t x;
    int16_t y;

};

int main(int argc, char **argv)
{

	// 80: nombre, 4: cabecera, 4: x e y
	
	// Haciendo este casting pierde precision asiq que no vale
	// Jugador one(argv[1], (int)argv[2]  - 48, (int)argv[3]  - 48);
	// Hay que utilizar atoi https://stackoverflow.com/questions/12417378/cast-from-char-to-int-loses-precision

	Jugador one(argv[1], atoi(argv[2]), atoi(argv[3]));
	one.to_bin();

	const char * path = "ejercicio3.txt";
	int fileDescriptor = open(path, O_RDWR | O_CREAT);

	write(fileDescriptor, one.data(), one.size());
	
	close(fileDescriptor);

	// Vacio
	Jugador two("", 0, 0);
	
	char * dataTwo = (char*)malloc(one.size());

	// Como solo lo tiene que mostrar por pantalla solo tiene permisos de lectura
	int fileDescriptor2 = open(path, O_RDONLY);

	write(fileDescriptor2, dataTwo, one.size());
	
	close(fileDescriptor2);

	two.from_bin(dataTwo);

	two.MostrarInfo();
}
