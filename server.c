//
// Created by julekgwa on 2017/07/04.
//


#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <memory.h>
#include <unistd.h>

int main(int ac, char **av) {
    int sock_fd;
    int new_socket_fd;
    int port_number;
    ssize_t rval;
    int client_len;
    struct sockaddr_in server;
    struct sockaddr_in client;
    char buff[1024];

    if (ac < 2)
    {
        printf("Please provide port number\n");
        return (-1);
    }
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0)
    {
        printf("There was an error while creating socket");
        return (-1);
    }

    //TODO remove atoi with ft_atoi

    port_number = atoi(av[1]);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port_number);

    if (bind(sock_fd, (struct sockaddr *) &server, sizeof(server)) < 0) {
        printf("Error while binding");
        return (-1);
    }

    listen(sock_fd, 5);
    client_len = sizeof(client);
    while (42) {
        new_socket_fd = accept(sock_fd, (struct sockaddr *) &client, &client_len);
        if (new_socket_fd < 0) {
            printf("Error while accepting connection");
            break;
        }
        memset(buff, 0, sizeof(buff));
        if ((rval = recv(new_socket_fd, buff, sizeof(buff), 0)) < 0)
            printf("error reading stream\n");
        else if (rval == 0)
            printf("Ending connection\n");
        else
            printf("message: %s\n", buff);
        close(new_socket_fd);
    }
    return (0);
}