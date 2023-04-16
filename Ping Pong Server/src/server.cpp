#include "server.h"
#pragma warning(disable:4996)

namespace Net
{
	Server::Server(int port, std::string ipaddress)
		:
		wsa{ 0 },
		port(port),
		ipaddress(ipaddress),
		serversocket(INVALID_SOCKET),
		info{ 0 }{}

	void Server::init()
	{
		info.sin_family = AF_INET;
		info.sin_port = htons(port);
		info.sin_addr.s_addr = inet_addr(ipaddress.c_str());


		printf("WSA init\n");
		WORD wVersionRequested = MAKEWORD(2, 2);
		int err = WSAStartup(wVersionRequested, &wsa);
		if (err != 0) {
			printf("WSAStartup failed with error: %d\n", err);
			return;
		}
		printf("WSA success\n");


		printf("Creating socket\n");

		if ((serversocket = socket(AF_INET, SOCK_DGRAM, 0)) == SOCKET_ERROR)
		{
			__debugbreak();
		}

		printf("Success!\n");

		infolength = sizeof(info);
		printf("bind socket\n");
		if ((bind(serversocket, (SOCKADDR*)&info, infolength)) != 0)
		{
			__debugbreak();
		}
		printf("socket binded\n");


		printf("Server started at:%s:%d\n", inet_ntoa(info.sin_addr), ntohs(info.sin_port));

	}


	void Server::start()
	{
		init();
		for (;;)
		{
			recieve();
			process();
			send();
		}
	}

	void Server::recieve()
	{
		if ((reclength = recvfrom(serversocket, buffer, SIZE, 0, (struct sockaddr*)&info, &infolength)) == SOCKET_ERROR)
		{
			printf("Recieve Error %d\n", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
	}

	void Server::process()
	{
		printf("packet from:%s:%d\n", inet_ntoa(info.sin_addr), ntohs(info.sin_port));
		for (unsigned i = 0; i < reclength; i++)
		{
			printf("%c", buffer[i]);
		}
		printf("\n");
	}
	void Server::send()
	{
		if ((sendto(serversocket, buffer, reclength, 0, (struct sockaddr*)&info, infolength)) == SOCKET_ERROR)
		{
			printf("Send Error %d\n", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
	}
	Server::~Server()
	{ 
		WSACleanup();
		closesocket(serversocket);
	}


}