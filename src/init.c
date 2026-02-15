/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <alpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 18:23:06 by alpascua          #+#    #+#             */
/*   Updated: 2026/02/15 18:25:00 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_init(t_data *data)
{
	data->textures.ceiling = NULL;
	data->textures.east = NULL;
	data->textures.west = NULL;
	data->textures.north= NULL;
	data->textures.south = NULL;
	data->textures.floor = NULL;
}
