#include "fdf.h"
#include <X11/keysymdef.h>
#include <stdio.h> // @TODO rm
int	loop_hook(t_context *context)
{
	const int	*keycode;

	keycode = queue_next(&context->queue);
	while (keycode)
	{
		if (*keycode == XK_Escape)
			return (mlx_loop_end(context->renderer.mlx));
		else if (*keycode == XK_1)
			clear_renderer(&context->renderer);
		else if (*keycode == XK_2)
			put_origins(&context->renderer);
		else if (*keycode == XK_3)
			draw_cube(&context->renderer, (t_point){20., -20., -20., 0x00FFFF00}, 50.);
		else if (*keycode == XK_4)
			draw_cube(&context->renderer, (t_point){20., 10., 10., 0x00FFFFFF}, 75.);
		keycode = queue_next(&context->queue);
	}
	render_tick(&context->renderer);
	return (0);
}
