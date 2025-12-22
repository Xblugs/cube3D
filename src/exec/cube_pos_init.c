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

/*
	Function to print current position is located 
		in cube_debug along other info prints
*/

static void	find_start_pos(t_map *map, t_raycast *rc);
static void	find_start_angle(t_map *map, t_raycast *rc);

void	start_pos_wrapper(t_data *data, t_map *map, t_raycast *rc)
{
	find_start_pos(map, rc);
	find_start_angle(map, rc);
	printf("pos(x, y) = (%d, %d)\n", data->rc->pos[X], data->rc->pos[Y]);
	printf("   (l, c) = (%d, %d)\n\n", data->map->height, data->map->width);
	print_pos(data, -1, -1);
}

/*
	Find start position in index values
	[stored in rc->pos to save memory]

	TODO: Normalize map
*/
static void	find_start_pos(t_map *map, t_raycast *rc)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height - 1)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S'
				|| map->map[i][j] == 'W' || map->map[i][j] == 'E')
			{
				rc->pos[Y] = i;
				rc->pos[X] = j;
				return ;
			}
			j++;
		}
		i++;
	}
	printf(B_RED"This should never print as map is correct at this point\n"END);
}

/*
	Set start angle and switches coordinates to px representation
*/
static void	find_start_angle(t_map *map, t_raycast *rc)
{
	int	i;
	int	j;

	i = rc->pos[Y];
	j = rc->pos[X];
	if (map->map[i][j] == 'W')
		rc->view_angle = 90;
	if (map->map[i][j] == 'N')
		rc->view_angle = 180;
	else if (map->map[i][j] == 'E')
		rc->view_angle = 270;
	rc->pos[Y] = i * UNIT + HALF_UNIT;
	rc->pos[X] = j * UNIT + HALF_UNIT;
}
