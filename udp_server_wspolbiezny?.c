#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define PORT 1234

//usuwanie zombie
void chldend(int signo) {
    wait(NULL);
}

int main() {

    int sfd;
    int on = 1;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buff[256];
    char *message = "tu serwer";

    signal(SIGCHLD, chldend);

    //socket
    sfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    //bind
    bind(sfd, (const struct sockaddr*)&server_addr, sizeof(server_addr));
    printf("Bindowanie\n");

    while(1) {

        //odbieranie danych
        int rc = recvfrom(sfd, buff, sizeof(buff), 0, (struct sockaddr*)&client_addr, &client_len);
        buff[rc] = '\0';
        printf("Odebrano dane: %s\n", buff);

        if (fork() == 0) {

            //wysylanie danych
            sendto(sfd, message, strlen(message), 0, (const struct sockaddr*)&client_addr, client_len);
        }
        printf("Wyslano dane\n");

        exit(0); //zakonczenie procesu potomnego

    }

    close(sfd);
    return 0;
}
