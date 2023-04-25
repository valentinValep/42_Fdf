/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs_ticks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:05:18 by vlepille          #+#    #+#             */
/*   Updated: 2023/04/25 17:05:19 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/keysymdef.h>
#include <math.h>

void	key_hook_tick(t_context *context, int keycode)
{
	int	update;

	(void)context;
	(void)keycode;
	update = 1;
	if (keycode == XK_minus || keycode == XK_KP_Subtract)
		change_height_map(&context->map, DOWNSCALE);
	else if (keycode == XK_equal || keycode == XK_KP_Add)
		change_height_map(&context->map, UPSCALE);
	else if (keycode == XK_r)
		reset_rotation(&context->camera);
	else if (keycode == XK_Up)
		rotate_camera(&context->camera, 100, 0, 0);
	else if (keycode == XK_Down)
		rotate_camera(&context->camera, -100, 0, 0);
	else
		update = 0;
	if (update)
		context->map.is_update = 0;
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
			context->mouse.left_button.start_x,
			context->mouse.left_button.start_y);
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
		context->map.is_update = 1;
	}
}
