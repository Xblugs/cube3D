/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_texturing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:22:19 by cczerwin          #+#    #+#             */
/*   Updated: 2025/12/16 18:22:20 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	select_texture_1(t_data *data, t_raycast *rc, t_draw *draw);
static void	select_texture_2(t_data *data, t_raycast *rc, t_draw *draw);

void	draw_texture(t_data *data, t_raycast *rc, t_draw *draw)
{
	if (rc->ray_angle <= 180)
		select_texture_1(data, rc, draw);
	else
		select_texture_2(data, rc, draw);
	data->map->h_wall = draw->color;
}

/*
	Select the texture depending on which side of the wall we're seeing
	Colors (C_COLORNAME) act as flags here

	When hitting a corner, consider the last drawn wall as the correct one

		N = C_YELLOW			S = C_GREEN
		W = C_ORANGE			E = C_WHITE

	(TODO: to be eventually replaced with corresponding macros)
*/
static void	select_texture_1(t_data *data, t_raycast *rc, t_draw *draw)
{
	short	i;

	i = rc->ray_index;
	if (rc->ray_angle <= 90)
	{
		if (rc->wall_hit[i][X] % (short)UNIT == 0
			&& rc->wall_hit[i][Y] % (short)UNIT == UNIT - 1)
			draw->color = data->map->h_wall;
		else if (rc->wall_hit[i][X] % (short)UNIT == 0)
			draw->color = C_GREEN;
		else if (rc->wall_hit[i][Y] % (short)UNIT == UNIT - 1)
			draw->color = C_ORANGE;
	}
	else if (rc->ray_angle <= 180)
	{
		if (rc->wall_hit[i][X] % (short)UNIT == UNIT - 1
			&& rc->wall_hit[i][Y] % (short)UNIT == UNIT - 1)
			draw->color = data->map->h_wall;
		else if (rc->wall_hit[i][X] % (short)UNIT == UNIT - 1)
			draw->color = C_YELLOW;
		else if (rc->wall_hit[i][Y] % (short)UNIT == UNIT - 1)
			draw->color = C_ORANGE;
	}
}

static void	select_texture_2(t_data *data, t_raycast *rc, t_draw *draw)
{
	short	i;

	i = rc->ray_index;
	if (rc->ray_angle <= 270)
	{
		if (rc->wall_hit[i][X] % (short)UNIT == UNIT - 1
			&& rc->wall_hit[i][Y] % (short)UNIT == 0)
			draw->color = data->map->h_wall;
		else if (rc->wall_hit[i][X] % (short)UNIT == UNIT - 1)
			draw->color = C_YELLOW;
		else if (rc->wall_hit[i][Y] % (short)UNIT == 0)
			draw->color = C_WHITE;
	}
	else if (rc->ray_angle < 360)
	{
		if (rc->wall_hit[i][X] % (short)UNIT == 0
			&& rc->wall_hit[i][Y] % (short)UNIT == 0)
			draw->color = data->map->h_wall;
		else if (rc->wall_hit[i][X] % (short)UNIT == 0)
			draw->color = C_GREEN;
		else if (rc->wall_hit[i][Y] % (short)UNIT == 0)
			draw->color = C_WHITE;
	}
}
