#include "fdf.h"
#include <X11/keysymdef.h>
#include <unistd.h>
#include <math.h>

#include <stdio.h> // @TODO rm
int	keydown_hook(int keycode, t_context *context)
{
	if (!add_queue(&context->queue, (t_queue_content){keycode, 0, 0, KEYBOARD_TYPE}))
	{
		write(STDERR_FILENO, "Queue add failed\n", 17);
		return (mlx_loop_end(context->renderer.mlx));
	}
	return (0);
}

int	button_press_hook(int button, int x, int y, t_context *context)
{
	if (!add_queue(&context->queue,
			(t_queue_content){button, x, y, BUTTON_PRESS_TYPE}))
	{
		write(STDERR_FILENO, "Queue add failed\n", 17);
		return (mlx_loop_end(context->renderer.mlx));
	}
	return (0);
}

int	button_release_hook(int button, int x, int y, t_context *context)
{
	if (!add_queue(&context->queue,
			(t_queue_content){button, x, y, BUTTON_RELEASE_TYPE}))
	{
		write(STDERR_FILENO, "Queue add failed\n", 17);
		return (mlx_loop_end(context->renderer.mlx));
	}
	return (0);
}

int	motion_hook(int x, int y, t_context *context)
{
	if (!add_queue(&context->queue,
			(t_queue_content){0, x, y, MOTION_TYPE}))
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
	(void)context;
	(void)keycode;
	if (keycode == XK_minus || keycode == XK_KP_Subtract)
	{
		change_height_map(&context->map, DOWNSCALE);
		context->map.is_update = 0;
	}
	else if (keycode == XK_equal || keycode == XK_KP_Add)
	{
		change_height_map(&context->map, UPSCALE);
		context->map.is_update = 0;
	}
	else if (keycode == XK_r)
	{
		reset_rotation(&context->camera);
		context->map.is_update = 0;
	}
	else if (keycode == XK_Up)
	{
		rotate_camera(&context->camera, 100, 0, 0);
		context->map.is_update = 0;
	}
	else if (keycode == XK_Down)
	{
		rotate_camera(&context->camera, -100, 0, 0);
		context->map.is_update = 0;
	}
	return ;
}

void	button_queue_hook(t_button *button, t_queue_content content)
{
	button->is_clicked = IS_PRESSED;
	button->start_x = content.x;
	button->start_y = content.y;
}

void	left_button_tick(t_context *context)
{
	if (context->mouse.left_button.is_clicked == IS_PRESSED)
	{
		mlx_mouse_hide(context->renderer.mlx, context->renderer.window);
		rotate_camera(&context->camera,
			-(context->mouse.y - context->mouse.left_button.start_y),
			0,
			context->mouse.x - context->mouse.left_button.start_x);
		mlx_mouse_move(context->renderer.mlx, context->renderer.window,
			context->mouse.left_button.start_x, context->mouse.left_button.start_y);
		context->mouse.x = context->mouse.left_button.start_x;
		context->mouse.y = context->mouse.left_button.start_y;
		context->map.is_update = 0;
	}
	if (context->mouse.left_button.is_clicked == WAS_PRESSED)
	{
		mlx_mouse_show(context->renderer.mlx, context->renderer.window);
		context->mouse.left_button.is_clicked = UNPRESSED;
	}
}

void	right_button_tick(t_context *context)
{
	if (context->mouse.right_button.is_clicked == IS_PRESSED)
	{
		translate_camera(&context->camera,
			(context->mouse.y - context->mouse.right_button.start_y)
			+ (context->mouse.x - context->mouse.right_button.start_x),
			(context->mouse.y - context->mouse.right_button.start_y)
			- (context->mouse.x - context->mouse.right_button.start_x),
			0);
		context->mouse.right_button.start_x = context->mouse.x;
		context->mouse.right_button.start_y = context->mouse.y;
		context->map.is_update = 0;
	}
	if (context->mouse.right_button.is_clicked == WAS_PRESSED)
		context->mouse.right_button.is_clicked = UNPRESSED;
}

void	draw_tick(t_context *context)
{
	if (!context->map.is_update)
	{
		clear_renderer(&context->renderer);
		draw_map(context);
		//put_origins(&context->renderer);
		context->map.is_update = 1;
	}
}
