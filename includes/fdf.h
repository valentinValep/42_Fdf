/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:05:28 by vlepille          #+#    #+#             */
/*   Updated: 2023/04/25 17:05:28 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "render.h"
# include "queue.h"
# include "map.h"

# define XK_MISCELLANY
# define XK_LATIN1
# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define ZOOM_MODIFIER 1.1
# define ROTATION_MODIFIER 4092.

# define UNPRESSED 0
# define IS_PRESSED 1
# define WAS_PRESSED 2

# define UPSCALE 2
# define DOWNSCALE 0.5

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_camera
{
	double		zoom;
	t_vector	translation;
	t_vector	rotation;
}	t_camera;

typedef struct s_button
{
	int	start_x;
	int	start_y;
	int	is_clicked;
}	t_button;

typedef struct s_mouse
{
	int			x;
	int			y;
	t_button	right_button;
	t_button	left_button;
}	t_mouse;

typedef struct s_context
{
	t_renderer	renderer;
	t_queue		queue;
	t_map		map;
	t_camera	camera;
	t_mouse		mouse;
}	t_context;

int		keydown_hook(int keycode, t_context *context);
int		button_press_hook(int button, int x, int y, t_context *context);
int		button_release_hook(int button, int x, int y, t_context *context);
int		motion_hook(int x, int y, t_context *context);
int		destroy_hook(t_renderer *renderer);
int		loop_hook(t_context *context);

void	key_hook_tick(t_context *context, int keycode);
void	left_button_tick(t_context *context);
void	right_button_tick(t_context *context);
void	draw_tick(t_context *context);

void	rotate_camera(
			t_camera *camera, double x_axis, double y_axis, double z_axis);
void	reset_rotation(t_camera *camera);
void	translate_camera(t_camera *camera, int x_axis, int y_axis, int z_axis);

#endif
