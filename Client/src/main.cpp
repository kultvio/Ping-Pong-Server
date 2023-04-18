#include "client.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::string ipaddress;
	printf("Input server ipaddress: ");
	std::getline(std::cin, ipaddress);
	Net::Client client(8888, ipaddress);
	client.connect();


	return 0;
}