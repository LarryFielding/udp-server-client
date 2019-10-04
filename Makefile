all: main_c main_s
main_c: main_c.cpp SocketDatagrama.o PaqueteDatagrama.o
	g++ main_c.cpp SocketDatagrama.o PaqueteDatagrama.o -o main_c
main_s: main_s.cpp SocketDatagrama.o PaqueteDatagrama.o
	g++ main_s.cpp SocketDatagrama.o PaqueteDatagrama.o -o main_s
SocketDatagrama.o: SocketDatagrama.cpp SocketDatagrama.h PaqueteDatagrama.o
	g++ SocketDatagrama.cpp -c
PaqueteDatagrama.o: PaqueteDatagrama.cpp PaqueteDatagrama.h
	g++ PaqueteDatagrama.cpp -c
	