#include "fdf.h"
#include <unistd.h>

#include <stdio.h> // @TODO rm
int	keydown_hook(int keycode, t_context *context)
{
	if (add_queue(&context->queue, keycode))
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
