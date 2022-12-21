#ifndef FDF_H
# define FDF_H

#include <mlx.h>

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
	void		*mlx;
	void		*window;
	t_render	render;
}	t_app;

void	init_app(t_app *app);
void	flush(t_app *app);
void	put_pixel(t_app *app, int x, int y, int color);

#endif