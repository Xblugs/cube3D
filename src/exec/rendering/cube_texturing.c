/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_texturing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:22:19 by cczerwin          #+#    #+#             */
/*   Updated: 2025/12/16 18:22:20 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	prepare_texture(t_data *data, t_raycast *rc, t_img *img, int side);
static void	scale_to_ratio(t_img *i, int *count, float *ratio, float *leftover);
static void	predraw_wall(t_data *data, t_raycast *rc, t_draw *draw, t_img *img);

/*
	Wall rendering wrapper

	This function was butchered to fit norminette
	TODO: Beautify this thing
	f[0] = ratio texture to wall size
	f[1] = leftover (drawing on integer but ratio is a float)
*/
void	draw_texture(t_data *data, t_raycast *rc, t_draw *draw)
{
	short	y_max;
	int		side;
	int		count;
	float	f[2];
	t_img	img;

	select_texture_wrapper(data, rc, draw);
	side = draw->color;
	prepare_texture(data, rc, &img, side);
	count = 0;
	f[1] = 0;
	f[0] = rc->wall_dist[rc->ray_index] / UNIT;
	y_max = data->calc->half_height + (rc->wall_dist[rc->ray_index] / 2);
	while (draw->y[1] != y_max)
	{
		predraw_wall(data, rc, draw, &img);
		draw_line(data->img, draw);
		scale_to_ratio(&img, &count, &f[0], &f[1]);
	}
}

/*
	Init img values, separated for norm compliance
*/
static void	prepare_texture(t_data *data, t_raycast *rc, t_img *img, int side)
{
	img->y = 0;
	img->x = rc->wall_hit[rc->ray_index][Y] % UNIT;
	if (rc->ray_status == Y)
		img->x = rc->wall_hit[rc->ray_index][X] % UNIT;
	img->addr = mlx_get_data_addr(data->tex->img[side], &img->bpp,
			&img->line_len, &img->endian);
}

static void	scale_to_ratio(t_img *i, int *count, float *ratio, float *leftover)
{
	(*count)++;
	if (*count >= *ratio)
	{
		*leftover += *ratio - *count;
		*count = 0;
		i->y++;
		if (*leftover >= 1)
		{
			(*count)--;
			*leftover -= 1;
		}
		else if (*leftover <= -1)
		{
			(*count)++;
			*leftover += 1;
		}
	}
}

/*
	Draw wall in-between
*/
static void	predraw_wall(t_data *data, t_raycast *rc, t_draw *draw, t_img *img)
{
	char	*cursor;

	(void) data;
	(void) rc;
	cursor = img->addr + (img->y * img->line_len + img->x * (img->bpp / 8));
	draw->color = *(unsigned int *)cursor;
	draw->y[0] = draw->y[1];
	draw->y[1] += 1;
}
