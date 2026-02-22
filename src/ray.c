/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <alpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 12:22:29 by alpascua          #+#    #+#             */
/*   Updated: 2026/02/22 17:51:04 by alpascua         ###   ########.fr       */
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

t_ray	ft_raycast(t_ray ray, char **map, t_data *data)
{
	char	hit;

	hit = map[(int)floor(ray.pos.x)][(int)floor(ray.pos.y)];
	while (hit != '1')//+ some conditions for safety (like count < dimensions of the map)
	{
		hit = ft_nearestwall(&ray, map);
		/*if (hit == '1')
			printf("hit: %f, %f\n", ray.pos.x, ray.pos.y);*/
	}
	data->map = data->map;
	return (ray);
	//printf("dist: %f\n", ft_distance(ray.start, ray.pos));
	//return ((unsigned int)((float)0xAAAAAA * ft_distance(ray.start, ray.pos) / 100000));
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
