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
	class Server
	{
	private:
		WSADATA wsa;
		SOCKET serversocket;
		std::string ipaddress;
		int port;
		char buffer[SIZE];
		std::string message;
		struct sockaddr_in info = {0};
		int infolength;
		int reclength;
	public:
		Server(int, std::string);
		~Server();
	public:
		void start();
		//void stop(); 
		void init();
		void recieve();
		void process();
		void send();
	};
}