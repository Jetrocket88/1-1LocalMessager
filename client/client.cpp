#include <WinSock2.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <thread>
#include <fstream>

#define PORT 8080
#define BUFFER_SIZE 1024


void receiveMessage(int clientSocket) {
    char buffer[BUFFER_SIZE] = {};
    while(true) {
        memset(buffer, 0, BUFFER_SIZE); //clear the buffer
        int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if (bytesReceived <= 0) {
            std::cerr << "Connection closed";
            exit(0);
        }
        std::cout << "\n< " << buffer << "\n> " << std::flush;
    }
}

int main()
{

    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddress, clientAddress;
    char buffer[BUFFER_SIZE] = {};


    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed: " << WSAGetLastError() << std::endl;
        return 1;
    }

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Connection failed: " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    
    std::thread receiveThread(receiveMessage, clientSocket);
    receiveThread.detach(); // Run it independently

    std::ofstream messageFile("../messages.txt", std::ios::app);
    while (true) {
        memset(buffer, 0, BUFFER_SIZE); //clear the buffer
        std::cout << "> ";
        std::cin.getline(buffer, BUFFER_SIZE);

        // send message to client
        send(clientSocket, buffer, strlen(buffer), 0);
        messageFile << "<" << buffer << std::endl;
    }

    // closing socket
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
