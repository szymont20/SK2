#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

//#defince PORT 12345;
//#define SERVER_ADDR 127.0.0.1;

int main(int argc, char *argv[]) {

    int cfd;
    struct sockaddr_in server_addr;
    char *message = "Witaj serwerze!";
    char buffer[256];

    //Tworzenie gniazda
    cfd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2])); //drugi argument to numer portu

    inet_pton(AF_INET, argv[1], &server_addr.sin_addr); //konwertowanie adresu IP

    //Łączenie z serwerem
    connect(cfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    //Wysyłanie danych
    send(cfd, message, strlen(message), 0);

    //Odbieranie odpowiedzi od serwera
    read(cfd, buffer, 256);
    printf("Otrzymano odpowiedź: %s\n", buffer);

    close(cfd);
    return 0;
}
