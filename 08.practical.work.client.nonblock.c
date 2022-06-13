#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<netdb.h>
#include <fcntl.h> 
#include <unistd.h>

int main(){
    char input[200];
    struct sockaddr_in saddr;
    struct hostent *h;
    int sockfd;
    unsigned short port = 8784;
    char cliem[9999], svm[9999];

    if ((sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Cannot connect \n");
        return 1;
    }
    
    struct in_addr *address;
    printf("Enter host domain name: ");
    fgets(input, 200, stdin);
    input[strlen(input) - 1] = '\0';

    if ((h=gethostbyname(input)) == NULL) {
        printf("Unknown host \n");
        return 1;
    }

    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    memcpy((char *) &saddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
    saddr.sin_port = htons(port);

    if (connect(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0) {
        printf("Cannot connect\n");
        return 1;
    }
    printf("Connected\n");
    
    while (1){
        printf("Message : ");

        do{
            fgets(cliem, 9999, stdin);
            if (strcmp(cliem,"/quit\n")==0){
                send(sockfd, cliem, strlen(cliem) + 1, 0);
                close(sockfd);
                printf("Disconnected \n");
                return 0;
            }
            send(sockfd, cliem, strlen(cliem) + 1, 0);
        } while (cliem[strlen(cliem) - 1] != '\n');
        
        printf("Server message: ");

        do{
            recv(sockfd, svm, sizeof(svm), 0);
            if (strcmp(svm,"/dc\n")==0){
                close(sockfd);
                printf("Disconected\n");
                return 0;
            }
            printf("%s", svm);
        } while (svm[strlen(svm) - 1] != '\n');
    }
    return 0;
}
