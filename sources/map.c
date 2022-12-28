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

static int	split_len(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		;
	return (i);
}

static int	new_map(t_map *map, char	**line_split, int len)
{
	int				i;
	t_point			new_point;

	upscale_map(map, len);
	if (!map->tab)
		return ((free_split(line_split, map->width), -1));
	i = -1;
	while (++i < len)
	{
		new_point.x = i % map->width * ZOOM + START_X;
		new_point.y = i / map->width * ZOOM + START_Y;
		new_point.z = ft_atoi(line_split[i % map->width]) * ZOOM;
		new_point.color = 0x00008000;
		map->tab[i] = new_point;
	}
	return ((free_split(line_split, map->width), 0));
}

int	init_map(t_map *map, char *str)
{
	int		fd;
	int		len;
	char	*line_str;
	char	**line_split;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (fd);
	line_str = get_next_line(fd);
	if (!line_str)
		return (-2);
	map->width = 0;
	map->malloc_size = 0;
	map->tab = NULL;
	len = 0;
	while (line_str)
	{
		line_split = ft_split(line_str, ' ');
		free(line_str);
		if (!map->width || map->width != split_len(line_split))
		{
			if (map->width)
			{
				if (map->tab)
					free(map->tab);
				return ((gnl_close(fd),
						free_split(line_split, split_len(line_split)), -3));
			}
			map->width = split_len(line_split);
		}
		len += map->width;
		if (new_map(map, line_split, len))
			return ((gnl_close(fd), -4));
		line_str = get_next_line(fd);
	}
	map->height = len / map->width;
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
