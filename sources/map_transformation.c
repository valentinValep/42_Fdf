#include "fdf.h"
#include <math.h>

t_point	transform(t_context *context, t_point *point)
{
	return ((t_point){
		point->x * context->camera.zoom + context->camera.translation_vec.x,
		point->y * context->camera.zoom + context->camera.translation_vec.y,
		point->z * context->camera.zoom + context->camera.translation_vec.z,
		point->color
	});
}

void	rotate_map_side(t_map	*map, double radiant)
{
	unsigned int	i;

	i = 0;
	while (i < map->height * map->width)
	{
		map->points_tab[i].x = map->points_tab[i].x * cos(radiant)
			+ map->points_tab[i].y * -sin(radiant);
		map->points_tab[i].y = map->points_tab[i].x * sin(radiant)
			+ map->points_tab[i].y * cos(radiant);
		i++;
	}
}
