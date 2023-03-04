#include "fdf.h"
#include <math.h>

t_point	transform(t_context *context, t_point *point)
{
	return ((t_point){
		point->x * context->camera.zoom,
		point->y * context->camera.zoom,
		point->z * context->camera.zoom,
		point->color
	});
}

void	translate_map(t_map	*map, int x_axis, int y_axis, int z_axis)
{
	unsigned int	i;

	i = 0;
	while (i < map->height * map->width)
	{
		map->points_tab[i].x += TRANSLATION_MODIFIER * x_axis;
		map->points_tab[i].y += TRANSLATION_MODIFIER * y_axis;
		map->points_tab[i].z += TRANSLATION_MODIFIER * z_axis;
		i++;
	}
}

void	rotate_map(t_map *map, double x_axis, double y_axis, double z_axis)
{
	unsigned int	i;
	double			*tmp;
	const double	rad[3] = {z_axis * M_PI / ROTATION_MODIFIER,
		y_axis * M_PI / ROTATION_MODIFIER, x_axis * M_PI / ROTATION_MODIFIER};

	i = 0;
	while (i < map->height * map->width)
	{
		tmp = (double [3]){map->points_tab[i].x,
			map->points_tab[i].y, map->points_tab[i].z};
		map->points_tab[i].x = cos(rad[0]) * cos(rad[1]) * tmp[0]
			+ ((cos(rad[0]) * sin(rad[1]) * sin(rad[2]))
				- (sin(rad[0]) * cos(rad[2]))) * tmp[1]
			+ ((cos(rad[0]) * sin(rad[1]) * cos(rad[2]))
				+ (sin(rad[0]) * sin(rad[2]))) * tmp[2];
		map->points_tab[i].y = sin(rad[0]) * cos(rad[1]) * tmp[0]
			+ ((sin(rad[0]) * sin(rad[1]) * sin(rad[2]))
				+ (cos(rad[0]) * cos(rad[2]))) * tmp[1]
			+ ((sin(rad[0]) * sin(rad[1]) * cos(rad[2]))
				- (cos(rad[0]) * sin(rad[2]))) * tmp[2];
		map->points_tab[i].z = -sin(rad[1]) * tmp[0]
			+ (cos(rad[1]) * sin(rad[2])) * tmp[1]
			+ (cos(rad[1]) * cos(rad[2])) * tmp[2];

		//tmp = map->points_tab[i].y;
		//map->points_tab[i].y
		//	= tmp[1] * cos(alpha)
		//	+ map->points_tab[i].z * -sin(alpha);
		//map->points_tab[i].z
		//	= tmp[1] * sin(alpha)
		//	+ map->points_tab[i].z * cos(alpha);

		//tmp = map->points_tab[i].x;
		//map->points_tab[i].x
		//	= tmp[0] * cos(beta)
		//	+ map->points_tab[i].z * sin(beta);
		//map->points_tab[i].z
		//	= tmp[0] * -sin(beta)
		//	+ map->points_tab[i].z * cos(beta);

		//tmp = map->points_tab[i].x;
		//map->points_tab[i].x
		//	= tmp[0] * cos(gamma)
		//	+ map->points_tab[i].y * -sin(gamma);
		//map->points_tab[i].y
		//	= tmp[0] * sin(gamma)
		//	+ map->points_tab[i].y * cos(gamma);
		i++;
	}
}
