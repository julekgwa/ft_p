/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 10:10:20 by julekgwa          #+#    #+#             */
/*   Updated: 2017/07/15 18:04:30 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_p.h"
#include <netinet/in.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio.h>

#define ERROR -1

// int display_response(int fd)
// {
//     char *feedback;
//     // ssize_t len;
//     // char output[BUFFER];
//     // char feedback[] = "received";

//     // len = BUFFER;
//     // while (len)
//     // {
//     //     len = recv(fd, output, BUFFER, 0);
//     //     if (len)
//     //     {
//     //         output[len] = '\0';
//     //         if (strncmp(output, "done", 4) == 0) 
//     //             break;
//     //         if (len < BUFFER)
//     //             send(fd, feedback, strlen(feedback), 0);
//     //         printf("%s", output);
//     //     }
//     // }
//     feedback = read_cmd(fd);
//     if (EQUAL(feedback, "done"))
//         return (1);
//     printf("%s\n", feedback);
//     return (0);
// }

// int send_to_server(char *cmd, int server_fd)
// {
//     printf("%s\n", "Connected");
//     send(server_fd, cmd, strlen(cmd), 0);
//     return display_response(server_fd);
// }

int ft_send_data(t_cmd *cmd, struct termios *term, t_stack *hist, int fd)
{
    int put_get;

    if ((put_get = ft_check_put_get(cmd->get_line)) == 1)
        return (0);
    if (put_get == 2)
        ft_upload_file(cmd->get_line, fd);
    else
        put_get = send_to_server(cmd->get_line, fd);
    printf("%s\n", "Disconnected");
    if (EQUAL(cmd->get_line, "quit") || put_get == 1)
    {
        free_cmd(cmd);
        ft_free_hash_table(hist->hash);
        ft_close_keyboard(term);
        exit(0);
    }
    return (1);
}

int ft_check_put_get(char *cmd)
{
    char **check;

    check = SPLIT(cmd, ' ');
    if (!EQUAL(check[0], "put") && !EQUAL(check[0], "get"))
        return (0);
    if (ft_array_len(check) < 2)
    {
        printf("%s\n", "missing file name");
        freecopy(check);
        return (1);
    }
    return (2);
}

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
        printf("Insufficient number of arguments. \n Usage: ./%s <IP Address Of Server> <Port Number>", av[0]);
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
