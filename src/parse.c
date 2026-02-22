/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <alpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 18:08:04 by alpascua          #+#    #+#             */
/*   Updated: 2026/02/22 19:19:44 by alpascua         ###   ########.fr       */
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
