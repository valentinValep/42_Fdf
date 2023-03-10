#include "fdf.h"
#include <X11/keysymdef.h>
#include <X11/X.h>

#include <stdio.h> // @TODO rm
static void	mouse_hook(t_context *context, t_content content)
{
	if (content.type == BUTTON_PRESS_TYPE)
	{
		//printf("PRESS <%d>, x <%d>, y <%d>\n", content.content, content.content2, content.content3);
		if (content.content == Button3
			&& !context->mouse.is_left_clicked)
		{
			context->mouse.is_left_clicked = IS_PRESSED;
			context->mouse.start_x = content.content2;
			context->mouse.start_y = content.content3;
			context->mouse.x = context->mouse.start_x;
			context->mouse.y = context->mouse.start_y;
		}
		if (content.content == Button4)
		{
			context->camera.zoom *= ZOOM_MODIFIER;
			context->map.is_update = 0;
		}
		if (content.content == Button5)
		{
			context->camera.zoom /= ZOOM_MODIFIER;
			context->map.is_update = 0;
		}
	}
	else if (content.type == BUTTON_RELEASE_TYPE)
	{
		//printf("RELEASE <%d>, x <%d>, y <%d>\n", content.content, content.content2, content.content3);
		if (content.content == Button3)
			context->mouse.is_left_clicked = WAS_PRESSED;
	}
	else if (content.type == MOTION_TYPE)
	{
		//printf("Motion x <%d>, y <%d>\n", content.content, content.content2);
		if (context->mouse.is_left_clicked == IS_PRESSED)
		{
			context->mouse.x = content.content;
			context->mouse.y = content.content2;
		}
	}
}

int	loop_hook(t_context *context)
{
	t_content	content;

	while (queue_next(&context->queue, &content))
	{
		if (content.type == KEYBOARD_TYPE)
		{
			if (content.content == XK_Escape)
				return (mlx_loop_end(context->renderer.mlx));
			key_hook_tick(context, content.content);
		}
		else
			mouse_hook(context, content);
	}
	if (context->mouse.is_left_clicked == IS_PRESSED)
	{
		mlx_mouse_hide(context->renderer.mlx, context->renderer.window);
		rotate_map(&context->map,
			-(context->mouse.y - context->mouse.start_y),
			context->mouse.y - context->mouse.start_y,
			context->mouse.x - context->mouse.start_x);
		mlx_mouse_move(context->renderer.mlx, context->renderer.window,
			context->mouse.start_x, context->mouse.start_y);
		context->mouse.x = context->mouse.start_x;
		context->mouse.y = context->mouse.start_y;
		context->map.is_update = 0;
	}
	if (context->mouse.is_left_clicked == WAS_PRESSED)
	{
		mlx_mouse_show(context->renderer.mlx, context->renderer.window);
		context->map.is_update = 0;
		context->mouse.is_left_clicked = UNPRESSED;
	}
	if (!context->map.is_update)
	{
		clear_renderer(&context->renderer);
		draw_map(context);
		//put_origins(&context->renderer);
		context->map.is_update = 1;
	}
	render_tick(&context->renderer);
	return (0);
}
