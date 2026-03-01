/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpascua <alpascua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 11:17:12 by alpascua          #+#    #+#             */
/*   Updated: 2026/03/01 13:41:35 by alpascua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	ft_pow(int a, int b)
{
	int	count;
	int	res;

	count = 0;
	res = 1;
	while (count < b)
	{
		res = res * a;
		count++;
	}
	return (res);
}

unsigned int	ft_parse_rgb(char *str)
{
	int	num;
	int	count;

	count = 0;
	num = 0;
	while (count < 3)
	{
		num = num + ft_atoi(str) * ft_pow(256, 2 - count);
		while (ft_isdigit(*str))
			str++;
		while (ft_isspace(*str))
			str++;
		if (*str)
			str++;
		while (ft_isspace(*str))
			str++;
		count++;
	}
	return ((unsigned int)num);
}

int	ft_isrgb(char *str)
{
	int	num;

	if (!ft_isdigit(str[0]))
		return (0);
	num = ft_atoi(str);
	if (num < 0 || num >= 256)
		return (0);
	return (1);
}

int	ft_checkrgb(t_data *data, char *str, int type)
{
	int		count;
	char	*color;

	str = str + 2;
	while (ft_isspace(*str))
		str++;
	count = 0;
	color = str;
	while (count < 3)
	{
		if (!ft_isrgb(str))
			return (ft_perror("Color in line is not RGB", 2));
		while (ft_isdigit(*str))
			str++;
		while (ft_isspace(*str))
			str++;
		if (*str == ',')
			str++;
		while (ft_isspace(*str))
			str++;
		count++;
	}
	ft_assigntype(type, color, &data->textures);
	return (0);
}
