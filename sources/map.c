#include <stdlib.h>
#include <math.h>
#include <mlx.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"
#include "fdf.h"

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
	t_point *const	old_tab = map->tab;
	int				i;
	t_point			new_point;

	map->tab = malloc(len * sizeof(t_point));
	if (!map->tab)
	{
		free(old_tab);
		free_split(line_split, map->width);
		return (-1);
	}
	i = -1;
	while (++i < len - map->width)
	{
		map->tab[i] = old_tab[i];
	}
	i--;
	while (++i < len)
	{
		new_point.x = i % map->width * ZOOM + START_X;
		new_point.y = i / map->width * ZOOM + START_Y;
		new_point.z = ft_atoi(line_split[i % map->width]) * ZOOM / 15;
		map->tab[i] = new_point;
	}
	return ((free(old_tab), free_split(line_split, map->width), 0));
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
	map->tab = NULL;
	len = 0;
	while (line_str)
	{
		line_split = ft_split(line_str, ' ');
		if (!map->width || map->width != split_len(line_split))
		{
			if (map->width)
			{
				if (map->tab)
					free(map->tab);
				return ((free_split(line_split, split_len(line_split)), -3));
			}
			map->width = split_len(line_split);
		}
		len += map->width;
		if (new_map(map, line_split, len))
			return (-4);
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

	i = -1;
	x = p1.x;
	y = p1.y;
	while (++i < POINTS_PER_LINE)
	{
		x += (p2.x - p1.x) / POINTS_PER_LINE;
		y += (p2.y - p1.y) / POINTS_PER_LINE;
		put_pixel(app, round(x), round(y), 0x00FFFFFF);
	}
}

static void	print_point(t_app *app, t_point p1)
{
	p1.x = p1.x;
	p1.y = p1.y;
	put_pixel(app, round(p1.x), round(p1.y), 0x00FF0000);
	put_pixel(app, round(p1.x + 1), round(p1.y), 0x00FF0000);
	put_pixel(app, round(p1.x), round(p1.y + 1), 0x00FF0000);
	put_pixel(app, round(p1.x - 1), round(p1.y), 0x00FF0000);
	put_pixel(app, round(p1.x), round(p1.y - 1), 0x00FF0000);
	put_pixel(app, round(p1.x + 1), round(p1.y + 1), 0x00FF0000);
	put_pixel(app, round(p1.x - 1), round(p1.y - 1), 0x00FF0000);
	put_pixel(app, round(p1.x + 1), round(p1.y - 1), 0x00FF0000);
	put_pixel(app, round(p1.x - 1), round(p1.y + 1), 0x00FF0000);
	put_pixel(app, round(p1.x + 2), round(p1.y), 0x00FF0000);
	put_pixel(app, round(p1.x), round(p1.y + 2), 0x00FF0000);
	put_pixel(app, round(p1.x - 2), round(p1.y), 0x00FF0000);
	put_pixel(app, round(p1.x), round(p1.y - 2), 0x00FF0000);
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
		print_point(app, projection(map->tab[i]));
	}
	print_line(app, projection((t_point){-2000, 0, 0}), projection((t_point){2000, 0, 0}));
	print_line(app, projection((t_point){0, -2000, 0}), projection((t_point){0, 2000, 0}));
	print_point(app, projection((t_point){0, 0, 0}));
	flush(app);
}
