/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <alpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 17:04:36 by alpascua          #+#    #+#             */
/*   Updated: 2026/03/01 13:06:21 by alpascua         ###   ########.fr       */
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
		return (ft_perror("Malloc error\n", 1));
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

int	ft_classify(char *str)
{
	if (ft_strncmp(str, "NO", 2) == 0 && ft_isspace(str[2]))
		return (1);
	if (ft_strncmp(str, "SO", 2) == 0 && ft_isspace(str[2]))
		return (2);
	if (ft_strncmp(str, "EA", 2) == 0 && ft_isspace(str[2]))
		return (3);
	if (ft_strncmp(str, "WE", 2) == 0 && ft_isspace(str[2]))
		return (4);
	if (ft_strncmp(str, "F", 1) == 0 && ft_isspace(str[1]))
		return (5);
	if (ft_strncmp(str, "C", 1) == 0 && ft_isspace(str[1]))
		return (6);
	return (0);
}
