/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_more_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 17:01:06 by julekgwa          #+#    #+#             */
/*   Updated: 2017/07/15 20:24:37 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_contains(char *str, char c)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (1);
        i++;
    }
    return (0);
}

void ft_multi_com(char *cmd, t_env *envp, t_stack *hist)
{
    t_cmd *tmp;
    char **split_com;
    int i;

    tmp = (t_cmd *) malloc(sizeof(t_cmd) + 1);
    split_com = SPLIT(cmd, ';');
    i = 0;
    if (split_com)
    {
        while (split_com[i])
        {
            tmp->get_line = ft_strdup(split_com[i]);
            tmp->user_comm = SPLIT(tmp->get_line, ' ');
            ft_run_commands(tmp->get_line, envp, hist);
            free_cmd(tmp);
            i++;
        }
    }
    if (split_com)
        freecopy(split_com);
    free(tmp);
}

int ft_advanced_com(char *cmd, t_env *envp, t_stack *hist)
{
    char *exec;
    char **search;
    int val;

    val = -1;
    search = SPLIT(cmd, ' ');
    if (CONTAINS(cmd, ';') && (!EQUAL(search[0], "put") && !EQUAL(search[0], "get")))
        ft_multi_com(cmd, envp, hist);
    else if (SEARCH(search[0]) && (EQUAL(search[0], "put") || EQUAL(search[0], "get")))
        val = ft_execute_commands(search, cmd, envp, hist);
    else if (SEARCH(search[0]) && !CONTAINS(cmd, '>'))
        val = ft_execute_commands(search, cmd, envp, hist);
    else if ((exec = ft_build_exec(search, hist)))
        val = ft_execute(exec, cmd, envp, hist);
    else if (ft_is_execute(search[0]))
        val = ft_execute(cmd, cmd, envp, hist);
    else
        ft_print_error(search[0], 0);
    freecopy(search);
    return (val);
}

char *ft_last_word(const char *s)
{
    int i;
    char *last;
    int j;

    i = 0;
    j = 0;
    last = (char *) malloc(sizeof(char) * ft_strlen(s));
    while (s[i])
        i++;
    i -= 1;
    while (s[i] == ' ' || s[i] == '\t')
        i--;
    while ((s[i] != ' ' && s[i] != '\t') && i >= 0)
        i--;
    i += 1;
    while (s[i] && s[i] != ' ' && s[i] != '\t')
    {
        last[j] = s[i];
        i++;
        j++;
    }
    return (last);
}

char *ft_first_word(const char *s)
{
    int i;
    char *first;
    int j;

    i = 0;
    j = 0;
    first = (char *) malloc(sizeof(char) * ft_strlen(s));
    while (s[i] == ' ' || s[i] == '\t')
        i++;
    while (s[i] && s[i] != ' ' && s[i] != '\t')
    {
        first[j] = s[i];
        i++;
        j++;
    }
    return (first);
}
