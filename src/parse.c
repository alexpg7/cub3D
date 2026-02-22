/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <alpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 18:08:04 by alpascua          #+#    #+#             */
/*   Updated: 2026/02/22 17:05:26 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_parsefile(t_list **list, int fd)
{
	char	*line;
	t_list	*newelement;

	line = get_next_line(fd);
	*list = ft_lstnew(line);
	if (!list)
		return (ft_closeerror(fd, "Malloc error"));
	line = get_next_line(fd);
	while (line)
	{
		newelement = ft_lstnew(line);
		if (!newelement)
		{
			ft_lstclear(list, &free);
			return (ft_closeerror(fd, "Malloc error"));
		}
		ft_lstadd_back(list, newelement);
		line = get_next_line(fd);
	}
	close(fd);
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

int	ft_readline(char *str, t_data *data, int type, char *origstring)
{
	if (type != 0)
	{
		if (type == 5 || type == 6)
		{
			if (!ft_checkrgb(data, str, type))
				return (1);
		}
		else if (!ft_checktexture(data, str, type))
			return (1);
		return (0);
	}
	else
	{
		if (str[0] == '0' || str[0] == '1')
		{
			ft_putstr_fd("Error: map detected before defining textures\n", 2);
			return (0);
		}
		ft_putstr_fd("Error reading line \"", 2);
		write(2, origstring, ft_strlen(origstring) - 1);
		ft_putstr_fd("\", it does not match any instruction ", 2);
		ft_putstr_fd("(NO, SO, EA, WE, F, C)\n", 2);
		return (0);
	}
	return (1);
}

int	ft_checkmap(int fd, t_data *data)
{
	t_list	*file;
	t_list	*node;
	int		num_rows;
	int		num_cols;
	char	**map_array;

	if (!ft_parsefile(&file, fd))
		return (0);
	if (!ft_gettextures(file, data))
	{
		ft_lstclear(&file, &free);
		return (0);
	}
	//create matrix funtion
	node = file;
	num_cols = 0;
	num_rows = 0;
	while (node)
	{
		if (ft_strlen((char *)node->content) > (size_t)num_cols)
			num_cols = ft_strlen((char *)node->content);
		num_rows++;
		node = node->next;
	}
	map_array = (char **)malloc((num_rows + 1) * sizeof(char *));
	if (!map_array)
		return (ft_closeerror(fd, "Malloc error"));
	while (num_cols > 0)
	{
		map_array[num_rows] = (char *)malloc((num_cols + 1) * sizeof(int));
		if (!map_array[num_rows])
			return (ft_closeerror(fd, "Malloc error"));
		num_cols--;
	}
	while (file)
	{
		ft_printf("%s", file->content);
		file = file->next;
	}
	//Leaks from map_array and file
	return (1);
}
