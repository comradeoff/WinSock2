#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

int main(int argc, char* argv) {
    	std::cout << "Starting server..." << std::endl;

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cout << "Error#" << WSAGetLastError() << std::endl;
		return 1;
	}

	SOCKADDR_IN addr;
	int sizeOfAddr = sizeof(addr);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1111);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	if (sListen == INVALID_SOCKET) {
		std::cout << "Error#" << WSAGetLastError() << std::endl;
	}
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	std::cout << "Waiting for the client..." << std::endl;
	listen(sListen, SOMAXCONN);

	SOCKET sConnection = accept(sListen, (SOCKADDR*)&addr, &sizeOfAddr);
	if (sConnection == INVALID_SOCKET) {
		std::cout << "Error#" << WSAGetLastError() << std::endl;
	}

	std::cout << "Connected!" << std::endl;

	char msg[256];
	
	while (true) {
		std::cout << "Enter message to client(enter \"exit.\" to stop): ";
		fgets(msg, sizeof(msg), stdin);
		
		send(sConnection, msg, sizeof(msg), 0);
		if (msg[0] == 'e' && msg[1] == 'x' && msg[2] == 'i' && msg[3] == 't' && msg[4] == '.') {
			std::cout << "Connection closed!" << std::endl;
			WSACleanup();
			return 1;
		}

		std::cout << "Waiting answer from client..." << std::endl;
		recv(sConnection, msg, sizeof(msg), 0);
		if (msg[0] == 'e' && msg[1] == 'x' && msg[2] == 'i' && msg[3] == 't' && msg[4] == '.') {
			std::cout << "Connection closed!" << std::endl;
			WSACleanup();
			return 1;
		}

		std::cout << "Answer form client: " << msg;
	}

	return 0;
}