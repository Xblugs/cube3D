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

static void	angle_handler(int key, t_data *data);

/*
	move values depend on current orientation
	use arrow key and [wasd] for movement

	TODO: move handler actual calc into regular function to link mouse later on
	forward_handler()
	backward_handler()
	+ Make a wall detection + if(move value > dist to wall), move to wall (-1)

	manage in mouse_hook then call the function with emulated key depending
		on where we clicked on screen?
	
				UP
			╔═══════╗			Or bind LMD / RMB and mousewheel?		
			║ \   / ║				+ make sure it doesn't conflict
			║  \ /	║				with some other Kb input
	TURN  	║   X   ║ 	TURN	
	  LEFT	║  / \	║	  RIGHT	
			║ /   \ ║					
			╚═══════╝
				DOWN
*/
void	move_handler(int key, t_data *data)
{
	int	mov;

	mov = MOV_SCALE;
	if (key == UP || key == 'w')
	{
		data->rc->pos[X] += (cos(deg_to_rad(data->rc->view_angle)) * mov);
		data->rc->pos[Y] -= (sin(deg_to_rad(data->rc->view_angle)) * mov);
	}
	else if (key == DOWN || key == 's')
	{
		data->rc->pos[X] -= (cos(deg_to_rad(data->rc->view_angle)) * mov);
		data->rc->pos[Y] += (sin(deg_to_rad(data->rc->view_angle)) * mov);
	}
	else if (key == LEFT || key == 'a' || key == RIGHT || key == 'd')
		angle_handler(key, data);
}

static void	angle_handler(int key, t_data *data)
{
	if (key == LEFT || key == 'a')
		data->rc->view_angle += 10;
	else if (key == RIGHT || key == 'd')
	{
		data->rc->view_angle -= 10;
		if (data->rc->view_angle < 0)
			data->rc->view_angle += 360;
	}
	data->rc->view_angle %= 360;
}

/*
	for testing purposes along brick_wall()
	arrow keys to move the brick wall on the mosaic

	To be completely deleted or commented once unused
*/
// void	brick_move_handler(int key, t_data *data)
// {
// 	if (key == UP && data->img->y > 0)
// 		data->img->y--;
// 	else if (key == DOWN && data->img->y < (HEIGHT / UNIT) - 1)
// 		data->img->y++;
// 	else if (key == LEFT && data->img->x > 0)
// 		data->img->x--;
// 	else if (key == RIGHT && data->img->x < (WIDTH / UNIT) - 1)
// 		data->img->x++;
// 	printf(BLINK_YELLOW"TEST HANDLER ! x=[%d] y=[%d]%s\n",
// 		data->img->x, data->img->y, END);
// 	brick_wall(data);
// }
