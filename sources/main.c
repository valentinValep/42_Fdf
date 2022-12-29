#include "fdf.h"
#include <stdlib.h>
#include <X11/keysymdef.h>
#include <mlx.h>
#include <libft.h>
// @TODO rm these include bellow
#include <unistd.h>
int	hook_keydown(int keycode, t_hook_args *args)
{
	if (keycode == XK_Escape)
		return (app_close(args->app));
	if (keycode == XK_Left)
	{
		rotate_map(args->map, X_AXIS, -5);
		rotate_map(args->map, Y_AXIS, -5);
		rotate_map(args->map, Z_AXIS, 5);
	}
	if (keycode == XK_Right)
	{
		rotate_map(args->map, X_AXIS, 5);
		rotate_map(args->map, Y_AXIS, 5);
		rotate_map(args->map, Z_AXIS, -5);
	}
	if (keycode == XK_y)
	{
		rotate_map(args->map, X_AXIS, 5);
		rotate_map(args->map, Y_AXIS, 5);
		rotate_map(args->map, Z_AXIS, 5);
	}
	if (keycode == XK_i)
	{
		rotate_map(args->map, X_AXIS, -5);
		rotate_map(args->map, Y_AXIS, -5);
		rotate_map(args->map, Z_AXIS, -5);
	}
	if (keycode == XK_Up)
	{
		rotate_map(args->map, X_AXIS, 5);
		rotate_map(args->map, Y_AXIS, -5);
	}
	if (keycode == XK_Down)
	{
		rotate_map(args->map, X_AXIS, -5);
		rotate_map(args->map, Y_AXIS, 5);
	}
	if (keycode == XK_a)
	{
		translate_map(args->map, X_AXIS, 50);
		translate_map(args->map, Y_AXIS, -50);
	}
	if (keycode == XK_d)
	{
		translate_map(args->map, X_AXIS, -50);
		translate_map(args->map, Y_AXIS, 50);
	}
	if (keycode == XK_w)
		translate_map(args->map, Z_AXIS, -50);
	if (keycode == XK_s)
		translate_map(args->map, Z_AXIS, 50);
	if (keycode == XK_r)
		zoom_map(args->map, 2);
	if (keycode == XK_f)
		zoom_map(args->map, 1/2);
	print_map(args->map, args->app);
	return (0);
}

int	hook_destroy(t_app *app)
{
	return (app_close(app));
}

int	main(int argc, char **argv)
{
	t_app		app;
	t_map		map;
	t_hook_args	hook_args;

	if (argc != 2)
		return (1);
	if (init_map(&map, argv[1]))
		return (2);
	if (!map.tab)
		return (3);
	init_app(&app);
	hook_args.app = &app;
	hook_args.map = &map;

	print_map(&map, &app);
	mlx_hook(app.window, 2, 1L << 0, hook_keydown, &hook_args);
	mlx_hook(app.window, 17, 0, hook_destroy, &app);
	mlx_loop(app.mlx);
	mlx_destroy_display(app.mlx);
	free(app.mlx);
	free(map.tab);
	return (0);
}
