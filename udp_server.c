#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 12345

int main() {
    int sfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[256];

    // Tworzenie gniazda UDP
    sfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Binding gniazda z adresem i portem
    bind(sfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("Oczekiwanie na datagramy...\n");

    // Odbieranie datagramu
    int rc = recvfrom(sfd, buffer, 256, 0, (struct sockaddr *)&client_addr, &client_len);
    buffer[rc] = '\0';

    printf("Otrzymano: %s\n", buffer);

    // Wysyłanie odpowiedzi
    sendto(sfd, "Dziękuję!", strlen("Dziękuję!"), 0, (struct sockaddr *)&client_addr, client_len);

    close(sfd);
    return 0;
}
