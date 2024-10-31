#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#define SERVER_IP "172.16.40.1"
#define SERVER_PORT 7
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Создание TCP сокета
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Ошибка создания сокета" << std::endl;
        return EXIT_FAILURE;
    }

    // Настройка адреса сервера
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        std::cerr << "Неверный адрес" << std::endl;
        close(sock);
        return EXIT_FAILURE;
    }

    // Подключение к серверу
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Ошибка подключения" << std::endl;
        close(sock);
        return EXIT_FAILURE;
    }

    // Ввод сообщения на сервер
    std::cout << "Введите сообщение: ";
    std::cin.getline(buffer, BUFFER_SIZE);
    send(sock, buffer, strlen(buffer), 0);

    // Получение ответа
    int len = recv(sock, buffer, BUFFER_SIZE - 1, 0);
    if (len < 0) {
        std::cerr << "Ошибка получения данных" << std::endl;
    } else {
        buffer[len] = '\0';
        std::cout << "Эхо от сервера: " << buffer << std::endl;
    }

    close(sock);
    return 0;
}
