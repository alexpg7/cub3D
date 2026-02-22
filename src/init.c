/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <alpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 18:23:06 by alpascua          #+#    #+#             */
/*   Updated: 2026/02/22 17:08:17 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_screendef(t_mlx *mlx, t_data *data)
{
	mlx->x = 1000;
	mlx->y = 500;
	data->mlx = data->mlx;
	//more things?
}

void	ft_init_window(t_mlx *mlx, t_data *data)
{
	mlx->mlx = mlx_init();
	if (!(mlx->mlx))
	{
		perror("mlx init");
		ft_exit(data, 1);
	}
	ft_loadtextures(data);
	mlx->win = mlx_new_window(mlx->mlx, mlx->x, mlx->y, "cub3D");
	mlx->img = mlx_new_image(mlx->mlx, mlx->x, mlx->y);
	if (!(mlx->win) || !(mlx->img))
	{
		perror("mlx error");
		ft_exit(data, 1);
	}
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	if (!(mlx->addr) || !(mlx->bits_per_pixel) || !(mlx->line_length))
	{
		perror("mlx address get");
		ft_exit(data, 1);
	}
	ft_paintscreen(data);
	//mlx_mouse_hook(mlx->win, mouse_hook, vars);
	//mlx_key_hook(mlx->win, key_hook, vars);
	mlx_hook(mlx->win, 17, 0L, &ft_hookexit, data);
	mlx_loop(mlx->mlx);
}

int	ft_init(t_data *data)
{
	data->textures.east.path = NULL;
	data->textures.west.path = NULL;
	data->textures.north.path = NULL;
	data->textures.south.path = NULL;
	data->textures.floor = 0;
	data->textures.ceiling = 0;
	data->map = NULL;
	return (0);
}
