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
static void	predraw_wall(t_data *data, t_raycast *rc, t_draw *draw);
static void	predraw_floor(t_data *data, t_raycast *rc, t_draw *draw);

/*
	TODO: Delete color hardcode when merging with parsing
*/
void	render(t_data *data, t_raycast *rc)
{
	t_draw	draw;

	data->map->h_ceiling = C_CYAN;
	data->map->h_floor = C_BROWN;
	predraw_ceil(data, rc, &draw);
	draw_line(data->img, &draw);
	draw_texture(data, rc, &draw);
	predraw_wall(data, rc, &draw);
	draw_line(data->img, &draw);
	predraw_floor(data, rc, &draw);
	draw_line(data->img, &draw);
}

// prepare to draw ceiling
static void	predraw_ceil(t_data *data, t_raycast *rc, t_draw *draw)
{
	draw->color = data->map->h_ceiling;
	draw->x[0] = rc->ray_index;
	draw->x[1] = rc->ray_index;
	draw->y[0] = 0;
	draw->y[1] = data->calc->half_height - (rc->wall_dist[rc->ray_index] / 2);
}

// prepare to draw walls
static void	predraw_wall(t_data *data, t_raycast *rc, t_draw *draw)
{
	draw->y[0] = draw->y[1];
	draw->y[1] = data->calc->half_height + (rc->wall_dist[rc->ray_index] / 2);
}

// prepare to draw floor
static void	predraw_floor(t_data *data, t_raycast *rc, t_draw *draw)
{
	(void) rc;
	draw->color = data->map->h_floor;
	draw->y[0] = draw->y[1];
	draw->y[1] = HEIGHT - 1;
}
