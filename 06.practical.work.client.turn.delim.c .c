#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<netdb.h>

int main(){
    char input[200];
    struct sockaddr_in saddr;
    struct hostent *h;
    int sockfd;
    unsigned short port = 8784;
    char ms[1000], svm[1000];

    if ((sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error \n");
        return 1;
    }
    
    struct in_addr *address;
    printf("Enter host domain name: ");
    fgets(input, 200, stdin);
    input[strlen(input) - 1] = '\0';

    if ((h=gethostbyname(input)) == NULL) {
        printf("Error \n");
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
    printf("Connected \n");
    
    while (1){

        printf("Messages: ");
        fgets(ms, 1000, stdin);

        if (send(sockfd, ms, strlen(ms)+1, 0)<0){
            printf("Can not send to server \n");
        }

        if (recv(sockfd, svm, sizeof(svm), 0)<0){
            printf("Can not get server message \n");
        }
        while (1){
            int i=0;
            while (svm[i] != '\n'){
                ms[i]=svm[i];
                i+=1;
            }
            printf("Server: %s \n", ms);
            break;
        }

    }


    return 0;
}
