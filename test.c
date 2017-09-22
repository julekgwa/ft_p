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


int		is_regular_file(const char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

int		ft_get_file_size(const char *filename)
{
	struct stat	file;
	int			fd;

	if (!is_regular_file(filename))
		return (-1);
	fd = open(filename, O_RDONLY);
	memset(&file, 0, sizeof(struct stat));
	fstat(fd, &file);
	close(fd);
	return (file.st_size);
}


//char	*read_file(const char *filename)

char *read_file(const char *filename, ssize_t *size)
{
	char	*content;
	int		file_size;
	int		fd;
	ssize_t	retval;

	if ((file_size = ft_get_file_size(filename)) <= 0)
		return (NULL);
	content = (char *)malloc(sizeof(char) * file_size);
	fd = open(filename, O_RDONLY);
	retval = read(fd, content, file_size);
	*size = retval;
	close(fd);
	return (content);
}

//void	write_file(char *file, char *content)

void write_file(char *file, char *content, int size)
{
	int	fd;

	fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
	if (fd)
		write(fd, content, size);
	close(fd);
}

int main() {
	ssize_t size;
	char *test = read_file("ft_p.en.pdf", &size);
	write_file("tests.pdf", test, size);
	return EXIT_SUCCESS;
}
