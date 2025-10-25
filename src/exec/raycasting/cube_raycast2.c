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

// returns 0 if coordinates are outside the window screen
int	is_in_scope(int inter_h[2], int inter_v[2])
{
	int			x;
	int			y;

	x = inter_h[X] / UNIT;
	y = inter_h[Y] / UNIT;
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return (0);
	x = inter_v[X] / UNIT;
	y = inter_v[Y] / UNIT;
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return (0);
	return (1);
}

// on wall hit, copy coordinates for rendering
int	wall_hit(t_raycast *rc, t_map *map)
{
	static int	cur_ray = 0;
	int			x;
	int			y;

	if (cur_ray == WIDTH)
		cur_ray = 0;
	x = rc->inter_h[X] / UNIT;
	y = rc->inter_h[Y] / UNIT;
	if (map->map[x][y] == '1')
	{
		rc->wall_hit[cur_ray][X] = rc->inter_h[X];
		rc->wall_hit[cur_ray][Y] = rc->inter_h[Y];
		cur_ray++;
		return (1);
	}
	x = rc->inter_v[X] / UNIT;
	y = rc->inter_v[Y] / UNIT;
	if (map->map[x][y] == '1')
	{
		rc->wall_hit[cur_ray][X] = rc->inter_v[X];
		rc->wall_hit[cur_ray][Y] = rc->inter_v[Y];
		cur_ray++;
		return (1);
	}
	return (0);
}
