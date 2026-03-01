/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <alpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 12:22:29 by alpascua          #+#    #+#             */
/*   Updated: 2026/03/01 14:41:47 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	ft_newstep(t_ray *ray, float dx, float dy)
{
	float	t;

	if (dx < dy)
	{
		t = dx;
		ray->x = ray->x + 1 * (ray->dir.x >= 0) - 1 * (ray->dir.x < 0);
		if (ray->dir.x > 0)
			ray->orientation = 'N';
		else
			ray->orientation = 'S';
	}
	else
	{
		t = dy;
		ray->y = ray->y + 1 * (ray->dir.y >= 0) - 1 * (ray->dir.y < 0);
		if (ray->dir.y > 0)
			ray->orientation = 'W';
		else
			ray->orientation = 'E';
	}
	return (t);
}

char	ft_nearestwall(t_ray *ray, char **map)
{
	t_vec2	pos;
	float	dx;
	float	dy;
	float	t;

	pos.x = ray->pos.x;
	pos.y = ray->pos.y;
	dx = floor(pos.x + ray->dir.x * 0.000001) + 1 * (ray->dir.x > 0);
	dy = floor(pos.y + ray->dir.y * 0.000001) + 1 * (ray->dir.y > 0);
	dx = ft_div0(fabs((dx - pos.x)), fabs(ray->dir.x));
	dy = ft_div0(fabs((dy - pos.y)), fabs(ray->dir.y));
	t = ft_newstep(ray, dx, dy);
	pos.x = pos.x + t * ray->dir.x;
	pos.y = pos.y + t * ray->dir.y;
	ray->pos = pos;
	return (map[ray->x][ray->y]);
}

t_texture	ft_choosetex(char orientation, t_textures tex)
{
	if (orientation == 'N')
		return (tex.north);
	if (orientation == 'S')
		return (tex.south);
	if (orientation == 'E')
		return (tex.east);
	else
		return (tex.west);
}

t_texture	ft_raycast(t_ray *ray, char **map, t_data *data)
{
	char		hit;

	hit = map[(int)floor(ray->pos.x)][(int)floor(ray->pos.y)];
	while (hit != '1')
	{
		hit = ft_nearestwall(ray, map);
	}
	ray->dist = ft_distance(ray->pos, ray->start);
	return (ft_choosetex(ray->orientation, data->textures));
}

t_ray	ft_startray(t_vec2 start, float dir)
{
	t_ray	ray;

	ray.start = start;
	ray.dir.x = cos(dir);
	ray.dir.y = sin(dir);
	ray.pos = start;
	ray.x = (int)floor(start.x);
	ray.y = (int)floor(start.y);
	ray.orientation = '0';
	return (ray);
}
