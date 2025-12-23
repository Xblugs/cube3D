/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_map_validating.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:32:09 by aeudes            #+#    #+#             */
/*   Updated: 2025/12/22 17:09:27 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	init_map_copy_forflood(t_map *map);
static int	is_valid_char_forflood(char c);
static int	open_map_handling(t_map *map);

/*
	if outside of the map, error
	if 1 or V, true
	if ' ' false
	Set to 'V' for each visited space
*/
bool	flood_fill(t_map *map, int x, int y)
{
	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
		return (false);
	if (map->copy[y][x] == '1' || map->copy[y][x] == 'V')
		return (true);
	map->copy[y][x] = 'V';
	return (flood_fill(map, x + 1, y)
		&& flood_fill(map, x - 1, y)
		&& flood_fill(map, x, y + 1)
		&& flood_fill(map, x, y - 1)
	);
}

/*
	Floodfill the map to ensure it's closed
*/
int	check_if_map_closed(t_map *map)
{
	int	y;
	int	x;

	if (!init_map_copy_forflood(map))
		return (0);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (is_valid_char_forflood(map->copy[y][x]))
			{
				if (!flood_fill(map, x, y))
					return (open_map_handling(map));
			}
			x++;
		}
		y++;
	}
	free_dbl_arr(map->copy);
	return (1);
}

/*
	Creates a copy from the original map for floodfill
*/
static int	init_map_copy_forflood(t_map *map)
{
	map->copy = prepare_for_flood(map->map, map->height, map->width);
	if (!map->copy)
	{
		printf("%sError: Map copying failed.\n", ERROR);
		return (0);
	}
	return (1);
}

/*
	if 0 (can be walked on)
	if N S E W (player spawn)
	if not V, isn't visited yet
	its to show where flood fill starts from
*/
static int	is_valid_char_forflood(char c)
{
	return ((c == '0' || is_player_spawn(c)) && c != 'V');
}

/*
	Called when floodfill fails
*/
static int	open_map_handling(t_map *map)
{
	free_dbl_arr(map->copy);
	printf("%sError: Map is open.\n", ERROR);
	return (0);
}
