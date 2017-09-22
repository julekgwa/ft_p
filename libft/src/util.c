/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 17:26:31 by julekgwa          #+#    #+#             */
/*   Updated: 2017/09/22 17:40:54 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_search_command(char *command)
{
	static char	*cmd = "echo pwd cd history setenv unsetenv env exit clear";
	char		**comm_split;
	int			i;

	i = 0;
	if (check_builtin(command))
        return (1);
	comm_split = ft_strsplit(cmd, ' ');
	while (comm_split[i])
	{
		if (ft_strcmp(comm_split[i], command) == 0)
		{
			freecopy(comm_split);
			return (1);
		}
		i++;
	}
	freecopy(comm_split);
	return (0);
}

int		ft_execute_commands(char **cmd, char *line, t_env *envp, t_stack *hist)
{
	char *dir;

	if (ft_strequ(cmd[0], "cd") || ft_strequ(cmd[0], "lcd"))
		ft_cd(cmd, envp);
	else if (ft_strequ(cmd[0], "pwd") || ft_strequ(cmd[0], "lpwd"))
	{
		dir = ft_pwd();
		printf("%s\n", dir);
		free(dir);
	}
	else if (EQUAL(cmd[0], "get") || EQUAL(cmd[0], "put"))
		ft_put_get_file(cmd, line);
	else if (ft_strequ(cmd[0], "export"))
		ft_export(cmd, envp);
	else if (ft_strequ(cmd[0], "echo"))
		ft_echo(line, envp->list);
	else if (ft_strequ(cmd[0], "env") || ft_strequ(cmd[0], "lenv"))
		ft_print_env(envp);
	else if (ft_strequ(cmd[0], "setenv") || ft_strequ(cmd[0], "lsetenv"))
		ft_set_envir(envp, line, hist);
	else if (ft_strequ(cmd[0], "unsetenv") || ft_strequ(cmd[0], "unset"))
		ft_unsetting_env(line, envp, hist);
	else if (ft_strequ(cmd[0], "history") || ft_strequ(cmd[0], "lhistory"))
		ft_display_hist(hist, cmd, 0);
	else if (ft_strequ(cmd[0], "clear") || ft_strequ(cmd[0], "lclear"))
		tputs(tgetstr("cl", NULL), 1, ft_myputchar);
	return (0);
}

int ft_is_local(char *cmd)
{
	if (ft_start_with(cmd, 'l') && !EQUAL(cmd, "ls"))
		return (1);
	return (0);
}

int		ft_run_commands(t_cmd *cmd, t_env *envp, t_stack *hist)
{
	char 	**check;

	check = SPLIT(cmd->get_line, ' ');
	if (!ft_is_local(check[0]) && cmd->local == 0)
		return send_to_server(cmd->get_line, cmd->fd);
	return (ft_advanced_com(cmd, envp, hist));
}

char	*ft_build_cmd(t_stack *hist, char *comm, char *buf, int pos)
{
	while (42)
	{
		hist->ret = read(0, buf, 4);
		buf[hist->ret] = '\0';
		if (buf[hist->ret - 1] == '\n')
			if (ft_enter_key(&comm, &pos, hist))
				break ;
		ft_set_cmd_to_null(&comm, &pos);
		if (buf[0] == '\t')
			ft_autocomplete(&comm, &pos, hist->envp);
		else if (ft_ctrl_d(&comm, buf))
			break ;
		else if (ft_is_copy_n_paste(buf))
			ft_copy_n_paste(&comm, buf, &pos, hist);
		else if (ft_is_inter(buf) || ft_up_down(buf))
			ft_intermidiate(&comm, &pos, hist, buf);
		else if (ft_enter_and_edit_keys(buf, &pos, comm, hist))
			;
		else if (ft_navigation_keys(buf, &pos, comm))
			ft_cursor(comm, pos + 1, hist);
		else if (ft_character_keys(buf) && buf[0] != 27)
			ft_process_buff(&comm, pos++, buf[0], hist);
		ft_cursor(comm, pos + 1, hist);
	}
	return (comm);
}

int check_builtin(char *cmd)
{
    if (EQUAL(cmd, "export") || EQUAL(cmd, "unset") || EQUAL(cmd, "lcd"))
        return (1);
    if (EQUAL(cmd, "put") || EQUAL(cmd, "get") || EQUAL(cmd, "lpwd"))
        return (1);
    if (EQUAL(cmd, "lhistory") || EQUAL(cmd, "lclear"))
        return (1);
    if (EQUAL(cmd, "lsetenv") || EQUAL(cmd, "lenv"))
        return (1);
    return (0);
}
