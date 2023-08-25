#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <malloc.h>


int createTCPIpv4Socket();
int createTCPIpv4Socket() { return socket(AF_INET, SOCK_STREAM, 0); }

struct sockaddr_in* createIpv4Address(char *ip, int port);
struct sockaddr_in* createIpv4Address(char *ip, int port) {

    struct sockaddr_in * address = malloc(sizeof (struct sockaddr_in));
    address->sin_family = AF_INET;
    address->sin_port = htons(port);
    if (strlen(ip) == 0 ){
        address->sin_addr.s_addr = INADDR_ANY;
    } else{
        inet_pton(AF_INET,ip,&address->sin_addr.s_addr);
    }
    return address;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main () {

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed.\n");
        return 1;
    }


    int serverSocketFD = createTCPIpv4Socket();

    struct sockaddr_in * serverAddress = createIpv4Address("", 2000);

    int result = bind(serverSocketFD,(const struct sockaddr *) serverAddress,sizeof (*serverAddress));

    if (result == 0) {
        printf("Connection Successful \n");
    } else {
        printf("Unsuccessful");
    }

    int listenResult = listen(serverSocketFD,10);

    struct sockaddr_in clientAddress;
    int clientAddressSize = sizeof (struct sockaddr_in);
    int clientSocketFD = accept(serverSocketFD, (struct sockaddr *) &clientAddress, &clientAddressSize);

    char buffer[1024];
    recv(clientSocketFD,buffer,1024,0);

    printf("Response was %s\n",buffer);

    WSACleanup();

    return 0;
}










