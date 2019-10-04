#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;


int main(int argc, char const *argv[])
{
    int bytes_recv, bytes_env, puertoRemoto;
    char ipRemota[50];
    string mensaje;

	cout << "Soy cliente" << endl;
    cout << "Ingrese puerto remoto: ";
    cin >> puertoRemoto;
    cout << "Ingrese ip del servidor: ";
    cin >> ipRemota;
    cin.ignore();
    
    /**
     * Si es cliente inicializar con:
     * SocketDatagrama(int puertoRemoto, char * ipRemota),
     * pidiendo el puerto y direccion ip remotos al usuario.
     */
    
    SocketDatagrama socket  = SocketDatagrama(0);
    PaqueteDatagrama paquete_recv = PaqueteDatagrama(MAX_BUFF_TAM);

    while(1)
    {
        cout << "Ingrese su mensaje: ";
        getline(cin, mensaje);
        int tam = mensaje.length() + 1;
        const char * cmensaje = mensaje.c_str();
        
        PaqueteDatagrama paquete_env = PaqueteDatagrama(cmensaje, tam, ipRemota, puertoRemoto);
        bytes_env = socket.envia(paquete_env);

        if (bytes_env < 0)
        {
            perror("Fallo en envio");
            exit(1);
        }

        bytes_recv = socket.recibe(paquete_recv);

        if (bytes_recv < 0)
        {
            perror("Error al recibir");
            exit(1);
        }
        cout << "Servidor dijo: " << paquete_recv.obtieneDatos() << endl;
        cout << "Recibido desde ip: " << paquete_recv.obtieneDireccion() << endl;
        cout << "Con puerto: " << paquete_recv.obtienePuerto() << endl;

    }

    
	return 0;
}
