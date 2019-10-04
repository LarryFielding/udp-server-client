#include "SocketDatagrama.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>

using namespace std;

SocketDatagrama::SocketDatagrama(int puerto)
{
	int opc = 1;

	/* Paso 1: crear el socket */
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0)
	{
		perror("No se pudo crear socket");
		exit(1);
	}

	/* Paso 2: llenar estructura (direccion local) */

	memset(&direccionLocal, 0, sizeof(direccionLocal));
	direccionLocal.sin_family = AF_INET;
	direccionLocal.sin_addr.s_addr = INADDR_ANY;
	direccionLocal.sin_port = htons(puerto);
	
	/* Paso 3: asegurarse de que se puede utilizar el puerto */

	if (setsockopt(s,SOL_SOCKET,SO_REUSEADDR,&opc,sizeof(int)) < 0)
	{
        perror("setsockopt");
        exit(1);
    } 

	/* Paso 4: publicar direccion */

	if ((bind(s, (struct sockaddr *)&direccionLocal, sizeof(direccionLocal))) < 0)
	{
		perror("Error al publicar");
		exit(1);
	}
}

SocketDatagrama::SocketDatagrama(int puertoRemoto, char * ipRemota)
{
	/* Paso 1: crear el socket */
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0)
	{
		perror("No se pudo crear socket");
		exit(1);
	}


	/* Paso 2: llenar estructura (direccion local) */
	memset(&direccionLocal, 0, sizeof(direccionLocal));
	direccionLocal.sin_family = AF_INET;
	direccionLocal.sin_addr.s_addr = INADDR_ANY;
	direccionLocal.sin_port = htons(0);

	/* Paso 3: llenar estructura (direccion remota) */
	memset(&direccionForanea, 0, sizeof(direccionForanea));
	direccionForanea.sin_family = AF_INET;
	direccionForanea.sin_addr.s_addr = inet_addr(ipRemota);
	direccionForanea.sin_port = htons(puertoRemoto);

	/* Paso 4: publicar direccion */

	if ((bind(s, (struct sockaddr *)&direccionLocal, sizeof(direccionLocal))) < 0)
	{
		perror("Error al publicar");
		exit(1);
	}
}

SocketDatagrama::~SocketDatagrama() {}

int SocketDatagrama::recibe(PaqueteDatagrama &p)
{
	int bytes_recv;
	socklen_t tam_dir;
	char ipRemota[INET_ADDRSTRLEN];
	struct sockaddr_in msg_to_client_addr;
	
	tam_dir = sizeof(direccionForanea);
	cout << "Esperando mensaje..." << endl;
	
	bytes_recv = recvfrom(s, p.obtieneDatos(), MAX_BUFF_TAM, 0, (struct sockaddr *) &direccionForanea, &tam_dir);
	if (bytes_recv < 0)
	{
		perror("Error al recibir");
		exit(1);
	}
	/* Imprimir en consola la dirección y puerto del host remoto (asignarlas a PaqueteDatagrama)*/
	
	inet_ntop(AF_INET, &(msg_to_client_addr.sin_addr), ipRemota, INET_ADDRSTRLEN);
	p.inicializaIp(ipRemota);
	p.inicializaPuerto(htons(msg_to_client_addr.sin_port));
	
	cout << p.obtieneDatos() << endl;
	cout << p.obtienePuerto() << endl;

	return bytes_recv;
}

int SocketDatagrama::envia(PaqueteDatagrama &p)
{
	int bytes_env;
	unsigned int tam_msj;
	socklen_t tam_dir;

	tam_dir = sizeof(direccionForanea);
	tam_msj = p.obtieneLongitud();

	bytes_env = sendto(s, p.obtieneDatos(), tam_msj, 0, (struct sockaddr *) &direccionForanea, tam_dir);
	if (bytes_env < 0)
	{
		perror("Fallo en envio");
		exit(1);
	}

	return bytes_env;
}