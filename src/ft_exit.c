#include "cub3D.h"

void	ft_close_mlx(t_mlx *mlx)
{
	if (mlx->mlx)
	{
		if (mlx->img)
			mlx_destroy_image(mlx->mlx, mlx->img);
		if (mlx->win)
			mlx_destroy_window(mlx->mlx, mlx->win);
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
	}
}

void	ft_freetex(t_textures tex)
{
	if (tex.north)
		free(tex.north);
	if (tex.south)
		free(tex.south);
	if (tex.east)
		free(tex.east);
	if (tex.west)
		free(tex.west);
}

int	ft_exit(t_data *data, int ret)
{
	ft_freetex(data->textures);
	ft_close_mlx(&(data->mlx));
	exit(ret);
	return (ret);
}