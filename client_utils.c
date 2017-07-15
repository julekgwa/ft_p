/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 13:37:25 by julekgwa          #+#    #+#             */
/*   Updated: 2017/07/15 15:09:01 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_p.h"

void	ft_upload_file(char *put, char **line)
{
	char	*cmd;
	char	*content;
	char	*filename;
	char	**split_put;

	split_put = SPLIT(put, ' ');
	filename = split_put[1];
	content = read_file(filename);
	cmd = ft_strjoin("put", " ");
	cmd = ft_strjoin(cmd, content);
	cmd = ft_strjoin(cmd, " ");
	cmd = ft_strjoin(cmd, filename);
	ft_memset(*line, 0, ft_strlen(*line));
	ft_strcpy(*line, cmd);
}