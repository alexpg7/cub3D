/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexp <alexp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 13:06:08 by alpascua          #+#    #+#             */
/*   Updated: 2026/02/20 16:37:45 by alexp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_closeerror(int fd, char *str)
{
	ft_putstr_fd(str, 2);
	close(fd);
	return (0);
}

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

int	ft_checkargs(int narg, char **argv, t_data *data)
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
	return (ft_checkmap(fd, data));
}

int	main(int narg, char **argv)
{
	t_data	data;

	ft_init(&data);
	if (!ft_checkargs(narg, argv, &data))
		ft_exit(&data, 1);
	ft_screendef(&(data.mlx), &data);
	ft_init_window(&(data.mlx), &data);
	ft_exit(&data, 0);
	return (0);
}
