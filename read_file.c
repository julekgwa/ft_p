/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 00:16:38 by julekgwa          #+#    #+#             */
/*   Updated: 2017/07/13 00:19:04 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int ft_get_file_size(const char *filename)
{
    struct stat file;
    int fd;

    if (!is_regular_file(filename))
        return (-1);
    fd = open(filename, O_RDONLY);
    memset(&file, 0, sizeof(struct stat));
    fstat(fd, &file);
    close(fd);
    return file.st_size;
}


char *read_file(const char *filename)
{
    char *content;
    int file_size;
    int fd;

    if ((file_size = ft_get_file_size(filename)) <= 0)
        return (NULL);
    content = (char *) malloc(sizeof(char) * file_size);
    fd = open(filename, O_RDONLY);
    read(fd, content, file_size);
    return content;
}