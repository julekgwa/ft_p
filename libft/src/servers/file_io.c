/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 15:32:19 by julekgwa          #+#    #+#             */
/*   Updated: 2017/09/22 16:36:10 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_regular_file(const char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

int		ft_get_file_size(const char *filename)
{
	struct stat	file;
	int			fd;

	if (!is_regular_file(filename))
		return (-1);
	fd = open(filename, O_RDONLY);
	ft_memset(&file, 0, sizeof(struct stat));
	fstat(fd, &file);
	close(fd);
	return (file.st_size);
}

char *read_file(const char *filename, int *size)
{
	char	*content;
	int		file_size;
	int		fd;

	if ((file_size = ft_get_file_size(filename)) <= 0)
		return (NULL);
	content = (char *)malloc(sizeof(char) * file_size);
	fd = open(filename, O_RDONLY);
	*size = read(fd, content, file_size);
	close(fd);
	return (content);
}

void write_file(char *file, char *content, int size)
{
	int	fd;

	fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
	if (fd)
		write(fd, content, size);
	close(fd);
}

void	ft_process_get_put(char **cmd, char *line)
{
	if (EQUAL(cmd[0], "get"))
		ft_get_file(cmd[1]);
	else if (EQUAL(cmd[0], "put"))
		printf("%s %s\n", "PUT", line);
}
