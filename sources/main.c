#include "fdf.h"
#include <stdlib.h>
#include <X11/keysymdef.h>
#include <mlx.h>
#include <libft.h>
// @TODO rm these include bellow
#include <unistd.h>
#include <stdio.h>
int	hook_keydown(int keycode, t_hook_args *args)
{
	if (keycode == XK_Escape)
		return (app_close(args->app));
	if (keycode == XK_Left)
	{
		//args->map->renderer.z_axis_rotation_angle += 5;
		rotate_map(args->map, Z_AXIS, 5);
	}
	if (keycode == XK_Right)
	{
		//args->map->renderer.z_axis_rotation_angle -= 5;
		rotate_map(args->map, Z_AXIS, -5);
	}
	if (keycode == XK_y)
	{
		//args->map->renderer.x_axis_rotation_angle += 5;
		//args->map->renderer.y_axis_rotation_angle += 5;
		//args->map->renderer.z_axis_rotation_angle += 5;
		rotate_map(args->map, X_AXIS | Y_AXIS | Z_AXIS, 5);
	}
	if (keycode == XK_i)
	{
		//args->map->renderer.x_axis_rotation_angle -= 5;
		//args->map->renderer.y_axis_rotation_angle -= 5;
		//args->map->renderer.z_axis_rotation_angle -= 5;
		rotate_map(args->map, X_AXIS | Y_AXIS | Z_AXIS, -5);
	}
	if (keycode == XK_Up)
	{
		//args->map->renderer.x_axis_rotation_angle += 5;
		//args->map->renderer.y_axis_rotation_angle -= 5;
		rotate_map(args->map, X_AXIS, 5);
		rotate_map(args->map, Y_AXIS, -5);
	}
	if (keycode == XK_Down)
	{
		//args->map->renderer.x_axis_rotation_angle -= 5;
		//args->map->renderer.y_axis_rotation_angle += 5;
		rotate_map(args->map, X_AXIS, -5);
		rotate_map(args->map, Y_AXIS, 5);
	}
	if (keycode == XK_a)
	{
		args->map->renderer.x_axis_translation_value += 50 / args->map->renderer.zoom_value;
		args->map->renderer.y_axis_translation_value -= 50 / args->map->renderer.zoom_value;
		//translate_map(args->map, X_AXIS, 50);
		//translate_map(args->map, Y_AXIS, -50);
	}
	if (keycode == XK_d)
	{
		args->map->renderer.x_axis_translation_value -= 50 / args->map->renderer.zoom_value;
		args->map->renderer.y_axis_translation_value += 50 / args->map->renderer.zoom_value;
		//translate_map(args->map, X_AXIS, -50);
		//translate_map(args->map, Y_AXIS, 50);
	}
	if (keycode == XK_w)
	{
		args->map->renderer.z_axis_translation_value -= 50 / args->map->renderer.zoom_value;
		//translate_map(args->map, Z_AXIS, -50);
	}
	if (keycode == XK_s)
	{
		args->map->renderer.z_axis_translation_value += 50 / args->map->renderer.zoom_value;
		//translate_map(args->map, Z_AXIS, 50);
	}
	if (keycode == XK_r)
		if (args->map->renderer.zoom_value < 5000)
			args->map->renderer.zoom_value *= 2;
	if (keycode == XK_f)
		args->map->renderer.zoom_value *= 1. / 2;
	if (keycode == XK_t)
		args->map->renderer.scale_factor += 0.1;
	if (keycode == XK_g)
		args->map->renderer.scale_factor -= 0.1;
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
