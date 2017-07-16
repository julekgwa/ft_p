/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 10:10:20 by julekgwa          #+#    #+#             */
/*   Updated: 2017/07/16 09:00:23 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

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
    if (EQUAL(check[0], "put"))
        return (2);
    return (3);
}

void    ft_check_args(int ac, char *prog)
{
    if (ac < 3 || ac > 3)
    {
        printf("Insufficient number of arguments. \n");
        printf("Usage: ./%s <IP Address Of Server> <Port Number>\n", prog);
        exit(1);
    }
}

int main(int ac, char **av, char **envp)
{
    struct termios term;
    t_stack hist;
    t_cmd cmd;
    t_env *envp_copy;

    ft_check_args(ac, av[0]);
    ft_create_stack(&hist, envp);
    envp_copy = copy_envp(4096, envp);
    ft_init_keyboard(&term, &ac, &av);
    signal(SIGINT, ft_ctrl_c_signal_handler);
    cmd.fd = ft_socket();
    ft_connect(cmd.fd, av[2], av[1], envp_copy);
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
