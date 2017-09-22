/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 13:37:25 by julekgwa          #+#    #+#             */
/*   Updated: 2017/09/22 16:46:06 by julekgwa         ###   ########.fr       */
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
	cmd = ft_strjoin(cmd, " ");
	cmd = ft_strjoin(cmd, content);
	send_to_server(cmd, fd);
	return (2);
}

void	ft_save_file(char *file, char *orig, char *size)
{
	int	len;

	len = ft_strlen(file) + 10 + ft_strlen(size);
	write_file(file, orig + len, ft_atoi(size));
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
		ft_save_file(split[1], feedback, split[2]);
	else
		printf("%s\n", feedback);
	return (0);
}

int		send_to_server(char *cmd, int server_fd)
{
	send(server_fd, cmd, strlen(cmd), 0);
	return (display_response(server_fd));
}
