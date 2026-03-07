/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <alpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 13:06:26 by alpascua          #+#    #+#             */
/*   Updated: 2026/03/07 12:02:36 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../lib/Libft/libft.h"
# include "../lib/minilibx-linux/mlx.h"
# include "../lib/minilibx-linux/mlx_int.h"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <sys/time.h>

# define PI 3.1415926535
# define KEYW 119
# define KEYA 97
# define KEYS 115
# define KEYD 100
# define KEYLEFT 65361
# define KEYRIGHT 65363
# define KEYSHIFT 65505
# define KEYCTRL 65507
# define ESC 65307

//list of textures

typedef struct s_texture
{
	char	*path;
	void	*img;
	int		img_w;
	int		img_h;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
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
	float	dist;
	int		x;// i coordinate in map
	int		y;// j coordinate in map
	char	orientation;//N, S, E, W of last wall gone through
}	t_ray;

typedef struct s_player
{
	t_vec2	pos;
	float	look_dir;
	float	h;
	float	fov;
	char	w_key;
	char	a_key;
	char	s_key;
	char	d_key;
	char	left_key;
	char	right_key;
	char	shift_key;
	char	ctrl_key;
	t_vec2	vel;
	float	look_vel;
	float	h_vel;
}	t_player;

//struct where all data goes ("global variable")
typedef struct s_data
{
	t_mlx			mlx;
	t_player		player;
	t_textures		textures;
	char			tex_rec[6];
	struct timeval	last_time;
	char			**map;
	int				rows;
	int				cols;
}	t_data;

// cub3d.c functions
int				ft_closeerror(int fd, char *str);

// parse.c functions
int				ft_parsefile(t_list **list, int fd);
int				ft_checkargs(int narg, char **argv, t_data *data);
void			ft_assigntype(int type, char *str, t_textures *tex);
int				ft_readline(char *str, t_data *data, int type, char *o_string);
int				ft_classify(char *str);

// parse_map.c
int				ft_checkmap(int fd, t_data *data);
int				ft_validate_map_chars_and_players(t_data *data);
int				ft_is_closed(t_data *data);

// parse_map_utils.c
int				ft_validate_map(t_data *data, t_list *file);
int				ft_aroundmap(char **map, int i, int j);
float			ft_choosedir(char c);
void			ft_setdata(t_data *data, int *count, int i, int j);
void			ft_alloc_cols(char *content, char **map, int i, int cols);

// parse_utils.c
int				ft_perror(char *str, int ret);
int				ft_xpmextension(char *filename);
char			*ft_filename(char *str);
int				ft_isspace_n(char c);
int				ft_classify(char *str);

// ft_exit.c
int				ft_exit(t_data *data, int ret);

// hooks.c
int				ft_hookexit(t_data *data);
int				key_press(int keycode, t_data *data);
int				key_release(int keycode, t_data *data);
int				ft_movemouse(int x, int y, t_data *data);

// hooks_utils.c
t_vec2			ft_rotate(t_vec2 vec, float angle);
int				game_loop(t_data *data);
t_vec2			ft_changepos(t_vec2 vec, float angle, t_data *data);

// init.c
int				ft_init(t_data *data);
void			ft_screendef(t_mlx *mlx, t_data *data);
void			ft_init_window(t_mlx *mlx, t_data *data);

// ft_paintscreen.c
void			ft_paintscreen(t_data *data);

//ft_paintscreen_utils.c
void			pixel_put(t_mlx *mlx, int x, int y, int color);
unsigned int	pixel_get(t_texture tex, int x, int y);

// ray.c
float			ft_distance(t_vec2 v1, t_vec2 v2);
t_ray			ft_startray(t_vec2 start, float dir);
t_texture		ft_raycast(t_ray *ray, char **map, t_data *data);

// ray_utils.c
//char			get_cell(char **map, t_vec2 pos, t_vec2 dir);
float			ft_div0(float f1, float f2);

// parse_textures.c
int				ft_checktexture(t_data *data, char *str, int type);
int				ft_gettextures(t_list *file, t_data *data);
void			ft_assigntype(int type, char *str, t_textures *tex);
int				ft_classify(char *str);

// parse_rgb.c
int				ft_checkrgb(t_data *data, char *str, int type);
unsigned int	ft_parse_rgb(char *str);

// textures.c
int				ft_loadtextures(t_data *data);

#endif
