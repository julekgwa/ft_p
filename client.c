/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 10:10:20 by julekgwa          #+#    #+#             */
/*   Updated: 2017/09/24 13:10:11 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	ft_check_args(int ac, char *prog)
{
	if (ac < 3 || ac > 3)
	{
		printf("Insufficient number of arguments. \n");
		printf("Usage: ./%s <IP Address Of Server> <Port Number>\n", prog);
		exit(1);
	}
}

int		main(int ac, char **av, char **envp)
{
	struct termios	term;
	t_stack			hist;
	t_cmd			cmd;
	t_env			*envp_copy;

	ft_check_args(ac, av[0]);
	ft_create_stack(&hist, envp);
	envp_copy = copy_envp(4096, envp);
	signal(SIGINT, ft_ctrl_c_signal_handler);
	cmd.fd = ft_socket();
	ft_connect(cmd.fd, av[2], av[1], envp_copy);
	ft_init_keyboard(&term, &ac, &av);
	while (42)
	{
		prompt(&cmd, &hist);
		ft_process_slash_inhibitor(&cmd, &term);
		ft_complete_cmd(&cmd, &term);
		ft_putchar('\n');
		if (!ft_strequ(cmd.get_line, "") && ft_spaces_tabs(cmd.get_line))
			ft_pro_cmd(&cmd, envp_copy, &term, &hist);
		free(cmd.get_line);
	}
	return (0);
}
