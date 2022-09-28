# include <iostream>
# include <cstring>//<string.h>은 c언어에서 사용
# include <unistd.h>
# include <arpa/inet.h>
# include <sys/socket.h>
using namespace std;

# define BUF_SIZE 1024
void err_handling(char *message);

//argc 인자 갯수 변수 argv 인자 저장 변수
int main(int argc, char *argv[]) 
{

	int sock;
	char message[BUF_SIZE];
	struct sockaddr_in serv_addr;
	socklen_t clnt_addr_size;
	int str_len;

	//인자로 ip와 포트번호를 입력받는다.
	if (argc!=3)
	{
		std::cout << "Usage : "<< argv[0] << " <IP> <port>" << std::endl;
		exit(1);
	}
	
	//소켓생성
	//PF_INET = IPv4
	//SOCK_STREAM = TCP
	//SOCK_DGRAM = UDP
	sock=socket(PF_INET, SOCK_STREAM, 0);
	//실패시 -1 리턴
	if (sock == -1)
		 err_handling("socket() error");
	
	//메모리 초기화
	memset(&serv_addr,0,sizeof(serv_addr));
	//주소정보 설정
	serv_addr.sin_family=AF_INET;
	//inet_addr, inet_ntoa 주소변환 함수 네트워크바이트 형태 변환시 addr 반대는 ntoa
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	//대부분의 x86 데스크톱 컴퓨터는 리틀엔디언, 네트워크에선 주소를 빅 엔디언 그래서 htons로 바꿔준다.
	serv_addr.sin_port=htons(atoi(argv[2]));

	//설정한 소켓에 연결 요청
	if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
	{
		 err_handling("connect() err");
	}
	else 
		puts("Server Connection success.");
	while (1)
	{
		fputs("Input message(Q to quit) : ",stdout);
		fgets(message, BUF_SIZE, stdin);

		if(!strcmp(message,"Q\n"))
		{
			break;
		}
		
		write(sock, message, strlen(message));
		//read함수는 읽어온 바이트수를 반환함
		str_len=read(sock, message, BUF_SIZE-1);
		message[str_len]=0;
		std::cout << "Message from server : " << message << std::endl;
	}

	close(sock);
	puts("Closed.");
	return 0;
}

void err_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n',stderr);
    exit(1);
}
