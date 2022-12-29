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
		new_point.x = i % map->width - map->width / 2.;
		new_point.y = i / map->width;
		new_point.z = ft_atoi(current_word);
		current_word = get_next_word(current_word);
		if (!*current_word && i != map->height * map->width - 1)
			return ((free(map->tab), -2));
		new_point.color = 0x00008000;
		map->tab[i] = new_point;
		i++;
	}
	return (0);
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
	return (0);
}

static void	print_line(t_app *app, t_point p1, t_point p2)
{
	int		i;
	double	x;
	double	y;
	double	z;
	int		color;

	i = -1;
	x = p1.x;
	y = p1.y;
	z = p1.z;
	color = p1.color;
	while (++i < POINTS_PER_LINE)
	{
		x += (p2.x - p1.x) / POINTS_PER_LINE;
		y += (p2.y - p1.y) / POINTS_PER_LINE;
		z += (p2.z - p1.z) / POINTS_PER_LINE;
		color = 0x00FFFFFF;
		put_pixel(app, round(x), round(y), color);
	}
}

void	print_map(t_map *map, t_app *app)
{
	int	i;

	i = -1;
	while (++i < map->width * map->height)
	{
		if ((i + 1) % map->width)
			print_line(
				app, projection(map->tab[i]),
				projection(map->tab[i + 1]));
		if (i / map->width != map->height - 1)
			print_line(
				app, projection(map->tab[i]),
				projection(map->tab[i + map->width]));
	}
	flush(app);
}
