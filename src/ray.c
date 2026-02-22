/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <alpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 12:22:29 by alpascua          #+#    #+#             */
/*   Updated: 2026/02/22 19:14:28 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	ft_nearestwall(t_ray *ray, char **map)
{
	t_vec2	pos;
	float	dx;
	float	dy;
	float	t;

	pos.x = ray->pos.x + ray->dir.x * 0.000001;
	pos.y = ray->pos.y + ray->dir.y * 0.000001;
	//printf("start: %f, %f\n", pos.x, pos.y);
	dx = floor(pos.x) + 1 * (ray->dir.x > 0);
	dy = floor(pos.y) + 1 * (ray->dir.y > 0);
	dx = ft_div0(fabs((dx - pos.x)), fabs(ray->dir.x));
	dy = ft_div0(fabs((dy - pos.y)), fabs(ray->dir.y));
	//printf("dir: %f, %f\n", ray->dir.x, ray->dir.y);
	//printf("dxdy: %f, %f\n", dx, dy);
	if (dx < dy)
		t = dx;
	else
		t = dy;
	pos.x = pos.x + t * ray->dir.x;
	pos.y = pos.y + t * ray->dir.y;
	ray->pos = pos;
	//printf("newpos: %f, %f\n", ray->pos.x, ray->pos.y);
	return (get_cell(map, pos, ray->dir));
}

t_texture	ft_choosetex(t_vec2 pos, t_vec2 dir, t_data *data)
{
	if (pos.x - floor(pos.x) > pos.y - floor(pos.y))//hit with x axis
	{
		if (dir.y > 0)
			return (data->textures.west);
		else
			return (data->textures.east);
	}
	else
	{
		if (dir.x > 0)
			return (data->textures.north);
		else
			return (data->textures.south);
	}
}

t_texture	ft_raycast(t_ray *ray, char **map, t_data *data)
{
	char		hit;

	hit = map[(int)floor(ray->pos.x)][(int)floor(ray->pos.y)];
	while (hit != '1')//+ some conditions for safety (like count < dimensions of the map)
	{
		hit = ft_nearestwall(ray, map);
	}
	ray->dist = ft_distance(ray->pos, ray->start);
	return (ft_choosetex(ray->pos, ray->dir, data));
}

t_ray	ft_startray(t_vec2 start, float dir)
{
	t_ray	ray;

	ray.start = start;
	ray.dir.x = cos(dir);
	ray.dir.y = sin(dir);
	ray.pos = start;
	return (ray);
}
