#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "render.h"
# include "queue.h"
# include "map.h"

# define XK_MISCELLANY
# define XK_LATIN1
# define WINDOW_WIDTH 1920 // @TODO make renderer use different window size
# define WINDOW_HEIGHT 1080
# define ZOOM_MODIFIER 1.1
# define ROTATION_MODIFIER 48.

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_camera
{
	double		zoom;
	t_vector	translation_vec;
}	t_camera;

typedef struct s_context
{
	t_renderer	renderer;
	t_queue		queue;
	t_map		map;
	t_camera	camera;
}	t_context;

int		keydown_hook(int keycode, t_context *context);
int		destroy_hook(t_renderer *renderer);
int		loop_hook(t_context *context);

void	key_hook_tick(t_context *context, int keycode);

t_point	transform(t_context *context, t_point *point);

#endif
