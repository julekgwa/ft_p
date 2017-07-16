/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 13:51:11 by julekgwa          #+#    #+#             */
/*   Updated: 2017/07/16 08:40:39 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_FT_P_H
#define FT_P_FT_P_H
#define SA struct sockaddr
#define SAI struct sockaddr_in
#include "minishell.h"
int send_to_server(char *cmd, int server_fd);
#endif //FT_P_FT_P_H
