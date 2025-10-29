/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_raycast2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:37:56 by cczerwin          #+#    #+#             */
/*   Updated: 2025/10/25 16:37:58 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	find_closest_hit(t_data *data, t_raycast *rc);
static void	find_closest_hit2(t_data *data, t_raycast *rc);

// did we hit a wall yet?
int	wall_hit(t_data *data, t_raycast *rc, t_map *map)
{
	int			x[2];
	int			y[2];

	x[H] = rc->inter[H][X] / UNIT;
	y[H] = rc->inter[H][Y] / UNIT;
	x[V] = rc->inter[V][X] / UNIT;
	y[V] = rc->inter[V][Y] / UNIT;
	if (map->map[x[H]][y[H]] == '1' || map->map[x[V]][y[V]] == '1')
	{
		if (map->map[x[H]][y[H]] == '1')
			printf("H %c, index %d %d, val %d %d\n", map->map[x[H]][y[H]], x[H], y[H], rc->inter[H][X], rc->inter[H][Y]);
		else if (map->map[x[V]][y[V]] == '1')
			printf("V %c, index %d %d, val %d %d\n", map->map[x[V]][y[V]], x[V], y[V], rc->inter[V][X], rc->inter[V][Y]);
		find_closest_hit(data, rc);
		rc->ray_index++;
		return (1);
	}
	return (0);
}

// check if our raycast are going out of bounds
void	scope_check(t_raycast *rc, t_calc *calc)
{
	int			x;
	int			y;

	x = rc->inter[H][X];
	y = rc->inter[H][Y];
	if (x >= calc->max_width || y >= calc->max_height || x < 0 || y < 0)
		rc->out[H] = 1;
	x = rc->inter[V][X];
	y = rc->inter[V][Y];
	if (x >= calc->max_width || y >= calc->max_height || x < 0 || y < 0)
		rc->out[V] = 1;
}

/*
	This function is called only once a wall is hit
	If one ray is out of bound, the other must have hit the wall
*/
static void	find_closest_hit(t_data *data, t_raycast *rc)
{
	scope_check(rc, data->calc);
	if (rc->out[H])
	{
		rc->wall_hit[rc->ray_index][X] = rc->inter[V][X];
		rc->wall_hit[rc->ray_index][Y] = rc->inter[V][Y];
		return ;
	}
	if (rc->out[V])
	{
		rc->wall_hit[rc->ray_index][X] = rc->inter[H][X];
		rc->wall_hit[rc->ray_index][Y] = rc->inter[H][Y];
		return ;
	}
	find_closest_hit2(data, rc);
}

// both ray hit, calc distance and copy the closest one
static void	find_closest_hit2(t_data *data, t_raycast *rc)
{
	double	dist_h;
	double	dist_v;

	(void)data;
	dist_h = sqrt(pow(rc->pos[X] - rc->inter[H][X], 2)
			+ pow(rc->pos[Y] - rc->inter[H][Y], 2));
	dist_v = sqrt(pow(rc->pos[X] - rc->inter[V][X], 2)
			+ pow(rc->pos[Y] - rc->inter[V][Y], 2));
	if (dist_h < dist_v)
	{
		rc->wall_hit[rc->ray_index][X] = rc->inter[H][X];
		rc->wall_hit[rc->ray_index][Y] = rc->inter[H][Y];
	}
	else
	{
		rc->wall_hit[rc->ray_index][X] = rc->inter[V][X];
		rc->wall_hit[rc->ray_index][Y] = rc->inter[V][Y];
	}
}
