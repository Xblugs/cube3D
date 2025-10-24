/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_pos_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:17:22 by cczerwin          #+#    #+#             */
/*   Updated: 2025/10/24 16:17:23 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	find_start_pos(t_map *map);
static void	find_start_angle(t_map *map);

void	start_pos_wrapper(t_data *data, t_map *map)
{
	find_start_pos(map);
	find_start_angle(map);
	printf("pos(x, y) = (%d, %d)\n", data->map->pos[X], data->map->pos[Y]);
	printf("   (l, c) = (%d, %d)\n\n", data->map->line, data->map->col);
	print_pos(data);
}

// find position in index values
static void	find_start_pos(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->line)
	{
		j = 0;
		while (j < map->col)
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S'
				|| map->map[i][j] == 'W' || map->map[i][j] == 'E')
			{
				map->pos[X] = j;
				map->pos[Y] = i;
				return ;
			}
			j++;
		}
		i++;
	}
	printf("This should never print as map is correct at this point\n");
}

// set start angle and switches coordinates to px representation
static void	find_start_angle(t_map *map)
{
	int	i;
	int	j;

	i = map->pos[X];
	j = map->pos[Y];
	if (map->map[i][j] == 'N')
		map->view_angle = 90;
	else if (map->map[i][j] == 'W')
		map->view_angle = 180;
	else if (map->map[i][j] == 'S')
		map->view_angle = 270;
	map->pos[X] = map->pos[X] * UNIT + HALF_UNIT;
	map->pos[Y] = map->pos[Y] * UNIT + HALF_UNIT;
}
