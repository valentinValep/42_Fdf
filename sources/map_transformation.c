#include "fdf.h"

void	translate_camera(t_camera *camera, int x_axis, int y_axis, int z_axis)
{
	camera->translation.x += x_axis;
	camera->translation.y += y_axis;
	camera->translation.z += z_axis;
}

void	translate_map(t_map	*map, int x_axis, int y_axis, int z_axis)
{
	unsigned int	i;

	i = 0;
	while (i < map->height * map->width)
	{
		map->points_tab[i].x += x_axis;
		map->points_tab[i].y += y_axis;
		map->points_tab[i].z += z_axis;
		i++;
	}
}

void	rotate_camera(
	t_camera *camera, double x_axis, double y_axis, double z_axis)
{
	camera->rotation.x += x_axis;
	camera->rotation.y += y_axis;
	camera->rotation.z += z_axis;
}

void	reset_rotation(t_camera *camera)
{
	camera->rotation.x = 0;
	camera->rotation.y = 0;
	camera->rotation.z = 0;
}

void	change_height_map(t_map *map, float scale)
{
	if (map->height_scale > 32)
		return ;
	map->height_scale *= scale;
}
