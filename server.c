/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 10:09:07 by julekgwa          #+#    #+#             */
/*   Updated: 2017/07/15 23:54:29 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void handle_client(char *data, t_env *envp, t_stack *hist, int client_fd)
{
    if (strcmp(data, "received") != 0)
        ft_pro_cmd(data, envp, hist);
    else
    {
        char s[] = "done";
        send(client_fd, s, strlen(s), 0);
    }
}

int main(int ac, char **av, char **envp)
{
    int socket_fd, len, client_fd;
    ssize_t data_len;
    struct sockaddr_in server, client;
    pid_t pid, pid2;
    int stdout_copy = dup(1);
    // char data[MAX_DATA];
    t_stack hist;
    t_env *envp_copy;

    ft_create_stack(&hist, envp);

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
    char *cmd;
    while (42) {
        //    accept
        if ((client_fd = accept(socket_fd, (struct sockaddr *) &client, (socklen_t * ) & len)) == ERROR) {
            perror("accept");
            exit(-1);
        } else {
            pid2 = fork();
            if (pid2 == 0) {
                printf("New client connected from port no %d and IP %s\n", ntohs(client.sin_port),
                       inet_ntoa(client.sin_addr));
                envp_copy = copy_envp(4096, envp);
                close(1);
                data_len = 1;
                dup2(client_fd, 0);
                dup2(client_fd, 1);
                dup2(client_fd, 2);
                while (data_len) {
                    cmd = read_cmd(client_fd);
                    if (EQUAL(cmd, "quit") || data_len == 0)
                    {
                        char s[] = "done";
        send(client_fd, s, strlen(s), 0);
        // data_len = 0;
        break;
                    }
                    if (cmd && data_len) {
                        // data[data_len] = '\0';
                        pid = fork();
                        if (pid == 0) {
                            handle_client(cmd, envp_copy, &hist, client_fd);
                        }
                        wait(&status);
                    }
                }
            }
            close(client_fd);
            dup2(stdout_copy, 1);
            printf("Client disconnected\n");
        }
    }
    return 0;
}
