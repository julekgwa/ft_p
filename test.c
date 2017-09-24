//
// Created by julekgwa on 2017/09/22.
//



#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "minishell.h"
#include "libft.h"
 #include <sys/types.h>
       #include <sys/socket.h>
       #include <netdb.h>
#include<stdio.h>
#include<netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// int		is_regular_file(const char *path)
// {
// 	struct stat	path_stat;

// 	stat(path, &path_stat);
// 	return (S_ISREG(path_stat.st_mode));
// }

// int		ft_get_file_size(const char *filename)
// {
// 	struct stat	file;
// 	int			fd;

// 	if (!is_regular_file(filename))
// 		return (-1);
// 	fd = open(filename, O_RDONLY);
// 	memset(&file, 0, sizeof(struct stat));
// 	fstat(fd, &file);
// 	close(fd);
// 	return (file.st_size);
// }


// //char	*read_file(const char *filename)

// char *read_file(const char *filename, int *size)
// {
// 	char	*content;
// 	int		file_size;
// 	int		fd;
// 	ssize_t	retval;

// 	if ((file_size = ft_get_file_size(filename)) <= 0)
// 		return (NULL);
// 	content = (char *)malloc(sizeof(char) * file_size);
// 	fd = open(filename, O_RDONLY);
// 	retval = read(fd, content, file_size);
// 	*size = retval;
// 	close(fd);
// 	return (content);
// }

// //void	write_file(char *file, char *content)

// void write_file(char *file, char *content, int size)
// {
// 	int	fd;

// 	fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
// 	if (fd)
// 		write(fd, content, size);
// 	close(fd);
// }

// void	*ft_gets_file(char *file)
// {
// 	char	*content;
// 	char	*cmd;
// 	int		size;

// 	if (!ft_file_exist(file))
// 	{
// 		printf("ft_p: %s %s\n", "no such file or directory:", file);
// 		return NULL;
// 	}
// 	content = read_file(file, &size);
// 	return content;
// 	cmd = ft_strjoin("fgetter", " ");
// 	cmd = ft_strjoin(cmd, file);
// 	cmd = ft_strjoin(cmd, " ");
// 	cmd = ft_strjoin(cmd, ft_itoa(size));
// 	cmd = ft_strjoin(cmd, " ");
// 	cmd = ft_strjoin(cmd, content);
// 	return cmd;
// }

// void	ft_save_file(char *file, void *orig, char *size)
// {
// 	int	len;

// 	len = ft_strlen(file) + 10 + ft_strlen(size);
// 	write_file(file, orig, ft_atoi(size));
// }

int main(int ac, char **argv) {
	// int ssize;
	// void *test = read_file("ft_p.en.pdf", &ssize);
	// write_file("tests.pdf", test, size);
	// void *s = ft_gets_file("ft_p.en.pdf");
	// char **st = SPLIT(s, ' ');
	// char *file = st[1];
	// char *size = st[2];
	// printf("%s\n", size);
	// ft_save_file("pt_p.en.pdf", s, "4193016");

	// if (!ft_file_exist("/home/julekgwa/test.pdf"))
	// {
	// 	printf("ft_p: %s %s\n", "no such file or directory:", "/home/julekgwa/test.pdf");
	// 	// return ;
	// }
int i;
    struct hostent *he;
    struct in_addr **addr_list;

    if (ac != 2) {
        fprintf(stderr,"usage: ghbn hostname\n");
        return 1;
    }

    if ((he = gethostbyname(argv[1])) == NULL) {  // get the host info
        herror("gethostbyname");
        return 2;
    }

    // print information about this host:
    printf("Official name is: %s\n", he->h_name);
    printf("    IP addresses: ");
    addr_list = (struct in_addr **)he->h_addr_list;
    for(i = 0; addr_list[i] != NULL; i++) {
        printf("%s ", inet_ntoa(*addr_list[i]));
    }
    printf("\n");
	return EXIT_SUCCESS;
}
