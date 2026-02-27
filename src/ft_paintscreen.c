/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paintscreen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <alpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 11:29:29 by alpascua          #+#    #+#             */
/*   Updated: 2026/02/27 18:59:17 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

unsigned int	ft_getcolor(t_texture tex, t_ray ray, float h)
{
	float	dist;

	if (ray.orientation == 'N')
		dist = (int)((1 - ray.pos.y + floor(ray.pos.y)) * tex.img_w);
	else if (ray.orientation == 'S')
		dist = (int)((ray.pos.y - floor(ray.pos.y)) * tex.img_w);
	else if (ray.orientation == 'W')
		dist = (int)((ray.pos.x - floor(ray.pos.x)) * tex.img_w);
	else
		dist = (int)((1 - ray.pos.x + floor(ray.pos.x)) * tex.img_w);
	return (pixel_get(tex, dist, h));
}

void	ft_paintraycolumn(int	x, t_data *data, float angle, float da)
{
	t_ray		ray;
	int			color;
	int			y;
	float		an;
	int			h;
	t_texture	tex;

	//printf("%f\n", data->player.pos.x);
	ray = ft_startray(data->player.pos, angle);
	tex = ft_raycast(&ray, data->map, data);
	y = 0;
	an = 0 - data->mlx.y / 2 * da;
	while (y < data->mlx.y)
	{
		h = (int)(tex.img_h * (data->player.h + ray.dist * tan(an) * cos(angle - data->player.look_dir)));
		if (h > 0 && h <= tex.img_h)
			color = ft_getcolor(tex, ray, h);
		else if (h > 0 && h > tex.img_h)
			color = data->textures.ceiling;
		else
			color = data->textures.floor;
		pixel_put(&data->mlx, x, y, color);
		y++;
		an = an + da;
	}
}

void	ft_paintscreen(t_data *data)
{
	float	angle;
	float	da;
	int		step;

	angle = data->player.look_dir - data->player.fov / 2;
	da = data->player.fov / data->mlx.x;
	step = 0;
	while (step < data->mlx.x)
	{
		ft_paintraycolumn(data->mlx.x - step, data, angle + da * step, da);
		step++;
	}
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}
