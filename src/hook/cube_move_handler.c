/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_move_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:48:08 by cczerwin          #+#    #+#             */
/*   Updated: 2025/10/24 16:48:09 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*
	move values depend on current orientation
	currently arrow key are used on brick_handler and [wasd] for player pos
	TODO: change this comment and comment brick_handler once it's out of prod
*/
void	move_handler(int key, t_data *data)
{
	int	mov;

	mov = MOV_SCALE;
	if (key == UP || key == DOWN || key == 'w' || key == 's')
	{
		if (key == UP || key == 'w')
		{
			data->rc->pos[X] += (cos(deg_to_rad(data->rc->view_angle)) * mov);
			data->rc->pos[Y] -= (sin(deg_to_rad(data->rc->view_angle)) * mov);
		}
		else
		{
			data->rc->pos[X] -= (cos(deg_to_rad(data->rc->view_angle)) * mov);
			data->rc->pos[Y] += (sin(deg_to_rad(data->rc->view_angle)) * mov);
		}
	}
	else if (key == LEFT || key == 'a')
		data->rc->view_angle += 10;
	else if (key == RIGHT || key == 'd')
	{
		data->rc->view_angle -= 10;
		if (data->rc->view_angle < 0)
			data->rc->view_angle += 360;
	}
	data->rc->view_angle %= 360;
}

// for testing purposes along brick_wall()
void	brick_move_handler(int key, t_data *data)
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
