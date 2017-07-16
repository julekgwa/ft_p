/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 15:32:19 by julekgwa          #+#    #+#             */
/*   Updated: 2017/07/16 13:45:45 by julekgwa         ###   ########.fr       */
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

char	*read_file(const char *filename)
{
	char	*content;
	int		file_size;
	int		fd;
	ssize_t	retval;

	if ((file_size = ft_get_file_size(filename)) <= 0)
		return (NULL);
	content = (char *)malloc(sizeof(char) * file_size + 1);
	fd = open(filename, O_RDONLY);
	retval = read(fd, content, file_size);
	content[retval + 1] = '\0';
	close(fd);
	return (content);
}

void	write_file(char *file, char *content)
{
	int	fd;

	fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
	if (fd)
		write(fd, content, ft_strlen(content));
	close(fd);
}
