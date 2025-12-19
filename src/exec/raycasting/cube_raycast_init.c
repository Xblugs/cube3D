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

/*
	Set ray status and increment value for each step
*/
void	raycast_init_wrapper(t_data *data, t_raycast *rc)
{
	(void) data;
	rc->ray_status = CASTING;
	rc->ray[X] = rc->pos[X];
	rc->ray[Y] = rc->pos[Y];
	if (rc->ray_angle >= 360)
		rc->ray_angle -= 360;
	else if (rc->ray_angle < 0)
		rc->ray_angle += 360;
	rc->delta[X] = -sin(deg_to_rad(rc->ray_angle));
	rc->delta[Y] = +cos(deg_to_rad(rc->ray_angle));
}
