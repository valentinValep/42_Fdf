#ifndef MAP_H
# define MAP_H

# include "render.h"
# include <stdlib.h>

# define GROUP_1 1
# define GROUP_2 3
# define GROUP_3 6
# define GROUP_4 9

typedef struct s_map
{
	t_point			*points_tab;
	size_t			malloc_size;
	float			translation_modifier;
	unsigned int	height;
	unsigned int	width;
	int				min_z;
	int				max_z;
	int				is_update;
}	t_map;

typedef struct s_context	t_context;

int		parse_map(t_map *map, char *str);
void	destroy_map(t_map *map);
void	draw_map(t_context *context);
void	set_map_color(t_map *map);

void	translate_map(t_map	*map, int x_axis, int y_axis, int z_axis);
void	rotate_map(t_map	*map, double x_axis, double y_axis, double z_axis);

#endif
