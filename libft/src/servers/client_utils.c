/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 13:37:25 by julekgwa          #+#    #+#             */
/*   Updated: 2017/09/24 13:31:06 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_upload_file(char *put, int fd)
{
	char	*cmd;
	char	*content;
	char	*filename;
	char	**split_put;
	int		size;

	split_put = SPLIT(put, ' ');
	filename = split_put[1];
	if (!ft_file_exist(filename))
	{
		printf("ft_p: %s %s\n", "no such file or directory:", filename);
		return (0);
	}
	content = read_file(filename, &size);
	cmd = ft_strjoin("put", " ");
	cmd = ft_strjoin(cmd, filename);
	cmd = ft_strjoin(cmd, " ");
	cmd = ft_strjoin(cmd, ft_itoa(size));
	send(fd, cmd, strlen(cmd), 0);
	read_cmd(fd);
	if (!content)
		send(fd, "ERROR", strlen("ERROR"), 0);
	else
		send(fd, content, size, 0);
	return (2);
}

void	ft_save_file(char *file, char *size, int server_fd)
{
	char	*feedback;

	feedback = (char *)malloc(sizeof(char) * ft_atoi(size));
	send(server_fd, "OK", strlen("OK"), 0);
	recv(server_fd, feedback, ft_atoi(size), 0);
	if (feedback)
	{
		write_file(file, feedback, ft_atoi(size));
		printf("%s\n", "SUCCESS");
	}
	else
		printf("%s\n", "ERROR");
}

int		display_response(int fd)
{
	char	*feedback;
	char	**split;

	feedback = read_cmd(fd);
	split = SPLIT(feedback, ' ');
	if (EQUAL(feedback, "quit"))
		return (1);
	if (EQUAL(split[0], "fgetter"))
		ft_save_file(split[1], split[2], fd);
	else
	{
		if (feedback[strlen(feedback) - 1] == '\n')
			feedback[strlen(feedback) - 1] = '\0';
		printf("%s\n", feedback);
	}
	return (0);
}

int		send_to_server(char *cmd, int server_fd)
{
	char	**split;

	split = SPLIT(cmd, ' ');
	if (EQUAL(split[0], "put"))
		ft_upload_file(cmd, server_fd);
	else
		send(server_fd, cmd, strlen(cmd), 0);
	freecopy(split);
	return (display_response(server_fd));
}
