#include "fdf.h"
#include <X11/keysymdef.h>
#include <unistd.h>
#include <math.h>

#include <stdio.h> // @TODO rm
int	keydown_hook(int keycode, t_context *context)
{
	if (!add_queue(&context->queue, keycode))
	{
		write(STDERR_FILENO, "Queue add failed\n", 17);
		return (mlx_loop_end(context->renderer.mlx));
	}
	return (0);
}

int	destroy_hook(t_renderer *renderer)
{
	return (mlx_loop_end(renderer->mlx));
}

void	key_hook_tick(t_context *context, int keycode)
{
	if (keycode == XK_1)
		clear_renderer(&context->renderer);
	else if (keycode == XK_2)
		put_origins(&context->renderer);
	else if (keycode == XK_3)
		draw_cube(&context->renderer, (t_point){20., -20., -20., 0x00FFFF00}, 50.);
	else if (keycode == XK_4)
		draw_cube(&context->renderer, (t_point){20., 10., 10., 0x00FFFFFF}, 75.);
	else if (keycode == XK_minus || keycode == XK_KP_Subtract)
	{
		context->camera.zoom /= ZOOM_MODIFIER;
		context->map.is_update = 0;
	}
	else if (keycode == XK_equal || keycode == XK_KP_Add)
	{
		context->camera.zoom *= ZOOM_MODIFIER;
		context->map.is_update = 0;
	}
	else if (keycode == XK_w)
	{
		translate_map(&context->map, 1, 1, 0);
		context->map.is_update = 0;
	}
	else if (keycode == XK_s)
	{
		translate_map(&context->map, -1, -1, 0);
		context->map.is_update = 0;
	}
	else if (keycode == XK_a)
	{
		translate_map(&context->map, 1, -1, 0);
		context->map.is_update = 0;
	}
	else if (keycode == XK_d)
	{
		translate_map(&context->map, -1, 1, 0);
		context->map.is_update = 0;
	}
	else if (keycode == XK_Right)
	{
		rotate_map(&context->map, 0, 0, 1);
		context->map.is_update = 0;
	}
	else if (keycode == XK_Left)
	{
		rotate_map(&context->map, 0, 0, -1);
		context->map.is_update = 0;
	}
	else if (keycode == XK_Up)
	{
		rotate_map(&context->map, 1, -1, 0);
		context->map.is_update = 0;
	}
	else if (keycode == XK_Down)
	{
		rotate_map(&context->map, -1, 1, 0);
		context->map.is_update = 0;
	}
}
