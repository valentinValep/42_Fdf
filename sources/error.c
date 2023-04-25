/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:05:16 by vlepille          #+#    #+#             */
/*   Updated: 2023/04/25 17:05:17 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdio.h>

int	basic_error(char *str, int return_number)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	return (return_number);
}

int	open_error(char *filename)
{
	write(STDERR_FILENO, "Can't open file ", 16);
	write(STDERR_FILENO, filename, ft_strlen(filename));
	write(STDERR_FILENO, "\n", 1);
	return (2);
}

int	close_file_error(void)
{
	perror("Close file error : ");
	return (4);
}
