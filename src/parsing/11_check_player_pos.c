/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_check_player_pos.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:32:03 by aeudes            #+#    #+#             */
/*   Updated: 2025/12/15 14:41:09 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*
	Locating the player's starting point and orientation
	(Values setting got moved to exec part)
*/
void	check_player_pos(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (is_player_spawn(map->map[y][x]))
				return ;
			x++;
		}
		y++;
	}
}
