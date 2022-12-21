#include <stdlib.h>
#include <mlx.h>
#include <libft.h>
#include "fdf.h"
// @TODO rm these include bellow
#include <unistd.h>
int	main(void)
{
	t_app	app;
	t_map	map;

	init_app(&app);
	init_map(&map, NULL);
	if (!map.tab)
		return (1);

	print_map(&map, &app);
	mlx_loop(app.mlx);
	free(map.tab);
}
