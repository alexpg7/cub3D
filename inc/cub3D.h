/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <alpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 13:06:26 by alpascua          #+#    #+#             */
/*   Updated: 2026/02/15 18:51:14 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/Libft/libft.h"
#include <fcntl.h>

//list of textures
typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	char	*floor;
	char	*ceiling;
	//should also save the img (minilibx) associated
}	t_textures;

//struct where all data goes ("global variable")
typedef struct s_data
{
	t_textures	textures;
}	t_data;

// cub3d.c functions
int	ft_closeerror(int fd, char *str);

// parse.c functions
int	ft_parsefile(t_list **list, int fd);
int	ft_checkmap(int fd, t_data *data);
int	ft_checkargs(int narg, char **argv, t_data *data);


