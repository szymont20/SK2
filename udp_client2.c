#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    int cfd;
    struct sockaddr_in server_addr;
    socklen_t server_len = sizeof(server_addr);
    char buff[256];
    char *message = "tu klient";

    //socket
    cfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);

    //wysylanie danych
    sendto(cfd, message, strlen(message), 0, (const struct sockaddr*)&server_addr, server_len);
    printf("Wyslano dane\n");

    //odbieranie danych
    int rc = recvfrom(cfd, buff, sizeof(buff), 0, (struct sockaddr*)&server_addr, &server_len);
    buff[rc] = '\0';
    printf("Odebrano dane: %s\n", buff);

    close(cfd);
    return 0;
}
