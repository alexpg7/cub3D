/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paintscreen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexp <alexp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 11:29:29 by alpascua          #+#    #+#             */
/*   Updated: 2026/02/25 14:58:26 by alexp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_fillmap(t_data *data)
{
	data->map = (char **)malloc(sizeof(char *) * 8);
	data->map[0] = ft_strdup("11111111111");
	data->map[1] = ft_strdup("10000000001");
	data->map[2] = ft_strdup("100000000W1");
	data->map[3] = ft_strdup("10000000001");
	data->map[4] = ft_strdup("10000100001");
	data->map[5] = ft_strdup("10000000001");
	data->map[6] = ft_strdup("11111111111");
	data->map[7] = NULL;
	data->player.pos.x = 2.5;
	data->player.pos.y = 9.5;
	data->player.look_dir = 3 * PI / 2;
	data->player.h = 0.5;
	data->player.fov = 90.0 * PI / 180.0;
}

void	pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + y * mlx->line_length + x * mlx->bits_per_pixel / 8;
	*(unsigned int *)dst = color;
}

unsigned int pixel_get(t_texture tex, int x, int y)
{
	return (*(unsigned int *)(tex.data + y * tex.size_line + x * (tex.bpp / 8)));
}

void	ft_paintray(int	x, t_data *data, float angle, float da)
{
	t_ray		ray;
	int			color;
	int			y;
	float		an;
	int			h;
	t_texture	tex;

	ray = ft_startray(data->player.pos, angle);
	tex = ft_raycast(&ray, data->map, data);
	y = 0;
	an = 0 - data->mlx.y / 2 * da;
	while (y < data->mlx.y)
	{
		h = (int)(tex.img_h * (data->player.h + ray.dist * tan(an)));
		if (h > 0 && h <= tex.img_h)
			color = pixel_get(tex, (int)((ray.pos.x - floor(ray.pos.x)) * tex.img_w), h);
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

	ft_fillmap(data); //this one is provisional, while waiting to have the map parsing
	angle = data->player.look_dir - data->player.fov / 2;
	da = data->player.fov / data->mlx.x;
	step = 0;
	while (step < data->mlx.x)
	{
		ft_paintray(data->mlx.x - step, data, angle + da * step, da);
		step++;
	}
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}
