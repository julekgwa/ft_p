/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 13:51:11 by julekgwa          #+#    #+#             */
/*   Updated: 2017/07/16 09:19:51 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_FT_P_H
#define FT_P_FT_P_H
#define SA struct sockaddr
#define SAI struct sockaddr_in
#define ERROR -1
#include "minishell.h"
#include <arpa/inet.h>
int send_to_server(char *cmd, int server_fd);
int ft_socket(void);
void    ft_connect(int fd, char *port, char *server, t_env *envp);
void	ft_bind(int fd, char *port);
int ft_accept(int fd, SAI *client);
#endif //FT_P_FT_P_H
