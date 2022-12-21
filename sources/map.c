#include <stdlib.h>
#include <math.h>
#include <mlx.h>
#include "fdf.h"

void	init_map(t_map *map, char *str)
{
	(void) str;
	map->height = 5;
	map->width = 5;
	map->tab = malloc((25) * sizeof(t_point));
	if (!map->tab)
		return ;
	for (int i = 0; i < 25; i++)
		map->tab[i] = (t_point){i % 5, i / 5, (i % 5 == (i / 5)) * 3 + 1};
}

static void	print_line(t_app *app, t_point p1, t_point p2)
{
	int		i;
	double	x;
	double	y;

	p1.x = p1.x * ZOOM + START_X;
	p1.y = p1.y * ZOOM + START_Y;
	p2.x = p2.x * ZOOM + START_X;
	p2.y = p2.y * ZOOM + START_Y;
	i = -1;
	x = p1.x;
	y = p1.y;
	while (++i < POINTS_PER_LINE)
	{
		x += ((p2.x - p1.x) * ((p2.x - p1.x > 0) * 2 - 1)) / POINTS_PER_LINE;
		y += ((p2.y - p1.y) * ((p2.y - p1.y > 0) * 2 - 1)) / POINTS_PER_LINE;
		put_pixel(app, round(x), round(y), 0x00FFFFFF);
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
				app, rotate(map->tab[i], Z_AXIS, 5/90.),
				rotate(map->tab[i + 1], Z_AXIS, 5/90.));
		if (i / map->width != map->height - 1)
			print_line(
				app, rotate(map->tab[i - 1], Z_AXIS, 5/90.),
				rotate(map->tab[i + map->width], Z_AXIS, 5/90.));
	}
	flush(app);
}
