#include "fdf.h"
#include <math.h>

t_point	transform(t_context *context, t_point *point)
{
	const t_vector	rad = (t_vector){
		context->camera.rotation.x * M_PI / ROTATION_MODIFIER,
		context->camera.rotation.y * M_PI / ROTATION_MODIFIER,
		context->camera.rotation.z * M_PI / ROTATION_MODIFIER};
	t_vector		tmp;
	t_point			res;

	res.color = point->color;
	tmp.x = point->x;
	tmp.y = point->y;
	tmp.z = point->z;
	res.x = cos(rad.z) * cos(rad.y) * tmp.x
		+ ((cos(rad.z) * sin(rad.y) * sin(rad.x))
			- (sin(rad.z) * cos(rad.x))) * tmp.y
		+ ((cos(rad.z) * sin(rad.y) * cos(rad.x))
			+ (sin(rad.z) * sin(rad.x))) * tmp.z;
	res.y = sin(rad.z) * cos(rad.y) * tmp.x
		+ ((sin(rad.z) * sin(rad.y) * sin(rad.x))
			+ (cos(rad.z) * cos(rad.x))) * tmp.y
		+ ((sin(rad.z) * sin(rad.y) * cos(rad.x))
			- (cos(rad.z) * sin(rad.x))) * tmp.z;
	res.z = -sin(rad.y) * tmp.x
		+ (cos(rad.y) * sin(rad.x)) * tmp.y
		+ (cos(rad.y) * cos(rad.x)) * tmp.z;
	res.x += context->camera.translation.x * context->map.translation_modifier;
	res.y += context->camera.translation.y * context->map.translation_modifier;
	res.z += context->camera.translation.z * context->map.translation_modifier;
	res.x *= context->camera.zoom;
	res.y *= context->camera.zoom;
	res.z *= context->camera.zoom;
	return (res);
}

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

void	rotate_camera(t_camera *camera, double x_axis, double y_axis, double z_axis)
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
	unsigned int	i;

	if (map->height_scale > 32)
		return ;
	map->height_scale *= scale;
	i = 0;
	while (i < map->height * map->width)
	{
		map->points_tab[i].z *= scale;
		i++;
	}
}
