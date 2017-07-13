/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 10:10:20 by julekgwa          #+#    #+#             */
/*   Updated: 2017/07/12 16:29:22 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <netinet/in.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio.h>

#define ERROR -1

int main(int ac, char **av, char **envp)
{
    struct termios term;
    t_stack hist;
    t_cmd cmd;
    t_env *envp_copy;
    struct sockaddr_in remote_server;
    int socket_fd;

    if (ac < 3 || ac > 3)
    {
        printf("Insufficient number of arguments. \n Usage: ./%s <IP Address Of Server> <Port Number>",av[0]);
        exit(1);
    }
    ft_create_stack(&hist, envp);
    envp_copy = copy_envp(4096, envp);
    ft_init_keyboard(&term, &ac, &av);
    signal(SIGINT, ft_ctrl_c_signal_handler);
    (void) envp_copy;

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == ERROR)
    {
        perror("socket");
        exit(-1);
    }

    remote_server.sin_family = AF_INET;
    remote_server.sin_port = htons(atoi(av[2]));
    remote_server.sin_addr.s_addr = inet_addr(av[1]);
    bzero(&remote_server.sin_zero, 8);

    if ((connect(socket_fd, (struct sockaddr *) &remote_server, sizeof(struct sockaddr_in))) == ERROR)
    {
        perror("connect");
        exit(-1);
    }
    cmd.fd = socket_fd;
    while (42)
    {
        prompt(&cmd, &hist);
        ft_process_slash_inhibitor(&cmd, &term);
        ft_complete_cmd(&cmd, &term);
        ft_putchar('\n');
        if (!ft_strequ(cmd.get_line, "") && ft_spaces_tabs(cmd.get_line))
            ft_send_data(&cmd, &term, &hist, cmd.fd);
        free(cmd.get_line);
    }
    return (0);
}
