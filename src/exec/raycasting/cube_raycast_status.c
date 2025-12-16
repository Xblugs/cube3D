/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_raycast_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:37:56 by cczerwin          #+#    #+#             */
/*   Updated: 2025/10/25 16:37:58 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	ray_status_check(t_data *data, t_raycast *rc, t_calc *calc);

// check if our rays are going out of bounds or hit a wall
void	ray_status_check_wrapper(t_data *data, t_raycast *rc)
{
	if (!(rc->ray_status))
		ray_status_check(data, rc, data->calc);
}

/*
	Did we hit a wall or got out of the map?
		x = line index
		y = col  index
*/
static void	ray_status_check(t_data *data, t_raycast *rc, t_calc *calc)
{
	int	x;
	int	y;

	x = rc->ray[Y];
	y = rc->ray[X];
	if (y >= calc->max_width || x >= calc->max_height || x < 0 || y < 0)
		rc->ray_status = OUT;
	else
	{
		x /= UNIT;
		y /= UNIT;
		if (data->map->map[x][y] == '1')
			rc->ray_status = HIT;
	}
}

// get the wall coordinates
int	wall_hit(t_data *data, t_raycast *rc)
{
	if (rc->ray_status == HIT)
	{
		rc->wall_hit[rc->ray_index][X] = rc->ray[Y];
		rc->wall_hit[rc->ray_index][Y] = rc->ray[X];
		return (1);
	}
	else if (rc->ray_status == OUT)
		printf(RED"ray [%d] did not hit%s\n", data->rc->ray_index, END);
	return (0);
}
