/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 13:37:25 by julekgwa          #+#    #+#             */
/*   Updated: 2017/07/20 13:04:00 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_p.h"

int		ft_upload_file(char *put, int fd)
{
	char	*cmd;
	char	*content;
	char	*filename;
	char	**split_put;

	split_put = SPLIT(put, ' ');
	filename = split_put[1];
	if (!ft_file_exist(filename))
	{
		printf("ft_p: %s %s\n", "no such file or directory:", filename);
		return (0);
	}
	content = read_file(filename);
	cmd = ft_strjoin("put", " ");
	cmd = ft_strjoin(cmd, filename);
	cmd = ft_strjoin(cmd, " ");
	cmd = ft_strjoin(cmd, content);
	send_to_server(cmd, fd);
	return (2);
}

void	ft_save_file(char *file, char *orig)
{
	int	len;

	len = ft_strlen(file) + 9;
	write_file(file, orig + len);
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
		ft_save_file(split[1], feedback);
	else
		ft_putendl(feedback);
	return (0);
}

int		send_to_server(char *cmd, int server_fd)
{
	send(server_fd, cmd, strlen(cmd), 0);
	return (display_response(server_fd));
}
