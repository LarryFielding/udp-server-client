#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;


int main(int argc, char const *argv[])
{
    int bytes_recv, bytes_env;
    cout << "Soy servidor" << endl;

    string respuesta ("Recibí mensaje, gracias.");
    string ipAddress ("127.0.0.1");
    int puerto = 7200;
    int tam = respuesta.length() + 1;
    const char * crespuesta = respuesta.c_str();
    const char * cIpAddress = ipAddress.c_str();


	/**
     * 
     * Si es servidor inicializar con:
     * SocketDatagrama(int puerto), pidiendo el puerto al usuario.
     * Inicializar paquetes datagrama para envío y recibimiento
     */
    SocketDatagrama socket  = SocketDatagrama(7200);
    PaqueteDatagrama paquete_recv = PaqueteDatagrama(MAX_BUFF_TAM);

    while(1)
    {
        bytes_recv = socket.recibe(paquete_recv);

        if (bytes_recv < 0)
        {
            perror("Error al recibir");
            exit(1);
        }

        cout << "Cliente dijo: " << paquete_recv.obtieneDatos() << endl;
        cout << "Recibido desde ip: " << paquete_recv.obtieneDireccion() << endl;
        cout << "Con puerto: " << htons(paquete_recv.obtienePuerto()) << endl;

        PaqueteDatagrama paquete_env = PaqueteDatagrama(crespuesta, tam, cIpAddress, puerto);
        bytes_env = socket.envia(paquete_env);
    }
    
	return 0;
}
