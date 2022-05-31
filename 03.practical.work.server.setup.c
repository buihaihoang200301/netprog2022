#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>   
int main () {
    int sockfd, clen, clientfd;
    struct sockaddr_in saddr, caddr;
    unsigned short port = 8784;

    if ((sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error");

    }
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(port);
    
    printf("Bind to port %hd\n",port);
    
    if (bind(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0) {
	    printf("Error");
    
    }
    if (listen(sockfd, 5) < 0) {
        printf("Error");
    }
    
    clen=sizeof(caddr);
    if ((clientfd=accept(sockfd, (struct sockaddr *) &caddr, &clen)) < 0) {
        printf("Error");

    } else {
    printf("Connected\n");
    return 0;
    }
 }
