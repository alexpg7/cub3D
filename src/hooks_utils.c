/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexp <alexp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 19:50:35 by alpascua          #+#    #+#             */
/*   Updated: 2026/02/28 16:58:23 by alexp            ###   ########.fr       */
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
	data->player.look_dir += data->player.look_vel * dt * 1.0;
	ft_paintscreen(data);
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
