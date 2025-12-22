/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_select_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 18:46:35 by cczerwin          #+#    #+#             */
/*   Updated: 2025/12/17 18:46:36 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	select_texture_1(t_data *data, t_raycast *rc, t_draw *draw);
static void	select_texture_2(t_data *data, t_raycast *rc, t_draw *draw);
static void	select_texture_3(t_data *data, t_raycast *rc, t_draw *draw);
static void	select_texture_4(t_data *data, t_raycast *rc, t_draw *draw);

/*
	Select the texture depending on which side of the wall we're seeing
	Colors (C_COLORNAME) act as flags here

	When hitting a corner, consider the last drawn wall as the correct one

	[rc->ray_status] is re-used as a flag representing which wall side got hit
		, default as [X] changed if needed
*/
void	select_texture_wrapper(t_data *data, t_raycast *rc, t_draw *draw)
{
	rc->ray_status = X;
	if (rc->ray_angle <= 90)
		select_texture_1(data, rc, draw);
	else if (rc->ray_angle <= 180)
		select_texture_2(data, rc, draw);
	else if (rc->ray_angle <= 270)
		select_texture_3(data, rc, draw);
	else if (rc->ray_angle <= 360)
		select_texture_4(data, rc, draw);
	data->map->h_wall = draw->color;
}

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
			draw->color = S;
		else if (rc->wall_hit[i][Y] % (short)UNIT == UNIT - 1)
			draw->color = W;
		if (draw->color == W)
			rc->ray_status = Y;
	}
}

static void	select_texture_2(t_data *data, t_raycast *rc, t_draw *draw)
{
	short	i;

	i = rc->ray_index;
	if (rc->ray_angle <= 180)
	{
		if (rc->wall_hit[i][X] % (short)UNIT == UNIT - 1
			&& rc->wall_hit[i][Y] % (short)UNIT == UNIT - 1)
			draw->color = data->map->h_wall;
		else if (rc->wall_hit[i][X] % (short)UNIT == UNIT - 1)
			draw->color = N;
		else if (rc->wall_hit[i][Y] % (short)UNIT == UNIT - 1)
			draw->color = W;
		if (draw->color == W)
			rc->ray_status = Y;
	}
}

static void	select_texture_3(t_data *data, t_raycast *rc, t_draw *draw)
{
	short	i;

	i = rc->ray_index;
	if (rc->ray_angle <= 270)
	{
		if (rc->wall_hit[i][X] % (short)UNIT == UNIT - 1
			&& rc->wall_hit[i][Y] % (short)UNIT == 0)
			draw->color = data->map->h_wall;
		else if (rc->wall_hit[i][X] % (short)UNIT == UNIT - 1)
			draw->color = N;
		else if (rc->wall_hit[i][Y] % (short)UNIT == 0)
			draw->color = E;
		if (draw->color == E)
			rc->ray_status = Y;
	}
}

static void	select_texture_4(t_data *data, t_raycast *rc, t_draw *draw)
{
	short	i;

	i = rc->ray_index;
	if (rc->ray_angle < 360)
	{
		if (rc->wall_hit[i][X] % (short)UNIT == 0
			&& rc->wall_hit[i][Y] % (short)UNIT == 0)
			draw->color = data->map->h_wall;
		else if (rc->wall_hit[i][X] % (short)UNIT == 0)
			draw->color = S;
		else if (rc->wall_hit[i][Y] % (short)UNIT == 0)
			draw->color = E;
		if (draw->color == E)
			rc->ray_status = Y;
	}
}
