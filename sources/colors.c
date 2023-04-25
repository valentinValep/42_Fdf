/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:05:14 by vlepille          #+#    #+#             */
/*   Updated: 2023/04/25 17:05:16 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <math.h>

static int	is_hexa(char c)
{
	return ((c >= '0' && c <= '9')
		|| (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'));
}

static int	c_to_x(char c)
{
	static char	tab[17] = "0123456789ABCDEF";
	int			i;

	c = c - (('a' - 'A') * (c >= 'a' && c <= 'f'));
	i = 0;
	while (c != tab[i])
		i++;
	return (i);
}

int	get_color(char *word)
{
	int	len;
	int	x_pos;
	int	i;
	int	res;

	len = 0;
	while (word[len] != '\0' && word[len] != ' ' && word[len] != '\n')
		len++;
	x_pos = 3;
	while (x_pos < len && word[x_pos] != 'x'
		&& word[x_pos - 1] != '0' && word[x_pos - 2] != ',')
		x_pos++;
	if (x_pos == len
		|| ((len - x_pos) != 3 && (len - x_pos) != 5 && (len - x_pos) != 7))
		return (-1);
	i = x_pos + 1;
	while (is_hexa(word[i]))
		i++;
	if (i != len)
		return (-1);
	res = 0;
	i = len;
	while (--i > x_pos)
		res += c_to_x(word[i]) * pow(16, (len - i - 1));
	return (res);
}

static int	get_height_color(t_point point, t_map *map)
{
	const double	diff = map->max_z - map->min_z;
	const double	group_size = diff / GROUP_COUNT;
	const int		height_group = (point.z - map->min_z) / group_size;

	if (height_group < GROUP_1)
		return (0x00000080
			+ (int)(0x80 * ((point.z - map->min_z) / (group_size * GROUP_1))));
	if (height_group < GROUP_2)
		return (0x000000FF
			-(int)(0xc0 * ((point.z - map->min_z - group_size * GROUP_1)
				/ (group_size * (GROUP_2 - GROUP_1))))
			+(((int)(0x80 * ((point.z - map->min_z - group_size * GROUP_1)
				/ (group_size * (GROUP_2 - GROUP_1))))) << 8)
			+(((int)(0x40 * ((point.z - map->min_z - group_size * GROUP_1)
				/ (group_size * (GROUP_2 - GROUP_1))))) << 16));
	if (height_group < GROUP_3)
		return (0x0040C040
			-(int)(0x40 * ((point.z - map->min_z - group_size * GROUP_2)
				/ (group_size * (GROUP_3 - GROUP_2))))
			-(((int)(0x80 * ((point.z - map->min_z - group_size * GROUP_2)
				/ (group_size * (GROUP_3 - GROUP_2))))) << 8)
			+(((int)(0x40 * ((point.z - map->min_z - group_size * GROUP_2)
				/ (group_size * (GROUP_3 - GROUP_2))))) << 16));
	return ((int []){0x00FFFFFF, 0x00804000}[height_group < GROUP_3]);
}

void	set_map_color(t_map *map)
{
	unsigned int	i;

	i = -1;
	while (++i < map->height * map->width)
	{
		if (map->points_tab[i].color == -1)
			map->points_tab[i].color
				= get_height_color(map->points_tab[i], map);
	}
}
