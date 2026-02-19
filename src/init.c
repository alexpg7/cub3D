/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexp <alexp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 18:23:06 by alpascua          #+#    #+#             */
/*   Updated: 2026/02/19 19:55:33 by alexp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_init(t_data *data)
{
	data->textures.east = NULL;
	data->textures.west = NULL;
	data->textures.north= NULL;
	data->textures.south = NULL;
	data->textures.floor = 0;
	data->textures.ceiling = 0;
	return (0);
}
