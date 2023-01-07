#include <math.h>
#include "fdf.h"

double	get_distance(t_point p1, t_point p2)
{
	double	res;

	res = 0;
	res += (p1.x - p2.x) * (p1.x - p2.x);
	res += (p1.y - p2.y) * (p1.y - p2.y);
	res += (p1.z - p2.z) * (p1.z - p2.z);
	return (sqrt(res));
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

t_point	zoom(t_point point, double scale)
{
	point.x = point.x * scale;
	point.y = point.y * scale;
	point.z = point.z * scale;
	return (point);
}

void	zoom_map(t_map *map, double scale)
{
	int	i;

	i = 0;
	while (i < map->height * map->width)
	{
		map->tab[i] = zoom(map->tab[i], scale);
		i++;
	}
}

t_point	projection(t_point point, t_map_renderer m_rend)
{
	t_point	res;

	res = point;
	point = rotate(point, X_AXIS, m_rend.x_axis_rotation_angle);
	point = rotate(point, Y_AXIS, m_rend.y_axis_rotation_angle);
	point = rotate(point, Z_AXIS, m_rend.z_axis_rotation_angle);
	point = translate(point, X_AXIS, m_rend.x_axis_translation_value);
	point = translate(point, Y_AXIS, m_rend.y_axis_translation_value);
	point = translate(point, Z_AXIS, m_rend.z_axis_translation_value);
	point = zoom(point, m_rend.zoom_value);
	point.z *= m_rend.scale_factor;
	res.z = point.z;
	res.x = (sqrt(2.) / 2) * (point.x - point.y) + WINDOW_WIDTH / 2;
	res.y = (1. / sqrt(6.)) * (point.x + point.y) - sqrt(2. / 3.) * point.z + WINDOW_HEIGHT / 2;
	return (res);
}
