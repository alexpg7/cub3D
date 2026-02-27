/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <alpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 18:23:06 by alpascua          #+#    #+#             */
/*   Updated: 2026/02/27 19:06:27 by alpascua         ###   ########.fr       */
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
	data->player.fov = 70.0 * PI / 180.0;
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
	ft_fillmap(data); //this one is provisional, while waiting to have the map parsing
	ft_paintscreen(data);
	///mlx_mouse_hook(mlx->win, mouse_hook, data);
	mlx_hook(mlx->win, 6, 1L<<6, &ft_movemouse, data);
	//mlx_key_hook(mlx->win, key_hook, data);
	mlx_hook(mlx->win, 17, 0L, &ft_hookexit, data);
	mlx_hook(mlx->win, 2, 1L<<0, &key_press, data);
	mlx_hook(mlx->win, 3, 1L<<1, &key_release, data);
	mlx_loop_hook(mlx->mlx, game_loop, data);
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
	gettimeofday(&data->last_time, NULL);
	data->map = NULL;
	data->player.w_key = '0';
	data->player.a_key = '0';
	data->player.s_key = '0';
	data->player.d_key = '0';
	data->player.left_key = '0';
	data->player.right_key = '0';
	return (0);
}
