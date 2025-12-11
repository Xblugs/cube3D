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
static void	ray_status_check(t_data *data, t_raycast *rc, t_calc *calc, int i);
static void	find_hit(t_data *data, t_raycast *rc);
static void	find_closest_hit(t_data *data, t_raycast *rc);

// check if our rays are going out of bounds or hit a wall
void	ray_status_check_wrapper(t_data *data, t_raycast *rc)
{
	if (!(rc->ray_status[H]))
		ray_status_check(data, rc, data->calc, H);
	if (!(rc->ray_status[V]))
		ray_status_check(data, rc, data->calc, V);
}

/*
	TODO: Change the map wall check depending on current quadrant

	i is the equivalent value to macro [H] or [V]
		to differentiate vertical / horizontal ray
*/
static void	ray_status_check(t_data *data, t_raycast *rc, t_calc *calc, int i)
{
	int	x;
	int	y;

	x = rc->inter[i][X];
	y = rc->inter[i][Y];
	if (x >= calc->max_width || y >= calc->max_height || x < 0 || y < 0)
		rc->ray_status[i] = OUT;
	else
	{
		x /= UNIT;
		y /= UNIT;
		if (data->map->map[x][y] == '1')
			rc->ray_status[i] = HIT;
	}
}

// get the wall coordinates
int	wall_hit(t_data *data, t_raycast *rc)
{
	if (rc->ray_status[H] == HIT || rc->ray_status[V] == HIT)
	{
		find_hit(data, rc);
		rc->ray_index++;
		return (1);
	}
	else
		printf(RED"ray [%d] did not hit%s\n", rc->ray_index, END);
	return (0);
}

/*
	This function is called only once a wall is hit
	If one ray is out of bound, the other must have hit the wall
*/
static void	find_hit(t_data *data, t_raycast *rc)
{
	if (rc->ray_status[H] == OUT && rc->ray_status[V] == HIT)
	{
		rc->wall_hit[rc->ray_index][X] = rc->inter[V][X];
		rc->wall_hit[rc->ray_index][Y] = rc->inter[V][Y];
		return ;
	}
	else if (rc->ray_status[H] == HIT && rc->ray_status[V] == OUT)
	{
		rc->wall_hit[rc->ray_index][X] = rc->inter[H][X];
		rc->wall_hit[rc->ray_index][Y] = rc->inter[H][Y];
		return ;
	}
	else if (rc->ray_status[H] == HIT && rc->ray_status[V] == HIT)
		find_closest_hit(data, rc);
}

// both ray hit, calc distance and copy the closest one
static void	find_closest_hit(t_data *data, t_raycast *rc)
{
	double	dist[2];

	(void)data;
	dist[H] = sqrt(pow(rc->pos[X] - rc->inter[H][X], 2)
			+ pow(rc->pos[Y] - rc->inter[H][Y], 2));
	dist[V] = sqrt(pow(rc->pos[X] - rc->inter[V][X], 2)
			+ pow(rc->pos[Y] - rc->inter[V][Y], 2));
	if (dist[H] < dist[V])
	{
		rc->wall_hit[rc->ray_index][X] = rc->inter[H][X];
		rc->wall_hit[rc->ray_index][Y] = rc->inter[H][Y];
		rc->ray_status[V] = OUT;
	}
	else
	{
		rc->wall_hit[rc->ray_index][X] = rc->inter[V][X];
		rc->wall_hit[rc->ray_index][Y] = rc->inter[V][Y];
		rc->ray_status[H] = OUT;
	}
}
