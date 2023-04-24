#ifndef MAP_H
# define MAP_H

# include "render.h"
# include <stdlib.h>

# define GROUP_COUNT 100
# define GROUP_1 50
# define GROUP_2 60
# define GROUP_3 80
# define GROUP_4 90

typedef struct s_map
{
	t_point			position;
	t_point			rotation;
	t_point			*points_tab;
	size_t			malloc_size;
	float			translation_modifier;
	double			height_scale;
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
void	change_height_map(t_map *map, float scale);

#endif
