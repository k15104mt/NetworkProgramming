#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF_SIZE 256
#define MONEY_DIGHT_SIZE 10

void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}

int prepare_client_socket(char *ipaddr, int port)
{
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        DieWithError("socket() failed");

    struct sockaddr_in target;
    target.sin_family = AF_INET;
    target.sin_addr.s_addr = inet_addr(ipaddr);
    target.sin_port = htons(port);
    if (connect(sock, (struct sockaddr *)&target, sizeof(target)) < 0)
        DieWithError("connect() failed");

    return sock;
}

void commun(int sock)
{
    char buf[BUF_SIZE];
    int len_r;
    char *message = "Hello server!";

    if (send(sock, message, strlen(message), 0) != strlen(message))
        DieWithError("send() sent a message of unexpected bytes");

    if ((len_r = recv(sock, buf, BUF_SIZE, 0)) <= 0)
        DieWithError("recv() failed");

    buf[len_r] = '\0';
    printf("%s\n", buf);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
        DieWithError("the number of arguments is unexpected");

    int sock = prepare_client_socket(argv[1], atoi(argv[2]));

    commun(sock);
    close(sock);
    return 0;
}