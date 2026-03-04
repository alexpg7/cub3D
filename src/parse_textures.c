/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexp <alexp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 17:04:36 by alpascua          #+#    #+#             */
/*   Updated: 2026/03/04 15:16:01 by alexp            ###   ########.fr       */
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
		return (ft_perror("Malloc error", 1));
	if (!ft_xpmextension(filename))
		return (1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nError reading \"", 2);
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

int	ft_tex_rec(char *list)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (list[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	ft_checktext(char *str, t_data *data, int type, char *content)
{
	if (!ft_readline(str, data, type, content))
		return (0);
	if (data->tex_rec[type - 1] == '1')
		return (ft_perror("Repeated instruction", 0));
	data->tex_rec[type - 1] = '1';
	return (1);
}

int	ft_gettextures(t_list *file, t_data *data)
{
	char	*str;

	while (file && !ft_tex_rec(data->tex_rec))
	{
		if (!file->content)
			break ;
		str = file->content;
		while (ft_isspace(*str))
			str++;
		if (!(*str))
		{
			file = file->next;
			continue ;
		}
		if (!ft_checktext(str, data, ft_classify(str), file->content))
			return (0);
		file = file->next;
	}
	if (!ft_tex_rec(data->tex_rec))
		return (ft_perror("Missing textures/colors information", 0));
	return (1);
}

void	ft_assigntype(int type, char *str, t_textures *tex)
{
	if (type == 1)
		tex->north.path = ft_strdup(str);
	else if (type == 2)
		tex->south.path = ft_strdup(str);
	else if (type == 3)
		tex->east.path = ft_strdup(str);
	else if (type == 4)
		tex->west.path = ft_strdup(str);
	else if (type == 5)
		tex->floor = ft_parse_rgb(str);
	else if (type == 6)
		tex->ceiling = ft_parse_rgb(str);
}
