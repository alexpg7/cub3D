/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexp <alexp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 18:23:06 by alpascua          #+#    #+#             */
/*   Updated: 2026/03/04 14:49:44 by alexp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_screendef(t_mlx *mlx, t_data *data)
{
	mlx->x = 1500;
	mlx->y = 800;
	data->mlx = data->mlx;
	data->player.h = 0.5;
	data->player.fov = 70.0 * PI / 180.0;
	data->player.vel.x = 0;
	data->player.vel.y = 0;
	data->player.look_vel = 0.0;
	data->player.h_vel = 0.0;
}

/*void	ft_fillmap(t_data *data)
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
}*/

void	ft_init_window(t_mlx *mlx, t_data *data)
{
	mlx->mlx = mlx_init();
	mlx->win = NULL;
	mlx->img = NULL;
	if (!(mlx->mlx))
		ft_exit(data, ft_perror("mlx init failed", 1));
	if (!ft_loadtextures(data))
		ft_exit(data, ft_perror("Loading textures failed", 1));
	mlx->win = mlx_new_window(mlx->mlx, mlx->x, mlx->y, "cub3D");
	mlx->img = mlx_new_image(mlx->mlx, mlx->x, mlx->y);
	if (!(mlx->win) || !(mlx->img))
		ft_exit(data, ft_perror("mlx window failed", 1));
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	if (!(mlx->addr) || !(mlx->bits_per_pixel) || !(mlx->line_length))
		ft_exit(data, ft_perror("mlx get adress failed", 1));
	mlx_hook(mlx->win, 6, 1L << 6, &ft_movemouse, data);
	mlx_hook(mlx->win, 17, 0L, &ft_hookexit, data);
	mlx_hook(mlx->win, 2, 1L << 0, &key_press, data);
	mlx_hook(mlx->win, 3, 1L << 1, &key_release, data);
	mlx_loop_hook(mlx->mlx, game_loop, data);
	mlx_loop(mlx->mlx);
}

void	ft_inittex(t_texture *tex)
{
	tex->path = NULL;
	tex->data = NULL;
	tex->img = NULL;
}

int	ft_init(t_data *data)
{
	ft_inittex(&data->textures.east);
	ft_inittex(&data->textures.north);
	ft_inittex(&data->textures.south);
	ft_inittex(&data->textures.west);
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
	data->player.shift_key = '0';
	data->player.ctrl_key = '0';
	data->mlx.mlx = NULL;
	return (0);
}
