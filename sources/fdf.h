#ifndef FDF_H
# define FDF_H

# include <mlx.h>

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

# define X_AXIS 1
# define Y_AXIS 2
# define Z_AXIS 4

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}	t_point;

t_point	rotate(t_point point, char axis, double degree);
t_point	projection(t_point point);

# define POINTS_PER_LINE 1000
# define ZOOM 100
# define START_X 100
# define START_Y 100

typedef struct s_map
{
	t_point	*tab;
	int		height;
	int		width;
}	t_map;

void	init_map(t_map *map, char *str);
void	print_map(t_map *map, t_app *app);

#endif
