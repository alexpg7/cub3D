/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarodrig <sarodrig@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 13:06:26 by alpascua          #+#    #+#             */
/*   Updated: 2026/02/15 15:48:10 by sarodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/Libft/libft.h"
#include <fcntl.h>

// cub3d.c functions
int	ft_closeerror(int fd, char *str);

// parse.c functions
int	ft_parsefile(t_list **list, int fd);
int	ft_checkmap(int fd);
int	ft_checkargs(int narg, char **argv);


