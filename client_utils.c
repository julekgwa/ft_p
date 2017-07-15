/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 13:37:25 by julekgwa          #+#    #+#             */
/*   Updated: 2017/07/15 19:52:54 by julekgwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_p.h"

int	ft_upload_file(char *put, int fd)
{
	char	*cmd;
	char	*content;
	char	*filename;
	char	**split_put;

	split_put = SPLIT(put, ' ');
	filename = split_put[1];
	content = read_file(filename);
	cmd = ft_strjoin("put", " ");
	cmd = ft_strjoin(cmd, filename);
	cmd = ft_strjoin(cmd, " ");
	cmd = ft_strjoin(cmd, content);
	send_to_server(cmd, fd);
	return (2);
}

int display_response(int fd)
{
    char *feedback;
    // ssize_t len;
    // char output[BUFFER];
    // char feedback[] = "received";

    // len = BUFFER;
    // while (len)
    // {
    //     len = recv(fd, output, BUFFER, 0);
    //     if (len)
    //     {
    //         output[len] = '\0';
    //         if (strncmp(output, "done", 4) == 0) 
    //             break;
    //         if (len < BUFFER)
    //             send(fd, feedback, strlen(feedback), 0);
    //         printf("%s", output);
    //     }
    // }
    feedback = read_cmd(fd);
    if (EQUAL(feedback, "done"))
        return (1);
    printf("%s\n", feedback);
    return (0);
}

int send_to_server(char *cmd, int server_fd)
{
    printf("%s\n", "Connected");
    send(server_fd, cmd, strlen(cmd), 0);
    return display_response(server_fd);
}