#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

using namespace std;

class Server {
private:
    int m_socket;
    struct sockaddr_in m_serverAddr;
    char m_buffer[1024];

public:
    Server() {
        m_socket = socket(AF_INET, SOCK_DGRAM, 0);
        if (m_socket < 0) {
            cerr << "Failed to create socket" << endl;
            exit(EXIT_FAILURE);
        }
        memset(&m_serverAddr, 0, sizeof(m_serverAddr));
        m_serverAddr.sin_family = AF_INET;
        m_serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        m_serverAddr.sin_port = htons(1234);
    }

    ~Server() {
        close(m_socket);
    }

    void init() {
        if (bind(m_socket, (struct sockaddr*)&m_serverAddr, sizeof(m_serverAddr)) < 0) {
            cerr << "Failed to bind socket" << endl;
            exit(EXIT_FAILURE);
        }
    }

    void start() {
        while (true) {
            receive();
            process();
            send();
        }
    }

    void receive() {
        memset(m_buffer, 0, sizeof(m_buffer));
        struct sockaddr_in clientAddr;
        socklen_t clientLen = sizeof(clientAddr);
        int n = recvfrom(m_socket, m_buffer, sizeof(m_buffer), 0,
            (struct sockaddr*)&clientAddr, &clientLen);
        if (n < 0) {
            cerr << "Failed to receive packet" << endl;
            exit(EXIT_FAILURE);
        }
    }

    void process() {
        struct hostent* host = gethostbyaddr((const char*)&m_serverAddr.sin_addr.s_addr,
            sizeof(m_serverAddr.sin_addr.s_addr), AF_INET);
        cout << "Received packet from " << host->h_name << endl;
        cout << "Packet data: " << m_buffer << endl;
    }

    void send() {
        struct sockaddr_in clientAddr;
        socklen_t clientLen = sizeof(clientAddr);
        int n = sendto(m_socket, m_buffer, strlen(m_buffer), 0,
            (struct sockaddr*)&clientAddr, clientLen);
        if (n < 0) {
            cerr << "Failed to send packet" << endl;
            exit(EXIT_FAILURE);
        }
    }
};
