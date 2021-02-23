#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>

#ifdef __WIN32__
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#endif

int main(int argc, char* argv[])
{
#ifdef __WIN32__
    WORD versionWanted = MAKEWORD(1, 1);
    WSADATA wsaData;
    WSAStartup(versionWanted, &wsaData);
#endif

    char message[256] = "Hello world! (from your friendly neighbourhood TCP server)\n";

    // Setup server TCP socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9003);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind the socket to the IP and port
    bind(server_socket, (sockaddr*) &server_address, sizeof(server_address));

    // Start server listening
    listen(server_socket, 5);

    // Create client socket
    int client_socket = accept(server_socket, 0, 0);

    // Send message to the client
    send(client_socket, message, sizeof(message), 0);

#ifdef __WIN32__
    closesocket(server_socket);
    WSACleanup();
#else
    close(server_socket);
#endif

    return 0;
}
