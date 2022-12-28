#include <stdlib.h>
#include <mlx.h>
#include <libft.h>
#include "fdf.h"
// @TODO rm these include bellow
#include <unistd.h>
int	main(int argc, char **argv)
{
	t_app	app;
	t_map	map;

	if (argc != 2)
		return (1);
	init_app(&app);
	if (init_map(&map, argv[1]))
		return (2);
	if (!map.tab)
		return (3);

	print_map(&map, &app);
	mlx_hook(app.window, 2, 1L << 0, app_close, &app);
	mlx_loop(app.mlx);
	mlx_destroy_display(app.mlx);
	free(app.mlx);
	free(map.tab);
	return (0);
}
