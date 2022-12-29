#include <stdlib.h>
#include <math.h>
#include <mlx.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"
#include "fdf.h"

void	upscale_map(t_map *map, int size)
{
	t_point	*new;
	int		i;

	if (map->malloc_size >= size)
		return ;
	while (map->malloc_size < size)
		map->malloc_size = map->malloc_size * 2 + (!map->malloc_size);
	new = malloc((map->malloc_size) * sizeof(t_point));
	if (!new)
	{
		if (map->tab)
			free(map->tab);
		map->tab = NULL;
		return ;
	}
	i = -1;
	while (++i < size - map->width)
		new[i] = map->tab[i];
	free(map->tab);
	map->tab = new;
}

static char	*get_next_word(char	*current_word)
{
	while (*current_word && *current_word != ' ' && *current_word != '\n')
		current_word++;
	while (*current_word && *current_word == ' ' && *current_word != '\n')
		current_word++;
	return (current_word);
}

static int	new_map(t_map *map, char	*line_str)
{
	int				i;
	char			*current_word;
	t_point			new_point;

	if (map->height == 1)
		map->width = count_word(line_str, ' ');
	upscale_map(map, map->width * map->height);
	if (!map->tab)
		return (-1);
	i = map->height * map->width - map->width;
	current_word = line_str;
	while (*current_word && *current_word == ' ' && *current_word != '\n')
		current_word++;
	while (i < map->height * map->width)
	{
		new_point.x = i % map->width;
		new_point.y = i / map->width;
		new_point.z = ft_atoi(current_word);
		if (!i || map->min_z > new_point.z)
			map->min_z = new_point.z;
		if (!i || map->max_z < new_point.z)
			map->max_z = new_point.z;
		current_word = get_next_word(current_word);
		if (!*current_word && i != map->height * map->width - 1)
			return ((free(map->tab), -2));
		map->tab[i] = new_point;
		i++;
	}
	return (0);
}

static void	init_map_renderer(t_map *map)
{
	double	diag;

	map->renderer.x_axis_rotation_angle = 0;
	map->renderer.y_axis_rotation_angle = 0;
	map->renderer.z_axis_rotation_angle = 0;
	map->renderer.x_axis_translation_value = 0;
	map->renderer.y_axis_translation_value = 0;
	map->renderer.z_axis_translation_value = 0;
	diag = sqrt(map->height * map->height + map->width * map->width);
	if (WINDOW_WIDTH > WINDOW_HEIGHT)
		map->renderer.zoom_value = (WINDOW_HEIGHT - 200) / diag;
	else
		map->renderer.zoom_value = (WINDOW_WIDTH - 200) / diag;
}

int	init_map(t_map *map, char *str)
{
	int		fd;
	char	*line_str;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (fd);
	line_str = get_next_line(fd);
	if (!line_str)
		return (-2);
	map->height = 0;
	map->malloc_size = 0;
	map->tab = NULL;
	while (line_str)
	{
		map->height += 1;
		if (new_map(map, line_str))
			return ((free(line_str), gnl_close(fd), -4));
		free(line_str);
		line_str = get_next_line(fd);
	}
	translate_map(map, X_AXIS | Y_AXIS, -map->height / 2.);
	init_map_renderer(map);
	return (0);
}

static void	print_line(t_app *app, t_point p1, t_point p2, int color)
{
	int		i;
	t_point	res;
	double	dist;

	i = -1;
	res.x = p1.x;
	res.y = p1.y;
	res.z = p1.z;
	dist = get_distance(p1, p2);
	while (++i < dist)
	{
		res.x += (p2.x - p1.x) / dist;
		res.y += (p2.y - p1.y) / dist;
		put_pixel(app, round(res.x), round(res.y), color);
	}
}

int	get_color(t_point point, t_map *map)
{
	double	diff;

	diff = map->max_z - map->min_z;
	if (point.z < diff / 6 + map->min_z)
		return (0x00000080 + (char)(((point.z - map->min_z) / (diff / 6 - map->min_z)) * 128));
	if (point.z < 3 * diff / 6 + map->min_z)
		return (0x00008040);
	if (point.z < 5 * diff / 6 + map->min_z)
		return (0x00806000);
	else
		return (0x00FFFFFF);
}
#include <stdio.h>
void	print_map(t_map *map, t_app *app)
{
	int		i;
	t_point	p1;
	t_point	p2;

	i = -1;
	while (++i < map->width * map->height)
	{
		p1 = projection(map->tab[i], map->renderer);
		if ((i + 1) % map->width)
		{
			p2 = projection(map->tab[i + 1], map->renderer);
			if ((p1.y >= 0 || p2.y >= 0)
				&& (p1.y < WINDOW_HEIGHT || p2.y < WINDOW_HEIGHT)
				&& (p1.x > 0 || p2.x > 0)
				&& (p1.x < WINDOW_WIDTH || p2.x < WINDOW_WIDTH))
				print_line(app, p1, p2, get_color(map->tab[i], map));
		}
		if (i / map->width != map->height -1)
		{
			p2 = projection(map->tab[i + map->width], map->renderer);
			if ((p1.y >= 0 || p2.y >= 0)
				&& (p1.y < WINDOW_HEIGHT || p2.y < WINDOW_HEIGHT)
				&& (p1.x > 0 || p2.x > 0)
				&& (p1.x < WINDOW_WIDTH || p2.x < WINDOW_WIDTH))
				print_line(app, p1, p2, get_color(map->tab[i], map));
		}
	}
	flush(app);
}
