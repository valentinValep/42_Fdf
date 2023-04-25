#include "fdf.h"
#include "error.h"

void	upscale_map(t_map *map, size_t size)
{
	t_point	*new;
	size_t	i;

	if (map->malloc_size >= size)
		return ;
	while (map->malloc_size < size)
		map->malloc_size = map->malloc_size * 2 + (!map->malloc_size);
	new = malloc((map->malloc_size) * sizeof(t_point));
	if (!new)
	{
		if (map->points_tab)
			free(map->points_tab);
		map->points_tab = NULL;
		basic_error("A malloc failed\n", 1);
		return ;
	}
	i = -1;
	while (++i < size - map->width)
		new[i] = map->points_tab[i];
	free(map->points_tab);
	map->points_tab = new;
}
