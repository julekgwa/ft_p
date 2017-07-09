//
// Created by julekgwa on 2017/07/08.
//

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>

#define ERROR -1
#define MAX_DATA 1024

void test() {
    char *args[2];

    args[0] = "/bin/ls";
    args[1] = NULL;
    if (execv(args[0], args) < -1)
        perror("execv");
}

void test2() {
    char *args[2];

    args[0] = "/bin/pwd";
    args[1] = NULL;
    if (execv(args[0], args) < ERROR)
        perror("execv");
}

void handle_client(char *data) {
    if (strncmp(data, "ls", strlen(data)) == 0) {
        test();
    } else
        test2();
}

int main(int ac, char **av, char **envp) {
    int socket_fd, len, client_fd;
    ssize_t data_len;
    struct sockaddr_in server, client;
    pid_t pid;
    int stdout_copy = dup(1);
    char data[MAX_DATA];

    if (ac < 2 || ac > 2) {
        printf("Usage: %s <Port number>\n", av[0]);
        exit(1);
    }

    //    socket
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == ERROR) {
        perror("socket: ");
        exit(-1);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(av[1]));
    server.sin_addr.s_addr = INADDR_ANY;
    bzero(&server.sin_zero, 8);

    //    bind
    len = sizeof(struct sockaddr_in);

    if ((bind(socket_fd, (struct sockaddr *) &server, len)) == ERROR) {
        perror("Bind");
        exit(-1);
    }

    //    listen
    listen(socket_fd, 5);
    int status;
    while (42) {
        //    accept
        if ((client_fd = accept(socket_fd, (struct sockaddr *) &client, (socklen_t *) &len)) == ERROR) {
            perror("accept");
            exit(-1);
        }
        printf("New client connected from port no %d and IP %s\n", ntohs(client.sin_port), inet_ntoa(client.sin_addr));
        close(1);
        data_len = 1;
        dup2(client_fd, 1);
        while (data_len) {
            data_len = recv(client_fd, data, MAX_DATA - 1, 0);
            if (data_len) {
                data[data_len] = '\0';
                pid = fork();
                if (pid == 0) {
                    handle_client(data);
                }
                wait(&status);
            }
        }
        close(client_fd);
        dup2(stdout_copy, 1);
        printf("Client disconnected\n");
        dup2(stdout_copy, 1);
    }
    return 0;
}
