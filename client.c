//
// Created by julekgwa on 2017/07/04.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include <stdio.h>

int main(int ac, char **av) {
    int socket_fd;
    int port_number;
    struct sockaddr_in server;
    struct hostent *host;
    char buff[1024];

    if (ac < 3) {
        printf("Please provide hostname and port number\n");
        return (-1);
    }

    port_number = atoi(av[2]);
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        printf("Error opening socket");
        return (-1);
    }

    host = gethostbyname(av[1]);
    if (host == NULL) {
        printf("host not found");
        return (-1);
    }

    memset((char *) &server, 0, sizeof(server));
    server.sin_family = AF_INET;
    memcpy(&server.sin_addr, host->h_addr, host->h_length);
    server.sin_port = htons(port_number);
    if (connect(socket_fd, (struct sockaddr *) &server, sizeof(server))) {
        printf("Error connecting");
        return (-1);
    }

    printf("Enter a message: ");
    memset(buff, 0, sizeof(buff));
    fgets(buff, 1024, stdin);
    write(socket_fd, buff, strlen(buff));
    return (0);
}