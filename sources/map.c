#include "fdf.h"
#include <stdlib.h>

void	destroy_map(t_map *map)
{
	free(map->points_tab);
}

void	draw_map(t_context *context)
{
	unsigned int	i;
	t_point			tranformed_point;

	i = 0;
	while (i < context->map.height * context->map.width)
	{
		tranformed_point = (t_point){
			context->map.points_tab[i].x * context->zoom,
			context->map.points_tab[i].y * context->zoom,
			context->map.points_tab[i].z * context->zoom,
			context->map.points_tab[i].color
		};
		draw_point(&context->renderer, &tranformed_point);
		i++;
	}
}
