/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexp <alexp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 11:18:19 by alpascua          #+#    #+#             */
/*   Updated: 2026/03/04 15:16:08 by alexp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_xpmextension(char *filename)
{
	if (ft_strlen(filename) < 1)
	{
		free(filename);
		return (ft_perror("No filename found", 0));
	}
	if (ft_strlen(filename) < 4)
	{
		ft_putstr_fd("Error\n\"", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd("\" has no .xpm extension\n", 2);
		free(filename);
		return (0);
	}
	if (ft_strncmp(filename + ft_strlen(filename) - 4, ".xpm", 4) == 0)
		return (1);
	ft_putstr_fd("Error\n\"", 2);
	ft_putstr_fd(filename, 2);
	free(filename);
	ft_putstr_fd("\" has no .xpm extension\n", 2);
	return (0);
}

int	ft_isspace_n(char c)
{
	if (c == ' ' || c == '\t'
		|| c == '\f' || c == '\f' || c == '\v')
	{
		return (1);
	}
	return (0);
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

char	*ft_filename(char *str)
{
	int		i;
	char	*ptr;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			break ;
		i++;
	}
	ptr = ft_substr(str, 0, i);
	if (!ptr)
		return (NULL);
	return (ptr);
}

int	ft_perror(char *str, int ret)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return (ret);
}
