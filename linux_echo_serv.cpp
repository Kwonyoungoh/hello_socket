# include <iostream>
# include <cstring>//<string.h>은 c언어에서 사용
# include <unistd.h>
# include <arpa/inet.h>
# include <sys/socket.h>
using namespace std;

# define BUF_SIZE 1024
void err_handling(char *message);

int main(int argc, char* argv[])
{
    int serv_sock, clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    char message[BUF_SIZE];
    char temp[20];
    int str_len, i;

    if (argc != 2)
    {
        std::cout << "Usage : " << argv[0] << " <port>" << std::endl;
        exit(1);
    }

    //소켓생성 socket
    serv_sock=socket(PF_INET, SOCK_STREAM, 0);
    if ( serv_sock == -1)
    {
        err_handling("socket() err");
    }

    //해당 메모리값 초기화
    memset(&serv_addr, 0, sizeof(serv_addr));
    //주소정보 초기화
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(argv[1]));

    //bind
    if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1)
    {
        err_handling("bind() err");
    }
    //listen
    if (listen(serv_sock,5)==-1)
    {
        err_handling("listen() err");
    }
    
    clnt_addr_size=sizeof(clnt_addr);
    
    //accept
    for(i=0; i<5; i++)
    {
        clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_addr, &clnt_addr_size);
        if (clnt_sock ==-1)
        {
            err_handling("accept() err");
        }
        else
        {
           std:: cout  << "Connected Client : " << i+1 << std::endl;
           inet_ntop( AF_INET, &clnt_addr.sin_addr.s_addr , temp, sizeof(temp));
           std:: cout  << "Client IP: " << temp << std::endl;
        }
        while ((str_len=read(clnt_sock, message, BUF_SIZE))!=0)
        {
            std:: cout << "Received Message :  "<< message << std::endl;
            write(clnt_sock, message, str_len);
        }

        close(clnt_sock);
        std::cout << "Client Closed" << std::endl;
    }
    close(serv_sock);
    return 0;
}

void err_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n',stderr);
    exit(1);
}