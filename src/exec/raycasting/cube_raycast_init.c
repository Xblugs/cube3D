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
	This file set initial values used in raycast depending on angle

	Angles that would result in undefined tan() values are skipped
	In rendering consider (0, 0) as previous value

	Functions are agenced this way to allow for static and norm compliance

	TODO: Change (0, 0) to (-1, -1) even if a corner MUST be a wall
		  better have a clean workflow to prevent potential errors
*/
void	raycast_init_wrapper(t_data *data, t_raycast *rc)
{
	rc->out[H] = 0;
	rc->out[V] = 0;
	if (fmod(rc->ray_angle, 90) == 0)
	{
		rc->ray_angle += data->calc->angle_between_rays;
		rc->ray_index++;
	}
	if (rc->ray_angle < 90)
		q1_init(data, rc);
	else if (rc->ray_angle < 180)
		q2_init(data, rc);
	else if (rc->ray_angle < 270)
		q3_init(data, rc);
	else if (rc->ray_angle < 360)
		q4_init(data, rc);
}

static void	q1_init(t_data *data, t_raycast *rc)
{
	(void) data;
	rc->alpha = tan(deg_to_rad(rc->ray_angle));
	rc->mov[H][X] = UNIT / rc->alpha;
	rc->mov[V][Y] = -rc->alpha * (UNIT);
	printf("mov[H][X]= %d\tmov[V][Y]= %d\n", rc->mov[H][X], rc->mov[V][Y]);
	rc->inter[H][Y] = ((rc->pos[Y] / UNIT) * UNIT) - 1;
	rc->inter[H][X] = ((rc->inter[H][Y] - rc->pos[Y]) / rc->alpha) + rc->pos[X];
	rc->inter[V][X] = ((rc->pos[X] / UNIT) * UNIT) + UNIT;
	rc->inter[V][Y] = rc->alpha * (rc->inter[V][X] - rc->pos[X]) + rc->pos[Y];
	printf("inter[H][X] = %d, inter[H][Y] = %d, inter[V][X] = %d, inter[V][Y] = %d\n\n",
		rc->inter[H][X], rc->inter[H][Y], rc->inter[V][X], rc->inter[V][Y]);
}

static void	q2_init(t_data *data, t_raycast *rc)
{
	(void) data;
	rc->alpha = tan(deg_to_rad(rc->ray_angle - 90));
	rc->mov[H][X] = -UNIT * rc->alpha;
	rc->mov[V][Y] = -UNIT / rc->alpha;
	rc->inter[H][Y] = ((rc->pos[Y] / UNIT) * UNIT) - 1;
	rc->inter[H][X] = rc->alpha * (rc->pos[Y] - rc->inter[H][Y]);
	rc->inter[V][X] = ((rc->pos[X] / UNIT) * UNIT) - 1;
	rc->inter[V][Y] = rc->pos[Y] - ((rc->pos[X] - rc->inter[V][X]) / rc->alpha);
}

static void	q3_init(t_data *data, t_raycast *rc)
{
	(void) data;
	rc->alpha = tan(deg_to_rad(rc->ray_angle - 180));
	rc->mov[H][X] = -UNIT * rc->alpha;
	rc->mov[V][Y] = UNIT * rc->alpha;
	rc->inter[H][Y] = ((rc->pos[Y] / UNIT) * UNIT) + UNIT;
	rc->inter[H][X] = rc->pos[X] - (rc->inter[H][Y] - rc->pos[Y]) / rc->alpha;
	rc->inter[V][X] = ((rc->pos[X] / UNIT) * UNIT) - 1;
	rc->inter[V][Y] = rc->alpha * (rc->pos[X] - rc->inter[V][X]) + rc->pos[Y];
}

static void	q4_init(t_data *data, t_raycast *rc)
{
	(void) data;
	rc->alpha = tan(deg_to_rad(rc->ray_angle - 270));
	rc->mov[H][X] = UNIT * rc->alpha;
	rc->mov[V][Y] = UNIT / rc->alpha;
	rc->inter[H][Y] = ((rc->pos[Y] / UNIT) * UNIT) + UNIT;
	rc->inter[H][X] = rc->pos[X] + rc->alpha * (rc->inter[H][Y] - rc->pos[Y]);
	rc->inter[V][X] = ((rc->pos[X] / UNIT) * UNIT) - UNIT;
	rc->inter[V][Y] = rc->pos[Y] + (rc->inter[V][X] - rc->pos[X]) / rc->alpha;
}
