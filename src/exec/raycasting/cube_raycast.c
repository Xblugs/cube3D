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
static void	distance_calc(t_data *data, t_raycast *rc);
static void	distance_correction(t_data *data, t_raycast *rc);

/*
	Reset various indexes and flag before proceeding to actual raycast
*/
void	raycast_wrapper(t_data *data, t_raycast *rc)
{
	rc->ray_index = 0;
	rc->ray_angle = rc->view_angle - data->calc->half_fov;
	ft_memset(data->rc->wall_hit, 0, WIDTH * 2 * sizeof(short));
	ft_memset(data->rc->wall_dist, 0, WIDTH * sizeof(double));
	while (rc->ray_index != WIDTH)
	{
		raycast_init_wrapper(data, rc);
		raycast(data, rc);
		rc->ray_angle += data->calc->angle_between_rays;
		rc->ray_index++;
	}
	mlx_pitow(data->mlx, data->win, data->img->img, 0);
}

/*
	ray_status is [TRUE] once the ray is [OUT] or [HIT] a wall
*/
static void	raycast(t_data *data, t_raycast *rc)
{
	while (!(rc->ray_status))
	{
		ray_status_check_wrapper(data, rc);
		if (!rc->ray_status)
			rc->ray[X] += rc->delta[X];
		ray_status_check_wrapper(data, rc);
		if (!rc->ray_status)
			rc->ray[Y] += rc->delta[Y];
	}
	wall_hit(data, rc);
	distance_calc(data, rc);
	distance_correction(data, rc);
	render(data, rc);
}

/*
	Calculating distance to wall
*/
static void	distance_calc(t_data *data, t_raycast *rc)
{
	short	i;

	i = rc->ray_index;
	if (rc->wall_hit[i][X] != 0 || rc->wall_hit[i][Y] != 0)
	{
		rc->wall_dist[i] = sqrt(pow(rc->pos[Y] - rc->wall_hit[i][X], 2)
				+ pow(rc->pos[X] - rc->wall_hit[i][Y], 2));
		rc->wall_dist[i] = ((double) UNIT / (double) rc->wall_dist[i])
			* data->calc->dist_to_proj;
	}
}

/*
	Correction for fisheye lens effect
	Can be disabled for maximum FOV experience
*/
static void	distance_correction(t_data *data, t_raycast *rc)
{
	short	i;

	(void) data;
	i = rc->ray_index;
	if (rc->wall_hit[i][X] != 0 || rc->wall_hit[i][Y] != 0)
		rc->wall_dist[i] /= cos(deg_to_rad(rc->ray_angle - rc->view_angle));
}
