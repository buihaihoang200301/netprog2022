#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<netdb.h>
#include <fcntl.h> 
#include <unistd.h>

int main(){

    int sockfd, clen, clientfd;
    struct sockaddr_in saddr, caddr;
    unsigned short port = 8784;
    char cliem[9999], svm[9999];

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
    printf("Connected \n");
    
    while (1){
        printf("Client : ");
        
        do{
            recv(clientfd, cliem, sizeof(cliem), 0);
            printf("%s", cliem);
            if (strcmp(cliem,"/quit\n")==0){
                printf("Disconected\n");
            }
        } while (cliem[strlen(cliem) - 1] != '\n');

        if (strcmp(svm,"/dc\n")==0){
                printf("Disconnected\n");
                close(clientfd);
                close(sockfd);
                return 0;
        }

        printf("Message to client: ");
        
        do{
            fgets(svm, 9999, stdin);
            if (strcmp(svm,"/dc\n")==0){
                send(clientfd, svm, strlen(svm) + 1, 0);
            }
            send(clientfd, svm, strlen(svm) + 1, 0);
        } while (svm[strlen(svm) - 1] != '\n');
    }
    return 0;
}
