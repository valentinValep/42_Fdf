#ifndef FDF_H
# define FDF_H

# include <mlx.h>

# define XK_MISCELLANY
# define XK_LATIN1
# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_render
{
	t_img	imgs[2];
	char	seq;
}	t_render;

typedef struct s_app
{
	t_render	render;
	void		*mlx;
	void		*window;
}	t_app;

void	init_app(t_app *app);
void	flush(t_app *app);
void	put_pixel(t_app *app, int x, int y, int color);
int		app_close(t_app *app);

# define ZOOM 50
# define POINTS_PER_LINE ZOOM

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	int		color;
}	t_point;

typedef struct s_map
{
	t_point	*tab;
	int		malloc_size;
	int		height;
	int		width;
}	t_map;

int		init_map(t_map *map, char *str);
void	print_map(t_map *map, t_app *app);

# define X_AXIS 1
# define Y_AXIS 2
# define Z_AXIS 4

t_point	projection(t_point point);
t_point	rotate(t_point point, char axis, double degree);
void	rotate_map(t_map *map, char axis_flag, double degree);
void	translate_map(t_map *map, char axis_flag, double value);
void	zoom_map(t_map *map, int scale);

typedef struct s_hook_args
{
	t_app	*app;
	t_map	*map;
}	t_hook_args;

#endif
