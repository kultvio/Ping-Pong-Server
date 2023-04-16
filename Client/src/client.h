#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include <WinSock2.h>
#include <unordered_map>
#include <string>
#include <cassert>


#pragma comment(lib, "Ws2_32.lib")


#define SIZE 1024

namespace Net
{
	class Client
	{
	private:
		WSADATA wsa;
		SOCKET clientsocket;
		std::string ipadress;
		int port;
		char buffer[SIZE];
		std::string message;
		struct sockaddr_in info;
		int infolength;
		int reclength;
	public:
		Client(int, std::string);
		~Client();
	public:
		void connect();
		void init();
		void recieve();
		void process();
		void send();
	};
}
