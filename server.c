#include<sys/scket.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

#define BUF_SIZE 256

void DieWithError(char *ErrorMessage){
	perror(ErrorMessage);
	exit(1);
}

void commun(int sock){
	char buf[BUF_SIZE];
	int len_r;
	if ((len_r = recv(sock, buf, BUF_SIZE, 0)) <= 0)
		DieWithError("recv()failed");
	buf[len_r] = '\0';
	printf("%d\n",buf);
	if (send(sock, buf, strlen(buf), 0) != strlen(buf))
		DieWithError("send() sent a message of unexpected byes");
}

int main(int argc, char **argv){
	int servSock = socket(PF_INET, SOCK_STREAM, 0);
	struct sockaadr_in servAddress;
	int cliSock;
	struct sockaddr_in clientAddress;
	unsigned int szClientAddr.
		servAddress.sin_family = AF_INET;
	servAddress.sin_addr.s_addr = htonl(NADDR_ANY);
	servAddress.sin_port = htones(10001);
	bind(servSock, (struct sockaadr*)&servAddress, sizeof(servAddress));
	listen(servSock,5);
	while (1){
		sz ClientAddr = sizeof(clientAddress);
		cliSock = accept(ser);
		commun(cliSock);
	}
	close(servSock);
	return 0;
}