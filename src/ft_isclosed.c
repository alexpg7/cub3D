/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isclosed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexp <alexp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 16:14:03 by alpascua          #+#    #+#             */
/*   Updated: 2026/02/18 19:04:00 by alexp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../lib/Libft/libft.h"

int	ft_checkaround(char **str, int i, int j)
{
	if (str[i - 1][j] == ' ')
		return (0);
	if (str[i + 1][j] == ' ')
		return (0);
	if (str[i][j - 1] == ' ')
		return (0);
	if (str[i][j + 1] == ' ')
		return (0);
	return (1);
}

int	ft_isclosed(char **str)
{
	int	i;
	int	j;
	int	xmax;
	int	ymax;

	i = 0;
	xmax = ft_arrlen((const char **)str);
	ymax = ft_strlen(str[0]);
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '0')
			{
				if (i == 0 || j == 0 || i == xmax - 1 || j == ymax - 1)
					return (0);
				if (!ft_checkaround(str, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

/*int	main(void)
{
	char	**str;

	str = (char **)malloc(sizeof(char *) * 8);
	str[0] = ft_strdup("11111111 111111111");
	str[1] = ft_strdup("100000011100000001");
	str[2] = ft_strdup("100000000000000011");
	str[3] = ft_strdup("100000000000100001");
	str[4] = ft_strdup("111111111111111111");
	str[5] = ft_strdup("100000000000000001");
	str[6] = ft_strdup("111111111111111111");
	str[7] = NULL;
	for (int i = 0; i < 7; i++)
		printf("%s\n", str[i]);
	printf("\n");
	if (!ft_isclosed(str))
		printf("Not floodable!\n");
	for (int i = 0; i < 7; i++)
		printf("%s\n", str[i]);
	return (1);//ft_isclosed(str));
}*/
