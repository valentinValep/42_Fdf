#include <mlx.h>
#include <libft.h>
#include "fdf.h"
// @TODO
int	main(void)
{
	t_app	app;

	init_app(&app);
	put_pixel(&app, 5, 5, 0x00FF0000);
	flush(&app);
	for (int i = 0; i < 2000; i++)
		put_pixel(&app, i, 5, 0x00FF0000);
	read()
	flush(&app);
	mlx_loop(app.mlx);
}
