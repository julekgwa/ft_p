/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 15:30:35 by julekgwa          #+#    #+#             */
/*   Updated: 2017/09/24 04:04:10 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_file_exist(char *filename)
{
	struct stat	buffer;

	ft_memset(&buffer, 0, sizeof(struct stat));
	return (stat(filename, &buffer) == 0);
}

void	ft_get_file(char *file, int client_fd)
{
	char	*content;
	char	*cmd;
	char	*feedback;
	int		size;

	if (!ft_file_exist(file))
	{
		printf("ft_p: %s %s\n", "no such file or directory:", file);
		return ;
	}
	content = read_file(file, &size);
	cmd = ft_strjoin("fgetter", " ");
	cmd = ft_strjoin(cmd, file);
	cmd = ft_strjoin(cmd, " ");
	cmd = ft_strjoin(cmd, ft_itoa(size));
	send(client_fd, cmd, strlen(cmd), 0);
	feedback = (char *)malloc(sizeof(char) * size);
	recv(client_fd, feedback, size, 0);
	send(client_fd, content, size, 0);
}

void	ft_put_get_file(char **cmd, int fd)
{
	char	*file;
	char	*feedback;
	char	*size;

	file = cmd[1];
	if (EQUAL(cmd[0], "put"))
	{
		size = cmd[2];
		send(fd, "OK", strlen("OK"), 0);
		feedback = (char *)malloc(sizeof(char) * ft_atoi(size));
		recv(fd, feedback, ft_atoi(size), 0);
		if (!EQUAL(feedback, "ERROR"))
			write_file(file, feedback, ft_atoi(size));
		else
			printf("%s\n", "ERROR");
	}
	else if (EQUAL(cmd[0], "get"))
	{
		ft_get_file(file, fd);
		return ;
	}
	printf("%s\n", "SUCCESS");
}

char	*read_cmd(int fd)
{
	char	buff[BUFFER];
	char	*cmd;
	ssize_t	retval;

	cmd = ft_strjoin("", "");
	while (42)
	{
		retval = recv(fd, buff, BUFFER - 1, 0);
		if (retval)
		{
			buff[retval] = '\0';
			cmd = ft_strjoin(cmd, buff);
		}
		if (retval < BUFFER - 1)
			break ;
	}
	return (cmd);
}

void	ft_handle_cd(char **cmd, t_env *envp)
{
	char	*home;
	char	*pwd;

	home = ft_get_env("$HOME", envp->list);
	pwd = ft_pwd();
	if (LENGTH(cmd) == 1)
		ft_cd(cmd, envp);
	else if (EQUAL(home, pwd) && ft_strncmp(cmd[1], "..", 2) == 0)
		printf("ft_p: Cannot go any lower than server's Home directory\n");
	else
		ft_cd(cmd, envp);
}
