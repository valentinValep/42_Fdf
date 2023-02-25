#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "render.h"
# include "queue.h"

# define XK_MISCELLANY
# define XK_LATIN1
# define WINDOW_WIDTH 1920 // @TODO make renderer use different window size
# define WINDOW_HEIGHT 1080

typedef struct s_context
{
	t_renderer	renderer;
	t_queue		queue;
}	t_context;

int		keydown_hook(int keycode, t_context *context);
int		destroy_hook(t_renderer *renderer);
int		loop_hook(t_context *context);

void	key_hook_tick(t_context *context, int keycode);

#endif
