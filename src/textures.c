/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <alpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 18:31:41 by alpascua          #+#    #+#             */
/*   Updated: 2026/03/01 13:58:49 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_loadtex(t_texture *tex, void *mlx)
{
	char	**data;
	int		*size;

	data = &tex->data;
	size = &tex->size_line;
	tex->img = mlx_xpm_file_to_image(mlx, tex->path, &tex->img_w, &tex->img_h);
	if (!tex->img)
		return (ft_perror("Failed trying to get img from .xpm", 0));
	*data = mlx_get_data_addr(tex->img, &tex->bpp, size, &tex->endian);
	if (!(*data))
		return (ft_perror("Failed trying to get img data", 0));
	return (1);
}

int	ft_loadtextures(t_data *data)
{
	if (!ft_loadtex(&data->textures.north, data->mlx.mlx))
		return (0);
	if (!ft_loadtex(&data->textures.south, data->mlx.mlx))
		return (0);
	if (!ft_loadtex(&data->textures.west, data->mlx.mlx))
		return (0);
	if (!ft_loadtex(&data->textures.east, data->mlx.mlx))
		return (0);
	return (1);
}
