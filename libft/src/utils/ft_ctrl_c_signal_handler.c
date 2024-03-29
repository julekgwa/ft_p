/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl_c_signal_handler.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 17:23:04 by julekgwa          #+#    #+#             */
/*   Updated: 2017/07/20 12:59:47 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_handle_ctrl_c(int in_c)
{
	static int ctrl_c = 0;

	if (in_c == 1)
		ctrl_c++;
	else if (in_c == 2)
		ctrl_c = 0;
	return ctrl_c;
}

void	ft_ctrl_c_signal_handler(int signum)
{
	ft_putstr("\n");
	ft_cmd_prompt();
	tputs(tgetstr("so", NULL), 1, ft_myputchar);
	ft_putchar(' ');
	tputs(tgetstr("se", NULL), 1, ft_myputchar);
	ft_handle_ctrl_c(1);
	(void)signum;
}

void	ft_print_error(char *cmd, int errorno)
{
	if (errorno == 3)
	{
		printf("%s","ERROR: ");
		printf("%s","no such file or directory: ");
		printf("%s\n", cmd);
		return ;
	}
	else if (errorno == 5)
	{
		printf("%s","\nft_p: event not found: ");
		printf("%s\n", cmd);
		return ;
	}
	printf("%s","ft_p: ");
	printf("%s",cmd);
	if (errorno == 1)
		printf("%s",": Permission denied\n");
	else if (errorno == 0)
		printf("%s",": command not found...\n");
	else if (errorno == 2)
		printf("%s",": Is a directory\n");
}

void	prompt(t_cmd *cmd, t_stack *hist)
{
	char			*comm;
	char			*buf;
	int				pos;

	buf = ft_memalloc(GET_C_BUFF_SIZE);
	comm = ft_memalloc(BUFF_SIZE);
	cmd->get_line = ft_memalloc(BUFF_SIZE);
	cmd->local = 0;
	ft_memset(cmd->get_line, 0, BUFF_SIZE);
	pos = 0;
	ft_cmd_prompt();
	tputs(tgetstr("so", NULL), 1, ft_myputchar);
	ft_putchar(' ');
	tputs(tgetstr("se", NULL), 1, ft_myputchar);
	strcpy(cmd->get_line, ft_build_cmd(hist, comm, buf, pos));
	free(buf);
	free(comm);
}

char	**envp_cpy(char **envp)
{
	char	**copy;
	int		i;

	i = 0;
	copy = (char **)malloc((ft_array_len(envp) + 1) * sizeof(char *));
	copy[ft_array_len(envp)] = NULL;
	if (copy)
	{
		while (envp[i])
		{
			copy[i] = ft_strdup(envp[i]);
			i++;
		}
	}
	return (copy);
}
