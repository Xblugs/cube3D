/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_check_if_one_spawn.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:31:56 by aeudes            #+#    #+#             */
/*   Updated: 2025/12/22 17:08:48 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	is_player_spawn(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	find_last_line(char **map)
{
	int	k;

	k = 0;
	while (map[k])
		k++;
	return (k);
}

/*
	Ensures there is exactly one player spawn
*/
int	check_if_one_spawn(char **map)
{
	int	x;
	int	y;
	int	count;

	y = 0;
	count = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_player_spawn(map[y][x]))
			{
				if (y == 0 || x == 0 || y == find_last_line(map) - 1
					|| x == (int)ft_strlen(map[y]) - 1)
					return (0);
				count++;
			}
			x++;
		}
		y++;
	}
	if (count != 1)
		return (printf("%s%s%d\n", ERROR, ONLY_ONE_SPAWN, count), 0);
	return (1);
}
