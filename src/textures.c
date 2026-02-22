/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <alpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 17:04:36 by alpascua          #+#    #+#             */
/*   Updated: 2026/02/22 17:05:36 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_checktexture(t_data *data, char *str, int type)
{
	int		fd;
	char	*filename;

	str = str + 2;
	while (ft_isspace(*str))
		str++;
	filename = ft_filename(str);
	if (!filename)
		return (ft_printerrorreturn("Malloc error\n", 1));
	if (!ft_xpmextension(filename))
		return (1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error reading \"", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd("\"\n", 2);
		free(filename);
		return (1);
	}
	close(fd);
	ft_assigntype(type, filename, &data->textures);
	free(filename);
	return (0);
}

int	ft_gettextures(t_list *file, t_data *data)
{
	char	*str;
	int		count;

	count = 0;
	while (file->content && count < 6)
	{
		str = file->content;
		while (ft_isspace(*str))
			str++;
		if (!(*str))
		{
			file = file->next;
			continue ;
		}
		if (!ft_readline(str, data, ft_classify(str), file->content))
			return (0);
		else
			count++;
		file = file->next;
	}
	if (count != 6)
		return (0);//missing information
	return (1);
}

void	ft_loadtex(t_texture *tex, void *mlx)
{
	tex->img = mlx_xpm_file_to_image(mlx, tex->path, &tex->img_w, &tex->img_h);
	ft_printf("%p\n", tex->img);
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
