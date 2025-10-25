/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 13:41:49 by cczerwin          #+#    #+#             */
/*   Updated: 2025/10/25 13:41:52 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*
	This file mostly implement [math.md] formulas for quadrant raycasting
*/

static void	q1_raycast(t_data *data, t_raycast *rc);
static void	q2_raycast(t_data *data, t_raycast *rc);
static void	q3_raycast(t_data *data, t_raycast *rc);
static void	q4_raycast(t_data *data, t_raycast *rc);

void	raycast_wrapper(t_data *data, t_raycast *rc)
{
	rc->ray_angle = rc->view_angle - data->calc->half_fov;
	while (rc->ray_angle < rc->view_angle + data->calc->half_fov)
	{
		rc->out_h = 0;
		rc->out_v = 0;
		if (fmod(rc->ray_angle, 90) == 0)
			rc->ray_angle += data->calc->angle_between_rays;
		if (rc->ray_angle < 90)
			q1_raycast(data, rc);
		else if (rc->ray_angle < 180)
			q2_raycast(data, rc);
		else if (rc->ray_angle < 270)
			q3_raycast(data, rc);
		else if (rc->ray_angle < 360)
			q4_raycast(data, rc);
		rc->ray_angle += data->calc->angle_between_rays;
	}
}

// (0 < ray_angle < 90)
static void	q1_raycast(t_data *data, t_raycast *rc)
{
	rc->alpha = tan(deg_to_rad(rc->ray_angle));
	rc->mov_h[X] = UNIT / rc->alpha;
	rc->mov_v[Y] = -rc->alpha * (rc->mov_v[X]);
	rc->inter_h[X] = ((rc->inter_h[Y] - rc->pos[Y]) / rc->alpha) + rc->pos[X];
	rc->inter_h[Y] = ((rc->pos[Y] / UNIT) * UNIT) - 1;
	rc->inter_v[X] = ((rc->pos[X] / UNIT) * UNIT) + UNIT;
	rc->inter_v[Y] = rc->alpha * (rc->inter_v[X] - rc->pos[X]) + rc->pos[Y];
	while (!(rc->out_h && rc->out_v))
	{
		if (wall_hit(rc, data->map))
			break ;
		if (!rc->out_h)
		{
			rc->inter_h[X] += rc->mov_h[X];
			rc->inter_h[Y] += -UNIT;
		}
		if (!rc->out_v)
		{
			rc->inter_v[X] += UNIT;
			rc->inter_v[Y] += rc->mov_v[Y];
		}
		scope_check(rc, rc->inter_h, rc->inter_v);
	}
}

// (91 < ray_angle < 179)
static void	q2_raycast(t_data *data, t_raycast *rc)
{
	rc->alpha = tan(deg_to_rad(rc->ray_angle - 90));
	rc->mov_h[X] = -UNIT * rc->alpha;
	rc->mov_v[Y] = -UNIT / rc->alpha;
	rc->inter_h[Y] = ((rc->pos[Y] / UNIT) * UNIT) - 1;
	rc->inter_h[X] = rc->alpha * (rc->pos[Y] - rc->inter_h[Y]);
	rc->inter_v[X] = ((rc->pos[X] / UNIT) * UNIT) - 1;
	rc->inter_v[Y] = rc->pos[Y] - ((rc->pos[X] - rc->inter_v[X]) / rc->alpha);
	while (!(rc->out_h && rc->out_v))
	{
		if (wall_hit(rc, data->map))
			break ;
		if (!rc->out_h)
		{
			rc->inter_h[X] += rc->mov_h[X];
			rc->inter_h[Y] += -UNIT;
		}
		if (!rc->out_v)
		{
			rc->inter_v[X] += -UNIT;
			rc->inter_v[Y] += rc->mov_v[Y];
		}
		scope_check(rc, rc->inter_h, rc->inter_v);
	}
}

// (181 < ray_angle < 269)
static void	q3_raycast(t_data *data, t_raycast *rc)
{
	rc->alpha = tan(deg_to_rad(rc->ray_angle - 180));
	rc->mov_h[X] = -UNIT * rc->alpha;
	rc->mov_v[Y] = UNIT * rc->alpha;
	rc->inter_h[Y] = ((rc->pos[Y] / UNIT) * UNIT) + UNIT;
	rc->inter_h[X] = rc->pos[X] - (rc->inter_h[Y] - rc->pos[Y]) / rc->alpha;
	rc->inter_v[X] = ((rc->pos[X] / UNIT) * UNIT) - 1;
	rc->inter_v[Y] = rc->alpha * (rc->pos[X] - rc->inter_v[X]) + rc->pos[Y];
	while (!(rc->out_h && rc->out_v))
	{
		if (wall_hit(rc, data->map))
			break ;
		if (!rc->out_h)
		{
			rc->inter_h[X] += rc->mov_h[X];
			rc->inter_h[Y] += UNIT;
		}
		if (!rc->out_v)
		{
			rc->inter_v[X] += -UNIT;
			rc->inter_v[Y] += rc->mov_v[Y];
		}
		scope_check(rc, rc->inter_h, rc->inter_v);
	}
}

// (271 < ray_angle < 359)
static void	q4_raycast(t_data *data, t_raycast *rc)
{
	rc->alpha = tan(deg_to_rad(rc->ray_angle - 270));
	rc->mov_h[X] = UNIT * rc->alpha;
	rc->mov_v[Y] = UNIT / rc->alpha;
	rc->inter_h[Y] = ((rc->pos[Y] / UNIT) * UNIT) + UNIT;
	rc->inter_h[X] = rc->pos[X] + rc->alpha * (rc->inter_h[Y] - rc->pos[Y]);
	rc->inter_v[X] = ((rc->pos[X] / UNIT) * UNIT) - UNIT;
	rc->inter_v[Y] = rc->pos[Y] + (rc->inter_v[X] - rc->pos[X]) / rc->alpha;
	while (!(rc->out_h && rc->out_v))
	{
		if (wall_hit(rc, data->map))
			break ;
		if (!rc->out_h)
		{
			rc->inter_h[X] += rc->mov_h[X];
			rc->inter_h[Y] += UNIT;
		}
		if (!rc->out_v)
		{
			rc->inter_v[X] += UNIT;
			rc->inter_v[Y] += rc->mov_v[Y];
		}
		scope_check(rc, rc->inter_h, rc->inter_v);
	}
}

// quadrant template before changes
// static void	q4_raycast(type name, type name, ...)
// {
// 	const static int	mov_h[Y] = UNIT;
// 	const static int	mov_v[X] = UNIT;

// 	alpha = tan(deg_to_rad(ray_angle - 270));
// 	mov_h[X] = UNIT * alpha;
// 	mov_v[Y] = UNIT / alpha;
// 	inter_h[Y] = ((pos[Y] / UNIT) * UNIT) + UNIT;
// 	inter_h[X] = pos[X] + alpha * (inter_h[Y] - pos[Y]);
// 	inter_v[X] = ((pos[X] / UNIT) * UNIT) - UNIT;
// 	inter_v[Y] = pos[Y] + (inter_v[X] - pos[X]) / alpha;
// 	while (not out of scope)
// 	{
// 		inter_h[X] += mov_h[X];
// 		inter_h[Y] += mov_h[Y];
// 		inter_v[X] += mov_v[X];
// 		inter_v[Y] += mov_v[Y];
// 	}
// 	return (depend on wall hit but map is closed sooooooo);
// }