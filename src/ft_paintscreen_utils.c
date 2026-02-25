#include "cub3D.h"


void	pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + y * mlx->line_length + x * mlx->bits_per_pixel / 8;
	*(unsigned int *)dst = color;
}

unsigned int	pixel_get(t_texture tex, int x, int y)
{
	return (*(unsigned int *)(tex.data + y * tex.size_line + x * (tex.bpp / 8)));
}