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
char    *ft_get_logical_sep(char *line);
void    split_by_word(char av[][BUFF_SIZE], char **arr, char *word);
int     ft_pro_cmd2(char *cmd, char  **envp, t_stack *hist);
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

int     ft_execute2(char *command, char *cmd, char **envp, t_stack *hist)
{
    pid_t   pid;
    int     status;
    int     value;

    value = 0;
    if ((pid = fork()) < 0)
        exit(1);
    else if (pid == 0)
    {
        if (ft_is_pipe_or_redirect(cmd))
            ft_process_pipes(cmd, envp, hist);
        else
            ft_execute_cmd(command, SPLIT(cmd, ' '), envp);
        exit(0);
    }
    else
    {
        wait(&status);
        if (WIFEXITED(status))
        {
            if (WEXITSTATUS(status) != 0)
                value = -1;
        }
    }
    return (value);
}

int		ft_advanced_com2(char *cmd, char **envp, t_stack *hist)
{
   char	*exec;
   char	**search;
   int		val;

   val = -1;
   search = SPLIT(cmd, ' ');
   // if (CONTAINS(cmd, ';'))
   //     ft_multi_com2(cmd, envp, hist);
   // else if (SEARCH(search[0]) && !CONTAINS(cmd, '>'))
   //     val = ft_execute_commands(search, cmd, envp, hist);
   // else
    if ((exec = ft_build_exec(search, hist)))
       val = ft_execute2(exec, cmd, envp, hist);
   else if (ft_is_execute(search[0]))
       val = ft_execute2(cmd, cmd, envp, hist);
   else
       ft_print_error(search[0], 0);
   freecopy(search);
   return (val);
}

int     ft_run_commands2(char *cmd, char **envp, t_stack *hist)
{
    return (ft_advanced_com2(cmd, envp, hist));
}

void    ft_log_op2(char *cmd, char **envp, t_stack *hist)
{
    char    log[BUFF_SIZE][BUFF_SIZE];
    char    *sep;
    int     i;
    // char logic;
    int     exec;
    char    **split;

    memset(log, 0, sizeof(log[0][0]) * BUFF_SIZE * BUFF_SIZE);
    exec = 0;
    split = SPLIT(cmd, ' ');
    sep = ft_get_logical_sep(cmd);
    i = 0;
    split_by_word(log, split, sep);
    while (log[i] && log[i][0])
    {
        // logic.get_line = log[i];
        if (exec == -1 && EQUAL(sep, "&&"))
            break ;
        exec = ft_pro_cmd2(log[i], envp, hist);
        if (exec == 0 && EQUAL(sep, "||"))
            break ;
        i++;
    }
    free(sep);
    freecopy(split);
}


int     ft_pro_cmd2(char *cmd, char  **envp, t_stack *hist)
{
    char    *tmp;
    char    **split;

    tmp = ft_strdup(cmd);
    hist->counter = -1;
    ft_str_substitution(&cmd, envp);
    if ((split = ft_strsplit(cmd, ' ')) != NULL)
    {
        // if (ft_strequ(cmd->user_comm[0], "quit"))
        // {
        //     free_cmd(cmd);
        //     ft_free_hash_table(hist->hash);
        //     ft_close_keyboard(t);
        //     exit(0);
        // }
        ft_push(hist, tmp);
        // ft_term_off(t);
        if (ft_is_logical(cmd))
            ft_log_op2(cmd, envp,hist);
        else
            hist->counter = ft_run_commands2(cmd, envp, hist);
        // ft_term_on(t);
    }
    freecopy(split);
    return (hist->counter);
}

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
    // char *exec;
    // char **split;
    // split = SPLIT(data, ' ');
    // if ((exec = ft_build_exec(split, hist))) {
    //     ft_send_cmd_to_server(exec, split, envp);
    // } else if (ft_is_execute(split[0])) {
    //     ft_send_cmd_to_server(split[0], split, envp);
    // }else
    //     ft_print_error(split[0], 0);
    ft_pro_cmd2(data, envp, hist);
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
