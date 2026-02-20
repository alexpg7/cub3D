#include "cub3D.h"

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
	exit(ret);
	return (ret);
}