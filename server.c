/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 10:09:07 by julekgwa          #+#    #+#             */
/*   Updated: 2017/07/16 15:30:59 by julekgwa         ###   ########.fr       */
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

void	handle_client(char *data, t_env *envp, t_stack *hist)
{
	ft_pro_cmd(data, envp, hist);
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

	ft_strcpy(s, "done");
	if (EQUAL(cmd, "quit"))
	{
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
	hist.home = ft_pwd();
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
