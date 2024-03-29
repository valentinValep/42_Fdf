/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:05:20 by vlepille          #+#    #+#             */
/*   Updated: 2023/04/28 16:28:12 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "error.h"
#include "libft.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static char	*get_next_word(char	*current_word)
{
	while (*current_word && *current_word != ' ' && *current_word != '\n')
		current_word++;
	while (*current_word && *current_word == ' ' && *current_word != '\n')
		current_word++;
	return (current_word);
}

static int	parse_line(t_map *map, char *line_str)
{
	size_t			i;
	char			*current_word;
	t_point			new_point;

	upscale_map(map, (size_t) map->height * map->width);
	if (!map->points_tab)
		return (-1);
	i = map->height * map->width - map->width;
	current_word = line_str;
	while (*current_word && *current_word == ' ' && *current_word != '\n')
		current_word++;
	while (i < map->height * map->width)
	{
		new_point = (t_point){i % map->width, i / map->width,
			ft_atoi(current_word), get_color(current_word)};
		if (!i || map->min_z > new_point.z)
			map->min_z = new_point.z;
		if (!i || map->max_z < new_point.z)
			map->max_z = new_point.z;
		current_word = get_next_word(current_word);
		map->points_tab[i] = new_point;
		i++;
	}
	return (0);
}

static int	end_parsing(t_map *map)
{
	const int	diff = map->max_z - map->min_z;

	set_map_color(map);
	map->position = (t_point){0, 0, 0, 0};
	map->rotation = (t_point){0, 0, 0, 0};
	if (diff < 50)
		map->height_scale = 0.08;
	else if (diff < 120)
		map->height_scale = 0.2;
	else if (diff < 300)
		map->height_scale = 0.4;
	else if (diff < 600)
		map->height_scale = 0.2;
	else if (diff < 1000)
		map->height_scale = 0.08;
	else
		map->height_scale = 0.02;
	return (0);
}

static int	start_parsing(t_map *map, char *filename, int *fd, char **line_str)
{
	*fd = open(filename, O_RDONLY);
	if (*fd < 0)
		return (open_error(filename));
	*line_str = get_next_line(*fd);
	if (!*line_str)
	{
		if (close(*fd))
			close_file_error();
		return (basic_error("Empty file or malloc fail\n", 3));
	}
	map->height = 0;
	map->malloc_size = 0;
	map->points_tab = NULL;
	map->width = count_word(*line_str, ' ');
	map->is_update = 0;
	return (0);
}

int	parse_map(t_map *map, char *filename)
{
	int		fd;
	char	*line_str;

	if (start_parsing(map, filename, &fd, &line_str))
		return (1);
	while (line_str)
	{
		map->height++;
		if (parse_line(map, line_str))
		{
			if (close(fd))
				close_file_error();
			free(line_str);
			gnl_close(fd);
			return (basic_error("Error while parsing file\n", 5));
		}
		line_str = get_next_line((free(line_str), fd));
	}
	if (close(fd))
	{
		destroy_map(map);
		return (close_file_error());
	}
	return (end_parsing(map));
}
