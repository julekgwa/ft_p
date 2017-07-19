/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 21:57:42 by julekgwa          #+#    #+#             */
/*   Updated: 2017/07/19 22:12:31 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int		ft_send_data(t_cmd *cmd, int fd)
{
	int	put_get;

	if ((put_get = ft_check_put_get(cmd->get_line)) == 1)
		return (0);
	if (put_get == 2)
		ft_upload_file(cmd->get_line, fd);
	else
		put_get = send_to_server(cmd->get_line, fd);
	return (1);
}

int		ft_check_put_get(char *cmd)
{
	char	**check;

	check = SPLIT(cmd, ' ');
	if (!EQUAL(check[0], "put") && !EQUAL(check[0], "get"))
		return (0);
	if (ft_array_len(check) < 2)
	{
		printf("%s\n", "missing file name");
		freecopy(check);
		return (1);
	}
	if (EQUAL(check[0], "put"))
		return (2);
	return (3);
}