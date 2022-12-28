#include <math.h>
#include "fdf.h"

t_point	projection(t_point point)
{
	t_point	res;

	res.color = point.color;
	res.z = point.z;
	res.x = (sqrt(2.) / 2) * (point.x - point.y) + WINDOW_WIDTH / 2;
	res.y = (1. / sqrt(6.)) * (point.x + point.y) - sqrt(2. / 3.) * point.z;
	return (res);
}

t_point	rotate(t_point point, char axis_flag, double degree)
{
	double	ex_value;

	degree = degree / 90;
	if (axis_flag & X_AXIS)
	{
		ex_value = point.y;
		point.y = point.y * cos((double) degree)
			+ point.z * (-sin((double) degree));
		point.z = point.z * cos((double) degree)
			+ ex_value * sin((double) degree);
	}
	if (axis_flag & Y_AXIS)
	{
		ex_value = point.x;
		point.x = point.x * cos((double) degree)
			+ point.z * sin((double) degree);
		point.z = ex_value * (-sin((double) degree))
			+ point.z * cos((double) degree);
	}
	if (axis_flag & Z_AXIS)
	{
		ex_value = point.x;
		point.x = point.x * cos((double) degree)
			+ point.y * (-sin((double) degree));
		point.y = ex_value * sin((double) degree)
			+ point.y * cos((double) degree);
	}
	return (point);
}

void	rotate_map(t_map *map, char axis_flag, double degree)
{
	int	i;

	i = 0;
	while (i < map->height * map->width)
	{
		map->tab[i] = rotate(map->tab[i], axis_flag, degree);
		i++;
	}
}

t_point	translate(t_point point, char axis_flag, double value)
{
	if (axis_flag & X_AXIS)
		point.x += value;
	if (axis_flag & Y_AXIS)
		point.y += value;
	if (axis_flag & Z_AXIS)
		point.z += value;
	return (point);
}

void	translate_map(t_map *map, char axis_flag, double value)
{
	int	i;

	i = 0;
	while (i < map->height * map->width)
	{
		map->tab[i] = translate(map->tab[i], axis_flag, value);
		i++;
	}
}
