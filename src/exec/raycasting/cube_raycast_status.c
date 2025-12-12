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

// using a short here would spawn a [LINE TOO LONG] norm error :c
static void	ray_status_check(t_data *data, t_raycast *rc, t_calc *calc);

// check if our rays are going out of bounds or hit a wall
void	ray_status_check_wrapper(t_data *data, t_raycast *rc)
{
	if (!(rc->ray_status))
		ray_status_check(data, rc, data->calc);
}

/*
	Did we hit a wall or got out of the map?
*/
static void	ray_status_check(t_data *data, t_raycast *rc, t_calc *calc)
{
	int	x;
	int	y;

	x = rc->ray[X];
	y = rc->ray[Y];
	if (x >= calc->max_width || y >= calc->max_height || x < 0 || y < 0)
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
		rc->wall_hit[rc->ray_index][X] = rc->ray[X];
		rc->wall_hit[rc->ray_index][Y] = rc->ray[Y];
		return (1);
	}
	else
		printf(RED"ray [%d] did not hit%s\n", data->rc->ray_index, END);
	return (0);
}
