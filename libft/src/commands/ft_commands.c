/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 07:45:09 by julekgwa          #+#    #+#             */
/*   Updated: 2017/07/15 20:58:44 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env(const char *env, char **env_list)
{
	int			index;
	const char	*ptr;

	if (*env != '$')
		return (NULL);
	env += 1;
	while (*env_list)
	{
		ptr = ft_strchr(*env_list, '=');
		index = ptr - *env_list;
		if (ft_strncmp(env, *env_list, index) == 0)
			return (*env_list + ft_strlen(env) + 1);
		env_list++;
	}
	return (NULL);
}

char	*ft_get_str(char **av)
{
	char	*ps;
	int		i;
	int		j;
	int		found;

	ps = av[2];
	i = 2;
	j = 3;
	found = 0;
	if (ft_start_with(av[2], '"'))
	{
		while (!ft_end_with(av[i], '"') && av[i])
			i++;
		if (ft_end_with(av[i], '"'))
			found = 1;
		while (j <= i && found)
		{
			ps = ft_strjoin(ps, " ");
			ps = ft_strjoin(ps, av[j]);
			j++;
		}
	}
	return (ps);
}

char	*ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	return (pwd);
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd->user_comm)
	{
		freecopy(cmd->user_comm);
		cmd->user_comm = NULL;
	}
	if (cmd->get_line)
	{
		free(cmd->get_line);
		cmd->get_line = NULL;
	}
	if (cmd->user_comm || cmd->get_line)
		free_cmd(cmd);
}

int     ft_pro_cmd(char *cmd, t_env *envp, t_stack *hist)
{
    char    *tmp;
    char    **split;

    tmp = ft_strdup(cmd);
    hist->counter = -1;
    if (ft_strncmp(cmd, "put", 3) != 0) 
    	ft_str_substitution(&cmd, envp->list);
    if ((split = ft_strsplit(cmd, ' ')) != NULL)
    {
        ft_push(hist, tmp);
        if (ft_is_logical(cmd) && !EQUAL(split[0], "put"))
            ft_log_op(cmd, envp,hist);
        else
            hist->counter = ft_run_commands(cmd, envp, hist);
    }
    freecopy(split);
    return (hist->counter);
}
