/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 15:30:35 by julekgwa          #+#    #+#             */
/*   Updated: 2017/09/22 19:06:34 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_file_exist(char *filename)
{
	struct stat	buffer;

	ft_memset(&buffer, 0, sizeof(struct stat));
	return (stat(filename, &buffer) == 0);
}

void	ft_get_file(char *file)
{
	char	*content;
	char	*cmd;
	int		size;

	if (!ft_file_exist(file))
	{
		printf("ft_p: %s %s\n", "no such file or directory:", file);
		return ;
	}
	content = read_file(file, &size);
	cmd = ft_strjoin("fgetter", " ");
	cmd = ft_strjoin(cmd, file);
	cmd = ft_strjoin(cmd, " ");
	cmd = ft_strjoin(cmd, ft_itoa(size));
	cmd = ft_strjoin(cmd, " ");
	cmd = ft_strjoin(cmd, content);
	printf("%s\n", cmd);
}

void	ft_put_get_file(char **cmd, char *orig)
{
	char	*file;
	int		len;
	char	*size;

	file = cmd[1];
	if (EQUAL(cmd[0], "put"))
	{
		size = cmd[2];
		len = ft_strlen(file) + 6 + ft_strlen(size);
		write_file(file, orig + len, ft_atoi(size));
	}
	else if (EQUAL(cmd[0], "get"))
	{
		ft_get_file(file);
		return ;
	}
	printf("%s\n", "SUCCESS");
}

char	*read_cmd(int fd)
{
	char	buff[BUFFER];
	char	*cmd;
	ssize_t	retval;

	cmd = ft_strjoin("", "");
	while (42)
	{
		retval = recv(fd, buff, BUFFER - 1, 0);
		if (retval)
		{
			buff[retval] = '\0';
			cmd = ft_strjoin(cmd, buff);
		}
		if (retval < BUFFER - 1)
			break ;
	}
	return (cmd);
}

// void	ft_handle_cd(char **cmd, t_env *envp, t_stack *hist)
// {
// 	char	*dir;
// 	char	*oldpwd;
// 	int		dirflag;

// 	if (cmd[1] == NULL)
// 	{
// 		oldpwd = getcwd(NULL, 0);
// 		dirflag = chdir(hist->home);
// 		ft_modpwd(dirflag, oldpwd, envp);
// 		return ;
// 	}
// 	dir = ft_pwd();
// 	if (!(EQUAL(dir, hist->home) == 1 && EQUAL(cmd[1], "..") == 1))
// 		ft_cd(cmd, envp, hist->home);
// 	else
// 	{
// 		printf("%s", "ft_p: Cannot go any lower than server's Home directory");
// 	}
// }
