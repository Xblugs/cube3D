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

static void	q1_raycast(t_data *data, t_raycast *rc);
static void	q2_raycast(t_data *data, t_raycast *rc);
static void	q3_raycast(t_data *data, t_raycast *rc);
static void	q4_raycast(t_data *data, t_raycast *rc);

void	raycast_wrapper(t_data *data)
{
	if (ray_angle % 90 == 0)
		ray_angle++;
	if (ray_angle < 90)
		q1_raycast(data, data->rc);
	else if (ray_angle < 180)
		q2_raycast(data, data->rc);
	else if (ray_angle < 270)
		q3_raycast(data, data->rc);
	else if (ray_angle < 360)
		q4_raycast(data, data->rc);
}

// (0 < ray_angle < 90)
// wrong formula, to be completed
static void	q1_raycast(t_data *data, t_raycast *rc)
{
	rc->alpha = tan(deg_to_rad(ray_angle));
	rc->mov_h[X] = UNIT / rc->alpha;
	rc->mov_v[Y] = -rc->alpha * (rc->mov_v[X]);
	rc->inter_h[X] = ((rc->inter_h[Y] - rc->pos[Y]) / rc->alpha) + rc->pos[X];
	rc->inter_h[Y] = ((rc->pos[Y] / UNIT) * UNIT) - 1;
	rc->inter_v[X] = ((rc->pos[X] / UNIT) * UNIT) + UNIT;
	rc->inter_v[Y] = rc->alpha * (rc->inter_v[X] - rc->pos[X]) + rc->pos[Y];
	while (is_in_scope(rc->inter_h, rc->inter_v))
	{
		rc->inter_h[X] += rc->mov_h[X];
		rc->inter_h[Y] += -UNIT;
		rc->inter_v[X] += UNIT;
		rc->inter_v[Y] += rc->mov_v[Y];
	}
	return ();
}

// (91 < ray_angle < 179)
static void	q2_raycast(t_data *data, t_raycast *rc)
{
	rc->alpha = tan(deg_to_rad(ray_angle - 90));
	rc->mov_h[X] = -UNIT * rc->alpha;
	rc->mov_v[Y] = -UNIT / rc->alpha;
	rc->inter_h[Y] = ((rc->pos[Y] / UNIT) * UNIT) - 1;
	rc->inter_h[X] = rc->alpha * (rc->pos[Y] - rc->inter_h[Y]);
	rc->inter_v[X] = ((rc->pos[X] / UNIT) * UNIT) - 1;
	rc->inter_v[Y] = rc->pos[Y] - ((rc->pos[X] - rc->inter_v[X]) / rc->alpha);
	while (is_in_scope(rc->inter_h, rc->inter_v))
	{
		rc->inter_h[X] += rc->mov_h[X];
		rc->inter_h[Y] += -UNIT;
		rc->inter_v[X] += -UNIT;
		rc->inter_v[Y] += rc->mov_v[Y];
	}
	return ();
}

// (181 < ray_angle < 269)
static void	q3_raycast(t_data *data, t_raycast *rc)
{
	rc->alpha = tan(deg_to_rad(ray_angle - 180));
	rc->mov_h[X] = -UNIT * rc->alpha;
	rc->mov_v[Y] = UNIT * rc->alpha;
	rc->inter_h[Y] = ((rc->pos[Y] / UNIT) * UNIT) + UNIT;
	rc->inter_h[X] = rc->pos[X] - (rc->inter_h[Y] - rc->pos[Y]) / rc->alpha;
	rc->inter_v[X] = ((rc->pos[X] / UNIT) * UNIT) - 1;
	rc->inter_v[Y] = rc->alpha * (rc->pos[X] - rc->inter_v[X]) + rc->pos[Y];
	while (is_in_scope(rc->inter_h, rc->inter_v))
	{
		rc->inter_h[X] += rc->mov_h[X];
		rc->inter_h[Y] += UNIT;
		rc->inter_v[X] += -UNIT;
		rc->inter_v[Y] += rc->mov_v[Y];
	}
	return ();
}

// (271 < ray_angle < 359)
static void	q4_raycast(t_data *data, t_raycast *rc)
{
	rc->alpha = tan(deg_to_rad(ray_angle - 270));
	rc->mov_h[X] = UNIT * rc->alpha;
	rc->mov_v[Y] = UNIT / rc->alpha;
	rc->inter_h[Y] = ((rc->pos[Y] / UNIT) * UNIT) + UNIT;
	rc->inter_h[X] = rc->pos[X] + rc->alpha * (rc->inter_h[Y] - rc->pos[Y]);
	rc->inter_v[X] = ((rc->pos[X] / UNIT) * UNIT) - UNIT;
	rc->inter_v[Y] = rc->pos[Y] + (rc->inter_v[X] - rc->pos[X]) / rc->alpha;
	while (is_in_scope(rc->inter_h, rc->inter_v))
	{
		rc->inter_h[X] += rc->mov_h[X];
		rc->inter_h[Y] += UNIT;
		rc->inter_v[X] += UNIT;
		rc->inter_v[Y] += rc->mov_v[Y];
	}
	return ();
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