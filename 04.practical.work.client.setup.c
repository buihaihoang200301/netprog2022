#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>  
int main() {
	struct sockaddr_in saddr;
	struct hostent *h;
	int sockfd;
	unsigned short port = 8784;
	char domain[200];
	
	if ((sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Error");
	
	}	
	struct in_addr * address;
	printf("Enter the domain: ");
	scanf("%s",domain);
	
	if ((h=gethostbyname(domain)) == NULL) {
		printf("Unknown host!");
		}
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	memcpy((char *) &saddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
	saddr.sin_port = htons(port);

	if (connect(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0) {
		printf("Cannot connect");
	}else{
		printf("Connect successful\n");
	}
}
