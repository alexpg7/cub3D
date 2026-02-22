/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <alpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 18:31:41 by alpascua          #+#    #+#             */
/*   Updated: 2026/02/22 18:31:49 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_loadtex(t_texture *tex, void *mlx)
{
	tex->img = mlx_xpm_file_to_image(mlx, tex->path, &tex->img_w, &tex->img_h);
	tex->data = mlx_get_data_addr(tex->img, &tex->bpp, &tex->size_line, &tex->endian);
	//protect
}

int	ft_loadtextures(t_data *data)
{
	//protect
	ft_loadtex(&data->textures.north, data->mlx.mlx);
	ft_loadtex(&data->textures.south, data->mlx.mlx);
	ft_loadtex(&data->textures.west, data->mlx.mlx);
	ft_loadtex(&data->textures.east, data->mlx.mlx);
	return (1);
}
