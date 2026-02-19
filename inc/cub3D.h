/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexp <alexp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 13:06:26 by alpascua          #+#    #+#             */
/*   Updated: 2026/02/19 19:54:37 by alexp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/Libft/libft.h"
#include <fcntl.h>

//list of textures
typedef struct s_textures
{
	char			*north;
	char			*south;
	char			*east;
	char			*west;
	unsigned int	floor;
	unsigned int	ceiling;
	//should also save the img (minilibx) associated
}	t_textures;

//struct where all data goes ("global variable")
typedef struct s_data
{
	t_textures	textures;
}	t_data;

// cub3d.c functions
int				ft_closeerror(int fd, char *str);

// parse.c functions
int				ft_parsefile(t_list **list, int fd);
int				ft_checkmap(int fd, t_data *data);
int				ft_checkargs(int narg, char **argv, t_data *data);
void			ft_assigntype(int type, char *str, t_textures *tex);

// parse_utils.c
int				ft_printerrorreturn(char *str, int ret);
int				ft_xpmextension(char *filename);
char			*ft_filename(char *str);

// parse_rgb.c
int				ft_checkrgb(t_data *data, char *str, int type);
unsigned int	ft_parse_rgb(char *str);

// ft_exit.c
void			ft_exit(t_data *data, int ret);

// init.c
int				ft_init(t_data *data);


