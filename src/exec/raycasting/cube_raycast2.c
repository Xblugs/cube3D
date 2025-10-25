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

static void	find_closest_hit(t_raycast *rc);
static void	find_closest_hit2(t_raycast *rc);

// check if our raycast are going out of bounds
void	scope_check(t_raycast *rc, int inter_h[2], int inter_v[2])
{
	int			x;
	int			y;

	x = inter_h[X];
	y = inter_h[Y];
	if (x >= 256 || y >= 256 || x < 0 || y < 0)
		rc->out_h = 1;
	x = inter_v[X];
	y = inter_v[Y];
	if (x >= 256 || y >= 256 || x < 0 || y < 0)
		rc->out_v = 1;
}

// copy closest wall hit coordinates for rendering
// int	wall_hit(t_raycast *rc, t_map *map)
// {
// 	static int	cur_ray = 0;
// 	int			x;
// 	int			y;

// 	if (cur_ray == WIDTH)
// 		cur_ray = 0;
// 	x = rc->inter_h[X] / UNIT;
// 	y = rc->inter_h[Y] / UNIT;
// 	if (map->map[x][y] == '1')
// 	{
// 		rc->wall_hit[cur_ray][X] = rc->inter_h[X];
// 		rc->wall_hit[cur_ray][Y] = rc->inter_h[Y];
// 		cur_ray++;
// 		return (1);
// 	}
// 	x = rc->inter_v[X] / UNIT;
// 	y = rc->inter_v[Y] / UNIT;
// 	if (map->map[x][y] == '1')
// 	{
// 		rc->wall_hit[cur_ray][X] = rc->inter_v[X];
// 		rc->wall_hit[cur_ray][Y] = rc->inter_v[Y];
// 		cur_ray++;
// 		return (1);
// 	}
// 	return (0);
// }

int	wall_hit(t_raycast *rc, t_map *map)
{
	int			x[2];
	int			y[2];

	if (rc->ray_index == WIDTH)
		rc->ray_index = 0;
	x[0] = rc->inter_h[X] / UNIT;
	y[0] = rc->inter_h[Y] / UNIT;
	x[1] = rc->inter_v[X] / UNIT;
	y[1] = rc->inter_v[Y] / UNIT;
	if (map->map[x[0]][y[0]] == '1' || map->map[x[1]][y[1]] == '1')
	{
		find_closest_hit(rc);
		rc->ray_index++;
		return (1);
	}
	return (0);
}

static void	find_closest_hit(t_raycast *rc)
{
	scope_check(rc, rc->inter_h, rc->inter_v);
	if (rc->out_h)
	{
		rc->wall_hit[rc->ray_index][X] = rc->inter_v[X];
		rc->wall_hit[rc->ray_index][Y] = rc->inter_v[Y];
		return ;
	}
	if (rc->out_v)
	{
		rc->wall_hit[rc->ray_index][X] = rc->inter_h[X];
		rc->wall_hit[rc->ray_index][Y] = rc->inter_h[Y];
		return ;
	}
	find_closest_hit2(rc);
}

// both ray hit, calc distance and copy the closest one
static void	find_closest_hit2(t_raycast *rc)
{
	int	dist_h;
	int	dist_v;

	dist_h = sqrt(ft_iter_pow(rc->pos[X] - rc->inter_h[X], 2)
			+ ft_iter_pow(rc->pos[Y] - rc->inter_h[Y], 2));
	dist_v = sqrt(ft_iter_pow(rc->pos[X] - rc->inter_v[X], 2)
			+ ft_iter_pow(rc->pos[Y] - rc->inter_v[Y], 2));
	if (dist_h > dist_v)
	{
		rc->wall_hit[rc->ray_index][X] = rc->inter_h[X];
		rc->wall_hit[rc->ray_index][Y] = rc->inter_h[Y];
	}
	else
	{
		rc->wall_hit[rc->ray_index][X] = rc->inter_v[X];
		rc->wall_hit[rc->ray_index][Y] = rc->inter_v[Y];
	}
}
