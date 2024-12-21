#include <iostream>
#include <thread>
#include <string>
#include <WS2tcpip.h>
#include "ChatCommon.h"
#pragma comment(lib, "ws2_32.lib")

class ChatClient {
private:
    SOCKET clientSocket;
    bool running;

public:
    ChatClient() : running(true) {
        WSADATA wsData;
        WORD ver = MAKEWORD(2, 2);
        WSAStartup(ver, &wsData);

        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        
        sockaddr_in hint;
        hint.sin_family = AF_INET;
        hint.sin_port = htons(PORT);
        inet_pton(AF_INET, SERVER_IP.c_str(), &hint.sin_addr);

        int connResult = connect(clientSocket, (sockaddr*)&hint, sizeof(hint));
        if (connResult == SOCKET_ERROR) {
            std::cerr << "Failed to connect to server!" << std::endl;
            running = false;
        }
    }

    void start() {
        if (!running) return;

        std::cout << "Connected to server!" << std::endl;
        std::thread receiveThread(&ChatClient::receiveMessages, this);
        receiveThread.detach();

        std::string message;
        while (running) {
            std::getline(std::cin, message);
            if (message == "quit") {
                running = false;
                break;
            }
            send(clientSocket, message.c_str(), message.size() + 1, 0);
        }
    }

    void receiveMessages() {
        char buffer[BUFFER_SIZE];
        while (running) {
            ZeroMemory(buffer, BUFFER_SIZE);
            int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
            if (bytesReceived <= 0) {
                std::cout << "Server disconnected" << std::endl;
                running = false;
                break;
            }
            std::cout << buffer << std::endl;
        }
    }

    ~ChatClient() {
        closesocket(clientSocket);
        WSACleanup();
    }
};

int main() {
    ChatClient client;
    client.start();
    return 0;
} 