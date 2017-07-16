/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcp_wrapper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/16 08:56:37 by julekgwa          #+#    #+#             */
/*   Updated: 2017/07/16 13:38:46 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		ft_socket(void)
{
	int	socketfd;

	if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == ERROR)
	{
		printf("%s\n", "Socket ERROR");
		exit(-1);
	}
	return (socketfd);
}

void	ft_connect(int fd, char *port, char *server, t_env *envp)
{
	SAI	remote_server;

	(void)envp;
	remote_server.sin_family = AF_INET;
	remote_server.sin_port = htons(atoi(port));
	remote_server.sin_addr.s_addr = inet_addr(server);
	ft_bzero(&remote_server.sin_zero, 8);
	if ((connect(fd, (SA *)&remote_server, sizeof(SAI))) == ERROR)
	{
		printf("connect: %s", "connection ERROR\n");
		exit(-1);
	}
}

void	ft_bind(int fd, char *port)
{
	SAI	server;
	int	len;

	server.sin_family = AF_INET;
	server.sin_port = htons(ft_atoi(port));
	server.sin_addr.s_addr = INADDR_ANY;
	ft_bzero(&server.sin_zero, 8);
	len = sizeof(SAI);
	if ((bind(fd, (SA *)&server, len)) == ERROR)
	{
		printf("Bind: %s", "bind ERROR");
		exit(-1);
	}
	listen(fd, 5);
}

int		ft_accept(int fd, SAI *client)
{
	int	socketfd;
	int	len;

	len = sizeof(SAI);
	if ((socketfd = accept(fd, (SA *)client, (socklen_t *)&len)) == ERROR)
	{
		perror("accept");
		exit(-1);
	}
	return (socketfd);
}

t_env	*ft_welcome_msg(int port, char *ip, char **envp)
{
	printf("New client connected from port no %d and IP %s\n", port, ip);
	return (copy_envp(4096, envp));
}
