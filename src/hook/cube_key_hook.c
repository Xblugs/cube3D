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

static int	s_key_handler(int key, t_data *data);
static void	brick_move_handler(int key, t_data *data);

int	key_handler(int key, t_data *data)
{
	if (key == ESC)
	{
		printf(RED"ESC pressed, closing...%s\n", END);
		mlx_close(data);
	}
	else if (key >= 0xFF00)
		s_key_handler(key, data);
	else if (key == 'w' || key == 'a' || key == 's' || key == 'd')
		move_handler(key, data);
	if (key != ENTER)
		printf("Key press = [%d 0x%X '%c']\n", key, key, key);
	return (0);
}

// 0xFF51 to 0xFF54 = arrow keys
static int	s_key_handler(int key, t_data *data)
{
	if ((key >= 0xFF51 && key <= 0xFF54))
		brick_move_handler(key, data);
	return (0);
}

// for testing purposes along brick_wall()
static void	brick_move_handler(int key, t_data *data)
{
	printf(BLINK_YELLOW"TEST HANDLER ! x=[%d] y=[%d]%s\n",
		data->img->x, data->img->y, END);
	if (key == UP && data->img->y > 0)
		data->img->y--;
	else if (key == DOWN && data->img->y < (HEIGHT / UNIT) - 1)
		data->img->y++;
	else if (key == LEFT && data->img->x > 0)
		data->img->x--;
	else if (key == RIGHT && data->img->x < (WIDTH / UNIT) - 1)
		data->img->x++;
	brick_wall(data);
}
