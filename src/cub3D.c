/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <alpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 13:06:08 by alpascua          #+#    #+#             */
/*   Updated: 2026/02/15 13:39:46 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_checkfilename(char *name)
{
	int	len;

	len = ft_strlen(name);
	if (ft_strcmp(name + len - 4, ".cub") == 0)
		return (1);
	ft_putstr_fd("Argument file (", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(") has wrong extension\n", 2);
	ft_putstr_fd("You must input a .cub file\n", 2);
	return (0);
}

int	ft_closeerror(int fd, char *str)
{
	ft_putstr_fd(str, 2);
	close(fd);
	return (0);
}

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

int	ft_checkmap(int fd)
{
	t_list	*file;

	if (!ft_parsefile(&file, fd))
		return (0);
	while(file)
	{
		ft_printf("%s", file->content);
		file = file->next;
	}
	return (1);
}

int	ft_checkargs(int narg, char **argv)
{
	int	fd;

	if (narg != 2)
	{
		ft_putstr_fd("No map file (.cub)\n", 2);
		return (0);
	}
	if (!ft_checkfilename(argv[1]))
		return (0);
	fd = open(argv[1], __O_DIRECTORY);
	if (fd != -1)
	{
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(" is a directory\n", 2);
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Could not open ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	return (ft_checkmap(fd));
}

int	main(int narg, char **argv)
{
	if (!ft_checkargs(narg, argv))
		return (1);
	return (0);
}
