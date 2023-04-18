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
		info{ 0 },
		infolength(sizeof(info)){}

	void Server::init()
	{
		info.sin_family = AF_INET;
		info.sin_port = htons(port);
		info.sin_addr.s_addr = inet_addr(ipaddress.c_str());


		printf("WSA init\n");
		if (WSAStartup(MAKEWORD(2, 2), &wsa) == SOCKET_ERROR) {
			printf("Couldn't init WSA\n");
			__debugbreak();
		}
		printf("WSA success\n");


		printf("Creating socket\n");

		if ((serversocket = socket(AF_INET, SOCK_DGRAM, 0)) == SOCKET_ERROR)
		{
			printf("Couldn't create socket\n");
			__debugbreak();
		}

		printf("Success!\n");

		printf("bind socket\n");
		if ((bind(serversocket, (SOCKADDR*)&info, infolength)) != 0)
		{
			printf("Couldn't bind socket\n");
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
		message = "Your port: " + std::to_string(ntohs(info.sin_port)) + "\nYour message: " ;
		
		for (unsigned i = 0; i < reclength; i++)
		{
			printf("%c", buffer[i]);
			message += buffer[i];
		}
		printf("\n");
	}
	void Server::send()
	{

		if ((sendto(serversocket, message.c_str(), message.size(), 0, (struct sockaddr*)&info, infolength)) == SOCKET_ERROR)
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