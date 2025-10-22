/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_draw_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:47:40 by cczerwin          #+#    #+#             */
/*   Updated: 2025/10/15 10:47:42 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	draw_low(t_img *img, t_draw draw);
static void	draw_high(t_img *img, t_draw draw);
static void	invert_coordinates(t_draw *draw);

// function to draw lines from FdF
void	draw_line(t_img *img, t_draw *draw)
{
	if (abs_val(draw->y[1] - draw->y[0]) < abs_val(draw->x[1] - draw->x[0]))
	{
		if (draw->x[0] > draw->x[1])
		{
			invert_coordinates(draw);
			draw_low(img, *draw);
			invert_coordinates(draw);
		}
		else
			draw_low(img, *draw);
	}
	else
	{
		if (draw->y[0] > draw->y[1])
		{
			invert_coordinates(draw);
			draw_high(img, *draw);
			invert_coordinates(draw);
		}
		else
			draw_high(img, *draw);
	}
}

// x[3] = {x0 x1 dx} = {start end (end - start)}
static void	draw_low(t_img *img, t_draw draw)
{
	int	d;
	int	yi;

	yi = 1;
	if (draw.y[2] < 0)
	{
		yi = -1;
		draw.y[2] = -draw.y[2];
	}
	d = (2 * draw.y[2]) - draw.x[2];
	while (draw.x[0] != draw.x[1])
	{
		pixel_put(img, draw.x[0], draw.y[0], draw.color);
		if (d > 0)
		{
			draw.y[0] = draw.y[0] + yi;
			d = d + (2 * (draw.y[2] - draw.x[2]));
		}
		else
			d = d + 2 * draw.y[2];
		draw.x[0]++;
	}
}

static void	draw_high(t_img *img, t_draw draw)
{
	int	d;
	int	xi;

	xi = 1;
	if (draw.x[2] < 0)
	{
		xi = -1;
		draw.x[2] = -draw.x[2];
	}
	d = (2 * draw.x[2]) - draw.y[2];
	while (draw.y[0] != draw.y[1])
	{
		pixel_put(img, draw.x[0], draw.y[0], draw.color);
		if (d > 0)
		{
			draw.x[0] = draw.x[0] + xi;
			d = d + (2 * (draw.x[2] - draw.y[2]));
		}
		else
			d = d + 2 * draw.x[2];
		draw.y[0]++;
	}
}

// put pixel except if we're outside the window to prevent crashing
void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->x || y >= img->y)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	invert_coordinates(t_draw *draw)
{
	int	swap;

	swap = draw->x[0];
	draw->x[0] = draw->x[1];
	draw->x[1] = swap;
	swap = draw->y[0];
	draw->y[0] = draw->y[1];
	draw->y[1] = swap;
}
