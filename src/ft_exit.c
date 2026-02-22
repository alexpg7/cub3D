/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <alpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 11:14:20 by alpascua          #+#    #+#             */
/*   Updated: 2026/02/22 11:26:06 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_close_mlx(t_mlx *mlx)
{
	if (mlx->mlx)
	{
		if (mlx->img)
			mlx_destroy_image(mlx->mlx, mlx->img);
		if (mlx->win)
			mlx_destroy_window(mlx->mlx, mlx->win);
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
	}
}

void	ft_freetex(t_textures tex)
{
	if (tex.north)
		free(tex.north);
	if (tex.south)
		free(tex.south);
	if (tex.east)
		free(tex.east);
	if (tex.west)
		free(tex.west);
}

int	ft_exit(t_data *data, int ret)
{
	ft_freetex(data->textures);
	ft_close_mlx(&(data->mlx));
	if (data->map)
		ft_freestrarr(&(data->map), 0);
	exit(ret);
	return (ret);
}
