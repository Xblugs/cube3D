/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_move_handler2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 19:22:12 by cczerwin          #+#    #+#             */
/*   Updated: 2025/12/19 19:22:13 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*
	Regular moves but shifted from [pi/2] or [-pi/2]
		to go forward on the selected side
*/
void	lateral_handler(t_data *data, t_raycast *rc, int key)
{
	int	x;
	int	y;

	if (key == 'a')
		move_prep(rc, -90);
	else if (key == 'd')
		move_prep(rc, +90);
	x = rc->pos[Y] / UNIT;
	y = (rc->pos[X] + rc->delta[X]) / UNIT;
	if (data->map->map[x][y] != '1')
		rc->pos[X] += rc->delta[X];
	x = (rc->pos[Y] + rc->delta[Y]) / UNIT;
	y = rc->pos[X] / UNIT;
	if (data->map->map[x][y] != '1')
		rc->pos[Y] += rc->delta[Y];
}
