/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_brick_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:58:01 by cczerwin          #+#    #+#             */
/*   Updated: 2025/10/22 14:58:02 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*
	Requires:
		cube_key_hook.c
		void	brick_move_handler(int keycode, t_data *data)
*/
void	brick_wall(t_data *data)
{
	int		i;
	int		j;
	int		k;
	long	wh;

	i = 0;
	j = 0;
	k = 0;
	while (data->tex->h * j < PROJ_H)
	{
		while (data->tex->w * i < PROJ_W)
		{
			wh = int_to_long(data->tex->w * i, data->tex->h * j);
			if (i == data->img->x && j == data->img->y)
				mlx_pitow(data->mlx, data->win, data->tex->img1, wh);
			else
				brick_wall_drawing(data, wh, &k);
			k++;
			if (k == 3)
				k = 0;
			i++;
		}
		i = 0;
		j++;
	}
}

void	brick_wall_drawing(t_data *data, long wh, int *k)
{
	if (*k == 0)
		mlx_pitow(data->mlx, data->win, data->tex->img2, wh);
	else if (*k == 1)
		mlx_pitow(data->mlx, data->win, data->tex->img3, wh);
	else if (*k == 2)
		mlx_pitow(data->mlx, data->win, data->tex->img4, wh);
}
