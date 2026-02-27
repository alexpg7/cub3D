/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <alpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 11:15:00 by alpascua          #+#    #+#             */
/*   Updated: 2026/02/27 18:51:52 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_vec2	ft_rotate(t_vec2 vec, float angle)
{
	t_vec2 result;
	float cos_a;
	float sin_a;

	cos_a = cos(angle);
	sin_a = sin(angle);
	result.x = vec.x * cos_a - vec.y * sin_a;
	result.y = vec.x * sin_a + vec.y * cos_a;
	return (result);
}

int	game_loop(t_data *data)
{
	struct timeval	current_time;
	t_vec2			vel;
	t_vec2			fpos;
	float			dt;

	gettimeofday(&current_time, NULL);
	dt = (current_time.tv_sec - data->last_time.tv_sec) \
		+(current_time.tv_usec - data->last_time.tv_usec) / 1000000.0f;
	vel = ft_rotate(data->player.vel, data->player.look_dir);
	fpos.x = data->player.pos.x + 2 * vel.x * dt;
	fpos.y = data->player.pos.y + 2 * vel.y * dt;
	if (data->map[(int)floor(fpos.x)][(int)floor(fpos.y)] != '1')
	{
		data->player.pos.x = fpos.x;
		data->player.pos.y = fpos.y;
	}
	data->last_time = current_time;
	ft_paintscreen(data);
	return (0);
}

int	ft_movemouse(int x, int y, t_data *data)
{
	int	dx;

	y = y + 1 - 1;
	if (x == data->mlx.x / 2)
		return (0);
	dx = x - data->mlx.x / 2;
	data->player.look_dir -= (float)dx * 0.0005;
	mlx_mouse_move(data->mlx.mlx, data->mlx.win, data->mlx.x / 2, data->mlx.y / 2);
	return (0);
}

t_vec2	ft_changepos(t_vec2 vec, float angle, t_data *data)
{
	float	step;
	t_vec2	fpos;

	step = 0.2;
	fpos.x = vec.x;
	fpos.y = vec.y;
	fpos.x += step * cos(angle);
	fpos.y += step * sin(angle);
	if (data->map[(int)floor(fpos.x)][(int)floor(fpos.y)] == '1')
		return (vec);
	return (fpos);
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

	vec0.x = 0.0;
	vec0.y = 0.0;
	player->vel.x = 1.0 * (player->w_key == '1') \
		- 1.0 * (player->s_key == '1');
	player->vel.y = 1.0 * (player->a_key == '1') \
		- 1.0 * (player->d_key == '1');
	norm = ft_distance(player->vel, vec0);
	if (norm != 0)
	{
		player->vel.x /= norm;
		player->vel.y /= norm;
	}
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
	ft_updatevel(player);
	return (0);
}
