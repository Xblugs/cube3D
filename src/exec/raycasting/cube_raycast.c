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

static void	q1_raycast(type name, type name, ...);
static void	q2_raycast(type name, type name, ...);
static void	q3_raycast(type name, type name, ...);
static void	q4_raycast(type name, type name, ...);

void	raycast_wrapper(t_data *data)
{
	if (ray_angle % 90 == 0)
		ray_angle++;
	if (ray_angle < 90)
		q1_raycast(...);
	else if (ray_angle < 180)
		q2_raycast(...);
	else if (ray_angle < 270)
		q3_raycast(...);
	else if (ray_angle < 360)
		q4_raycast(...);
}

// (0 < ray_angle < 90)
// wrong formula, to be completed
static void	q1_raycast(type name, type name, ...)
{
	const static int	mov_h[Y] = -UNIT;
	const static int	mov_v[X] = UNIT;

	alpha = tan(deg_to_rad(ray_angle));
	mov_h[X] = UNIT / alpha;
	mov_v[Y] = -alpha * (mov_v[X]);
	inter_h[X] = ((inter_h[Y] - pos[Y]) / alpha) + pos[X];
	inter_h[Y] = ((pos[Y] / UNIT) * UNIT) - 1;
	inter_v[X] = ((pos[X] / UNIT) * UNIT) + UNIT;
	inter_v[Y] = alpha * (inter_v[X] - pos[X]) + pos[Y];
	while (not out of scope)
	{
		inter_h[X] += mov_h[X];
		inter_h[Y] += mov_h[Y];
		inter_v[X] += mov_v[X];
		inter_v[Y] += mov_v[Y];
	}
	return (depend on wall hit but map is closed sooooooo);
}

// (91 < ray_angle < 179)
static void	q2_raycast(type name, type name, ...)
{
	const static int	mov_h[Y] = -UNIT;
	const static int	mov_v[X] = -UNIT;

	alpha = tan(deg_to_rad(ray_angle - 90));
	mov_h[X] = -UNIT * alpha;
	mov_v[Y] = -UNIT / alpha;
	inter_h[Y] = ((pos[Y] / UNIT) * UNIT) - 1;
	inter_h[X] = alpha * (pos[Y] - inter_h[Y]);
	inter_v[X] = ((pos[X] / UNIT) * UNIT) - 1;
	inter_v[Y] = pos[Y] - ((pos[X] - inter_v[X]) / alpha);
	while (not out of scope)
	{
		inter_h[X] += mov_h[X];
		inter_h[Y] += mov_h[Y];
		inter_v[X] += mov_v[X];
		inter_v[Y] += mov_v[Y];
	}
	return (depend on wall hit but map is closed sooooooo);
}

// (181 < ray_angle < 269)
static void	q3_raycast(type name, type name, ...)
{
	const static int	mov_h[Y] = UNIT;
	const static int	mov_v[X] = -UNIT;

	alpha = tan(deg_to_rad(ray_angle - 180));
	mov_h[X] = -UNIT * alpha;
	mov_v[Y] = UNIT * alpha;
	inter_h[Y] = ((pos[Y] / UNIT) * UNIT) + UNIT;
	inter_h[X] = pos[X] - (inter_h.y - pos[Y]) / alpha;
	inter_v[X] = ((pos[X] / UNIT) * UNIT) - 1;
	inter_v[Y] = alpha * (pos[X] - inter_v[X]) + pos[Y];
	while (not out of scope)
	{
		inter_h[X] += mov_h[X];
		inter_h[Y] += mov_h[Y];
		inter_v[X] += mov_v[X];
		inter_v[Y] += mov_v[Y];
	}
	return (depend on wall hit but map is closed sooooooo);
}

// (271 < ray_angle < 359)
static void	q4_raycast(type name, type name, ...)
{
	const static int	mov_h[Y] = UNIT;
	const static int	mov_v[X] = UNIT;

	alpha = tan(deg_to_rad(ray_angle - 270));
	mov_h[X] = UNIT * alpha;
	mov_v[Y] = UNIT / alpha;
	inter_h[Y] = ((pos[Y] / UNIT) * UNIT) + UNIT;
	inter_h[X] = pos[X] + alpha * (inter_h[Y] - pos[Y]);
	inter_v[X] = ((pos[X] / UNIT) * UNIT) - UNIT;
	inter_v[Y] = pos[Y] + (inter_v[X] - pos[X]) / alpha;
	while (not out of scope)
	{
		inter_h[X] += mov_h[X];
		inter_h[Y] += mov_h[Y];
		inter_v[X] += mov_v[X];
		inter_v[Y] += mov_v[Y];
	}
	return (depend on wall hit but map is closed sooooooo);
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