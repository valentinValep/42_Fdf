/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:05:17 by vlepille          #+#    #+#             */
/*   Updated: 2023/04/25 17:05:18 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <unistd.h>

int	keydown_hook(int keycode, t_context *context)
{
	if (!add_queue(&context->queue,
			(t_queue_content){keycode, 0, 0, KEYBOARD_TYPE}))
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
