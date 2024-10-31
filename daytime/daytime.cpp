#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#define SERVER_IP "172.16.40.1"
#define SERVER_PORT 13
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Создание UDP сокета
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
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

    // Отправка пустого запроса
    if (sendto(sock, nullptr, 0, 0, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Ошибка отправки" << std::endl;
        close(sock);
        return EXIT_FAILURE;
    }

    // Получение ответа
    socklen_t addr_len = sizeof(server_addr);
    int len = recvfrom(sock, buffer, BUFFER_SIZE - 1, 0, (struct sockaddr*)&server_addr, &addr_len);
    if (len < 0) {
        std::cerr << "Ошибка получения данных" << std::endl;
        close(sock);
        return EXIT_FAILURE;
    }
    buffer[len] = '\0';
    std::cout << "Время сервера: " << buffer << std::endl;

    close(sock);
    return 0;
}
