#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

const int BUFFER_SIZE = 1024;

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Ошибка: не удалось создать сокет" << std::endl;
        return 1;
    }
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr <<"Ошибка: не удается привязать сокет к адресу" << std::endl;
        close(serverSocket);
        return 1;
    }
    if (listen(serverSocket, 5) == -1) {
        std::cerr << "Ошибка: не удается прослушать сокет" << std::endl;
        close(serverSocket);
        return 1;
    }
    std::cout <<"Сервер запущен, ожидает подключения..." << std::endl;
    while (true) {
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
        if (clientSocket == -1) {
            std::cerr << "Ошибка: не удается установить соединение" << std::endl;
            continue;
        }
        std::cout << "Соединение принято от " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << std::endl;
        char buffer[BUFFER_SIZE];
        while (true) {
            int bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0);
            if (bytesRead == -1) {
                std::cerr << "Ошибка: Не удается получить данные" << std::endl;
                break;
            } else if (bytesRead == 0) {
                std::cout << "Клиент отключен" << std::endl;
                break;
            }
            int bytesSent = send(clientSocket, "Received", strlen("Received"), 0);
            if (bytesSent == -1) {
                std::cerr << "Ошибка: Не удается отправить данные" << std::endl;
                break;
            }
            memset(buffer, 0, BUFFER_SIZE);
        }
        close(clientSocket);
    }
    close(serverSocket);
}
