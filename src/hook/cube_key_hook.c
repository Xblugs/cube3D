/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_key_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:09:18 by cczerwin          #+#    #+#             */
/*   Updated: 2025/10/21 16:09:19 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	key_handler(int keycode, t_data *data)
{
	if (keycode == ESC)
	{
		printf(RED"ESC pressed, closing...%s\n", END);
		mlx_close(data);
	}
	else if (keycode >= 0xFF00)
		s_key_handler(keycode, data);
	if (keycode != ENTER)
		printf("Key press = [%d 0x%X '%c']\n", keycode, keycode, keycode);
	return (0);
}

// 0xFF51 to 0xFF54 = arrow keys
int	s_key_handler(int keycode, t_data *data)
{
	if (keycode >= 0xFF51 && keycode <= 0xFF54)
		test_move_handler(keycode, data);
	return (0);
}

// for testing purposes along brick_wall()
void	test_move_handler(int keycode, t_data *data)
{
	printf(BLINK_YELLOW"TEST HANDLER ! x=[%d] y=[%d]%s\n",
		data->img->x, data->img->y, END);
	if (keycode == UP && data->img->y > 0)
		data->img->y--;
	else if (keycode == DOWN && data->img->y < (PROJ_H / UNIT_SIZE) - 1)
		data->img->y++;
	else if (keycode == LEFT && data->img->x > 0)
		data->img->x--;
	else if (keycode == RIGHT && data->img->x < (PROJ_W / UNIT_SIZE) - 1)
		data->img->x++;
	brick_wall(data);
}
