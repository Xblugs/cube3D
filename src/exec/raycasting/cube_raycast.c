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

static void	raycast(t_data *data, t_raycast *rc);

/*
	Raycast is calculated depending on its angle
*/
void	raycast_wrapper(t_data *data, t_raycast *rc)
{
	rc->ray_index = 0;
	rc->ray_angle = rc->view_angle - data->calc->half_fov;
	while (rc->ray_angle < rc->view_angle + data->calc->half_fov)
	{
		raycast_init_wrapper(data, rc);
		raycast(data, rc);
		rc->ray_angle += data->calc->angle_between_rays;
	}
}

// ray_status is [TRUE] once the ray is [OUT] or [HIT] a wall
static void	raycast(t_data *data, t_raycast *rc)
{
	while (!(rc->ray_status[H] && rc->ray_status[V]))
	{
		ray_status_check_wrapper(data, rc);
		if (!rc->ray_status[H])
		{
			rc->inter[H][X] += rc->mov[H][X];
			rc->inter[H][Y] += rc->mov[H][Y];
		}
		if (!rc->ray_status[V])
		{
			rc->inter[V][X] += rc->mov[V][X];
			rc->inter[V][Y] += rc->mov[V][Y];
		}
	}
	wall_hit(data, rc);
}

// quadrant template before changes
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
// 	return (depend on wall hit but map is closed sooooooo);
// }