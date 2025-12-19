/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_rendering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:08:38 by cczerwin          #+#    #+#             */
/*   Updated: 2025/12/16 17:08:39 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	predraw_ceil(t_data *data, t_raycast *rc, t_draw *draw);
static void	predraw_floor(t_data *data, t_raycast *rc, t_draw *draw);

/*
	TODO: Delete color hardcode when merging with parsing
		+ move predraw_wall once texturing gets done
*/
void	render(t_data *data, t_raycast *rc)
{
	t_draw	draw;

	data->map->h_ceiling = C_CYAN;
	data->map->h_floor = C_BROWN;
	predraw_ceil(data, rc, &draw);
	draw_line(data->img, &draw);
	draw_texture(data, rc, &draw);
	predraw_floor(data, rc, &draw);
	draw_line(data->img, &draw);
}

/*
	Draw from top of the screen to wall

	fmod to add missing dot (i.e: 149 / 2 = 74 on each side, 1px is missing)
*/
static void	predraw_ceil(t_data *data, t_raycast *rc, t_draw *draw)
{
	draw->color = data->map->h_ceiling;
	draw->x[0] = rc->ray_index;
	draw->x[1] = rc->ray_index;
	draw->y[0] = 0;
	draw->y[1] = data->calc->half_height - (rc->wall_dist[rc->ray_index] / 2);
	if (fmod(rc->wall_dist[rc->ray_index], 2) != 0)
		draw->y[1]++;
}

/*
	Draw from last wall part to the bottom of the screen
*/
static void	predraw_floor(t_data *data, t_raycast *rc, t_draw *draw)
{
	(void) rc;
	draw->color = data->map->h_floor;
	draw->y[0] = draw->y[1];
	draw->y[1] = HEIGHT - 1;
}
