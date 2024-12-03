#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

//#define DEFAULT_PORT 12345

int main(int argc, char *argv[]) {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[256];
    int PORT = atoi(argv[1]);
    int on = 1;

    //Tworzenie gniazda TCP
    server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));

    //Ustawianie adresu serwera
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; //nasłuchujemy na wszystkich interfejsach
    server_addr.sin_port = htons(PORT);

    //Bindowanie gniazda z adresem IP i portem
    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    //Nasłuchujemy na połączenia
    listen(server_fd, 3); // 3 to max liczba oczekujących połączeń w kolejce
    printf("Oczekujemy na polaczenia...\n");

    //Akceptowanie połączenia od klienta
    socklen_t client_len = sizeof(client_addr);
    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
    printf("Połączenie z klientem: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    //Odbieranie danych od klienta
    read(client_fd, buffer, 256);
    printf("Otrzymano: %s\n", buffer);

    //Wysyłanie odpowiedzi [server-->client]
    send(client_fd, "Dziękuję za połączenie!", strlen("Dziękuję za połączenie!"), 0);

    close(client_fd);
    close(server_fd);
    return 0;
}
