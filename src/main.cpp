#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#ifdef __WIN32__
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#endif

// Client
int main(int argc, char* argv[])
{
#ifdef __WIN32__
    WORD versionWanted = MAKEWORD(1, 1);
    WSADATA wsaData;
    WSAStartup(versionWanted, &wsaData);
#endif

    // TCP socket for serving the HTTP server
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Setup socket address
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9003);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Setup a connection
    int success = connect(tcp_socket, (sockaddr*) &server_address, sizeof(server_address));
    if (success < 0)
    {
        printf("Error connecting socket: %d\n", WSAGetLastError());
    }

    // Receive some data
    char response[256] = {0};
    recv(tcp_socket, response, sizeof(response), 0);

    printf("Received response from server: %s\n", response);

    // Close the socket and the connection
#ifdef __WIN32__
    closesocket(tcp_socket);
    WSACleanup();
#else
    close(tcp_socket);
#endif

    return 0;
}
