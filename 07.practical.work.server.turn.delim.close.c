#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<netdb.h>
int main(){

    int sockfd, clen, clientfd;
    struct sockaddr_in saddr, caddr;
    unsigned short port = 8784;
    char cliem[1000], ms[1000];

    if ((sockfd =  socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error\n");
        return 1;
    }

    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(port);


    if (bind(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0){
        printf("Error\n");  
        return 1;
    }

    if (listen(sockfd, 5) < 0){
        printf("Error\n");  
        return 1;
    }

 
    clen = sizeof(caddr);
    if ((clientfd = accept(sockfd, (struct sockaddr *) &caddr, &clen)) < 0) {
        printf("Error\n"); 
        return 1;
    }
    printf("Connected\n");
    
    while (1){
        if (recv(clientfd, cliem, sizeof(cliem), 0)<0){
            printf("Can not get client message \n");
        }

        while (1){
            int i=0;
            while (cliem[i] != '\n'){
                ms[i]=cliem[i];
                i+=1;
            }
            printf("Client: %s \n", ms);
            break;
        }
	if (strcmp(serverms,"/dc\n\0")==0){
                shutdown(sockfd,SHUT_RDWR);
                shutdown(clientfd, SHUT_RDWR);
                printf("Server disconnected\n");
                close(sockfd);
                close(clientfd);
                return 0;
            }
	
        printf("Messages to client: ");
        fgets( ms, 1000, stdin);
        ms[strlen(ms)-1]='\0';

        if (send(clientfd, ms, strlen(ms)+1, 0)<0){
            printf("Error \n");
        }    
    }
    return 0;
}
