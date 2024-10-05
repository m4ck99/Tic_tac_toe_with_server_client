#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <netdb.h>
#include "funcs.h"
#define PORT 8082
#define SERVER "X"
#define CLIENT "O"


char grid[9] = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};
int player = 1, count = 0;
char ch[3];

int main(void) {
    unsigned short int dec;
    int sockfd, n, newsockfd, portno;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    printf("(1) Host or (2) join?: ");
    scanf("%hu", &dec);
    if (dec == 1) { 
        player = 1;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        memset((char *)&serv_addr, 0, sizeof(serv_addr));
        portno = PORT;
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(portno);
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
        listen(sockfd, 5);
        clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    }
    else {
        player = 2;
        char ip[INET_ADDRSTRLEN];
        printf("Enter IP: ");
        scanf("%s", ip);
        struct hostent *server;
        portno = PORT;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        server = gethostbyname(ip);
        memset((char *)&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
        serv_addr.sin_port = htons(portno);
        connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    }
    print_grid(grid);
    while (1) {
        if (count == 9)
            break;
        if (dec != 1) {
            n = read(sockfd, ch, sizeof(ch));
            set_input(ch, SERVER, grid, 2);
            check(grid, 1);
            do {
                printf("Enter position: ");
                scanf("%s", ch);
            }
            while (validate(ch));
            n = write(sockfd, ch, sizeof(ch));
            set_input(ch, CLIENT, grid, 1);
            check(grid, 2);
        }
        else {
            do {
                printf("Enter position: ");
                scanf("%s", ch);
            }
            while (validate(ch));
            n = write(newsockfd, ch, sizeof(ch));
            set_input(ch, SERVER, grid, 1);
            check(grid, 2);
            n = read(newsockfd, ch, sizeof(ch));
            set_input(ch, CLIENT, grid, 2);
            check(grid, 1);
        }
        count += 1;
    }
    close(newsockfd);
    close(sockfd);
    return 0;
}
