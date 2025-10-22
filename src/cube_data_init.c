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

void	data_init(t_data *data, t_img *img, t_draw *draw, t_map *map)
{
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		printf("%s", MLX_FAIL);
		exit(1);
	}
	data_value_init(data, img, draw, map);
}

void	data_value_init(t_data *data, t_img *img, t_draw *draw, t_map *map)
{
	data->x = PROJ_W;
	data->y = PROJ_H;
	data->img = img;
	data->draw = draw;
	data->map = map;
	draw->scale = 1;
}

/*
	mlx window is initialized separately to allow for various checks
	without having to open/close any window in case something goes wrong
*/
void	mlx_data_init(t_data *data)
{
	data->win = mlx_new_window(data->mlx, data->x, data->y, "Cube3D");
	if (data->mlx == NULL || data->win == NULL)
		mlx_close(data);
	set_hook(data);
}
// img->img = mlx_new_image(data->mlx, data->x, data->y);|| img->img == NULL
// img->addr = mlx_get_data_addr(img->img, &img->bpp,
	// 		&(img->line_len), &img->endian);
