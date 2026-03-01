/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <alpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 15:36:48 by alpascua          #+#    #+#             */
/*   Updated: 2026/03/01 15:38:14 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_validate_map(t_data *data, t_list *file)
{
	if (!ft_validate_map_chars_and_players(data) || !ft_is_closed(data))
	{
		ft_lstclear(&file, &free);
		return (0);
	}
	ft_lstclear(&file, &free);
	return (1);
}

int	ft_aroundmap(char **map, int i, int j)
{
	return (map[i - 1][j] == ' '
			|| map[i + 1][j] == ' '
			|| map[i][j - 1] == ' '
			|| map[i][j + 1] == ' ');
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

void	ft_setdata(t_data *data, int *count, int i, int j)
{
	data->player.look_dir = ft_choosedir(data->map[i][j]);
	data->player.pos.x = i + 0.5;
	data->player.pos.y = j + 0.5;
	*count = *count + 1;
}

void	ft_alloc_cols(char *content, char **map, int i, int cols)
{
	int	j;

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
}
