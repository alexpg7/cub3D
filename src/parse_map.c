/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <alpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 17:46:31 by sarodrig          #+#    #+#             */
/*   Updated: 2026/03/01 14:04:33 by alpascua         ###   ########.fr       */
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
	int		j;

	i = 0;
	map = malloc(sizeof(char *) * (rows + 1));
	if (!map)
		return (NULL);
	while (i < rows)
	{
		content = (char *)node->content;
		map[i] = malloc(sizeof(char) * (cols + 1));
		if (!map[i])
			return (NULL);
		j = 0;
		while (j < cols)
		{
			if (j < (int)ft_strlen(content) - 1)
				map[i][j] = content[j];
			else
				map[i][j] = ' ';
			j++;
		}
		map[i][j] = '\0';
		node = node->next;
		i++;
	}
	map[i] = (NULL);
	return (map);
}

int	ft_is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' ||
			c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

float	ft_choosedir(char c)
{
	if (c == 'N')
		return (PI);
	else if (c == 'S')
		return (0);
	else if (c == 'E')
		return (PI / 2);
	return (3 * PI / 2);
}

int	ft_validate_map_chars_and_players(t_data *data)
{
	int i = 0;
	int j;
	int player_count = 0;

	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (!ft_is_valid_char(data->map[i][j]))
				return (ft_perror("Invalid map character", 0));
			if (ft_strchr("NSEW", data->map[i][j]))
			{
				data->player.look_dir = ft_choosedir(data->map[i][j]);
				data->player.pos.x = i + 0.5;
				data->player.pos.y = j + 0.5;
				player_count++;
			}
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
	int i;
	int j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '0' ||
				ft_strchr("NSEW", data->map[i][j]))
			{
				if (i == 0 || j == 0 ||
					!data->map[i + 1] ||
					data->map[i][j + 1] == '\0')
					return (ft_perror("Map is not closed", 0));
				if (data->map[i - 1][j] == ' ' ||
					data->map[i + 1][j] == ' ' ||
					data->map[i][j - 1] == ' ' ||
					data->map[i][j + 1] == ' ')
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
	if (!ft_validate_map_chars_and_players(data) || !ft_is_closed(data))
	{
		ft_lstclear(&file, &free);
		return (0);
	}
	ft_lstclear(&file, &free);
	return (1);
}

// int	ft_checkmap(int fd, t_data *data)
// {
// 	t_list	*file;
// 	t_list	*node;
// 	int		num_rows;
// 	int		num_cols;
// 	char	**map_array;

// 	if (!ft_parsefile(&file, fd))
// 		return (0);
// 	if (!ft_gettextures(file, data))
// 	{
// 		ft_lstclear(&file, &free);
// 		return (0);
// 	}
// 	//create matrix funtion
// 	node = file;
// 	num_cols = 0;
// 	num_rows = 0;
// 	while (node)
// 	{
// 		if (ft_strlen((char *)node->content) > (size_t)num_cols)
// 			num_cols = ft_strlen((char *)node->content);
// 		num_rows++;
// 		node = node->next;
// 	}
// 	map_array = (char **)malloc((num_rows + 1) * sizeof(char *));
// 	if (!map_array)
// 		return (ft_closeerror(fd, "Malloc error"));
// 	while (num_cols > 0)
// 	{
// 		map_array[num_rows] = (char *)malloc((num_cols + 1) * sizeof(int));
// 		if (!map_array[num_rows])
// 			return (ft_closeerror(fd, "Malloc error"));
// 		num_cols--;
// 	}



// 	while (file)
// 	{
// 		ft_printf("%s", file->content);
// 		file = file->next;
// 	}

// 	//Leaks from map_array and file
// 	return (1);
// }
