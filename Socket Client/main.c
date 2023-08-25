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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main () {

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed.\n");
        return 1;
    }
    int socketFD = createTCPIpv4Socket();

    struct sockaddr_in * address = createIpv4Address("10.10.15.8", 2000);


    int result =connect(socketFD, (const struct sockaddr *) address, sizeof (*address));

    if (result == 0) {
        printf("Connection Successful \n");
    } else {
        printf("Unsuccessful");
    }

    char* message;

    message = "GET \\ HTTP/1.1\r\nHost:google.com\r\n\r\n";
    send(socketFD,message, strlen(message),0);

    char buffer[1024];
    recv(socketFD,buffer,1024,0);

    printf("Response was %s\n",buffer);
    WSACleanup();

    return 0;
}


//int main() {
//    WSADATA wsaData;
//    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
//        printf("WSAStartup failed.\n");
//        return 1;
//    }
//
//    char hostname[256];
//    if (gethostname(hostname, sizeof(hostname)) != 0) {
//        printf("Error getting hostname.\n");
//        WSACleanup();
//        return 1;
//    }
//
//    struct addrinfo* result = NULL;
//    struct addrinfo hints = { 0 };
//    hints.ai_family = AF_INET; // IPv4
//    hints.ai_socktype = SOCK_STREAM;
//
//    if (getaddrinfo(hostname, NULL, &hints, &result) != 0) {
//        printf("Error getting address info.\n");
//        WSACleanup();
//        return 1;
//    }
//
//    struct sockaddr_in* localAddr = (struct sockaddr_in*)result->ai_addr;
//    char ipStr[INET_ADDRSTRLEN];
//    inet_ntop(AF_INET, &(localAddr->sin_addr), ipStr, INET_ADDRSTRLEN);
//
//    printf("Local host IP address: %s\n", ipStr);
//
//    freeaddrinfo(result);
//    WSACleanup();
//    return 0;
//}










