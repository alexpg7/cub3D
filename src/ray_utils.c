/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <alpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 19:03:34 by alpascua          #+#    #+#             */
/*   Updated: 2026/02/22 19:03:42 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	ft_distance(t_vec2 v1, t_vec2 v2)
{
	return ((float)hypot(v1.x - v2.x, v1.y - v2.y));
}

char	get_cell(char **map, t_vec2 pos, t_vec2 dir)//, int hit_vert)
{
	int	map_x;
	int	map_y;

	map_x = (int)floor(pos.x + dir.x * 0.00001);
	map_y = (int)floor(pos.y + dir.y * 0.00001);
	return (map[map_x][map_y]);
}

float	ft_div0(float f1, float f2)
{
	if (f2 == 0.0)
		return (1000000.0);
	return (f1 / f2);
}
