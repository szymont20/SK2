#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define PORT 1234

// usuwanie zombie
void childend(int signo) {
    wait(NULL);
}

int main() {

    int sfd, cfd;
    struct sockaddr_in server_addr, client_addr;
    char buff[256];
    int on = 1;

    signal(SIGCHLD, childend);

    //socket
    sfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    //bind
    bind(sfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    //listen
    listen(sfd, 3);
    printf("Listening...\n");

    while (1) {
        socklen_t client_len = sizeof(client_addr);

        //accept
        cfd = accept(sfd, (struct sockaddr*)&client_addr, &client_len);
        printf("Połączenie od: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        // Tworzenie procesu potomnego
        if (fork() == 0) {
            close(sfd);

            //odbieranie
            read(cfd, buff, sizeof(buff));
            printf("Odebrano dane: %s\n", buff);

            //wysylanie
            write(cfd, "tu serwer", strlen("tu serwer"));

            close(cfd);
            exit(0); //zakonczenie procesu potomnego
        }

        close(cfd);
    }

    close(sfd);
    return 0;
}
