/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:05:24 by vlepille          #+#    #+#             */
/*   Updated: 2023/04/28 14:10:45 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include <math.h>

void	destroy_map(t_map *map)
{
	free(map->points_tab);
}

static void	init_transform(
	t_context *context, t_point *point, t_vector *tmp, t_point *res)
{
	res->color = point->color;
	tmp->x = point->x;
	tmp->y = point->y;
	tmp->z = point->z * context->map.height_scale;
}

static void	end_tranform(t_context *context, t_point *res)
{
	res->x += context->camera.translation.x * context->map.translation_modifier;
	res->y += context->camera.translation.y * context->map.translation_modifier;
	res->z += context->camera.translation.z * context->map.translation_modifier;
	res->x *= context->camera.zoom;
	res->y *= context->camera.zoom;
	res->z *= context->camera.zoom;
}

static t_point	transform(t_context *context, t_point *point)
{
	const t_vector	rad = (t_vector){
		context->camera.rotation.x * M_PI / 180,
		context->camera.rotation.y * M_PI / 180,
		context->camera.rotation.z * M_PI / 180};
	t_vector		tmp;
	t_point			res;

	init_transform(context, point, &tmp, &res);
	res.x = cos(rad.z) * cos(rad.y) * tmp.x
		+ ((cos(rad.z) * sin(rad.y) * sin(rad.x))
			- (sin(rad.z) * cos(rad.x))) * tmp.y
		+ ((cos(rad.z) * sin(rad.y) * cos(rad.x))
			+ (sin(rad.z) * sin(rad.x))) * tmp.z;
	res.y = sin(rad.z) * cos(rad.y) * tmp.x
		+ ((sin(rad.z) * sin(rad.y) * sin(rad.x))
			+ (cos(rad.z) * cos(rad.x))) * tmp.y
		+ ((sin(rad.z) * sin(rad.y) * cos(rad.x))
			- (cos(rad.z) * sin(rad.x))) * tmp.z;
	res.z = -sin(rad.y) * tmp.x
		+ (cos(rad.y) * sin(rad.x)) * tmp.y
		+ (cos(rad.y) * cos(rad.x)) * tmp.z;
	end_tranform(context, &res);
	return (res);
}

void	draw_map(t_context *context)
{
	unsigned int	i;

	i = 0;
	while (i < context->map.height * context->map.width)
	{
		if (i % context->map.width != context->map.width - 1)
			draw_line(&context->renderer,
				transform(context, &context->map.points_tab[i]),
				transform(context, &context->map.points_tab[i + 1]));
		if (i / context->map.width != context->map.height - 1)
			draw_line(&context->renderer,
				transform(context, &context->map.points_tab[i]),
				transform(context,
					&context->map.points_tab[i + context->map.width]));
		i++;
	}
}
