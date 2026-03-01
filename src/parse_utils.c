/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <alpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 11:18:19 by alpascua          #+#    #+#             */
/*   Updated: 2026/03/01 13:06:20 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_xpmextension(char *filename)
{
	if (ft_strncmp(filename + ft_strlen(filename) - 4, ".xpm", 4) == 0)
		return (1);
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(" has no .xpm extension\n", 2);
	return (0);
}

char	*ft_filename(char *str)
{
	int		i;
	char	*ptr;

	i = 0;
	while (!ft_isspace(str[i]))
		i++;
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
