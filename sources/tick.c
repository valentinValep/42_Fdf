/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tick.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:05:26 by vlepille          #+#    #+#             */
/*   Updated: 2023/04/25 17:05:27 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/keysymdef.h>
#include <X11/X.h>

static void	button_queue_hook(t_button *button, t_queue_content content)
{
	button->is_clicked = IS_PRESSED;
	button->start_x = content.x;
	button->start_y = content.y;
}

static void	mouse_button_press_hook(t_context *context, t_queue_content content)
{
	if (content.button == Button1
		&& !context->mouse.right_button.is_clicked)
		button_queue_hook(&context->mouse.right_button, content);
	if (content.button == Button2)
	{
		swap_projection(&context->renderer);
		context->map.is_update = 0;
	}
	if (content.button == Button3
		&& !context->mouse.left_button.is_clicked)
		button_queue_hook(&context->mouse.left_button, content);
	if (content.button == Button4)
	{
		context->camera.zoom *= ZOOM_MODIFIER;
		context->map.is_update = 0;
	}
	if (content.button == Button5)
	{
		context->camera.zoom /= ZOOM_MODIFIER;
		context->map.is_update = 0;
	}
}

static void	mouse_hook(t_context *context, t_queue_content content)
{
	if (content.type == BUTTON_PRESS_TYPE)
		mouse_button_press_hook(context, content);
	else if (content.type == BUTTON_RELEASE_TYPE)
	{
		if (content.button == Button1)
			context->mouse.right_button.is_clicked = WAS_PRESSED;
		if (content.button == Button3)
			context->mouse.left_button.is_clicked = WAS_PRESSED;
	}
	context->mouse.x = content.x;
	context->mouse.y = content.y;
}

int	loop_hook(t_context *context)
{
	t_queue_content	content;

	while (queue_next(&context->queue, &content))
	{
		if (content.type == KEYBOARD_TYPE)
		{
			if (content.button == XK_Escape)
				return (mlx_loop_end(context->renderer.mlx));
			key_hook_tick(context, content.button);
		}
		else
			mouse_hook(context, content);
	}
	left_button_tick(context);
	right_button_tick(context);
	draw_tick(context);
	render_tick(&context->renderer);
	return (0);
}
