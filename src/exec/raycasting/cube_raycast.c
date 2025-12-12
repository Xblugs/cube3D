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
static void	test_render(t_data *data, t_raycast *rc);
static void	test_predraw(t_data *data, t_raycast *rc, t_draw *draw);

/*
	Raycast is calculated depending on its angle
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
		// here correct wall hit to be the exact pixel
		test_render(data, rc);
		rc->ray_angle += data->calc->angle_between_rays;
		rc->ray_index++;
	}
	mlx_pitow(data->mlx, data->win, data->img->img, 0);
}

// ray_status is [TRUE] once the ray is [OUT] or [HIT] a wall
static void	raycast(t_data *data, t_raycast *rc)
{
	while (!(rc->ray_status))
	{
		ray_status_check_wrapper(data, rc);
		if (!rc->ray_status)
		{
			rc->ray[X] += rc->delta[X];
			rc->ray[Y] += rc->delta[Y];
		}
	}
	wall_hit(data, rc);
}

// calc distance, resulting projection and correction for fisheye lens effect
// TODO: move this to its own file, eventually separate it into multiple func?
// 	distance calculation could be optimized, sqrt and pow are cpu expensive
static void	test_render(t_data *data, t_raycast *rc)
{
	t_draw	draw;

	(void) data;
	rc->wall_dist[rc->ray_index] = sqrt(pow(rc->pos[X]
				- rc->wall_hit[rc->ray_index][X], 2)
			+ pow(rc->pos[Y] - rc->wall_hit[rc->ray_index][Y], 2));
	rc->wall_dist[rc->ray_index] = ((float) UNIT / rc->wall_dist[rc->ray_index])
		* data->calc->dist_to_proj;
	rc->wall_dist[rc->ray_index] /= cos(deg_to_rad(
				rc->ray_angle - rc->view_angle));

	// map->h_ceiling
	draw.color = C_CYAN;
	test_predraw(data, rc, &draw);
	draw_line(data->img, &draw);

	// walls
	draw.color = C_PURPLE;
	test_predraw(data, rc, &draw);
	draw_line(data->img, &draw);

	// map->h_floor
	draw.color = C_BROWN;
	test_predraw(data, rc, &draw);
	draw_line(data->img, &draw);
}

static void	test_predraw(t_data *data, t_raycast *rc, t_draw *draw)
{
	draw->x[0] = (WIDTH - 1) - rc->ray_index;
	draw->x[1] = (WIDTH - 1) - rc->ray_index;
	if (draw->color == C_CYAN)
	{
		draw->y[0] = 0;
		draw->y[1] = data->calc->half_height - (rc->wall_dist[rc->ray_index] / 2);
	}
	else if (draw->color == C_PURPLE)
	{
		draw->y[0] = draw->y[1];
		draw->y[1] = data->calc->half_height + (rc->wall_dist[rc->ray_index] / 2);
	}
	else if (draw->color == C_BROWN)
	{
		draw->y[0] = draw->y[1];
		draw->y[1] = HEIGHT - 1;
	}
}
