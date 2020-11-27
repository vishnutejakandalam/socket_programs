/*Include headder files*/
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    int index= -1;
    int sockfd, newsockfd,port_num,clilen;
    struct sockaddr_in serv_addr,cli_addr;
    char buffer[256];
    int n;
    /*Check weither the port is given or not*/
    if(argc < 2)
    {
        printf("YOU MISSED PORT NUMBER !\n");
        return 1;
    }
    /*Create data as arrays*/
    char* cur_name[6] = {"US Dollar","Canadian Dollar","Euro","British Pound","Japanese Yen","Swiss Franc"};
    char* password[6] = {"uCh781fY","Cfw61RqV","Pd82bG57","Crc51RqV","wD82bV67","G6M7p8az"};
    char* values[6] = {"11081.00","14632.87","9359.20","8578.96","1158748.55","10100.44"};
    /*Create a socket and check it*/
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if (sockfd < 0)
    {
        printf("ERROR CONNECTING A SOCKET");
        return 1;
    }
    else
        printf("SOCKET CONNECTED \n");
    bzero(&serv_addr,sizeof(serv_addr));
    port_num = atol(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(0);
    serv_addr.sin_port = htons(port_num);
    /*Bind our socet to a specific address and port*/
    if(bind(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) <0){
        printf("ERROR IN BINIDING SOCKET");
    }
    printf("Server started \n");
    printf("The address is %s on port %d \n",inet_ntoa(serv_addr.sin_addr),port_num);
    /*Start listening for requests*/
    if(listen(sockfd,3) < 0)
    {
        printf("Error in listening. \n");
    }
    else
    {
        printf("Listening... \n");
    }
    for(;;)
    {
    /*Get the sockcet details of newly connected client*/
    clilen = sizeof(cli_addr);

    newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
    if(newsockfd < 0)
    {
        printf("ERROR ON ACCEPT");
    }
    else
        printf("Connected to %s \n",inet_ntoa(cli_addr.sin_addr));
    bzero(buffer,sizeof(buffer));
    /*Read the buffer for Currency name*/
    n = read(newsockfd,buffer,sizeof(buffer));
    if(n<0)
        sleep(30);
    if(n<0)
        close(newsockfd);
    printf("%s \n ",buffer);
    buffer[strlen(buffer)-1] = '\0';
    int flag = 0;
    for(int i=0;i<6;i++)
    {   
        if (strcmp(buffer,cur_name[i]) == 0)
        {
            flag = 1;
            index = i;
        }
        if (flag == 1)
        {
            break;
        }
    }
    if (flag == 0)
    {   
        close(newsockfd);
    }
    write(newsockfd,"LETS CONTINUE!",sizeof("LETS CONTINUE!"));
    n = read(newsockfd,buffer,sizeof(buffer));
    if(n<0)
        sleep(30);
    if(n<0)
        close(newsockfd);
    
    buffer[strlen(buffer)-1] = '\0';
    if(strcmp(buffer,password[index]) == 0)
    flag = 0;
    if (flag == 1)
    {   
        write(newsockfd,'\0',1);
        close(newsockfd);
    }
    write(newsockfd,values[index],sizeof(values[index]));
    // write(newsockfd,"correct!",sizeof("correct!"));
    read(newsockfd,buffer,sizeof(buffer));
    if(strcmp(buffer,"quit") == 0)
    {
        write(newsockfd,"Good Bye..!",sizeof("Good Bye..!"));
        close(newsockfd);
    }
    }
   return 0;
}

