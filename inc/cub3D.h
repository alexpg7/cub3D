/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <alpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 13:06:26 by alpascua          #+#    #+#             */
/*   Updated: 2026/02/22 17:07:27 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/Libft/libft.h"
#include "../lib/minilibx-linux/mlx.h"
#include "../lib/minilibx-linux/mlx_int.h"
#include <fcntl.h>
#include <stdio.h>
#include <math.h>

#define PI 3.1415926535

//list of textures

typedef struct s_texture
{
	char	*path;
	void	*img;
	int		img_w;
	int		img_h;
}	t_texture;

typedef struct s_textures
{
	t_texture		north;
	t_texture		south;
	t_texture		east;
	t_texture		west;
	unsigned int	floor;
	unsigned int	ceiling;
}	t_textures;

//struct for mlx variables
typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	int		x;
	int		y;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx;

typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;

typedef struct s_ray
{
	t_vec2	start;
	t_vec2	pos;
	t_vec2	dir;
}	t_ray;

typedef struct s_player
{
	t_vec2	pos;
	float	look_dir;
	float	h;
	float	fov;
}	t_player;

//struct where all data goes ("global variable")
typedef struct s_data
{
	t_mlx		mlx;
	t_player	player;
	t_textures	textures;
	char		**map;
}	t_data;

// cub3d.c functions
int				ft_closeerror(int fd, char *str);

// parse.c functions
int				ft_parsefile(t_list **list, int fd);
int				ft_checkmap(int fd, t_data *data);
int				ft_checkargs(int narg, char **argv, t_data *data);
void			ft_assigntype(int type, char *str, t_textures *tex);
int				ft_readline(char *str, t_data *data, int type, char *origstring);
int				ft_classify(char *str);

// parse_utils.c
int				ft_printerrorreturn(char *str, int ret);
int				ft_xpmextension(char *filename);
char			*ft_filename(char *str);

// parse_rgb.c
int				ft_checkrgb(t_data *data, char *str, int type);
unsigned int	ft_parse_rgb(char *str);

// ft_exit.c
int				ft_exit(t_data *data, int ret);

// hooks.c
int				ft_hookexit(t_data *data);

// init.c
int				ft_init(t_data *data);
void			ft_screendef(t_mlx *mlx, t_data *data);
void			ft_init_window(t_mlx *mlx, t_data *data);

// ft_paintscreen
void			ft_paintscreen(t_data *data);

// ray.c
float			ft_distance(t_vec2 v1, t_vec2 v2);
t_ray			ft_startray(t_vec2 start, float dir);
int				ft_raycast(t_ray ray, char **map, t_data *data);

// textures.c
int				ft_checktexture(t_data *data, char *str, int type);
int				ft_gettextures(t_list *file, t_data *data);
void			ft_loadtex(t_texture *tex, void *mlx);
int				ft_loadtextures(t_data *data);
