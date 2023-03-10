#include "fdf.h"
#include <X11/keysymdef.h>
#include <unistd.h>
#include <math.h>

#include <stdio.h> // @TODO rm
int	keydown_hook(int keycode, t_context *context)
{
	if (!add_queue(&context->queue, (t_content){keycode, 0, 0, KEYBOARD_TYPE}))
	{
		write(STDERR_FILENO, "Queue add failed\n", 17);
		return (mlx_loop_end(context->renderer.mlx));
	}
	return (0);
}

int	button_press_hook(int button, int x, int y, t_context *context)
{
	if (!add_queue(&context->queue,
			(t_content){button, x, y, BUTTON_PRESS_TYPE}))
	{
		write(STDERR_FILENO, "Queue add failed\n", 17);
		return (mlx_loop_end(context->renderer.mlx));
	}
	return (0);
}

int	button_release_hook(int button, int x, int y, t_context *context)
{
	if (!add_queue(&context->queue,
			(t_content){button, x, y, BUTTON_RELEASE_TYPE}))
	{
		write(STDERR_FILENO, "Queue add failed\n", 17);
		return (mlx_loop_end(context->renderer.mlx));
	}
	return (0);
}

int	motion_hook(int x, int y, t_context *context)
{
	if (!add_queue(&context->queue,
			(t_content){x, y, 0, MOTION_TYPE}))
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
	if (keycode == XK_w)
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
	else if (keycode == XK_c)
	{
		swap_projection(&context->renderer);
		context->map.is_update = 0;
	}
}
