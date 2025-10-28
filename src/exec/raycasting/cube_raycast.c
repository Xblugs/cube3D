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
	rc->ray_index = 0;
	rc->ray_angle = rc->view_angle - data->calc->half_fov;
	while (rc->ray_angle < rc->view_angle + data->calc->half_fov)
	{
		rc->out[H] = 0;
		rc->out[V] = 0;
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
	rc->mov[H][X] = UNIT / rc->alpha;
	rc->mov[V][Y] = -rc->alpha * (rc->mov[V][X]);
	rc->inter[H][X] = ((rc->inter[H][Y] - rc->pos[Y]) / rc->alpha) + rc->pos[X];
	rc->inter[H][Y] = ((rc->pos[Y] / UNIT) * UNIT) - 1;
	rc->inter[V][X] = ((rc->pos[X] / UNIT) * UNIT) + UNIT;
	rc->inter[V][Y] = rc->alpha * (rc->inter[V][X] - rc->pos[X]) + rc->pos[Y];
	while (!(rc->out[H] && rc->out[V]))
	{
		if (wall_hit(data, rc, data->map))
			break ;
		if (!rc->out[H])
		{
			rc->inter[H][X] += rc->mov[H][X];
			rc->inter[H][Y] += -UNIT;
		}
		if (!rc->out[V])
		{
			rc->inter[V][X] += UNIT;
			rc->inter[V][Y] += rc->mov[V][Y];
		}
	}
}

// (91 < ray_angle < 179)
static void	q2_raycast(t_data *data, t_raycast *rc)
{
	rc->alpha = tan(deg_to_rad(rc->ray_angle - 90));
	rc->mov[H][X] = -UNIT * rc->alpha;
	rc->mov[V][Y] = -UNIT / rc->alpha;
	rc->inter[H][Y] = ((rc->pos[Y] / UNIT) * UNIT) - 1;
	rc->inter[H][X] = rc->alpha * (rc->pos[Y] - rc->inter[H][Y]);
	rc->inter[V][X] = ((rc->pos[X] / UNIT) * UNIT) - 1;
	rc->inter[V][Y] = rc->pos[Y] - ((rc->pos[X] - rc->inter[V][X]) / rc->alpha);
	while (!(rc->out[H] && rc->out[V]))
	{
		if (wall_hit(data, rc, data->map))
			break ;
		if (!rc->out[H])
		{
			rc->inter[H][X] += rc->mov[H][X];
			rc->inter[H][Y] += -UNIT;
		}
		if (!rc->out[V])
		{
			rc->inter[V][X] += -UNIT;
			rc->inter[V][Y] += rc->mov[V][Y];
		}
	}
}

// (181 < ray_angle < 269)
static void	q3_raycast(t_data *data, t_raycast *rc)
{
	rc->alpha = tan(deg_to_rad(rc->ray_angle - 180));
	rc->mov[H][X] = -UNIT * rc->alpha;
	rc->mov[V][Y] = UNIT * rc->alpha;
	rc->inter[H][Y] = ((rc->pos[Y] / UNIT) * UNIT) + UNIT;
	rc->inter[H][X] = rc->pos[X] - (rc->inter[H][Y] - rc->pos[Y]) / rc->alpha;
	rc->inter[V][X] = ((rc->pos[X] / UNIT) * UNIT) - 1;
	rc->inter[V][Y] = rc->alpha * (rc->pos[X] - rc->inter[V][X]) + rc->pos[Y];
	while (!(rc->out[H] && rc->out[V]))
	{
		if (wall_hit(data, rc, data->map))
			break ;
		if (!rc->out[H])
		{
			rc->inter[H][X] += rc->mov[H][X];
			rc->inter[H][Y] += UNIT;
		}
		if (!rc->out[V])
		{
			rc->inter[V][X] += -UNIT;
			rc->inter[V][Y] += rc->mov[V][Y];
		}
	}
}

// (271 < ray_angle < 359)
static void	q4_raycast(t_data *data, t_raycast *rc)
{
	rc->alpha = tan(deg_to_rad(rc->ray_angle - 270));
	rc->mov[H][X] = UNIT * rc->alpha;
	rc->mov[V][Y] = UNIT / rc->alpha;
	rc->inter[H][Y] = ((rc->pos[Y] / UNIT) * UNIT) + UNIT;
	rc->inter[H][X] = rc->pos[X] + rc->alpha * (rc->inter[H][Y] - rc->pos[Y]);
	rc->inter[V][X] = ((rc->pos[X] / UNIT) * UNIT) - UNIT;
	rc->inter[V][Y] = rc->pos[Y] + (rc->inter[V][X] - rc->pos[X]) / rc->alpha;
	while (!(rc->out[H] && rc->out[V]))
	{
		if (wall_hit(data, rc, data->map))
			break ;
		if (!rc->out[H])
		{
			rc->inter[H][X] += rc->mov[H][X];
			rc->inter[H][Y] += UNIT;
		}
		if (!rc->out[V])
		{
			rc->inter[V][X] += UNIT;
			rc->inter[V][Y] += rc->mov[V][Y];
		}
	}
}

// quadrant template before changes
// static void	q4_raycast(type name, type name, ...)
// {
// 	const static int	mov[H][Y] = UNIT;
// 	const static int	mov[V][X] = UNIT;

// 	alpha = tan(deg_to_rad(ray_angle - 270));
// 	mov[H][X] = UNIT * alpha;
// 	mov[V][Y] = UNIT / alpha;
// 	inter[H][Y] = ((pos[Y] / UNIT) * UNIT) + UNIT;
// 	inter[H][X] = pos[X] + alpha * (inter[H][Y] - pos[Y]);
// 	inter[V][X] = ((pos[X] / UNIT) * UNIT) - UNIT;
// 	inter[V][Y] = pos[Y] + (inter[V][X] - pos[X]) / alpha;
// 	while (not out of scope)
// 	{
// 		inter[H][X] += mov[H][X];
// 		inter[H][Y] += mov[H][Y];
// 		inter[V][X] += mov[V][X];
// 		inter[V][Y] += mov[V][Y];
// 	}
// 	return (depend on wall hit but map is closed sooooooo);
// }