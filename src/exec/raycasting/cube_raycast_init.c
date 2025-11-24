/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_raycast_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:54:55 by cczerwin          #+#    #+#             */
/*   Updated: 2025/10/29 12:54:56 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	q1_init(t_data *data, t_raycast *rc);
static void	q2_init(t_data *data, t_raycast *rc);
static void	q3_init(t_data *data, t_raycast *rc);
static void	q4_init(t_data *data, t_raycast *rc);

/*
	This file mostly implement [math.md] formulas for raycasting
		(set initial values used in raycast depending on angle/quadrant)

	Angles that would result in undefined tan() values are skipped
	In rendering consider (0, 0) as previous value as one index is also skipped

	Functions are agenced this way to allow for static and norm compliance

	TODO: Change (0, 0) to (-1, -1) even if a corner MUST be a wall
		  better have a clean workflow to prevent potential errors
*/
void	raycast_init_wrapper(t_data *data, t_raycast *rc)
{
	rc->ray_status[H] = CASTING;
	rc->ray_status[V] = CASTING;
	if (fmod(rc->ray_angle, 90) == 0)
		rc->ray_angle += data->calc->angle_between_rays;
	if (rc->ray_angle < 90)
		q1_init(data, rc);
	else if (rc->ray_angle < 180)
		q2_init(data, rc);
	else if (rc->ray_angle < 270)
		q3_init(data, rc);
	else if (rc->ray_angle < 360)
		q4_init(data, rc);
}

// (0 < ray_angle < 90)
static void	q1_init(t_data *data, t_raycast *rc)
{
	(void) data;
	rc->alpha = tan(deg_to_rad(rc->ray_angle));
	rc->mov[H][X] = UNIT / rc->alpha;
	rc->mov[H][Y] = -UNIT;
	rc->mov[V][X] = UNIT;
	rc->mov[V][Y] = -rc->alpha * (UNIT);
	rc->inter[H][Y] = ((rc->pos[Y] / UNIT) * UNIT) - 1;
	rc->inter[H][X] = ((rc->inter[H][Y] - rc->pos[Y]) / rc->alpha) + rc->pos[X];
	rc->inter[V][X] = ((rc->pos[X] / UNIT) * UNIT) + UNIT;
	rc->inter[V][Y] = rc->alpha * (rc->inter[V][X] - rc->pos[X]) + rc->pos[Y];
}

// (91 < ray_angle < 179)
static void	q2_init(t_data *data, t_raycast *rc)
{
	(void) data;
	rc->alpha = tan(deg_to_rad(rc->ray_angle - 90));
	rc->mov[H][X] = -UNIT * rc->alpha;
	rc->mov[H][Y] = -UNIT;
	rc->mov[V][X] = -UNIT;
	rc->mov[V][Y] = -UNIT / rc->alpha;
	rc->inter[H][Y] = ((rc->pos[Y] / UNIT) * UNIT) - 1;
	rc->inter[H][X] = rc->alpha * (rc->pos[Y] - rc->inter[H][Y]);
	rc->inter[V][X] = ((rc->pos[X] / UNIT) * UNIT) - 1;
	rc->inter[V][Y] = rc->pos[Y] - ((rc->pos[X] - rc->inter[V][X]) / rc->alpha);
}

// (181 < ray_angle < 269)
static void	q3_init(t_data *data, t_raycast *rc)
{
	(void) data;
	rc->alpha = tan(deg_to_rad(rc->ray_angle - 180));
	rc->mov[H][X] = -UNIT * rc->alpha;
	rc->mov[H][Y] = UNIT;
	rc->mov[V][X] = -UNIT;
	rc->mov[V][Y] = UNIT * rc->alpha;
	rc->inter[H][Y] = ((rc->pos[Y] / UNIT) * UNIT) + UNIT;
	rc->inter[H][X] = rc->pos[X] - (rc->inter[H][Y] - rc->pos[Y]) / rc->alpha;
	rc->inter[V][X] = ((rc->pos[X] / UNIT) * UNIT) - 1;
	rc->inter[V][Y] = rc->alpha * (rc->pos[X] - rc->inter[V][X]) + rc->pos[Y];
}

// (271 < ray_angle < 359)
static void	q4_init(t_data *data, t_raycast *rc)
{
	(void) data;
	rc->alpha = tan(deg_to_rad(rc->ray_angle - 270));
	rc->mov[H][X] = UNIT * rc->alpha;
	rc->mov[H][Y] = UNIT;
	rc->mov[V][X] = UNIT;
	rc->mov[V][Y] = UNIT / rc->alpha;
	rc->inter[H][Y] = ((rc->pos[Y] / UNIT) * UNIT) + UNIT;
	rc->inter[H][X] = rc->pos[X] + rc->alpha * (rc->inter[H][Y] - rc->pos[Y]);
	rc->inter[V][X] = ((rc->pos[X] / UNIT) * UNIT) - UNIT;
	rc->inter[V][Y] = rc->pos[Y] + (rc->inter[V][X] - rc->pos[X]) / rc->alpha;
}

// quadrant template before changes (concept)
// static void	q4_raycast(type name, type name, ...)
// {
// 	const static int	mov[H][Y] = UNIT;	// note: compiler doesn't like this
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
// 	return (depend on wall hit but map is closed so we will hit);
// }