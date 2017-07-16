/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/16 14:41:29 by julekgwa          #+#    #+#             */
/*   Updated: 2017/07/16 14:45:02 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"

int	get_next_line(const int fd, char **line);
int	ft_getchar(const int fd);
# define GET_C_BUFF_SIZE 1024
# define BUFF_SIZE 1024

#endif
