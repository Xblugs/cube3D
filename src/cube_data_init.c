/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_data_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:50:16 by cczerwin          #+#    #+#             */
/*   Updated: 2025/10/15 10:50:17 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	data_value_init(t_data *data, t_img *img, t_draw *draw);

void	data_init(t_data *data, t_img *img, t_draw *draw)
{
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		printf("%s", MLX_FAIL);
		exit(1);
	}
	data_value_init(data, img, draw);
}

static void	data_value_init(t_data *data, t_img *img, t_draw *draw)
{
	if (data != NULL)
	{
		data->img = img;
		data->draw = draw;
	}
	if (img != NULL)
	{
		*img = (t_img){0};
	}
	if (draw != NULL)
	{
		*draw = (t_draw){0};
	}
}

/*
	mlx window is initialized separately to allow for various checks
	without having to open/close any window in case something goes wrong
*/
void	mlx_data_init(t_data *data)
{
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cube3D");
	data->img->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img->addr = mlx_get_data_addr(data->img->img, &(data->img->bpp),
			&(data->img->line_len), &(data->img->endian));
	if (data->mlx == NULL || data->win == NULL || data->img->img == NULL)
		mlx_close(data);
	set_hook(data);
}
