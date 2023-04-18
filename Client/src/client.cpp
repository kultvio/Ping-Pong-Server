#include "client.h"

#pragma warning(disable:4996)

namespace Net
{
	Client::Client(int port, std::string ipadress)
		:
		wsa{ 0 },
		port(port),
		ipadress(ipadress),
		clientsocket(INVALID_SOCKET),
		info{ 0 },
		infolength(sizeof(info)){}

	void Client::init()
	{
		info.sin_family = AF_INET;
		info.sin_port = htons(port);
		info.sin_addr.s_addr = inet_addr(ipadress.c_str());

		printf("WSA init \n");
		if ((WSAStartup(MAKEWORD(2, 2), &wsa)) == SOCKET_ERROR)
		{
			printf("Couldn't init WSA\n");
		}
		printf("WSA success\n");

		printf("Creating socket\n");
		if ((clientsocket = socket(AF_INET, SOCK_DGRAM, 0)) == SOCKET_ERROR)
		{
			printf("Couldn't create socket\n");
		}
		printf("Success\n");

	}

	void Client::connect()
	{
		init();
		for (;;)
		{
			send();
			recieve();
			process();
		}
	}
	void Client::send()
	{
		printf("Enter massage: ");
		std::getline(std::cin, message);
		start_time = clock();
		printf("\nTry to send\n");
		
		if ((sendto(clientsocket, message.c_str(), message.size(), 0, (SOCKADDR*)&info, infolength)) == SOCKET_ERROR)
		{
			printf("Send Error %d\n", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		printf("Send success\n");
	}

	void Client::recieve()
	{
		printf("Try to recieve\n");
		if ((reclength = recvfrom(clientsocket, buffer, SIZE, 0, (struct sockaddr*)&info, &infolength)) == SOCKET_ERROR)
		{
			printf("Recieve Error %d\n", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		end_time = clock();
		printf("Send success\n");
	}

	void Client::process()
	{
		printf("__________________________________\n\n");
		printf("packet from: %s:%d\n", inet_ntoa(info.sin_addr), ntohs(info.sin_port));
		for (unsigned i = 0; i < reclength; i++)
		{
			printf("%c", buffer[i]);
		}
		int time = end_time - start_time;
		printf(", ping: %u", time);
		printf("\n__________________________________\n\n");
		printf("\n");
	}
	Client::~Client()
	{
		WSACleanup();
		closesocket(clientsocket);
	}


}