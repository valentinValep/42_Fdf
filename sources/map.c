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

// start_color + ((range_color
//	* (point.z * 10 / diff - start_range_z)
//	* (100 / (end_range_z - start_range_z))) / 100 << color_shift)
static int	get_color(t_point point, t_map *map)
{
	const double	diff = map->max_z - map->min_z;

	if (point.z < 2 * diff / 10 + map->min_z)
		return (0x00000080
			+ (0x80 * (point.z * 10 / diff) * 50) / 100);
	if (point.z < 6 * diff / 10 + map->min_z)
		return (0x000000FF
			-(0xc0 * (point.z * 10 / diff - 2) * 25) / 100
			+((int)((0xFF * (point.z * 10 / diff - 2) * 25) / 100) << 8)
			+((int)((0x40 * (point.z * 10 / diff - 2) * 25) / 100) << 16));
	if (point.z < 9 * diff / 10 + map->min_z)
		return (0x0040FF40
			-(0x40 * (point.z * 10 / diff - 2) * (100 / (3.))) / 100
			-((int)((0xc0 * (point.z * 10 / diff - 2)
					* (100 / (3.))) / 100) << 8)
			+((int)((0x40 * (point.z * 10 / diff - 2)
					* (100 / (3.))) / 100) << 8));
	else
		return (0x00FFFFFF);
}

void	set_map_color(t_map *map)
{
	unsigned int	i;

	i = -1;
	while (++i < map->height * map->width)
	{
		map->points_tab[i].color = get_color(map->points_tab[i], map);
	}
}
