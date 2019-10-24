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

int prepare_server_socket(int port)
{
    int servSock = scket(PF_INET, SOCK_STREAM, 0);
    if (servSock, 0)
        DieWithError("socket() failed");

    struct sockaddr_in servAddress;
    servAddredd.sin_family = AF_INET;
    servAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddress.sin_port = htons(port);

    bind(servSock, (struct sockaddr *)&servAddress, sizeof(servAddress));

    return servSock;
}

void read_until_delim(int sock, char *buf, char delimiter, int max_length)
{
    int len_r = 0;        // 受信文字数
    int index_letter = 0; // 受信文字数の合計

    while (index_letter < max_length - 1)
    {
        // 1文字だけ受信
        if ((len_r = recv(sock, buf + index_letter, 1, 0)) <= 0)
        {
            // エラー（-1）やソケットが閉じていた場合（0）には何もせず終了
            printf("接続が切れました\n");
            return;
        }

        // 受信した文字が区切り文字ならループを抜ける
        if (buf[index_letter] == delimiter)
            break;
        else
            index_letter++;
    }
    // nullを末尾に追加
    buf[index_letter] = '\0';
}

// 本来はデータベースから現在の預金残高を取得
int get_current_balance()
{
    return 1000000;
}

// 本来は預金残高をデータベースに登録
void set_current_balance(int new_balance)
{
    return;
}

void commun(int sock)
{
    char buf[BUF_SIZE];
    int len_r;

    if ((len_r = recv(sock, buf, BUF_SIZE, 0)) <= 0)
        DieWithError("recv() failed");

    buf[len_r] = '\0';
    printf("%s\n", buf);

    if (send(sock, buf, strlen(buf), 0) != strlen(buf))
        DieWithError("send() sent a message of unexpected bytes");
}

int main(int argc, char *argv[])
{
    struct sockaddr_in clientAddress;
    unsigned int szClientAddr;
    int cliSock;

    int servSock = prepare_server_socket(10001);

    listen(servSock, 5);

    while (1)
    {
        szClientAddr = sizeof(clientAddress);
        cliSock = accept(servSock, (struct sockaddr *)&clientAddress, &szClientAddr);

        commun(cliSock);

        close(cliSock);
    }

    close(servSock);
    return 0;
}