#include <mlx.h>
#include "fdf.h"

void	init_app(t_app *app)
{
	app->mlx = mlx_init();
	app->window = mlx_new_window(app->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FdF");
	app->render.imgs[0].img = mlx_new_image(app->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	app->render.imgs[0].addr = mlx_get_data_addr(
			app->render.imgs[0].img,
			&app->render.imgs[0].bits_per_pixel,
			&app->render.imgs[0].line_length,
			&app->render.imgs[0].endian
			);
	app->render.imgs[1].img = mlx_new_image(app->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	app->render.imgs[1].addr = mlx_get_data_addr(
			app->render.imgs[1].img,
			&app->render.imgs[1].bits_per_pixel,
			&app->render.imgs[1].line_length,
			&app->render.imgs[1].endian
			);
	app->render.seq = 0;
}

void	put_pixel(t_app *app, int x, int y, int color)
{
	char			*dst;
	t_img *const	img = &app->render.imgs[(int) app->render.seq];

	if (y < 0 || y > WINDOW_HEIGHT || x < 0 || x > WINDOW_WIDTH)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	flush(t_app *app)
{
	mlx_put_image_to_window(app->mlx, app->window,
		app->render.imgs[(int) app->render.seq].img, 0, 0);
	app->render.seq = (app->render.seq + 1) % 2;
}
