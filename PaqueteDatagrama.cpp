#include "PaqueteDatagrama.h"
#include <string.h>

PaqueteDatagrama::PaqueteDatagrama(const char * payload, unsigned int size, const char * ipAddress, int port) : longitud(size), puerto(port)
{
	strcpy(ip, ipAddress);
	datos = new char[size];
	memcpy(datos, payload, size);
}

PaqueteDatagrama::PaqueteDatagrama(unsigned int size) : longitud(size), datos(new char[size+1]) {}

PaqueteDatagrama::~PaqueteDatagrama()
{
	delete[] datos;
}

char * PaqueteDatagrama::obtieneDireccion()
{
	return ip;
}

unsigned int PaqueteDatagrama::obtieneLongitud()
{
	return longitud;
}

int PaqueteDatagrama::obtienePuerto()
{
	return puerto;
}

char * PaqueteDatagrama::obtieneDatos()
{
	return datos;
}

void PaqueteDatagrama::inicializaPuerto(int puerto)
{
	this->puerto = puerto;
}

void PaqueteDatagrama::inicializaIp(char * ip)
{
	//strcpy(this->ip, ip);
	for (int i = 0; i < strlen(ip); ++i)
	{
		this->ip[i] = ip[i];
	}
}

void PaqueteDatagrama::inicializaDatos(char * datos)
{
	memcpy(this->datos, datos, longitud);
}
