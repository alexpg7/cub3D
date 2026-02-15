/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarodrig <sarodrig@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 15:35:08 by sarodrig          #+#    #+#             */
/*   Updated: 2026/02/15 16:47:31 by sarodrig         ###   ########.fr       */
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

int	**ft_checkmap(int fd)
{
	t_list	*file;
    t_list  *node;
    int     num_rows;
    int     num_cols;
    char    **map_array;

	if (!ft_parsefile(&file, fd))
		return (0);
    
    node = file;
    num_cols = 0;
    num_rows = 0;

    while (node)
    {
        if (ft_strlen((char *)node->content) > num_cols)
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
	return (map_array);
}
