/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <alpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 17:46:31 by sarodrig          #+#    #+#             */
/*   Updated: 2026/03/01 15:38:10 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_list	*ft_locate_and_size_map(t_list *file, int *rows, int *cols)
{
	int		count;
	int		len;
	t_list	*map_start;

	*rows = 0;
	*cols = 0;
	count = 0;
	while (file && count < 6)
	{
		if (ft_strlen((char *)file->content) > 1)
			count++;
		file = file->next;
	}
	while (file && ft_strlen((char *)file->content) <= 1)
		file = file->next;
	map_start = file;
	while (file)
	{
		len = ft_strlen((char *)file->content);
		if (len > *cols)
			*cols = len;
		(*rows)++;
		file = file->next;
	}
	return (map_start);
}

char	**ft_alloc_map(t_list *node, int rows, int cols)
{
	char	**map;
	char	*content;
	int		i;

	i = 0;
	map = (char **)malloc(sizeof(char *) * (rows + 1));
	if (!map)
		return (NULL);
	while (i < rows)
	{
		content = (char *)node->content;
		map[i] = malloc(sizeof(char) * (cols + 1));
		if (!map[i])
			return (NULL);
		ft_alloc_cols(content, map, i, cols);
		node = node->next;
		i++;
	}
	map[i] = (NULL);
	return (map);
}

int	ft_validate_map_chars_and_players(t_data *data)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (!ft_strchr("01NSEW ", data->map[i][j]))
				return (ft_perror("Invalid map character", 0));
			if (ft_strchr("NSEW", data->map[i][j]))
				ft_setdata(data, &player_count, i, j);
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (ft_perror("Invalid number of players", 0));
	return (1);
}

int	ft_is_closed(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '0' ||
				ft_strchr("NSEW", data->map[i][j]))
			{
				if (i == 0 || j == 0
					|| !data->map[i + 1]
					|| data->map[i][j + 1] == '\0')
					return (ft_perror("Map is not closed", 0));
				if (ft_aroundmap(data->map, i, j))
					return (ft_perror("Map is not closed", 0));
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_checkmap(int fd, t_data *data)
{
	t_list	*file;
	t_list	*map_start;
	int		rows;
	int		cols;

	if (!ft_parsefile(&file, fd))
		return (0);
	if (!ft_gettextures(file, data))
	{
		ft_lstclear(&file, &free);
		return (0);
	}
	map_start = ft_locate_and_size_map(file, &rows, &cols);
	if (!map_start || rows == 0)
	{
		ft_lstclear(&file, &free);
		return (ft_perror("Map missing", 0));
	}
	data->map = ft_alloc_map(map_start, rows, cols);
	if (!data->map)
	{
		ft_lstclear(&file, &free);
		return (ft_perror("Malloc error", 0));
	}
	return (ft_validate_map(data, file));
}
