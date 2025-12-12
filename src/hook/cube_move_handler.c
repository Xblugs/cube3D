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

static void	move_prep(t_raycast *rc);
static void	forward_handler(t_data *data, t_raycast *rc);
static void	backward_handler(t_data *data, t_raycast *rc);
static void	angle_handler(int key, t_data *data);

/*
	move values depend on current orientation
	use arrow key and [wasd] for movement

	TODO:
	manage in mouse_hook then call the function with emulated key depending
		on where we clicked on screen?
	
				UP
			╔═══════╗			Or bind LMD / RMB and mousewheel?		
			║ \   / ║				+ make sure it doesn't conflict
			║  \ /	║				with some other Kb input
	TURN  	║   X   ║ 	TURN	
	  LEFT	║  / \	║	  RIGHT		Or even consider "banner" on the screen edge
			║ /   \ ║					
			╚═══════╝				Bonus is only rotating with mouse, EASY
				DOWN
*/
void	move_handler(int key, t_data *data)
{
	if (key == UP || key == 'w')
		forward_handler(data, data->rc);
	else if (key == DOWN || key == 's')
		backward_handler(data, data->rc);
	else if (key == LEFT || key == 'a' || key == RIGHT || key == 'd')
		angle_handler(key, data);
	exec_loop(data);
}

/*
	Re-using delta array to not allocate more memory
*/
static void	move_prep(t_raycast *rc)
{
	rc->delta[X] = cos(deg_to_rad(rc->view_angle));
	rc->delta[Y] = -sin(deg_to_rad(rc->view_angle));
	rc->delta[X] *= MOV_SPEED;
	rc->delta[Y] *= MOV_SPEED;
}

/*
	Check both directions individually
		wall licking is allowed
*/
static void	forward_handler(t_data *data, t_raycast *rc)
{
	int	x;
	int	y;

	move_prep(rc);
	x = (rc->pos[X] + rc->delta[X]) / UNIT;
	y = rc->pos[Y] / UNIT;
	if (data->map->map[x][y] != '1')
		rc->pos[X] += rc->delta[X];
	x = rc->pos[X] / UNIT;
	y = (rc->pos[Y] + rc->delta[Y]) / UNIT;
	if (data->map->map[x][y] != '1')
		rc->pos[Y] += rc->delta[Y];
}

static void	backward_handler(t_data *data, t_raycast *rc)
{
	int	x;
	int	y;

	move_prep(rc);
	x = (rc->pos[X] - rc->delta[X]) / UNIT;
	y = rc->pos[Y] / UNIT;
	if (data->map->map[x][y] != '1')
		rc->pos[X] -= rc->delta[X];
	x = rc->pos[X] / UNIT;
	y = (rc->pos[Y] - rc->delta[Y]) / UNIT;
	if (data->map->map[x][y] != '1')
		rc->pos[Y] -= rc->delta[Y];
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
