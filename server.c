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
//int		ft_advanced_com2(t_cmd *cmd, t_env *envp, t_stack *hist);
//
//void	ft_multi_com2(t_cmd *cmd, t_env *envp, t_stack *hist)
//{
//    t_cmd	*tmp;
//    char	**split_com;
//    int		i;
//
//    tmp = (t_cmd *)malloc(sizeof(t_cmd) + 1);
//    split_com = SPLIT(cmd->get_line, ';');
//    i = 0;
//    if (split_com)
//    {
//        while (split_com[i])
//        {
//            tmp->get_line = ft_strdup(split_com[i]);
//            tmp->user_comm = SPLIT(tmp->get_line, ' ');
//            ft_advanced_com2(tmp, envp, hist);
//            free_cmd(tmp);
//            i++;
//        }
//    }
//    if (split_com)
//        freecopy(split_com);
//    free(tmp);
//}
//
//int		ft_advanced_com2(t_cmd *cmd, t_env *envp, t_stack *hist)
//{
//    char	*exec;
//    char	**search;
//    int		val;
//
//    val = -1;
//    search = SPLIT(cmd->get_line, ' ');
//    if (CONTAINS(cmd->get_line, ';'))
//        ft_multi_com2(cmd, envp, hist);
//    else if (SEARCH(search[0]) && !CONTAINS(cmd->get_line, '>'))
//        val = ft_execute_commands(search, cmd->get_line, envp, hist);
//    else if ((exec = ft_build_exec(cmd->user_comm, hist)))
//        val = ft_send_cmd_to_server(exec, cmd->user_comm, envp->list);
//    else if (ft_is_execute(cmd->user_comm[0]))
//        val = ft_send_cmd_to_server(cmd->get_line, cmd, envp->list);
//    else
//        ft_print_error(cmd->user_comm[0], 0);
//    freecopy(search);
//    return (val);
//}

void test(char *data, char **envp) {
    char **sp = SPLIT(data, ' ');
    ft_send_cmd_to_server(sp[0], sp, envp);
}

void test2(char *data, char **envp) {
    char **sp = SPLIT(data, ' ');
    ft_send_cmd_to_server(sp[0], sp, envp);
}

void handle_client(char *data, char **envp, t_stack *hist) {
//    if (strncmp(data, "ls", strlen(data)) == 0) {
//        test(data,envp);
//    } else
//        test2(data, envp);
    char *exec;
    char **split;
    split = SPLIT(data, ' ');
    if ((exec = ft_build_exec(split, hist))) {
        ft_send_cmd_to_server(exec, split, envp);
    } else if (ft_is_execute(split[0])) {
        ft_send_cmd_to_server(split[0], split, envp);
    }else
        ft_print_error(split[0], 0);
}

int main(int ac, char **av, char **envp) {
    int socket_fd, len, client_fd;
    ssize_t data_len;
    struct sockaddr_in server, client;
    pid_t pid;
    int stdout_copy = dup(1);
    char data[MAX_DATA];
    t_stack			hist;

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
                    handle_client(data, envp, &hist);
                }
                wait(&status);
            }
        }
        close(client_fd);
        dup2(stdout_copy, 1);
        printf("Client disconnected\n");
        //dup2(stdout_copy, 1);
    }
    return 0;
}
