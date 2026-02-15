/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <alpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 18:08:04 by alpascua          #+#    #+#             */
/*   Updated: 2026/02/15 18:52:21 by alpascua         ###   ########.fr       */
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
	while (line)
	{
		newelement = ft_lstnew(line);
		if (!newelement)
			return (ft_closeerror(fd, "Malloc error"));
		ft_lstadd_back(list, newelement);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}
void	ft_assigntype(int type, char *str, t_textures *tex)
{
	if (type == 1)
		tex->north = str;
	else if (type == 2)
		tex->south = str;
	else if (type == 3)
		tex->east = str;
	else if (type == 4)
		tex->west = str;
	else if (type == 5)
		tex->floor = str;
	else if (type == 6)
		tex->ceiling = str;
}

int	ft_checktexture(t_data *data, char *str, int type)
{
	int	fd;

	if (str[0] == 'F' || str[0] == 'C')
	{
		if (!ft_isspace(*(str + 1)))
			return (0);//syntax error
	}
	str++;
	if (!ft_isspace(*(str + 1)))
		return (0);//syntax error
	while (ft_isspace(*str))
		str++;
	//before opening, check file extension .xpm
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (0); //read error;
	close(fd);
	ft_assigntype(type, str, &data->textures);
	return (0);
}

int	ft_classify(char *str)
{
	if (ft_strncmp(str, "NO", 2) == 0)
		return (1);
	if (ft_strncmp(str, "SO", 2) == 0)
		return (2);
	if (ft_strncmp(str, "EA", 2) == 0)
		return (3);
	if (ft_strncmp(str, "WE", 2) == 0)
		return (4);
	if (ft_strncmp(str, "F", 1) == 0)
		return (5);
	if (ft_strncmp(str, "C", 1) == 0)
		return (6);
	return (0);
}

int	ft_gettextures(t_list *file, t_data *data)
{
	char	*str;
	int		count;
	int		type;

	count = 0;
	while (file->content)
	{
		str = file->content;
		while (ft_isspace(*str))
			str++;
		type = ft_classify(str);
		if (type != 0)
		{
			if (!ft_checktexture(data, str, type))
				return (0);
			count++;
		}
		file = file->next;
	}
	if (count != 6)
		return (0);//missing information
	return (1);
}

int	ft_checkmap(int fd, t_data *data)
{
	t_list	*file;
	t_list  *node;
	int	 num_rows;
	int	 num_cols;
	char	**map_array;

	if (!ft_parsefile(&file, fd))
		return (0);
	if (!ft_gettextures(file, data))
		return (0);
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
	map_array = malloc((num_rows + 1) * sizeof(char *));
	if (!map_array)
		return (ft_closeerror(fd, "Malloc error"));
	while (num_cols > 0)
	{
		map_array[num_rows] = malloc((num_cols + 1) * sizeof(int));
		if (!map_array[num_rows])
			return (ft_closeerror(fd, "Malloc error"));
		num_cols--;
	}

	while(file)
	{
		ft_printf("%s", file->content);
		file = file->next;
	}
	return (0);
}
