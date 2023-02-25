#include "fdf.h"
#include <unistd.h>
#include <X11/X.h>
#include <stdlib.h>

void	init_context(t_context	*context)
{
	if (init_renderer(&context->renderer))
	{
		destroy_queue(&context->queue);
		write(STDERR_FILENO, "Renderer initialisation failed\n", 31);
		exit(1);
	}
	init_queue(&context->queue);
}

void	destroy_context(t_context	*context)
{
	destroy_queue(&context->queue);
	if (destroy_renderer(&context->renderer))
	{
		write(STDERR_FILENO, "Renderer destruction failed\n", 28);
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	t_context	context;

	//if (argc != 2)
	//	return (1);
	init_context(&context);
	(void) argc;
	(void) argv;

	put_origins(&context.renderer);
	draw_cube(&context.renderer, (t_point){20., -20., -20., 0x00FFFF00}, 50.);

	mlx_hook(context.renderer.window, KeyPress, KeyPressMask,
		keydown_hook, &context);
	mlx_hook(context.renderer.window, DestroyNotify, NoEventMask,
		destroy_hook, &context.renderer);
	mlx_loop_hook(context.renderer.mlx, loop_hook, &context);
	mlx_loop(context.renderer.mlx);
	destroy_context(&context);
	return (0);
}
