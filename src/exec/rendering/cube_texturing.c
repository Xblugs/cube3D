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

static void	prepare_texture(t_data *data, t_img *img, t_draw *d, float *ratio);
static void	scale_to_ratio(t_img *i, int *count, float *ratio, float *leftover);
static void	predraw_wall(t_draw *draw, t_img *img, int px_count);

/*
	Wall rendering wrapper

	Drawing texture is the most expensive operation in all cube3D
*/
void	draw_texture(t_data *data, t_raycast *rc, t_draw *draw)
{
	short	y_max;
	int		count;
	float	ratio;
	float	leftover;
	t_img	img;

	select_texture_wrapper(data, rc, draw);
	prepare_texture(data, &img, draw, &ratio);
	count = 0;
	leftover = 0;
	y_max = data->calc->half_height + (rc->wall_dist[rc->ray_index] / 2);
	while (draw->y[1] != y_max)
	{
		scale_to_ratio(&img, &count, &ratio, &leftover);
		if (draw->y[1] + floor(ratio) + count >= y_max)
			predraw_wall(draw, &img, y_max - draw->y[1]);
		else
			predraw_wall(draw, &img, ratio + count);
		draw_line(data->img, draw);
	}
}

/*
	Init img values, separated for norm compliance
*/
static void	prepare_texture(t_data *data, t_img *img, t_draw *d, float *ratio)
{
	int	side;

	side = d->color;
	*ratio = data->rc->wall_dist[data->rc->ray_index] / data->tex->h[side];
	img->y = -1;
	img->x = data->rc->wall_hit[data->rc->ray_index][Y] % UNIT;
	if (data->rc->ray_status == Y)
		img->x = data->rc->wall_hit[data->rc->ray_index][X] % UNIT;
	img->addr = mlx_get_data_addr(data->tex->img[side], &img->bpp,
			&img->line_len, &img->endian);
	img->x *= (img->bpp / 8);
}

/*
	How many pixel on screen need to be filled per one pixel of texture
		+ leftovers for non-int ratio values to be taken in account
*/
static void	scale_to_ratio(t_img *i, int *count, float *ratio, float *leftover)
{
	*leftover += *ratio - floor(*ratio);
	*count = 0;
	i->y++;
	if (*leftover >= 1)
	{
		(*count)++;
		*leftover -= 1;
	}
	else if (*leftover <= -1)
	{
		(*count)--;
		*leftover += 1;
	}
}

/*
	Draw wall in-between

	img->addr + (img->y * img->line_len + img->x * (img->bpp / 8))
		(img->bpp / 8) is precalculated (constant in our case)
*/
static void	predraw_wall(t_draw *draw, t_img *img, int px_count)
{
	char	*cursor;

	cursor = img->addr + (img->y * img->line_len + img->x);
	draw->color = *(unsigned int *)cursor;
	draw->y[0] = draw->y[1];
	draw->y[1] += px_count;
}
