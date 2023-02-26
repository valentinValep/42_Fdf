#ifndef MAP_H
# define MAP_H

# include "render.h"
# include <stdlib.h>

typedef struct s_map
{
	t_point			*points_tab;
	size_t			malloc_size;
	unsigned int	height;
	unsigned int	width;
	int				min_z;
	int				max_z;
}	t_map;

int		parse_map(t_map *map, char *str);
void	destroy_map(t_map *map);

#endif
