/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:46:31 by cczerwin          #+#    #+#             */
/*   Updated: 2025/10/15 10:46:33 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	mlx_close_tex(t_data *data);

/*
	Close wrapper
*/
int	mlx_close(t_data *data)
{
	mlx_close_tex(data);
	if (data->img->img != NULL)
		mlx_destroy_image(data->mlx, data->img->img);
	if (data->win != NULL)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx != NULL)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(0);
	return (0);
}
// TODO: Add back once merge with parsing
// if (data->map->map != NULL)
// 	char_cleanup(data->map->map, data->map->line);

/*
	Free texture related memory
*/
static int	mlx_close_tex(t_data *data)
{
	if (data->tex->img[N] != NULL)
		mlx_destroy_image(data->mlx, data->tex->img[N]);
	if (data->tex->img[W] != NULL)
		mlx_destroy_image(data->mlx, data->tex->img[W]);
	if (data->tex->img[S] != NULL)
		mlx_destroy_image(data->mlx, data->tex->img[S]);
	if (data->tex->img[E] != NULL)
		mlx_destroy_image(data->mlx, data->tex->img[E]);
	return (0);
}

/*
	Force clear the img from data struct
*/
void	clear_screen(t_data *data)
{
	void	*black_screen;

	black_screen = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	mlx_put_image_to_window(data->mlx, data->win, black_screen, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	mlx_destroy_image(data->mlx, black_screen);
}

/*
	mlx_pixel_put with bound check to prevent crashing
		and without force-refreshing the affected image (better performances)
*/
void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
