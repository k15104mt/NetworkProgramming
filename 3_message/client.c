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

void my_scanf(char *buf, int num_letter)
{
    char format[20];
    sprintf(format, "%s%d%s", "%", num_letter, "s%*[^\n]");
    scanf(format, buf);
    getchar();
}

void read_until_delim(int sock, char *buf, char delimiter, int max_length)
{
    int len_r = 0;        // 受信文字数
    int index_letter = 0; // 受信文字数の合計

    while (index_letter < max_length - 1)
    {
        // 1文字だけ受信
        if ((len_r = recv(sock, buf + index_letter, 1, 0)) <= 0)
            DieWithError("recv() failed");

        // 受信した文字が区切り文字ならループを抜ける
        if (buf[index_letter] == delimiter)
            break;
        else
            index_letter++;
    }
    // nullを末尾に追加
    buf[index_letter] = '\0';
}

void commun(int sock)
{
    char cmd[2] = "";
    char withdraw[MONEY_DIGHT_SIZE + 1];
    char deposit[MONEY_DIGHT_SIZE + 1];
    char msg[BUF_SIZE];

    printf("0:引き出し 1:預け入れ 2:残高照会 9:終了\n");
    printf("何をしますか？ > ");

    my_scanf(cmd, 1);

    switch (cmd[0])
    {
    case '0':
        printf("引き出す金額を入力してください > ");
        my_scanf(withdraw, MONEY_DIGHT_SIZE);

        sprintf(msg, "0_%s_", withdraw);
        break;
    case '1':
        printf("預け入れる金額を入力してください > ");
        my_scanf(deposit, MONEY_DIGHT_SIZE);

        sprintf(msg, "0_%s_", deposit);
        break;
    case '2':
        break;
    default:
    }
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