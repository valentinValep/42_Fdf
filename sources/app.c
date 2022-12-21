#include <mlx.h>
#include "fdf.h"

void	init_app(t_app *app)
{
	app->mlx = mlx_init();
	app->window = mlx_new_window(app->mlx, 1920, 1080, "Hello world!");
	app->render.imgs[0].img = mlx_new_image(app->mlx, 1920, 1080);
	app->render.imgs[0].addr = mlx_get_data_addr(
			app->render.imgs[0].img,
			&app->render.imgs[0].bits_per_pixel,
			&app->render.imgs[0].line_length,
			&app->render.imgs[0].endian
			);
	app->render.imgs[1].img = mlx_new_image(app->mlx, 1920, 1080);
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
	t_img *const	img = &app->render.imgs[app->render.seq];

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	flush(t_app *app)
{
	mlx_put_image_to_window(app->mlx, app->window,
		app->render.imgs[app->render.seq].img, 0, 0);
	app->render.seq = (app->render.seq + 1) % 2;
}
