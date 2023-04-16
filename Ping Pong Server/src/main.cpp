#include "server.h"
//UTP
int main()
{
	Net::Server server(8888, "127.0.0.1");
	server.start();
	return 0;
}