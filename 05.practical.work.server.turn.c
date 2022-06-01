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
    char clim[1000], svm[1000];


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
        if (recv(clientfd, clim, sizeof(clim), 0)<0){
            printf("Can not receive \n");
        }

        printf("Client: %s \n", clim);

        printf("Send message: ");
        scanf("%s",svms);

        if (send(clientfd, svm, sizeof(svm), 0)<0){
            printf("Can not send\n");
        }    
    }
    return 0;
}
