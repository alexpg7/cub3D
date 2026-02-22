/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paintscreen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <alpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 11:29:29 by alpascua          #+#    #+#             */
/*   Updated: 2026/02/22 15:31:38 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_fillmap(t_data *data)
{
	data->map = (char **)malloc(sizeof(char *) * 7);
	data->map[0] = ft_strdup("11111111111");
	data->map[1] = ft_strdup("10000000001");
	data->map[2] = ft_strdup("100000000W1");
	data->map[3] = ft_strdup("10010000001");
	data->map[4] = ft_strdup("10000000001");
	data->map[5] = ft_strdup("11111111111");
	data->map[6] = NULL;
	data->player.pos.x = 2.5;
	data->player.pos.y = 9.5;
	data->player.look_dir = 3 * PI / 2;
	data->player.h = 0.5;
	data->player.fov = 120.0 * PI / 180.0;
}

void	pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + y * mlx->line_length + x * mlx->bits_per_pixel / 8;
	*(unsigned int *)dst = color;
}

void	ft_paintray(int	x, t_data *data, float angle)
{
	t_ray	ray;
	int		color;

	ray = ft_startray(data->player.pos, angle);//data->player.dir);//angle instead of player.dir
	color = ft_raycast(ray, data->map, data);
	pixel_put(&data->mlx, x, data->mlx.y, color);
	for (int y = 0; y < data->mlx.y; y++)
		pixel_put(&data->mlx, x, y, color);
	angle = angle + 1;
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
		ft_paintray(step, data, angle + da * step);
		step++;
	}
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}
