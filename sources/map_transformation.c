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

void	rotate_map_side(t_map	*map, double radiant)
{
	unsigned int	i;

	i = 0;
	while (i < map->height * map->width)
	{
		map->points_tab[i].x
			= map->points_tab[i].x * cos(radiant)
			+ map->points_tab[i].y * -sin(radiant);
		map->points_tab[i].y
			= map->points_tab[i].x * sin(radiant)
			+ map->points_tab[i].y * cos(radiant);
		i++;
	}
}
