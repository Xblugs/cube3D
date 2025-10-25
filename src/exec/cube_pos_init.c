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

static void	find_start_pos(t_map *map, t_raycast *rc);
static void	find_start_angle(t_map *map, t_raycast *rc);

void	start_pos_wrapper(t_data *data, t_map *map, t_raycast *rc)
{
	find_start_pos(map, rc);
	find_start_angle(map, rc);
	printf("pos(x, y) = (%d, %d)\n", data->rc->pos[X], data->rc->pos[Y]);
	printf("   (l, c) = (%d, %d)\n\n", data->map->line, data->map->col);
	print_pos(data);
}

// find position in index values
static void	find_start_pos(t_map *map, t_raycast *rc)
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
				rc->pos[X] = j;
				rc->pos[Y] = i;
				return ;
			}
			j++;
		}
		i++;
	}
	printf("This should never print as map is correct at this point\n");
}

// set start angle and switches coordinates to px representation
static void	find_start_angle(t_map *map, t_raycast *rc)
{
	int	i;
	int	j;

	i = rc->pos[X];
	j = rc->pos[Y];
	if (map->map[i][j] == 'N')
		rc->view_angle = 90;
	else if (map->map[i][j] == 'W')
		rc->view_angle = 180;
	else if (map->map[i][j] == 'S')
		rc->view_angle = 270;
	rc->pos[X] = rc->pos[X] * UNIT + HALF_UNIT;
	rc->pos[Y] = rc->pos[Y] * UNIT + HALF_UNIT;
}
