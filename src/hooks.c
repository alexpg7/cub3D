/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <alpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 11:15:00 by alpascua          #+#    #+#             */
/*   Updated: 2026/03/01 14:09:25 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_movemouse(int x, int y, t_data *data)
{
	int		dx;
	t_mlx	*mlx;

	mlx = &data->mlx;
	y = y + 1 - 1;
	if (x == mlx->x / 2)
		return (0);
	dx = x - mlx->x / 2;
	data->player.look_dir -= (float)dx * 0.0005;
	mlx_mouse_move(mlx->mlx, mlx->win, mlx->x / 2, mlx->y / 2);
	return (0);
}

int	ft_hookexit(t_data *data)
{
	ft_exit(data, 0);
	return (0);
}

/*int	key_hook(int keycode, t_data *data)
{
	t_player	*player;

	player = &data->player;
	if (keycode == ESC)
		ft_hookexit(data);
		player->pos = ft_changepos(player->pos, -player->look_dir, data);
	if (keycode == RIGHT)
		player->pos = ft_changepos(player->pos, player->look_dir - PI / 2, data);
	else if (keycode == LEFT)
		player->pos = ft_changepos(player->pos, player->look_dir + PI / 2, data);
	//printf("%f\n", data->player.pos.x);
	return (0);
}*/

void	ft_updatevel(t_player *player)
{
	float	norm;
	t_vec2	vec0;
	float	lv;
	float	hv;

	vec0.x = 0.0;
	vec0.y = 0.0;
	player->vel.x = 1 * (player->w_key == '1') - 1 * (player->s_key == '1');
	player->vel.y = 1 * (player->a_key == '1') - 1 * (player->d_key == '1');
	norm = ft_distance(player->vel, vec0);
	if (norm != 0)
	{
		player->vel.x /= norm;
		player->vel.y /= norm;
	}
	lv = 1 * (player->left_key == '1') - 1 * (player->right_key == '1');
	hv = 1 * (player->ctrl_key == '1') - 1 * (player->ctrl_key == '0');
	player->look_vel = lv;
	player->h_vel = hv;
}

int	key_press(int keycode, t_data *data)
{
	t_player	*player;

	player = &data->player;
	if (keycode == ESC)
		ft_hookexit(data);
	else if (keycode == KEYW)
		player->w_key = '1';
	else if (keycode == KEYA)
		player->a_key = '1';
	else if (keycode == KEYS)
		player->s_key = '1';
	else if (keycode == KEYD)
		player->d_key = '1';
	else if (keycode == KEYLEFT)
		player->left_key = '1';
	else if (keycode == KEYRIGHT)
		player->right_key = '1';
	else if (keycode == KEYSHIFT)
		player->shift_key = '1';
	else if (keycode == KEYCTRL)
		player->ctrl_key = '1';
	ft_updatevel(player);
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	t_player	*player;

	player = &data->player;
	if (keycode == KEYW)
		data->player.w_key = '0';
	else if (keycode == KEYA)
		data->player.a_key = '0';
	else if (keycode == KEYS)
		data->player.s_key = '0';
	else if (keycode == KEYD)
		data->player.d_key = '0';
	else if (keycode == KEYLEFT)
		data->player.left_key = '0';
	else if (keycode == KEYRIGHT)
		data->player.right_key = '0';
	else if (keycode == KEYSHIFT)
		player->shift_key = '0';
	else if (keycode == KEYCTRL)
		player->ctrl_key = '0';
	ft_updatevel(player);
	return (0);
}
