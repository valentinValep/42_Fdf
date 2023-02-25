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
		key_hook_tick(context, *keycode);
		keycode = queue_next(&context->queue);
	}
	render_tick(&context->renderer);
	return (0);
}
