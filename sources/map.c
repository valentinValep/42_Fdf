#include "fdf.h"
#include <stdlib.h>

void	destroy_map(t_map *map)
{
	free(map->points_tab);
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

static int	get_color(t_point point, t_map *map)
{
	const double	diff = map->max_z - map->min_z;
	const double	group_size = diff / 10;
	const int		height_group = (point.z - map->min_z) / group_size;

	if (height_group < GROUP_1)
		return (0x00000080
			+ (int)(0x80 * ((point.z - map->min_z) / (group_size * GROUP_1))));
	if (height_group < GROUP_2)
		return (0x000000FF
			-(int)(0xc0 * ((point.z - map->min_z - group_size * GROUP_1)
				/ (group_size * (GROUP_2 - GROUP_1))))
			+(((int)(0xFF * ((point.z - map->min_z - group_size * GROUP_1)
				/ (group_size * (GROUP_2 - GROUP_1))))) << 8)
			+(((int)(0x40 * ((point.z - map->min_z - group_size * GROUP_1)
				/ (group_size * (GROUP_2 - GROUP_1))))) << 16));
	if (height_group < GROUP_3)
		return (0x0040FF40
			-(int)(0x40 * ((point.z - map->min_z - group_size * GROUP_2)
				/ (group_size * (GROUP_3 - GROUP_2))))
			-(((int)(0xc0 * ((point.z - map->min_z - group_size * GROUP_2)
				/ (group_size * (GROUP_3 - GROUP_2))))) << 8)
			+(((int)(0x40 * ((point.z - map->min_z - group_size * GROUP_2)
				/ (group_size * (GROUP_3 - GROUP_2))))) << 16));
	if (height_group < 9)
		return (0x00804000);
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
