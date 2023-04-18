#include "server.h"
#include <Windows.h>
//UTP
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Net::Server server(8888, "0.0.0.0");
	server.start();
	return 0;
}