#include "map.h"
#include "error.h"
#include "libft.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void	upscale_map(t_map *map, size_t size)
{
	t_point	*new;
	size_t	i;

	if (map->malloc_size >= size)
		return ;
	while (map->malloc_size < size)
		map->malloc_size = map->malloc_size * 2 + (!map->malloc_size);
	new = malloc((map->malloc_size) * sizeof(t_point));
	if (!new)
	{
		if (map->points_tab)
			free(map->points_tab);
		map->points_tab = NULL;
		basic_error("A malloc failed\n", 1);
		return ;
	}
	i = -1;
	while (++i < size - map->width)
		new[i] = map->points_tab[i];
	free(map->points_tab);
	map->points_tab = new;
}

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

static void	init_map(t_map *map, char *first_line)
{
	map->height = 0;
	map->malloc_size = 0;
	map->points_tab = NULL;
	map->width = count_word(first_line, ' ');
	map->is_update = 0;
}

static int	end_parsing(t_map *map)
{
	set_map_color(map);
	map->position = (t_point){0, 0, 0, 0};
	map->rotation = (t_point){0, 0, 0, 0};
	if (map->width > map->height)
		map->translation_modifier = map->width / 800.;
	else
		map->translation_modifier = map->height / 800.;
	map->height_scale = (double)(1 << 5) / (map->max_z - map->min_z);
	return (0);
}

int	parse_map(t_map *map, char *filename)
{
	int		fd;
	char	*line_str;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (open_error(filename));
	line_str = get_next_line(fd);
	if (!line_str)
	{
		if (close(fd))
			close_file_error();
		return (basic_error("Empty file or malloc fail\n", 3));
	}
	init_map(map, line_str);
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
		free(line_str);
		line_str = get_next_line(fd);
	}
	if (close(fd))
	{
		destroy_map(map);
		return (close_file_error());
	}
	return (end_parsing(map));
}
