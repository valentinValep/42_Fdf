#include "libft.h"
#include <unistd.h>
#include <stdio.h>

int	malloc_error(void)
{
	write(STDERR_FILENO, "A malloc failed\n", 16);
	return (1);
}

int	open_error(char *filename)
{
	write(STDERR_FILENO, "Can't open file ", 16);
	write(STDERR_FILENO, filename, ft_strlen(filename));
	write(STDERR_FILENO, "\n", 1);
	return (2);
}

int	empty_map_error(void)
{
	write(STDERR_FILENO, "Empty file or malloc fail\n", 26);
	return (3);
}

int	close_file_error(void)
{
	perror("Close file error : ");
	return (4);
}

int	parsing_error(void)
{
	write(STDERR_FILENO, "Error while parsing file\n", 25);
	return (5);
}
