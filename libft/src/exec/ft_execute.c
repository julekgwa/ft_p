/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 12:37:20 by julekgwa          #+#    #+#             */
/*   Updated: 2017/07/12 20:31:59 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_is_executable(const char *path)
{
    struct stat path_stat;

    ft_memset(&path_stat, 0, sizeof(struct stat));
    if (stat(path, &path_stat) == 0 && path_stat.st_mode & S_IXUSR)
        return (1);
    return (0);
}

int ft_is_dir(const char *path)
{
    struct stat path_stat;

    ft_memset(&path_stat, 0, sizeof(struct stat));
    if (stat(path, &path_stat) < 0)
        return (0);
    return (S_ISDIR(path_stat.st_mode));
}

void ft_rm_quotes_array(char *av[], char **cmd)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (cmd[i])
    {
        av[j++] = ft_rm_quotes(cmd[i]);
        i++;
    }
    av[j] = 0;
}

void display_response(int fd)
{
    ssize_t len;
    char output[BUFFER];
    char feedback[] = "received";

    len = BUFFER;
    while (len)
    {
        len = recv(fd, output, BUFFER, 0);
        if (len)
        {
            output[len] = '\0';
            if (strncmp(output, "done", 4) == 0) 
            	break;
            if (len < BUFFER)
            	send(fd, feedback, strlen(feedback), 0);
            printf("%s", output);
        }
    }
}

void send_to_server(char *cmd, int server_fd)
{
    send(server_fd, cmd, strlen(cmd), 0);
    display_response(server_fd);
}

int ft_send_data(t_cmd *cmd, struct termios *term, t_stack *hist, int fd)
{
    if (EQUAL(cmd->get_line, "quit"))
    {
        free_cmd(cmd);
        ft_free_hash_table(hist->hash);
        ft_close_keyboard(term);
        exit(0);
    }
    send_to_server(cmd->get_line, fd);
    return (1);
}

int ft_execute_cmd(char *com, char **cmd, char **envp)
{
    int exec;
    char *av[BUFF_SIZE];

    ft_memset(av, 0, sizeof(char *) * BUFF_SIZE);
    ft_rm_quotes_array(av, cmd);
    exec = execve(com, &av[0], envp);
    if (exec == -1 && !ft_is_executable(com))
        ft_print_error(com, 1);
    else if (exec == -1 && ft_is_dir(com))
        ft_print_error(com, 2);
    return (exec);
}

int ft_send_cmd_to_server(char *com, char **cmd, char **envp)
{
    int exec;
    char *av[BUFF_SIZE];

    ft_memset(av, 0, sizeof(char *) * BUFF_SIZE);
    ft_rm_quotes_array(av, cmd);
    exec = execve(com, &av[0], envp);
    if (exec == -1 && !ft_is_executable(com))
        ft_print_error(com, 1);
    else if (exec == -1 && ft_is_dir(com))
        ft_print_error(com, 2);
    return (exec);
}

int ft_set_cmd_to_null(char **cmd, int *pos)
{
    if (ft_handle_ctrl_c(0) == 1)
    {
        ft_memset(*cmd, 0, BUFF_SIZE);
        ft_strcpy(*cmd, "");
        ft_handle_ctrl_c(2);
        *pos = 0;
        return (0);
    }
    return (1);
}
