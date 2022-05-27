#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h> 

int DNS(char*hostname,char*ip) {
    struct hostent *H;
    struct in_addr **Addrlist;
    if ((H = gethostbyname(hostname))==NULL) {
        herror("Error");
        return 1;
    }

    Addrlist = (struct in_addr **) H->h_addr_list;
    for (int i=0;Addrlist[i] != NULL;i++) {
        strcpy(ip,inet_ntoa(*Addrlist[i]));
        return 0;
    }
    return 1;
  
}


int main (int argc, char*argv[]) {
    if (argc<2) {
        printf("No hostport");
    }
    char *hostname = argv[1];
    char ip[100];
    DNS(hostname,ip);
    printf("%s resolve to %s",hostname,ip);
}