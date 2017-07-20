/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 10:09:07 by julekgwa          #+#    #+#             */
/*   Updated: 2017/07/20 12:50:07 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"
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

int		ft_search_ftp_cmd(char *command)
{
	static char	*cmd = "pwd cd ls put get";
	char		**comm_split;
	int			i;

	i = 0;
	comm_split = ft_strsplit(cmd, ' ');
	while (comm_split[i])
	{
		if (ft_strcmp(comm_split[i], command) == 0)
		{
			freecopy(comm_split);
			return (1);
		}
		i++;
	}
	freecopy(comm_split);
	return (0);
}

void	handle_client(char *data, t_env *envp, t_stack *hist)
{
	struct termios	term;
	t_cmd			cmd;
	char 			**com;

	com = SPLIT(data, ' ');
	if (!ft_search_ftp_cmd(com[0]))
	{
		ft_print_error(com[0], 0);
		freecopy(com);
		return ;
	}
	cmd.get_line = (char *)malloc(sizeof(char) * strlen(data));
	cmd.local = 1;
	ft_strcpy(cmd.get_line, data);
	ft_pro_cmd(&cmd, envp, &term, hist);
	freecopy(com);
}

void	ft_check_ser_args(int ac, char *prog)
{
	if (ac < 2 || ac > 2)
	{
		printf("Usage: %s <Port number>\n", prog);
		exit(1);
	}
}

int		ft_check_quit(int client_fd, char *cmd)
{
	char	s[5];

	if (EQUAL(cmd, "quit"))
	{
		ft_strcpy(s, "quit");
		send(client_fd, s, strlen(s), 0);
		return (1);
	}
	return (0);
}

void	ft_handle_client_request(int client_fd, char **envp, SAI client)
{
	t_env	*copy;
	t_stack	hist;
	char	*cmd;

	ft_create_stack(&hist, envp);
	copy = ft_welcome_msg(client.sin_port, inet_ntoa(client.sin_addr), envp);
	// hist.home = ft_pwd();
	close(1);
	dup2(client_fd, 0);
	dup2(client_fd, 1);
	dup2(client_fd, 2);
	while (42)
	{
		cmd = read_cmd(client_fd);
		if (ft_check_quit(client_fd, cmd))
			break ;
		handle_client(cmd, copy, &hist);
	}
}

int		main(int ac, char **av, char **envp)
{
	int		socket_fd;
	int		client_fd;
	SAI		client;
	pid_t	pid2;
	int		stdout_copy;

	stdout_copy = dup(1);
	ft_check_ser_args(ac, av[0]);
	socket_fd = ft_socket();
	ft_bind(socket_fd, av[1]);
	while (42)
	{
		client_fd = ft_accept(socket_fd, &client);
		pid2 = fork();
		if (pid2 == 0)
			ft_handle_client_request(client_fd, envp, client);
		close(client_fd);
		dup2(stdout_copy, 1);
		printf("Client disconnected\n");
	}
	return (0);
}
