#include "fdf.h"
#include <X11/keysymdef.h>
#include <stdio.h> // @TODO rm
int	loop_hook(t_context *context)
{
	int	keycode;

	while (queue_next(&context->queue, &keycode))
	{
		if (keycode == XK_Escape)
			return (mlx_loop_end(context->renderer.mlx));
		key_hook_tick(context, keycode);
	}
	if (!context->map.is_update)
	{
		clear_renderer(&context->renderer);
		draw_map(context);
		put_origins(&context->renderer);
		context->map.is_update = 1;
	}
	render_tick(&context->renderer);
	return (0);
}
