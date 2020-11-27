#include <arpa/inet.h>
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int n, sockfd, port_num;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];
    if (argc < 3)
    {
        printf("YOU MISSED SOMETHING..! \n");
        return 1;
    }
    port_num = atol(argv[2]);
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if (sockfd < 0)
    {
        printf("UNABLE TO CREATE SOCKET :() \n");
    }
    else
    {
        printf("Socket created.. :) \n");
    }
    server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        printf("WRONG HOST NAME \n");
    }
    bzero(&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcmp((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(port_num);
    if (connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0){
        printf("UNABLE TO CONNECT \n");
        return 0;
    }
    else 
        printf("CONNECTED TO SERVER \n");
    printf("Enter the currency name: \n");
    char cur_name[20];
    fgets(cur_name,sizeof(cur_name),stdin);
    write(sockfd,cur_name,sizeof(cur_name));
    n = read(sockfd,buffer,sizeof(buffer));
    if (strlen(buffer) == 0 )
    {
        printf("You entered wrong currency name! \n");
        return 0;
    }
    printf("%s \n ",buffer);
    char password[16];
    printf("Enter the password: \n");
    fgets(password,sizeof(password),stdin);
    write(sockfd,password,sizeof(password));
    bzero(buffer,sizeof(buffer));
    n = read(sockfd,buffer,sizeof(buffer));
if (strlen(buffer) == 0 )
    {
        printf("You entered wrong Password! \n");
        return 0;
    }
    printf("the result is %s \n",buffer);
    write(sockfd,"quit",sizeof("quit"));
    read(sockfd,buffer,sizeof(buffer));
    printf("%s \n",buffer);


    return 0;
}
