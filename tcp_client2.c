#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    int cfd;
    struct sockaddr_in server_addr;
    char buff[256];

    //socket
    cfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);

    //laczenie (connect)
    connect(cfd, (const struct sockaddr*)&server_addr, sizeof(server_addr));
    printf("Łączenie z serwerem...\n");

    //wysylanie danych
    write(cfd, "tu klient", strlen("tu klient"));
    printf("Wyslano dane\n");

    //odbieranie danych
    read(cfd, buff, sizeof(buff));
    printf("Odebrano dane: %s\n", buff);

    close(cfd);
    return 0;

}
