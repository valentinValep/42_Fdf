/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:05:19 by vlepille          #+#    #+#             */
/*   Updated: 2023/04/25 17:05:20 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "error.h"
#include <unistd.h>
#include <X11/X.h>
#include <stdlib.h>
#include <math.h>

void	init_context(t_context	*context, char **argv)
{
	init_queue(&context->queue);
	if (parse_map(&context->map, argv[1]))
	{
		destroy_queue(&context->queue);
		exit(1);
	}
	if (init_renderer(&context->renderer))
	{
		destroy_queue(&context->queue);
		destroy_map(&context->map);
		exit(basic_error("Renderer initialisation failed\n", 2));
	}
	context->camera = (t_camera){WINDOW_HEIGHT
		/ sqrt(context->map.height * context->map.height
			+ context->map.width * context->map.width),
		(t_vector){0, 0, 0}, (t_vector){0, 0, 0}};
	translate_map(&context->map,
		-(context->map.width / 2), -(context->map.height / 2), 0);
	context->mouse = (t_mouse){0, 0, (t_button){0, 0, 0}, (t_button){0, 0, 0}};
}

void	destroy_context(t_context	*context)
{
	destroy_queue(&context->queue);
	destroy_map(&context->map);
	if (destroy_renderer(&context->renderer))
		exit(basic_error("Renderer destruction failed\n", 1));
}

int	main(int argc, char **argv)
{
	t_context	context;

	if (argc != 2)
		return (basic_error("Need one argument\n", 1));
	init_context(&context, argv);
	mlx_hook(context.renderer.window, KeyPress, KeyPressMask,
		keydown_hook, &context);
	mlx_hook(context.renderer.window, DestroyNotify, NoEventMask,
		destroy_hook, &context.renderer);
	mlx_hook(context.renderer.window, ButtonPress, ButtonPressMask,
		button_press_hook, &context.renderer);
	mlx_hook(context.renderer.window, ButtonRelease, ButtonReleaseMask,
		button_release_hook, &context.renderer);
	mlx_hook(context.renderer.window, MotionNotify, PointerMotionMask,
		motion_hook, &context.renderer);
	mlx_loop_hook(context.renderer.mlx, loop_hook, &context);
	mlx_loop(context.renderer.mlx);
	destroy_context(&context);
	return (0);
}
