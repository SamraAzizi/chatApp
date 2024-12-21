#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <WS2tcpip.h>
#include "ChatCommon.h"
#pragma comment(lib, "ws2_32.lib")

class ChatServer {
private:
    SOCKET serverSocket;
    std::vector<SOCKET> clients;
    std::mutex clientsMutex;

public:
    ChatServer() {
        WSADATA wsData;
        WORD ver = MAKEWORD(2, 2);
        WSAStartup(ver, &wsData);

        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        
        sockaddr_in hint;
        hint.sin_family = AF_INET;
        hint.sin_port = htons(PORT);
        hint.sin_addr.S_un.S_addr = INADDR_ANY;

        bind(serverSocket, (sockaddr*)&hint, sizeof(hint));
        listen(serverSocket, SOMAXCONN);
    }

    void start() {
        std::cout << "Server started on port " << PORT << std::endl;
        
        while (true) {
            SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
            
            {
                std::lock_guard<std::mutex> lock(clientsMutex);
                clients.push_back(clientSocket);
            }

            std::thread clientThread(&ChatServer::handleClient, this, clientSocket);
            clientThread.detach();
        }
    }

    void handleClient(SOCKET clientSocket) {
        char buffer[BUFFER_SIZE];

        while (true) {
            ZeroMemory(buffer, BUFFER_SIZE);
            int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
            
            if (bytesReceived <= 0) {
                removeClient(clientSocket);
                break;
            }

            broadcastMessage(buffer, clientSocket);
        }
    }

    void broadcastMessage(const char* message, SOCKET sender) {
        std::lock_guard<std::mutex> lock(clientsMutex);
        for (SOCKET client : clients) {
            if (client != sender) {
                send(client, message, strlen(message), 0);
            }
        }
    }

    void removeClient(SOCKET clientSocket) {
        std::lock_guard<std::mutex> lock(clientsMutex);
        auto it = std::find(clients.begin(), clients.end(), clientSocket);
        if (it != clients.end()) {
            closesocket(*it);
            clients.erase(it);
        }
    }

    ~ChatServer() {
        for (SOCKET client : clients) {
            closesocket(client);
        }
        closesocket(serverSocket);
        WSACleanup();
    }
};

int main() {
    ChatServer server;
    server.start();
    return 0;
} 