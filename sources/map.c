#include "fdf.h"
#include <stdlib.h>

void	destroy_map(t_map *map)
{
	free(map->points_tab);
}

static t_point	transform(t_context *context, t_point *point)
{
	return ((t_point){
		point->x * context->zoom,
		point->y * context->zoom,
		point->z * context->zoom,
		point->color
	});
}

void	draw_map(t_context *context)
{
	unsigned int	i;

	i = 0;
	while (i < context->map.height * context->map.width)
	{
		if (i % context->map.width != context->map.width - 1)
			draw_line(&context->renderer,
				transform(context, &context->map.points_tab[i]),
				transform(context, &context->map.points_tab[i + 1]));
		if (i / context->map.width != context->map.height - 1)
			draw_line(&context->renderer,
				transform(context, &context->map.points_tab[i]),
				transform(context,
					&context->map.points_tab[i + context->map.width]));
		i++;
	}
}
