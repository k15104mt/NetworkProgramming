#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<unistd.h>//closeを使うため
#include<string.h>
#include<stdlib.h>

#define BUF_SIZE 256 //マクロ

void DieWithError(char *ErrorMessage){
	perror(ErrorMessage);//標準エラー出力にエラーメッセージを出す
	exit(1);//≒終了ステータス。エラーの時は１以上を返す
	
}
void commun(int sock){//原則としてプログラムは上から下に読み込まれるので、どういう関数かを教えるこの関数はmainの上に書いたほうがよい
	char buf[BUF_SIZE];
	int len_r;
	char *message = "banana banana banana banana banana banana banana banana banana banana banana";
	//send(sock,message,strlen(message),0);
	
	if(send(sock,message,strlen(message),0)!=strlen(message))DieWithError("send()send a message of unexpected bytes");
	
	if(len_r = recv(sock,buf,BUF_SIZE,0)<=0)DieWithError("recv()failed");
	
	buf[len_r] = '\0';//nul
	printf("%s\n",buf);//%s 文字列の出力
}


//send関数の引数　ソケットディスクリプタ、メッセージ、メッセージの文字数、0(固定)

int main(int argc,char**argv){
	
	if(argc != 3)DieWithError("arduments is not available");
	char *server_ipaddr = argv[1];//char *server_ipaddr = "10.13.64.20";
	int server_port = atoi(argv[2]);//int server_port = 10001;
	int sock = socket(PF_INET,SOCK_STREAM,0);//通信用の設備を開く
	if(sock < 0)DieWithError("soclet()failed");
	
	struct sockaddr_in target;
	
	target.sin_family = AF_INET;
	
	//target.sin_addr.s_addr = inet_addr("10.13.64.20");
	//target.sin_port = htons(10001);
	
	target.sin_addr.s_addr = inet_addr("server_ipaddr");
	target.sin_port = htons(server_port);
	
	if(connect(sock,(struct sockaddr*)&target,sizeof(target))<0)DieWithError("connect()failed");
	
	commun(sock);
	//printf("sock is %d",sock);
	close(sock);	//終了時に閉じる

	return 0;
}



