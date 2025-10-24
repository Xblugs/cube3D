/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_move_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:48:08 by cczerwin          #+#    #+#             */
/*   Updated: 2025/10/24 16:48:09 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*
	move values depend on current orientation
	currently arrow key are used on brick_handler and [wasd] for player pos
*/
void	move_handler(int key, t_data *data)
{
	int	ms;

	ms = MOV_SCALE;
	if (key == UP || key == DOWN || key == 'w' || key == 's')
	{
		if (key == UP || key == 'w')
		{
			data->map->pos[X] += (cos(deg_to_rad(data->map->view_angle)) * ms);
			data->map->pos[Y] += (sin(deg_to_rad(data->map->view_angle)) * ms);
		}
		else
		{
			data->map->pos[X] -= (cos(deg_to_rad(data->map->view_angle)) * ms);
			data->map->pos[Y] -= (sin(deg_to_rad(data->map->view_angle)) * ms);
		}
	}
	else if (key == LEFT || key == 'a')
		data->map->view_angle += 10;
	else if (key == RIGHT || key == 'd')
	{
		data->map->view_angle -= 10;
		if (data->map->view_angle < 0)
			data->map->view_angle += 360;
	}
	data->map->view_angle %= 360;
}
