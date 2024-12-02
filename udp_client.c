#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

//#define SERVER_IP "127.0.0.1"
//#define PORT 12345

int main(int argc, char *argv[]) {

    int cfd;
    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);
    char *message = "Cześć, serwerze!";
    char buffer[256];

    // Tworzenie gniazda UDP
    cfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));

    // Konwertowanie adresu IP
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);

    // Wysyłanie datagramu
    sendto(cfd, message, strlen(message), 0, (const struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("Wysłano: %s\n", message);

    // Odbieranie odpowiedzi
    int rc = recvfrom(cfd, (char *)buffer, 256, 0, (struct sockaddr *)&server_addr, &addr_len);
    buffer[rc] = '\0';
    printf("Odpowiedź: %s\n", buffer);

    close(cfd);
    return 0;
}
